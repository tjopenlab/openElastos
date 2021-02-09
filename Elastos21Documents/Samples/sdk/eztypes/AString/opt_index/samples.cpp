//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use operator index of AString.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    AString as("Hello,World!");
    AChar str = as[0];
    CConsole::Write("This str is: ");
    CConsole::WriteLine(str);

    return 0;
}

//==========================================================================
//Output:This str is: H
//==========================================================================
