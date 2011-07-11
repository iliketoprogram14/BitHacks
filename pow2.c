/*****************************************************************************
* pow2.c
* 
* Randy Miller
*
* Determines if an integer is a power of 2
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_BYTE 8
#define FASTER 0
#define SLOWER 1
//method 0 is faster, but thinks 0 is a power of 2
//method 1 is slower, but remedies the above problem

int
pow2(void)
{
    int value, result, method;

    printf("Which method do you want to use to determine if a value is a power of 2?\n");
    printf("0. Faster, but thinks 0 is a power of 2\n");
    printf("1. Slower, but remedies the above problem\n");
    do {
        printf("Please type the number of one of the following options:");
        scanf("%d", &method);
    } while(method < 0 || method > 1);
    
    //get input
    printf("Which value do you think is a power of 2?\n");
    scanf("%d", &value);

    /* determine if it's a power of 2 */
    //method 0 needs to check if the value is 0
    if (!method) {
        result = (value & (value - 1)) == 0;
        printf("%s\n", (!result || value == 0 ? "No" : "Yes"));
    }
    else {
        result = value && !(value & (value - 1));
        printf("%s\n", (!result ? "No" : "Yes"));
    }

    return 0;
}
