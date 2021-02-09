//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* _putenv.cpp: This program uses getenv to retrieve
 * the LIB environment variable and then uses
 * _putenv to change it to a new value.
 */

#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *libvar;

    /* Get the value of the LIB environment variable. */
    libvar = getenv("LIB");

    if (libvar != NULL)
        printf("Original LIB variable is: %s\n", libvar);
    else
       printf("can not get the enviroment\n");
    /* Attempt to change path. Note that this only affects the environment
     * variable of the current process. The command processor's environment
     * is not changed.
     */
    _putenv("LIB=c:\\mylib;c:\\yourlib");

    /* Get new value. */
    libvar = getenv("LIB");

    if (libvar != NULL)
        printf("New LIB variable is: %s\n", libvar);

    return 0;
}



/*
Output

     Original LIB variable is: C:\progra~1\devstu~1\vc\lib
     New LIB variable is: c:\mylib;c:\yourlib
*/
