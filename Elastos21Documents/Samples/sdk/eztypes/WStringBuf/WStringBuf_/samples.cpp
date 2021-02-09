//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "WStrBuf_" of
//             WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf_<12> as;

    Int32 i = as.GetCapacity();
    CConsole::Write("Using WStringBuf_ ,as's capacity is: ");
    CConsole::WriteLine(i);

    return 0;
}

//==========================================================================
//Output:Using WStringBuf_  ,as'capacity is: 12
//==========================================================================
