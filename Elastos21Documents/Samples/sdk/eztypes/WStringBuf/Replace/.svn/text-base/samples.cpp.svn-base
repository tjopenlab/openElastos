//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Replace" of WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf_<15> as;
    as.Copy(L"gReat");
    CConsole::Write("as is: ");
    CConsole::WriteLine(as);
    as.Replace(0, 2, L"Gr");
    CConsole::Write("as is: ");
    CConsole::WriteLine(as);

    return 0;
}

//==========================================================================
//Output:as is: gReat
//       as is: Great
//==========================================================================
