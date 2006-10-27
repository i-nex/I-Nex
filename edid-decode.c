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

/* booleans for determining 1.3 conformance */
int claims_one_point_two = 0;
int claims_one_point_three = 0;
int conformant_digital_display = 0;
int did_detailed_timing = 0;
int has_name_descriptor = 0;
int has_range_descriptor = 0;
int has_preferred_timing = 0;
int has_valid_checksum = 0;

static char *manufacturer_name(unsigned char *x)
{
    static char name[4];

    name[0] = ((x[0] & 0x7C) >> 2) + '@';
    name[1] = ((x[0] & 0x03) << 3) + ((x[1] & 0xE0) >> 5) + '@';
    name[2] = (x[1] & 0x1F) + '@';
    name[3] = 0;

    return name;
}

static void
detailed_block(unsigned char *x)
{
    static unsigned char name[53];
    int ha, hbl, hso, hspw, hborder, va, vbl, vso, vspw, vborder;

    if (!x[0] && !x[1] && !x[2] && !x[4]) {
	switch (x[3]) {
	case 0x10:
	    printf("Dummy block\n");
	    return;
	case 0xFA:
	    printf("More standard timings\n");
	    return;
	case 0xFB:
	    printf("Color point\n");
	    return;
	case 0xFC:
	    has_name_descriptor = 1;
	    if (strchr((char *)name, '\n')) return;
	    strncat((char *)name, (char *)x + 5, 12);
	    if (strchr((char *)name, '\n'))
		printf("Monitor name: %s", name);
	    return;
	case 0xFD:
	    has_range_descriptor = 1;
	    printf("Monitor ranges\n");
	    return;
	case 0xFE:
	    printf("ASCII string\n");
	    return;
	case 0xFF:
	    printf("Serial number\n");
	    return;
	default:
	    printf("Unknown monitor description type %d\n", x[3]);
	    return;
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
}

static unsigned char *
extract_edid(int fd)
{
    struct stat buf;
    unsigned char *ret;

    if (fstat(fd, &buf))
	return NULL;

    ret = calloc(1, buf.st_size);
    if (!ret)
	return NULL;

    read(fd, ret, buf.st_size);

    return ret;
}

int main(int argc, char **argv)
{
    int fd;
    unsigned char *edid;
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

    if (memcmp(edid, "\x00\xFF\xFF\xFF\xFF\xFF\xFF\x00", 8)) {
	printf("No header found\n");
	return 1;
    }

    printf("Manufacturer: %s Model %x Serial Number %u\n",
	    manufacturer_name(edid + 0x08),
	    (unsigned short)edid[0x0A],
	    (unsigned int)edid[0x0C]);
    if (edid[0x11])
	printf("Made week %hd of %hd\n", edid[0x10], edid[0x11]);
    else
	printf("No manufacture date given\n");
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
	if (!(edid[0x14] & conformance_mask))
	    conformant_digital_display = 1;
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
    detailed_block(edid + 0x36);
    if (has_preferred_timing && !did_detailed_timing)
	has_preferred_timing = 0; /* not really accurate... */
    detailed_block(edid + 0x48);
    detailed_block(edid + 0x5A);
    detailed_block(edid + 0x6C);

    if (edid[0x7e])
	printf("Has %d extension blocks\n", edid[0x7e]);

    printf("Checksum: 0x%hx\n", edid[0x7f]);
    {
	unsigned char sum = 0;
	int i;
	for (i = 0; i < 128; i++)
	    sum += edid[i];
	has_valid_checksum = !sum;
    }
    if (!has_valid_checksum)
	printf("Block has broken checksum!\n");

    if (claims_one_point_three) {
	if (!conformant_digital_display ||
	    !has_name_descriptor ||
	    !has_preferred_timing ||
	    !has_range_descriptor)
	    printf("EDID block does NOT conform to EDID 1.3!\n");
    } else if (claims_one_point_two) {
	if (!conformant_digital_display)
	    printf("EDID block does NOT conform to EDID 1.2!\n");
    }

    return 0;
}
