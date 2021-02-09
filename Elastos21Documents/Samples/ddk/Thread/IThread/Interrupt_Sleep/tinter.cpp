//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : 这个程序演示了IThread的Interrupt和Sleep方法。
//==========================================================================

#include <ddk.h>

INT ThreadFunc(void *pArg)
{
    //Sleep all the time, wait to be interrupted
    DzSleep();

    return NOERROR;
}


ECode DoInterrupt()
{
    ECode ec;
    IThread *pThread = NULL;

    ec = DzCreateKernelThread(ThreadFunc, 0, 0, PriorityRank_Normal, &pThread);
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%08x\n", ec);

        return ec;
    }

    DzSleep(1000, NULL);//let the new thread go first

    //Interrupt the thread
    ec = pThread->Interrupt();
    if (FAILED(ec)) {
        kprintf("Thread interrupt failed, ec = 0x%08x\n", ec);

        goto Exit;
    }
    kprintf("Interrupt thread successfully.\n");

    ec = pThread->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        kprintf("Join thread failed, the ec = 0x%08x\n", ec);
    }

Exit:
    if (pThread) {
        pThread->Release();
    }

    return ec;
}
