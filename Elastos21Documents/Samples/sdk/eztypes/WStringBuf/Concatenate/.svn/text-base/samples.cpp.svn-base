//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use method "Concatenate".
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WStringBuf_<20> as;
    as.Copy(L"Great");
    CConsole::Write("before call Concatenate,the string is: ");
    CConsole::WriteLine(as);
    as.Concatenate(L" Wall", L" of", L" China", NULL);
    CConsole::Write("after call Concatenate,the string is: ");
    CConsole::WriteLine(as);

    return 0;
}

//==========================================================================
//Output:before call Concatenate,the string is: Great
//       after call Concatenate,the string is: Great Wall of China
//==========================================================================
