//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fclose.cpp: This program opens files named "data"
 * ".It  uses fclose to close "data" .
 */

#include <stdio.h>

FILE *stream;

int main()
{

    /* Open for read (will fail if file "data" does not exist) */
    if ((stream  = fopen("data", "w")) == NULL)
        printf("The file 'data' was not opened.\n");
    else
        printf("The file 'data' was opened.\n");

    /* Close stream */
    if (!fclose(stream))
        printf("The file 'data' was closed.\n");

    return 0;
}


/*
Output

    The file 'data' was opened.
    The file 'data' was closed.
*/
