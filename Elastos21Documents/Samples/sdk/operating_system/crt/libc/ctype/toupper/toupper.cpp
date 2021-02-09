//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* toupper.cpp: This program use toupper converts a english characters
 * string to a uppercase string.
 */

#include <stdio.h>
#include <ctype.h>

char msg[] = "THESE letters will BE Capitals\n";
char *p;

int main()
{
    printf("%s", msg);

    /* Reverse case of message. */
    for (p = msg; *p; p++)
        putchar(toupper(*p));

    return 0;
}

/*
Output

    THESE letters will BE Capitals
    THESE LETTERS WILL BE CAPITALS
*/
