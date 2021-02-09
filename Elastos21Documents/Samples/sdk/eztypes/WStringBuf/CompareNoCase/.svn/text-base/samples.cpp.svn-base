//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "CompareNoCase" of WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf_<15> as;
    as.Copy("great");
    CConsole::Write("as is: ");
    CConsole::WriteLine(as);
    WStringBuf_<15> sz;
    sz.Copy("Great");
    CConsole::Write("sz is: ");
    CConsole::WriteLine(sz);
    if (as.Compare(sz, StringCase_Insensitive) == 0) {
        CConsole::WriteLine("The strings are equal if calling CompareNoCase.");
    }
    else {
        CConsole::WriteLine("The strings are unequal if calling CompareNoCase.");
    }

    return 0;
}

//==========================================================================
//Output:as is: great
//       sz is: Great
//       The strings are equal if calling CompareNoCase.
//==========================================================================
