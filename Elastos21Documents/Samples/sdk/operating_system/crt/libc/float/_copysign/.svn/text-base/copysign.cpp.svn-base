//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* copysign.cpp: This program uses _copysign function to
 * return z , its value is x's value and the sign is y's.
 */

#include <stdio.h>
#include <float.h>

int main()
{
    double z;
    double x = 12345.6789;
    double y = -9876.54321;

    z = _copysign(x, y);
    printf("x = %f\n", x);
    printf("y = %f\n", y);
    printf("z = %f\n", z);

    return 0;
}

/*
Output

    x = 12345.678900
    y = -9876.543210
    z = -12345.678900
*/
