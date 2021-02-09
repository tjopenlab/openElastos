//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* isxdigit.cpp: This program uses isxdigit to verify c
 * whether it is a hexadecimal digit (A ¨C F, a ¨C f, or 0 ¨C 9).
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    int c = 65;
    if (isxdigit(c)) {
        printf("it is a hexadecimal character.\n");
    }
    else {
        printf("it is not a hexadecimal character.\n");
    }

    return 0;
}

/*
Output

    it is a hexadecimal character.
*/
