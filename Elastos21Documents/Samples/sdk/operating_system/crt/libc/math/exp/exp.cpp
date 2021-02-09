//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* exp.cpp: This program uses exp returns the exponential value of x */

#include <math.h>
#include <stdio.h>

int main()
{
    double x = 2.302585093, y;

    y = exp(x);
    printf("exp(%f) = %f\n", x, y);

    return 0;
}


/*
Output

    exp(2.302585) = 10.000000
*/
