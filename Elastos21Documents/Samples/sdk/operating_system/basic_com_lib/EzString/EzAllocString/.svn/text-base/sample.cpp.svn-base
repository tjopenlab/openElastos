//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==============================================================
// Description  : 这个程序演示了EzXXXString系列函数的使用
//==============================================================

#include <stdio.h>
#include <elastos.h>

//==============================================================
// Description  : Error Handler
//==============================================================
void HandleError(const char* msg, ECode ec)
{
    printf("%s (ec = 0x%08x)\n", msg, ec);
}


int main()
{
    OLECHAR * szSource = L"Hello World!";
    BSTR str;

    // Allocates and copies a string.
    str = EzAllocString(szSource);
    if (0 == str) {
        printf("Out of memory.\n");
        return -1;
    }

    printf("%S\n", str);
    // Free the allocated string.
    EzFreeString(str);


    return 0;
}
