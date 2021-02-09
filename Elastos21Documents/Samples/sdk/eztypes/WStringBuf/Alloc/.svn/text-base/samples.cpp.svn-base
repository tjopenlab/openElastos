//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Alloc" of WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf *pas = WStringBuf::Alloc(12);
    CConsole::Write("The capacity of the string is ");
    CConsole::WriteLine(pas->GetCapacity());
    WStringBuf::Free(pas);

    pas = WStringBuf::Alloc(L"Great Wall of China", 30);
    CConsole::Write("The capacity of the string is ");
    CConsole::WriteLine(pas->GetCapacity());
    WStringBuf::Free(pas);

    return 0;
}

//=========================================================================
//Output:The capacity of the string is 12
//       The capacity of the string is 29
//=========================================================================
