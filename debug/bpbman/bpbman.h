#pragma once

#include "fatdef.h"

void manBpbRead(loccnt_t* const lcnt);
size_t _bpbGetSctrSz(void);
size_t _bpbGetNumbofRsvdSec(void);
size_t _bpbGetNumbofFatRegionSec(void);
size_t _bpbGetNumbfFatTables(void);
size_t _bpbGetClusterSize(void);
size_t _bpbGetNumbofClusters(void);