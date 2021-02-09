//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description: The following example demonstrates the main thread waitting
//              for the child thread to exit.
//
//==========================================================================

#include <elastos.h>
#include <stdio.h>
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

    IThread *iThread = NULL;
    ECode ec = NOERROR;

    //Create a child thread
    ec = CThread::New(ThreadFunc, 0, ThreadCreationFlag_Started, &iThread);
    if (FAILED(ec)) {
        printf("CThread::New failed.\n");
        return -1;
    }
    else {
        printf("Create thread successfully.\n");
    }

    printf("Wait for the child thread to exit ...\n");

    WaitResult wr;
    ec = iThread->Join(INFINITE, &wr);
    if (SUCCEEDED(ec) && WaitResult_OK == ec) {
        printf("Thread exited.\n");
    }

    iThread->Release();

    return 0;
}

//==========================================================================
// Output:
//
//  Create thread successfully.
//  Wait for the child thread to exit ...
//  thread is running ...
//  thread is running ...
//  thread is running ...
//  thread is running ...
//  thread is running ...
//  Thread exited.
//
//==========================================================================
