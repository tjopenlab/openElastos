//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
//  Description : The following example demonstrates how to set the used
//                elements number of the data region of CarArray object.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    Int32 array1[4] = {0, 1, 2, 3};
    Int32 old_used, new_used;

    BufferOf<Int32> myArray(array1, 4, 4);
    old_used = myArray.GetUsed();
    CConsole::Write("Before changed myArray's used is: ");
    CConsole::WriteLine(old_used);

    myArray.SetUsed(2);
    new_used = myArray.GetUsed();
    CConsole::Write("Now myArray's used is: ");
    CConsole::WriteLine(new_used);

    return 0;
}

//==========================================================================
//Output
//
//    Before changed myArray's used is: 4
//    Now myArray's used is: 2
//==========================================================================
