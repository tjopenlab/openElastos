//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
//==========================================================================
// Description:This program shows how to use the method "GetPayload".
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    BufferOf_<Int32, 4> MyArray;
    for (Int32 i = 0; i < 4; i++) {
        MyArray[i] = i;
    }
    Int32 *p = MyArray.GetPayload();

    CConsole::WriteLine("MyArray is");
    for (Int32 j = 0; j < 4; j++) {
    	CConsole::WriteLine(MyArray[j]);
    }

    CConsole::WriteLine("p is");
    for (Int32 k = 0; k < 4; k++) {
    	CConsole::WriteLine(p[k]);
    }

    return 0;
}

//==========================================================================
//Output:
//       MyArray is
//       0
//       1
//       2
//       3
//       p is
//       0
//       1
//       2
//       3
//==========================================================================
