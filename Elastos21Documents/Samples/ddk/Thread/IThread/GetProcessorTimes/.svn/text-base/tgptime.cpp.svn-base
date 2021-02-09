//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : This sample demonstrates how to use GetProcessorTimes.
//
//==========================================================================

#include <ddk.h>

INT ThreadFunc(void *pArg)
{
    // wait for 5 seconds
    DzSleep(5000, NULL);

    return NOERROR;
}


ECode DoGetProcessTime()
{
    IThread *pThread = NULL;
    ECode ec = NOERROR;
    int nUserTime = 0;
    int nPrivilegedTime = 0;

    // Create a kernel thread
    ec = DzCreateKernelThread(ThreadFunc, 0, 0, PriorityRank_Normal, &pThread);
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%08x\n", ec);
        goto Exit;
    }

    // Waits for the thread to terminate
    ec = pThread->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        kprintf("Join failed. ec = 0x%08x\n", ec);
        goto Exit;
    }

    // Get the time that the thread has spent on utilizing the CPU.
    ec = pThread->GetProcessorTimes(&nUserTime, &nPrivilegedTime);
    if (FAILED(ec)) {
        kprintf("GetFinishCode failed. ec = 0x%08x\n", ec);
        goto Exit;
    }

    kprintf("nUserTime = %d, nPrivilegedTime = %d\n", \
            nUserTime, nPrivilegedTime);

Exit:
    if (pThread) {
        pThread->Release();
    }

    return ec;
}
