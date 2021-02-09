//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* islower.cpp: This program uses islower to verify
 * whether it is lowercase character (a ¨C z).
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    int c = 67;
    if (islower(c)) {
        printf("the character is a lowercase letter !\n");
    }
    else {
        printf("the character is not a lowercase letter !\n");
    }

    return 0;
}

/*
Output

    the character is not a lowercase letter !
*/
