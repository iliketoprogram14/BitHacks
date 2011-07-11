/*****************************************************************************
* swap.c
* 
* Randy Miller
*
* Swaps two values through a few different methods
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
#define NORMAL 0
#define XOR        1
#define XOR_ON_BITS   2 //same as XOR method, but swaps individual bits

static inline unsigned int absvalue (int v) {
    int const mask = v >> (sizeof(int) * BITS_PER_BYTE - 1);

    return (unsigned int) (v + mask) ^ mask;
}

int
swap(void)
{
    int method, first, second, tmp;
    int value; //value for bits to be swapped in (XOR_ON_BITS only)
    unsigned int num_consec_bits, result; //XOR_ON_BITS only

    //get input
    printf("Which method should we use to swap two integers?  Here are your options:\n\n0. Using Subtraction and Addition\n1. Using XOR\n2. Using XOR on individual bits (swapping individual bits)\n");

    do {
        printf("Please type one of the ints in the option list above:\n");
        scanf("%d", &method);
    }while (method < NORMAL || method > XOR_ON_BITS);

    //get input
    printf("What's the %s?\n",
           (method == XOR_ON_BITS ? "position of the first bit to be swapped":
            "first value to be swapped"));
    scanf("%d", &first);
    printf("What's the %s?\n",
           (method == XOR_ON_BITS ? "position of the second bit to be swapped":
            "second value to be swapped"));
    scanf("%d", &second);

    switch(method) {
    case NORMAL:
        tmp = first;
        first = second;
        second = tmp;
        break;
    case XOR:
        //Note: this fails when aliasing occurs or both are in same location
        first ^= second;
        second ^= first;
        first ^= second;
        break;
    case XOR_ON_BITS:
        //get more input
        printf("What's the value whose bits you would like to swap?\n");
        scanf("%d", &value);

        //position and value must be unsigned
        first = absvalue(first); second = absvalue(second);
        value = absvalue(value);
        num_consec_bits = absvalue(second - first);

        //do it!
        tmp = ((value >> first) ^ (value >> second)) &
            ((1U << num_consec_bits) -1);
        result = value ^ ((tmp << first) | (tmp << second));
        printf("The value after the swap of bits is %d\n", result);
        return 0;
        break;
    default:
        printf("ERROR, WILL ROBINSON, ERROR!!!\n");
        return 1;
    }
    printf("The first value is now %d, and the second value is now %d.\n",
           first, second);

    return 0;
}

