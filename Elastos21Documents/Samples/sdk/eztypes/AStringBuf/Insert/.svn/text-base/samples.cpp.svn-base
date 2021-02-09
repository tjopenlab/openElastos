//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Insert" of AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf_<15> as;
    as.Copy("123");
    CConsole::Write("Before insert,the string is: ");
    CConsole::WriteLine(as);
    as.Insert(1, "hello,world!");
    CConsole::Write("After insert,the string is: ");
    CConsole::WriteLine(as);

    return 0;
}

//==========================================================================
//Output:Before insert,the string is: 123
//       After insert,the string is: 1hello,world!23
//==========================================================================
