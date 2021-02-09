//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _close.cpp: This program uses _open to open a file
 * named _close.sam and then close it.
 */

#include <fcntl.h>
#include <io.h>
#include <stat.h>
#include <stdio.h>

int main()
{
    int fh1 = 0;

    fh1 = _open("_close.sam", _O_RDWR | _O_CREAT, _S_IREAD | _S_IWRITE);

    if (fh1 == -1)
        perror("open failed on file _close.sam");
    else {
        if ((fh1 = _close(fh1)) == -1) {
            printf("Close failed on file :_close.sam.\n");
            return 1;
        }
        printf("Open file _close.sam success!\n");
        printf("Close file _close.sam success!\n");
    }

    return 0;
}


/*
Output

    Open file _close.sam succeess!
    Close file _close.sam succeess!
*/
