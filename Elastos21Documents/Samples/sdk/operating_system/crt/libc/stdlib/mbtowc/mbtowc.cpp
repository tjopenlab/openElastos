//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* mbtowc.cpp: illustrates the behavior of the mbtowc function
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    int i;
    wchar_t *pwc = (wchar_t *)malloc(sizeof(wchar_t));

    printf("Convert multibyte character back to a wide "
            "character:\n");
    i = mbtowc(pwc, "    aaaa", 1);
    printf("\tBytes converted: %u\n", i);
    printf("\tWide character: %x\n\n", pwc);

    printf("Attempt to convert when target is NULL\n");
    printf("\tReturns the length of the multibyte character:\n");
    i = mbtowc(NULL, "   aaaa", 1);
    printf("\tLength of multibyte character: %u\n\n", i);

    printf("Attempt to convert a NULL pointer to a");
    printf(" wide character:\n");
    i = mbtowc(pwc, NULL, 1);
    printf("\tBytes converted: %u\n\n", i);

    printf("Attempt to convert a Zero-count to a");
    printf(" wide character:\n");
    i = mbtowc(pwc, "aaaa", 0);
    printf("\tBytes converted: %u\n", i);

    free(pwc);
    return 0;
}

/*
Output

    Convert multibyte character back to a wide character:
            Bytes converted: 1
            Wide character: 153420

    Attempt to convert when target is NULL
            Returns the length of the multibyte character:
            Length of multibyte character: 1

    Attempt to convert a NULL pointer to a wide character:
            Bytes converted: 0

    Attempt to convert a Zero-count to a wide character:
            Bytes converted: 0

*/
