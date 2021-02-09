//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : 这个程序演示了IThread的GetPriority和SetPriority方法。
//==========================================================================
#include <ddk.h>

char esPriority[][16] = {
                        "",
                        "Lowest",
                        "BelowNormal",
                        "Normal",
                        "AboveNormal",
                        "Highest"
                    };

ECode DoChangePriority()
{
    ECode ec;
    ThreadPriority threadPrior;
    IThread *pThread = NULL;

    ec = DzGetCurrentThread(&pThread);
    if (FAILED(ec)) {
        kprintf("GetCurrentThread failed. ec = 0x%08x\n", ec);

        return ec;
    }

    //Get the priority
    ec = pThread->GetPriority(&threadPrior);
    if (FAILED(ec)) {
        kprintf("Get thread priority failed.ec = 0x%08x\n", ec);

        goto Exit;
    }
    kprintf("Thread priority is %s\n", esPriority[threadPrior]);

    //Set the priority. If current priority is not the highest,
    //new priority is the highest; if current priority is the highest,
    //new priority is the lowest.
    if (ThreadPriority_Highest != threadPrior)
        ec = pThread->SetPriority(ThreadPriority_Highest);
    else
        ec = pThread->SetPriority(ThreadPriority_Lowest);
    if (FAILED(ec)) {
        kprintf("Set thread priority failed. ec = 0x%08x\n", ec);

        goto Exit;
    }
    kprintf("Set thread priority successfully.\n");

    //Get the priority
    ec = pThread->GetPriority(&threadPrior);
    if (FAILED(ec)) {
        kprintf("Get thread priority failed.ec = 0x%08x\n", ec);

        goto Exit;
    }
    kprintf("Now the new thread priority is %s\n", esPriority[threadPrior]);

Exit:
    if (pThread) {
        pThread->Release();
    }

    return ec;
}
