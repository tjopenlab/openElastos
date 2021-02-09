//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* ferror.cpp: This program uses ferror to tests for an error on a stream.
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int  count = 0;
    char buffer[100];
    FILE *stream;

    if ((stream = fopen("ferror.txt", "w")) == NULL) {
        printf("problem open the file!");
        return 1;
    }

    /* Attempt to read in 10 bytes: */
    count = fread(buffer, sizeof(char), 100, stream);
    if (ferror(stream)) {
        printf("Read error.\n");
    }
    else {
        printf("Read OK!\n");
    }

    fclose(stream);

    return 0;
}


/*
Output

     Read error.
*/
