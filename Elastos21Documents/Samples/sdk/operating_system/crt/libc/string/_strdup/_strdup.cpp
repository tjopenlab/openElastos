//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _strdup.cpp:this program calls malloc to allocate storage space for a copy of buffer
               and then copies buffer to the allocated space
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char buffer[] = "This is the buffer text";
    char *newstring;
    printf("Original: %s\n", buffer);
    newstring = _strdup(buffer);
    printf("Copy:      %s\n", newstring);
    free(newstring);

    return 0;
}


/*
Output

    Original: This is the buffer text
    Copy:      This is the buffer text
*/
