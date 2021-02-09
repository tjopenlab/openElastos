//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* ceil.cpp: This example shows the smallest integers greater
 * than or equal to 2.8 and -2.8.
 */

#include <math.h>
#include <stdio.h>

int main()
{
    double y;

    y = ceil(2.8);
    printf("The ceil of 2.8 is %f\n", y);
    y = ceil(-2.8);
    printf("The ceil of -2.8 is %f\n", y);

    return 0;
}


/*
Output
    The ceil of 2.8 is 3.000000
    The ceil of -2.8 is -2.000000
*/
