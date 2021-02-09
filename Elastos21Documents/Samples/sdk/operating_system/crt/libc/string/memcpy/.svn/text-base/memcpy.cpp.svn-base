//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* memcpy.cpp:this program use memcpy to  copies count bytes of string1 to string2
 */

#include <string.h>
#include <stdio.h>

char string1[60] = "The quick brown dog jumps over the lazy fox";
char string2[60] = "The quick brown fox jumps over the lazy dog";
/*                               1         2         3         4         5
 *                      12345678901234567890123456789012345678901234567890
 */

int main()
{
    printf("Function:    memcpy without overlap\n");
    printf("Source:      %s\n", string1 + 40);
    printf("Destination: %s\n", string1 + 16);
    memcpy(string1 + 16, string1 + 40, 6);
    printf("Result:      %s\n", string1);

    return 0;
}

//==========================================================================
//Output
//    Function:    memcpy without overlap
//    Source:      fox
//    Destination: dog jumps over the lazy fox
//    Result:      The quick brown fox
//==========================================================================

