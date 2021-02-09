//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "GetLength" of AString.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AString as;
    Int32 length = as.GetLength(10);
    CConsole::Write("The length of as is ");
    CConsole::WriteLine(length);
    as = "Great Wall of China";
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
