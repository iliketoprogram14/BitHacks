/*****************************************************************************
* highest_pow2.c
* 
* Randy Miller
*
* Finds the next highest power of 2 from a given value
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define FLOAT   0
#define REGULAR 1

int
highest_pow2(void)
{
    int v, result, method, t;
    float tmp;
    
    printf("Which method should be used?\n\n0. Float casting\n1. Using or operators\n");

    do {
        printf("Please enter the number of one of the above options:");
        scanf("%d", &method);
    } while (method < FLOAT && method);
    
    //get input
    printf("Compute the absolute value of: \n");
    scanf("%d", &v);

    switch(method) {
    case FLOAT:
        if (v > 1) {
            tmp = (float)v;
            t = 1U << ((*(unsigned int *)&tmp >> 23) - 0x7f);
            result = t << (t < v);
        } else
            result = 1;
        break;
    case REGULAR:
        result = v;
        
        result--;
        result |= result >> 1;
        result |= result >> 2;
        result |= result >> 4;
        result |= result >> 8;
        result |= result >> 16;
        result++;
        break;
    default:
        printf("ERROR, WILL ROBINSON, ERROR\n");
        return 1;
    }

    printf("The next highest power of 2 of %d is %d\n", v, result);
    
    return 0;
}
