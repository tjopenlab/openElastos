//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _swab.cpp: this program copies n bytes from from,
    swaps each pair of adjacent bytes,
    and stores the result at to
 */

#include <stdlib.h>
#include <stdio.h>

char from[] = "BADCFEHGJILKNMPORQTSVUXWZY";
char to[] =   "..........................";

int main()
{
    printf("Before:\t%s\n\t%s\n\n", from, to);
    _swab(from, to, sizeof(from));
    printf("After:\t%s\n\t%s\n\n", from, to);

    return 0;
}


/*
Output

    Before: BADCFEHGJILKNMPORQTSVUXWZY
            ..........................

    After:  BADCFEHGJILKNMPORQTSVUXWZY
            ABCDEFGHIJKLMNOPQRSTUVWXYZ
*/
