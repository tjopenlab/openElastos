//==========================================================================
// Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description  : The following example shows how to use the CProcess::AtExit
//                method to do something special before quit a thread.
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

void f(void * p)

{
    printf("@ f ... p = %p\n", p);
}

class CHello {
public:
    ELFUNC_(void) g()
    {
        printf("# g1 ...\n");
    }
};

CHello obj;

ECode ElastosMain(const BufferOf<WString> & argv)
{
    CProcess::AtExit(&obj, &CHello::g);
    CProcess::AtExit(f, NULL);

    return 0;
}


//==========================================================================
// Output:
//  @ f ... p = 00000000
//  # g1 ...
//==========================================================================
