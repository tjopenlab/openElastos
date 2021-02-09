//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* malloc.cpp:This program allocates memory with
 * malloc, then frees the memory with free.
 */

#include <stdlib.h>            /* For _MAX_PATH definition */
#include <stdio.h>
#include <malloc.h>

int main()
{
    char *string;

    /* Allocate space for a path name */
    string = (char *)malloc(_MAX_PATH);
    if (string == NULL)
        printf("Insufficient memory available\n");
    else {
        printf("Memory space allocated for path name\n");
        free(string);
        printf("Memory freed\n");
    }

    return 0;
}


/*
Output

     Memory space allocated for path name
     Memory freed
*/
