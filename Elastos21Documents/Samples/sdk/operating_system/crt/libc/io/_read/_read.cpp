//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _read.cpp: This program opens a file named
 * _read.cpp and tries to read 60,000 bytes from
 * that file using _read. It then displays the
 * actual number of bytes read from READ.C.
 */

#include <fcntl.h>        /* Needed only for _O_RDWR definition */
#include <io.h>
#include <stdlib.h>
#include <stdio.h>

char buffer[60000];

int main()
{
    int fh;
    unsigned int nbytes = 60000, bytesread;

    /* Open file for input: */
    if ((fh = _open("_read.exe", _O_RDONLY)) == -1) {
        perror("open failed on input file");
        exit(1);
    }

    /* Read in input: */
    if ((bytesread = _read(fh, buffer, nbytes)) <= 0)
        perror("Problem reading file");
    else
        printf("Read %u bytes from file\n", bytesread);

    _close(fh);

    return 0;
}

/*
Output

    Read 6152 bytes from file
*/
