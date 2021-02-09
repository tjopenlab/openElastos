//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//strstr.cpp:this program returns a pointer to the first occurrence of strCharSet in string
 


#include <string.h>
#include <stdio.h>

char str[] =    "lazy";
char string[] = "The quick brown dog jumps over the lazy fox";
char fmt1[] =   "         1         2         3         4         5";
char fmt2[] =   "12345678901234567890123456789012345678901234567890";

int main()
{
    char *pdest;
    int  result;
    printf("String to be searched:\n\t%s\n", string);
    printf("\t%s\n\t%s\n\n", fmt1, fmt2);
    pdest = strstr(string, str);
    result = pdest - string + 1;
    if (pdest != NULL)
        printf("%s found at position %d\n\n", str, result);
    else
        printf("%s not found\n", str);

    return 0;
}

//==========================================================================
//Output:Output
//
//    String to be searched:
//           The quick brown dog jumps over the lazy fox
//                     1         2         3         4         5
//            12345678901234567890123456789012345678901234567890
//
//    lazy found at position 36
//==========================================================================
