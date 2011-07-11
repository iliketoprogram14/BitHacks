/*****************************************************************************
* parity.c
* 
* Randy Miller
*
* Checks if a given integer is true or false
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARCH_IS_64 0
#define BITS_PER_BYTE (ARCH_IS_64 ? 16 : 8)
#define ARCH_NUM_BITS (ARCH_IS_64 ? 64 : 32)
//different types of methods for computing parity
#define NAIVE      0
#define LOOKUP     1
#define MULT       2
#define PARALLEL   3

static const int ParityTable256[256] = {
#define P2(n) n, n^1, n^1, n
#define P4(n) P2(n), P2(n^1), P2(n^1), P2(n)
#define P6(n) P4(n), P4(n^1), P4(n^1), P4(n)
    P6(0), P6(1), P6(1), P6(0)
};

static inline unsigned int absvalue (int v) {
    int const mask = v >> (sizeof(int) * BITS_PER_BYTE - 1);

    return (unsigned int) (v + mask) ^ mask;
}

int
parity(void)
{
    int method, value, tmp, parity;
    int mask, last_shift; //for MULT
    
     //get input
    printf("Which method should we use to compute the parity of an integer?  Here are your options:\n\n0. Naively\n1. Using a lookup table\n2. Using a multiplication\n3. In parallel\n");


    do {
        printf("Please type one of the ints in the option list above:\n");
        scanf("%d", &method);
    }while (method < NAIVE && method > PARALLEL);

    printf("What's the value to operate on?\n");
    scanf("%d", &value);
    tmp = abs(value);

    switch(method) {
    case NAIVE:
        while (tmp) {
            parity = !parity;
            tmp = tmp & (tmp - 1);
        }
        break;
    //uses lookup table defined above
    case LOOKUP:
        //for 32-bit words
        tmp ^= tmp >> 16;
        tmp ^= tmp >> 8;
        parity = !(ParityTable256[tmp & 0xff]); //adjust parity for printf
        break;
    //always takes 8 operations
    case MULT:
        mask = (ARCH_IS_64 ? 0x11111111111111UL : 0x1111111U);
        last_shift = ARCH_NUM_BITS - 4;
        tmp ^= tmp >> 1;
        tmp ^= tmp >> 2;
        tmp = (tmp & mask) * mask;
        parity = (tmp >> last_shift) & 1;
        break;
    //takes 9 operations for 32 bit words
    case PARALLEL:
        tmp ^= tmp >> 16;
        tmp ^= tmp >> 8;
        tmp ^= tmp >> 4;
        tmp &= 0xf;
        //0x6996 is like a 16-bit parity table indexed by the low 4 bits of tmp
        parity = !((0x6996 >> tmp) & 1); //adjust parity for printf
        break;
    default:
        printf("ERROR, WILL ROBINSON, ERROR!!!\n");
        return 1;
    }
    
    printf("Your value is %s.\n", (parity ? "even" : "odd"));

    return 0;
}

