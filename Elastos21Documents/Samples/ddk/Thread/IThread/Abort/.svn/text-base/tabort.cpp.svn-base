//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================


//==========================================================================
//
// Description  : This sample demonstrates various thread function:
//                CreateKernelThread, Sleep, Abort.
//
//==========================================================================
#include <ddk.h>

INT ThreadFunc(void *pArg)
{
    // Suspends the execution of the current thread
    DzSleep(0, NULL);

    return NOERROR;
}

ECode DoAbort()
{
    IThread     *pThread = NULL;
    ECode     ec = NOERROR;

    // Create a kernel thread
    ec = DzCreateKernelThread(ThreadFunc, 0, 0, PriorityRank_Normal, &pThread);
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%08x\n", ec);
        return ec;
    }

    // Call Abort to terminate the thread
    ec = pThread->Abort();
    if (SUCCEEDED(ec)) {
        kprintf("Abort the thread successfully\n");
    }
    else {
        kprintf("Abort failed. ec = 0x%08x\n", ec);
    }

    pThread->Release();

    return ec;
}
