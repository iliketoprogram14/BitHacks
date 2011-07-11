/*****************************************************************************
* sign.c
* 
* Randy Miller
*
* Compute the sign of an integer
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARCH_IS_64 0
#define BITS_PER_BYTE (ARCH_IS_64 ? 16 : 8)
#define ARCH_NUM_BITS (ARCH_IS_64 ? 64 : 32)
#define CHAR_BIT 8
//different types of methods for computing sign
#define CHAR_BIT 0
#define X86      1
#define NONPORT  2
#define NEG_OR_POS 3
#define OR_ZERO  4
#define SPEEDIER 5
#define PORTABLE 6
#define NON_NEG  7

int
sign(void) 
{
    int method, value, result, v;
    
    //get input
    printf("Which method should we use to compute the sign of an integer?  Here are your options:\n\n");
    printf("0. ");

    do {
        printf("Please type one of the ints in the option list above:\n");
        scanf("%d", &method);
    }while (method < CHAR_BIT && method > NON_NEG);

    //get input
    printf("Compute the sign of what value?");
    scanf("%d", &value);
    v = value;
    
    switch(method) {
    case CHAR_BIT:
        result = -(v < 0);
        break;
    case X86:
        result = -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT -1));
        break;
    case NONPORT:
        result = v >> (sizeof(int) * CHAR_BIT - 1);
        break;
    case NEG_OR_POS:
        result = +1 | (v >> (sizeof(int) * CHAR_BIT - 1));
        break;
    case OR_ZERO:
        result = (v != 0) | -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
        break;
    case SPEEDIER:
        result = (v != 0) | (v >> (sizeof(int) * CHAR_BIT - 1));
        break;
    case PORTABLE:
        result = (v > 0) - (v < 0);
        break;
    case NON_NEG:
        result = 1 ^ ((unsigned int)v >> (sizeof(int) * CHAR_BIT - 1));
        break;
    default:
        printf("ERROR, WILL ROBINSON, ERROR!!!\n");
        return;
        break;
    }
    printf("The sign of %d is %s\n", value, ());

    return;
}

