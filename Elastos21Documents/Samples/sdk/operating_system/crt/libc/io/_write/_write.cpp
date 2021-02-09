//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _write.cpp: This program opens a file for output
 * and uses _write to write some bytes to the file.
 */

#include <io.h>
#include <stat.h>
#include <stdio.h>
#include <fcntl.h>

char buffer[] = "This is a test of '_write' function";

int main()
{
    int fh;
    int byteswritten;

    if ((fh = _open("write.o", _O_RDWR | _O_CREAT,
                                         _S_IREAD | _S_IWRITE)) != -1) {
        if ((byteswritten = _write(fh, buffer, sizeof(buffer))) == -1)
            perror("Write failed");
        else
            printf("Wrote %d bytes to file\n", byteswritten);

        _close(fh);
    }

    return 0;
}


/*
Output

    Wrote 36 bytes to file
*/
