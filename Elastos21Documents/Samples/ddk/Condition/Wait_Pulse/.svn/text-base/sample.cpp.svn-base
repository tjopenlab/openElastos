//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : 这个程序演示了Condition的Wait和Pulse方法的使用。
//==========================================================================

#include <ddk.h>

//Global variable, to be tested
unsigned int g_nCount = 0;

//Global pointer to IMutex
DzMutex *g_pMutex = NULL;

//Global pointer to ICondition
DzCondition *g_pCond = NULL;

ECode DoCreate()
{
    g_pMutex = new DzMutex();
    if (NULL == g_pMutex) {
        kprintf("Create mutex failed\n");
        return E_FAIL;
    }

    g_pCond = new DzCondition();
    if (NULL == g_pCond) {
        kprintf("Create condition failed\n");
        delete g_pMutex;

        return E_FAIL;
    }

    return NOERROR;
}

//Thread routine for the first thread
ECode Increment(void *pArg)
{
    WaitResult wr;
    
    g_pMutex->Lock(&wr);

    //Test the variable. If g_nCount is 0, wake up one waiting thread
    if (0 == g_nCount) {
        kprintf("Condition changed, notify one waiting thread.\n");
        g_pCond->Pulse();
    }

    g_nCount++;

    g_pMutex->Unlock();

    return NOERROR;
}

//Thread routine for the second thread
ECode Decrement(void *pArg)
{
	WaitResult wr;
    g_pMutex->Lock(&wr);

    //Test the variable. If g_nCount is 0, wait for the condititon
    while (0 == g_nCount) {
        kprintf("Condition is not meet, thread starts to wait.\n");
        g_pCond->Wait(g_pMutex, &wr);
    }
    
    kprintf("Condition is meet, thread continues executing.\n");

    g_nCount--;

    g_pMutex->Unlock();

    return NOERROR;
}

ECode DoMain()
{
    ECode ec;
    IThread *pDecThread = NULL;
    IThread *pIncThread = NULL;

    ec = DoCreate();
    if (FAILED(ec)) {
        kprintf("Create Mutex and Condition failed. ec = 0x%08x\n", ec);
        return ec;
    }

    //Create the decrement thread
    ec = DzCreateKernelThread(Decrement, 0, 0, PriorityRank_Normal, &pDecThread);
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    DzSleep(1000, NULL);

    //Create the increment thread
    ec = DzCreateKernelThread(Increment, 0, 0, PriorityRank_Normal, &pIncThread);
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    ec = pDecThread->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        kprintf("Join failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    ec = pIncThread->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        kprintf("Join failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    //g_nCount should be still 0
    kprintf("Now the g_nCount = %d\n", g_nCount);

Exit:
    if (g_pMutex) {
        delete g_pMutex;
    }

    if (g_pCond) {
        delete g_pCond;
    }

    if (pIncThread) {
        pIncThread->Release();
    }

    if (pDecThread) {
        pDecThread->Release();
    }

    return ec;
}
