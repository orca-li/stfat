#include "bpbman.h"

#define BytsPerSec_offset 11
#define SecPerClus_offset 13
#define RsvdSecCnt_offset 14
#define NumFATs_offset 16
#define FATSz32_offset 36

typedef uint16_t BytsPerSec_t;
typedef uint8_t SecPerClus_t;
typedef uint16_t RsvdSecCnt_t;
typedef uint8_t NumFATs_t;
typedef uint32_t FATSz32_t;

typedef struct BIOS_PARAMETER_BLOCK
{
    BytsPerSec_t BytsPerSec; /* кол-во байтов внутри сектора */
    SecPerClus_t SecPerClus; /* кол-во секторов в одном кластере */
    RsvdSecCnt_t RsvdSecCnt; /* кол-во секторов в reserved region */
    NumFATs_t NumFATs; /* количество fat-таблиц */
    FATSz32_t FATSz32; /* количество секторов в fat region */
} bpblock_t;

static bpblock_t bpb;

static void ParseClusterSize(loccnt_t lcnt)
{
    lcntadd(&lcnt, SecPerClus_offset);
    SecPerClus_t* read;

    read = (SecPerClus_t*)lcnt.p;
    bpb.SecPerClus = *read;
}

static void ParseFatRegionSize(loccnt_t lcnt)
{
    lcntadd(&lcnt, FATSz32_offset);
    FATSz32_t* read;

    read = (FATSz32_t*)lcnt.p;
    bpb.FATSz32 = *read;
}

static void ParseSectorSize(loccnt_t lcnt)
{
    lcntadd(&lcnt, BytsPerSec_offset);
    BytsPerSec_t* read;

    read = (BytsPerSec_t*)lcnt.p;
    bpb.BytsPerSec = *read;
}

static void ParseReservedRegionSize(loccnt_t lcnt)
{
    lcntadd(&lcnt, RsvdSecCnt_offset);
    RsvdSecCnt_t* read;

    read = (RsvdSecCnt_t*)lcnt.p;
    bpb.RsvdSecCnt = *read;
}

static void ParseNumbofFats(loccnt_t lcnt)
{
    lcntadd(&lcnt, NumFATs_offset);
    NumFATs_t* read;

    read = (NumFATs_t*)lcnt.p;
    bpb.NumFATs = *read;
}

void manBpbRead(loccnt_t* const lcnt)
{
    ParseSectorSize(*lcnt);
    ParseClusterSize(*lcnt);
    ParseReservedRegionSize(*lcnt);
    ParseNumbofFats(*lcnt);
    ParseFatRegionSize(*lcnt);
}

/* количество секторов в зарезервированном регионе */
size_t _bpbGetNumbofRsvdSec(void)
{
    return bpb.RsvdSecCnt;
}

/* размер зарезервированного региона */
size_t _bpbGetRsvdRegSz(void)
{
    return bpb.RsvdSecCnt * bpb.BytsPerSec;
}

/* количество байтов в секторе */
size_t _bpbGetSctrSz(void)
{
    return bpb.BytsPerSec;
}

/* количество секторов в fat регионе */
size_t _bpbGetNumbofFatRegionSec(void)
{
    return bpb.FATSz32;
}

/* количество фат таблиц */
size_t _bpbGetNumbfFatTables(void)
{
    return bpb.NumFATs;
}

/* получить размер кластера в секторах */
size_t _bpbGetClusterSize(void)
{
    return bpb.SecPerClus;
}