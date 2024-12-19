#pragma once

#include "lcnt.h"

#include <stddef.h>
#include <stdint.h>

typedef uint8_t status_fat_t;
typedef uint8_t level_fat_t;

/**
 * status list
 */
#define fatSILENT 0
#define fatEVENT 1

/**
 * level list
 */
#define fatLEVELok 0
#define fatLEVELwarning 1
#define fatLEVELerror 2

#define fatINDEX_OFFSET_SZ 1