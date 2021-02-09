//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _getch.cpp: This program reads characters from
 * the keyboard until it receives a 'Y' or 'y'.
 */

#include <conio.h>
#include <ctype.h>
#include <stdio.h>


int main()
{
    int ch;

    puts("Type 'Y' when finished typing keys: ");
    do {
        ch = _getch();
        ch = toupper(ch);
    } while (ch != 'Y');

    _putch(ch);
    _putch('\r');     /* Carriage return */
    _putch('\n');     /* Line feed         */

    return 0;
}

/*
Output

    Type 'Y' when finished typing keys:
    Y
*/
