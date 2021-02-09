//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================


//==========================================================================
//
// Description :This sample demonstrates how to get the state of the thread.
//
//==========================================================================
#include <ddk.h>

INT ThreadFunc(void *pArg)
{
    // Suspends the execution of the current thread
    DzSleep();

    return NOERROR;
}

ECode DoGetState()
{
    IThread     *pThread = NULL;
    ECode     ec = NOERROR;
    ThreadState thdState;

    // Create a kernel thread
    ec = DzCreateKernelThread(ThreadFunc, 0, 0, PriorityRank_Normal, &pThread);
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%08x\n", ec);
        return ec;
    }

    // Gets the state of the thread
    ec = pThread->GetState(&thdState);
    if (SUCCEEDED(ec)) {
        if (ThreadState_Sleeping == thdState) {
            kprintf("The thread is sleeping.\n");
        }
    }
    else {
        kprintf("GetState failed. ec = 0x%08x\n", ec);
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
