//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "GetLength" of WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf_<12> as;
    as.Copy(L"hello");
    Int32 length = as.GetLength();
    CConsole::Write("The length of as is ");
    CConsole::WriteLine(length);

    return 0;
}

//==========================================================================
//Output:The length of as is 5
//==========================================================================
