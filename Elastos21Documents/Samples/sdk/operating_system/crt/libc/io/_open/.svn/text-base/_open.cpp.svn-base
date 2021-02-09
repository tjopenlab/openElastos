//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _open.cpp: This program uses _open to open a file
 * named _open.cpp for input and a file named OPEN.OUT
 * for output. The files are then closed.
 */

#include <fcntl.h>
#include <io.h>
#include <stat.h>
#include <stdio.h>

int main()
{
    int fh1, fh2;

    fh1 = _open("_open.exe", _O_RDONLY);
    if (fh1 == -1)
        perror("open failed on input file");
    else {
        printf("open succeeded on input file\n");
        _close(fh1);
    }

    fh2 = _open("OPEN.OUT", _O_WRONLY | _O_CREAT, _S_IREAD | _S_IWRITE);
    if (fh2 == -1)
        perror("Open failed on output file");
    else {
        printf("Open succeeded on output file\n");
        _close(fh2);
    }

    return 0;
}


/*
Output

    Open succeeded on input file
    Open succeeded on output file
*/
