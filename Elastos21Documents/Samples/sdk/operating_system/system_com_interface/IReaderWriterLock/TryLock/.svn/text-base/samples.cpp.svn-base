//==============================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==============================================================================

//==============================================================================
// Description  : This program shows how to use the methods of IReaderWriterLock
//                WriterTryLock and ReaderTryLock.
//==============================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

// Error Handler
void HandleError(const char* msg, ECode ec)
{
    printf("%s (ec = 0x%08x)\n", msg, ec);
}

// ReaderWriterLock Object
IReaderWriterLock*  g_iLock;

//==============================================================================
// Description  : Thread Function
//                Repeats to try to get a reader lock each 50 ms
//                until succeeding. Prints the shared data.
//                Then exits.
//==============================================================================
ECode MyThreadFunc(void* arg)
{
    ECode ec = NOERROR;
    WaitResult wr;
    while (1) {

        // Tries to get the reader lock.
        ec = g_iLock->ReaderTryLock(100, &wr);

        // Succeeds. Prints the shared data.
        if (NOERROR == ec && WaitResult_OK == wr) {
            printf("Thread ReaderTryLock succeeded.\n");
            CThread::Sleep(1000, NULL);
            printf("Thread ReaderUnlock.\n");
            g_iLock->ReaderUnlock();
            break;
        }
        // Timeout, try again.
        else if (NOERROR == ec && WaitResult_TimedOut == wr) {
            printf("Thread ReaderTryLock timeout.\n");
        }
        // Error, exits.
        else {
            HandleError("Thread ReaderTryLock failed.", ec);
            break;
        }
    }

    return ec;
}

//==============================================================================
// Description  : The main function, also the main thread.
//                Repeats to try to get a writer lock each 50 ms
//                until succeeding. Prints the shared data.
//                Then exits.
//==============================================================================
Int32 main()
{
    ECode ec;
    IThread* iThread;
    WaitResult wr;

    // Creates a ReaderWriterLock.
    ec = CReaderWriterLock::New(&g_iLock);
    if (FAILED(ec)) {
        HandleError("Create ReaderWriterLock failed", ec);
        return 1;
    }

    // Create a child thread.
    ec = CThread::New(MyThreadFunc, 0, 0, &iThread);
    if (FAILED(ec)) {
        HandleError("Create thread failed", ec);
        g_iLock->Release();
        return 1;
    }

    while (1) {

        // Tries to get the writer lock.
        ec = g_iLock->WriterTryLock(50, &wr);

        // Succeeds. Prints the shared data.
        if (NOERROR == ec && wr == WaitResult_OK) {
            printf("Main WriterTryLock succeeded.\n");
            CThread::Sleep(1000, NULL);
            printf("Main WriterUnlock\n");
            g_iLock->WriterUnlock();
            break;
        }
        // Timeout, try again.
        else if (NOERROR == ec && WaitResult_TimedOut == wr) {
            printf("Main WriterTryLock timeout.\n");
        }
        // Error, exits.
        else {
            HandleError("Main WriterTryLock failed.", ec);
            break;
        }
    }

    // Joins child thread.
    iThread->Join(INFINITE, NULL);

    // Release objects.
    iThread->Release();
    g_iLock->Release();

    return 0;
}

//==============================================================================
//OutPut:
//
//   Main WriterTryLock succeeded.
//   Thread ReaderTryLock timeout.
//   Thread ReaderTryLock timeout.
//   Thread ReaderTryLock timeout.
//   Thread ReaderTryLock timeout.
//   Thread ReaderTryLock timeout.
//   Thread ReaderTryLock timeout.
//   Thread ReaderTryLock timeout.
//   Thread ReaderTryLock timeout.
//   Thread ReaderTryLock timeout.
//   Thread ReaderTryLock timeout.
//   Main WriterUnlock.
//   Thread ReaderTryLock succeeded.
//   Thread ReaderUnlock.
//==============================================================================
