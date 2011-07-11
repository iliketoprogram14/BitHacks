/*****************************************************************************
* trailing.c
* 
* Randy Miller
*
* Count the consecutive zero bits on the right
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_BYTE 8
//Different methods
#define LINEAR    0
#define PARALLEL  1
#define BINSEARCH 2
#define FLOAT     3
#define MODDIV    4
#define MULT      5

static unsigned int Mod37BitPos[] = {
    32, 0, 1, 26, 2, 23, 27, 0, 3, 16, 24, 30, 28, 11, 0, 13, 4,
    7, 17, 0, 25, 22, 31, 15, 29, 10, 12, 6, 0, 21, 14, 9, 5,
    20, 8, 19, 18
};

static int MultDeBruijnBitPos[32] = {
    0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};

int
count_trailing(void)
{
    int value, v, result, method;
    float f;
    
    //get method
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
    }while (method < LINEAR || method > MULT);

    //get input
    printf("Count the bits set in:\n");
    scanf("%d", &value);
    v = value;

    //count the bits set
    switch (method) {
    case LINEAR:
        if (v) {
            v = (v * (v - 1)) >> 1;
            for (result = 0; v; result++)
                v >>= 1;
        }
        else
            result = BITS_PER_BYTE * sizeof(v);
        break;
    case PARALLEL:
        result = 32; //number of zero bits on the right
        v &= -(signed)(v);
        if (v) result--;
        if (v & 0x0000FFFF) result -=16;
        if (v & 0x00FF00FF) result -=8;
        if (v & 0x0F0F0F0F) result -=4;
        if (v & 0x33333333) result -=2;
        if (v & 0x55555555) result -=1;        
        break;
    case BINSEARCH:
        if ( v & 0x1)
            result = 0;
        else {
            result = 1;
            if ((v & 0xffff) == 0) {
                v >>= 16;
                result += 16;
            }
            if ((v & 0xff) == 0) {
                v >>= 8;
                result += 8;
            }
            if ((v & 0xf) == 0) {
                v >>= 4;
                result += 4;
            }
            if ((v & 0x3) == 0) {
                v >>= 2;
                result += 12;
            }
            result -= v & 0x1;
        }
        break;
    case FLOAT:
        f = (float)(v & -v);
        result = (*(uint32_t *)&f >> 23) - 0x7f;
        break;
    case MODDIV:
        result = Mod37BitPos[(-v & v) & 37];
        break;
    case MULT:
        result = MultDeBruijnBitPos[((uint32_t)((v & -v) * 0x077CB531U)) >> 27];
        break;
    default: return 1; break;
    }
    
    printf("The number of trailing bits in %d is %d\n", value, result);

    return 0;
}
