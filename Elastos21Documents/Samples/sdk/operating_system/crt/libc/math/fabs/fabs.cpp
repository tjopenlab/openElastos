//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fabs.cpp: This program uses fabs to
 * calculates the absolute value of the floating-point argument.
 */

#include  <stdio.h>
#include  <math.h>

int main()
{
    double x, y;

    x = -3.14159;
    y = fabs(x);
    printf("The absolute value of %f is %f\n", x, y);

    return 0;
}

/*
Output

    The absolute value of -3.141590 is 3.141590
*/
