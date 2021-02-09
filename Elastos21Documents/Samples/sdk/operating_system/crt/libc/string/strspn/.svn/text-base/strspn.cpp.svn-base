//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strspn.cpp: This program uses strspn to determine
 * the length of the segment in the string "cabbage"
 * consisting of a's, b's, and c's. In other words,
 * it finds the first non-abc letter.
 */

#include <string.h>
#include <stdio.h>

int main()
{
    char string[] = "cabbage";
    int  result;
    result = strspn(string, "abc");
    printf("The portion of '%s' containing only a, b, or c "
           "is %d bytes long\n", string, result);
    return 0;
}

//==========================================================================
//Output
//
//    The portion of 'cabbage' containing only a, b, or c is 5 bytes long
//==========================================================================
