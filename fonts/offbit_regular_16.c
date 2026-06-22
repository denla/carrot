/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --font /Users/denislabutin/Library/Fonts/OffBit-Regular.ttf --size 16 --bpp 1 --format lvgl --range 0x20-0x7F,0x0400-0x04FF -o /Users/denislabutin/Documents/PlatformIO/Projects/CarrotOS/fonts/offbit_regular_16.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef OFFBIT_REGULAR_16
#define OFFBIT_REGULAR_16 1
#endif

#if OFFBIT_REGULAR_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0x30,

    /* U+0022 "\"" */
    0xb4,

    /* U+0023 "#" */
    0x1, 0x10, 0x4, 0x40, 0x20, 0xf, 0xff, 0x4,
    0x20, 0x10, 0x80, 0x4, 0x2, 0x20, 0xff, 0xf0,
    0x44, 0x2, 0x20, 0x8, 0x80,

    /* U+0024 "$" */
    0x8, 0x3c, 0x4a, 0x89, 0x88, 0x88, 0x0, 0x7c,
    0xb, 0x89, 0x89, 0x0, 0x7e, 0x8,

    /* U+0025 "%" */
    0x20, 0x4a, 0xa, 0x22, 0x44, 0x85, 0x10, 0x44,
    0x1, 0x0, 0xce, 0x22, 0x24, 0x45, 0x5, 0x20,
    0x40,

    /* U+0026 "&" */
    0x18, 0x4, 0x81, 0x8, 0x21, 0x2, 0x40, 0x31,
    0xc, 0x16, 0x66, 0x83, 0x10, 0x21, 0xc, 0x9e,
    0x60,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x12, 0x44, 0x88, 0x88, 0x88, 0x44, 0x21,

    /* U+0029 ")" */
    0x84, 0x22, 0x11, 0x11, 0x11, 0x22, 0x48,

    /* U+002A "*" */
    0xab, 0x88, 0xa8, 0x80,

    /* U+002B "+" */
    0x10, 0x20, 0x40, 0x8f, 0xe2, 0x4, 0x8, 0x10,

    /* U+002C "," */
    0x58,

    /* U+002D "-" */
    0xfe,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x4, 0x10, 0x41, 0x8, 0x21, 0x4, 0x30, 0x84,
    0x10, 0x82, 0x0,

    /* U+0030 "0" */
    0x3c, 0x42, 0x81, 0x83, 0x85, 0x89, 0x91, 0xb1,
    0xc1, 0x81, 0x42, 0x3c,

    /* U+0031 "1" */
    0x23, 0x28, 0x42, 0x10, 0x84, 0x21, 0x9, 0xf0,

    /* U+0032 "2" */
    0x3c, 0x42, 0x81, 0x81, 0x0, 0x2, 0x4, 0x8,
    0x10, 0x20, 0x40, 0xff,

    /* U+0033 "3" */
    0x3c, 0x42, 0x81, 0x1, 0x0, 0x2, 0x3c, 0x2,
    0x1, 0x81, 0x42, 0x3c,

    /* U+0034 "4" */
    0x1, 0x0, 0xc0, 0x50, 0x24, 0x11, 0x8, 0x42,
    0x13, 0x4, 0xff, 0xc0, 0x40, 0x10, 0x4,

    /* U+0035 "5" */
    0x7e, 0x40, 0x40, 0x80, 0x80, 0xbc, 0xc2, 0x81,
    0x1, 0x81, 0x42, 0x3c,

    /* U+0036 "6" */
    0x3c, 0x42, 0x81, 0x80, 0x80, 0x9c, 0xa2, 0xc1,
    0x81, 0x81, 0x42, 0x3c,

    /* U+0037 "7" */
    0xfe, 0x4, 0x8, 0x20, 0x41, 0x2, 0x8, 0x10,
    0x0, 0x81, 0x0,

    /* U+0038 "8" */
    0x3c, 0x42, 0x81, 0x81, 0x0, 0x42, 0x3c, 0x42,
    0x81, 0x81, 0x42, 0x3c,

    /* U+0039 "9" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x1, 0x43, 0x3d,
    0x1, 0x81, 0x42, 0x3c,

    /* U+003A ":" */
    0xc3,

    /* U+003B ";" */
    0x50, 0x5, 0x80,

    /* U+003C "<" */
    0x1, 0x81, 0x3, 0x6, 0xc, 0x1, 0x80, 0x38,
    0x3,

    /* U+003D "=" */
    0xfe, 0x0, 0x0, 0xf, 0xe0,

    /* U+003E ">" */
    0xc0, 0x18, 0x3, 0x0, 0x40, 0x18, 0x10, 0xf1,
    0x80,

    /* U+003F "?" */
    0x38, 0x8a, 0xc, 0x10, 0x0, 0x82, 0x8, 0x10,
    0x0, 0x40, 0x80,

    /* U+0040 "@" */
    0x1f, 0x2, 0xc, 0x40, 0x24, 0xca, 0x92, 0x9a,
    0x19, 0xa0, 0x9a, 0x9, 0xa1, 0x99, 0x2a, 0x4c,
    0x44, 0x0, 0x20, 0x31, 0xfc,

    /* U+0041 "A" */
    0x8, 0x5, 0x1, 0x40, 0x48, 0x12, 0x8, 0x42,
    0x10, 0x84, 0x7f, 0x90, 0x28, 0x6, 0x1,

    /* U+0042 "B" */
    0xfc, 0x41, 0x20, 0x50, 0x28, 0x4, 0x13, 0xf1,
    0x6, 0x80, 0xc0, 0x60, 0x5f, 0xc0,

    /* U+0043 "C" */
    0x3e, 0x20, 0x90, 0x50, 0x18, 0xc, 0x2, 0x1,
    0x1, 0x80, 0xa0, 0x90, 0x47, 0xc0,

    /* U+0044 "D" */
    0xfc, 0x41, 0x20, 0x50, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80, 0xc0, 0xa0, 0x9f, 0x80,

    /* U+0045 "E" */
    0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfe, 0x80,
    0x80, 0x80, 0x80, 0xff,

    /* U+0046 "F" */
    0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfe, 0x80,
    0x80, 0x80, 0x80, 0x80,

    /* U+0047 "G" */
    0x3e, 0x20, 0xa0, 0x30, 0x18, 0x4, 0x2, 0x1,
    0x7, 0x80, 0xc0, 0xd0, 0xa7, 0x90,

    /* U+0048 "H" */
    0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff, 0x81,
    0x81, 0x81, 0x81, 0x81,

    /* U+0049 "I" */
    0xff, 0xf0,

    /* U+004A "J" */
    0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x81, 0x83,
    0x5, 0x11, 0xc0,

    /* U+004B "K" */
    0x81, 0x82, 0x84, 0x84, 0x88, 0x90, 0xa0, 0xd8,
    0x84, 0x84, 0x82, 0x81,

    /* U+004C "L" */
    0x81, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x81,
    0x2, 0x7, 0xf0,

    /* U+004D "M" */
    0x80, 0x70, 0x3c, 0xe, 0x85, 0xa1, 0x64, 0x99,
    0x26, 0x51, 0x88, 0x62, 0x18, 0x6, 0x1,

    /* U+004E "N" */
    0x81, 0xc1, 0xc1, 0xa1, 0x91, 0x91, 0x89, 0x85,
    0x85, 0x83, 0x83, 0x81,

    /* U+004F "O" */
    0x1e, 0x8, 0x44, 0x9, 0x2, 0x80, 0x60, 0x18,
    0x6, 0x1, 0x40, 0x90, 0x22, 0x10, 0x78,

    /* U+0050 "P" */
    0xfc, 0x82, 0x81, 0x81, 0x81, 0x80, 0x82, 0xfc,
    0x80, 0x80, 0x80, 0x80,

    /* U+0051 "Q" */
    0x1e, 0x8, 0x44, 0xa, 0x1, 0x80, 0x60, 0x18,
    0x6, 0x1, 0x80, 0x50, 0x22, 0x10, 0x78, 0x0,
    0x1, 0x10, 0x38,

    /* U+0052 "R" */
    0xfe, 0x40, 0xa0, 0x30, 0x18, 0xc, 0x2, 0x5,
    0xfe, 0x80, 0x40, 0x60, 0x30, 0x10,

    /* U+0053 "S" */
    0x3c, 0x42, 0x81, 0x80, 0x80, 0x40, 0x3c, 0x3,
    0x81, 0x81, 0x42, 0x3c,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x80,

    /* U+0055 "U" */
    0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x81, 0x81, 0x42, 0x3c,

    /* U+0056 "V" */
    0x80, 0x60, 0x10, 0x1, 0x2, 0x40, 0x88, 0x42,
    0x10, 0x48, 0x12, 0x5, 0x1, 0x40, 0x20,

    /* U+0057 "W" */
    0x81, 0x3, 0x2, 0x5, 0xa, 0x12, 0x14, 0x22,
    0x44, 0x84, 0x89, 0x9, 0x12, 0xa, 0x14, 0x14,
    0x28, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80,

    /* U+0058 "X" */
    0x80, 0x50, 0x22, 0x10, 0x84, 0x12, 0x3, 0x0,
    0x80, 0x78, 0x21, 0x8, 0x44, 0xa, 0x1,

    /* U+0059 "Y" */
    0x80, 0x50, 0x22, 0x10, 0x84, 0x12, 0x3, 0x0,
    0xc0, 0x10, 0x4, 0x1, 0x0, 0x40, 0x10,

    /* U+005A "Z" */
    0xff, 0x80, 0x80, 0x80, 0x80, 0x40, 0x20, 0x10,
    0x30, 0x10, 0x10, 0x10, 0x1f, 0xf0,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x49, 0xc0,

    /* U+005C "\\" */
    0x82, 0x4, 0x10, 0x20, 0x81, 0x4, 0x0, 0x40,
    0x82, 0x4, 0x10,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x93, 0xc0,

    /* U+005E "^" */
    0x10, 0xa4, 0x61,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x88, 0x80,

    /* U+0061 "a" */
    0x79, 0x8, 0x10, 0xe6, 0x40, 0xa3, 0x4a, 0x62,

    /* U+0062 "b" */
    0x81, 0x2, 0x4, 0xca, 0x58, 0x60, 0xc1, 0x83,
    0x7, 0x15, 0xc0,

    /* U+0063 "c" */
    0x3c, 0x42, 0x41, 0x81, 0x80, 0x81, 0x41, 0x42,
    0x3c,

    /* U+0064 "d" */
    0x2, 0x4, 0x9, 0xd4, 0x70, 0x60, 0xc1, 0x83,
    0x5, 0x19, 0xd0,

    /* U+0065 "e" */
    0x38, 0x8a, 0xc, 0x1f, 0xf0, 0x20, 0xa2, 0x38,

    /* U+0066 "f" */
    0x38, 0x4, 0x50, 0x23, 0xf2, 0x8, 0x20, 0x82,
    0x8,

    /* U+0067 "g" */
    0x1f, 0x24, 0x0, 0x42, 0x42, 0x24, 0x18, 0x20,
    0x7c, 0x42, 0x81, 0x42, 0x3c,

    /* U+0068 "h" */
    0x81, 0x2, 0x4, 0xca, 0x58, 0x60, 0xc1, 0x83,
    0x6, 0xc, 0x10,

    /* U+0069 "i" */
    0xcf, 0xf0,

    /* U+006A "j" */
    0x11, 0x0, 0x11, 0x11, 0x11, 0x11, 0x19, 0xe0,

    /* U+006B "k" */
    0x82, 0x8, 0x20, 0x86, 0x29, 0x3c, 0x8a, 0x28,
    0x61,

    /* U+006C "l" */
    0xaa, 0xaa, 0xa9,

    /* U+006D "m" */
    0x90, 0x95, 0x2b, 0x18, 0xc2, 0x18, 0x43, 0x8,
    0x61, 0xc, 0x21, 0x84, 0x20,

    /* U+006E "n" */
    0x99, 0x4b, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x82,

    /* U+006F "o" */
    0x38, 0x8a, 0xc, 0x18, 0x30, 0x60, 0xa2, 0x38,

    /* U+0070 "p" */
    0x99, 0x4b, 0xc, 0x18, 0x30, 0x60, 0xe1, 0xbd,
    0x2, 0x4, 0x8, 0x0,

    /* U+0071 "q" */
    0x32, 0x96, 0x1c, 0x18, 0x30, 0x60, 0xc3, 0x7a,
    0x4, 0x8, 0x10, 0x20,

    /* U+0072 "r" */
    0x95, 0x71, 0x8, 0x42, 0x10, 0x80,

    /* U+0073 "s" */
    0x3c, 0x8a, 0xa, 0x3, 0xc0, 0xa0, 0xa2, 0x3c,

    /* U+0074 "t" */
    0x20, 0x84, 0x3f, 0x20, 0x82, 0x8, 0x24, 0x60,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x53, 0x34,

    /* U+0076 "v" */
    0x81, 0x81, 0x42, 0x42, 0x24, 0x18, 0x18, 0x10,
    0x10,

    /* U+0077 "w" */
    0x84, 0x30, 0x84, 0x0, 0x25, 0x24, 0xa4, 0x62,
    0x8c, 0x50, 0x84, 0x10, 0x80,

    /* U+0078 "x" */
    0x86, 0x14, 0x8c, 0x31, 0x20, 0x21, 0x84,

    /* U+0079 "y" */
    0x81, 0x81, 0x0, 0x42, 0x42, 0x24, 0x24, 0x18,
    0x18, 0x10, 0x10, 0x90, 0x60,

    /* U+007A "z" */
    0xfe, 0x4, 0x10, 0x41, 0x4, 0x10, 0x40, 0xfe,

    /* U+007B "{" */
    0x19, 0x8, 0x42, 0x11, 0x10, 0x61, 0x8, 0x42,
    0xc,

    /* U+007C "|" */
    0xff, 0xfc,

    /* U+007D "}" */
    0xc1, 0x8, 0x42, 0x10, 0x41, 0x31, 0x8, 0x42,
    0x60,

    /* U+007E "~" */
    0x70, 0xa2, 0x18, 0x45, 0xe,

    /* U+0401 "Ё" */
    0x12, 0x4, 0x8f, 0xfe, 0x0, 0x80, 0x20, 0x8,
    0x2, 0x0, 0xff, 0xa0, 0x8, 0x2, 0x0, 0x80,
    0x3f, 0xf0,

    /* U+0402 "Ђ" */
    0xff, 0x2, 0x0, 0x40, 0x8, 0x1, 0x0, 0x27,
    0x7, 0x18, 0x81, 0x10, 0x22, 0x4, 0x41, 0x9,
    0xc0,

    /* U+0403 "Ѓ" */
    0x8, 0x20, 0x47, 0xf8, 0x10, 0x20, 0x40, 0x81,
    0x2, 0x4, 0x8, 0x10, 0x20, 0x0,

    /* U+0404 "Є" */
    0x1f, 0x8, 0x24, 0x6, 0x1, 0x80, 0x20, 0xf,
    0xf2, 0x0, 0x80, 0x50, 0x12, 0x8, 0x7c,

    /* U+0405 "Ѕ" */
    0x3e, 0x20, 0x80, 0x10, 0x18, 0xb, 0xc0, 0x3e,
    0x1, 0x80, 0xc0, 0x50, 0x47, 0xc0,

    /* U+0406 "І" */
    0xff, 0xf0,

    /* U+0407 "Ї" */
    0xb5, 0x24, 0x92, 0x49, 0x24, 0x80,

    /* U+0408 "Ј" */
    0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x81, 0x83,
    0x5, 0x11, 0xc0,

    /* U+0409 "Љ" */
    0x1f, 0xc0, 0x8, 0x20, 0x4, 0x10, 0x2, 0x8,
    0x1, 0x4, 0x0, 0x82, 0x0, 0x41, 0xf8, 0x20,
    0x82, 0x10, 0x40, 0x90, 0x20, 0x50, 0x10, 0x50,
    0xf, 0xc0,

    /* U+040A "Њ" */
    0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10,
    0x8, 0x8, 0x4, 0x4, 0x3, 0xff, 0xf9, 0x1,
    0x2, 0x80, 0x80, 0xc0, 0x40, 0x60, 0x20, 0x50,
    0x1f, 0xc0,

    /* U+040B "Ћ" */
    0xff, 0x2, 0x0, 0x40, 0x8, 0x1, 0x0, 0x2f,
    0x6, 0x10, 0x81, 0x10, 0x22, 0x4, 0x40, 0x88,
    0x10,

    /* U+040C "Ќ" */
    0x4, 0x2, 0x1, 0x2, 0x1, 0x81, 0xa0, 0x88,
    0xc2, 0x40, 0x90, 0x2c, 0xc, 0xc2, 0x8, 0x81,
    0x20, 0x28, 0x4,

    /* U+040E "Ў" */
    0x11, 0x3, 0x88, 0x5, 0x2, 0x40, 0x88, 0x42,
    0x10, 0x48, 0x12, 0x3, 0x0, 0x80, 0x20, 0x8,
    0x1c, 0x0,

    /* U+040F "Џ" */
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3,
    0x1, 0x80, 0xc0, 0x60, 0x3f, 0xf0, 0x80, 0x40,
    0x20,

    /* U+0410 "А" */
    0x4, 0x1, 0x40, 0x28, 0x8, 0x81, 0x10, 0x21,
    0x4, 0x21, 0x0, 0x7f, 0xc8, 0xa, 0x0, 0xc0,
    0x10,

    /* U+0411 "Б" */
    0xff, 0x20, 0x8, 0x2, 0x0, 0x80, 0x3f, 0xc8,
    0xe, 0x1, 0x80, 0x60, 0x18, 0xb, 0xfc,

    /* U+0412 "В" */
    0xff, 0x20, 0x28, 0x2, 0x1, 0x80, 0x60, 0x2f,
    0xf2, 0x2, 0x80, 0x60, 0x18, 0xb, 0xfc,

    /* U+0413 "Г" */
    0xff, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x81,
    0x2, 0x4, 0x0,

    /* U+0414 "Д" */
    0x1f, 0xc1, 0x4, 0x10, 0x41, 0x4, 0x10, 0x41,
    0x4, 0x10, 0x41, 0x4, 0x20, 0x42, 0x4, 0x20,
    0x4f, 0xff, 0x80, 0x18, 0x1, 0x80, 0x10,

    /* U+0415 "Е" */
    0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80,
    0x80, 0x80, 0x80, 0xff,

    /* U+0416 "Ж" */
    0x80, 0x80, 0xa0, 0x40, 0x88, 0x20, 0x82, 0x10,
    0x80, 0x88, 0x80, 0x44, 0x80, 0x12, 0x40, 0x15,
    0x60, 0x19, 0xcc, 0x10, 0x41, 0x10, 0x20, 0x50,
    0x10, 0x10,

    /* U+0417 "З" */
    0x3e, 0x20, 0x80, 0x10, 0x18, 0x8, 0x8, 0x78,
    0x2, 0x80, 0xc0, 0x50, 0x47, 0xc0,

    /* U+0418 "И" */
    0x80, 0x60, 0x38, 0x16, 0x5, 0x82, 0x61, 0x18,
    0x86, 0x21, 0xb0, 0x68, 0x1c, 0x6, 0x1,

    /* U+0419 "Й" */
    0x21, 0x7, 0x88, 0x6, 0x3, 0x81, 0x60, 0x58,
    0x26, 0x11, 0x88, 0x62, 0x1b, 0x6, 0x81, 0xc0,
    0x60, 0x10,

    /* U+041A "К" */
    0x80, 0x60, 0x68, 0x22, 0x10, 0x88, 0x24, 0xf,
    0x2, 0x20, 0x86, 0x20, 0x48, 0xa, 0x1,

    /* U+041B "Л" */
    0x1f, 0xc4, 0x11, 0x4, 0x41, 0x10, 0x44, 0x11,
    0x4, 0x41, 0x10, 0x44, 0x12, 0x7, 0x1,

    /* U+041C "М" */
    0x80, 0x38, 0xf, 0x1, 0xd0, 0x3a, 0x7, 0x21,
    0x64, 0x2c, 0x89, 0x8a, 0x31, 0x46, 0x10, 0xc2,
    0x10,

    /* U+041D "Н" */
    0x80, 0x60, 0x18, 0x6, 0x1, 0x80, 0x60, 0x1f,
    0xfe, 0x1, 0x80, 0x60, 0x18, 0x6, 0x1,

    /* U+041E "О" */
    0x1f, 0x4, 0x11, 0x1, 0x40, 0x18, 0x3, 0x0,
    0x60, 0xc, 0x1, 0x80, 0x28, 0x8, 0x82, 0xf,
    0x80,

    /* U+041F "П" */
    0xff, 0xe0, 0x18, 0x6, 0x1, 0x80, 0x60, 0x18,
    0x6, 0x1, 0x80, 0x60, 0x18, 0x6, 0x1,

    /* U+0420 "Р" */
    0xfc, 0x82, 0x80, 0x81, 0x81, 0x82, 0xfc, 0x80,
    0x80, 0x80, 0x80, 0x80,

    /* U+0421 "С" */
    0x1e, 0x8, 0x44, 0xa, 0x1, 0x80, 0x20, 0x8,
    0x2, 0x0, 0x80, 0x50, 0x22, 0x10, 0x78,

    /* U+0422 "Т" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x80,

    /* U+0423 "У" */
    0x80, 0xc0, 0x50, 0x48, 0x22, 0x21, 0x10, 0x10,
    0x28, 0x18, 0x8, 0x20, 0xc, 0x0,

    /* U+0424 "Ф" */
    0x2, 0x0, 0x10, 0xf, 0xf8, 0x84, 0x28, 0x20,
    0xc1, 0x6, 0x8, 0x30, 0x41, 0x42, 0x11, 0xff,
    0x0, 0x80, 0x4, 0x0,

    /* U+0425 "Х" */
    0x80, 0x60, 0x14, 0x8, 0x84, 0x12, 0x3, 0x0,
    0x80, 0x30, 0x33, 0x10, 0x28, 0x6, 0x1,

    /* U+0426 "Ц" */
    0x80, 0xa0, 0x28, 0xa, 0x2, 0x80, 0xa0, 0x28,
    0xa, 0x2, 0x80, 0xa0, 0x28, 0xb, 0xff, 0x0,
    0x40, 0x10, 0x4,

    /* U+0427 "Ч" */
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6, 0x6,
    0xfd, 0x0, 0x80, 0x40, 0x20, 0x10,

    /* U+0428 "Ш" */
    0x82, 0xc, 0x10, 0x60, 0x83, 0x4, 0x18, 0x20,
    0xc1, 0x6, 0x8, 0x30, 0x41, 0x82, 0xc, 0x10,
    0x60, 0x83, 0xff, 0xf0,

    /* U+0429 "Щ" */
    0x81, 0x2, 0x81, 0x2, 0x81, 0x2, 0x81, 0x2,
    0x81, 0x2, 0x81, 0x2, 0x81, 0x2, 0x81, 0x2,
    0x81, 0x2, 0x81, 0x2, 0x81, 0x2, 0xff, 0xff,
    0x0, 0x1, 0x0, 0x1, 0x0, 0x1,

    /* U+042A "Ъ" */
    0xf0, 0x2, 0x0, 0x40, 0x8, 0x1, 0x0, 0x20,
    0x7, 0xe0, 0x82, 0x10, 0x22, 0x4, 0x41, 0xf,
    0xc0,

    /* U+042B "Ы" */
    0x80, 0x60, 0x18, 0x6, 0x1, 0x80, 0x60, 0x1f,
    0xe6, 0x5, 0x80, 0xe0, 0x38, 0x17, 0xf9,

    /* U+042C "Ь" */
    0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x3, 0xf9,
    0x2, 0x80, 0xc0, 0x60, 0x5f, 0xc0,

    /* U+042D "Э" */
    0x3e, 0x10, 0x48, 0xa, 0x1, 0x0, 0x40, 0x11,
    0xfc, 0x1, 0x80, 0x60, 0x24, 0x10, 0xf8,

    /* U+042E "Ю" */
    0x83, 0xe2, 0x10, 0x48, 0x80, 0xa4, 0x1, 0x90,
    0x6, 0x40, 0x1f, 0x0, 0x64, 0x1, 0x90, 0x6,
    0x20, 0x28, 0x41, 0x20, 0xf8,

    /* U+042F "Я" */
    0x3f, 0xa0, 0x60, 0x30, 0x18, 0xc, 0x5, 0x2,
    0x7f, 0xc0, 0xc0, 0x60, 0x30, 0x10,

    /* U+0430 "а" */
    0x7c, 0x82, 0x2, 0x1e, 0x72, 0x86, 0x8a, 0x71,

    /* U+0431 "б" */
    0x6, 0x71, 0x4, 0xb, 0x98, 0xa0, 0xc1, 0x83,
    0x5, 0x11, 0xc0,

    /* U+0432 "в" */
    0xfa, 0x18, 0x60, 0xfa, 0x18, 0x7e,

    /* U+0433 "г" */
    0xfc, 0x21, 0x8, 0x42, 0x10,

    /* U+0434 "д" */
    0x1f, 0x8, 0x84, 0x42, 0x21, 0x11, 0x9, 0x5,
    0xff, 0x80, 0xc0, 0x60, 0x20,

    /* U+0435 "е" */
    0x38, 0x8a, 0xc, 0x1f, 0xf0, 0x51, 0x1c,

    /* U+0436 "ж" */
    0x22, 0x21, 0x12, 0x4, 0x90, 0x15, 0x1, 0x74,
    0x11, 0x11, 0x8, 0x50, 0x41,

    /* U+0437 "з" */
    0x38, 0x8a, 0x8, 0x29, 0xd0, 0x51, 0x1c,

    /* U+0438 "и" */
    0x87, 0x16, 0x2c, 0x9b, 0x34, 0x70, 0xc1,

    /* U+0439 "й" */
    0x44, 0x70, 0x0, 0x8, 0x71, 0x62, 0xc9, 0xb3,
    0x47, 0xc, 0x10,

    /* U+043A "к" */
    0x85, 0x12, 0x44, 0x8f, 0x11, 0x21, 0x41,

    /* U+043B "л" */
    0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x21, 0xc1,

    /* U+043C "м" */
    0xc0, 0xe8, 0x5a, 0x16, 0x49, 0x94, 0x65, 0x18,
    0x86, 0x21,

    /* U+043D "н" */
    0x83, 0x6, 0xf, 0xf8, 0x30, 0x60, 0xc1,

    /* U+043E "о" */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3c,

    /* U+043F "п" */
    0xff, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,

    /* U+0440 "р" */
    0x9c, 0xa2, 0xc1, 0x81, 0x81, 0x81, 0xe3, 0x9c,
    0x80, 0x80, 0x80,

    /* U+0441 "с" */
    0x38, 0x8a, 0xc, 0x8, 0x10, 0x51, 0x1c,

    /* U+0442 "т" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8,

    /* U+0443 "у" */
    0x81, 0x42, 0x42, 0x24, 0x24, 0x28, 0x18, 0x18,
    0x8, 0x88, 0x70,

    /* U+0444 "ф" */
    0x4, 0x0, 0x80, 0x10, 0x1a, 0xc4, 0xe5, 0x8,
    0x61, 0xc, 0x21, 0x84, 0x20, 0x81, 0xff, 0x2,
    0x0, 0x40, 0x8, 0x0,

    /* U+0445 "х" */
    0x81, 0x42, 0x24, 0x14, 0x1c, 0x24, 0x42, 0x81,

    /* U+0446 "ц" */
    0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0xff,
    0x1, 0x1, 0x1,

    /* U+0447 "ч" */
    0x86, 0x18, 0x63, 0x74, 0x10, 0x41,

    /* U+0448 "ш" */
    0x84, 0x30, 0x86, 0x10, 0xc2, 0x18, 0x43, 0x8,
    0x61, 0xf, 0xff,

    /* U+0449 "щ" */
    0x84, 0x48, 0x44, 0x84, 0x48, 0x44, 0x84, 0x48,
    0x44, 0x84, 0x4f, 0xff, 0x0, 0x10, 0x1, 0x0,
    0x10,

    /* U+044A "ъ" */
    0xf0, 0x4, 0x1, 0x0, 0x7f, 0x10, 0x44, 0x11,
    0x4, 0x7e,

    /* U+044B "ы" */
    0x80, 0xc0, 0x60, 0x3f, 0xd8, 0x2c, 0x16, 0xb,
    0xf9,

    /* U+044C "ь" */
    0x81, 0x2, 0x7, 0xf8, 0x30, 0x60, 0xfe,

    /* U+044D "э" */
    0x3c, 0x42, 0x81, 0x1, 0x1f, 0x81, 0x42, 0x3c,

    /* U+044E "ю" */
    0x87, 0x22, 0x29, 0x6, 0x41, 0xf0, 0x64, 0x18,
    0x8a, 0x1c,

    /* U+044F "я" */
    0x7f, 0x6, 0x8, 0x17, 0xe6, 0x50, 0xc1,

    /* U+0451 "ё" */
    0x18, 0x18, 0x0, 0x3c, 0x42, 0x81, 0x81, 0xff,
    0x81, 0x42, 0x3c,

    /* U+0452 "ђ" */
    0x40, 0x40, 0xfc, 0x40, 0x4c, 0x52, 0x61, 0x41,
    0x41, 0x41, 0x41, 0x41, 0x1, 0x2, 0xc,

    /* U+0453 "ѓ" */
    0x10, 0x88, 0xf, 0xc2, 0x10, 0x84, 0x21, 0x0,

    /* U+0454 "є" */
    0x38, 0x8a, 0xc, 0xf, 0x90, 0x51, 0x1c,

    /* U+0455 "ѕ" */
    0x38, 0x8a, 0xb, 0x19, 0xd0, 0x51, 0x1c,

    /* U+0456 "і" */
    0xdf, 0xe0,

    /* U+0457 "ї" */
    0xb4, 0x24, 0x92, 0x49, 0x0,

    /* U+0458 "ј" */
    0x24, 0x92, 0x49, 0x24, 0x9c,

    /* U+0459 "љ" */
    0x1f, 0x0, 0x88, 0x4, 0x40, 0x23, 0xf1, 0x10,
    0x90, 0x84, 0x84, 0x38, 0x3e,

    /* U+045A "њ" */
    0x84, 0x8, 0x40, 0x84, 0xf, 0xff, 0x84, 0x18,
    0x41, 0x84, 0x18, 0x7e,

    /* U+045B "ћ" */
    0x20, 0x10, 0x3f, 0x4, 0x2, 0x61, 0x48, 0xc2,
    0x41, 0x20, 0x90, 0x48, 0x24, 0x10,

    /* U+045C "ќ" */
    0x10, 0x42, 0x0, 0x86, 0x29, 0x24, 0xf2, 0x48,
    0xa1,

    /* U+045E "ў" */
    0x24, 0x18, 0x81, 0x81, 0x42, 0x42, 0x24, 0x24,
    0x18, 0x10, 0x10, 0x90, 0x60,

    /* U+045F "џ" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xff, 0x10,
    0x20, 0x40,

    /* U+0490 "Ґ" */
    0x2, 0x7, 0xfc, 0x8, 0x10, 0x20, 0x40, 0x81,
    0x2, 0x4, 0x8, 0x10, 0x0,

    /* U+0491 "ґ" */
    0x8, 0x43, 0xf8, 0x42, 0x10, 0x84, 0x20
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 77, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 28, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 55, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 4, .adv_w = 234, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 138, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 39, .adv_w = 193, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 193, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 28, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 74, .adv_w = 69, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 81, .adv_w = 69, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 88, .adv_w = 83, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 92, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 100, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 101, .adv_w = 124, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 102, .adv_w = 28, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 111, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 114, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 83, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 28, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 41, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 236, .adv_w = 152, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 245, .adv_w = 124, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 250, .adv_w = 152, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 259, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 205, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 291, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 28, .box_w = 1, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 166, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 165, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 507, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 248, .box_w = 15, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 166, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 55, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 644, .adv_w = 111, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 655, .adv_w = 55, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 661, .adv_w = 110, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 664, .adv_w = 97, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 665, .adv_w = 55, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 667, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 695, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 706, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 714, .adv_w = 97, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 723, .adv_w = 138, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 736, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 747, .adv_w = 28, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 749, .adv_w = 83, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 757, .adv_w = 110, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 766, .adv_w = 41, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 769, .adv_w = 193, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 782, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 790, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 798, .adv_w = 124, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 810, .adv_w = 124, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 822, .adv_w = 97, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 828, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 97, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 844, .adv_w = 110, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 851, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 860, .adv_w = 193, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 873, .adv_w = 110, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 880, .adv_w = 138, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 893, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 901, .adv_w = 83, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 910, .adv_w = 28, .box_w = 1, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 912, .adv_w = 83, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 921, .adv_w = 179, .box_w = 10, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 926, .adv_w = 152, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 944, .adv_w = 193, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 961, .adv_w = 124, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 975, .adv_w = 179, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 990, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1004, .adv_w = 28, .box_w = 1, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1006, .adv_w = 55, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1012, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1023, .adv_w = 290, .box_w = 17, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1049, .adv_w = 276, .box_w = 17, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1075, .adv_w = 193, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1092, .adv_w = 165, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1111, .adv_w = 165, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1129, .adv_w = 165, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1146, .adv_w = 193, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1163, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1178, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1193, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1204, .adv_w = 207, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1227, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1239, .adv_w = 276, .box_w = 17, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1265, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1279, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1294, .adv_w = 165, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1312, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1327, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1342, .adv_w = 193, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1359, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1374, .adv_w = 193, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1391, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1406, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1418, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1433, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1444, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1458, .adv_w = 220, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1478, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1493, .adv_w = 179, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1512, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1526, .adv_w = 221, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1546, .adv_w = 276, .box_w = 16, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1576, .adv_w = 193, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1593, .adv_w = 179, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1608, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1622, .adv_w = 179, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1637, .adv_w = 234, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1658, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1672, .adv_w = 138, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1680, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1691, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1697, .adv_w = 97, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1702, .adv_w = 151, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1715, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1722, .adv_w = 220, .box_w = 13, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1735, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1742, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1749, .adv_w = 124, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1760, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1767, .adv_w = 138, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1775, .adv_w = 166, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1785, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1792, .adv_w = 138, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1800, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1807, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1818, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1825, .adv_w = 138, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1832, .adv_w = 137, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1843, .adv_w = 193, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1863, .adv_w = 138, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1871, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1882, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1888, .adv_w = 193, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1899, .adv_w = 206, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1916, .adv_w = 165, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1926, .adv_w = 152, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1935, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1942, .adv_w = 138, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1950, .adv_w = 179, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1960, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1967, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1978, .adv_w = 138, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1993, .adv_w = 97, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2001, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2008, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2015, .adv_w = 28, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2017, .adv_w = 55, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2022, .adv_w = 55, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2027, .adv_w = 221, .box_w = 13, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2040, .adv_w = 207, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2052, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2066, .adv_w = 110, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2075, .adv_w = 138, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2088, .adv_w = 111, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2098, .adv_w = 124, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2111, .adv_w = 97, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_4[] = {
    0x0, 0x1, 0x32, 0x33
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 1025, .range_length = 12, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 1038, .range_length = 66, .glyph_id_start = 108,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 1105, .range_length = 12, .glyph_id_start = 174,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 1118, .range_length = 52, .glyph_id_start = 186,
        .unicode_list = unicode_list_4, .glyph_id_ofs_list = NULL, .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    9, 21,
    18, 21,
    18, 23,
    18, 24,
    18, 25,
    18, 26,
    19, 21,
    21, 10,
    21, 24,
    22, 24,
    24, 21,
    25, 24,
    26, 24,
    34, 11,
    34, 36,
    34, 48,
    34, 50,
    34, 53,
    34, 55,
    34, 56,
    34, 58,
    34, 68,
    34, 71,
    34, 72,
    34, 75,
    34, 80,
    34, 85,
    34, 87,
    34, 88,
    34, 90,
    35, 53,
    35, 55,
    35, 56,
    35, 57,
    35, 58,
    35, 59,
    35, 71,
    35, 72,
    35, 75,
    35, 85,
    35, 87,
    35, 88,
    35, 90,
    36, 34,
    36, 53,
    36, 56,
    36, 57,
    36, 58,
    36, 59,
    36, 72,
    36, 75,
    37, 34,
    37, 53,
    37, 56,
    37, 57,
    37, 58,
    37, 59,
    37, 72,
    37, 75,
    38, 36,
    38, 40,
    38, 43,
    38, 48,
    38, 50,
    38, 52,
    38, 68,
    38, 69,
    38, 70,
    38, 71,
    38, 72,
    38, 75,
    38, 80,
    38, 82,
    38, 84,
    38, 85,
    38, 86,
    38, 87,
    38, 88,
    38, 90,
    39, 34,
    39, 36,
    39, 40,
    39, 43,
    39, 48,
    39, 50,
    39, 52,
    39, 66,
    39, 68,
    39, 69,
    39, 70,
    39, 71,
    39, 72,
    39, 75,
    39, 78,
    39, 79,
    39, 80,
    39, 81,
    39, 82,
    39, 83,
    39, 84,
    39, 85,
    39, 86,
    39, 87,
    39, 88,
    39, 89,
    39, 90,
    39, 91,
    40, 53,
    40, 58,
    40, 71,
    40, 72,
    40, 75,
    40, 85,
    41, 72,
    41, 75,
    42, 72,
    42, 75,
    43, 72,
    43, 75,
    44, 36,
    44, 40,
    44, 43,
    44, 48,
    44, 50,
    44, 70,
    44, 71,
    44, 72,
    44, 75,
    44, 80,
    44, 82,
    44, 84,
    44, 85,
    44, 86,
    44, 87,
    44, 88,
    44, 90,
    45, 36,
    45, 40,
    45, 43,
    45, 48,
    45, 50,
    45, 52,
    45, 53,
    45, 54,
    45, 55,
    45, 56,
    45, 58,
    45, 68,
    45, 69,
    45, 70,
    45, 71,
    45, 72,
    45, 75,
    45, 80,
    45, 82,
    45, 84,
    45, 85,
    45, 86,
    45, 87,
    45, 88,
    45, 90,
    46, 75,
    47, 72,
    47, 75,
    48, 34,
    48, 53,
    48, 55,
    48, 56,
    48, 57,
    48, 58,
    48, 59,
    48, 72,
    48, 75,
    49, 34,
    49, 43,
    49, 53,
    49, 57,
    49, 58,
    49, 59,
    49, 72,
    49, 75,
    50, 34,
    50, 53,
    50, 56,
    50, 57,
    50, 58,
    50, 59,
    51, 53,
    51, 58,
    51, 72,
    51, 75,
    52, 53,
    52, 58,
    52, 59,
    52, 71,
    52, 72,
    52, 75,
    52, 85,
    53, 34,
    53, 36,
    53, 40,
    53, 43,
    53, 48,
    53, 50,
    53, 52,
    53, 66,
    53, 68,
    53, 69,
    53, 70,
    53, 71,
    53, 72,
    53, 75,
    53, 78,
    53, 79,
    53, 80,
    53, 81,
    53, 82,
    53, 83,
    53, 84,
    53, 85,
    53, 86,
    53, 87,
    53, 88,
    53, 89,
    53, 90,
    53, 91,
    54, 72,
    54, 75,
    55, 34,
    55, 43,
    55, 48,
    55, 66,
    55, 68,
    55, 69,
    55, 70,
    55, 71,
    55, 72,
    55, 75,
    55, 80,
    55, 82,
    55, 84,
    55, 85,
    56, 34,
    56, 36,
    56, 43,
    56, 48,
    56, 50,
    56, 66,
    56, 68,
    56, 69,
    56, 70,
    56, 71,
    56, 72,
    56, 75,
    56, 78,
    56, 79,
    56, 80,
    56, 81,
    56, 82,
    56, 83,
    56, 84,
    56, 85,
    56, 86,
    56, 87,
    56, 88,
    56, 89,
    56, 90,
    56, 91,
    57, 36,
    57, 40,
    57, 43,
    57, 48,
    57, 50,
    57, 68,
    57, 69,
    57, 70,
    57, 71,
    57, 72,
    57, 75,
    57, 80,
    57, 82,
    57, 84,
    57, 85,
    57, 86,
    57, 87,
    57, 88,
    57, 90,
    58, 34,
    58, 36,
    58, 40,
    58, 43,
    58, 48,
    58, 50,
    58, 52,
    58, 66,
    58, 68,
    58, 69,
    58, 70,
    58, 71,
    58, 72,
    58, 75,
    58, 78,
    58, 79,
    58, 80,
    58, 81,
    58, 82,
    58, 83,
    58, 84,
    58, 85,
    58, 86,
    58, 87,
    58, 88,
    58, 89,
    58, 90,
    58, 91,
    59, 36,
    59, 40,
    59, 43,
    59, 48,
    59, 50,
    59, 52,
    59, 68,
    59, 69,
    59, 70,
    59, 71,
    59, 72,
    59, 75,
    59, 80,
    59, 82,
    59, 84,
    59, 85,
    59, 86,
    59, 87,
    59, 88,
    59, 90,
    66, 68,
    66, 69,
    66, 70,
    66, 71,
    66, 72,
    66, 75,
    66, 80,
    66, 84,
    66, 85,
    66, 86,
    66, 87,
    66, 88,
    66, 90,
    67, 75,
    68, 72,
    68, 75,
    69, 72,
    69, 75,
    70, 72,
    70, 75,
    71, 34,
    71, 72,
    71, 75,
    72, 34,
    72, 68,
    72, 69,
    72, 70,
    72, 71,
    72, 80,
    72, 82,
    72, 84,
    72, 85,
    73, 72,
    73, 75,
    74, 72,
    74, 75,
    76, 68,
    76, 72,
    76, 75,
    76, 80,
    77, 48,
    77, 68,
    77, 69,
    77, 70,
    77, 71,
    77, 72,
    77, 75,
    77, 80,
    77, 82,
    77, 84,
    77, 85,
    77, 86,
    77, 87,
    77, 88,
    77, 90,
    78, 72,
    78, 75,
    79, 72,
    79, 75,
    80, 34,
    80, 72,
    80, 75,
    80, 87,
    80, 91,
    81, 72,
    81, 75,
    83, 68,
    83, 72,
    83, 75,
    83, 80,
    84, 72,
    84, 75,
    85, 72,
    85, 75,
    86, 72,
    86, 75,
    87, 34,
    87, 68,
    87, 72,
    87, 75,
    87, 80,
    88, 34,
    88, 72,
    88, 75,
    89, 72,
    89, 75,
    90, 34,
    90, 72,
    90, 75,
    91, 68,
    91, 72,
    91, 75,
    91, 80,
    110, 124,
    110, 127,
    110, 128,
    110, 130,
    110, 133,
    110, 136,
    110, 139,
    110, 160,
    110, 161,
    110, 168,
    111, 114,
    111, 116,
    111, 121,
    111, 128,
    111, 136,
    112, 114,
    112, 116,
    112, 121,
    112, 128,
    113, 110,
    113, 114,
    113, 117,
    113, 121,
    113, 124,
    113, 127,
    113, 130,
    113, 139,
    113, 141,
    114, 117,
    114, 124,
    114, 127,
    114, 128,
    114, 130,
    114, 133,
    114, 136,
    115, 139,
    116, 117,
    116, 139,
    117, 114,
    117, 128,
    120, 117,
    120, 124,
    120, 127,
    120, 130,
    120, 139,
    120, 161,
    124, 110,
    124, 114,
    124, 121,
    124, 128,
    124, 129,
    124, 131,
    126, 110,
    126, 114,
    126, 116,
    126, 121,
    126, 128,
    126, 136,
    127, 110,
    127, 114,
    127, 121,
    127, 128,
    127, 129,
    127, 136,
    128, 110,
    128, 114,
    128, 117,
    128, 121,
    128, 124,
    128, 127,
    128, 130,
    128, 139,
    128, 141,
    129, 110,
    129, 114,
    129, 121,
    129, 124,
    129, 127,
    129, 130,
    129, 139,
    130, 110,
    130, 114,
    130, 121,
    130, 128,
    130, 129,
    130, 136,
    131, 124,
    132, 117,
    132, 124,
    132, 136,
    132, 139,
    135, 117,
    135, 127,
    135, 128,
    135, 136,
    135, 139,
    136, 114,
    136, 116,
    136, 121,
    136, 128,
    136, 136,
    138, 114,
    138, 116,
    138, 121,
    138, 128,
    138, 133,
    138, 136,
    139, 110,
    139, 114,
    139, 116,
    139, 121,
    139, 128,
    139, 129,
    139, 136,
    140, 110,
    140, 114,
    140, 116,
    140, 121,
    140, 128,
    140, 129,
    140, 131,
    140, 136,
    142, 143,
    142, 159,
    142, 160,
    142, 161,
    142, 168,
    143, 146,
    143, 148,
    143, 153,
    143, 160,
    143, 161,
    143, 163,
    143, 168,
    145, 110,
    145, 146,
    145, 147,
    145, 148,
    145, 149,
    145, 153,
    145, 156,
    145, 159,
    145, 162,
    146, 143,
    146, 147,
    146, 149,
    146, 156,
    146, 159,
    146, 160,
    146, 162,
    146, 165,
    146, 168,
    146, 171,
    147, 146,
    147, 148,
    147, 153,
    147, 160,
    147, 161,
    147, 163,
    147, 168,
    148, 147,
    148, 149,
    148, 156,
    148, 159,
    148, 160,
    148, 161,
    148, 162,
    148, 165,
    148, 168,
    148, 171,
    149, 146,
    149, 148,
    149, 153,
    149, 160,
    149, 161,
    149, 163,
    149, 168,
    152, 147,
    152, 149,
    152, 156,
    152, 159,
    152, 160,
    152, 161,
    152, 162,
    152, 165,
    152, 168,
    152, 171,
    156, 146,
    156, 148,
    156, 153,
    156, 160,
    156, 163,
    156, 168,
    158, 146,
    158, 148,
    158, 153,
    158, 160,
    158, 161,
    158, 163,
    158, 168,
    159, 146,
    159, 148,
    159, 153,
    159, 160,
    159, 161,
    159, 163,
    159, 168,
    160, 110,
    160, 146,
    160, 147,
    160, 148,
    160, 149,
    160, 153,
    160, 156,
    160, 159,
    160, 162,
    160, 171,
    161, 110,
    161, 146,
    161, 147,
    161, 148,
    161, 149,
    161, 153,
    161, 159,
    161, 162,
    161, 171,
    162, 146,
    162, 148,
    162, 153,
    162, 160,
    162, 161,
    162, 163,
    162, 168,
    163, 147,
    163, 149,
    163, 156,
    163, 159,
    163, 162,
    163, 171,
    164, 143,
    164, 147,
    164, 149,
    164, 159,
    164, 160,
    164, 162,
    164, 168,
    164, 171,
    167, 143,
    167, 147,
    167, 149,
    167, 156,
    167, 159,
    167, 160,
    167, 162,
    167, 165,
    167, 168,
    167, 171,
    168, 160,
    168, 161,
    170, 160,
    170, 161,
    170, 168,
    171, 146,
    171, 148,
    171, 153,
    171, 160,
    171, 161,
    171, 163,
    171, 168,
    172, 146,
    172, 148,
    172, 153,
    172, 160,
    172, 161,
    172, 163,
    172, 168
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -14, -14, -14, -14, -14, -14, -14, -14,
    -27, -14, -41, -14, -14, -41, -14, -14,
    -14, -55, -41, -42, -55, -14, -27, -13,
    -55, -14, -27, -41, -28, -28, -27, -14,
    -14, -14, -27, -14, -14, -14, -54, -14,
    -14, -14, -14, -14, -14, -14, -15, -13,
    -14, -14, -55, -14, -27, -14, -27, -27,
    -28, -14, -55, -14, -15, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -55, -14,
    -14, -14, -14, -14, -27, -14, -14, -42,
    -14, -14, -97, -15, -14, -14, -14, -14,
    -14, -14, -14, -27, -55, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -27, -14,
    -27, -14, -55, -14, -14, -14, -14, -55,
    -14, -14, -55, -14, -55, -14, -55, -14,
    -14, -14, -27, -27, -14, -14, -14, -55,
    -27, -14, -14, -27, -14, -27, -27, -27,
    -14, -14, -14, -27, -28, -14, -55, -14,
    -55, -55, -70, -14, -14, -14, -27, -14,
    -55, -27, -14, -14, -28, -14, -55, -41,
    -41, -55, -14, -55, -14, -27, -14, -14,
    -27, -28, -27, -14, -55, -27, -97, -13,
    -14, -14, -14, -14, -55, -14, -27, -14,
    -27, -27, -27, -14, -14, -14, -55, -14,
    -14, -14, -14, -14, -55, -27, -55, -14,
    -14, -55, -27, -27, -14, -55, -55, -55,
    -56, -14, -69, -55, -55, -55, -56, -55,
    -55, -55, -55, -27, -55, -55, -55, -55,
    -55, -55, -14, -55, -41, -41, -14, -14,
    -27, -14, -14, -14, -27, -55, -27, -14,
    -14, -14, -40, -14, -41, -14, -14, -14,
    -27, -27, -27, -14, -42, -55, -14, -14,
    -27, -14, -27, -14, -27, -27, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -27,
    -27, -14, -14, -14, -14, -14, -55, -27,
    -14, -14, -27, -14, -27, -27, -27, -55,
    -14, -14, -69, -27, -27, -14, -27, -42,
    -41, -41, -14, -55, -55, -27, -27, -55,
    -27, -42, -27, -41, -27, -27, -27, -27,
    -27, -27, -27, -14, -14, -14, -27, -27,
    -14, -14, -14, -14, -14, -14, -55, -27,
    -14, -14, -27, -14, -27, -27, -27, -14,
    -14, -13, -13, -14, -55, -14, -14, -14,
    -14, -14, -14, -14, -55, -14, -55, -14,
    -55, -14, -55, -27, -14, -55, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -55, -14, -55, -14, -14, -55, -14, -14,
    -14, -14, -14, -14, -14, -55, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -55,
    -14, -55, -13, -14, -55, -14, -14, -14,
    -55, -14, -14, -55, -14, -14, -55, -14,
    -55, -14, -55, -28, -13, -14, -55, -14,
    -27, -14, -55, -14, -55, -27, -14, -55,
    -14, -14, -55, -14, -14, -14, -55, -14,
    -27, -55, -14, -39, -39, -41, -14, -14,
    -14, -27, -27, -14, -14, -14, -14, -69,
    -55, -14, -41, -27, -27, -99, -27, -14,
    -14, -27, -27, -27, -27, -27, -27, -27,
    -14, -27, -14, -14, -14, -27, -27, -27,
    -27, -27, -14, -27, -27, -27, -14, -14,
    -41, -55, -14, -27, -14, -14, -14, -27,
    -27, -27, -14, -27, -55, -55, -14, -27,
    -27, -27, -55, -27, -14, -55, -55, -27,
    -14, -14, -14, -14, -14, -27, -27, -55,
    -14, -55, -14, -14, -14, -27, -27, -14,
    -27, -27, -27, -27, -14, -14, -14, -55,
    -55, -14, -14, -14, -55, -14, -55, -14,
    -27, -27, -27, -27, -14, -27, -14, -27,
    -27, -27, -27, -14, -14, -27, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -14, -14, -39, -41, -14, -27, -14, -41,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -27, -14, -14, -27, -27, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -14, -14, -14, -27, -41, -14, -27, -14,
    -41, -14, -14, -14, -14, -41, -41, -14,
    -14, -14, -41, -14, -14, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14,
    -27, -14, -27, -27, -14, -55, -27, -55,
    -27, -41, -14, -14, -14, -14, -14, -14,
    -14, -14, -14, -14, -14, -14, -14, -14
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 704,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 5,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t offbit_regular_16 = {
#else
lv_font_t offbit_regular_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if OFFBIT_REGULAR_16*/

