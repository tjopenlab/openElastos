//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* tolower.cpp: This program use tolower converts a english characters
 * string to a lowercase string.
 */

#include <stdio.h>
#include <ctype.h>

char msg[] = "THESE letters will BE in lower cases\r\n";
char *p;

int main()
{
    printf("%s", msg);

    /* Reverse case of message. */
    for (p = msg; *p; p++)
        putchar(tolower(*p));

    return 0;
}

/*
Output

    THESE letters will BE in lower cases
    these letters will be in lower cases
*/
