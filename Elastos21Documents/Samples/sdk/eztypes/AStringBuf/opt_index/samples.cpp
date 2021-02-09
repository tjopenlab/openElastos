//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use operator index of AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf_<12> as;
    as.Copy("Hello,World!");
    AChar ch = as[0];
    CConsole::Write("this ch is: ");
    CConsole::WriteLine(ch);

    return 0;
}

//==========================================================================
//Output:This ch is: H
//==========================================================================
