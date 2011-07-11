/*****************************************************************************
* binary_search.c
* 
* Randy Miller
*
* special binary search.  Looks for first entry that is >= TARGET
*****************************************************************************/

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_BYTE 8
#define TARGET 22

int
binary_search(void)
{
    int low = 0;
    int high, middle;//, i;

    int a[3] = {13, 19, 21};
    high = sizeof(a)/sizeof(int) - 1;

    printf("high: %d\n", high);

    if (high < 0) {
        printf("array is empty\n");
        return 1;
    }

    if (high == low && a[high] < TARGET) {
        printf("one element is too low: %d\n", a[high]);
        return 2;
    }

    if (a[low] >= TARGET) {
        printf("result = %d; index = %d\n", a[low], low);
        return 0;
    }
    
    while (low <= high) {
        middle = low + (high - low)/2;
        if (TARGET < a[middle]) {
            if (middle > 0 && TARGET > a[middle - 1]) {
                printf("result = %d; index = %d\n", a[middle], middle);
                return 0;
            }
            high = middle - 1;
        }
        else if (TARGET > a[middle])
            low = middle + 1;
        else {
            printf("result = %d; index = %d\n", a[middle], middle);
            return 0;
        }
    }

    printf("fail\n");
    return -1;
}
