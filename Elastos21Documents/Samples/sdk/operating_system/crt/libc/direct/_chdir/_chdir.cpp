//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _chdir.cpp: This program uses the _chdir function to verify
 * that a given directory exists.
 */

#include <direct.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    if (_chdir("\\Elastos21"))
       printf("Unable to locate the directory: %s\n", "\\Elastos21");
    else
       printf("this directory: %s exists\n", "\\Elastos21");

    return 0;
}


/*
Output

    this directory: \Elastos21 exists
*/
