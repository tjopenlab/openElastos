//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "WString" of AString.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AString as;
    if (as.IsNull()) {
        CConsole::WriteLine("as is NULL.");
    }
    else {
        CConsole::WriteLine("as is not NULL.");
    }

    AString sz("Great Wall of China");
    if (sz.IsNull()) {
        CConsole::WriteLine("sz is NULL.");
    }
    else {
        CConsole::WriteLine("sz is not NULL.");
    }

    return 0;
}

//==========================================================================
//Output:as is NULL.
//       sz is not NULL.
//==========================================================================
