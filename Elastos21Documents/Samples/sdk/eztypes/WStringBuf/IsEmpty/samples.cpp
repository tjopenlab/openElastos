//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "IsEmpty" of WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf *pas = WStringBuf::Alloc(L"", 30);
    CConsole::Write("The capacity of the string is ");
    CConsole::WriteLine(pas->GetCapacity());
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
//Output:The capacity of the string is 29
//       The string is empty.
//==========================================================================
