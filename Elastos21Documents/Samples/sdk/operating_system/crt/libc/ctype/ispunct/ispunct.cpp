//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* ispunct.cpp: This program uses ispunct to verify c
 * whether it is a punctuation character.
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    int c = 36;
    if (ispunct(c)) {
        printf("it is a punctuation character.\n");
    }
    else {
        printf("it is not a punctuation character.\n");
    }

    return 0;
}

/*
Output

    it is a punctuation character.
*/
