#include "lcnt.h"

/**
 * @brief LOCATION COUNTER
 */
void lcntpp(loccnt_t* lcnt)
{
    lcnt->p++;
    lcnt->c++;
}

void lcntset(loccnt_t* lcnt, char* const newpos)
{
    char* direction;
    unsigned long step;

    step = 0;
    direction = newpos;

    direction++;
    step = (lcnt->p < newpos) ? newpos - lcnt->p : lcnt->p - newpos;
    if (direction < newpos)
    {
        lcnt->c -= step;
    }
    else
    {
        lcnt->c += step;
    }

    lcnt->p = newpos;
}

void lcntadd(loccnt_t* lcnt, const signed long inc)
{
    lcnt->p += inc;
    lcnt->c += inc;
}

/**
 * @brief SECTOR COUNTER
 */
void seccntpp(seccnt_t* seccnt)
{
    lcntset(&seccnt->lcnt, seccnt->lcnt.p + seccnt->sz);
    seccnt->c++;
}

void seccntadd(seccnt_t* seccnt, const signed long inc)
{
    lcntset(&seccnt->lcnt, seccnt->lcnt.p + (seccnt->sz * inc));
    seccnt->c += inc;
}

/**
 * @brief CLUSTER COUNTER
 */
void clscntpp(clscnt_t* clscnt)
{
    seccntadd(&clscnt->seccnt, clscnt->sz);
    clscnt->c++;
}