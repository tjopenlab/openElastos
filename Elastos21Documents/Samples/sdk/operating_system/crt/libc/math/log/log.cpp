//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* log.cpp: This program uses log
 * to calculate the natural logarithm of 9,000.
 */

#include <math.h>
#include <stdio.h>

int main()
{
    double x = 9000.0;
    double y;

    y = log(x);
    printf("log(%.2f) = %f\n", x, y);

    return 0;
}


/*
Output

    log(9000.00) = 9.104980
*/
