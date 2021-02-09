//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <ddk.h>

ECode ReadAndWriteData(DzReaderWriterLock* pLock)
{
	WaitResult wr;
    pLock->ReaderLock(&wr);
    // Reads data ...

    pLock->UpgradeToWriter(&wr);
    if (WaitResult_OK == wr) {
        // Writes data ...

        pLock->WriterUnlock();
    }
    else {
        if (WaitResult_Interrupted == wr) {
            // Interrupted
        }

        pLock->ReaderUnlock();
    }

    return NOERROR;
}
