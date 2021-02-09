//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Insert" of WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf_<15> as;
    as.Copy(L"123");
    CConsole::Write("before insert,the string is: ");
    CConsole::WriteLine(as);
    as.Insert(1, L"hello,world!");
    CConsole::Write("after insert,the string is: ");
    CConsole::WriteLine(as);

    return 0;
}

//==========================================================================
//Output:before insert,the string is: 123
//       after insert,the string is: 1hello,world!23
//==========================================================================
