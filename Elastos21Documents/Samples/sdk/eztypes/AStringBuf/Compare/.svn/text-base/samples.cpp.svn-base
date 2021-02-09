//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Compare" of AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf_<15> as;
    as.Copy("great");
    CConsole::Write("as is: ");
    CConsole::WriteLine(as);
    AStringBuf_<15> sz;
    sz.Copy("Great");
    CConsole::Write("sz is: ");
    CConsole::WriteLine(sz);
    if (as.Compare(sz) == 0) {
        CConsole::WriteLine("The strings are equal if calling Compare");
    }
    else {
        CConsole::WriteLine("The strings are unequal if calling Compare");
    }

    return 0;
}

//==========================================================================
//Output:as is: great
//       sz is: Great
//       The strings are unequal if calling Compare
//==========================================================================
