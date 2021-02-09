//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates how to use copy
//               constructer of cararray
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    Int32 array1[4] = {0, 1, 2, 3};

    BufferOf<Int32> array2(array1, 4, 4);

    CConsole::WriteLine("CarArray array2:");

    for (Int32 i = 0; i < array2.GetCapacity(); i++) {
        CConsole::WriteLine(array2[i]);
    }
    CConsole::Write("CarArray array2 used: ");
    CConsole::WriteLine(array2.GetUsed());

    return 0;
}

//==========================================================================
//Output
//
//    CarArray array2:
//    0
//    1
//    2
//    3
//    CarArray array2 used: 4

//==========================================================================
