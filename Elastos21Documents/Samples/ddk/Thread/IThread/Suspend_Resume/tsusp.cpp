//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : 这个程序演示了IThread的Suspend和Resume方法。
//==========================================================================

#include <ddk.h>

IThread *g_pThread = NULL;

INT ThreadFunc(void *pArg)
{
    ECode ec;

    //Suspend the thread
    kprintf("Thread start to suspend.\n");
    ec = g_pThread->Suspend();
    if (FAILED(ec)) {
        kprintf("Thread Suspend failed. ec = 0x%08x\n", ec);
    }

    return ec;
}

ECode DoResume()
{
    ECode ec;

    ec = DzCreateKernelThread(ThreadFunc, 0, 0, PriorityRank_Normal, &g_pThread);
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%08x\n", ec);

        return ec;
    }

    DzSleep(1000, NULL); //let the new thread go first

    //Resume the suspended thread
    ec = g_pThread->Resume();
    if (FAILED(ec)) {
        kprintf("Thread interrupt failed, ec = 0x%08x\n", ec);

        goto Exit;
    }

    kprintf("Thread resumed\n");

    ec = g_pThread->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        kprintf("Join thread failed. ec = ec = 0x%08x\n", ec);
    }

Exit:
    if (g_pThread) {
        g_pThread->Release();
    }

    return ec;
}
