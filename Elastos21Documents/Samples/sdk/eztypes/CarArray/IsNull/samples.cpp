//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
//  Description : The following example demonstrates how to judge the
//                data region of CarArray object is null or not.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    BufferOf<Int32> myArray(NULL, 0);
    if (!myArray.IsNull()) {
        CConsole::WriteLine("myArray is not NULL.");
    }
    else {
        CConsole::WriteLine("myArray is NULL.");
    }

    return 0;
}

//==========================================================================
//Output
//
//    myArray is NULL.
//==========================================================================
