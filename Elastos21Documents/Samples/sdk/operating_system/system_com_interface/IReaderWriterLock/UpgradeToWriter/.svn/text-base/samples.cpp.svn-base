//==============================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==============================================================================

//==============================================================================
// Description  : This program shows how to use the methods of IReaderWriterLock
//                UpgradeToWriter to change the status from Reader to Writer.
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

// Shared Data
char g_szShared[20] = "Uninitialized.";

// The flag is true if the main thread upgrades to the writer.
Boolean g_bOk = false;

//  Reader Thread
ECode ReaderFunc(void* arg)
{
    // Repeats to get a reader lock. Prints the shared data.
    WaitResult wr;
    while (!g_bOk) {
        g_iLock->ReaderLock(&wr);
        printf("Reader: %s\n", g_szShared);
        g_iLock->ReaderUnlock();

        // Sleeps for a while, gives the main thread chance to
        // get the writer lock.
        CThread::Sleep(50, NULL);
    }

    // Prints the modified data.
    g_iLock->ReaderLock(&wr);
    printf("Reader: %s\n", g_szShared);
    g_iLock->ReaderUnlock();

    return NOERROR;
}

//==============================================================================
// Description  : The main function, also the main thread.
//                Gets a reader lock first, then upgrades to the
//                writer, and modifis the shared data.
//==============================================================================

Int32 main()
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

    // Gets a reader lock.
    g_iLock->ReaderLock(&wr);

    // Creates the reader thread.
    ec = CThread::New(ReaderFunc, 0, 0, &iReader);
    if (FAILED(ec)) {
        HandleError("Create reader thread failed", ec);
        g_iLock->Release();
        return 1;
    }

    // Sleeps for a while.
    CThread::Sleep(500, NULL);

    // Upgrades to a writer and modifies the shared data.
    ec = g_iLock->UpgradeToWriter(&wr);
    if (FAILED(ec)) {
        HandleError("Failed to upgrade to writer.", ec);
        g_iLock->ReaderUnlock();
    }
    else {
        sprintf(g_szShared, "Hello.");
        g_iLock->WriterUnlock();
    }
    g_bOk = true;

    // Join the child thread.
    iReader->Join(INFINITE, NULL);

    // Releases objects.
    iReader->Release();
    g_iLock->Release();

    return 0;
}

//==============================================================================
//OutPut:
//
//   Reader: Uninitialized.
//   Reader: Uninitialized.
//   Reader: Uninitialized.
//   Reader: Uninitialized.
//   Reader: Uninitialized.
//   Reader: Uninitialized.
//   Reader: Uninitialized.
//   Reader: Uninitialized.
//   Reader: Uninitialized.
//   Reader: Uninitialized.
//   Reader: Uninitialized.
//   Reader: Hello.
//==============================================================================
