//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "IsNullorEmpty" of WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf *pas = WStringBuf::Alloc(NULL, 30);
    CConsole::Write("The capacity of the string is ");
    CConsole::WriteLine(pas->GetCapacity());
    if (pas->IsNullOrEmpty()) {
        CConsole::WriteLine("The string is null or empty.\n");
    }
    else {
        CConsole::WriteLine("The string is not null or empty.\n");
    }
    WStringBuf::Free(pas);

    pas = WStringBuf::Alloc(L"", 30);
    CConsole::Write("The capacity of the string is ");
    CConsole::WriteLine(pas->GetCapacity());
    if (pas->IsNullOrEmpty()) {
        CConsole::WriteLine("The string is null or empty.");
    }
    else {
        CConsole::WriteLine("The string is not null or empty.");
    }
    WStringBuf::Free(pas);

    return 0;
}

//==========================================================================
//Output:The capacity of the string is 0
//       The string is null or empty.
//       The capacity of the string is 29
//       The string is null or empty.
//==========================================================================
