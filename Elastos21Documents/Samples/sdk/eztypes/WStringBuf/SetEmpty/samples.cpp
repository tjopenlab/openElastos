//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "SetEmpty" of WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf *pas = WStringBuf::Alloc(L"Great Wall of China", 30);

    CConsole::WriteLine("Before calling \"SetEmpty\":");
    if (pas->IsEmpty()) {
        CConsole::WriteLine("The string is empty.");
    }
    else {
        CConsole::WriteLine("The string is not empty.");
    }

    pas->SetEmpty();
    CConsole::WriteLine("After calling \"SetEmpty\":");
    if (pas->IsEmpty()) {
        CConsole::WriteLine("The string is empty.");
    }
    else {
        CConsole::WriteLine("The string is not empty.");
    }
    WStringBuf::Free(pas);

    return 0;
}

//==========================================================================
//Output:Before calling "SetEmpty":
//       The string is not empty.
//       After calling "SetEmpty":
//       The string is empty.
//==========================================================================
