//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "AStrBuf_" of
//             AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf_<12> as;

    CConsole::Write("Using AStringBuf_ ,as's capacity is: ");
    CConsole::WriteLine(as.GetCapacity());

    return 0;
}

//==========================================================================
//Output:Using AStringBuf_  ,as'capacity is: 12
//==========================================================================
