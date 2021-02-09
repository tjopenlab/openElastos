//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description :  The following  example shows how to get the system time when
//                process was last put into a running state.
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
#include <time.h>
using namespace Elastos;

Int32 main()
{
    ECode ec;
    IProcess * iProc;

    // get current process
    iProc = CProcess::GetCurrent();

    CThread::Sleep(1000 * 2, NULL);

    // get process start time
    SystemTime startTime = {0, 0};
    ec = iProc->GetStartTime(&startTime);
    if (FAILED(ec)) {
        printf("Get the process start time failed, ec = 0x%08x.\n", ec);
        return -1;
    }

    printf("Process start at time: %s", ctime((const time_t *)&startTime.seconds));

    return 0;
}

//==========================================================================
// Output:
//
//  Process start at time: Tue May 22 17:10:52 2007.
//
//==========================================================================
