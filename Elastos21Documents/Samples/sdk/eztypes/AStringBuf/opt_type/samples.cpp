//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use operator datatypes of AStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 printASB(AString as)
{
	CConsole::Write("Calling (AString): ");
	CConsole::WriteLine(as);

	return 0;
}

Int32 printCHAR(char *as)
{
	CConsole::Write("Calling (char *): ");
	CConsole::WriteLine(as);

	return 0;
}

Int32 main()
{
    AStringBuf_<12> as;
    as.Copy("Hello,world!");
    printCHAR(as);
    printASB(as);

    return 0;
}

//==========================================================================
//Output:Calling (char *): Hello,world!
//       Calling (AString): Hello,world!
//==========================================================================
