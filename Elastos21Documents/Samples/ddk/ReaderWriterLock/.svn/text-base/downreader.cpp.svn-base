//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================


//==========================================================================
//
// Description : This sample demonstrates how to downgrades the acquired
//               writer lock to reader lock.
//
//==========================================================================

#include <ddk.h>

ECode WriteAndReadData(DzReaderWriterLock* pLock)
{
	WaitResult wr;                        
	
    pLock->WriterLock(&wr);

    // Writes the data ...

    // downgrades the acquired writer lock to reader lock
    pLock->DowngradeFromWriter();

    // Reads the data ...

    pLock->ReaderUnlock();

    return NOERROR;
}
