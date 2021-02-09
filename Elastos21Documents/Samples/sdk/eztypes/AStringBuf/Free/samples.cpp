//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Free" of
//             AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf *pas = AStringBuf::Alloc(12);
    CConsole::Write("The capacity of the string is ");
    CConsole::WriteLine(pas->GetCapacity());
    AStringBuf::Free(pas);

    return 0;
}

//==========================================================================
//Output:The capacity of the string is 12
//==========================================================================
