#pragma once

/**
 * @file lcnt.h
 * @details this file provide counter objects API
 * lcnt - location counter
 * seccnt - sector counter
 * sctcnt - section counter
 * clscnt - cluster counter
 */

#include <stddef.h>

typedef struct LOCATION_COUNTER
{
    char* p; /* byte address */
    unsigned long c; /* byte counter */
} loccnt_t;
/**
 * lcnt++
 */
void lcntpp(loccnt_t*);
/**
 * lcnt = p;
 */
void lcntset(loccnt_t*, char* const set);
/**
 * lcnt += x;
 */
void lcntadd(loccnt_t*, const signed long inc);


typedef struct SECTOR_COUNTER
{
    size_t sz; /* sector size */
    size_t c; /* sector counter */
    loccnt_t lcnt;
} seccnt_t;
/**
 * seccnt++;
 */
void seccntpp(seccnt_t*);
/**
 * seccnt += x;
 */
void seccntadd(seccnt_t* seccnt, const signed long inc);


typedef struct CLUSTER_COUNTER
{
    size_t sz; /* cluster size */
    size_t c; /* cluster counter */
    seccnt_t seccnt; /* sector counter */
} clscnt_t;
/**
 * 
 */
void clscntpp(clscnt_t*);