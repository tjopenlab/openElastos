//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <ddk.h>

void CDECL TimerFunc(void* pv);

int     g_nTimes = 10;

DzTimer   g_Timer(100, TimerFunc, NULL);

// Timer Function
void CDECL TimerFunc(void* pv)
{
    // It is time to do someting ...

    if (--g_nTimes > 0) {
        // does someting at the first time ...

        g_Timer.Restart(100);
    }
}

void UseTimer()
{
    // Starts the timer.
    g_Timer.Start();
}
