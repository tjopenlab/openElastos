//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <ddk.h>

// Timer Function
void CDECL TimerFunc(void* pv)
{
    // Never executed ...
}

void UseTimer()
{
    uint_t uLeftRelativeTicks;

    DzTimer* pTimer = new DzTimer(1000, TimerFunc, pTimer);

    // Starts a time.
    pTimer->Start();

    // Cancels it.
    pTimer->Cancel();

    // Get the residual ticks.
    uLeftRelativeTicks = pTimer->GetResidualTicks();

    delete pTimer;
}

