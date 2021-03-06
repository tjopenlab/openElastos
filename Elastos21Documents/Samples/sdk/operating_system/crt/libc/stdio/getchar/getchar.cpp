//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* getchar.cpp: This program uses getchar to read a single line
 * of input from stdin, places this input in buffer, then
 * terminates the string before printing it to the screen.
 */

#include <stdio.h>

int main()
{
    char buffer[81];
    int i, ch;

    printf("Enter a line: ");

    /* Read in single line from "stdin": */
    for (i = 0; (i < 80) && ((ch = getchar()) != EOF) && (ch != '\n'); i++)
        buffer[i] = (char)ch;

    /* Terminate string with null character: */
    buffer[i] = '\0';
    printf("%s\n", buffer);

    return 0;
}

/*
Output

    Enter a line: This is a test
    This is a test
*/
