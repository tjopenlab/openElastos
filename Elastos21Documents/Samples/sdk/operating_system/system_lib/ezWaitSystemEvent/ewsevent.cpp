//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================


//==========================================================================
//
// Description : The following example demonstrates how to use the API
//               EzWaitSystemEvent.
//
//==========================================================================


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

    // Gets the system time
    ec = CSystem::GetMachineTime(&tm);
    if (FAILED(ec)) {
        printf("Failed to get time.\n");
        return ec;
    }

    printf("The system time is %s\n", ctime((const time_t *)&tm));

    // Change the system time
    tmnew = tm;
    tmnew.seconds += 3600; // increase an hour

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
    SystemEvent *pSysEvent = NULL;
    IThread     *pIThread  = NULL;
    ECode ec = NOERROR;

    // Create a child thread
    CThread::New(ThreadFunc, NULL, NULL, &pIThread);

    // Wait for the system time to change
    ec = EzWaitSystemEvent(SystemEvent_TimeChanged, pSysEvent);
    if (FAILED(ec)) {
        printf("EzWaitSystemEvent Failed.\n");
    }

    pIThread->Join(INFINITE, NULL);
    pIThread->Release();

    return 0;
}

