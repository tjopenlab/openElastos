//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _rmdir.cpp: This program uses the _mkdir function to created
 * a new directory and then uses _rmdir function to remove this directory
 */

#include <stdio.h>
#include <direct.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (_mkdir("testtmp") == 0) {
        printf("Directory 'testtmp' was successfully created\n");
        if (_rmdir("testtmp") == 0)
            printf("Directory 'testtmp' was successfully removed\n" );
        else
            printf("Problem removing directory 'testtmp'\n");
    }
    else
        printf("Problem creating directory 'testtmp'\n");

    return 0;
}

/*
Output

    Directory 'testtmp' was successfully created
    Directory 'testtmp' was successfully removed
*/
