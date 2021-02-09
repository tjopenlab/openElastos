//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use operator datatypes of WStringBuf.
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 printWSB(WString as)
{
	CConsole::Write("Calling (WString): ");
	CConsole::WriteLine(as);

	return 0;
}

Int32 printWCHAR(wchar_t *as)
{
	CConsole::Write("Calling (WCHAR *): ");
	CConsole::WriteLine(as);

	return 0;
}


Int32 main()
{
    WStringBuf_<12> as;
    as.Copy(L"Hello,world!");
    printWCHAR(as);
    printWSB(as);

    return 0;
}

//==========================================================================
//Output:Calling (WCHAR *): Hello,world!
//       Calling (WString): Hello,world!
//==========================================================================
