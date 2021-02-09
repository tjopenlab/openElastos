//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* isascii.cpp: This program verify a character
 * whether it is a character ASCII.
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    int c, d;
    c = 0x7f;
    d = -3;
    if (__isascii(c)) {
        printf("c is an ASCII character.\n");
    }
    else {
        printf("error01!\n");
    }
    if (!__isascii(d)) {
        printf("d is not an ASCII character.\n");
    }
    else {
        printf("error02!\n");
    }

    return 0;
}

/*
Output

    c is an ASCII character.
    d is not an ASCII character.
*/
