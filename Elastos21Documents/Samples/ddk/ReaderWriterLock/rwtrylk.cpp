//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : This sample demonstrates how to use
//               ReaderWriterLock::ReaderTryLock and
//               ReaderWriterLock::WriterTryLock
//
//==========================================================================

#include <ddk.h>

void TryLock(DzReaderWriterLock* pLock)
{
    const uint_t uTicks = 100;

    WaitResult wr;
    // Tries to acquire the reader lock within given time interval
    pLock->ReaderTryLock(uTicks, &wr);
    if (WaitResult_OK == wr) {
        // Succeeds, reads data ...

        pLock->ReaderUnlock();
    }
    else if (WaitResult_Interrupted == wr) {
        // Be interrupted
    }
    else if (WaitResult_TimedOut == wr) {
        // Timeout
    }

    // Tries to acquire the writer lock, within the given time interval
    pLock->WriterTryLock(uTicks, &wr);
    if (WaitResult_OK == wr) {
        // Succeeds, writes data ...

        pLock->WriterUnlock();
    }
    else if (WaitResult_Interrupted == wr) {
        // Interrupted
    }
    else if (WaitResult_TimedOut == wr) {
        // Timeout
    }
}
