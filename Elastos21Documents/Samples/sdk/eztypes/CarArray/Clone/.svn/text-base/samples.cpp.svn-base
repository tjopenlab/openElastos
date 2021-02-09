//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates acquiring a deep copy of
//               CarArray object,copy CarArray array at heap,you should use
//               Dispose function to release the memory when you don't use
//               the CarArray object.
//
//==========================================================================

#include <elastos.h>
using namespace Elastos;

int main()
{
    BufferOf_<Int32, 50> a;
    a[12] = 321;

    BufferOf<Int32> *pb = a.Clone();
    CConsole::Write("The length of b after clone is ");
    CConsole::WriteLine(pb->GetCapacity());
    CConsole::Write("b[12] = ");
    CConsole::WriteLine((*pb)[12]);

    BufferOf<Int32>::Free(pb);

    return 0;
}

//==========================================================================
//Output:The length of b after clone is 50
//       b[12] = 321
//
//==========================================================================
