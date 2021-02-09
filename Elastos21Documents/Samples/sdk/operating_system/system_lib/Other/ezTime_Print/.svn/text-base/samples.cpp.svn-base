//=============================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//=============================================================================

//=============================================================================
// Description  : this example show the usage of API
//                CSystem::GetMachineTime CSystem::DebugPrint and CSystem::SetMachineTime.
//=============================================================================

#include <stdio.h>
#include <time.h>
#include <elastos.h>
using namespace Elastos;

EXTERN_C int main()
{
    ECode ec;
    SystemTime tm1, tm2;

    // get the system time
    ec = CSystem::GetMachineTime(&tm1);
    if (FAILED(ec)) {
        // output debug information to console
        CSystem::DebugPrint(L"Failed to get time.\n");
        printf("ECode is 0x%08x\n", ec);
        return 1;
    }

    printf("The time is %s\n", ctime((const time_t *)&tm1));

    // set the system time, increase an hour
    tm2 = tm1;
    tm2.seconds += 3600;

    CSystem::DebugPrint(L"Set time to 1 hour later.\n");

    ec = CSystem::SetMachineTime(tm2);
    if (FAILED(ec)) {
        CSystem::DebugPrint(L"Failed to set time.\n");
        printf("ECode is 0x%08x\n", ec);
        return 1;
    }

    // get current time again
    ec = CSystem::GetMachineTime(&tm1);
    if (FAILED(ec)) {
        CSystem::DebugPrint(L"Failed to get time.\n");
        printf("ECode is 0x%08x\n", ec);
        return 1;
    }

    printf("The time is %s\n", ctime((const time_t *)&tm1));

    return 0;
}


//=============================================================================
//output:
//The time is Wed Nov 18 20:38:28 2006
//
//Set time to 1 hour later.
//The time is Wed Nov 18 21:38:28 2006
//=============================================================================
