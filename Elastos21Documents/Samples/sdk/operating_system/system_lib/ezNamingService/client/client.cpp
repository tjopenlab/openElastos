//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  :  In the client part,this sample shows how to use
//                 CSystem::WaitForRunningObject to wait for register of the service
//                 component and how to use CSystem::FindRunningObject to use the service
//                 which has already registered.
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
    IHello * pIHello;   // declare IHello interface pointer
    IEvent * pIEvent;   // declare IEvent interface pointer
    WaitResult pResult;

    // Create server process
    ec = CProcess::New(
                L"nameservice_s.exe", NULL, NULL);
    if (FAILED(ec)) {
        printf("Create server process failed. ec = 0x%08x\n", ec);
        return 1;
    }
    else
        printf("CreateServerProcess\n");

    // wait for register of the component named hello
    ec = CSystem::WaitForRunningObject(L"hello", INFINITE, &pResult);
    if (FAILED(ec)) {
        printf("WaitForHelloError\n");
        return 1;
    }
    else
        printf("WaitForHello\n");

    //wait for register of the component named event
    ec = CSystem::WaitForRunningObject(L"event", INFINITE, &pResult);
    if (FAILED(ec)) {
        printf("WaitForEventError\n");
        return 1;
    }
    else
        printf("WaitForEvent\n");

    // find the service through the string ¡°hello¡±
    ec = CSystem::FindRunningObject(L"hello", (IInterface**)&pIHello);
    if (FAILED(ec)) {
        printf("FindHelloError\n");
        return 1;
    }
    else {
        printf("FindHello\n");
        // remote call the functiong Hello£¬print¡±Hello, world¡±
        pIHello->Hello(L"Hello,world\n");
        pIHello->Release();   // release pIHello pointer
    }

    // find the service through the string ¡°event¡±
    ec = CSystem::FindRunningObject(L"event", (IInterface**)&pIEvent);
    if (FAILED(ec)) {
        printf("FindEventError\n");
        return 1;
    }
    else {
        printf("FindEvent\n");

        // wake the server process up by function notify
        pIEvent->Notify(1);
        pIEvent->Release();   // release pIEvent pointer
    }
    return 0;
}


