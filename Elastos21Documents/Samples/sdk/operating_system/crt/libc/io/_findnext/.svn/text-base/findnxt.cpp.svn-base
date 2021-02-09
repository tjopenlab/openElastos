//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* findnxt.cpp: This program uses _findnext to find the next name after
 * _findfirst, and then display the attrib of fileinfo structure
 * contents accordingly.
 */

#include <stdio.h>
#include <io.h>
#include <time.h>

int main()
{
    long hFile;
    struct _finddata_t fileinf;;

    /* Find first _find??.exe file in current directory */
    if ((hFile = _findfirst("find*.*", &fileinf)) == -1L)
        printf("No find*.exe files in current directory!\n");
    else {
        do {
            printf((fileinf.attrib & _A_RDONLY) ? " Y  " : " N  ");
            printf((fileinf.attrib & _A_SYSTEM) ? " Y  " : " N  ");
            printf((fileinf.attrib & _A_HIDDEN) ? " Y  " : " N  ");
            printf((fileinf.attrib & _A_ARCH)   ? " Y  " : " N  ");
            printf(" %s\n", fileinf.name);
        } while (_findnext(hFile, &fileinf) == 0);
        _findclose(hFile);
    }

    return 0;
}

/*
Output

     N   N   N   N   findcls.exe
     N   N   N   N   findfst.exe
     N   N   N   N   findnxt.exe
*/
