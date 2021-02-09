//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "IsNull" of WString.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WString as;
    if (as.IsNull()) {
        CConsole::WriteLine("The string is NULL.");
    }
    else {
        CConsole::WriteLine("The string is not NULL.");
    }
    as = L"Great Wall of China";
    if (as.IsNull()) {
        CConsole::WriteLine("The string is NULL.");
    }
    else {
        CConsole::WriteLine("The string is not NULL.");
    }

    return 0;
}

//==========================================================================
//Output:The string is NULL.
//       The string is not NULL.
//==========================================================================
