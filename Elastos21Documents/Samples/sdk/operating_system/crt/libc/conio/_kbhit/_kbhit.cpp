//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _kbhit.cpp: This program loops until the user
 * presses a key. If _kbhit returns nonzero, a
 * keystroke is waiting in the buffer. The program
 * can call _getch or _getche to get the keystroke.
 */

#include <conio.h>
#include <stdio.h>

int main()
{
    /* Display message until key is pressed. */
    while (!_kbhit())
        puts("Hit me!! ");

    /* Use _getch to throw key away. */
    printf("\nKey struck was '%c'\n", _getch());
    _getch();

    return 0;
}

/*
Output

    Hit me!!
    Hit me!!
    Hit me!!
    Hit me!!
    Hit me!!
    Hit me!!
    Hit me!!
    Hit me!!
    Hit me!!
    Hit me!!
    Hit me!!
    Hit me!!

    Key struck was 'q'
*/

