//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates how to construct Cararray
//               object,and allot memory on stack for the object.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    BufferOf_<Int32, 10> MyArray;

    Int32 i = MyArray.GetCapacity();
    CConsole::Write("MyArray's Length = ");
    CConsole::WriteLine(i);

    return 0;
}

//==========================================================================
//Output:MyArray's Length = 10
//==========================================================================
