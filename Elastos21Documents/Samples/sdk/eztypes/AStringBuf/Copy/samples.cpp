//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "Copy" of AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AStringBuf_<5> as;
    as.Copy("Hello,World!");
    CConsole::Write("After calling copy,the string is: ");
    CConsole::WriteLine(as);

    return 0;
}

//==========================================================================
//Output:After calling copy,the string is: Hello
//==========================================================================
