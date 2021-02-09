//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* memmove.cpp:this program use memmoe to copies count bytes of characters from src to dest
 */

#include <stdio.h>
#include <string.h>

char string1[60] = "The quick brown dog jumps over the lazy fox";
/*                           1         2         3         4         5
 *                  12345678901234567890123456789012345678901234567890
 */

int main()
{
    printf("Function : memmove with overlap\n");
    printf("Source : %s\n", string1 + 4);
    printf("Destination : %s\n", string1 + 10);
    memmove(string1 + 10, string1 + 4, 40);
    printf("Result : %s\n", string1);
    printf("Length : %d characters\n", strlen(string1));

    return 0;
}

/*
Output

    Function : memmove with overlap
    Source : quick brown dog jumps over the lazy fox
    Destination : brown dog jumps over the lazy fox
    Result : The quick quick brown dog jumps over the lazy fox
    Length : 49 characters
*/
