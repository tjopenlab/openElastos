//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _getch.cpp: This program uses _findfirst to find first instance of
 * a filename that matches the file specified in the filespec argument.

 */

#include <stdio.h>
#include <io.h>
#include <time.h>

int main()
{
    long hFile;
    struct _finddata_t fileinf;

    /* Find first findf*.exe file in current directory */
    if ((hFile = _findfirst("findf*.exe", &fileinf)) == -1L)
        printf("No findf*.exe files in current directory!\n");
    else {
        printf("findf*.exe: %-18s %.24s  %9ld\n", fileinf.name,
            ctime(&(fileinf.time_write)), fileinf.size);
        _findclose(hFile);
    }

    return 0;
}

/*
Output

    findf*.exe: findfst.exe        Tue Nov 23 13:56:08 2004     248886
*/
