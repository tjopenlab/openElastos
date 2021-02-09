//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <ddk.h>

void CDECL TimerFunc(void* pv)
{
    // It is time to do someting ...
}

void UseTimer()
{
    DzTimer* pTimer = new DzTimer(100, TimerFunc, NULL);

    // Starts a timer.
    pTimer->Start();

    // Tests until the time dues.
    while (pTimer->Due() != TRUE) {
        DzYield();
    }

    delete pTimer;
}
