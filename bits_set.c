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
#define NAIVE     0
#define LOOKUP    1
#define KERNIGHAN 2
#define SIZE      3
#define PARALLEL  4
#define MSB       5
#define BEST      6

static unsigned char BitsSetTable[256];
static const int S[] = {1, 2, 4, 8, 16};
static const int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};

static inline void generate_table(void)
{
    BitsSetTable[0] = 0;
    for (int i = 0; i < 256; i++)
        BitsSetTable[i] = (i & 1) + BitsSetTable[i / 2];
}

int
bits_set(void) 
{
    int value, v, result, method, pos;
    unsigned char *p;

    //generate the table used for LOOKUP algorithmically
    generate_table();

    printf("Which method should we use to count the number of bits set?  Here are your options:\n\n");
    printf("0. The naive way\n");
    printf("1. By a lookup table\n");
    printf("2. By Brian Kernighan's way\n");
    printf("3. Assuming different sized values (we'll assume only 32-bit values)\n");
    printf("4. In parallel\n");
    printf("5. From the most-significant bit up to a given position\n");
    printf("6. Supposedly, the best method\n");

    do {
        printf("Please type one of the ints in the option list above:\n");
        scanf("%d", &method);
    }while (method < NAIVE || method > BEST);

    if (method == MSB) {
        do {
            printf("Please pick a bit position:\n");
            scanf("%d", &pos);
        } while(pos < 0 || pos > 31);
    }

     //get input
    printf("Count the bits set in:\n");
    scanf("%d", &value);
    v = value;

    //count the bits set
    switch (method) {
    case NAIVE:
        for (result = 0; v; v >>= 1) result += v & 1;
        break;
    case LOOKUP:
        p = (unsigned char *) &v;
        result = BitsSetTable[p[0]] +
            BitsSetTable[p[1]] +
            BitsSetTable[p[2]] +
            BitsSetTable[p[3]];
        break;
    case KERNIGHAN:
        for (result = 0; v; result++) v &= v - 1;
            break;
    case SIZE:
        result = ((v & 0xfff) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
        result += (((v & 0xfff000) >> 12) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
        result += ((v >> 24) * 0x1001001001001ULL & 0x84210842108421ULL) % 0x1f;
        break;
    case PARALLEL:
        result = v - ((v >> 1) & B[0]);
        result = ((result >> S[1]) & B[1]) + (result & B[1]);
        result = ((result >> S[2]) + result) & B[2];
        result = ((result >> S[3]) + result) & B[3];
        result = ((result >> S[4]) + result) & B[4];
        break;
    case MSB:
        result = v >> (sizeof(v) * BITS_PER_BYTE - pos);
        result = result - ((result >> 1) & ~0UL/3);
        result = (result & ~0UL/5) + ((result >> 2) & ~0UL/5);
        result = (result + (result >> 4)) & ~0UL/17;
        result = (result * (~0UL/255)) >> ((sizeof(v) - 1) * BITS_PER_BYTE);
        break;
    case BEST:
        v = v - ((v >> 1) & 0x55555555);
        v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
        result = (((v + (v >> 4)) & 0xF0F0F0F0) * 0x1010101) >> 24;
        break;
    default: return 1; break;
    }
    
    printf("The number of bits set in %d is %d\n", value, result);

    return 0;
}
