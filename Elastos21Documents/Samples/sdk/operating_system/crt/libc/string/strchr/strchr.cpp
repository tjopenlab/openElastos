//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* strchr.cpp: This program reads characters from
* 本程序在字符串中查找字符 'r'。
 */

#include <string.h>
#include <stdio.h>

char ch = 'r';
char string[] = "The quick brown dog jumps over the lazy fox";
char fmt1[] = "         1         2         3         4         5";
char fmt2[] = "12345678901234567890123456789012345678901234567890";

int main()
{
    char *pdest;
    int result;
    printf("String to be searched:\n\t\t%s\n", string);
    printf("\t\t%s\n\t\t%s\n\n", fmt1, fmt2);

    printf("Search wchar_t:\t%c\n", ch);
    pdest = strchr(string, ch);
    result = pdest - string + 1;
    if (pdest != NULL)
        printf("Result:\t\tfirst %c found at position %d\n\n", ch, result);
    else
        printf("Result:\t\t%c not found\n", ch);

    return 0;
}

/*
Output

    String to be searched:
                    The quick brown dog jumps over the lazy fox
                             1         2         3         4         5
                    12345678901234567890123456789012345678901234567890

    Search wchar_t: r
    Result:         first r found at position 12

*/
