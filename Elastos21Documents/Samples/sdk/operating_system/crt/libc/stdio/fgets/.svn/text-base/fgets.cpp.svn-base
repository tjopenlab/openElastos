//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fgets.cpp: This program uses fgets to display
 * a line from a file on the screen.
 */

#include <stdio.h>

int main()
{
    FILE *stream;
    char line[100];

    if ((stream = fopen("fgets.exe", "r")) != NULL) {
        if (fgets(line, 100, stream) == NULL)
            printf("fgets error\n");
        else
            printf("%s\n", line);
        fclose(stream);
    }
    else
        printf("problem open the file!\n");

    return 0;
}

/*
Output

    MZ?
*/
