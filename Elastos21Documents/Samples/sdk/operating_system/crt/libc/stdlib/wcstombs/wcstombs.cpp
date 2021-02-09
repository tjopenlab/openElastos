//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* wcstombs.cpp: this program use wcstombs to converts the multibyte string */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    char    pmbhello[13];
    wchar_t *pwchello = L"Hello,world!";

    printf("Convert to multibyte string:%S\n", pwchello);
    i = wcstombs(pmbhello, pwchello, 13);
    printf("\tCharacters converted: %d\n", i);
    printf("\tmultibyte character: %s\n\n", pmbhello);

    return 0;
}


/*
Output

    Convert to multibyte string:Hello,world!
            Characters converted: 12
            multibyte character: Hello,world!
*/
