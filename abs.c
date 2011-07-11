/*****************************************************************************
* abs.c
* 
* Randy Miller
*
* Compute the absolute value of an integer (without branching)
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_BYTE 8

int
abs_bits(void) 
{
    int value, result, mask;
    
     //get input
    printf("Compute the absolute value of: \n");
    scanf("%d", &value);

    //compute the mask
    mask = value >> (sizeof(int) * BITS_PER_BYTE - 1);

    //compute the abs value and store in result
    result = (value + mask) ^ mask;
    printf("The absolute value of %d is %d\n", value, result);

    return 0;
}
