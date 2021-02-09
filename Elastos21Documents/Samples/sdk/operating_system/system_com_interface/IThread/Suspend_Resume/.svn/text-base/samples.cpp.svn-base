//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//===========================================================================
//
// Description: The following example demonstrates suspending the thread by
//              using the Suspend method and resume a thread that has been
//              suspended by using the Resume method of the IThead interface.
//
//============================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

ECode ThreadFunc(void *pArg)
{
    ECode ec;
    IThread *iThread = CThread::GetCurrent();

    //Suspend the thread
    printf("Thread will be suspended.\n");
    ec = iThread->Suspend();
    if (FAILED(ec)) {
        printf("Suspend thread failed. ec = 0x%08x.\n", ec);
        return ec;
    }

    return ec;
}

Int32 main(Int32 argc, Int8 *argv[])
{
    ECode ec;
    const Int32 nSleepUnit = 2000;
    IThread *iThread;

    //Create a child thread
    ec = CThread::New(ThreadFunc, 0, ThreadCreationFlag_Started, &iThread);
    if (FAILED(ec)) {
        printf("Create Thread failed, ec = 0x%08x.\n", ec);
        return -1;
    }
    else {
        printf("Create thread successfully.\n");
    }

    CThread::Sleep(nSleepUnit, NULL);

    //Resume the suspended thread
    ec = iThread->Resume();
    if (FAILED(ec)) {
        printf("Resume thread failed, ec = 0x%08x.\n", ec);
        iThread->Release();
        return -1;
    }
    else {
        printf("Thread is resumed.\n");
    }

    iThread->Join(INFINITE, NULL);

    iThread->Release();
    return 0;
}

//==========================================================================
// Output:
//
//  Create thread successfully.
//  Thread will be suspended.
//  Thread is resumed.
//
//==========================================================================
