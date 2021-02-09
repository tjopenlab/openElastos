//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strncat.cpp:this program use strncat to appends, at most, the first count characters of suffix to string
 */

#include <string.h>
#include <stdio.h>

int main()
{
    char string[80] = "This is the initial string!";
    char suffix[] = " extra text to add to the string...";
    /* Combine strings with no more than 19 characters of suffix: */
    printf("Before: %s\n", string);
    strncat(string, suffix, 19);
    printf("After:  %s\n", string);

    return 0;
}

/*
Output

    Before: This is the initial string!
    After:  This is the initial string! extra text to add
*/
