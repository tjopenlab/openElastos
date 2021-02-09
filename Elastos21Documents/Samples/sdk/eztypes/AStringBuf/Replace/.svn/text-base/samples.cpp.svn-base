//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Replace" of AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf_<15> as;
    as.Copy("gReat");
    CConsole::Write("as is: ");
    CConsole::WriteLine(as);
    as.Replace(0, 2, "Gr");
    CConsole::Write("as is: ");
    CConsole::WriteLine(as);

    return 0;
}

//==========================================================================
//Output:as is: gReat
//       as is: Great
//==========================================================================
