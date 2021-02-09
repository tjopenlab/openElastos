//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* rand.cpp: This program seeds the random-number generator
 * with the time, then displays 10 random integers.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
    int i;

    /* Seed the random-number generator with current time so that
     * the numbers will be different every time we run.
     */
    srand((unsigned)time(NULL));

    /* Display 10 numbers. */
    for (i = 0;    i < 10;i++)
        printf("  %6d\n", rand());

    return 0;
}

/*
Output

       17893
        5049
       11778
       14295
        3256
        9799
        2405
        9964
       12710
       27842
*/
