//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================


//==========================================================================
//
// Description : This sample demonstrates how to use
//               ReaderWriterLock::ReaderLock and
//               ReaderWriterLock::ReaderUnlock
//
//==========================================================================


#include <ddk.h>

ECode ReadData(DzReaderWriterLock* pLock)
{
    // Acquires the reader lock   
    WaitResult wr;
    pLock->ReaderLock(&wr);
    // Reads the data ...

    // Releases the acquired reader lock
    pLock->ReaderUnlock();

    return NOERROR;
}
