//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fopen.cpp: This program opens files named "data"
 * and "data2".It  uses fclose to close "data" and
 * _fcloseall to close all remaining files.
 */

#include <stdio.h>

FILE *stream, *stream2;

int main()
{

    /* Open for read (will fail if file "data" does not exist) */
    if ((stream  = fopen("fopen.exe", "r")) == NULL)
        printf("The file 'fopen.cpp' was not opened\n");
    else
        printf("The file 'fopen.cpp' was opened\n");

    /* Open for write */
    if ((stream2 = fopen("fopen.out", "w+")) == NULL)
          printf("The file 'fopen.out' was not opened\n");
    else
          printf("The file 'fopen.out' was opened\n");

     /* Close stream */
    if (fclose(stream))
        printf("The file 'fopen.cpp' was not closed\n");

    if (fclose(stream2))
        printf("The file 'fopen.out' was not closed\n");

    return 0;
}


/*
Output

    The file 'fopen.cpp' was opened.
    The file 'fopen.out' was opened.
*/
