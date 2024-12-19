#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define fatENABLE_TABLE_LOGGER
#include "logger.h"
#include "regman.h"
#include "bpbman.h"

static void fatLogCreateTable(void)
{
    fatTABLE0_PrintBoard();
    fatTABLE0_PrintColumn(REGION);
    fatTABLE0_PrintColumn(CLUSTER);
    fatTABLE0_PrintColumn(SECTOR);
    fatTABLE0_PrintColumn(ADDRESS);
    fatTABLE0_PrintColumn(HEX);
    fatTABLE0_PrintColumn(DEC);
    fatTABLE0_PrintColumn(ASCII);
    fatTABLE0_PrintColumn(DUMP);

    putchar('\n');
    fatTABLE0_PrintBoard();
}

static void FillTableHexDump(loccnt_t lcnt)
{
    for(size_t i = 0; i < fatTABLE0_NUMBOFCHAR_DUMP; i++)
    {
        printf("%02hhx ", *lcnt.p++);
    }
}

static void FillTableAsciiDump(loccnt_t lcnt)
{
    char c;

    for (size_t i = 0; i < fatTABLE0_NUMBOFCHAR_DUMP; i++)
    {
        c = *lcnt.p++;    
        if (isprint(c))
        {
            putchar(c);
        }
        else
        {
            putchar('.');
        }
    }
    printf("  ");
}

static void FilligTableNoData(char *region, const seccnt_t seccnt)
{
    static char buffer[fatTABLE0_TOTAL_WIDTH];

    fatTABLE0_PrintItem(region, REGION);
    fatTABLE0_PrintItem("-", CLUSTER);

    sprintf(buffer, "sector[%ld]", seccnt.c);
    fatTABLE0_PrintItem(buffer, SECTOR);

    sprintf(buffer, "%-16p", seccnt.lcnt.p);
    fatTABLE0_PrintItem(buffer, ADDRESS);

    sprintf(buffer, "%lx", seccnt.lcnt.c);
    fatTABLE0_PrintItem(buffer, HEX);

    sprintf(buffer, "%ld", seccnt.lcnt.c);
    fatTABLE0_PrintItem(buffer, DEC);

    FillTableAsciiDump(seccnt.lcnt);
    FillTableHexDump(seccnt.lcnt);

    putchar('\n');
}

static void FillingTableDataRegion(const clscnt_t clscnt)
{
    static char buffer[fatTABLE0_TOTAL_WIDTH];

    fatTABLE0_PrintItem("data", REGION);

    sprintf(buffer, "cluster[%ld]", clscnt.c);
    fatTABLE0_PrintItem(buffer, CLUSTER);

    sprintf(buffer, "sector[%ld]", clscnt.seccnt.c);
    fatTABLE0_PrintItem(buffer, SECTOR);

    sprintf(buffer, "%-16p", clscnt.seccnt.lcnt.p);
    fatTABLE0_PrintItem(buffer, ADDRESS);

    sprintf(buffer, "%lx", clscnt.seccnt.lcnt.c);
    fatTABLE0_PrintItem(buffer, HEX);

    sprintf(buffer, "%ld", clscnt.seccnt.lcnt.c);
    fatTABLE0_PrintItem(buffer, DEC);

    FillTableAsciiDump(clscnt.seccnt.lcnt);
    FillTableHexDump(clscnt.seccnt.lcnt);

    putchar('\n');
}

static void fatLogFillingTable(char *const position)
{
    clscnt_t clscnt = {
        .c = 0,
        .sz = _bpbGetClusterSize(),
        .seccnt = {
            .c = 0,
            .sz = _bpbGetSctrSz(),
            .lcnt = {
                .c = 0,
                .p = position}}};

    FilligTableNoData("rsvd[bpb]", clscnt.seccnt);
    for (size_t i = 0; i < _bpbGetNumbofRsvdSec() - fatINDEX_OFFSET_SZ; i++)
    {
        seccntpp(&clscnt.seccnt);
        FilligTableNoData("rsvd", clscnt.seccnt);
    }
    for (size_t i = 0; i < _bpbGetNumbfFatTables(); i++)
    {
        char fat_idx[fatTABLE0_REGION_WIDTH];
        sprintf(fat_idx, "fat[%ld]", i);
        for (size_t ii = 0; ii < _bpbGetNumbofFatRegionSec(); ii++)
        {
            seccntpp(&clscnt.seccnt);
            FilligTableNoData(fat_idx, clscnt.seccnt);
        }
    }

    seccntpp(&clscnt.seccnt); /* offset for cluster zero index */
    for (size_t i = 0; i < _bpbGetNumbofClusters(); i++)
    {
        FillingTableDataRegion(clscnt);
        clscntpp(&clscnt);
    }
}

void fatLogSctr(char *buffer)
{
    fatLogCreateTable();
    fatLogFillingTable(buffer);
    putchar('\n');
}