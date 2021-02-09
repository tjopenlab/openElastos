//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _chmod.cpp: This program uses _chmod to
 * change the mode of a file to read-only.
 * It then attempts to modify the file.
 */

#include <stdio.h>
#include <io.h>
#include <stat.h>
#include <fcntl.h>


int main()
{
    /* Make file read-only: */
    if (_chmod("_chmod.exe", _S_IREAD) == -1)
        perror("File not found\n");
    else
        printf("Mode changed to read-only\n");

    /* Change back to read/write: */
    if (_chmod("_chmod.exe", _S_IWRITE) == -1)
        perror("File not found\n");
    else
        printf("Mode changed to read/write\n");

    return 0;
}


/*
Output

    Mode changed to read-only
    Mode changed to read/write
*/
