//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
//  Description : The following example demonstrates how to judge the
//                data region of CarArray object is empty or null.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    BufferOf<Int32> myArray(NULL, 0);
    if (!myArray.IsNullOrEmpty()) {
        CConsole::WriteLine("myArray is not NULL or Empty.");
    }
    else {
        CConsole::WriteLine("myArray is NULL or Empty.");
    }

    BufferOf_<Int32, 4> myArray1;
    myArray1.SetUsed(0);
    if (!myArray1.IsNullOrEmpty()) {
        CConsole::WriteLine("myArray1 is not NULL or Empty.");
    }
    else {
        CConsole::WriteLine("myArray1 is NULL or Empty.");
    }

    return 0;
}

//==========================================================================
//Output
//
//    myArray is NULL or Empty.
//    myArray1 is NULL or Empty.
//==========================================================================
