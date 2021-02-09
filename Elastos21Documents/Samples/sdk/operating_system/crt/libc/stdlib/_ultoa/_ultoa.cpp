//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _ultoa.cpp:this program convert ul whose type is unsigned long to string
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    char buffer[20];
    unsigned long ul = 1234567890UL;

    _ultoa(ul, buffer, 16);
    printf("String of unsigned long %lu (radix 16): 0x%s.\n", ul,
                                                                     buffer);
    return 0;
}


/*
Output

    String of unsigned long 1234567890 (radix 16): 0x499602d2.
*/
