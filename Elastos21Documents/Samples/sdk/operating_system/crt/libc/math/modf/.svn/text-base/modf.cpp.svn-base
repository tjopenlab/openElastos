//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* modf.cpp:This program uses modf to calculate the signed fractional portion */

#include <math.h>
#include <stdio.h>

int main()
{
    double x, y, n;

    x = -14.87654321;      /* Divide x into its fractional */
    y = modf(x, &n);     /* and integer parts            */

    printf("For %f, the fraction is %f and the integer is %.f\n",
           x, y, n);

    return 0;
}

/*
Output

    For -14.876543, the fraction is -0.876543 and the integer is -14
*/
