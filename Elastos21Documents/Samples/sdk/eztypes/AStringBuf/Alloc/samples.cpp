//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Alloc" of AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf *pas = AStringBuf::Alloc(12);
    CConsole::Write("The capacity of the string is ");
    CConsole::WriteLine(pas->GetCapacity());
    AStringBuf::Free(pas);

    pas = AStringBuf::Alloc("Great Wall of China", 30);
    CConsole::Write("The capacity of the string is ");
    CConsole::WriteLine(pas->GetCapacity());
    AStringBuf::Free(pas);

    return 0;
}

//==========================================================================
//Output:The capacity of the string is 12.
//       The capacity of the string is 29.
//==========================================================================
