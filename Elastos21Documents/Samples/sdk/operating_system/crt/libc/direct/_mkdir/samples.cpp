//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// discription:: This program uses the _mkdir function to created
// that a given directory.
//==========================================================================

#include <stdio.h>
#include <direct.h>


int main()
{
    if (_mkdir("\\testtmp") == 0) {
        printf("Directory '\\testtmp' was successfully created\n");
        if (_rmdir("\\testtmp") == 0)
            printf( "Directory '\\testtmp' was successfully removed\n"  );
        else
            printf( "Problem removing directory '\\testtmp'\n" );
    }
    else
        printf("Problem creating directory '\\testtmp'\n");
    return 0;
}


//==========================================================================
//Output:
//  Directory '\testtmp' was successfully created
//==========================================================================
