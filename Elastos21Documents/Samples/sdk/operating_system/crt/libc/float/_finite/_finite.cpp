//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _finite.cpp: This program uses _finite function to verify
 * x is finite.
 */

#include <float.h>
#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

int main()
{
    double x;
    Boolean TF;

    x = -14.87654321;
    if (_finite(x))
        TF = TRUE;
    else
        TF = FALSE;
    printf("For this x, is %s\n", TF ? "finite" : "infinite");

    return 0;
}


/*
Output

    For this x, is finite
*/
