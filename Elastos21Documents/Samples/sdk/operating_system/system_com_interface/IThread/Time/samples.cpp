//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : The following example demonstrates the GetStartTime method
//               and the GetQuitTime method of the IThread interface .
//
//==========================================================================

#include <stdio.h>
#include <elastos.h>
#include <time.h>
using namespace Elastos;

ECode ThreadFunc(void *pArg)
{
    CThread::Sleep(5000, NULL);
    return NOERROR;
}

Int32 main(Int32 argc, Int8 *argv[])
{
    ECode ec;
    IThread *iThread = NULL;

    //Create a child thread
    ec = CThread::New(
        ThreadFunc, 0, ThreadCreationFlag_Started, &iThread);
    if (FAILED(ec)) {
        printf("Create thread failed, ec = 0x%08x.\n", ec);
        return -1;
    }
    else {
        printf("Create thread successfully.\n");
        CThread::Sleep(500, NULL);

        //Get the starting time
        SystemTime startTime;
        ec = iThread->GetStartTime(&startTime);
        if (FAILED(ec)) {
        }
        else {
            printf("Thread start at time : %s",
                ctime((const time_t *)&startTime.seconds));
        }
    }

    iThread->Join(INFINITE, NULL);

    //Get the exitting time
    SystemTime quitTime;
    iThread->GetQuitTime(&quitTime);
    printf("Thread exitted at time %s", ctime((const time_t *)&quitTime.seconds));

    iThread->Release();
    return 0;
}

//==========================================================================
// Output:
//
//  Create thread successfully.
//  Thread start at time : Wed May 23 18:07:22 2007
//  Thread exitted at time Wed May 23 18:07:27 2007
//
//==========================================================================
