/*****************************************************************************
* main.c
* 
* Randy Miller
*
* Control flow distributor
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_BYTE 8

static void print_bithacks(void)
{
    printf("1. Compute the absolute value\n");
    printf("2. Binary search\n");
    printf("3. Find the highest power of 2 of a number\n");
    printf("4. Compute the log base 10 of a number\n");
    printf("5. Compute the log base 2 of a number\n");
    printf("6. Compute the min or max of two numbers\n");
    printf("7. Negate a number\n");
    printf("8. See if two numbers have opposite signs\n");
    printf("9. Compute the parity\n");
    printf("10. Determine if a number is a power of 2\n");
    printf("11. Set or clear some bits\n");
    printf("12. Determine a sign of a number\n");
    printf("13. Swap two numbers\n");
    printf("0. Reprint the bit hacks\n");
    printf("-1. Quit out of the program\n");
    
    return; 
}

int
main(int argc, char *argv[]) {

    int method, exit;

    exit = 0;

    printf("Welcome to the bit hacks hub.  Please pick from one of the following options:\n");
    do {
        print_bithacks();
        scanf("%d", &method);
        
        switch(method) {
        case ABS: abs(); break;
        case BIN_SEARCH: binary_search(); break;
        case HIGHPOW2: highest_pow2(); break;
        case LOG10: log10(); break;
        case LOG2: log2(); break;
        case MINMAX: minmax(); break;
        case NEGATE: negate(); break;
        case OPP_SIGNS: opp(); break;
        case PARITY: parity(); break;
        case POW2: pow2(); break;
        case SETCLEAR: setclear(); break;
        case SIGN: sign(); break;
        case SWAP: swap(); break;
        case REPRINT: print_bithacks(); break;
        case QUIT: exit = 1; break;
        default: exit = 1; break;
        }
    } while(!exit);
    
    return 0;
}
