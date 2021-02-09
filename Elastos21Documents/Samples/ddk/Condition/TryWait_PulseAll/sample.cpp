//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : This sample demonstrates how to use Condition::TryWait and
//               Condition::PulseAll
//
//==========================================================================


#include <ddk.h>

//Global variable, to be tested
int g_nCount = 0;

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
        delete g_pMutex;
        kprintf("Create condition failed\n");
        return E_FAIL;
    }

    return NOERROR;
}

ECode  Increment(void *pArg)
{
    WaitResult wr;
    g_pMutex->Lock(&wr);


    //Test the variable. If g_nCount is 0, wake up all the waiting threads
    if (g_nCount == 0) {
        kprintf("Condition changed, notifies one waiting thread.\n");
        g_pCond->PulseAll();
    }

    g_nCount++;

    g_pMutex->Unlock();
    return NOERROR;
}

ECode Decrement(void *pArg)
{
   	WaitResult wr;
    g_pMutex->Lock(&wr);

    //Test the variable. If g_nCount is 0, try to wait for the condititon
    //for 1 second.
    while (g_nCount == 0) {
        kprintf("Condition is not meet, thread starts to wait.\n");
        g_pCond->TryWait(g_pMutex, 1000, &wr);
    }

    kprintf("Condition is meet, thread continues executing.\n");

    g_nCount--;

    g_pMutex->Unlock();
    return NOERROR;
}

ECode DoMain()
{
    ECode ec;
    IThread *pDecThread1 = NULL;
    IThread *pDecThread2 = NULL;
    IThread *pIncThread = NULL;

    ec = DoCreate();
    if (FAILED(ec)) {
        kprintf("Create Mutex and Condition failed. ec = 0x%08x\n", ec);

        return ec;
    }

    //Create the decrement thread
    ec = DzCreateKernelThread(Decrement, (void *)1, 0, PriorityRank_Normal, &pDecThread1);
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    //Create the decrement thread
    ec = DzCreateKernelThread(Decrement, (void *)2, 0, PriorityRank_Normal, &pDecThread2);
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

    ec = pDecThread1->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        kprintf("Join failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    ec = pDecThread2->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        kprintf("Join failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    ec = pIncThread->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        kprintf("Join failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    //g_nCount should be -1
    kprintf("Now the g_nCount = %d\n", g_nCount);

Exit:
    if (g_pMutex) {
        delete g_pMutex;
        g_pMutex = NULL;
    }

    if (g_pCond) {
        delete g_pCond;
        g_pCond = NULL;
    }

    if (pIncThread) {
        pIncThread->Release();
    }

    if (pDecThread1) {
        pDecThread1->Release();
    }

    if (pDecThread2) {
        pDecThread2->Release();
    }

    return ec;
}
