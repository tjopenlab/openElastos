//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* sin.cpp: This program uses cos to calculates the sines.
 */

#include <math.h>
#include <stdio.h>

int main()
{
    double pi = 3.1415926535;
    double x, y;

    x = pi / 2;
    y = sin(x);
    printf("sin(%f) = %f\n", x, y);

    return 0;
}


/*
Output

    sin(1.570796) = 1.000000
*/
