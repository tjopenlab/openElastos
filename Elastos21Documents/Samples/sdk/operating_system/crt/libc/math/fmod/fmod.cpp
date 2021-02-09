//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fmod.cpp: This program displays a
 * floating-point remainder.
 */

#include <math.h>
#include <stdio.h>

int main()
{
    double w = -10.0, x = 3.0, y = 0.0, z;

    z = fmod(w, x);
    printf("The remainder of %.2f / %.2f is %f\n", w, x, z);
    z = fmod(x, y);
    printf("The remainder of %.2f / %.2f is %f\n", x, y, z);

    return 0;
}

/*
Output

    The remainder of -10.00 / 3.00 is -1.000000
    The remainder of 3.00 / 0.00 is NaN
*/
