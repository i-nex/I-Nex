/*
 * Copyright 2006 Red Hat, Inc.
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
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int claims_one_point_two = 0;
int claims_one_point_three = 0;
int nonconformant_digital_display = 0;
int did_detailed_timing = 0;
int has_name_descriptor = 0;
int name_descriptor_terminated = 0;
int has_range_descriptor = 0;
int has_preferred_timing = 0;
int has_valid_checksum = 0;
int has_valid_week = 0;
int has_valid_year = 0;
int has_valid_detailed_blocks = 0;
int has_valid_extension_count = 0;

int conformant = 1;

static char *manufacturer_name(unsigned char *x)
{
    static char name[4];

    name[0] = ((x[0] & 0x7C) >> 2) + '@';
    name[1] = ((x[0] & 0x03) << 3) + ((x[1] & 0xE0) >> 5) + '@';
    name[2] = (x[1] & 0x1F) + '@';
    name[3] = 0;

    return name;
}

/* 1 means valid data */
/* XXX need to check that timings are first */
static int
detailed_block(unsigned char *x)
{
    static unsigned char name[53];
    int ha, hbl, hso, hspw, hborder, va, vbl, vso, vspw, vborder;

    if (!x[0] && !x[1] && !x[2] && !x[4]) {
	switch (x[3]) {
	case 0x10:
	    printf("Dummy block\n");
	    return 1;
	case 0xFA:
	    printf("More standard timings\n");
	    return 1;
	case 0xFB:
	    printf("Color point\n");
	    return 1;
	case 0xFC:
	    /* XXX should check for spaces after the \n */
	    has_name_descriptor = 1;
	    if (strchr((char *)name, '\n')) return 1;
	    strncat((char *)name, (char *)x + 5, 13);
	    if (strchr((char *)name, '\n')) {
		name_descriptor_terminated = 1;
		printf("Monitor name: %s", name);
	    }
	    return 1;
	case 0xFD:
	    has_range_descriptor = 1;
	    printf("Monitor ranges\n");
	    return 1;
	case 0xFE:
	    printf("ASCII string: %s", x+5);
	    return 1;
	case 0xFF:
	    printf("Serial number\n");
	    return 1;
	default:
	    printf("Unknown monitor description type %d\n", x[3]);
	    return 0;
	}
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

    printf("Detailed mode: Clock %.3f MHz, %d mm x %d mm\n"
	   "               ha %d hbl %d hso %d hspw %d hborder %d\n"
	   "               va %d vbl %d vso %d vspw %d vborder %d\n",
	    (x[0] + (x[1] << 8)) / 100.0,
	    (x[12] + ((x[14] & 0xF0) << 4)),
	    (x[13] + ((x[14] & 0x0F) << 8)),
	    ha, hbl, hso, hspw, hborder, va, vbl, vso, vspw, vborder
	  );
    /* XXX flag decode */
    
    return 1;
}

static unsigned char *
extract_edid(int fd)
{
    struct stat buf;
    unsigned char *ret1 = NULL, *ret2 = NULL;
    int i;

    if (fstat(fd, &buf))
	return NULL;

    ret1 = calloc(1, buf.st_size);
    if (!ret1)
	return NULL;

    read(fd, ret1, buf.st_size);

    /* wait, is this a log file? */
    for (i = 0; i < 8; i++) {
	if (!isascii(ret1[i]))
	    return ret1;
    }

    /* I think it is, let's go scanning */
    unsigned char *start, *end, *c;
    unsigned char *out = NULL;
    int state = 0;
    int lines = 0;
    start = strstr(strstr(ret1, "EDID (in hex):"), "(II)");
    end = strstr(start, ": \n");
    for (c = start; c < end; c++) {
	if (state == 0) {
	    /* skip ahead to the : */
	    c = strstr(c, ":");
	    /* and find the first number */
	    while (!isxdigit(c[1]))
		c++;
	    state = 1;
	    lines++;
	    ret2 = realloc(ret2, lines * 16);
	    if (!out)
		out = ret2;
	} else if (state == 1) {
	    char buf[3];
	    if (!isxdigit(*c)) {
		state = 0;
		continue;
	    }
	    buf[0] = c[0];
	    buf[1] = c[1];
	    buf[2] = 0;
	    *out = strtol(buf, NULL, 16);
	    out++;
	    c++;
	}
    }

    free(ret1);

    return ret2;
}

int main(int argc, char **argv)
{
    int fd;
    unsigned char *edid;
    time_t the_time;
    struct tm *ptm;
    if (argc != 2) {
	printf("Need a file name\n");
	return 1;
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
	printf("Open failed\n");
	return 1;
    }

    edid = extract_edid(fd);
    close(fd);

    if (!edid || memcmp(edid, "\x00\xFF\xFF\xFF\xFF\xFF\xFF\x00", 8)) {
	printf("No header found\n");
	return 1;
    }

    printf("Manufacturer: %s Model %x Serial Number %u\n",
	    manufacturer_name(edid + 0x08),
	    (unsigned short)edid[0x0A],
	    (unsigned int)edid[0x0C]);
    /* XXX need manufacturer ID table */

    time(&the_time);
    ptm = localtime(&the_time);
    if (edid[0x10] < 55)
	has_valid_week = 1;
    if (edid[0x11] > 3 && (edid[0x11] + 90) <= ptm->tm_year)
	has_valid_year = 1;
    if (has_valid_week && has_valid_year)
	printf("Made week %hd of %hd\n", edid[0x10], edid[0x11] + 1990);

    printf("EDID version: %hd.%hd\n", edid[0x12], edid[0x13]);
    if (edid[0x12] == 1) {
	if (edid[0x13] > 3) {
	    printf("Claims > 1.3, assuming 1.3 conformance\n");
	    edid[0x13] = 3;
	}
	switch (edid[0x13]) {
	case 3:
	    claims_one_point_three = 1;
	case 2:
	    claims_one_point_two = 1;
	default:
	    break;
	}
    }

    /* display section */

    if (edid[0x14] & 0x80) {
	int conformance_mask = claims_one_point_two ? 0x7E : 0x7F;
	printf("Digital display\n");
	if (claims_one_point_two) {
	    if (edid[0x14] & 0x01) {
		printf("DFP 1.x compatible TMDS\n");
	    }
	}
	nonconformant_digital_display = edid[0x14] & conformance_mask;
    } else {
	int voltage = (edid[0x14] & 0x60) >> 5;
	int sync = (edid[0x14] & 0x0F);
	printf("Analog display, Input voltage level: %s V\n",
	       voltage == 3 ? "0.7/0.7" :
	       voltage == 2 ? "1.0/0.4" :
	       voltage == 1 ? "0.714/0.286" :
	       "0.7/0.3");
	if (edid[0x14] & 0x10)
	    printf("Configurable signal levels\n");
	printf("Sync: %s%s%s%s\n", sync & 0x08 ? "Separate " : "",
	       sync & 0x04 ? "Composite " : "",
	       sync & 0x02 ? "SyncOnGreen " : "",
	       sync & 0x01 ? "Serration " : "");
    }

    if (edid[0x15] && edid[0x16])
	printf("Maximum image size: %d cm x %d cm\n", edid[0x15], edid[0x16]);
    else
	printf("Maximum image size is variable\n");

    printf("Gamma: %.2f\n",
	    edid[0x17] == 0xff ? 1.0 : ((edid[0x17] + 100.0) / 100.0));

    if (edid[0x18] & 0xE0) {
	printf("DPMS levels:");
	if (edid[0x18] & 0x80) printf(" Standby");
	if (edid[0x18] & 0x40) printf(" Suspend");
	if (edid[0x18] & 0x20) printf(" Off");
	printf("\n");
    }

    if (edid[0x18] & 0x10)
	printf("Non-RGB color display\n");
    else if (edid[0x18] & 0x08)
	printf("RGB color display\n");
    else
	printf("Monochrome or grayscale display\n");

    if (edid[0x18] & 0x04)
	printf("Default color space is primary color space\n");
    if (edid[0x18] & 0x02) {
	printf("First detailed timing is preferred timing\n");
	has_preferred_timing = 1;
    }
    if (edid[0x18] & 0x01)
	printf("Supports GTF timings within operating range\n");

    /* XXX color section */

    /* XXX established timings */

    /* XXX standard timings */

    /* detailed timings */
    has_valid_detailed_blocks = detailed_block(edid + 0x36);
    if (has_preferred_timing && !did_detailed_timing)
	has_preferred_timing = 0; /* not really accurate... */
    has_valid_detailed_blocks &= detailed_block(edid + 0x48);
    has_valid_detailed_blocks &= detailed_block(edid + 0x5A);
    has_valid_detailed_blocks &= detailed_block(edid + 0x6C);

    if (edid[0x7e]) {
	printf("Has %d extension blocks\n", edid[0x7e]);
	/* 2 is impossible because of the block map */
	if (edid[0x7e] != 2)
	    has_valid_extension_count = 1;
    } else {
	has_valid_extension_count = 1;
    }

    printf("Checksum: 0x%hx\n", edid[0x7f]);
    {
	unsigned char sum = 0;
	int i;
	for (i = 0; i < 128; i++)
	    sum += edid[i];
	has_valid_checksum = !sum;
    }

    if (claims_one_point_three) {
	if (nonconformant_digital_display ||
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
    }

    if (!has_valid_checksum ||
	!has_valid_year ||
	!has_valid_week ||
	!has_valid_detailed_blocks ||
	!has_valid_extension_count) {
	printf("EDID block does not conform at all!\n");
	if (!has_valid_checksum)
	    printf("\tBlock has broken checksum\n");
	if (!has_valid_year)
	    printf("\tBad year of manufacture\n");
	if (!has_valid_week)
	    printf("\tBad week of manufacture\n");
	if (!has_valid_detailed_blocks)
	    printf("\tDetailed blocks filled with garbage\n");
	if (!has_valid_extension_count)
	    printf("\tImpossible extension block count\n");
    }

    free(edid);

    return 0;
}
