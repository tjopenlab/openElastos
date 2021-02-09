//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "WStrBuf" of
//             WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    wchar_t *p = new wchar_t[20];
    memset(p, 0, 1);

    WStringBuf wstrBuf(p, 10);

    Int32 ncap = wstrBuf.GetCapacity();
    CConsole::Write("use WStringBuf, as's capacity is: ");
    CConsole::WriteLine(ncap);

    return 0;
}

//==========================================================================
//Output:use WStringBuf, as'capacity is: 10
//==========================================================================
