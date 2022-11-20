#pragma once

#include <iostream>

static const uint8_t decode_shffule_table[256 * 16] = {
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, // 0000
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, // 1000
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, // 2000
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, // 3000
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, // 0100
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, // 1100
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, // 2100
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, // 3100
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, // 0200
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, // 1200
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, // 2200
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0x08, 0xFF, 0xFF, 0xFF, // 3200
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, // 0300
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, // 1300
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0xFF, 0xFF, 0x08, 0xFF, 0xFF, 0xFF, // 2300
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0xFF, 0x09, 0xFF, 0xFF, 0xFF, // 3300
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, // 0010
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, // 1010
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, // 2010
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, // 3010
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, // 0110
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, // 1110
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, // 2110
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0xFF, 0xFF, 0xFF, // 3110
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, // 0210
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, // 1210
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0xFF, 0xFF, 0xFF, // 2210
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0xFF, 0xFF, 0x09, 0xFF, 0xFF, 0xFF, // 3210
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, // 0310
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0xFF, 0xFF, 0xFF, // 1310
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0x09, 0xFF, 0xFF, 0xFF, // 2310
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, 0x0A, 0xFF, 0xFF, 0xFF, // 3310
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, // 0020
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, // 1020
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, // 2020
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0xFF, 0xFF, 0xFF, // 3020
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, // 0120
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, // 1120
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0xFF, 0xFF, 0xFF, // 2120
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0xFF, 0x09, 0xFF, 0xFF, 0xFF, // 3120
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, // 0220
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0xFF, 0xFF, 0xFF, // 1220
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0xFF, 0x09, 0xFF, 0xFF, 0xFF, // 2220
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0xFF, 0x0A, 0xFF, 0xFF, 0xFF, // 3220
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0x08, 0xFF, 0xFF, 0xFF, // 0320
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0x09, 0xFF, 0xFF, 0xFF, // 1320
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0x0A, 0xFF, 0xFF, 0xFF, // 2320
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0x0B, 0xFF, 0xFF, 0xFF, // 3320
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0xFF, 0xFF, // 0030
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0xFF, 0xFF, // 1030
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0xFF, // 2030
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, 0xFF, // 3030
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0xFF, 0xFF, // 0130
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0xFF, // 1130
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, 0xFF, // 2130
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0xFF, 0xFF, // 3130
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0xFF, // 0230
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, 0xFF, // 1230
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0xFF, 0xFF, // 2230
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, 0xFF, 0xFF, // 3230
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, 0xFF, // 0330
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0xFF, 0xFF, // 1330
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, 0xFF, 0xFF, // 2330
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0xFF, 0xFF, 0xFF, // 3330
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0xFF, 0xFF, // 0001
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0xFF, 0xFF, // 1001
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, // 2001
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0xFF, 0xFF, // 3001
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0xFF, 0xFF, // 0101
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, // 1101
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0xFF, 0xFF, // 2101
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0x08, 0xFF, 0xFF, // 3101
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, // 0201
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0xFF, 0xFF, // 1201
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0x08, 0xFF, 0xFF, // 2201
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0x08, 0x09, 0xFF, 0xFF, // 3201
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0xFF, 0xFF, // 0301
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0x08, 0xFF, 0xFF, // 1301
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0xFF, 0xFF, 0x08, 0x09, 0xFF, 0xFF, // 2301
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0xFF, 0x09, 0x0A, 0xFF, 0xFF, // 3301
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0xFF, 0xFF, // 0011
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, // 1011
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0xFF, 0xFF, // 2011
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0xFF, 0xFF, // 3011
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, // 0111
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0xFF, 0xFF, // 1111
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0xFF, 0xFF, // 2111
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0x09, 0xFF, 0xFF, // 3111
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0xFF, 0xFF, // 0211
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0xFF, 0xFF, // 1211
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0x09, 0xFF, 0xFF, // 2211
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0xFF, 0xFF, 0x09, 0x0A, 0xFF, 0xFF, // 3211
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0xFF, 0xFF, // 0311
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0x09, 0xFF, 0xFF, // 1311
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0x09, 0x0A, 0xFF, 0xFF, // 2311
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, 0x0A, 0x0B, 0xFF, 0xFF, // 3311
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0xFF, 0xFF, // 0021
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0xFF, 0xFF, // 1021
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0xFF, 0xFF, // 2021
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0xFF, 0xFF, // 3021
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0xFF, 0xFF, // 0121
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0xFF, 0xFF, // 1121
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0xFF, 0xFF, // 2121
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0xFF, 0x09, 0x0A, 0xFF, 0xFF, // 3121
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0xFF, 0xFF, // 0221
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0xFF, 0xFF, // 1221
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0xFF, 0x09, 0x0A, 0xFF, 0xFF, // 2221
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0xFF, 0x0A, 0x0B, 0xFF, 0xFF, // 3221
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0xFF, 0xFF, // 0321
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0x09, 0x0A, 0xFF, 0xFF, // 1321
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0x0A, 0x0B, 0xFF, 0xFF, // 2321
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0x0B, 0x0C, 0xFF, 0xFF, // 3321
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0xFF, // 0031
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, // 1031
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, // 2031
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0xFF, // 3031
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, // 0131
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, // 1131
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0xFF, // 2131
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, 0xFF, // 3131
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, // 0231
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0xFF, // 1231
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, 0xFF, // 2231
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0xFF, 0xFF, // 3231
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0xFF, // 0331
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, 0xFF, // 1331
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0xFF, 0xFF, // 2331
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0xFF, 0xFF, // 3331
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0xFF, // 0002
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0xFF, // 1002
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, // 2002
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0xFF, // 3002
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0xFF, // 0102
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, // 1102
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0xFF, // 2102
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0xFF, // 3102
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, // 0202
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0xFF, // 1202
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0xFF, // 2202
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0x08, 0x09, 0x0A, 0xFF, // 3202
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0xFF, // 0302
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0xFF, // 1302
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0xFF, 0xFF, 0x08, 0x09, 0x0A, 0xFF, // 2302
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0xFF, 0x09, 0x0A, 0x0B, 0xFF, // 3302
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0xFF, // 0012
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, // 1012
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0xFF, // 2012
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0xFF, // 3012
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, // 0112
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0xFF, // 1112
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0xFF, // 2112
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0x09, 0x0A, 0xFF, // 3112
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0xFF, // 0212
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0xFF, // 1212
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0x09, 0x0A, 0xFF, // 2212
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0xFF, 0xFF, 0x09, 0x0A, 0x0B, 0xFF, // 3212
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0xFF, // 0312
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0x09, 0x0A, 0xFF, // 1312
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0x09, 0x0A, 0x0B, 0xFF, // 2312
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, 0x0A, 0x0B, 0x0C, 0xFF, // 3312
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0x07, 0xFF, // 0022
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0xFF, // 1022
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0xFF, // 2022
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0x0A, 0xFF, // 3022
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0xFF, // 0122
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0xFF, // 1122
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0x0A, 0xFF, // 2122
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0xFF, 0x09, 0x0A, 0x0B, 0xFF, // 3122
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0xFF, // 0222
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0x0A, 0xFF, // 1222
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0xFF, 0x09, 0x0A, 0x0B, 0xFF, // 2222
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0xFF, 0x0A, 0x0B, 0x0C, 0xFF, // 3222
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0x0A, 0xFF, // 0322
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0x09, 0x0A, 0x0B, 0xFF, // 1322
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0x0A, 0x0B, 0x0C, 0xFF, // 2322
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0x0B, 0x0C, 0x0D, 0xFF, // 3322
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, // 0032
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, // 1032
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, // 2032
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, // 3032
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, // 0132
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, // 1132
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, // 2132
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0xFF, // 3132
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, // 0232
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, // 1232
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0xFF, // 2232
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0xFF, // 3232
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, // 0332
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0xFF, // 1332
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0xFF, // 2332
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0xFF, // 3332
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0x06, // 0003
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0x07, // 1003
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, // 2003
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, // 3003
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0x07, // 0103
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, // 1103
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, // 2103
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0x0A, // 3103
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, // 0203
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, // 1203
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0x0A, // 2203
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0xFF, 0xFF, 0xFF, 0x08, 0x09, 0x0A, 0x0B, // 3203
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, // 0303
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0x0A, // 1303
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0xFF, 0xFF, 0x08, 0x09, 0x0A, 0x0B, // 2303
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0xFF, 0x09, 0x0A, 0x0B, 0x0C, // 3303
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0x07, // 0013
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, // 1013
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, // 2013
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0x0A, // 3013
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, // 0113
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, // 1113
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0x0A, // 2113
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0x09, 0x0A, 0x0B, // 3113
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, // 0213
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0x0A, // 1213
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0x09, 0x0A, 0x0B, // 2213
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0xFF, 0xFF, 0x09, 0x0A, 0x0B, 0x0C, // 3213
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0xFF, 0x07, 0x08, 0x09, 0x0A, // 0313
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0xFF, 0x08, 0x09, 0x0A, 0x0B, // 1313
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0x09, 0x0A, 0x0B, 0x0C, // 2313
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, 0x0A, 0x0B, 0x0C, 0x0D, // 3313
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0x07, 0x08, // 0023
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0x09, // 1023
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0x0A, // 2023
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0x0A, 0x0B, // 3023
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0x09, // 0123
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0x0A, // 1123
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0x0A, 0x0B, // 2123
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0xFF, 0x09, 0x0A, 0x0B, 0x0C, // 3123
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0x0A, // 0223
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0x0A, 0x0B, // 1223
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0xFF, 0x09, 0x0A, 0x0B, 0x0C, // 2223
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0xFF, 0x0A, 0x0B, 0x0C, 0x0D, // 3223
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xFF, 0x08, 0x09, 0x0A, 0x0B, // 0323
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF, 0x09, 0x0A, 0x0B, 0x0C, // 1323
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0x0A, 0x0B, 0x0C, 0x0D, // 2323
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0xFF, 0x0B, 0x0C, 0x0D, 0x0E, // 3323
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, // 0033
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, // 1033
    0x00, 0x01, 0x02, 0xFF, 0x03, 0xFF, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, // 2033
    0x00, 0x01, 0x02, 0x03, 0x04, 0xFF, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, // 3033
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, // 0133
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0xFF, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, // 1133
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0xFF, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, // 2133
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0xFF, 0xFF, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, // 3133
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0xFF, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, // 0233
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0xFF, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, // 1233
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0xFF, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, // 2233
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0xFF, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, // 3233
    0x00, 0xFF, 0xFF, 0xFF, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, // 0333
    0x00, 0x01, 0xFF, 0xFF, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, // 1333
    0x00, 0x01, 0x02, 0xFF, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, // 2333
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, // 3333
};