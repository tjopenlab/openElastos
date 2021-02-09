//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strncmp.cpp:this program lexicographically compares, at most, the first count characters in string1 and string2
               and returns a value indicating the relationship between the substrings
 */

#include <stdio.h>
#include <string.h>

char string1[] = "The quick brown dog jumps over the lazy fox";
char string2[] = "The QUICK brown dog jumps over the lazy fox";

int main()
{
    char tmp[20];
    int result;

    printf("Compare strings:\n      %s\n      %s\n\n", string1, string2);
    printf("Function:   strncmp (first 10 characters only)\n");
    result = strncmp(string1, string2, 10);
    if (result > 0)
        strcpy(tmp, "greater than");
    else if (result < 0)
        strcpy(tmp, "less than");
    else
    strcpy(tmp, "equal to");
    printf("Result:      String 1 is %s string 2\n", tmp);

    return 0;
}


/*
Output

    Compare strings:
          The quick brown dog jumps over the lazy fox
          The QUICK brown dog jumps over the lazy fox

    Function:   strncmp (first 10 characters only)
    Result:      String 1 is greater than string 2
*/
