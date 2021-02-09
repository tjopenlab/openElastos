//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* findcls.cpp: This program search handle returned by a previous
 * call to _findfirst,and then uses _findclose to close the specified
 * search handle and releases associated resources.
 */

#include <fcntl.h>
#include <stdio.h>
#include <io.h>

int main()
{
    long hFile;
    struct _finddata_t fileinf;

    /* Find first _findf*.* file in current directory */
    if ((hFile = _findfirst("findcls*.*", &fileinf)) != -1L) {

        printf("Find specified file.\n");
        printf("Name is : %s\n", fileinf.name);
        if (_findclose(hFile) == 0)
            printf("_findclose is right\n");
        else
            printf("_findclose error\n");
    }

    return 0;
}

/*
Output

    Find specified file.
    Name is : findcls.exe
    _findclose is right
*/
