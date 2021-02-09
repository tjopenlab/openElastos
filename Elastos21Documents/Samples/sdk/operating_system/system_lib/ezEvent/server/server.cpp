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
    IEvent *pEvent = NULL;
    IProcess *pProcess = NULL;
    ECode ec;

    //Create a named event
    ec = CEvent::New(EVENT_NAME, FALSE, FALSE, &pEvent, NULL);
    if (FAILED(ec)) {
        fprintf(stderr, "Create named event failed. ec = 0x%08x\n", ec);
        return -1;
    }
    printf("Creates named event object %S\n", (wchar_t *)EVENT_NAME);

    //Create a child process
    ec = CProcess::New(L"event_c.exe", NULL, &pProcess);
    if (FAILED(ec)) {
        fprintf(stderr, "Create client process failed.ec = 0x%08x\n", ec);
        goto EXIT;
    }

    //Sleep for 2 seconds, child thread waits for the event
    WaitResult wr;
    CThread::Sleep(2000, &wr);
    //Notify
    pEvent->Notify(5);

    pProcess->Release();
EXIT:
    pEvent->Release();
    CSystem::UnregisterRunningObject(EVENT_NAME);
    return 0;
}

//==========================================================================
//OutPut:
//
//   Creates named event object event
//   Find service IEvent.
//   Now the state is 5
//==========================================================================
