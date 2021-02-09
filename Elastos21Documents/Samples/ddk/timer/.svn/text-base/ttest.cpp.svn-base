//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

IDriver *g_pTimer;
//Return TimerID (0 ~ 3), return -1 if fail

#define EVENT_USER            81   //user queue

typedef void (*TimerCallBackProc)(void * pvArg);
typedef struct {
    TimerCallBackProc pCallbackProc;
    void              * pvArg;
    int               eType;//QueueNo
    ULONG             Resolution;
    ULONG             Interval;
}TimerInfo;

ECode EzCreateTimer(TimerInfo *timer, int *pTimerID)
{
    BufferOf<Byte> ebbHandleOut = ByteArray_Box(pTimerID, 4, 4);
    BufferOf_<Byte, sizeof(TimerInfo)> ebbHandleIn;

    TimerInfo ti;
    ti.eType=timer->eType;
    ti.pCallbackProc=timer->pCallbackProc;
    ti.pvArg=timer->pvArg;
    ti.Resolution=timer->Resolution;
    ti.Interval=timer->Interval;
    ebbHandleIn.Copy(&ti, sizeof(ti));
    printf("EzCreateTimer(TimerInfo *timer, int *pTimerID)\n");

    return g_pTimer->Control(11, ebbHandleIn, ebbHandleOut, NULL );
}

ECode EzGetCurrentTicks(unsigned long *pTicks)
{
    BufferOf<Byte> ebbData = ByteArray_Box(pTicks, 4, 4);
    ECode ec = g_pTimer->Control(
                20, EZBYTEBUF_NULL, ebbData, NULL );
    return ec;
}

ECode EzSetTimerInterval(int TimerID, int Interval/*Milli Seconds*/)
{
    BufferOf_<Byte, 8> ebbParam;
    int *pParam = (int *)(char *)ebbParam;
    pParam[0] = TimerID;
    pParam[1] = Interval;
    ebbParam.SetUsed(8);

    ECode ec = g_pTimer->Control(
                13, ebbParam, EZBYTEBUF_NULL, NULL );
    return ec;
}

ECode EzStopTimer(int TimerID)
{
    BufferOf_<Byte, 4> ebbHandle;
    ebbHandle.Copy(&TimerID, sizeof(int));
    ECode ec = g_pTimer->Control(
                15, ebbHandle, EZBYTEBUF_NULL, NULL );
    return ec;
}


ECode EzKillTimer(int TimerID)
{
    BufferOf_<Byte, 4> ebbHandle;
    ebbHandle.Copy(&TimerID, sizeof(int));
    ECode ec = g_pTimer->Control(
                12, ebbHandle, EZBYTEBUF_NULL, NULL );
    return ec;
}

ECode EzStartTimer(int TimerID)
{
    BufferOf_<Byte, 4> ebbHandle;
    ebbHandle.Copy(&TimerID, sizeof(int));
    ECode ec = g_pTimer->Control(
                14, ebbHandle, EZBYTEBUF_NULL, NULL );
    return ec;
}

SystemTime t1,t2;

void OnTimer1Proc(void *pParam)
{
    if(NULL != pParam)
        printf("OnTimer1 pParam=%d\n", *((int *)pParam));
    SystemTime t;
    CSystem::GetMachineTime(&t);
    printf("111111111111Ti %d\n", t.m_seconds - t1.m_seconds);
    t1 = t;
}

void OnTimer2Proc(void *pParam)
{
    if(NULL != pParam)
        printf("OnTimer2 pParam=%d\n", *((int *)pParam));
    SystemTime t;
    CSystem::GetMachineTime(&t);
    printf("22222222222Ti %d\n", t.m_seconds - t2.m_seconds);
    t2 = t;
}


static IDriver *g_pEventQueues = NULL;
static ECode NotiProc(void * pArg)
{
    ECode ec;
    if (NULL == g_pEventQueues) {
        ec = CSystem::FindRunningObject(
                L"device:eq0", (IInterface **)&g_pEventQueues);
        assert(SUCCEEDED(ec));
    }
    BufferOf_<Byte, 8> ebbData;
    printf("Creating proc of receive\n");
    while(1) {
        ec = g_pEventQueues->Read(EVENT_USER, 0,
                ebbData, NULL);
        if (FAILED(ec)) {
            printf("No Data\n");
            continue;
        }
//        printf("succeed\n");
        unsigned long * data=(unsigned long *)(char *)ebbData;
        TimerCallBackProc func=(TimerCallBackProc)data[0];
//        printf("func=(TimerCallBackProc)data[0]=0x%x\n", func);
        assert(NULL != func);
        void * arg=(void *)data[1];
        func(arg);
    }
    return NOERROR;
}


int main(int argc, char *argv[])
{
    ECode ec;
    ec = CSystem::FindRunningObject(L"device:timer1", (IInterface**)&g_pTimer);
    if (FAILED(ec)) goto exit;
    static int arg = 12;
    int TimerID[2];
    TimerID[0] = 0;
    TimerID[1] = 0;
    TimerInfo ti[2];
    ti[0].eType=EVENT_USER;
    ti[0].pCallbackProc=OnTimer1Proc;
    ti[0].pvArg=&arg;
    ti[0].Resolution=1;//1s
    ti[0].Interval=2;
//    printf("------------->enter OnTimer1Proc:0x%x\n", OnTimer1Proc);
    ti[1].eType=EVENT_USER;
    ti[1].pCallbackProc=OnTimer2Proc;
    ti[1].pvArg=&arg;
    ti[1].Resolution=1;
    ti[1].Interval=5;
//    printf("------------->enter OnTimer2Proc:0x%x\n", OnTimer2Proc);

    //Create Timer 1
    ec = EzCreateTimer(&ti[0], &TimerID[0]);
    if(FAILED(ec)) goto exit;
    printf("CreatTimer %d\n", TimerID[0]);
    //Start Timer 1
    CSystem::GetMachineTime(&t1);
    ec = EzStartTimer(TimerID[0]);
    if (FAILED(ec)) goto exit;

    printf("StartTimer %d\n", TimerID[0]);
    CThread::New(NotiProc, NULL, 0, NULL);
    //Creat Timer 2
    ec = EzCreateTimer(&ti[1], &TimerID[1]);
    if (FAILED(ec)) goto exit;
    printf("CreatTimer %d\n", TimerID[1]);

    //Start Timer 2
    CSystem::GetMachineTime(&t2);
    ec = EzStartTimer(TimerID[1]);
    if (FAILED(ec)) goto exit;
    printf("StartTimer %d\n", TimerID[1]);

    printf("Press any key to stop timer1 ...");getchar();
    EzStopTimer(TimerID[0]);

    printf("Press any key to restart timer1 ...");getchar();
    //restart Timer 1
    CSystem::GetMachineTime(&t1);
    ec = EzStartTimer(TimerID[0]);
    printf("StartTimer1\n");

    printf("Press any key to stop timer2 ...");getchar();
    EzStopTimer(TimerID[1]);

    printf("Press any key to stop timer1 ...");getchar();
    EzStopTimer(TimerID[0]);

    printf("Press any key to kill timer ...");getchar();
    EzKillTimer(TimerID[0]);
    EzKillTimer(TimerID[1]);
    return 0;
exit:
printf("ERR\n");

    return 1;
}
