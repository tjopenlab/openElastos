//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description: The following example demonstrates waitting for the associated
//              process to exit by using method WaitForExit of interface IProcess.
//
//===========================================================================

#include <elastos.h>
#include <stdio.h>
using namespace Elastos;

Int32 main()
{
    ECode ec;
    IProcess *iProc;

    // creates a process object
    ec = CProcess::New(&iProc);
    if (FAILED(ec)) {
        printf("Create process object failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    // start a process
    ec = iProc->Start(L"Hello.exe", NULL);
    if (FAILED(ec)) {
        printf("Start process failed, ec = 0x%08x.\n", ec);
        iProc->Release();
        return -1;
    }

    printf("Start a process: hello.exe\n");

    // wait for the process to exit
    WaitResult wr;
    ec = iProc->WaitForExit(INFINITE, &wr);
    if (SUCCEEDED(ec)) {// && WaitResult_OK == wr){
        printf("Process has exited.\n");
        printf("wr = %08x\n",wr);
    }
    else {
        printf("problem in the process of WaitForExit\n");
        printf("wr = %08x\n",wr);
    }
    iProc->Release();

    return 0;
}

//===========================================================================
// Output:
//
//Start a process: hello.exe
//Hello,world
//Process has exited.
//wr = 00000000
//
//===========================================================================
