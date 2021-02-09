//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "IsEmpty" of AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf *pas = AStringBuf::Alloc("Great Wall of China", 30);
    if (pas->IsEmpty()) {
        CConsole::WriteLine("The string is empty.");
    }
    else {
        CConsole::WriteLine("The string is not empty.");
    }

    pas->SetEmpty();
    if (pas->IsEmpty()) {
        CConsole::WriteLine("The string is empty.");
    }
    else {
        CConsole::WriteLine("The string is not empty.");
    }

    AStringBuf::Free(pas);

    return 0;
}

//==========================================================================
//Output:The string is not empty.
//       The string is empty.
//==========================================================================
