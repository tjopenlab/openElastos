//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* rename.cpp: This program attempts to rename a file
 * named rename.tmp to newname.tmp. For this operation
 * to succeed, a file named rename.tmp must exist and
 * a file named newname.tmp must not exist.
 */

#include <stdio.h>

int main()
{
    int  result;
    char oldfile[] = "rename.tmp", newfile[] = "newname.tmp";

    /* Attempt to rename file: */
    result = rename(oldfile, newfile);
    if (result != 0)
        printf("Could not rename '%s'\n", oldfile);
    else
        printf("File '%s' renamed to '%s'\n", oldfile, newfile);

    return 0;
}

/*
Output

    File 'rename.tmp' renamed to 'newname.tmp'
*/
