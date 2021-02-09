//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates getting and setting the
//               process priority using GetPriority() method and
//               SetPriority() method.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

Int32 main()
{
    ECode ec;
    IProcess * iProc;

    // get current process
    ec = CProcess::GetCurrent(&iProc);
    if (FAILED(ec)) {
        printf("Get current process failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    // set the process ThreadPriorityRank
    ThreadPriorityRank rkSet = ThreadPriorityRank_SoftRealTime;
    ec = iProc->SetPriorityRank(rkSet);

    if (FAILED(ec)) {
        printf("set the ThreadPriorityRank of process failed, ec = 0x%08x.\n", ec);
        iProc->Release();
        return -1;
    }
    else {
        printf("Process ThreadPriorityRank has been set to SoftRealTime.\n");
    }

    // get the rank
    ThreadPriorityRank rkGet;
    ec = iProc->GetPriorityRank (&rkGet);

    if (FAILED(ec)) {
        printf("get the ThreadPriorityRank of process failed, ec = 0x%08x.\n", ec);
        iProc->Release();
        return -1;
    }
    else {
        printf("Process ThreadPriorityRank is %d.\n", rkGet);
    }

    iProc->Release();
    return 0;
}

//==========================================================================
// Output:
//
//  Process ThreadPriorityRank has been set to SoftRealTime.
//  Process ThreadPriorityRank is 3.
//
//==========================================================================
