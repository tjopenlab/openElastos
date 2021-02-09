//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <ddk.h>

void CDECL TimerFunc(void* pv);

DzTimer g_Timer(100, TimerFunc, NULL);

void CDECL TimerFunc(void* pv)
{
    // It is time to do someting ...
}

void UseTimer()
{
    // Starts the timer.
    g_Timer.Start();
}
