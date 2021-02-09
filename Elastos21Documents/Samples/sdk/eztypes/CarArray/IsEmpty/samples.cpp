//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
//  Description : The following example demonstrates how to judge the
//                data region of CarArray object is empty or not.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    BufferOf<Int32> myArray(NULL, 0);
    if (!myArray.IsEmpty()) {
        CConsole::WriteLine("myArray is not Empty.");
    }
    else {
        CConsole::WriteLine("myArray is Empty.");
    }

    BufferOf_<Int32, 4> myArray1;
    myArray1.SetUsed(0);
    if (!myArray1.IsEmpty()) {
        CConsole::WriteLine("myArray1 is not Empty.");
    }
    else {
        CConsole::WriteLine("myArray1 is Empty.");
    }

    Int32 array[4] = {0, 1, 2, 3};
    myArray1.Copy(array, 4);
    CConsole::Write("After coping,the used of myArray1 is : ");
    CConsole::WriteLine(myArray1.GetUsed());
    if (!myArray1.IsEmpty()) {
        CConsole::WriteLine("Now, myArray1 is not Empty.");
    }
    else {
        CConsole::WriteLine("Now, myArray1 is still Empty.");
    }

    return 0;
}

//==========================================================================
//Output
//
//    myArray is Empty.
//    myArray1 is Empty.
//    After coping,the used of myArray1 is : 4
//    Now, myArray1 is not Empty.
//==========================================================================
