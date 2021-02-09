//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use operator datatypes of WString.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WString as(L"Hi");
    CConsole::Write("as is: ");
    CConsole::WriteLine(as);

    wchar_t *str = L"Great Wall of China";
    as = str;
    CConsole::Write("as is: ");
    CConsole::WriteLine(as);

    WString ezstr(L"Hello,World!");
    as = ezstr;
    CConsole::Write("as is: ");
    CConsole::WriteLine(as);

    return 0;
}

//==========================================================================
//Output:as is: Hi
//       as is: Great Wall of China
//       as is: Hello,world!
//==========================================================================
