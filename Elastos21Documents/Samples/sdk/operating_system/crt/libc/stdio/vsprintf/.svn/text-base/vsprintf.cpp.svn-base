//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* vsprintf.cpp:this program write lines to a buffer*/

#include <stdio.h>

void __cdecl test(char* first, ...);

int main()
{
    char buffer[] = "world";
    test("hello %s", buffer);

    return 0;

}

void __cdecl test(char * first, ...)
{
    char writeBuf[550];
    va_list marker;

    va_start(marker, first);
    vsprintf(writeBuf, first, (unsigned char*)marker);
    va_end(marker);
    printf("%s\n", writeBuf);
}

/*
Output

    hello world
*/
