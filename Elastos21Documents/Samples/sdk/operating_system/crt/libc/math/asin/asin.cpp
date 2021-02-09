//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* asin.cpp: This program uses asin to calculates the arcsine.
 */

#include <math.h>
#include <stdio.h>

int main()
{
    double x = 0.32696, y;

    y = asin(x);
    printf("Arcsine of %f = %f\n", x, y);

    return 0;
}

/*
Output

    Arcsine of 0.326960 = 0.333085
*/
