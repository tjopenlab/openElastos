//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "GetLength" of WString.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    WString as;
    Int32 length = as.GetLength(10);
    CConsole::Write("The length of as is ");
    CConsole::WriteLine(length);
    as = L"Great Wall of China";
    length = as.GetLength(10);
    CConsole::Write("The length of as is ");
    CConsole::WriteLine(length);
    length = as.GetLength(20);
    CConsole::Write("The length of as is ");
    CConsole::WriteLine(length);

    return 0;
}

//==========================================================================
//Output:The length of as is -1
//       The length of as is -1
//       The length of as is 19
//==========================================================================
