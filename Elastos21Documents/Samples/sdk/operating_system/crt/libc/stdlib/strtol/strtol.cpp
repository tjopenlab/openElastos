//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strtol.cpp: This program uses strtol to
 * convert a string to long integer values.
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    char    *string, *stopstring;
    long    l;

    string = "-10110134932This stopped it";
    l = strtol(string, &stopstring, 10);
    printf("string = %s\n", string);
    printf("    strtol = %ld\n", l);
    printf("    Stopped scan at: %s\n", stopstring);

    return 0;
}


/*
Output

    string = -10110134932This stopped it
        strtol = -2147483648
        Stopped scan at: This stopped it
*/
