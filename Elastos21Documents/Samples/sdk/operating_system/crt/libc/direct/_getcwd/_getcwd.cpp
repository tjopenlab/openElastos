//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _getcwd.cpp:This program places the name of the current directory in the
 * buffer array, then displays the name of the current directory
 * on the screen. Specifying a length of _MAX_PATH leaves room
 * for the longest legal path name.
 */

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    char buffer[_MAX_PATH];

    /* Get the current working directory: */
    printf("the current working directory is:\n");
    if (_getcwd(buffer, _MAX_PATH) == NULL)
        perror("_getcwd error");
    else
        printf("%s\n", buffer);

   return 0;
}

/*
Output

    the current working directory is:
    /
*/
