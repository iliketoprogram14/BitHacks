/*****************************************************************************
* log2.c
* 
* Randy Miller
*
* Finds the log (base 2) of some integer
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARCH_IS_64 0
#define BITS_PER_BYTE (ARCH_IS_64 ? 16 : 8)
#define ARCH_NUM_BITS (ARCH_IS_64 ? 64 : 32)
//different types of methods for computing log base 2
#define OBVIOUS  0 
#define LOOKUP   1
#define LOGN     2
#define LOGN2    3
#define OF_FLOAT 4

//Lookup table for LOOKUP
static char LogTable[256] = {
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
    -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
    LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
};

//Lookup table for LOGN2
static const int LogTable2[32] = {
    0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
    8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
};


int
log2(void)
{
    int method, value, result, v;
    int tmp, tmp2; //for LOOKUP
    float vf; //for OF_FLOAT
    int b[5] = { 0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000 }; //for LOGN2
    int S[5] = { 1, 2, 4, 8, 12 }; //for LOGN2

    result = 0;
    
    //get method
    printf("Which method should we use to compute the integer value of the log (base 2) of some value?  Here are your options:\n\n0. The obvious way (O(n))\n1. Using a lookup table\n2. Find the log base 2 of an n-bit int in O(logn)\n3. Find the log base 2 of an n-bit int in O(logn) with multiply and lookup\n4. Find the log base 2 of a float\n\n");

    do {
        printf("Please type one of the ints in the option list above:\n");
        scanf("%d", &method);
    } while (method < OBVIOUS && method > OF_FLOAT);
 
   //get input
    printf("What's the value to operate on?  ");
    do {
        printf("Please select a value greater than 0\n");
        if (method == OF_FLOAT)
            scanf("%f", &vf);
        else
            scanf("%d", &value);
    } while (value <=0);
    v = value;

    switch(method) {
    case OBVIOUS: while (v >>= 1) result++; break;
    case LOOKUP:
        //make log table algorithmically
        LogTable[0] = 0;
        LogTable[1] = 0;
        for (int i = 2; i < 256; i++)
            LogTable[i] = 1 + LogTable[i/2];

        tmp2 = value >> 16;
        if (tmp2) {
            tmp = tmp2 >> 8;
            result = tmp ? 24 + LogTable[tmp] : 16 + LogTable[tmp2];
        }
        else {
            tmp = v >> 8;
            result = tmp ? LogTable[tmp] : LogTable[value];
        }
        break;
    //this is actually pretty slow
    case LOGN:
        for (int i = 4; i >= 0; i--) {
            if (v & b[i]) {
                v >>= S[i];
                result |= S[i];
            }
        }
        break;
    case LOGN2:
        v |= v >> 1; //first round down to 1 less than a power of 2
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        result = LogTable2[(v * 0x07C4ACDDU) >> 27];
        break;
    case OF_FLOAT:
        result = * (const int *) &vf;
        result = (result >> 23) - 127;
        printf("Log base 2 of %f is %d\n", vf, result);
        return 0;
        break;
    default:
        printf("ERROR, WILL ROBINSON, ERROR!!!\n");
        return 1;
    }

    printf("Log base 2 of %d is %d\n", value, result);


    return 0;
}

