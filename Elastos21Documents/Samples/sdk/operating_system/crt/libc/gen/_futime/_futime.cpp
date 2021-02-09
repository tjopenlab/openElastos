//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _futime.cpp: This program uses _futime to set the
 * file-modification time to the current time.
 */

#include <stdio.h>
#include <utime.h>
#include <fcntl.h>
#include <io.h>
#include <stat.h>

int main()
{
    int hFile;

    hFile = _open("_futime.exe", _O_RDWR, _S_IREAD | _S_IWRITE);
    if (-1 == hFile) {
        printf("_open error.\n");
        return 1;
    }

    if (_futime(hFile, NULL) == -1)
        printf("_futime failed.\n");
    else
        printf("File time modified.\n");

    _close(hFile);

    return 0;
}

/*
Output

    File time modified.
*/
