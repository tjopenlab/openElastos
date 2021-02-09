//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _isnan.cpp: This program uses _finite function to check
 * x is Nan.
 */

#include <float.h>
#include <stdio.h>

int main()
{
    double x = 242.55;

    printf("For x, is %s\n", _isnan(x) ? "NaN" : "not NaN");

    return 0;
}

/*
Output

    For x, is not NaN
*/
