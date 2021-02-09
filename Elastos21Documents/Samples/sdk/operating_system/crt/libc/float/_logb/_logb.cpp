//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _logb.cpp: This program extracts exponential value of f1.
 */

#include <stdio.h>
#include <float.h>
#include <math.h>

int main()
{
    double f, f1;

    f1 = 16.00;
    f = _logb(f1);
    printf("_logb(%f) = %f\n", f1, f);

    return 0;
}

/*
Output

    _logb(16.000000) = 4.000000
*/
