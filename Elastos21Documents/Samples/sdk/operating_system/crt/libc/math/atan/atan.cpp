//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* atan.cpp: This program uses atan to calculates the arctangent.
 */

#include <math.h>
#include <stdio.h>

int main()
{
    double x, y;

    x = -862.4200;
    y = atan(x);
    printf("Arctangent of %f: %f\n", x, y);

    return 0;
}


/*
Output

    Arctangent of -862.420000: -1.569637
*/
