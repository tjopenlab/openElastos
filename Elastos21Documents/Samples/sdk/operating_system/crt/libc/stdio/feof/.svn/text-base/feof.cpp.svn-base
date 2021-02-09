//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* feof.cpp: This program uses feof to indicate when
 * it reaches the end of the file feof.cpp. It also
 * checks for errors with ferror.
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int  count, total = 0;
    char buffer[100];
    FILE *stream;

    if ((stream = fopen("feof.exe", "r")) == NULL) {
        printf("problem open the file!\n");
        return 1;
    }

    /* Cycle until end of file reached: */
    while (!feof(stream)) {
        /* Attempt to read in 10 bytes: */
        count = fread(buffer, sizeof(char), 100, stream);
        if (ferror(stream)) {
            perror("Read error");
            break;
        }

        /* Total up actual bytes read */
        total += count;
    }
    printf("Number of bytes read = %d\n", total);
    fclose(stream);

    return 0;
}

/*
Output

     Number of bytes read = 41086
*/
