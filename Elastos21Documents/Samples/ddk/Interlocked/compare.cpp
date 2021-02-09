//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <ddk.h>

void SampleFunc()
{
    LONG lTarget = 0;
    LONG lRet;

    // lTarget is 0

    lRet = InterlockedCompareExchange(&lTarget, 1, 2);

    // lTarget does not equal 2, so lTarget keeps 0
    // lRet is 0

    lRet = InterlockedCompareExchange(&lTarget, 1, 0);

    // lTarget equals 0, so lTarget becomes 1
    // lRet is 0


    PLONG pTarget = NULL;
    PLONG pRet;

    // pTarget is NULL

    pRet = (PLONG)InterlockedCompareExchangePointer((PVOID*)&pTarget, &lTarget, NULL);

    // pTarget equals NULL, so pTarget becomes &lTarget
    // pRet is NULL
}
