//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : This program shows how to use the methods of ICondition
//                Wait and Pulse.
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

//Global variable, to be tested
Int32 g_nCount = 0;

//Global pointer to IMutex
IMutex *g_pMutex = NULL;
WaitResult wr;
//Global pointer to ICondition
ICondition *g_pCond = NULL;

ECode Increment(void *pArg)
{
    g_pMutex->Lock(&wr);
    printf("g_nCount = %d\n",g_nCount);

    //Test the variable. If g_nCount is 0, wake up one waiting thread
    if (g_nCount == 0) {
        printf("Condition changed, notify one waiting thread.\n");
        g_pCond->Pulse();
    }

    g_nCount++;
    printf("g_nCount = %d\n",g_nCount);
    g_pMutex->Unlock();
    return NOERROR;
}

ECode Decrement(void *pArg)
{
    g_pMutex->Lock(&wr);
    printf("g_nCount = %d\n",g_nCount);

    //Test the variable. If g_nCount is 0, wait for the condititon
    if (g_nCount == 0) {
        printf("Condition is not meet, thread starts to wait.\n");
        g_pCond->Wait(g_pMutex, &wr);
    }
    printf("Condition is meet, thread continues executing.\n");

    g_nCount--;
    printf("g_nCount = %d\n",g_nCount);

    g_pMutex->Unlock();
    return NOERROR;
}

Int32 main(Int32 argc, char **argv)
{
    ECode ec;

    //Create the Mutex
    ec = CMutex::New(&g_pMutex);
    if (FAILED(ec)) {
        fprintf(stderr, "Create mutex failed.\n");
        return -1;
    }

    //Create the Condition
    ec = CCondition::New(&g_pCond);
    if (FAILED(ec)) {
        fprintf(stderr, "Create conditon failed.\n");
        goto Exit;
    }

    //Create one thread running the Decrement function,
    //and one thread running the Increment function.
    CThread::New(Decrement, 0, 0, NULL);
    CThread::Sleep(100, NULL);
    CThread::New(Increment, 0, 0, NULL);

    //Wait for child threads to finish.
    CThread::Sleep(2000, NULL);

Exit:
    if(g_pMutex) g_pMutex->Release();
    if(g_pCond) g_pCond->Release();
    return 0;
}

//==========================================================================
//  OutPut:
//
//g_nCount = 0
//Condition is not meet, thread starts to wait.
//g_nCount = 0
//Condition changed, notify one waiting thread.
//g_nCount = 1
//Condition is meet, thread continues executing.
//g_nCount = 0
//==========================================================================
