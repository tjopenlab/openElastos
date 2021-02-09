//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strtoul.cpp: This program uses strtoul
 * to convert a string to unsigned long-integer values.
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    char    *string, *stopstring;
    int     base;
    unsigned long ul;

    string = "10110134932";
    printf("string = %s\n", string);
    /* Convert string using base 2, 4, and 8: */
    for (base = 2; base <= 8; base *= 2) {
        /* Convert the string: */
        ul = strtoul(string, &stopstring, base);
        printf("    strtol = %ld (base %d)\n", ul, base);
        printf("    Stopped scan at: %s\n", stopstring);
    }

    return 0;
}


/*
Output

    string = 10110134932
        strtol = 45 (base 2)
        Stopped scan at: 34932
        strtol = 4423 (base 4)
        Stopped scan at: 4932
        strtol = 2134108 (base 8)
        Stopped scan at: 932
*/
