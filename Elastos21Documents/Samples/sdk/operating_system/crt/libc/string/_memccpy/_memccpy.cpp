//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _memccpy.cpp:this program function copies 0 or more bytes of string1 to buffer,
                halting when the character c has been copied or when count bytes have been copied
 */

#include <stdio.h>
#include <string.h>

char string1[60] = "The quick brown dog jumps over the lazy fox";

int main()
{
    char buffer[61];

    printf("Function:\t_memccpy 60 characters or to character 's'\n");
    printf("Source:\t\t%s\n", string1);
   
    _memccpy(buffer, string1, 's', 60);
   
    printf("Result:\t\t%s\n", buffer);
    printf("Length:\t\t%d characters\n\n", strlen(buffer));

    return 0;
}

/*
Output

    Function:       _memccpy 60 characters or to character 's'
    Source:         The quick brown dog jumps over the lazy fox
    Result:         The quick brown dog jumps
    Length:         25 characters

*/
