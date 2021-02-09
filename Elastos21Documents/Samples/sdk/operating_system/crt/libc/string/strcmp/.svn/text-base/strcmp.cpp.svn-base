//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strcmp.cpp:this program compares string1 and string2 lexicographically
          and returns a value indicating their relationship
 */

#include <stdio.h>
#include <string.h>

int main()
{
    int isMatch;
    char str1[10] = "Hello";
    char str2[10] = "hello";

    isMatch = strcmp(str1, str2);

    if (isMatch == 0) {
        printf("str1: %s = str2: %s \n", str1, str2);
    }
    else if (isMatch > 0) {
        printf("str1: %s > str2: %s \n", str1, str2);
    }
    else if (isMatch < 0) {
        printf("str1: %s < str2: %s \n", str1, str2);
    }

    return 0;
}

/*
Output

    str1: Hello < str2: hello
*/
