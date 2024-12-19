#include "stfat.h"
#include "bpbman.h"

void fatInit(char* buffer)
{
    loccnt_t lcnt = {
        .p = buffer,
        .c = 0
    };
    manBpbRead(&lcnt);
}
