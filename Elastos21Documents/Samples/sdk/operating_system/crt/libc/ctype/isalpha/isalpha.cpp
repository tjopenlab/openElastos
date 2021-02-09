//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* isalpha.cpp: This program uses isalpha to verify c
 * whether it is an alphabetic letter(A ¨C Z or a ¨C z).
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    int c = 67;
    if (isalpha(c)) {
        printf("the character is an alphabetic letter !\n");
    }
    else {
        printf("the character is not an alphabetic letter !\n");
    }

    return 0;
}

/*
Output

    the character is an alphabetic letter !
*/
