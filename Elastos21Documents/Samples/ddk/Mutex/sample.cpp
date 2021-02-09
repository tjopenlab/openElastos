//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : 这个程序演示了Mutex的Lock, TryLock, Unlock和Mutex方法。
//==========================================================================
#include <ddk.h>

ECode DoCreate(DzMutex **ppMutex)
{
    if (NULL == ppMutex) {
        return E_INVALID_ARGUMENT;
    }

    *ppMutex = new DzMutex();
    if (NULL == *ppMutex) {
        kprintf("Create mutex failed\n");
        return E_FAIL;
    }

    return NOERROR;
}

INT ThreadFunc(void *pArg)
{
    DzMutex   *pMutex = NULL;   
    WaitResult wr;

    pMutex = (DzMutex *)pArg;
    if (NULL == pMutex) {
        return E_INVALID_ARGUMENT;
    }

    //Acquire the mutex within 500 ticks
    pMutex->TryLock(500, &wr);

    //Do the synchronized operation
    //......
    kprintf("Mutex is acquired by child thread\n");

    //Done the operation, release the mutex
    pMutex->Unlock();

    return NOERROR;
}

ECode DoFunc(DzMutex *pMutex)
{
    if (NULL == pMutex) {
        return E_INVALID_ARGUMENT;
    }

    //Acquire the mutex       
    WaitResult wr;
    pMutex->Lock(&wr);

    //Do the synchronized operation
    //......
    kprintf("Mutex is acquired by main thread\n");

    //Done the operation, release the mutex
    pMutex->Unlock();

    return NOERROR;
}

ECode DoSynchronize()
{
    ECode ec;
    DzMutex   *pMutex = NULL;
    IThread *pThread;

    ec = DoCreate(&pMutex);
    if (FAILED(ec)) {
        kprintf("Create Mutex failed. ec = 0x%08x\n", ec);
        return ec;
    }

    ec = DzCreateKernelThread(ThreadFunc, (void *)pMutex, 0, PriorityRank_Normal, &pThread);
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    ec = DoFunc(pMutex);
    if (FAILED(ec)) {
        kprintf("Mutex operation failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    ec = pThread->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        kprintf("Join failed. ec = 0x%08x\n", ec);
    }

Exit:
    if (pMutex) {
        delete pMutex;
    }

    if (pThread) {
        pThread->Release();
    }

    return ec;
}
