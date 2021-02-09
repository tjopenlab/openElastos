//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description: The following example demonstrates creating a process object
//              and starting a process with command line arguments.
//
//==========================================================================

#include <elastos.h>
#include <stdio.h>
using namespace Elastos;

Int32 main()
{
    ECode           ec;
    IProcess       *iProc;

    //creates a process object
    ec = CProcess::New(&iProc);
    //starts a process (hello.exe) with command line arguments
    if (FAILED(ec)){
        printf("Create Process Object  failed, ec = 0x%08x\n", ec);
    }
    ec = iProc->Start(L"hello.exe", NULL);
    if (FAILED(ec)) {
        printf("Start¡¡process  failed, ec = 0x%08x\n", ec);
        iProc->Release();
        return -1;
    }

    //waits for the process to exit
    WaitResult wr;
    ec = iProc->WaitForExit(INFINITE, &wr);
//    if (FAILED(ec) || WaitResult_OK != wr) {
//        printf("Wait for process to exit failed, ec = 0x%08x\n", ec);
//    }
    if (SUCCEEDED(ec)) {
        printf("Wait for process to exit succeed\n");
    }
    else
        printf("Wait for process to exit failed, ec = 0x%08x\n", ec);
    iProc->Release();

    return 0;
}

//==========================================================================
// Output:
//  Hello, world
//  Wait for process to exit succeed
//
//==========================================================================
