//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* putc.cpp: This program uses putc to write buffer
 * to a stream. If an error occurs, the program
 * stops before writing the entire buffer.
 */

#include <stdio.h>

int main()
{
    FILE *stream;
    char *p, buffer[] = "This is the line of output\n";
    int  ch;

    ch = 0;
    /* Make standard out the stream and write to it. */
    stream = stdout;
    for (p = buffer; (ch != EOF) && (*p != '\0'); p++)
        ch = putc(*p, stream);
    return 0;
}


/*
Output

    This is the line of output
*/
