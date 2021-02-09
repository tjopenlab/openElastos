//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates blocking the calling thread
//               until a thread terminates or the specified time elapses by
//               usingthe Join method, getting a exitted code for the current
//               thread by using the GetQuitCode method.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

ECode ThreadFunc(void *pArg)
{
    CThread::Sleep(5000, NULL);

    CThread::Quit(1);

    // will not execute here. only want to remove the compiler's complaint...
    return NOERROR;
}

Int32 main(Int32 argc, Int8 *argv[])
{
    ECode ec;
    IThread *iThread = NULL;

    ec = CThread::New(ThreadFunc, 0, ThreadCreationFlag_Started, &iThread);
    if (FAILED(ec)) {
        printf("Create Thread failed, ec = 0x%08x.\n", ec);
        return -1;
    }
    else {
        printf("Create thread successfully.\n");
    }

    iThread->Join(INFINITE, NULL);

    //Get the Quit code.
    Int32 nQuitCode;
    iThread->GetQuitCode(&nQuitCode);
    printf("Thread Quit code is 0x%08x.\n", nQuitCode);

    iThread->Release();
    return 0;
}

//==========================================================================
// Output:
//
//  Create thread successfully.
//  Thread Quit code is 0x00000001.
//
//==========================================================================
