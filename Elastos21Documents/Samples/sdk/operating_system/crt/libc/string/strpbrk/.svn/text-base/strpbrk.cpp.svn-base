//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strpbrk.cpp:this program returns a pointer to the first occurrence of a character in string
               that belongs to the set of characters in strCharSet
 */

#include <string.h>
#include <stdio.h>

int main()
{
    char string[100] = "The 3 men and 2 boys ate 5 pigs\n";
    char *result;
    /* Return pointer to first 'a' or 'b' in "string" */
    printf("1: %s\n", string);
    result = strpbrk(string, "0123456789");
    printf("2: %s\n", result++);
    result = strpbrk(result, "0123456789");
    printf("3: %s\n", result++);
    result = strpbrk(result, "0123456789");
    printf("4: %s\n", result);

    return 0;
}


//==========================================================================
//Output
//
//    1: The 3 men and 2 boys ate 5 pigs
//
//    2: 3 men and 2 boys ate 5 pigs
//
//    3: 2 boys ate 5 pigs
//
//    4: 5 pigs
//==========================================================================
