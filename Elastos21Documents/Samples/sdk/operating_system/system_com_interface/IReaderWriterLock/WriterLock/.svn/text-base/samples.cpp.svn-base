//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  :This program shows how to use the methods of IReaderWriterLock
//               WriterLock and WriterUnlock.
//==============================================================

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

// Writer Thread
ECode WriterFunc(void* arg)
{
    WaitResult wr;
    for (Int32 i = 0; i < 10;++i) {
        // Gets the writer lock and modifies the shared data.
        g_iLock->WriterLock(&wr);
        sprintf(g_szShared, "Hello (%d).", i);
        printf("Writer: %s\n", g_szShared);
        g_iLock->WriterUnlock();

        // Sleeps for a while and gives a chance to readers.
        CThread::Sleep(500, NULL);
    }

    return NOERROR;
}

// Reader Thread
ECode ReaderFunc(void* arg)
{
    Int32 nReader = reinterpret_cast<Int32>(arg);
    WaitResult wr;
    for (Int32 i = 0; i < 10;++i) {
        // Prints the shared data.
        g_iLock->ReaderLock(&wr);
        printf("Reader %d: %s\n", nReader, g_szShared);
        g_iLock->ReaderUnlock();

        // Sleeps for a while and gives a chance to the writer.
        CThread::Sleep(500, NULL);
    }

    return NOERROR;
}

Int32 main()
{
    ECode ec;
    IThread* iWriter;
    IThread* iReader1;
    IThread* iReader2;

    // Creates a ReaderWriterLock.
    ec = CReaderWriterLock::New(&g_iLock);
    if (FAILED(ec)) {
        HandleError("Create ReaderWriterLock failed", ec);
        return 1;
    }

    // Creates the writer thread.
    ec = CThread::New(WriterFunc, 0, 0, &iWriter);
    if (FAILED(ec)) {
        HandleError("Create writer thread failed", ec);
        g_iLock->Release();
        return 1;
    }

    // Creates the reader 1 thread.
    ec = CThread::New(ReaderFunc, (void*)1, 0, &iReader1);
    if (FAILED(ec)) {
        HandleError("Create reader1 thread failed", ec);
        iWriter->Release();
        g_iLock->Release();
        return 1;
    }

    // Creates the read 2 thread.
    ec = CThread::New(ReaderFunc, (void*)2, 0, &iReader2);
    if (FAILED(ec)) {
        HandleError("Create reader2 thread failed", ec);
        iWriter->Release();
        iReader1->Release();
        g_iLock->Release();
        return 1;
    }

    // Join child threads.
    iWriter->Join(INFINITE, NULL);
    iReader1->Join(INFINITE, NULL);
    iReader2->Join(INFINITE, NULL);

    // Releases objects.
    iWriter->Release();
    iReader1->Release();
    iReader2->Release();
    g_iLock->Release();

    return 0;
}

//===================================================================
//OutPut:
//
//Writer: Hello (0).
//Reader 1: Hello (0).
//Reader 2: Hello (0).
//Writer: Hello (1).
//Reader 1: Hello (1).
//Reader 2: Hello (1).
//Writer: Hello (2).
//Reader 1: Hello (2).
//Reader 2: Hello (2).
//Writer: Hello (3).
//Reader 1: Hello (3).
//Reader 2: Hello (3).
//Writer: Hello (4).
//Reader 1: Hello (4).
//Reader 2: Hello (4).
//Writer: Hello (5).
//Reader 1: Hello (5).
//Reader 2: Hello (5).
//Writer: Hello (6).
//Reader 1: Hello (6).
//Reader 2: Hello (6).
//Writer: Hello (7).
//Reader 1: Hello (7).
//Reader 2: Hello (7).
//Writer: Hello (8).
//Reader 1: Hello (8).
//Reader 2: Hello (8).
//Writer: Hello (9).
//Reader 1: Hello (9).
//Reader 2: Hello (9).
//======================================================================
