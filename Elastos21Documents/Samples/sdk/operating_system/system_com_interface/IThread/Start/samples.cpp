//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//===========================================================================
//
// Description: The following example demonstrates creating a thread object
//              and starting a thread by using the Start method of the IThread
//              interface.
//
//============================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

ECode ThreadFunc(void *pArg)
{
    Int32 i;
    for (i = 0; i < 5; i++) {
        printf("thread is running ...\n");
        CThread::Sleep(1000, NULL);
    }

    return NOERROR;
}

Int32 main(Int32 argc, Int8 *argv[])
{
    ECode ec;
    IThread *iThread;

    ec = CThread::New(ThreadFunc, 0, ThreadCreationFlag_Unstarted, &iThread);
    if (FAILED(ec)) {
        printf("Create thread failed, ec = 0x%08x.\n", ec);
    }
    else {
        printf("Create thread successfully.\n");

        ec = iThread->Start();
        if (FAILED(ec)) {
            printf("Start thread failed, ec = 0x%08x.\n", ec);
        }

        printf("Thread started.\n");
    }

    iThread->Join(INFINITE, NULL);

    printf("Thread run over.\n");
    iThread->Release();
    return 0;
}

//==========================================================================
// Output:
//
//  Create thread successfully.
//  Thread started.
//  thread is running ...
//  thread is running ...
//  thread is running ...
//  thread is running ...
//  thread is running ...
//  Thread run over.
//
//==========================================================================
