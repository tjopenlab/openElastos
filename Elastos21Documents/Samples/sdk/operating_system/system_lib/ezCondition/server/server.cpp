//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : This program shows how to use methods CSystem::FindRunningObject and
//                CCondition::New.
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

#define MUTEX_NAME L"mutex"
#define COND_NAME L"cond"

Int32 main(Int32 argc, char **argv)
{
    IMutex *pMutex = NULL;
    ICondition *pCond = NULL;
    IProcess *pProcess = NULL;
    ECode ec;
    WaitResult wr;

    //Create a named mutex
    ec = CMutex::New(MUTEX_NAME, &pMutex, NULL);
    if (FAILED(ec)) {
        printf("Create named mutex failed. ec = 0x%08x\n", ec);
        return -1;
    }
    printf("Create named mutex object %S\n", (wchar_t *)MUTEX_NAME);

    //Create a named condition
    ec = CCondition::New(COND_NAME, &pCond, NULL);
    if (FAILED(ec)) {
        printf("Create named condition failed. ec = 0x%08x\n", ec);
        goto ErrExit;
    }
    printf("Create named condition object %S\n", (wchar_t *)COND_NAME);

    //Enter the critical section
    printf("Server: Acquire the mutex\n");
    pMutex->Lock(&wr);

    ec = CProcess::New(L"ncondt_c.exe", NULL, &pProcess);
    if (FAILED(ec)) {
        printf("Create client process failed.ec = 0x%08x\n", ec);
        goto ErrExit;
    }

    //Wait for client find server
    CThread::Sleep(500, NULL);

    printf("Server: Wait for the condition\n");
    //Release the mutex, wait for child process's notification
    pCond->Wait(pMutex, &wr);
    printf("Server: Condition is meet\n");
    //Leave the critical section
    pMutex->Unlock();
    printf("Server: Release the mutex\n");

    // wait for the process exit
    pProcess->WaitForExit(INFINITE, &wr);
    pProcess->Release();

ErrExit:
    if (pMutex) {
        pMutex->Release();
        CSystem::UnregisterRunningObject(MUTEX_NAME);
    }
    if (pCond) {
        pCond->Release();
        CSystem::UnregisterRunningObject(COND_NAME);
    }
    return 0;
}

//==========================================================================
//Output:
//
//    Create named mutex object mutex
//    Create named condition object cond
//    Server: Acquire the mutex
//    Find service IMutex
//    Find service ICondition
//    Server: Wait for the condition
//    Client: Pulse the condition
//    Server: Condition is meet
//    Server: Release the mutex
//==========================================================================
