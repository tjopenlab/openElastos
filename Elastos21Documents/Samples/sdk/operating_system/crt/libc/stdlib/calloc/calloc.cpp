//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* calloc.cpp: This program uses calloc to allocate space for
 * 40 long integers. It initializes each element to zero.
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    long *buffer;

    buffer = (long *)calloc(40, sizeof(long));
    if (buffer != NULL)
        printf("Allocated 40 long integers\n");
    else
        printf("Can't allocate memory\n");
    free(buffer);

    return 0;
}

/*
Output

    Allocated 40 long integers
*/
