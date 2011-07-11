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
#define ZERO      0
#define EQN       1
#define LTN       2
#define GTN       3
#define BWMN      4

static inline int has_zero(int v)
{
    return (v - 0x01010101UL) & ~v & 0x80808080UL;
}

int
test_range(void)
{
    int value, v, result, method, value2, n, tmp, value3, m;

    //get method
    printf("Determine if a byte has which of the following properties?  Here are your options:\n\n");
    printf("0. A zero byte\n");
    printf("1. A byte equal to n\n");
    printf("2. A byte less than n\n");
    printf("3. A byte greater than n\n");
    printf("4. A byte between m and n\n");

    do {
        printf("Please type one of the ints in the option list above:\n");
        scanf("%d", &method);
    }while (method < ZERO || method > BWMN);

     //get input
    printf("What's the word?  It must be positive:");
    scanf("%d", &value);
    v = value;

    if (method == BWMN) {
        do {
            printf("Which byte should be the lower bound?\n");
            scanf("%d", &value3);
        } while(value2 < 0 || value2 > 127);
        m = value2;
    }
    
    if (method == !ZERO) {
        do {
            if (method == BWMN)
                printf("Which byte should be the upper bound?\n");
            else
                printf("Which byte should we compare against the word?");
            scanf("%d", &value2);
        } while(method == LTN && (value2 < 0 || value2 > 127));
        n = value2;
    }

    //Test the range
    switch (method) {
    case ZERO:
        result = has_zero(v);
        printf("%d %s a zero byte\n", value, (result ? "has" : "doesn't have"));
        break;
    case EQN:
        tmp = has_zero(v);
        result = tmp ^ (~0UL/255 * n);
        printf("%d %s a byte equal to %d\n", value,
               (result ? "has" : "doesn't have"), value2);
        break;
    case LTN:
        result = (v - ~0UL/255 * n) & ~0UL/255 * 128;
        printf("%d %s a byte less than %d\n", value,
               (result ? "has" : "doesn't have"), value2);        
        break;
    case GTN:
        result = ((v + ~0UL/255 * (127 - n)) | v) & ~0UL/255 * 128;
        printf("%d %s a byte greater than %d\n", value,
               (result ? "has" : "doesn't have"), value2);
        break;
    case BWMN:
        result = (((v - ~0UL/255 * n) & ~v & (v & ~0UL/255 * 127)) +
                  ~0UL/255 * (127 - m)) & ~0UL/255 * 128;
        printf("%d %s a byte between %d and %d\n", value,
               (result ? "has" : "doesn't have"), value2, value3);
        break;
    default: return 1; break;
    }
    
    return 0;
}
