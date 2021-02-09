//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <ddk.h>

void SampleFunc()
{
    LONG lTarget = 0;
    LONG lRet;

    // lTarget is 0

    lRet = InterlockedIncrement(&lTarget);

    // lTarget is 1
    // lRet is 1

    lRet = InterlockedDecrement(&lTarget);

    // lTarget is 0
    // lRet is 0
}
