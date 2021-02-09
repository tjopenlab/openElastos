//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fsopen.cpp: This program opens files named "data"
 * and "data2".It  uses fclose to close "data" and
 * _fcloseall to close all remaining files.
 */

#include <stdio.h>

FILE *stream, *stream2;

int main()
{

    /* Open for read (will fail if file "data" does not exist) */
    if ((stream  = fsopen("fsopen.exe", "r",1)) == NULL)
        printf("The file 'fsopen.cpp' was not opened\n");
    else
        printf("The file 'fsopen.cpp' was opened\n");

     /* Close stream */
    if (fclose(stream))
        printf("The file 'fsopen.cpp' was not closed\n");

    return 0;
}


/*
Output

    The file 'fsopen.cpp' was opened.
*/
