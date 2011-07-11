/*****************************************************************************
* negate.c
* 
* Randy Miller
*
* Conditionally negate a value without branching (flag is 1 if negating)
* This is equivalent to the following:
*
* if (flag)
*    word |= mask;
* else
*    word &= ~mask;
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BITS_PER_BYTE 8
#define UNCHANGED -1

int
negate(void)
{
    char flagstr[4];
    int flag, value, result;
    
    //get input
    printf("Should we negate the value? Type yes or no: \n");
 input:
    gets(flagstr);

    flag = UNCHANGED;
    flagstr[0] = tolower((int)flagstr[0]);
    flag = (strcmp(flagstr, "yes") == 0 ? 1 :
            (strcmp(flagstr, "no") == 0 ? 0 : UNCHANGED));

    if (flag == UNCHANGED) {
        flagstr[3] = '\0';
        printf("Please type in yes or no\n");
        goto input;
    }

    printf("What's the value to operate on?\n");
    scanf("%d", &value);

    result = (value ^ -flag) + flag;
    
    printf("result: %d\n", result);

    return 0;
}
