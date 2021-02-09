//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Clone" of AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf_<15> as;
    as.Copy("Hello,World");
    CConsole::Write("The string of as is: ");
    CConsole::WriteLine(as);
    AStringBuf *szbuf;
    szbuf = as.Clone();
    CConsole::Write("The string of szbuf is: ");
    CConsole::WriteLine(*szbuf);
    AStringBuf::Free(szbuf);

    return 0;
}

//==========================================================================
//Output:The string of as is: Hello,world!
//       The string of szbuf is: Hello,world!
//==========================================================================
