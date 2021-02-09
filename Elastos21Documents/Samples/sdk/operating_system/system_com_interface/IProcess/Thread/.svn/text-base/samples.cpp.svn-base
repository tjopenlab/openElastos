//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates setting the capacity in
//               the threadpoor, getting the capacity and the number of idle
//               threads in threadpoor by using GetThreadPoolState method,
//               getting threads in process by using enumeration.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

#define THREADNUM 5

//==============================================================
// Description  : Thread entry point
//==============================================================
ECode ThreadFunc(void *pArg)
{
    // only wait
    CThread::Sleep(1000 * (int)pArg, NULL);
    return NOERROR;
}

void CheckThreadPoolState(IProcess *iProcess)
{
    if (NULL == iProcess) return;

    // get thread pool state
    Int32 capacity, threadNum;
    ECode ec = iProcess->GetThreadPoolState(&capacity, &threadNum);

//    if (FAILED(ec)) {
//        printf("Get threadpool states failed, ec = 0x%08x.\n", ec);
//    }
//    else {
//        printf("Thread pool capacity is %d\n", puCapacity);
//        printf("Now %d threads in the pool\n", pcThreads);
//    }
    if (SUCCEEDED(ec)) {
        printf("Thread pool capacity is %d\n", capacity);
        printf("Now %d threads in the pool\n", threadNum);
     }
     else
        printf("Get threadpool states failed, ec = 0x%08x.\n", ec);

    return;
}

Int32 main()
{
    ECode ec;

    // get current process
    IProcess * iProc = CProcess::GetCurrent();

    //get default threadpool state
    CheckThreadPoolState(iProc);

    // create threads
    Int32 i;
    for (i = 0; i < THREADNUM; i++) {
        ec = CThread::New(
            ThreadFunc, (void *)i, ThreadCreationFlag_Started, NULL);
        if (FAILED(ec)) {
            printf("Create thread%d failed, ec = 0x%08x.\n", i, ec);
            return -1;
        }
    }

    printf("Create %d thread successfuly.\n", i);

    // get all threads
    IObjectEnumerator * iThreads;
    ec = iProc->GetAllThreads ((IObjectEnumerator **)&iThreads);
    if (FAILED(ec)) {
        printf("Get thread enumerator failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    // Reset
    ec = iThreads->Reset();
    if (FAILED(ec)) {
        printf("Thread enumerator Reset failed, ec = 0x%08x.\n", ec);
        iThreads->Release();
        return -1;
    }

    // enumerate threads
    printf("Enumerate threads in the process : \n");
    Boolean bSucceeded;
    ec = iThreads->MoveNext(&bSucceeded);
    while (SUCCEEDED(ec) && bSucceeded) {
        IThread * pThread;
        ec = iThreads->Current((IInterface**)&pThread);
        if (FAILED(ec)) {
            printf("Enumerate current thread failed, ec = 0x%08x.\n", ec);
            iThreads->Release();
            return -1;
        }

        // get thread id
        Int32 nID;
        ec = pThread->GetId(&nID);
        if (FAILED(ec)) {
            printf("get thread id failed, ec = 0x%08x.\n", ec);
            iThreads->Release();
            pThread->Release();
            return -1;
        }

        printf("Thread ID : %d\n", nID);

        pThread->Release();
        ec = iThreads->MoveNext(&bSucceeded);
    }

    iThreads->Release();

    // set thread pool state
    ec = iProc->SetThreadPoolCapacity(8);
    if (FAILED(ec)) {
        printf("Set threadpool states failed, ec = 0x%08x.\n", ec);
        return -1;
    }
    else {
        printf("Set threadpool states successfully.\n");
    }

    // sleep 2 seconds, some thread will exit;
    CThread::Sleep(5000, NULL);

    // get default threadpool state
    CheckThreadPoolState(iProc);

    return 0;
}

//==========================================================================
// Output:
//
//  Thread pool capacity is 3
//  Now 0 threads in the pool
//  Create 5 thread successfuly.
//  Enumerate threads in the process :
//  Thread ID : 31653888
//  Thread ID : 30040064
//  Thread ID : 30056448
//  Thread ID : 30072832
//  Thread ID : 30220288
//  Thread ID : 30236672
//  Set threadpool states successfully.
//  Thread pool capacity is 8
//  Now 5 threads in the pool

//
//==========================================================================
