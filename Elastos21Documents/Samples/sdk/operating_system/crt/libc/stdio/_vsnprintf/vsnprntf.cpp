//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* vsnprntf.cpp:the program return the number of characters written*/

#include <stdio.h>
#include <stdarg.h>
#define BUFSIZE 500
#define BUFMAX 100

void __cdecl test(char *buf, ...);

int main(int argc, char *argv[])
{
    char buffer[BUFSIZE] = "This is Elastos Of KoreTide Corp!";
    char ch = 'A';
    wchar_t wch = 'B';
    int i = 9999, j = -999;
    double x = 987.654321;
    test("Hello! %s a good operation system!", buffer);
    test("ch = %4c, wch = %-4d, i = %6d, j = %-10x, x= %10.5e", \
        ch, wch, i, j, x);

    return 0;
}

void __cdecl test(char *buf, ...)
{
    char writebuf[BUFSIZE];
    va_list marker;
    int result = 0;
    int k = BUFMAX;
    va_start(marker, buf);
    result = _vsnprintf(writebuf, k, buf , marker);
    va_end(marker);
    printf("%s\n",writebuf);
    printf("result = %d\n",result);
}

/*
Output

    Hello! This is Elastos Of KoreTide Corp! a good operation system!
    result = 65
    ch =    A, wch = 66  , i =   9999, j = fffffc19  , x= 9.87654e+002
    result = 66
*/
