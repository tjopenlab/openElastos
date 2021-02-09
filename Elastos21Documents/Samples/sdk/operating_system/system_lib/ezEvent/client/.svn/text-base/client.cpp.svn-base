//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : This program shows how to use methods of CSystem::FindRunningObject
//                and CEvent::New.
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

#define EVENT_NAME L"event"

Int32 main(Int32 argc, char **argv)
{
    ECode ec;
    IEvent *pEvent = NULL;
    WaitResult pResult;
    EventState pState;//The notification state to be received

    //Find the registered IEvent interface
    ec = CSystem::FindRunningObject(EVENT_NAME, (IInterface **)&pEvent);
    if (FAILED(ec)) {
        fprintf(stderr, "Find service event failed. ec = 0x%08x\n", ec);
        return -1;
    }
    printf("Find service IEvent.\n");

    //Wait for the notification
    pEvent->Wait(&pResult, &pState);
    printf("Now the state is %ld\n", pState);

    pEvent->Release();
    return 0;
}
