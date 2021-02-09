//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <ddk.h>

void SampleFunc()
{
    LONG lTarget = 0;
    LONG lRet;

    // lTarget is 0

    lRet = InterlockedExchange(&lTarget, 1);

    // lTarget is 1
    // lRet is 0

    InterlockedExchangeAdd(&lTarget, 5);

    // lTarget is 6
    // lRet is 1

    PLONG pTarget = NULL;
    PLONG pRet;

    // pTarget is NULL

    pRet = (PLONG)InterlockedExchangePointer((PVOID*)pTarget, &lTarget);

    // pTarget is &lTarget
    // pRet is NULL
}
