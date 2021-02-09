//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _lseek.cpp: This program first opens a file named _lseek.cpp.
 * It then uses _lseek to find the beginning of the file,
 * to find the current position in the file, and to find
 * the end of the file.
 */

#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int fh;
    long pos;               /* Position of file pointer */
    char buffer[10];

    fh = _open("_lseek.exe", _O_RDONLY);

    /* Seek the beginning of the file: */
   pos = _lseek(fh, 0L, SEEK_SET);
    if (pos == -1L)
        perror("_lseek to beginning failed");
    else
        printf("Position for beginning of file seek = %ld\n", pos);

    /* Move file pointer a little */
    _read(fh, buffer, 10);

    /* Find current position: */
    pos = _lseek(fh, 0L, SEEK_CUR);
    if (pos == -1L)
        perror("_lseek to current position failed");
    else
        printf("Position for current position seek = %ld\n", pos);

    /* Set the end of the file: */
    pos = _lseek(fh, 0L, SEEK_END);
    if (pos == -1L)
        perror("_lseek to end failed");
    else
        printf("Position for end of file seek = %ld\n", pos);

    _close(fh);

    return 0;
}

/*
Output

    Position for beginning of file seek = 0
    Position for current position seek = 10
    Position for end of file seek = 250284
*/
