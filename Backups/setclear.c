/*****************************************************************************
* setclear.c
* 
* Randy Miller
*
* Conditionally set or clear bits without branching
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
//method 1 is for superscalar CPUs, and method 0 is for everything else
#define METHOD 1
#define UNCHANGED -1

int
setclear(void)
{
    char flagstr[6];
    int flag, mask, word;
    
    //get input
    printf("Do you want to set or clear the bits of the word to modify? Type set or clear: \n");
 input:
    gets(flagstr);

    flag = UNCHANGED;
    flagstr[0] = tolower((int)flagstr[0]);
    flag = (strcmp(flagstr, "set") == 0 ? 1 :
            (strcmp(flagstr, "clear") == 0 ? 0 : UNCHANGED));

    if (flag == UNCHANGED) {
        flagstr[5] = '\0';
        printf("Please type in set or clear\n");
        goto input;
    }

    printf("What's the bit mask?\n");
    scanf("%d", &mask);
    printf("What's the word?\n");
    scanf("%d", &word);

    if (!METHOD)
        word ^= (-flag ^ word) & mask;
    //superscalar method
    else
        word = (word & ~mask) | (-flag & mask);

    printf("result: %d\n", word);

    return 0;
}
