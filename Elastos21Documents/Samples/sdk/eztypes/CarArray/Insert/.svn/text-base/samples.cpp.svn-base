//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates how to insert datas into
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
    CConsole::WriteLine("Before Insert,myArray:");
    for (Int32 i = 0; i < myArray.GetCapacity(); i++) {
        CConsole::WriteLine(myArray[i]);
    }
    CConsole::Write("The used of myArray is : ");
    CConsole::WriteLine(myArray.GetUsed());

    myArray.Insert(3, array2, 2);
    CConsole::Write("After Insert,myArray:");
    for (Int32 j = 0; j < myArray.GetCapacity(); j++) {
        CConsole::WriteLine(myArray[j]);
    }
    CConsole::Write("The used of myArray is : ");
    CConsole::WriteLine(myArray.GetUsed());

    return 0;
}

//==========================================================================
//Output
//
//    Before Insert,myArray:
//    0
//    1
//    2
//    3
//    4
//    5
//    The used of myArray is : 6.
//    After Insert,myArray:
//    0
//    1
//    2
//    8
//    9
//    3
//    The used of myArray is : 6.
//==========================================================================
