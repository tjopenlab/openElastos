//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _fdopen.cpp: This program opens a file using low-
 * level I/O, then uses _fdopen to switch to stream
 * access. It counts the lines in the file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

int main()
{
    FILE *stream;
    int  fh, count = 0;
    char inbuf[128];

    /* Open a file handle. */
    if ((fh = _open("_fdopen.exe", _O_RDONLY)) == -1) {
        perror("open failed on input file");
        return 1;
    }

    /* Change handle access to stream access. */
    if ((stream = _fdopen(fh, "r")) == NULL)
         return 1;

    while (fgets(inbuf, 128, stream) != NULL)
         count++;

    /* After _fdopen, close with fclose, not _close. */
    fclose(stream);
    printf("Lines in file: %d\n", count);
    return 0;
}

/*
Output

      Lines in file: 351
*/
