//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : 这个程序演示了IThread的GetStartTime和GetFinishTime方法。
//==========================================================================
#include <ddk.h>

ECode GetRunTime()
{
    ECode ec;
    IThread *pThread = NULL;

    ec = DzGetCurrentThread(&pThread);
    if (FAILED(ec)) {
        kprintf("GetCurrentThread failed. ec = 0x%08x\n", ec);

        return ec;
    }

    //Get the starting time
    SystemTime etStartTime;
    ec = pThread->GetStartTime(&etStartTime);
    if (FAILED(ec)) {
       kprintf("GetStartTime failed. ec = 0x%08x\n", ec);

       goto Exit;
    }
    kprintf("Thread starts at time %lu.\n", etStartTime.m_seconds);

    //Get the finishing time
    SystemTime etFinishTime;
    ec = pThread->GetFinishTime(&etFinishTime);
    if (FAILED(ec)) {
       kprintf("GetFinishTime failed. ec = 0x%08x\n", ec);

       goto Exit;
    }
    kprintf("Thread finishes at time %lu.\n", etFinishTime.m_seconds);

Exit:
    if (pThread) {
        pThread->Release();
    }

    return ec;
}
