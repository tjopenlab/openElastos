//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* isspace.cpp: This program uses isspace to verify c
 * whether it is a space character (0x09 ¨C 0x0D or 0x20).
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    int c = 0x09;
    if (isspace(c)) {
        printf("it is a particular representation of a "
            "space character.\n");
    }
    else {
        printf("it is not a particular representation of a "
            "space character.\n");
    }

    return 0;
}

/*
Output

    it is a particular representation of a space character.
*/
