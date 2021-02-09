//=============================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//=============================================================================

//=============================================================================
//
// Description : The following example demonstrates how to use the API
//               _CSystem_CreateSystemEventHandle.
//
//=============================================================================

#include <elastos.h>
#include <stdio.h>
#include <time.h>
using namespace Elastos;

//
// Child Thread entry point
//
ECode ThreadFunc(void *pArg)
{
    SystemTime tm, tmnew;
    ECode ec = NOERROR;

    //Let the new thread sleep for 1 second
    ec = CThread::Sleep(1000, NULL);
    if (FAILED(ec)) {
        printf("Failed to sleep.\n");
        return ec;
    }
    else
        printf("succeed to sleep the new thread!\n");

    // Gets the system time
    ec = CSystem::GetMachineTime(&tm);
    if (FAILED(ec)) {
        printf("Failed to get time.\n");
        return ec;
    }

    printf("The system time is %s\n", ctime((const time_t *)&tm));

    // Changes the system time,increase an hour
    tmnew = tm;
    tmnew.seconds += 3600;

    printf("Set time to 1 hour later.\n");

    ec = CSystem::SetMachineTime(tmnew);
    if (FAILED(ec)) {
        printf("Failed to set time.\n");
        return ec;
    }

    // Gets the new system time
    ec = CSystem::GetMachineTime(&tm);
    if (FAILED(ec)) {
        printf("Failed to get time.\n");
        return ec;
    }

    printf("The new system time is %s\n", ctime((const time_t *)&tm));

    return ec;
}

EXTERN_C int main()
{
    IThread *pIThread = NULL;
    IEvent  *pEvent   = NULL;
    ECode ec = NOERROR;
    WaitResult wr;

    // Gets the interface of system event
    ec = _CSystem_CreateSystemEventHandle(SystemEvent_TimeChanged, &pEvent);
    if (FAILED(ec)) {
        printf("_CSystem_CreateSystemEventHandle Failed.\n");
    }

    // Create a child thread
    CThread::New(ThreadFunc, NULL, NULL, &pIThread);

    //Wait for the system time to change
    pEvent->Wait(&wr,NULL);
    pEvent->Release();

    pIThread->Join(INFINITE, NULL);
    pIThread->Release();

    return 0;
}


//=============================================================================
//output:
//succeed to sleep the new thread!
//The system time is Wed Nov 18 20:38:28 2006
//
//Set time to 1 hour later.
//The new system time is Wed Nov 18 21:38:28 2006
//
//=============================================================================
