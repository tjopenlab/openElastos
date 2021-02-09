//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : 这个程序演示了IMutex的Lock,TryLock和Unlock方法。
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

const int n_sleepUnit = 1000;

ECode ThreadFunc(void *pArg)
{
    IMutex *pMutex;
    pMutex = *(IMutex **)pArg;
    WaitResult wr;

    ECode ec;
    //Try to acquire the mutex within n_sleepUnit interval
    ec = pMutex->TryLock(n_sleepUnit, &wr);
    if (NOERROR == ec) {// && WaitResult_OK == wr) {
        printf("Child thread locks the mutex.\n");
    }
    else if (NOERROR == ec && WaitResult_TimedOut == wr) {
        printf("Time out.\n");
        return ec;
    }
    else {
        fprintf(stderr, "Child thread can not lock the mutex.\n");
        return ec;
    }

    //Sleep after acquiring the mutex
    CThread::Sleep(n_sleepUnit, NULL);

    //Release the mutex
    ec = pMutex->Unlock();
    if (FAILED(ec)) {
        fprintf(stderr, "Thread does not acquire the mutex.\n");
        return ec;
    }
    else {
        printf("Child thread unlock the mutex.\n");
    }

    return ec;
}

int main(int argc, char **argv)
{
    IMutex *pMutex = NULL;
    IThread *pThread = NULL;
    ECode ec;
    WaitResult wr;

    //Create the mutex
    ec = CMutex::New(&pMutex);
    if (FAILED(ec)) {
        fprintf(stderr, "Function failed. ec = 0x%08x.\n", ec);
        return -1;
    }

    ec = CThread::New(ThreadFunc, &pMutex, 0, &pThread);
    if (FAILED(ec)) {
        fprintf(stderr, "Creates child thread failed.\n");
        goto Exit;
    }

    //Acquire the mutex
    ec = pMutex->Lock(&wr);
    if (SUCCEEDED(ec)) {
        printf("Main thread locks the mutex.\n");
    }
    else {
        fprintf(stderr, "Main thread can not lock the mutex.\n");
        goto Exit;
    }

    //Sleep long enough, cause the child thread timed out
    CThread::Sleep(2 * n_sleepUnit, NULL);

    //Release the acquired mutex
    ec = pMutex->Unlock();
    if (FAILED(ec)) {
        fprintf(stderr, "Thread does not acquire the mutex.\n");
        goto Exit;
    }
    else {
        printf("Main thread unlock the mutex.\n");
    }

    pThread->Join(INFINITE, NULL);

Exit:
    if(pMutex) pMutex->Release();
    if(pThread) pThread->Release();
    return 0;
}

/*output:
    Main thread locks the mutex.
    Child thread locks the mutex.
    Thread does not acquire the mutex.
    Main thread unlock the mutex.
*/
