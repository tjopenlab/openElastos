//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _setmode.cpp: This program uses _setmode to change
 * stdin from text mode to binary mode.
 */

#include <stdio.h>
#include <fcntl.h>
#include <io.h>

int main()
{
    int result;

    /* Set "stdin" to have binary mode: */
    result = _setmode(_fileno(stdin), _O_BINARY);
    if (result == -1)
        perror("Cannot set mode");
    else
        printf("'stdin' successfully changed to binary mode\n");

    return 0;
}


/*
Output

    'stdin' successfully changed to binary mode
*/
