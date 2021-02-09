//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates how to acquire the used
//                size of the data region of CaArray object.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    BufferOf_<Int32, 4> myArray;
    myArray.SetUsed(4);
    for (Int32 i = 0; i < myArray.GetCapacity(); i++) {
        myArray[i] = i;
    }
    CConsole::Write("The used of myArray is : ");
    CConsole::WriteLine(myArray.GetUsed());

    return 0;
}

//==========================================================================
//Output
//
//    The used of myArray is : 4.
//==========================================================================
