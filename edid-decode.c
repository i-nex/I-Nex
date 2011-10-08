/*
 * Copyright 2006-2009 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/* Author: Adam Jackson <ajax@nwnk.net> */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

static int claims_one_point_oh = 0;
static int claims_one_point_two = 0;
static int claims_one_point_three = 0;
static int claims_one_point_four = 0;
static int nonconformant_digital_display = 0;
static int nonconformant_extension = 0;
static int did_detailed_timing = 0;
static int has_name_descriptor = 0;
static int name_descriptor_terminated = 0;
static int has_range_descriptor = 0;
static int has_preferred_timing = 0;
static int has_valid_checksum = 1;
static int has_valid_cvt = 1;
static int has_valid_dummy_block = 1;
static int has_valid_week = 0;
static int has_valid_year = 0;
static int has_valid_detailed_blocks = 0;
static int has_valid_extension_count = 0;
static int has_valid_descriptor_ordering = 1;
static int has_valid_descriptor_pad = 1;
static int has_valid_range_descriptor = 1;
static int has_valid_max_dotclock = 1;
static int manufacturer_name_well_formed = 0;
static int seen_non_detailed_descriptor = 0;

static int warning_excessive_dotclock_correction = 0;
static int warning_zero_preferred_refresh = 0;

static int conformant = 1;

static char *manufacturer_name(unsigned char *x)
{
    static char name[4];

    name[0] = ((x[0] & 0x7C) >> 2) + '@';
    name[1] = ((x[0] & 0x03) << 3) + ((x[1] & 0xE0) >> 5) + '@';
    name[2] = (x[1] & 0x1F) + '@';
    name[3] = 0;

    if (isupper(name[0]) && isupper(name[1]) && isupper(name[2]))
	manufacturer_name_well_formed = 1;

    return name;
}

static int
detailed_cvt_descriptor(unsigned char *x, int first)
{
    const unsigned char empty[3] = { 0, 0, 0 };
    char *names[] = { "50", "60", "75", "85" };
    int width, height;
    int valid = 1;
    int fifty = 0, sixty = 0, seventyfive = 0, eightyfive = 0, reduced = 0;

    if (!first && !memcmp(x, empty, 3))
	return valid;

    height = x[0];
    height |= (x[1] & 0xf0) << 4;
    height++;
    height *= 2;

    switch (x[1] & 0x0c) {
    case 0x00:
	width = (height * 4) / 3; break;
    case 0x04:
	width = (height * 16) / 9; break;
    case 0x08:
	width = (height * 16) / 10; break;
    case 0x0c:
	width = (height * 15) / 9; break;
    }

    if (x[1] & 0x03)
	valid = 0;
    if (x[2] & 0x80)
	valid = 0;
    if (!(x[2] & 0x1f))
	valid = 0;

    fifty	= (x[2] & 0x10);
    sixty	= (x[2] & 0x08);
    seventyfive = (x[2] & 0x04);
    eightyfive  = (x[2] & 0x02);
    reduced	= (x[2] & 0x01);

    if (!valid) {
	printf("    (broken)\n");
    } else {
	printf("    %dx%d @ ( %s%s%s%s%s) Hz (%s%s preferred)\n", width, height,
		fifty ? "50 " : "",
		sixty ? "60 " : "",
		seventyfive ? "75 " : "",
		eightyfive ? "85 " : "",
		reduced ? "60RB " : "",
		names[(x[2] & 0x60) >> 5],
		(((x[2] & 0x60) == 0x20) && reduced) ? "RB" : "");
    }

    return valid;
}

/* 1 means valid data */
static int
detailed_block(unsigned char *x, int in_extension)
{
    static unsigned char name[53];
    int ha, hbl, hso, hspw, hborder, va, vbl, vso, vspw, vborder;
    int i;
    char phsync, pvsync, *syncmethod;

#if 0
    printf("Hex of detail: ");
    for (i = 0; i < 18; i++)
	printf("%02x", x[i]);
    printf("\n");
#endif

    if (x[0] == 0 && x[1] == 0) {
	/* Monitor descriptor block, not detailed timing descriptor. */
	if (x[2] != 0) {
	    /* 1.3, 3.10.3 */
	    printf("Monitor descriptor block has byte 2 nonzero (0x%02x)\n",
		   x[2]);
	    has_valid_descriptor_pad = 0;
	}
	if (x[3] != 0xfd && x[4] != 0x00) {
	    /* 1.3, 3.10.3 */
	    printf("Monitor descriptor block has byte 4 nonzero (0x%02x)\n",
		   x[4]);
	    has_valid_descriptor_pad = 0;
	}

	seen_non_detailed_descriptor = 1;
	if (x[3] <= 0xF) {
	    /*
             * in principle we can decode these, if we know what they are.
             * 0x0f seems to be common in laptop panels.
             * 0x0e is used by EPI: http://www.epi-standard.org/
             */
	    printf("Manufacturer-specified data, tag %d\n", x[3]);
	    return 1;
	}
	switch (x[3]) {
	case 0x10:
	    printf("Dummy block\n");
	    for (i = 5; i < 18; i++)
		if (x[i] != 0x00)
		    has_valid_dummy_block = 0;
	    return 1;
	case 0xF7:
	    /* TODO */
	    printf("Established timings III\n");
	    return 1;
	case 0xF8:
	{
	    int valid_cvt = 1; /* just this block */
	    printf("CVT 3-byte code descriptor:\n");
	    if (x[5] != 0x01) {
		has_valid_cvt = 0;
		return 0;
	    }
	    for (i = 0; i < 4; i++)
		valid_cvt &= detailed_cvt_descriptor(x + 6 + (i * 3), (i == 0));
	    has_valid_cvt &= valid_cvt;
	    return valid_cvt;
	}
	case 0xF9:
	    /* TODO */
	    printf("Color management data\n");
	    return 1;
	case 0xFA:
	    /* TODO */
	    printf("More standard timings\n");
	    return 1;
	case 0xFB:
	    /* TODO */
	    printf("Color point\n");
	    return 1;
	case 0xFC:
	    /* XXX should check for spaces after the \n */
	    /* XXX check: terminated with 0x0A, padded with 0x20 */
	    has_name_descriptor = 1;
	    if (strchr((char *)name, '\n')) return 1;
	    strncat((char *)name, (char *)x + 5, 13);
	    if (strchr((char *)name, '\n')) {
		name_descriptor_terminated = 1;
		printf("Monitor name: %s", name);
	    }
	    return 1;
	case 0xFD:
	{
	    int h_max_offset = 0, h_min_offset = 0;
	    int v_max_offset = 0, v_min_offset = 0;
	    int is_cvt = 0;
	    has_range_descriptor = 1;
	    /* 
	     * XXX todo: implement feature flags, vtd blocks
	     * XXX check: ranges are well-formed; block termination if no vtd
	     */
	    if (claims_one_point_four) {
		if (x[4] & 0x02) {
		    v_max_offset = 255;
		    if (x[4] & 0x01) {
			v_min_offset = 255;
		    }
		}
		if (x[4] & 0x04) {
		    h_max_offset = 255;
		    if (x[4] & 0x03) {
			h_min_offset = 255;
		    }
		}
	    } else if (x[4]) {
		has_valid_range_descriptor = 0;
	    }

	    /*
	     * despite the values, this is not a bitfield.
	     * XXX only 0x00 and 0x02 are legal for pre-1.4
	     */
	    switch (x[10]) {
	    case 0x00: /* default gtf */
		break;
	    case 0x01: /* range limits only */
		break;
	    case 0x02: /* secondary gtf curve */
		break;
	    case 0x04: /* cvt */
		is_cvt = 1;
		break;
	    default: /* invalid */
		break;
	    }

	    if (x[5] + v_min_offset > x[6] + v_max_offset)
		has_valid_range_descriptor = 0;
	    if (x[7] + h_min_offset > x[8] + h_max_offset)
		has_valid_range_descriptor = 0;
	    printf("Monitor ranges: %d-%dHZ vertical, %d-%dkHz horizontal",
		   x[5] + v_min_offset, x[6] + v_max_offset,
		   x[7] + h_min_offset, x[8] + h_max_offset);
	    if (x[9])
		printf(", max dotclock %dMHz\n", x[9] * 10);
	    else {
		if (claims_one_point_four)
		    has_valid_max_dotclock = 0;
		printf("\n");
	    }

	    if (is_cvt) {
		int max_h_pixels = 0;

		printf("CVT version %d.%d\n", x[11] & 0xf0 >> 4, x[11] & 0x0f);

		if (x[12] & 0xfc) {
		    int raw_offset = (x[12] & 0xfc) >> 2;
		    printf("Real max dotclock: %.2fMHz\n",
			   (x[9] * 10) - (raw_offset * 0.25));
		    if (raw_offset >= 40)
			warning_excessive_dotclock_correction = 1;
		}

		max_h_pixels = x[12] & 0x03;
		max_h_pixels <<= 8;
		max_h_pixels |= x[13];
		max_h_pixels *= 8;
		if (max_h_pixels)
		    printf("Max active pixels per line: %d\n", max_h_pixels);

		printf("Supported aspect ratios: %s %s %s %s %s\n",
			x[14] & 0x80 ? "4:3" : "",
			x[14] & 0x40 ? "16:9" : "",
			x[14] & 0x20 ? "16:10" : "",
			x[14] & 0x10 ? "5:4" : "",
			x[14] & 0x08 ? "15:9" : "");
		if (x[14] & 0x07)
		    has_valid_range_descriptor = 0;

		printf("Preferred aspect ratio: ");
		switch((x[15] & 0xe0) >> 5) {
		case 0x00: printf("4:3"); break;
		case 0x01: printf("16:9"); break;
		case 0x02: printf("16:10"); break;
		case 0x03: printf("5:4"); break;
		case 0x04: printf("15:9"); break;
		default: printf("(broken)"); break;
		}
		printf("\n");

		if (x[15] & 0x04)
		    printf("Supports CVT standard blanking\n");
		if (x[15] & 0x10)
		    printf("Supports CVT reduced blanking\n");

		if (x[15] & 0x07)
		    has_valid_range_descriptor = 0;

		if (x[16] & 0xf0) {
		    printf("Supported display scaling:\n");
		    if (x[16] & 0x80)
			printf("    Horizontal shrink\n");
		    if (x[16] & 0x40)
			printf("    Horizontal stretch\n");
		    if (x[16] & 0x20)
			printf("    Vertical shrink\n");
		    if (x[16] & 0x10)
			printf("    Vertical stretch\n");
		}

		if (x[16] & 0x0f)
		    has_valid_range_descriptor = 0;

		if (x[17])
		    printf("Preferred vertical refresh: %d Hz\n", x[17]);
		else
		    warning_zero_preferred_refresh = 1;
	    }

	    /*
	     * Slightly weird to return a global, but I've never seen any
	     * EDID block wth two range descriptors, so it's harmless.
	     */
	    return has_valid_range_descriptor;
	}
	case 0xFE:
            /*
             * TODO: Two of these in a row, in the third and fouth slots,
             * seems to be specified by SPWG: http://www.spwg.org/
             */
	    /* XXX check: terminated with 0x0A, padded with 0x20 */
	    printf("ASCII string: %s", x+5);
	    return 1;
	case 0xFF:
	    /* XXX check: terminated with 0x0A, padded with 0x20 */
	    printf("Serial number: %s", x+5);
	    return 1;
	default:
	    printf("Unknown monitor description type %d\n", x[3]);
	    return 0;
	}
    }

    if (seen_non_detailed_descriptor && !in_extension) {
	has_valid_descriptor_ordering = 0;
    }

    did_detailed_timing = 1;
    ha = (x[2] + ((x[4] & 0xF0) << 4));
    hbl = (x[3] + ((x[4] & 0x0F) << 8));
    hso = (x[8] + ((x[11] & 0xC0) << 2));
    hspw = (x[9] + ((x[11] & 0x30) << 4));
    hborder = x[15];
    va = (x[5] + ((x[7] & 0xF0) << 4));
    vbl = (x[6] + ((x[7] & 0x0F) << 8));
    vso = ((x[10] >> 4) + ((x[11] & 0x0C) << 2));
    vspw = ((x[10] & 0x0F) + ((x[11] & 0x03) << 4));
    vborder = x[16];
    switch ((x[17] & 0x18) >> 3) {
    case 0x00:
      syncmethod = " analog composite";
      break;
    case 0x01:
      syncmethod = " bipolar analog composite";
      break;
    case 0x02:
      syncmethod = " digital composite";
      break;
    case 0x03:
      syncmethod = "";
      break;
    }
    pvsync = (x[17] & (1 << 2)) ? '+' : '-';
    phsync = (x[17] & (1 << 1)) ? '+' : '-';

    printf("Detailed mode: Clock %.3f MHz, %d mm x %d mm\n"
	   "               %4d %4d %4d %4d hborder %d\n"
	   "               %4d %4d %4d %4d vborder %d\n"
	   "               %chsync %cvsync%s%s\n",
	    (x[0] + (x[1] << 8)) / 100.0,
	    (x[12] + ((x[14] & 0xF0) << 4)),
	    (x[13] + ((x[14] & 0x0F) << 8)),
	   ha, ha + hso, ha + hso + hspw, ha + hbl, hborder,
	   va, va + vso, va + vso + vspw, va + vbl, vborder,
	   phsync, pvsync, syncmethod, x[17] & 0x80 ? " interlaced" : ""
	  );
    /* XXX flag decode */
    
    return 1;
}

static void
do_checksum(unsigned char *x)
{
    printf("Checksum: 0x%hx", x[0x7f]);
    {
	unsigned char sum = 0;
	int i;
	for (i = 0; i < 128; i++)
	    sum += x[i];
	if (sum) {
	    printf(" (should be 0x%hx)", (unsigned char)(x[0x7f] - sum));
	    has_valid_checksum = 0;
	}
    }
    printf("\n");
}

/* CEA extension */

static void
cea_video_block(unsigned char *x)
{
    int i;
    int length = x[0] & 0x1f;

    for (i = 1; i < length; i++)
	printf("    VIC %02d %s\n", x[i] & 0x7f, x[i] & 0x80 ? "(native)" : "");
}

static void
cea_hdmi_block(unsigned char *x)
{
    int length = x[0] & 0x1f;

    printf(" (HDMI)\n");
    printf("    Source physical address %d.%d.%d.%d\n", x[4] >> 4, x[4] & 0x0f,
	   x[5] >> 4, x[5] & 0x0f);

    if (length > 5) {
	if (x[6] & 0x80)
	    printf("    Supports_AI\n");
	if (x[6] & 0x40)
	    printf("    DC_48bit\n");
	if (x[6] & 0x20)
	    printf("    DC_36bit\n");
	if (x[6] & 0x10)
	    printf("    DC_30bit\n");
	if (x[6] & 0x08)
	    printf("    DC_Y444\n");
	/* two reserved */
	if (x[6] & 0x01)
	    printf("    DVI_Dual\n");
    }

    if (length > 6)
	printf("    Maximum TMDS clock: %dMHz\n", x[7] * 5);

    /* latency info */
}

static void
cea_block(unsigned char *x)
{
    unsigned int oui;

    switch ((x[0] & 0xe0) >> 5) {
	case 0x01:
	    printf("  Audio data block\n");
	    break;
	case 0x02:
	    printf("  Video data block\n");
	    cea_video_block(x);
	    break;
	case 0x03:
	    /* yes really, endianness lols */
	    oui = (x[3] << 16) + (x[2] << 8) + x[1];
	    printf("  Vendor-specific data block, OUI %06x", oui);
	    if (oui == 0x000c03)
		cea_hdmi_block(x);
	    else
		printf("\n");
	    break;
	case 0x04:
	    printf("  Speaker allocation data block\n");
	    break;
	case 0x05:
	    printf("  VESA DTC data block\n");
	    break;
	case 0x07:
	    printf("  Extended tag: ");
	    switch (x[1]) {
		case 0x00:
		    printf("video capability data block\n");
		    break;
		case 0x01:
		    printf("vendor-specific video data block\n");
		    break;
		case 0x02:
		    printf("VESA video display device information data block\n");
		    break;
		case 0x03:
		    printf("VESA video data block\n");
		    break;
		case 0x04:
		    printf("HDMI video data block\n");
		    break;
		case 0x05:
		    printf("Colorimetry data block\n");
		    break;
		case 0x10:
		    printf("CEA miscellaneous audio fields\n");
		    break;
		case 0x11:
		    printf("Vendor-specific audio data block\n");
		    break;
		case 0x12:
		    printf("HDMI audio data block\n");
		    break;
		default:
		    if (x[1] >= 6 && x[1] <= 15)
			printf("Reserved video block (%02x)\n", x[1]);
		    else if (x[1] >= 19 && x[1] <= 31)
			printf("Reserved audio block (%02x)\n", x[1]);
		    else
			printf("Unknown (%02x)\n", x[1]);
		    break;
	    }
	    break;
	default:
	{
	    int tag = (*x & 0xe0) >> 5;
	    int length = *x & 0x1f;
	    printf("  Unknown tag %d, length %d (raw %02x)\n", tag, length, *x);
	    break;
	}
    }
}

static int
parse_cea(unsigned char *x)
{
    int ret = 0;
    int version = x[1];
    int offset = x[2];
    unsigned char *detailed;

    if (version >= 1) do {
	if (version == 1 && x[3] != 0)
	    ret = 1;

	if (offset < 4)
	    break;

	if (version < 3) {
	    printf("%d 8-byte timing descriptors\n", (offset - 4) / 8);
	    if (offset - 4 > 0)
		/* do stuff */ ;
	} else if (version == 3) {
	    int i;
	    printf("%d bytes of CEA data\n", offset - 4);
	    for (i = 4; i < offset; i += (x[i] & 0x1f) + 1) {
		cea_block(x + i);
	    }
	}
	
	if (version >= 2) {    
	    if (x[3] & 0x80)
		printf("Underscans PC formats by default\n");
	    if (x[3] & 0x40)
		printf("Basic audio support\n");
	    if (x[3] & 0x20)
		printf("Supports YCbCr 4:4:4\n");
	    if (x[3] & 0x10)
		printf("Supports YCbCr 4:2:2\n");
	    printf("%d native detailed modes\n", x[3] & 0x0f);
	}

	for (detailed = x + offset; detailed + 18 < x + 127; detailed += 18)
	    if (detailed[0])
		detailed_block(detailed, 1);
    } while (0);

    do_checksum(x);

    return ret;
}

/* generic extension code */

static void
extension_version(unsigned char *x)
{
    printf("Extension version: %d\n", x[1]);
}

static int
parse_extension(unsigned char *x)
{
    int conformant_extension;
    printf("\n");

    switch(x[0]) {
    case 0x02:
	printf("CEA extension block\n");
	extension_version(x);
	conformant_extension = parse_cea(x);
	break;
    case 0x10: printf("VTB extension block\n"); break;
    case 0x40: printf("DI extension block\n"); break;
    case 0x50: printf("LS extension block\n"); break;
    case 0x60: printf("DPVL extension block\n"); break;
    case 0xF0: printf("Block map\n"); break;
    case 0xFF: printf("Manufacturer-specific extension block\n");
    default:
	printf("Unknown extension block\n");
	break;
    }

    printf("\n");

    return conformant_extension;
}

static int edid_lines = 0;

static unsigned char *
extract_edid(int fd)
{
    char *ret = NULL;
    char *start, *c;
    unsigned char *out = NULL;
    int state = 0;
    int lines = 0;
    int i;
    int out_index = 0;
    int len, size;

    size = 1 << 10;
    ret = malloc(size);
    len = 0;

    if (ret == NULL)
        return NULL;

    for (;;) {
	i = read(fd, ret + len, size - len);
	if (i < 0) {
	    free(ret);
	    return NULL;
	}
	if (i == 0)
	    break;
	len += i;
	if (len == size) {
            char *t;
            size <<= 1;
	    t = realloc(ret, size);
            if (t == NULL) {
                free(ret);
                return NULL;
            }
            ret = t;
        }
    }

    start = strstr(ret, "EDID_DATA:");
    if (start == NULL)
    	start = strstr(ret, "EDID:");
    /* Look for xrandr --verbose output (8 lines of 16 hex bytes) */
    if (start != NULL) {
	const char indentation1[] = "                ";
	const char indentation2[] = "\t\t";
	const char *indentation;
	unsigned char *out;
	char *s;

	out = malloc(128);
	if (out == NULL)
	    return NULL;

	for (i = 0; i < 8; i++) {
	    int j;

	    /* Get the next start of the line of EDID hex. */
	    s = strstr(start, indentation = indentation1);
	    if (!s)
		s = strstr(start, indentation = indentation2);
	    if (s == NULL) {
		free(ret);
		free(out);
		return NULL;
	    }
	    start = s + strlen(indentation);

	    c = start;
	    for (j = 0; j < 16; j++) {
		char buf[3];
		/* Read a %02x from the log */
		if (!isxdigit(c[0]) || !isxdigit(c[1])) {
		    free(ret);
		    free(out);
		    return NULL;
		}
		buf[0] = c[0];
		buf[1] = c[1];
		buf[2] = 0;
		out[out_index++] = strtol(buf, NULL, 16);
		c += 2;
	    }
	}

	free(ret);
	return out;
    }

    /* wait, is this a log file? */
    for (i = 0; i < 8; i++) {
	if (!isascii(ret[i])) {
	    edid_lines = len / 16;
	    return (unsigned char *)ret;
	}
    }

    /* I think it is, let's go scanning */
    if (!(start = strstr(ret, "EDID (in hex):")))
	return (unsigned char *)ret;
    if (!(start = strstr(start, "(II)")))
	return (unsigned char *)ret;

    for (c = start; *c; c++) {
	if (state == 0) {
	    char *s;
	    /* skip ahead to the : */
	    s = strstr(c, ": \t");
	    if (!s)
		s = strstr(c, ":     ");
	    if (!s)
		break;
	    c = s;
	    /* and find the first number */
	    while (!isxdigit(c[1]))
		c++;
	    state = 1;
	    lines++;
	    out = realloc(out, lines * 16);
	} else if (state == 1) {
	    char buf[3];
	    /* Read a %02x from the log */
	    if (!isxdigit(*c)) {
		state = 0;
		continue;
	    }
	    buf[0] = c[0];
	    buf[1] = c[1];
	    buf[2] = 0;
	    out[out_index++] = strtol(buf, NULL, 16);
	    c++;
	}
    }

    edid_lines = lines;

    free(ret);

    return out;
}

static const struct {
  int x, y, refresh;
} established_timings[] = {
  /* 0x23 bit 7 - 0 */
  {720, 400, 70},
  {720, 400, 88},
  {640, 480, 60},
  {640, 480, 67},
  {640, 480, 72},
  {640, 480, 75},
  {800, 600, 56},
  {800, 600, 60},
  /* 0x24 bit 7 - 0 */
  {800, 600, 72},
  {800, 600, 75},
  {832, 624, 75},
  {1280, 768, 87},
  {1024, 768, 60},
  {1024, 768, 70},
  {1024, 768, 75},
  {1280, 1024, 75},
  /* 0x25 bit 7*/
  {1152, 870, 75},
};

static void print_subsection(char *name, unsigned char *edid, int start,
			     int end)
{
    int i;

    printf("%s:", name);
    for (i = strlen(name); i < 15; i++)
	printf(" ");
    for (i = start; i <= end; i++)
	printf(" %02x", edid[i]);
    printf("\n");
}

static void dump_breakdown(unsigned char *edid)
{
    printf("Extracted contents:\n");
    print_subsection("header", edid, 0, 7);
    print_subsection("serial number", edid, 8, 17);
    print_subsection("version", edid,18, 19);
    print_subsection("basic params", edid, 20, 24);
    print_subsection("chroma info", edid, 25, 34);
    print_subsection("established", edid, 35, 37);
    print_subsection("standard", edid, 38, 53);
    print_subsection("descriptor 1", edid, 54, 71);
    print_subsection("descriptor 2", edid, 72, 89);
    print_subsection("descriptor 3", edid, 90, 107);
    print_subsection("descriptor 4", edid, 108, 125);
    print_subsection("extensions", edid, 126, 126);
    print_subsection("checksum", edid, 127, 127);
    printf("\n");
}

int main(int argc, char **argv)
{
    int fd;
    unsigned char *edid;
    unsigned char *x;
    time_t the_time;
    struct tm *ptm;
    int analog, i;

    if (argc != 2) {
	fd = 0;
    } else {
	if ((fd = open(argv[1], O_RDONLY)) == -1) {
	    perror(argv[1]);
	    return 1;
	}
    }

    edid = extract_edid(fd);
    if (!edid) {
	fprintf(stderr, "edid extract failed\n");
	return 1;
    }
    if (fd != 0)
	close(fd);

    dump_breakdown(edid);

    if (!edid || memcmp(edid, "\x00\xFF\xFF\xFF\xFF\xFF\xFF\x00", 8)) {
	printf("No header found\n");
	// return 1;
    }

    printf("Manufacturer: %s Model %x Serial Number %u\n",
	    manufacturer_name(edid + 0x08),
	    (unsigned short)(edid[0x0A] + (edid[0x0B] << 8)),
	    (unsigned int)(edid[0x0C] + (edid[0x0D] << 8)
			   + (edid[0x0E] << 16) + (edid[0x0F] << 24)));
    /* XXX need manufacturer ID table */

    time(&the_time);
    ptm = localtime(&the_time);
    if (edid[0x10] < 55 || edid[0x10] == 0xff) {
	has_valid_week = 1;
	if (edid[0x11] > 0x0f) {
	    if (edid[0x10] == 0xff) {
		has_valid_year = 1;
		printf("Made week %hd of model year %hd\n", edid[0x10],
		       edid[0x11]);
	    } else if (edid[0x11] + 90 <= ptm->tm_year) {
		has_valid_year = 1;
		printf("Made week %hd of %hd\n", edid[0x10], edid[0x11] + 1990);
	    }
	}
    }

    printf("EDID version: %hd.%hd\n", edid[0x12], edid[0x13]);
    if (edid[0x12] == 1) {
	if (edid[0x13] > 4) {
	    printf("Claims > 1.4, assuming 1.4 conformance\n");
	    edid[0x13] = 4;
	}
	switch (edid[0x13]) {
	case 4:
	    claims_one_point_four = 1;
	case 3:
	    claims_one_point_three = 1;
	case 2:
	    claims_one_point_two = 1;
	default:
	    break;
	}
	claims_one_point_oh = 1;
    }

    /* display section */

    if (edid[0x14] & 0x80) {
	int conformance_mask;
	analog = 0;
	printf("Digital display\n");
	if (claims_one_point_four) {
	    conformance_mask = 0;
	    if ((edid[0x14] & 0x70) == 0x00)
		printf("Color depth is undefined\n");
	    else if ((edid[0x14] & 0x70) == 0x70)
		nonconformant_digital_display = 1;
	    else
		printf("%d bits per primary color channel\n",
		       ((edid[0x14] & 0x70) >> 3) + 4);

	    switch (edid[0x14] & 0x0f) {
	    case 0x00: printf("Digital interface is not defined\n"); break;
	    case 0x01: printf("DVI interface\n"); break;
	    case 0x02: printf("HDMI-a interface\n"); break;
	    case 0x03: printf("HDMI-b interface\n"); break;
	    case 0x04: printf("MDDI interface\n"); break;
	    case 0x05: printf("DisplayPort interface\n"); break;
	    default:
		nonconformant_digital_display = 1;
	    }
	} else if (claims_one_point_two) {
	    conformance_mask = 0x7E;
	    if (edid[0x14] & 0x01) {
		printf("DFP 1.x compatible TMDS\n");
	    }
	} else conformance_mask = 0x7F;
	if (!nonconformant_digital_display)
	    nonconformant_digital_display = edid[0x14] & conformance_mask;
    } else {
	analog = 1;
	int voltage = (edid[0x14] & 0x60) >> 5;
	int sync = (edid[0x14] & 0x0F);
	printf("Analog display, Input voltage level: %s V\n",
	       voltage == 3 ? "0.7/0.7" :
	       voltage == 2 ? "1.0/0.4" :
	       voltage == 1 ? "0.714/0.286" :
	       "0.7/0.3");

	if (claims_one_point_four) {
	    if (edid[0x14] & 0x10)
		printf("Blank-to-black setup/pedestal\n");
	    else
		printf("Blank level equals black level\n");
	} else if (edid[0x14] & 0x10) {
	    /*
	     * XXX this is just the X text.  1.3 says "if set, display expects
	     * a blank-to-black setup or pedestal per appropriate Signal
	     * Level Standard".  Whatever _that_ means.
	     */
	    printf("Configurable signal levels\n");
	}

	printf("Sync: %s%s%s%s\n", sync & 0x08 ? "Separate " : "",
	       sync & 0x04 ? "Composite " : "",
	       sync & 0x02 ? "SyncOnGreen " : "",
	       sync & 0x01 ? "Serration " : "");
    }

    if (edid[0x15] && edid[0x16])
	printf("Maximum image size: %d cm x %d cm\n", edid[0x15], edid[0x16]);
    else if (claims_one_point_four && (edid[0x15] || edid[0x16])) {
	if (edid[0x15])
	    printf("Aspect ratio is %f (landscape)\n", 100.0/(edid[0x16] + 99));
	else
	    printf("Aspect ratio is %f (portrait)\n", 100.0/(edid[0x15] + 99));
    } else {
	/* Either or both can be zero for 1.3 and before */
	printf("Image size is variable\n");
    }

    if (edid[0x17] == 0xff) {
	if (claims_one_point_four)
	    printf("Gamma is defined in an extension block\n");
	else
	    /* XXX Technically 1.3 doesn't say this... */
	    printf("Gamma: 1.0\n");
    } else printf("Gamma: %.2f\n", ((edid[0x17] + 100.0) / 100.0));

    if (edid[0x18] & 0xE0) {
	printf("DPMS levels:");
	if (edid[0x18] & 0x80) printf(" Standby");
	if (edid[0x18] & 0x40) printf(" Suspend");
	if (edid[0x18] & 0x20) printf(" Off");
	printf("\n");
    }

    /* FIXME: this is from 1.4 spec, check earlier */
    if (analog) {
	switch (edid[0x18] & 0x18) {
	case 0x00: printf("Monochrome or grayscale display\n"); break;
	case 0x08: printf("RGB color display\n"); break;
	case 0x10: printf("Non-RGB color display\n"); break;
	case 0x18: printf("Undefined display color type\n");
	}
    } else {
	printf("Supported color formats: RGB 4:4:4");
	if (edid[0x18] & 0x10)
	    printf(", YCrCb 4:4:4");
	if (edid[0x18] & 0x08)
	    printf(", YCrCb 4:2:2");
	printf("\n");
    }

    if (edid[0x18] & 0x04)
	printf("Default (sRGB) color space is primary color space\n");
    if (edid[0x18] & 0x02) {
	printf("First detailed timing is preferred timing\n");
	has_preferred_timing = 1;
    }
    if (edid[0x18] & 0x01)
	printf("Supports GTF timings within operating range\n");

    /* XXX color section */

    printf("Established timings supported:\n");
    for (i = 0; i < 17; i++) {
      if (edid[0x23 + i / 8] & (1 << (7 - i % 8))) {
	printf("  %dx%d@%dHz\n", established_timings[i].x,
	       established_timings[i].y, established_timings[i].refresh);
      }
    }

    printf("Standard timings supported:\n");
    for (i = 0; i < 8; i++) {
      uint8_t b1 = edid[0x26 + i * 2], b2 = edid[0x26 + i * 2 + 1];
      unsigned int x, y, refresh;

      if (b1 == 0x01 && b2 == 0x01)
	continue;

      if (b1 == 0) {
	printf("non-conformant standard timing (0 horiz)\n");
	continue;
      }
      x = (b1 + 31) * 8;
      switch ((b2 >> 6) & 0x3) {
      case 0x00:
	y = x * 10 / 16;
	break;
      case 0x01:
	y = x * 3 / 4;
	break;
      case 0x02:
	y = x * 4 / 5;
	break;
      case 0x03:
	y = x * 9 / 15;
	break;
      }
      refresh = 60 + (b2 & 0x3f);

      printf("  %dx%d@%dHz\n", x, y, refresh);
    }

    /* detailed timings */
    has_valid_detailed_blocks = detailed_block(edid + 0x36, 0);
    if (has_preferred_timing && !did_detailed_timing)
	has_preferred_timing = 0; /* not really accurate... */
    has_valid_detailed_blocks &= detailed_block(edid + 0x48, 0);
    has_valid_detailed_blocks &= detailed_block(edid + 0x5A, 0);
    has_valid_detailed_blocks &= detailed_block(edid + 0x6C, 0);

    /* check this, 1.4 verification guide says otherwise */
    if (edid[0x7e]) {
	printf("Has %d extension blocks\n", edid[0x7e]);
	/* 2 is impossible because of the block map */
	if (edid[0x7e] != 2)
	    has_valid_extension_count = 1;
    } else {
	has_valid_extension_count = 1;
    }

    do_checksum(edid);

    x = edid;
    for (edid_lines /= 8; edid_lines > 1; edid_lines--) {
	x += 128;
	nonconformant_digital_display += parse_extension(x);
    }

    if (claims_one_point_three) {
	if (nonconformant_digital_display ||
	    !has_valid_descriptor_pad ||
	    !has_name_descriptor ||
	    !name_descriptor_terminated ||
	    !has_preferred_timing ||
	    !has_range_descriptor)
	    conformant = 0;
	if (!conformant)
	    printf("EDID block does NOT conform to EDID 1.3!\n");
	if (nonconformant_digital_display)
	    printf("\tDigital display field contains garbage: %x\n",
		   nonconformant_digital_display);
	if (!has_name_descriptor)
	    printf("\tMissing name descriptor\n");
	else if (!name_descriptor_terminated)
	    printf("\tName descriptor not terminated with a newline\n");
	if (!has_preferred_timing)
	    printf("\tMissing preferred timing\n");
	if (!has_range_descriptor)
	    printf("\tMissing monitor ranges\n");
	if (!has_valid_descriptor_pad) /* Might be more than just 1.3 */
	    printf("\tInvalid descriptor block padding\n");
    } else if (claims_one_point_two) {
	if (nonconformant_digital_display ||
	    (has_name_descriptor && !name_descriptor_terminated))
	    conformant = 0;
	if (!conformant)
	    printf("EDID block does NOT conform to EDID 1.2!\n");
	if (nonconformant_digital_display)
	    printf("\tDigital display field contains garbage: %x\n",
		   nonconformant_digital_display);
	if (has_name_descriptor && !name_descriptor_terminated)
	    printf("\tName descriptor not terminated with a newline\n");
    } else if (claims_one_point_oh) {
	if (seen_non_detailed_descriptor)
	    conformant = 0;
	if (!conformant)
	    printf("EDID block does NOT conform to EDID 1.0!\n");
	if (seen_non_detailed_descriptor)
	    printf("\tHas descriptor blocks other than detailed timings\n");
    }

    if (nonconformant_extension ||
	!has_valid_checksum ||
	!has_valid_cvt ||
	!has_valid_year ||
	!has_valid_week ||
	!has_valid_detailed_blocks ||
	!has_valid_dummy_block ||
	!has_valid_extension_count ||
	!has_valid_descriptor_ordering ||
	!has_valid_range_descriptor ||
	!manufacturer_name_well_formed) {
	conformant = 0;
	printf("EDID block does not conform at all!\n");
	if (nonconformant_extension)
	    printf("\tHas at least one nonconformant extension block\n");
	if (!has_valid_checksum)
	    printf("\tBlock has broken checksum\n");
	if (!has_valid_cvt)
	    printf("\tBroken 3-byte CVT blocks\n");
	if (!has_valid_year)
	    printf("\tBad year of manufacture\n");
	if (!has_valid_week)
	    printf("\tBad week of manufacture\n");
	if (!has_valid_detailed_blocks)
	    printf("\tDetailed blocks filled with garbage\n");
	if (!has_valid_dummy_block)
	    printf("\tDummy block filled with garbage\n");
	if (!has_valid_extension_count)
	    printf("\tImpossible extension block count\n");
	if (!manufacturer_name_well_formed)
	    printf("\tManufacturer name field contains garbage\n");
	if (!has_valid_descriptor_ordering)
	    printf("\tInvalid detailed timing descriptor ordering\n");
	if (!has_valid_range_descriptor)
	    printf("\tRange descriptor contains garbage\n");
	if (!has_valid_max_dotclock)
	    printf("\tEDID 1.4 block does not set max dotclock\n");
    }

    if (warning_excessive_dotclock_correction)
	printf("Warning: CVT block corrects dotclock by more than 9.75MHz\n");
    if (warning_zero_preferred_refresh)
	printf("Warning: CVT block does not set preferred refresh rate\n");

    free(edid);

    return !conformant;
}
