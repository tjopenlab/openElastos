//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _ecvt.cpp: This program uses _ecvt to convert a
 * floating-point number to a character string.
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    int      decimal,    sign;
    char     *buffer;
    int      precision = 10;
    double  source = 3.1415926535;

    buffer = _ecvt(source, precision, &decimal, &sign);
    printf("source: %2.10f    buffer: '%s'  decimal: %d  sign: %d\n",
              source, buffer, decimal, sign);

    return 0;
}


/*
Output

    source: 3.1415926535    buffer: '3141592654'  decimal: 1    sign: 0
*/
