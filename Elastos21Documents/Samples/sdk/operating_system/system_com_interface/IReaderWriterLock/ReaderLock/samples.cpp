//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : This program shows how to use methods of IReaderWriterLock
//                ReaderLock and ReaderUnlock.
//==========================================================================

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

// Shared Data
char g_szShared[20] = "Hello.";

// Reader Thread
ECode ReaderFunc(void* arg)
{
    Int32 nReader = (Int32)(arg);

    // Gets a reader lock and prints the shared data.
    WaitResult wr;
    g_iLock->ReaderLock(&wr);
    for (Int32 i = 0; i < 10;++i) {
        printf("Reader %d: %s\n", nReader, g_szShared);
        CThread::Sleep(500, NULL);
    }
    g_iLock->ReaderUnlock();

    return NOERROR;
}

// The main function, also the main thread.
Int32 main()
{
    ECode ec;
    IThread* iReader1;
    IThread* iReader2;

    // Creates a ReaderWriterLock.
    ec = CReaderWriterLock::New(&g_iLock);
    if (FAILED(ec)) {
        HandleError("Create ReaderWriterLock failed", ec);
        return 1;
    }

    // Creates reader 1 thread.
    ec = CThread::New(ReaderFunc, (void*)1, 0, &iReader1);
    if (FAILED(ec)) {
        HandleError("Create reader1 thread failed", ec);
        g_iLock->Release();
        return 1;
    }

    // Creates reader 2 thread.
    ec = CThread::New(ReaderFunc, (void*)2, 0, &iReader2);
    if (FAILED(ec)) {
        HandleError("Create reader2 thread failed", ec);
        iReader1->Release();
        g_iLock->Release();
        return 1;
    }

    // Joins child threads.
    iReader1->Join(INFINITE, NULL);
    iReader2->Join(INFINITE, NULL);

    // Releases objects.
    iReader1->Release();
    iReader2->Release();
    g_iLock->Release();

    return 0;
}

//==========================================================================
//OutPut:
//
//   Reader 1: Hello.
//   Reader 2: Hello.
//   Reader 1: Hello.
//   Reader 2: Hello.
//   Reader 1: Hello.
//   Reader 2: Hello.
//   Reader 1: Hello.
//   Reader 2: Hello.
//   Reader 1: Hello.
//   Reader 2: Hello.
//   Reader 1: Hello.
//   Reader 2: Hello.
//   Reader 1: Hello.
//   Reader 2: Hello.
//   Reader 1: Hello.
//   Reader 2: Hello.
//   Reader 1: Hello.
//   Reader 2: Hello.
//   Reader 1: Hello.
//   Reader 2: Hello.
//==========================================================================
