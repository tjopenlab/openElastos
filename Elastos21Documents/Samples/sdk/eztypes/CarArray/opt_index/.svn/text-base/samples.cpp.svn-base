//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
//  Description : The following example demonstrates how to use [] to visit
//                the elements of the array.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    BufferOf_<Int32, 10> MyArray;

    Int32 i;
    for (i = 0; i < 10; i++)
        MyArray[i] = i;

    for (i = 0; i < 10; i++) {
        CConsole::Write(MyArray[i]);
        CConsole::Write("  ");
    }

    return 0;
}

//==========================================================================
//Output
//
//    0  1  2  3  4  5  6  7  8  9
//==========================================================================
