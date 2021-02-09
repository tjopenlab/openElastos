//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fsetpos.cpp: This program opens a file and reads
 * bytes at several different locations.
 */

#include <stdio.h>

int main()
{
    FILE    *stream = NULL;
    fpos_t pos;
    char    buffer[20];

    if ((stream = fopen("fgetpos.exe", "rb")) == NULL)
        printf("Trouble opening file\n");
    else {
        /* Read some data and then check the position. */
        fread(buffer, sizeof(char), 10, stream);
        if (fgetpos(stream, &pos) != 0)
            perror("fgetpos error");
        else {
            fread(buffer, sizeof(char), 10, stream);
            printf("10 bytes at byte %ld: %.10s\n", pos, buffer);
        }

        /* Set a new position and read more data */
        pos = 140;
        if (fsetpos(stream, &pos) != 0)
            perror("fsetpos error");

        fread(buffer, sizeof(char), 10, stream);
        printf("10 bytes at byte %ld: %.10s\n", pos, buffer);
        fclose(stream);
    }
    return 0;
}

/*
Output

    10 bytes at byte 10: (null)
    10 bytes at byte 140: (null)
*/
