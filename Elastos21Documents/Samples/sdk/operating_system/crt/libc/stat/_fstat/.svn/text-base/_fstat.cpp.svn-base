//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _fstat.cpp: This program uses _fstat to report
 * the size of a file named F_STAT.OUT.
 */

#include <io.h>
#include <stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct stat buf;
    int fh, result;
    char buffer[] = "A line to output";

    if ((fh = _open("_fstat.out", _O_CREAT | _O_WRONLY | _O_TRUNC ,
            _S_IREAD | _S_IWRITE)) ==  -1) {
        printf("problem open the file!\n");
        return 1;
    }

    _write(fh, buffer, strlen(buffer));

    /* Get data associated with "fh": */
    result = _fstat(fh, &buf);

    /* Check if statistics are valid: */
    if (result != 0)
        printf("Bad file handle\n");
    else {
        printf("File size      : %ld\n", buf.st_size);
        printf("Time modified : %s", ctime(&buf.st_ctime));
    }

    _close(fh);

    return 0;
}

/*
Output

     File size      : 16
     Time modified : Tue Nov 06 10:20:12 2007
*/
