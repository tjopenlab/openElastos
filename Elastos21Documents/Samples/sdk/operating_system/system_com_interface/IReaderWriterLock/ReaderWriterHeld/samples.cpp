//==============================================================================
// Copyright (c) 2000-2006,  Elastos, Inc.  All Rights Reserved.
//==============================================================================

//==============================================================================
// Description  : This program shows how to use the methods of IReaderWriterLock
//                IsReaderLockHeld and IsWriterLockHeld.
//==============================================================================

#include <stdio.h>
#include <elastos.h>
using namespace Elastos;

//==============================================================================
// Description  : Error Handler
//==============================================================================
void HandleError(const char* msg, ECode ec)
{
    printf("%s (ec = 0x%08x)\n", msg, ec);
}

Int32 main()
{
    ECode ec;
    IReaderWriterLock* iLock;

    // Creates a ReaderWriterLock.
    ec = CReaderWriterLock::New(&iLock);
    if (FAILED(ec)) {
        HandleError("Create ReaderWriterLock failed", ec);
        return 1;
    }

    // Prints the lock holding, becomes reader, prints the lock holding again.
    Boolean bIsHeld1, bIsHeld2;

    iLock->IsReaderLockHeld(&bIsHeld1);
    iLock->IsWriterLockHeld(&bIsHeld2);

    printf("Is ReaderLock? %s\n"
           "Is WriterLock? %s\n",
           bIsHeld1 ? "Yes" : "No",
           bIsHeld2 ? "Yes" : "No");
    printf("Call ReaderLock\n");
    WaitResult wr;
    ec = iLock->ReaderLock(&wr);
    if (FAILED(ec)) {
        HandleError("ReaderLock failed", ec);
    }
    else {
        iLock->IsReaderLockHeld(&bIsHeld1);
        iLock->IsWriterLockHeld(&bIsHeld2);
        printf("Is ReaderLock? %s\n"
               "Is WriterLock? %s\n",
               bIsHeld1 ? "Yes" : "No",
               bIsHeld2 ? "Yes" : "No");
        printf("Call ReaderUnlock\n");
        iLock->ReaderUnlock();
    }

    // Prints the lock holding, becomes writer, prints the lock holding again.
    iLock->IsReaderLockHeld(&bIsHeld1);
    iLock->IsWriterLockHeld(&bIsHeld2);
    printf("Is ReaderLock? %s\n"
           "Is WriterLock? %s\n",
           bIsHeld1? "Yes" : "No",
           bIsHeld2? "Yes" : "No");
    printf("Call WriterLock\n");
    ec = iLock->WriterLock(&wr);
    if (FAILED(ec)) {
        HandleError("WriterLock failed", ec);
    }
    else {
        iLock->IsReaderLockHeld(&bIsHeld1);
        iLock->IsWriterLockHeld(&bIsHeld2);
        printf("Is ReaderLock? %s\n"
               "Is WriterLock? %s\n",
               bIsHeld1? "Yes" : "No",
                  bIsHeld2? "Yes" : "No");
        printf("Call WriterUnlock\n");
        iLock->WriterUnlock();
    }

    // Releases the object.
    iLock->Release();

    return 0;
}

//==============================================================================
//OutPut:
//
//   Is ReaderLock? No
//   Is WriterLock? No
//   Call ReaderLock
//   Is ReaderLock? Yes
//   Is WriterLock? No
//   Call ReaderUnlock
//   Is ReaderLock? No
//   Is WriterLock? No
//   Call WriterLock
//   Is ReaderLock? No
//   Is WriterLock? Yes
//   Call WriterUnlock
//==============================================================================
