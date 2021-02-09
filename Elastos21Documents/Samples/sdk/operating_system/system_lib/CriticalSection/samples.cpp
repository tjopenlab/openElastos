//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : This program shows how to use methods realted
//                to CriticalSection.
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

#define THREADCOUNT 10

// global critical section variable
CRITICAL_SECTION g_cs;

// protected resource
Int32 g_num = 0;

// thread entry point
ECode ThreadFunc(void *pArg)
{
    for (Int32 i = 0; i < 5; i++) {
        // access the protected resource
        _CCriticalSection_Enter(&g_cs);
        g_num++;
        _CCriticalSection_Leave(&g_cs);
    }

    return NOERROR;
}

Int32 main(Int32 argc, char **argv)
{
    ECode ec;
    Int32 i;
    IThread * pThreads[THREADCOUNT];

    // init IThread array
    for (i = 0; i < THREADCOUNT; i++) {
        pThreads[i] = NULL;
    }

    // init critical section
    ec = _CCriticalSection_Initialize (&g_cs);
    if (FAILED(ec)) {
        printf("Init critical section failed, ec = 0x%08x\n", ec);
        return -1;
    }

    // create threads
    for (i = 0; i < THREADCOUNT; i++) {
        ec = CThread::New(ThreadFunc,
                            NULL,
                            ThreadCreationFlag_Started,
                            &pThreads[i]);
        if (FAILED(ec)) {
            printf("Error creating thread, ec = 0x%08x\n", ec);
            goto ErrExit;
        }
    }

    // wait for threads' exit
    for (i = 0; i < THREADCOUNT; i++) {
        pThreads[i]->Join(INFINITE, NULL);
    }

    if (g_num == 5 * THREADCOUNT) {
        printf("Protected resource was protected.\n");
    }
    else {
        printf("Protected resource was not protected.\n");
    }

ErrExit:

    // free thread
    for (i = 0; i < THREADCOUNT; i++) {
        if (pThreads[i]) {
            pThreads[i]->Release();
        }
    }

    // delete critical section
    _CCriticalSection_Terminate(&g_cs);

    return 0;
}

//==========================================================================
//Output:
//
//    Protected resource was protected.
//==========================================================================
