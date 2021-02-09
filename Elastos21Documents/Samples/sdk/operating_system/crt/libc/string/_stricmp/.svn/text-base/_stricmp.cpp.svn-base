//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _stricmp.cpp:this program compares lowercase versions of str1 and str2
                and returns a value indicating their relationship
 */

#include <stdio.h>
#include <string.h>

int main()
{
    int isMatch;
    char str1[20] = "Hello";
    char str2[20] = "hello";
    isMatch = _stricmp(str1, str2);

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

    str1: Hello = str2: hello
*/
