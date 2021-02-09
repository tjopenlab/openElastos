//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//===========================================================================
//
// Description : The following example demonstrates getting the thread priority
//               by using the GetPriority method , setting the thread
//               priority by using the SetPriority method.
//
//============================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

Int8 esPriority[][16] = {
                        "Lowest",
                        "BelowNormal",
                        "Normal",
                        "AboveNormal",
                        "Highest"
                    };

ECode ThreadFunc(void *pArg)
{
    CThread::Sleep(5000, NULL);
    return NOERROR;
}

Int32 main(Int32 argc, Int8 *argv[])
{
    ECode ec;
    IThread *iThread = NULL;

    ec = CThread::New(ThreadFunc, 0, ThreadCreationFlag_Started, &iThread);
    if (FAILED(ec)) {
        printf("Create thread failed, ec = 0x%08x.\n", ec);
        return -1;
    }
    else {
        printf("Create thread successfully.\n");
    }

    //Get the priority
    ThreadPriority threadPrior;
    ec = iThread->GetPriority(&threadPrior);
    if (FAILED(ec)) {
        printf("Get thread priority failed, ec = 0x%08x.\n", ec);
        goto Exit;
    }
    printf("Thread priority is %s.\n", esPriority[(threadPrior + 1) / 256]);

    //Set the highest priority for child thread.
    ec = iThread->SetPriority(ThreadPriority_Highest);
    if (FAILED(ec)) {
        printf("Set thread priority failed, ec = 0x%08x.\n", ec);
        goto Exit;
    }

    printf("Set thread priority successfully.\n");

    //Get the priority
    ec = iThread->GetPriority(&threadPrior);
    if (FAILED(ec)) {
        printf("Get thread priority failed, ec = 0x%08x.\n", ec);
        goto Exit;
    }
    printf("Thread priority is %s.\n", esPriority[(threadPrior + 1) / 256]);

    //Waits for the child thread to exit
    iThread->Join(INFINITE, NULL);

Exit:
    iThread->Release();
    return 0;
}

//==========================================================================
// Output:
//
//  Create thread successfully.
//  Thread priority is Normal.
//  Set thread priority successfully.
//  Thread priority is Highest.
//
//==========================================================================
