//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* snprintf.cpp: This program uses sprintf to format various
 * data and place them in the string named buffer.
 */

#include <stdio.h>

int main()
{
    char  buffer[200], s[] = "computer", c = 'l';
    int    i = 35, j;
    float fp = 1.7320534f;

    /* Format and print various data: */
    j  = sprintf(buffer,      "\tString:     %s\n", s);
    j += sprintf(buffer + j, "\tCharacter: %c\n", c);
    j += sprintf(buffer + j, "\tInteger:    %d\n", i);
    j += sprintf(buffer + j, "\tReal:        %f\n", fp);

    printf("Output:\n%s\ncharacter count = %d\n", buffer, j);

    return 0;
}

/*
Output

    Output:
            String:     computer
            Character: l
            Integer:    35
            Real:        1.732053

    character count = 75
*/
