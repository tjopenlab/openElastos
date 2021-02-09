//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//strrchr.cpp: This program reads characters from
//本程序查找字符 'r' 在字符串中最后出现的位置。
//

#include <string.h>
#include <stdio.h>

int  ch = 'r';
char string[] = "The quick brown dog jumps over the lazy fox";
char fmt1[] = "         1         2         3         4         5";
char fmt2[] = "12345678901234567890123456789012345678901234567890";

int main()
{
    char *pdest;
    int result;
    printf("String to be searched:\n\t\t%s\n", string);
    printf("\t\t%s\n\t\t%s\n\n", fmt1, fmt2);

    printf("Search char:\t%c\n", ch);
    pdest = strrchr(string, ch);
    result = pdest - string + 1;
    if (pdest != NULL)
        printf("Result:\tlast %c found at position %d\n\n", ch, result);
    else
        printf("Result:\t%c not found\n",ch);

    return 0;
}

//==========================================================================
//Output
//
//    String to be searched:
//                    The quick brown dog jumps over the lazy fox
//                             1         2         3         4         5
//                    12345678901234567890123456789012345678901234567890
//
//    Search char:    r
//    Result: last r found at position 30
//==========================================================================
