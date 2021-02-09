//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* realloc.cpp: This program allocates a block of memory for
 * buffer and then uses _msize to display the size of that
 * block. Next, it uses realloc to expand the amount of
 * memory used by buffer and then calls _msize again to
 * display the new amount of memory allocated to buffer.
 */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main()
{
    long *buffer;
    size_t size = 1000;

    if ((buffer = (long *)malloc(1000 * sizeof(long))) == NULL)
        exit(1);


    printf("The malloc is success.\n");

    /* Reallocate and show new size: */
    if ((buffer = (long *) realloc(buffer, size + (1000 * sizeof(long))))
        ==  NULL)
        exit(1);

    printf("The realloc is succcess.\n");

    free(buffer);

    return 0;
}

/*
Output

    The malloc is success.
    The realloc is succcess.

*/
