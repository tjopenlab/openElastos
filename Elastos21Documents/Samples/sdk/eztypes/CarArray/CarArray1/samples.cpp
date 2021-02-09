//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates how to construct a
//               cararray object using an array,and setup the length and
//               used length with the same value
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    Int32 * array1 = new (Int32 [4]);

    for (Int32 i = 0; i < 4; i++) {
        array1[i] = i;
    }
    CConsole::WriteLine("Array array1:");
    for (Int32 j = 0; j < 4; j++) {
        CConsole::WriteLine(array1[j]);
    }

    BufferOf<Int32> array2(array1, 4);
    CConsole::WriteLine("CarArray array2 construct by array array1.");
    CConsole::WriteLine("CarArray array2:");
    for (Int32 k = 0; k < array2.GetCapacity(); k++) {
        CConsole::WriteLine(array2[k]);
    }
    CConsole::Write("CarArray array2 used: ");
    CConsole::WriteLine(array2.GetUsed());

    delete array1;

    Int32 array3[6] = {4, 5, 6, 7, 8, 9};
    CConsole::Write("Array array3:\n");
    for (Int32 m = 0; m < 6; m++) {
        CConsole::WriteLine(array3[m]);
    }
    BufferOf<Int32> array4(array3, 4);
    CConsole::WriteLine("CarArray array4 construct by array array3.");
    CConsole::WriteLine("CarArray array4:");
    for (Int32 n = 0; n < array4.GetCapacity(); n++) {
        CConsole::WriteLine(array4[n]);
    }
    CConsole::Write("CarArray array4 used: ");
    CConsole::WriteLine(array4.GetUsed());

    return 0;
}

//==========================================================================
//Output
//
//    Array array1:
//    0
//    1
//    2
//    3
//    CarArray array2 construct by array array1.
//    CarArray array2:
//    0
//    1
//    2
//    3
//    CarArray array2 used: 4
//    Array array3:
//    4
//    5
//    6
//    7
//    8
//    9
//    CarArray array4 construct by array array3.
//    CarArray array4:
//    4
//    5
//    6
//    7
//    CarArray array4 used: 4
//==========================================================================
