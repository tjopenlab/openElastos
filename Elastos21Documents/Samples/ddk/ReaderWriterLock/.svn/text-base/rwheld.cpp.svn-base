//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================


//==========================================================================
//
// Description : This sample demonstrates how to use
//               ReaderWriterLock::IsReaderLockHeld and
//               ReaderWriterLock::IsWriterLockHeld.
//
//==========================================================================


#include <ddk.h>

void TestLockHeld(DzReaderWriterLock* pLock)
{
   
    BOOL bIsHeld;
    // Checks whether the thread has acquired the reader lock
    pLock->IsReaderLockHeld(&bIsHeld);
    if (bIsHeld) {
        // Yes, owns a reader lock
        //...
    }
    else {
        // No, does not own a reader lock
        //...
    }

    // Checks whether the thread has acquired the writer lock
    pLock->IsWriterLockHeld(&bIsHeld);
    if (bIsHeld) {
        // Yes, owns a writer lock
        //...
    }
    else {
        // No, does not own a writer lock
        //...
    }
}
