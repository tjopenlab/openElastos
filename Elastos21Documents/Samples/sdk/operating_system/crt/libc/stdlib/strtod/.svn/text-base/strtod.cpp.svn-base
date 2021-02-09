//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strtod.cpp: This program uses strtod to convert a
 * string to a double-precision value.
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    char    *string, *stopstring;
    double x;

    string = "3.1415926This stopped it";
    x = strtod(string, &stopstring);
    printf("string = %s\n", string);
    printf("    strtod = %f\n", x);
    printf("    Stopped scan at: %s\n\n", stopstring);

    return 0;
}


/*
Output

     string = 3.1415926This stopped it
         strtod = 3.141593
         Stopped scan at: This stopped it
*/
