//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Clone" of WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf_<15> as;
    as.Copy(L"Hello,World");
    CConsole::Write("The string of as is: ");
    CConsole::WriteLine(as);
    WStringBuf *szbuf;
    szbuf = as.Clone();
    CConsole::Write("The string of szbuf is: ");
    CConsole::WriteLine(*szbuf);
    WStringBuf::Free(szbuf);

    return 0;
}

//==========================================================================
//Output:The string of as is: Hello,world!
//       The string of szbuf is: Hello,world!
//==========================================================================
