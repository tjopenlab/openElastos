//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _eof.cpp: This program reads data from a file
 * ten bytes at a time until the end of the
 * file is reached or an error is encountered.
 */


#include <fcntl.h>
#include <io.h>
#include <stdio.h>

int main()
{
     int  fh, count, total = 0;
     char buf[10];
     if ((fh = _open("data", _O_RDONLY)) == - 1) {
         perror("Open failed");
         return 1;
     }
     /* Cycle until end of file reached: */
     while (!_eof(fh)) {
          /* Attempt to read in 10 bytes: */
          if ((count = _read(fh, buf, 10)) == -1) {
                perror("Read error");
                break;
          }
          /* Total actual bytes read */
          total += count;
     }

     printf("Number of bytes read = %d\n", total);
     _close(fh);

     return 0;
}

/*
Output

     Number of bytes read = 0
*/
