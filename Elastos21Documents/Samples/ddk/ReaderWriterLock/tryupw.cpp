//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <ddk.h>

ECode ReadAndWriteData(DzReaderWriterLock* pLock)
{
    const uint_t uTicks = 100;

	WaitResult wr;	
    pLock->ReaderLock(&wr);


    // Reads data ...

    pLock->TryUpgradeToWriter(uTicks, &wr);
    if (WaitResult_OK == wr) {
        // Writes data ...

        pLock->WriterUnlock();
    }
    else {
        if (WaitResult_Interrupted == wr) {
            // Interrupted
        }
        else if (WaitResult_TimedOut == wr) {
            // Timeout
        }

        pLock->ReaderUnlock();
    }

    return NOERROR;
}
