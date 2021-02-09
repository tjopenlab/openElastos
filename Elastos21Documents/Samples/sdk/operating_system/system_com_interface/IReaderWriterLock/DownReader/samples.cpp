//==========================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : This program shows how to use the methods of IReaderWriterLock
//                DowngradeFromWriter.
//==========================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

// Error Handler
void HandleError(const char* msg, ECode ec)
{
    printf("%s (ec = 0x%08x)\n", msg, ec);
}

// global ReaderWriterLock variable
IReaderWriterLock*  g_iLock;

// Shared Data
char g_szShared[20] = "Uninitialized.";

// Reader Thread
ECode ReaderFunc(void* arg)
{
    // Gets a reader lock and prints the shared data.
    WaitResult wr;
    g_iLock->ReaderLock(&wr);
    printf("Reader: %s\n", g_szShared);
    g_iLock->ReaderUnlock();
    return NOERROR;
}

// The main function, also the main thread.
// Gets the writer lock, modifies the shared data, and downgrades to a reader.
Int32 main(Int32 argc, char **argv)
{
    ECode ec;
    IThread* iReader;
    WaitResult wr;

    // Creates a ReaderWriterLock.
    ec = CReaderWriterLock::New(&g_iLock);
    if (FAILED(ec)) {
        HandleError("Create ReaderWriterLock failed", ec);
        return 1;
    }

    // Gets a writer lock.
    g_iLock->WriterLock(&wr);

    // Creates a reader thread.
    ec = CThread::New(ReaderFunc, NULL, ThreadCreationFlag_Started, &iReader);
    if (FAILED(ec)) {
        HandleError("Create reader thread failed", ec);
        g_iLock->Release();
        return 1;
    }

    // Modifies the shared data.
    sprintf(g_szShared, "Hello.");

    // Downgrades to a reader.
    g_iLock->DowngradeFromWriter();

    // Sleeps for 500 ms. Wait for the reader thread to get the reader lock.
    CThread::Sleep(500, NULL);

    // Prints the shared data.
    printf("Writer: %s\n", g_szShared);

    // Joins the child thread.
    iReader->Join(INFINITE, NULL);

    // Has become a reader, so unlocks the reader lock.
    g_iLock->ReaderUnlock();

    // Releases objects.
    iReader->Release();
    g_iLock->Release();

    return 0;
}

//==========================================================================
//Output:
//
//    Reader: Hello.
//    Writer: Hello.
//==========================================================================
