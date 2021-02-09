//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description: This program shows how to use methods CSystem::FindRunningObject and
//                CCondition::New.
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

#define MUTEX_NAME L"mutex"
#define COND_NAME L"cond"

Int32 main(Int32 argc, char **argv)
{
    ECode ec;
    IMutex *pMutex = NULL;
    ICondition *pCond = NULL;

    //Find the registered IMutex interface
    ec = CSystem::FindRunningObject(MUTEX_NAME, (IInterface **)&pMutex);
    if (FAILED(ec)) {
        printf("Find service mutex failed. ec = 0x%08x\n", ec);
        return -1;
    }
    printf("Find service IMutex\n");

    //Find the registered ICondition interface
    ec = CSystem::FindRunningObject(COND_NAME, (IInterface **)&pCond);
    if (FAILED(ec)) {
        printf("Find service condition failed. ec = 0x%08x\n", ec);
        goto ErrExit;
    }
    printf("Find service ICondition\n");

    //Enter the critical section
    WaitResult wr;
    pMutex->Lock(&wr);
    //Pulse one waiting process
    printf("Client: Pulse the condition\n");
    pCond->Pulse();
    //Leave the critical section
    pMutex->Unlock();

ErrExit:
    if (pMutex) pMutex->Release();
    if (pCond) pCond->Release();
    return 0;
}
