//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description  : The following example demonstrates how to use
//                CreateKernelThread to create a kernel thread and use Join
//                to wait for the kernel thread to terminate.
//
//==========================================================================
#include <ddk.h>

INT ThreadFunc(void *pArg)
{
    DzSleep(DzMillisecondsToTicks((uint_t)pArg), NULL);

    return NOERROR;
}

ECode DoCreate()
{
    ECode ec;
    uint_t iSecs = 2000;
    IThread *pThread = NULL;

    //Create a kernel thread
    ec = DzCreateKernelThread(ThreadFunc, //the thread routine
                            (void *)iSecs, //the parameter
                                           //for the thread routine
                            0, //kernel thread belongs to current process
                            PriorityRank_Normal, //priority rank. no use
                            &pThread);//pointer to the created thread
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%8x\n", ec);
        return ec;
    }

    //Wait fot the kernel thread to terminate
    ec = pThread->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        kprintf("Join failed. ec = 0x%08x\n", ec);
    }

    if (pThread) {
        pThread->Release();
    }

    return ec;
}
