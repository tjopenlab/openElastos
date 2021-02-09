//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates how to replace datas into
//                the appoint position.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    Int32 array1[6] = {0, 1, 2, 3, 4, 5};
    Int32 array2[2] = {8, 9};
    BufferOf_<Int32, 6> myArray;

    myArray.Copy(array1, 6);
    CConsole::WriteLine("Before Replace, myArray:");
    for (Int32 i = 0; i < myArray.GetCapacity(); i++) {
        CConsole::WriteLine(myArray[i]);
    }

    myArray.Replace(3, array2, 2);
    CConsole::WriteLine("After Replace, myArray:");
    for (Int32 j = 0; j < myArray.GetCapacity(); j++) {
        CConsole::WriteLine( myArray[j]);
    }

    return 0;
}

//==========================================================================
//Output
//
//    Before Replace, myArray:
//    0
//    1
//    2
//    3
//    4
//    5
//    After Replace, myArray:
//    0
//    1
//    2
//    8
//    9
//    5
//==========================================================================
