//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _tell.cpp: This program uses _tell to tell the
 * file pointer position after a file read.
 */

#include <io.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    int  fh;
    int pos;
    char buffer[500];

    if ((fh = _open("_tell.exe", _O_RDONLY )) == -1)
        printf("problem open the file !\n");
    else {
        printf("open the file success!\n");
        if ((_read(fh, buffer, 500)) != 0) {
            printf("read the file success\n" );
            pos = _tell(fh);
            if (pos)
                printf("Current file position is: %d\n", pos);
            else
                printf("problem Current file position is: %d\n", pos);
        }
        else
            printf("problem read the file.\n");
        _close(fh);
    }
    return 0;
}

/*
Output
    open the file success!
    read the file success
    Current file position is: 500
*/
