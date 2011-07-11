/*****************************************************************************
* bit_sets.c
* 
* Randy Miller
*
* Counts the number of bits set
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_BYTE 8
//Different methods
#define REG      0
#define MINUS1   1

int
mod_division(void)
{
    int result, method;
    int numerator, shift, denominator;

    printf("Which method should we use to count the number of bits set?  Here are your options:\n\n");
    printf("0. The regular way\n");
    printf("1. By (1 << s) - 1\n");

    do {
        printf("Please type one of the ints in the option list above:\n");
        scanf("%d", &method);
    }while (method < REG || method > MINUS1);

    //get input
    printf("The numerator is:\n");
    scanf("%d", &numerator);
    printf("The denominator is:\n");
    scanf("%d", &denominator);

    //do the division
    switch (method) {
    case REG:
        shift = 1U << denominator;
        result = numerator & (denominator - 1);
        break;
    case MINUS1:
        shift = (1 << denominator) - 1;
        for (result = numerator; numerator > denominator; numerator = result)
            for (result = 0; numerator; numerator >>= denominator)
                result += numerator & shift;
        result = result == denominator ? 0 : result;
        break;
    default: return 1; break;
    }
    
    printf("The result of dividing %d by %d is %d\n", numerator, denominator, result);

    return 0;
}
