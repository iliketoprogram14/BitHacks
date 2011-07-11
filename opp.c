/*****************************************************************************
* opp.c
* 
* Randy Miller
*
* Detects if two integers have opposite signs
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_BYTE 8

int
opp (void)
{
    int first, second, result;
    
    //get input
    printf("What's the first value?\n");
    scanf("%d", &first);
    printf("What's the second value?\n");
    scanf("%d", &second);

    //detect the difference in signs
    result = (first ^ second) < 0;
    printf("The signs are %s\n", (result == 0 ? "the same" : "different"));

    return 0;
}
