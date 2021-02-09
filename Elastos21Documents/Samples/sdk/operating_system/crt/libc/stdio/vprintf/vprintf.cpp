//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* vprintf.cpp:this program display a line to screen*/

#include <stdio.h>

void __cdecl test(char *, ...);

int main(int argc, char** argv)
{
    test("Hello,world! %s\n", "This is Elastos!");

    return 0;
}

void __cdecl test(char *first, ...)
{
    int result = 0;
    va_list parglist;

    va_start(parglist, first);
    result = vprintf(first, parglist);
    va_end(parglist);
}


/*
Output

    Hello, world! This is Elastos!
*/
