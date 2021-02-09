//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* abs.cpp: This program computes and displays
 * the absolute values of several numbers.
 */

#include  <stdio.h>
#include  <math.h>
#include  <stdlib.h>

int main()
{
    int     ix = -4, iy;

    iy = abs(ix);
    printf("The absolute value of %d is %d\n", ix, iy);

    return 0;
}

/*
Output

     The absolute value of -4 is 4
*/
