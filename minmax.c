/*****************************************************************************
* minmax.c
* 
* Randy Miller
*
* Computes the minimum or maximum between two ints
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITS_PER_BYTE 8

int
minmax(void)
{
    int x, y, result;
    char min_or_max[3];
    
    //does the user want to compute the min or the max?
    printf("Do you want to compute the min or the max?  Type min or max: ");
    gets(min_or_max);
    int strcmpmin = strcmp(min_or_max, "min");
    int strcmpmax = strcmp(min_or_max, "max");
    if (strcmpmin != 0 && strcmpmax != 0) {
        printf("Please enter \"max\" or \"min\"\n");
        return 1;
    }                           

    //get input
    printf("What's the first value?\n");
    scanf("%d", &x);
    printf("What's the second value?\n");
    scanf("%d", &y);

    //compute the min
    if (strcmpmin == 0)
        result = y ^ ((x ^ y) & -(x < y));
    //compute the max
    else
        result = x ^ ((x ^ y) & -(x < y));
    printf("\nThe %s of %d and %d is %d\n", min_or_max, x, y, result);

    return 0;
}
