//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _creat.cpp: This program uses _creat to create
 * the file (or truncate the existing file)
 * named data and open it for writing.
 */

#include <fcntl.h>
#include <io.h>
#include <stat.h>
#include <stdio.h>

int main()
{
    int fh;

    fh = _creat("data", _S_IREAD | _S_IWRITE);
    if (fh == -1)
        perror("Couldn't create data file");
    else {
        printf("Created data file.\n");
        _close(fh);
    }

    return 0;
}


/*
Output

    Created data file.
*/
