//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : This program shows how to use the methods of IEvent
//                TryWait.
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

void HandleError(const char* msg, ECode ec)
{
    printf("%s (ec = 0x%08x)\n", msg, ec);
}

Int32 main()
{
    ECode ec;
    IEvent*  iEvent;
    EventState dwState;
    WaitResult wr;
    // Creates event, cleared automatically, initial not signaled.
    ec = CEvent::New(FALSE, FALSE, &iEvent);
    if (FAILED(ec)) {
        HandleError("Create event failed", ec);
        return 1;
    }

    // Makes a notification.
    iEvent->Notify(1);

    // Tries to wait for notification the first time.
    printf("Try to wait for notification for 2000 ms...\n");
    ec = iEvent->TryWait(2000, &wr, &dwState);
    if (NOERROR == ec && WaitResult_OK == wr) {
        printf("Receives the notification, state is %d, "
            "the event is cleared automatically.\n", dwState);
    }
    else if (NOERROR == ec && WaitResult_TimedOut == wr) {
        printf("TryWait timeout\n");
    }
    else {
        HandleError("TraWait failed", ec);
    }

    // Tries to wait for notification the second time.
    printf("Try to wait for notification for 2000 ms again...\n");
    ec = iEvent->TryWait(2000, &wr, &dwState);
    if (NOERROR == ec && WaitResult_OK == wr) {
        printf("Receives the notification, state is %d, "
            "the event is cleared automatically.\n", dwState);
    }
    else if (NOERROR == ec && WaitResult_TimedOut == wr) {
        printf("TryWait timeout\n");
    }
    else {
        HandleError("TraWait failed", ec);
    }

    // Releases objects.
    iEvent->Release();

    return 0;
}

//==========================================================================
//OutPut:
//
//   Try to wait for notification for 2000 ms...
//   Receives the notification, state is 1, the event is cleared automatically.
//   Try to wait for notification for 2000 ms again...
//   TryWait timeout
//==========================================================================
