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
    AStringBuf_<20> as;
    as.Copy("Great");
    CConsole::Write("Before call Concatenate,the string is: ");
    CConsole::WriteLine(as);
    as.Concatenate(" Wall", " of", " China", NULL);
    CConsole::Write("After call Concatenate,the string is: ");
    CConsole::WriteLine(as);

    return 0;
}

//==========================================================================
//Output:Before call Concatenate,the string is: Great
//       After call Concatenate,the string is: Great Wall of China
//==========================================================================
