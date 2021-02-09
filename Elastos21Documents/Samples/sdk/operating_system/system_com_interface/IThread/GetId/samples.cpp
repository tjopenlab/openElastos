//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates getting the unique identifier
//               of the current process by using GetId method of the IThread
//               interface.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

ECode ThreadFunc(void *pArg)
{
    CThread::Sleep(2000, NULL);

    return NOERROR;
}

Int32 main(Int32 argc, Int8 *argv[])
{
    ECode ec;
    IThread *iThread = NULL;

    //Create a child thread
    ec = CThread::New(ThreadFunc, 0, ThreadCreationFlag_Started, &iThread);
    if (FAILED(ec)) {
        printf("Create Thread failed, ec = 0x%08x.\n", ec);
        return -1;
    }
    else {
        printf("Create thread successfully.\n");

        Int32 pid;
        //Get the thread id after been created.
        ec = iThread->GetId(&pid);
        if (FAILED(ec)) {
            printf("Get thread id failed, ec = 0x%08x.\n", ec);
        }

        printf("Thread id is %d.\n", pid);
    }

    //Wait for the child to finish
    iThread->Join(INFINITE, NULL);

    iThread->Release();
    return 0;
}

//==========================================================================
// Output:
//
//  Create thread successfully.
//  Thread id is 30253056.
//
//==========================================================================
