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
#define CHAR_BITS  0
#define X86        1
#define NONPORT    2
#define NEG_OR_POS 3
#define OR_ZERO    4
#define SPEEDIER   5
#define PORTABLE   6
#define NON_NEG    7

int
sign(void) 
{
    int method, value, result, v;
    
    //get input
    printf("Which method should we use to compute the sign of an integer?  Here are your options:\n\n");
    printf("0. Negate a comparison against 0\n");
    printf("1. Negate a right bit shift\n");
    printf("2. Same as 1, but not portable\n");
    printf("3. Same as 1, but different results\n");
    printf("4. Same as 1, but can detect 0\n");
    printf("5. Same as 4, but faster and less portable\n");
    printf("6. Same as 5, but more portable\n");
    printf("7. Same as 1, but delivers non-negative result\n");

    do {
        printf("Please type one of the ints in the option list above:\n");
        scanf("%d", &method);
    }while (method < CHAR_BIT || method > NON_NEG);

    //get input
    printf("Compute the sign of what value?\n");
    scanf("%d", &value);
    v = value;
    int is_positive = 0;
    
    switch(method) {
    case CHAR_BITS:
        result = -(v < 0);
        is_positive = !abs(result);
        break;
    case X86:
        result = -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT -1));
        is_positive = !abs(result);
        break;
    case NONPORT:
        result = v >> (sizeof(int) * CHAR_BIT - 1);
        is_positive = !abs(result);
        break;
    case NEG_OR_POS:
        result = +1 | (v >> (sizeof(int) * CHAR_BIT - 1));
        is_positive = (result == 1 ? 1 : 0);
        break;
    case OR_ZERO:
        result = (v != 0) | -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
        is_positive = (result >=0 ? 1 : 0);        
        break;
    case SPEEDIER:
        result = (v != 0) | (v >> (sizeof(int) * CHAR_BIT - 1));
        is_positive = (result >= 0 ? 1 : 0);
        break;
    case PORTABLE:
        result = (v > 0) - (v < 0);
        is_positive = (result >= 0 ? 1 : 0);
        break;
    case NON_NEG:
        result = 1 ^ ((unsigned int)v >> (sizeof(int) * CHAR_BIT - 1));
        is_positive = (result ? 1 : 0);
        break;
    default:
        printf("ERROR, WILL ROBINSON, ERROR!!!\n");
        return -1;
        break;
    }
    printf("The sign of %d is %s\n", value, (is_positive ? "positive" : "negative"));

    return 0;
}

