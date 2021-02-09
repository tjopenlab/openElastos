//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "IsNull" of WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf *pas = WStringBuf::Alloc(NULL, 30);
    CConsole::Write("The capacity of the string is ");
    CConsole::WriteLine(pas->GetCapacity());
    if (pas->IsNull()) {
        CConsole::WriteLine("The string is NULL.");
    }
    else {
        CConsole::WriteLine("The string is not NULL.");
    }
    WStringBuf::Free(pas);

    return 0;
}

//==========================================================================
//Output:The capacity of the string is 0
//       The string is NULL.
//==========================================================================
