//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* ungetc.cpp: This program first converts a character
 * representation of an unsigned integer to an integer. If
 * the program encounters a character that is not a digit,
 * the program uses ungetc to replace it in the  stream.
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    int ch;
    int result = 0;

    printf("Enter an integer: ");

    /* Read in and convert number: */
    while (((ch = getchar()) != EOF) && isdigit(ch))
        result = result * 10 + ch - '0';     /* Use digit. */
    if (ch != EOF)
        ungetc(ch, stdin);                     /* Put nondigit back. */
    printf("Number = %d\nNextcharacter in stream = '%c'",
            result, getchar());
    return 0;
}


/*
Output

     Enter an integer: 521a
     Number = 521
     Nextcharacter in stream = 'a'
*/
