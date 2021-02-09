//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : Delete the BufferOf<Int32> object which created by Alloc or
//               clone, and release the memory.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    BufferOf<Int32> *pMyArray = BufferOf<Int32>::Alloc(10);

    Int32 i = pMyArray->GetCapacity();
    CConsole::Write("MyArray's Length = ");
    CConsole::WriteLine(i);

    BufferOf<Int32>::Free(pMyArray);

    return 0;
}

//==========================================================================
//Output
//
//    MyArray's Length = 10.
//==========================================================================
