//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* atexit.cpp: This program pushes four functions onto
 * the stack of functions to be executed when atexit
 * is called. When the program exits, these programs
 * are executed on a "last in, first out" basis.
 */

#include <stdlib.h>
#include <stdio.h>

void __cdecl fn1()
{
    printf("next.\n");
}

void __cdecl fn2()
{
    printf("executed ");
}

void __cdecl fn3()
{
    printf("is ");
}

void __cdecl fn4()
{
    printf("This ");
}

int main()
{
    atexit(fn1);
    atexit(fn2);
    atexit(fn3);
    atexit(fn4);
    printf("This is executed first.\n");

    return 0;
}



/*
Output

     This is executed first.
     This is executed next.
*/
