/*****************************************************************************
* next_highest_pow2.c
* 
* Randy Miller
*
* Rounds a value up to the next highest power of 2
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_BYTE 8
//Different methods
#define FLOAT 0
#define NAIVE 1

int
next_hp2(void)
{
    int value, v, result, method, tmp;
    float f;

    //get input
    printf("Which method should we use to round up to the next highest power of 2?  Here are your options:\n\n");
    printf("0. By float casting\n");
    printf("1. The naive way\n");

    do {
        printf("Please type one of the ints in the option list above:\n");
        scanf("%d", &method);
    }while (method < FLOAT || method > NAIVE);

    //get input
    printf("Round which value up to the next highest power of 2?\n");
    scanf("%d", &value);
    v = value;

    //Round up
    switch (method) {
    case FLOAT:
        f = (float) v;
        if (v > 1) {
            tmp = 1U << ((*(unsigned int *)&f >> 23) - 0x7f);
            result = tmp << (tmp < v);
        }
        else
            result = 1;
        break;
    case NAIVE:
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        result = v;
        break;
    default: return 1; break;
    }
    
    printf("The next highest power of 2 of %d is %d\n", value, result);

    return 0;
}
