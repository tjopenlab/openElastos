//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Compare" of AString.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AString as("great");
    CConsole::Write("as is: ");
    CConsole::WriteLine(as);
    AString sz("Great");
    CConsole::Write("sz is: ");
    CConsole::WriteLine(sz);
    if (as.Compare(sz) == 0) {
        CConsole::WriteLine("The strings are equal if calling Compare.");
    }
    else {
        CConsole::WriteLine("The strings are unequal if calling Compare.");
    }

    return 0;
}

//==========================================================================
//Output:as is: great
//       sz is: Great
//       The strings are unequal if calling Compare.
//==========================================================================
