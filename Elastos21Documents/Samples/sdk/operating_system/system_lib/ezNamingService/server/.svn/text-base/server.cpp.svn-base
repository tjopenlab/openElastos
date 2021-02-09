//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  :  In the server part,this sample shows how to use
//                 CSystem::RegisterRunningObject to register service and how to use
//                 CSystem::UnregisterRunningObject to unregister service.
//                 This sample create a new process as server process in the
//                 client process,then the two process can run simultaneously.
//==========================================================================

#include <stdio.h>
#include <eladef.h>
#include <elastos.h>
#include "Hello.h"
using namespace Elastos;

Int32 main()
{
    ECode ec;
    WaitResult pResult;
    IHello *pIHello;     // declare IHello interface pointer
    IEvent *pIEvent;     // declare IEvent interface pointer

    // create a Hello component in this process
    ec = CHello::New(&pIHello);
    if (FAILED(ec)) {
        printf("NewHelloError\n");
        return 1;
    }
    else
        printf("NewHello\n");

    // register name service£¬bind Hello component with the string¡°hello¡±
    ec = CSystem::RegisterRunningObject(L"hello", pIHello);
    if (FAILED(ec)) {
        printf("RegisterHelloError\n");
        pIHello->Release();
        return 1;
    }
    else
        printf("RegisterHello\n");

    // get a kernal Event service through API function
    ec = CEvent::New(true, false, &pIEvent);
    if (FAILED(ec)) {
        printf("CreateEventError\n");
        pIHello->Release();
        return 1;
    }
    else
        printf("CreateEvent\n");

    // register name service£¬bind Event component with the string¡°event¡±
    ec = CSystem::RegisterRunningObject(L"event", pIEvent);
    if (FAILED(ec)) {
        printf("RegisterEventError\n");
        pIHello->Release();
        pIEvent->Release();
        return 1;
    }
    else
        printf("RegisterEvent\n");

    // let the process wait
    pIEvent->Wait(&pResult,NULL);

    // waked by other process, finish waiting,
    // unregister service, release resource
    ec = CSystem::UnregisterRunningObject(L"event");   // unregister Event service
    if (FAILED(ec)) {
        printf("UnregisterEventError\n");
        pIHello->Release();
        pIEvent->Release();
        return 1;
    }
    else {
        printf("UnregisterEvent\n");
        pIEvent->Release();    // release pIEvent pointer
    }
    ec = CSystem::UnregisterRunningObject(L"hello");   // unregister Hello service
    if (FAILED(ec)) {
        printf("UnregisterHelloError\n");
        pIHello->Release();
        return 1;
    }
    else {
        printf("UnregisterHello\n");
        pIHello->Release();    // release pIHello pointer
    }
    return 0;
}

//==========================================================================
//OutPut:
//  CreateServerProcess
//  NewHello
//  WaitForHello
//  RegisterHello
//  CreateEvent
//  WaitForEvent
//  RegisterEvent
//  FindHello
//  Hello,world
//  FindEvent
//  UnregisterEvent
//  UnregisterHello
//==========================================================================
