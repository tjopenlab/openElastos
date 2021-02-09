//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Append" of AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf_<12> as;
    as.Copy("Hello");
    CConsole::Write("Before call Append,as is: ");
    CConsole::WriteLine(as);
    as.Append(",world!", 0, 7);
    CConsole::Write("The first time to call Append ,as is: ");
    CConsole::WriteLine(as);

    as.SetEmpty();
    CConsole::WriteLine("SetEmpty");

    as.Copy("12");
    CConsole::Write("Before call Append,as is: ");
    CConsole::WriteLine(as);
    as.Append(3);
    CConsole::Write("The second time to call Append ,as is: ");
    CConsole::WriteLine(as);

    return 0;
}

//==========================================================================
//Output: Before call Append,as is: Hello
//        The first time to call Append,as is: Hello,world!
//        SetEmpty
//        Before call Append,as is: 12
//        The second time to call Append ,as is: 123
//==========================================================================
