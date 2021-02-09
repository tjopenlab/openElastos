//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates how to creat a BufferOf<Int32>
//               object at heap, remember release the memory using Dispose
//               function when you don't use the object.
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

    Int32 pBuf[] = {1, 2, 3};
    pMyArray = BufferOf<Int32>::Alloc(pBuf, 3);
    i = pMyArray->GetCapacity();
    CConsole::Write("MyArray's Length = ");
    CConsole::WriteLine(i);
    BufferOf<Int32>::Free(pMyArray);

    pMyArray = BufferOf<Int32>::Alloc(pBuf, 10, 3);
    i = pMyArray->GetCapacity();
    CConsole::Write("MyArray's Length = ");
    CConsole::WriteLine(i);
    BufferOf<Int32>::Free(pMyArray);

    return 0;
}

//==========================================================================
//Output MyArray's Length = 10
//       MyArray's Length = 3
//       MyArray's Length = 10
//==========================================================================
