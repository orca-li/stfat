#pragma once

#include "fatdef.h"

#if defined fatENABLE_TABLE_LOGGER

#define fatTABLE0_REGION_WIDTH 12
#define fatTABLE0_CLUSTER_WIDTH 16
#define fatTABLE0_SECTOR_WIDTH 16
#define fatTABLE0_ADDRESS_WIDTH 16
#define fatTABLE0_HEX_WIDTH 8
#define fatTABLE0_DEC_WIDTH 12
#define fatTABLE0_DUMP_WIDTH 23
#define fatTABLE0_ASCII_WIDTH 11

#define fatTABLE0_NUMBOFCHAR_DUMP 8

#define fatTABLE0_TOTAL_WIDTH (     \
      fatTABLE0_REGION_WIDTH        \
    + fatTABLE0_CLUSTER_WIDTH       \
    + fatTABLE0_SECTOR_WIDTH        \
    + fatTABLE0_ADDRESS_WIDTH       \
    + fatTABLE0_HEX_WIDTH           \
    + fatTABLE0_DEC_WIDTH           \
    + fatTABLE0_ASCII_WIDTH         \
    + fatTABLE0_DUMP_WIDTH          \
)

#define fatTABLE0_PrintBoard()  \
    for (unsigned char i = 0; i < fatTABLE0_TOTAL_WIDTH; i++) \
    {                   \
        putchar('=');   \
    }                   \
    putchar('\n')

#define fatTABLE0_PrintColumn(_name) \
    fatTABLE0_Internal_PrintColumn(_name, fatTABLE0_ ## _name ## _WIDTH)

#define _fatTABLE0_Internal_2_PrintColumn(_name, _sz) \
    printf("%-"#_sz"s", #_name)

#define fatTABLE0_Internal_PrintColumn(_name, _sz) \
    _fatTABLE0_Internal_2_PrintColumn(_name, _sz)

#define _fatTABLE0_Internal_2_PrintItem(_name, _col) \
    printf("%-"#_col"s", _name);

#define _fatTABLE0_Internal_PrintItem(_item, _col) \
    _fatTABLE0_Internal_2_PrintItem(_item, _col)

#define fatTABLE0_PrintItem(_item, _col) \
    _fatTABLE0_Internal_PrintItem(_item, fatTABLE0_ ## _col ## ## _WIDTH)

#endif