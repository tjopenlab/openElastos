//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(__MDRIVERS_H__)
#define __MDRIVERS_H__

#ifdef  __cplusplus
extern "C" {
#endif

ECode EzSetBackLight(/*[in]*/int iLevel);
ECode EzStartVibration(void);
ECode EzStopVibration(void);

ECode EzCreateTimer(int *pTimerID);
ECode EzKillTimer(int TimerID);
ECode EzSetTimerInterval(int TimerID, int Interval/*Milli Seconds*/);
ECode EzStartTimer(int TimerID);
ECode EzStopTimer(int TimerID);
ECode EzGetCurrentTicks(unsigned long *pTicks);

EZAPI EzNotify(int eType, int nCode, void *pParam);//callback
ECode EzAddNotify(int EventType, const void *pNotiProc);

///////////////////////////////////////////////////////////
#define EVENT_KEYPAD    1
#define EVENT_TOUCH     2
#define EVENT_TIMER     3

#define EVENT_TIMER0    4   //channel 0
#define EVENT_TIMER1    5
#define EVENT_TIMER2    6
#define EVENT_TIMER3    7

#define EVENT_MiniSD    10
#define EVENT_MAX       16
///////////////////////////////////////////////////////////

typedef struct KPD_DATA {
    unsigned long keycode;
    unsigned long status;
} KPD_DATA;

typedef struct DECL_PACKED _touch_data {
    short dir;
    short x;
    short y ;
}TOUCH_DATA;

#ifdef  __cplusplus
}
#endif

#endif // __MDRIVERS_H__
