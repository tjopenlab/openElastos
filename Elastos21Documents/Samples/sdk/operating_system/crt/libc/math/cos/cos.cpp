//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* cos.cpp: This program uses cos to calculates the cosine (cos).
 */

#include <math.h>
#include <stdio.h>

int main()
{
    double pi = 3.1415926535;
    double x, y;

    x = pi / 2;
    y = cos(x);
    printf("cos(%f) = %f\n", x, y);

    return 0;
}

/*
Output

    Tcos(1.570796) = 0.000000

*/
