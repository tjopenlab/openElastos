//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : This sample shows how to get the time that the thread
//               has spent on utilizing the CPU.
//
//==========================================================================

#include <elastos.h>
#include <stdio.h>
using namespace Elastos;

ECode ThreadFunc(void *pArg)
{
    printf("Child thread is running ...\n");

    Int32 i;
    for (i = 1; i <= 10000; i++) {
        if (i % 1000 == 0) {
            printf("@");
        }
    }

    return NOERROR;
}

Int32 main(Int32 argc, Int8 *argv[])
{
    ECode ec;
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

    //Waits for the child thread to exit
    iThread->Join(INFINITE, NULL);

    //After the thread has exited, Gets the time the associated
    //thread has spent on utilizing the CPU.
    Int32 nPrivilegedTime = 0;
    Int32 nUserTime       = 0;
    ec = iThread->GetProcessorTimes(&nUserTime, &nPrivilegedTime);
    if (FAILED(ec)) {
        printf("\nGet processor time failed, ec = 0x%08x.\n", ec);
    }
    else {
        printf("\nGet processor time successfully.");
        printf("\n UserTime = %dms", nUserTime);
        printf("\n PrivilegedTime = %dms\n", nPrivilegedTime);
    }

    iThread->Release();

    return 0;
}

//==========================================================================
// Output:
//
//Create thread successfully.
//Child thread is running ...
//@@@@@@@@@@
//Get processor time successfully.
//UserTime = 0ms
//PrivilegedTime = 10ms
//
//==========================================================================
