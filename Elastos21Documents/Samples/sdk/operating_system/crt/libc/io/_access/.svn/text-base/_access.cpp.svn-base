//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _access.cpp: This example uses _access to check the
 * file named "_access.exe" to see if it exists and if
 * reading is allowed.
 */

#include  <io.h>
#include  <stdio.h>
#include  <stdlib.h>

int main()
{
    /* Check for existence */
    if ((_access("_access.exe", 0)) != -1) {
        printf("File _access.exe exists\n");
        /* Check for Read permission */
        if ((_access("_access.exe", 4)) != -1)
            printf("File _access.exe has read permission\n");
    }

    return 0;
}


/*
Output

    File _access.exe exists
    File _access.exe has read permission
*/
