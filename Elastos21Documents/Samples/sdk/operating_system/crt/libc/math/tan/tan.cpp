//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* tan.cpp: This program displays the tangent of pi / 4
 * of the result.
 */


#include <math.h>
#include <stdio.h>

int main()
{
    double pi = 3.1415926535;
    double x;

    x = tan(pi / 4);
    printf("tan(pi/4) = %f\n", x);

    return 0;
}

/*
Output

    tan(pi/4) = 1.000000
*/
