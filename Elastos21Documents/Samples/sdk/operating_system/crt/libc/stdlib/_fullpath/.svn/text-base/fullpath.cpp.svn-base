//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* fullpath.cpp: This program demonstrates how _fullpath
 * creates a full path from a partial path.
 */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <direct.h>

char full[_MAX_PATH], part[_MAX_PATH];

int main()
{
    while (1) {
        printf("Enter partial path or ENTER to quit: ");
        gets(part);
        if (part[0] == 0)
            break;

        if (_fullpath(full, part, _MAX_PATH) != NULL)
            printf("Full path is: %s\n", full);
        else
            printf("Invalid path\n");
    }

    return 0;
}



/*
Output
    Enter partial path or ENTER to quit: Elastos
    Full path is:D:\Elastos21\XDK\Targets\pdk\win32\x86.msvc.pc.dbg\Elastos
*/
