//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "AStrBuf" of
//             AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    char *p = new char[20];
    memset(p, 0, 1);

    AStringBuf astrBuf(p, 10);

    Int32 ncap = astrBuf.GetCapacity();
    CConsole::Write("Using AStringBuf,as's capacity is: ");
    CConsole::WriteLine(ncap);

    return 0;
}

//==========================================================================
//Output:Using AStringBuf,as'capacity is: 10
//==========================================================================
