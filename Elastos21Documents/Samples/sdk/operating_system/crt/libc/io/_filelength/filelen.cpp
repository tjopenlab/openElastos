//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* filelen.cpp: This program uses _filelength to report the size
 * of a file before and after modifying it with _chsize.
 */

#include <fcntl.h>
#include <stdio.h>
#include <io.h>
#include <stat.h>

int main()
{
    int fh, result;

    /* Open a file */
    if ((fh = _open("data", _O_RDWR | _O_CREAT, _S_IREAD
                         | _S_IWRITE))  != -1) {
        printf("File length before: %ld\n", _filelength(fh));
        if ((result = _chsize(fh, 329678)) == 0)
            printf("Size successfully changed\n");
        else
            printf("Problem in changing the size\n");
        printf("File length after:  %ld\n", _filelength(fh));
        _close(fh);
    }

    return 0;
}


/*
Output

     File length before: 0
     Size successfully changed
     File length after:  329678
*/
