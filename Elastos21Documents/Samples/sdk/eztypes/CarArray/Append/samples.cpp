//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates appending datas at the
//               end of the used data region of the cararray object.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    Int32 array1[10] = {0, 1, 2, 3};
    Int32 array2[4] = {4, 5, 6, 7};
    Int32 array3[2] = {8, 9};

    BufferOf<Int32> myArray(array1, 10, 4);
    BufferOf<Int32> myArray1(array3, 2);
    CConsole::WriteLine("Before Append,myArray is:");
    for (Int32 i = 0; i < myArray.GetUsed(); i++) {
        CConsole::WriteLine(myArray[i]);
    }
    CConsole::Write("The used of myArray is : ");
    CConsole::WriteLine(myArray.GetUsed());

    myArray.Append(array2, 4);
    CConsole::WriteLine("After Append array2,myArray is:");
    for (Int32 j = 0; j < myArray.GetUsed(); j++) {
        CConsole::WriteLine(myArray[j]);
    }
    CConsole::Write("The used of myArray is : ");
    CConsole::WriteLine(myArray.GetUsed());

    myArray.Append(&myArray1);
    CConsole::WriteLine("After Append myArray1,myArray is:");
    for (Int32 k = 0; k < myArray.GetUsed(); k++) {
        CConsole::WriteLine(myArray[k]);
    }
    CConsole::Write("The used of myArray is : ");
    CConsole::WriteLine(myArray.GetUsed());

    return 0;
}

//==========================================================================
//Output:
//
//    Before Append,myArray:
//    0
//    1
//    2
//    3
//    The used of myArray is : 4.
//    After Append array2,myArray is:
//    0
//    1
//    2
//    3
//    4
//    5
//    6
//    7
//    The used of myArray is : 8.
//    After Append myArray1,myArray is:
//    0
//    1
//    2
//    3
//    4
//    5
//    6
//    7
//    8
//    9
//    The used of myArray is : 10.
//==========================================================================
