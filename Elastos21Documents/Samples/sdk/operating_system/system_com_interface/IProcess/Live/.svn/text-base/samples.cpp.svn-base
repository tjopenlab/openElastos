//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates creating a process, and
//               checking whether the process is alive with IsAlive and
//               killing a process
//
//==========================================================================

#include <elastos.h>
#include <stdio.h>
using namespace Elastos;

Int32 main()
{
    ECode ec;

    // Creates a process
    IProcess *iProc;
    ec = CProcess::New(L"hello.exe", NULL, &iProc);
    if (FAILED(ec)) {
        printf("Create process failed, ec = 0x%08x\n", ec);
        return -1;
    }

    // Check whether the process still alvie
    Boolean bIsLived;
    ec = iProc->IsAlive(&bIsLived);
    if (SUCCEEDED(ec) && bIsLived) {
        printf("Process is alive.\n");
    }
    else {
        printf("Process has exited.\n");
    }

    // Kill the process
    ec = iProc->Kill();
    if (SUCCEEDED(ec)) {
        printf("Process has been killed.\n");
    }

    // Check again
    ec = iProc->IsAlive(&bIsLived);
    if (SUCCEEDED(ec) && bIsLived) {
        printf("Process is alive.\n");
    }
    else {
        printf("Process is dead.\n");
    }

    iProc->Release();

    return 0;
}

//==========================================================================
// Output:
//
//  Process is alive.
//  Process has been killed.
//  Process is dead.
//
//==========================================================================
