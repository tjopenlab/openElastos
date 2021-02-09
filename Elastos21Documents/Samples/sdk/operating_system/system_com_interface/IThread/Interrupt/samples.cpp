//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description: The following shows the behavior of a running thread when it
//              is interrupted and subsequently gets blocked by using the
//              Interrupt method.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

ECode ThreadFunc(void *pArg)
{
    ECode ec;
    WaitResult wr;

    //Sleep long enough, waits to be interrupted
    ec = CThread::Sleep(5000, &wr);
    if (SUCCEEDED(ec) && WaitResult_Interrupted == wr) {
        printf("Thread is interrupted.\n", ec);
        return ec;
    }

    return ec;
}

Int32 main(Int32 argc, Int8 *argv[])
{
    ECode ec;
    const Int32 nSleepUnit = 500;
    IThread *iThread = NULL;

    ec = CThread::New(ThreadFunc, 0, ThreadCreationFlag_Started, &iThread);
    if (FAILED(ec)) {
        printf("Create Thread failed, ec = 0x%08x.\n", ec);
        return -1;
    }
    else {
        printf("Create thread successfully.\n");
    }

    CThread::Sleep(nSleepUnit, NULL);

    //Interrupt the child thread
    ec = iThread->Interrupt();
    if (FAILED(ec)) {
        printf("Thread interrupt failed, ec = 0x%08x.\n", ec);
        goto Exit;
    }
    else {
        printf("Interrupt thread successfully.\n");
    }

    ec = iThread->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        printf("Wait for child thread failed, ec = 0x%08x.\n", ec);
        goto Exit;
    }

Exit:
    iThread->Release();
    return 0;
}

//==========================================================================
// Output:
//
//Create thread successfully.
//Interrupt thread successfully.
//Thread is interrupted.
//
//==========================================================================
