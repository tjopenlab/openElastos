//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : This program shows how to use the methods of ICondition
//                TryWait and PulseAll.
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

    //Test the variable. If g_nCount is 0, wake up all the waiting threads
    if (g_nCount == 0) {
        printf("Condition changed, notifies one waiting thread.\n");
        g_pCond->PulseAll();
    }

    g_nCount++;

    g_pMutex->Unlock();
    return NOERROR;
}

ECode Decrement(void *pArg)
{
    g_pMutex->Lock(&wr);

    //Test the variable. If g_nCount is 0, try to wait for the condititon
    //for 1 second.
    if (g_nCount == 0) {
        printf("Condition is not meet, thread starts to wait.\n");
        g_pCond->TryWait(g_pMutex, 1000, &wr);
    }
    printf("Condition is meet, thread continues executing.\n");

    g_nCount--;

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

    //Create 2 threads that run the Decrement function
    //and 1 thread that runs the Increment function
    CThread::New(Decrement, 0, 0, NULL);
    CThread::New(Decrement, 0, 0, NULL);
    CThread::New(Increment, 0, 0, NULL);

    //Waite for all the threads to finish
    CThread::Sleep(2000, NULL);
    printf("Count :%d\n", g_nCount);

Exit:
    if(g_pMutex) g_pMutex->Release();
    if(g_pCond) g_pCond->Release();
    return 0;
}
//==========================================================================
//OutPut:
//
//Condition is not meet, thread starts to wait.
//Condition is not meet, thread starts to wait.
//Condition changed, notifies one waiting thread.
//Condition is meet, thread continues executing.
//Condition is meet, thread continues executing.
//Count :-1
//==========================================================================
