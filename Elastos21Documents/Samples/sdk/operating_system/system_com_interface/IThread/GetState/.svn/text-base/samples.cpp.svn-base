//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description: The following demonstrates getting a value containing the
//              states of the current thread by using the GetState method of
//              the IThread interface.
//==========================================================================

#include <elastos.h>
#include <stdio.h>
using namespace Elastos;

ECode ThreadFunc(void *pArg)
{
    CThread::Sleep(2000, NULL);

    printf("Child thread will exit.\n");
    return NOERROR;
}

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

Int32 main(Int32 argc, Int8 *argv[])
{
    ECode ec;
    IThread *iThread;

    //Create an unstared child thread
    ec = CThread::New(ThreadFunc, 0, ThreadCreationFlag_Unstarted, &iThread);
    if (FAILED(ec)) {
        printf("Create Thread failed, ec = 0x%08x.\n", ec);
        return -1;
    }
    else {
        printf("Create thread successfully.\n");
    }

    CheckThreadState(iThread);

    ec = iThread->Start();
    if (FAILED(ec)) {
        printf("Start Thread failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    CheckThreadState(iThread);

    //Waits for the child thread to exit
    iThread->Join(INFINITE, NULL);

    CheckThreadState(iThread);

    iThread->Release();
    return 0;
}

//==========================================================================
// Output:
//
//  Create thread successfully.
//  The child thread is Unstarted.
//  The child thread is Running.
//  Child thread will exit.
//  The child thread is Finished.
//
//==========================================================================
