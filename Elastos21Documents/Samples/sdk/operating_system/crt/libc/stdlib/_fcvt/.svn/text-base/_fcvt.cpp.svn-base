//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _fcvt.cpp: This program converts the constant
 * 3.1415926535 whose type is double to a string .
*/

#include <stdlib.h>
#include <stdio.h>

int main()
{
    int  decimal, sign;
    char *buffer;
    double source = 3.1415926535;

    buffer = _fcvt(source, 7, &decimal, &sign);
    printf("source: %2.10f    buffer: '%s'    decimal: %d    sign: %d\n",
                source, buffer, decimal, sign);

    return 0;
}


/*
Output

    source: 3.1415926535    buffer: '31415927'    decimal: 1    sign: 0
*/
