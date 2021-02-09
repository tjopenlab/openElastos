//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _utime.cpp: TThis program uses _utime to set the
 * file-modification time to the current time.
 */

#include <stdio.h>
#include <utime.h>

int main()
{
    if (_utime("_utime.exe", NULL) == -1)
        printf("_wutime failed\n");
    else
        printf("File time modified\n");

    return 0;
}


/*
Output

    File time modified
*/
