//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "IsEmpty" of AString.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AString as("");
    if (as.IsEmpty()) {
        CConsole::WriteLine("The string is empty.");
    }
    else {
        CConsole::WriteLine("The string is not empty.");
    }
    as = "Great Wall of China";
    if (as.IsEmpty()) {
        CConsole::WriteLine("The string is empty.");
    }
    else {
        CConsole::WriteLine("The string is not empty.");
    }

    return 0;
}

//==========================================================================
//Output:The string is empty.
//       The string is not empty.
//==========================================================================
