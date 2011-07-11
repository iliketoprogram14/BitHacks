/*****************************************************************************
* rev_seq.c
* 
* Randy Miller
*
* Reverse bit sequences
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_BYTE 8
//Different methods
#define NAIVE     0
#define LOOKUP    1
#define THREEOPS  2
#define FOUROPS   3
#define SEVOPS    4
#define PARALLEL  5

static unsigned char BitRevTable[256] = {
#define R2(n)    n, n + 2*64, n + 64, n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4), R4(n + 4), R4(n + 3*4)
        R6(0), R6(2), R6(1), R6(3)
};

static const int S[] = {1, 2, 4, 8, 16};
static const int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};

int
reverse_sequence(void)
{
    int value, v, result, method, shift, mask;
    unsigned char b, r;

    printf("Which method should we use to count the number of bits set?  Here are your options:\n\n");
    printf("0. The naive way\n");
    printf("1. By a lookup table\n");
    printf("2. In three operations (for a byte-sized value)\n");
    printf("3. In four operations (for a byte-sized value)\n");
    printf("4. In seven operations (for a byte-sized value)\n");
    printf("5. In parallel\n");

    do {
        printf("Please type one of the ints in the option list above:\n");
        scanf("%d", &method);
    }while (method < NAIVE || method > PARALLEL);

    if (method >= THREEOPS && method <= SEVOPS) {
        do {
            printf("Please choose a value less than 255\n");
            b = getchar();
        } while('b' > 255);
        r = b;
    }
    else {
        printf("Reverse the bits in:\n");
        scanf("%d", &value);
        v = value;
    }

    //Reverse the bits
    switch (method) {
    case NAIVE:
        shift = sizeof(v) * BITS_PER_BYTE - 1;
        result = v;
        for (v >>= 1; v; v >>= 1) {
            result <<= 1;
            result |= v & 1;
            shift--;
        }
        result <<= shift;
        break;
    case LOOKUP:
        result = (BitRevTable[v & 0xff] << 24) |
            (BitRevTable[(v >> 8) & 0xff] << 16) |
            (BitRevTable[(v >> 16) & 0xff] << 8) |
            (BitRevTable[(v >> 24) & 0xff]);
        break;
    case THREEOPS:
        r = (b * 0x0202020202UL & 0x010884422010ULL) & 1023;
        break;
    case FOUROPS:
        r = ((b * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
        break;
    case SEVOPS:
        r = ((b * 0x0802LU & 0x22110LU) | (b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
        break;
    case PARALLEL:
        shift = sizeof(v) * BITS_PER_BYTE;
        mask = ~0;
        while ((shift >>= 1) > 0) {
            mask ^= (mask << shift);
            v = ((v >> shift) & mask) | ((v << shift) & ~mask);
        }
        result = v;
        break;
    default: return 1; break;
    }
    if (method >= THREEOPS && method <= SEVOPS)
        printf("The result of reversing bits in %c is %c\n", b, r);
    else
        printf("The result of reversing bits in %d is %d\n", value, result);

    return 0;
}
