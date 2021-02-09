//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

/* vfprintf.cpp:this program uses vfprintf to write lines and then read it to
                display to the screen*/

#include <stdio.h>

int __cdecl test(FILE *out, ...);

int main()
{
    FILE *out = NULL;
    char buffer[100];
    int retCun = 0;

    out = fopen("vfprintf.out", "w");
    if (out == NULL) {
        printf("cannot open:vfprintf.out\n");
        return 1;
    }
    retCun = test(out, "This is Elastos!");
    fclose(out);
    out = fopen("vfprintf.out", "r");
    if (out == NULL) {
        printf("cannot open:vfprintf.out\n");
        return 1;
    }
    fread(buffer, retCun, sizeof(char), out);
    buffer[retCun] = '\0';
    printf("%s", buffer);
    fclose(out);
    return 0;
}

int __cdecl test(FILE *out, ...)
{
    int result = 0;
    va_list parglist;
    va_start(parglist, out);
    result = vfprintf(out, "Hello,world! %s\n", parglist);
    va_end(parglist);
    printf("The return value is %d\n", result);
    return result;
}

/*
Output

    The return value is 30
    Hello, world! This is Elastos!
*/
