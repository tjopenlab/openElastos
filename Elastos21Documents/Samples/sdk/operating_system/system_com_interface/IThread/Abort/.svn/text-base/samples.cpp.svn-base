//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates terminating the thread by
//               using the Abort method of the IThread interface.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

void CheckThreadState(IThread *iThread)
{
    if (NULL == iThread) return;

    //Gets the state of the associated thread
    ThreadState threadState;
    ECode ec = iThread->GetState(&threadState);
    if (FAILED(ec)) {
        printf("Get thread state failed, ec = 0x%08x.\n", ec);
        return;
    }

    switch (threadState) {
        case ThreadState_Running:
            printf("The child thread is Running.\n");
            break;
        case ThreadState_Sleeping:
            printf("The child thread is Sleeping.\n");
            break;
        case ThreadState_Suspended:
            printf("The child thread is Suspended.\n");
            break;
        case ThreadState_Finished:
            printf("The child thread is Finished.\n");
            break;
        case ThreadState_Unstarted:
            printf("The child thread is Unstarted.\n");
            break;
        default:
            printf("Error. threadState = 0x%x.\n", threadState);
            break;
    }

    return;
}

ECode ThreadFunc(void *pArg)
{
    ECode ec;
    IThread *iThread = CThread::GetCurrent();

    CheckThreadState(iThread);

    printf("Suspend the thread.\n");
    //Suspends the thread
    ec = iThread->Suspend();
    if (FAILED(ec)) {
        printf("Suspend the thread failed, ec = 0x%08x.\n", ec);
        return ec;
    }

    printf("this line can not be printed.\n");

    return ec;
}

Int32 main(Int32 argc, Int8 **argv)
{
    ECode ec;
    IThread *iThread;

    ec = CThread::New(ThreadFunc, 0, ThreadCreationFlag_Started, &iThread);
    if (FAILED(ec)) {
        printf("Create thread failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    //Let the child thread to execute
    CThread::Sleep(1000, NULL);

    //Get the state of the child thread after child been suspended
    CheckThreadState(iThread);

    //Abort thread
    ec = iThread->Abort();
    if (FAILED(ec)) {
        printf("Abort thread failed, ec = 0x%08x.\n", ec);
        iThread->Release();
        return -1;
    }

    printf("Abort the thread successfully.\n");

    //Now get the state again.
    CheckThreadState(iThread);

    iThread->Release();
    return 0;
}

//==========================================================================
// Output:
//
//  The child thread is Running.
//  Suspend the thread.
//  The child thread is Suspended.
//  Abort the thread successfully.
//  The child thread is Finished.
//
//==========================================================================
