//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : This sample shows how to get the time that the process
//               has spent on utilizing the CPU.
//
//==========================================================================

#include <elastos.h>
#include <stdio.h>
using namespace Elastos;

Int32 main()
{
    ECode ec;
    IProcess * iProc;

    // Gets the current process
    iProc = CProcess::GetCurrent();

    // Gets the time the process has spent on utilizing the CPU.
    Int32 nUserTime = 0;
    Int32 nPrivilegedTime = 0;
    ec = iProc->GetProcessorTimes(&nUserTime, &nPrivilegedTime);
    if (FAILED(ec)) {
        printf("Get processor times failed, ec = 0x%08x.\n", ec);
    }
    else {
        printf("Get processor times successfully.\n");
        printf("UserTime = %d, PrivilegedTime = %d\n", \
                nUserTime, nPrivilegedTime);
    }

    return 0;
}

//==========================================================================
// Output:
//
//  Get processor times successfully.
//  UserTime = 0, PrivilegedTime = 46(variational)
//
//==========================================================================
