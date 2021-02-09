//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* isdigit.cpp: This program uses isdigit to verify c
 * whether it is a decimal-digit character('0' ¨C '9').
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    int c = '6';
    if (isdigit(c)) {
        printf("c is a decimal-digit character.\n");
    }
    else {
        printf("c isn't a decimal-digit character.\n");
    }

    return 0;
}

/*
Output

    c is a decimal-digit character.
*/
