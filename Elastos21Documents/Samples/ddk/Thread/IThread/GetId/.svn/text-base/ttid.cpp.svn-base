//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : This sample demonstrates how to get the current thread
//               and get the id of the thread.
//
//==========================================================================

#include <ddk.h>

ECode GetId()
{
    IThread *pThread = NULL;
    ECode ec       = NOERROR;
    INT     nTid;

    // Gets the current thread
    ec = DzGetCurrentThread(&pThread);
    if (FAILED(ec)) {
        kprintf("GetCurrentThread failed. ec = 0x%08x\n", ec);

        return ec;
    }

    // Gets the id of the thread
    ec = pThread->GetId(&nTid);
    if (FAILED(ec)) {
        kprintf("Get thread id failed. ec = 0x%08x\n", ec);
    }
    else {
        kprintf("The id of the thread is %d\n", nTid);
    }

    if (pThread) {
        pThread->Release();
    }

    return ec;
}
