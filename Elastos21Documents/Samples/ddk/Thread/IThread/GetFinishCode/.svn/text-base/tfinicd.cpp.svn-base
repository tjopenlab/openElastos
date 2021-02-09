//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : 这个程序演示了IThread的GetFinishCode方法。
//==========================================================================
#include <ddk.h>

INT ThreadFunc(void *pArg)
{
    DzSleep(5000, NULL);

    return E_FAIL;
}


ECode GetFinishCode()
{
    ECode ec;
    IThread *pThread = NULL;

    ec = DzCreateKernelThread(ThreadFunc, 0, 0, PriorityRank_Normal, &pThread);
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%08x\n", ec);

        return ec;
    }

    ec = pThread->Join(INFINITE, NULL);
    if (FAILED(ec)) {
       kprintf("Join failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    //Get the finish code.
    int nFinishCode;
    ec = pThread->GetFinishCode(&nFinishCode);//receive the finish code
    if (FAILED(ec)) {
        kprintf("GetFinishCode failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    kprintf("The finish code is 0x%08x\n", nFinishCode);

Exit:
    if (pThread) {
        pThread->Release();
    }

    return ec;
}
