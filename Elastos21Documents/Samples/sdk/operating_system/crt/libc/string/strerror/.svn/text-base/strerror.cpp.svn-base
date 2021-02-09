//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//strerror.cpp:  This program attempts to open a file named
// NOSUCHF.ILE. Because this file probably doesn't exist,
// an error message is displayed. The same message is
// created using perror, strerror, and _strerror.
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{
    int  fh;

    if ((fh = _open("NOSUCHF.ILE", _O_RDONLY)) == -1) {
        /* Three ways to create error message: */
        perror("perror says open failed");
        printf("strerror says open failed: %s\n", strerror(errno));
        printf(_strerror("_strerror says open failed"));
    }
    else {
        printf("open succeeded on input file\n");
        _close(fh);
    }

    return 0;
}


//==========================================================================
//Output
//
//     perror says open failed: No such file or directory
//
//     strerror says open failed: No such file or directory
//    _strerror says open failed: No such file or directory
//==========================================================================
