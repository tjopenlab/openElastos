//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================


//==========================================================================
//
// Description : This sample demonstrates how to use
//               ReaderWriterLock::WriterLock and
//               ReaderWriterLock::WriterUnlock
//
//==========================================================================


#include <ddk.h>

ECode WriteData(DzReaderWriterLock* pLock)
{
    WaitResult wr;
    // Acquires the writer lock
    pLock->WriterLock(&wr);
    // Writes the data ...

    // Releases the acquired writer lock
    pLock->WriterUnlock();

    return NOERROR;
}
