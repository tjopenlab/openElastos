//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* iscntrl.cpp: This program uses iscntrl to verify c
 * whether it is a control character(0x00 ¨C 0x1F or 0x7F).
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    int c, d;
    c = 0x1f;
    d = -3;
    if (iscntrl(c)) {
        printf("c is a Ctrl character.\n");
    }
    else {
        printf("error01!\n");
    }
    if (!iscntrl(d)) {
        printf("d is not a Ctrl character.\n");
    }
    else {
        printf("error02!\n");
    }

    return 0;
}

/*
Output

    c is a Ctrl character.
    d is not a Ctrl character.
*/
