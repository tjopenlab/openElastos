//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* srand.cpp: This program seeds the random-number generator
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

       13018
       27308
        3986
       10484
        4469
       11688
       21712
         241
        2406
        1993
*/
