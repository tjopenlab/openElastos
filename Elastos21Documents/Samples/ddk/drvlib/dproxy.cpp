//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <mdrivers.h>

extern IDriver *gpGenDev;
#define MAKECONTROL(_c_, _n_)   ((_c_ << 16) + _n_)
//Add your driver proxy here
ECode EzSetBackLight(/*[in]*/int iLevel)
{
    if (NULL == gpGenDev) return E_ACCESS_DENIED;
    BufferOf_<Byte, 4> buf;
    buf.Copy(&iLevel, 4);
    return gpGenDev->Control(MAKECONTROL(120, 17), buf, EZBYTEBUF_NULL, 0);
}

ECode EzStartVibration(void)
{
    return E_NOT_IMPLEMENTED;
}

//Return TimerID (0 ~ 3), return -1 if fail
ECode EzCreateTimer(int *pTimerID)
{
    BufferOf<Byte> ebbHandle = ByteArray_Box(pTimerID, 4, 4);
    ECode ec = gpGenDev->Control(
                MAKECONTROL(150, 11), EZBYTEBUF_NULL, ebbHandle, NULL );
    if (FAILED(ec)) return ec;

    assert(*pTimerID >= 0);
    return ec;
}

ECode EzKillTimer(int TimerID)
{
    BufferOf_<Byte, 4> ebbHandle;
    ebbHandle.Copy(&TimerID, sizeof(int));
    ECode ec = gpGenDev->Control(
                MAKECONTROL(150, 12), ebbHandle, EZBYTEBUF_NULL, NULL );
    return ec;
}

ECode EzStartTimer(int TimerID)
{
    BufferOf_<Byte, 4> ebbHandle;
    ebbHandle.Copy(&TimerID, sizeof(int));
    ECode ec = gpGenDev->Control(
                MAKECONTROL(150, 14), ebbHandle, EZBYTEBUF_NULL, NULL );
    return ec;
}

ECode EzSetTimerInterval(int TimerID, int Interval/*Milli Seconds*/)
{
    BufferOf_<Byte, 8> ebbParam;
    int *pParam = (int *)(char *)ebbParam;
    pParam[0] = TimerID;
    pParam[1] = Interval;
    ebbParam.SetUsed(8);

    ECode ec = gpGenDev->Control(
                MAKECONTROL(150, 13), ebbParam, EZBYTEBUF_NULL, NULL );
    return ec;
}

ECode EzStopTimer(int TimerID)
{
    BufferOf_<Byte, 4> ebbHandle;
    ebbHandle.Copy(&TimerID, sizeof(int));
    ECode ec = gpGenDev->Control(
                MAKECONTROL(150, 15), ebbHandle, EZBYTEBUF_NULL, NULL );
    return ec;
}

ECode EzGetCurrentTicks(unsigned long *pTicks)
{
    BufferOf<Byte> ebbData = ByteArray_Box(pTicks, 4, 4);
    ECode ec = gpGenDev->Control(
                MAKECONTROL(150, 20), EZBYTEBUF_NULL, ebbData, NULL );
    return ec;
}
