//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* wctomb.cpp: this program use wctomb to converts the wide character to a multibyte character */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    wchar_t wc = L'a';
    char *pmbnull = NULL;
    char *pmb = (char *)malloc(sizeof(char));

    printf("Convert a wide character:\n");
    i = wctomb(pmb, wc);
    printf("\tCharacters converted: %u\n", i);
    printf("\tMultibyte character: %.1s\n\n", pmb);

    printf("Attempt to convert when target is NULL:\n");
    i = wctomb(pmbnull, wc);
    printf("\tCharacters converted: %u\n", i);
    printf("\tMultibyte character: %.1s\n", pmbnull);


    free(pmb);

    return 0;
}


/*
Output

    Convert a wide character:
            Characters converted: 1
            Multibyte character: a
            
    Attempt to convert when target is NULL:
    Characters converted: 0
    Multibyte character: (
*/
