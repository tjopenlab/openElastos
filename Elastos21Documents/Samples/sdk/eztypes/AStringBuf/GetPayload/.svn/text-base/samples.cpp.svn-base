//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "GetPayload" of AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf *pas = AStringBuf::Alloc("Great Wall of China", 20);
    char *p = pas->GetPayload();
    CConsole::Write("The string pas is : ");
    CConsole::Write("The string pas is : ");
    CConsole::WriteLine(*pas);
    CConsole::Write("The string p is : ");
    CConsole::WriteLine(p);
    AStringBuf::Free(pas);

    return 0;
}

//==========================================================================
//Output:The string pas is : Great Wall of China
//       The string p is : Great Wall of China
//==========================================================================
