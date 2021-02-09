//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description  : The following example shows how to use the CThread::New
//                method to create thread, and it also demonstrates the
//                following methods.  £º
//                  CThread::Yield : give up processor
//                  CThread::Delay : make the current process delaying
//                  CThread::Quit : exit the current thread
//                  CThread::GetCurrent : get the thread interface of current
//                            thread object.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

//==============================================================
// Description  : Thread entry point
//==============================================================

ECode ThreadFunc(void *pArg)
{
    ECode ec;
    IThread * iCurThread = NULL;

    // get current thread interface
    iCurThread = CThread::GetCurrent();

    // get thread id
    Int32 nID;
    ec = iCurThread->GetId(&nID);
    if (FAILED(ec)) {
        printf("Get current thread id failed, ec = 0x%08x.\n", ec);
        return ec;
    }

    printf("Child thread[%d] id: 0x%08x.\n", (Int32)pArg, nID);

    // exit thread
    CThread::Quit(0);

    // will not execute here. only want to remove the compiler's complaint...
    return ec;
}

EXTERN_C Int32 main()
{
    ECode ec;
    IThread * iCurThread = NULL;

    // get current thread interface
    iCurThread = CThread::GetCurrent();

    // get thread id
    Int32 nID;
    ec = iCurThread->GetId(&nID);
    if (FAILED(ec)) {
        printf("Get current thread id failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    // create then threads
    Int32 i;
    for (i = 0; i < 10; i++) {
        ec = CThread::New(
            ThreadFunc, (void *)i, ThreadCreationFlag_Started, NULL);
        if (FAILED(ec)) {
            printf("Create thread[%d] failed, ec = 0x%08x.\n", i, ec);
            return -1;
        }
    }

    // give up processor
    CThread::Yield();
    printf("Main thread id: 0x%08x.\n", nID);
    CThread::Delay(10000);

    return 0;
}

//==========================================================================
// Output:
//
//  Main thread id: 0x019b4000.
//  Child thread[0] id: 0x01934000.
//  Child thread[1] id: 0x01948000.
//  Child thread[2] id: 0x01908000.
//  Child thread[3] id: 0x01920000.
//  Child thread[4] id: 0x01910000.
//  Child thread[5] id: 0x01934000.
//  Child thread[6] id: 0x01948000.
//  Child thread[7] id: 0x01908000.
//  Child thread[8] id: 0x01934000.
//  Child thread[9] id: 0x01948000.
//
//==========================================================================
