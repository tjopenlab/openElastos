//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
// #include <mdrivers.h>

#define EVENT_BATTERY 88

IDriver *g_pBattery = NULL;
IDriver *g_pEQ = NULL;

static IDriver *g_pEventQueues = NULL;
static IDriver *g_pNotiCenter = NULL;

typedef void (*NOTIPROC)(int id, int nCode, void *pParam);

typedef struct {
    int EventType;
    NOTIPROC pNotiProc;
}NotiInfo;

NotiInfo g_Info;


EZAPI notitest(int id, int nCode, void *pParam)
{

    printf("notitest %d : %08x\n", nCode, *(UINT*)pParam);

    return NOERROR;
}


static ECode __stdcall NotiProc(void * pArg)
{
    assert(pArg != NULL);
    NotiInfo Info;
    memcpy(&Info, pArg, sizeof(NotiInfo));

    BufferOf_<Byte, 256> ebbData;
    while(1) {

        ECode ec = g_pEventQueues->Read(Info.EventType, 0,
                ebbData, NULL);
        if (FAILED(ec)) {
            printf("No Data\n");
            continue;
        }
        //CallHook
        (Info.pNotiProc)(Info.EventType, ebbData.Used()/*test*/, (char *)ebbData);
        ebbData.SetUsed(0);
    }

    printf("exit NotiProc\n");

    return 0;
}

ECode EzAddNotify(int EventType, const void *pNotiProc)
{
    ECode ec;
    if (!g_pEventQueues) {
        ec = CSystem::FindRunningObject(
                L"device:eq0", (IInterface **)&g_pEventQueues);
        assert(SUCCEEDED(ec));
    }

    g_Info.EventType = EventType;
    g_Info.pNotiProc = (NOTIPROC)pNotiProc;
    ec = CThread::New(NotiProc, &g_Info, 0, NULL);
    return ec;
}

void EzEvNotify(int eType, int nCode, void *pParam)//callback from app
{
    ECode ec;
    if (!g_pNotiCenter) {
        ec = CSystem::FindRunningObject(
                L"device:nc0", (IInterface **)&g_pNotiCenter);
        assert(SUCCEEDED(ec));
    }

    int BufSize = -1;
    switch(eType) {
        case EVENT_BATTERY:    // event battery
            BufSize = sizeof(int);
        default:
            break;
    }
    if (-1 == BufSize) {
        assert(0);
        return ;
    }
    BufferOf<Byte> ebbData = ByteArray_Box(pParam, BufSize, BufSize);
    g_pNotiCenter->Control(eType, ebbData, EZBYTEBUF_NULL, NULL);
    return;
}

int main()
{
    UINT nBatStatus = 0;
    BufferOf<Byte> ebbData = BufferOf<Byte>::AllocByteBuf(10);


    ECode ec = CSystem::FindRunningObject(
                L"device:battery0", (IInterface **)&g_pBattery);
    if (FAILED(ec)) {
        printf("can not find battery\n");
        return 1;
    }

    // Get the current battery voltage, in millivolts (mV).
    g_pBattery->Control(1, EZBYTEBUF_NULL, ebbData, NULL);
    printf("voltage is %d mV.\n", *(DWORD *)(char *)ebbData);

    // Get current charge status

    g_pBattery->Control(2, EZBYTEBUF_NULL, ebbData, NULL);
    printf("charge status is %d .\n", *(DWORD *)(char *)ebbData);

    // Get the current charge mode

    g_pBattery->Control(3, EZBYTEBUF_NULL, ebbData, NULL);
    printf("charge mode is %d .\n", *(DWORD *)(char *)ebbData);


    // Get the charger type 0: wall charger 1: USB charger
    g_pBattery->Control(4, EZBYTEBUF_NULL, ebbData, NULL);
    printf("charge type is %d .\n", *(int *)(char *)ebbData);

    ec = CSystem::FindRunningObject(
                L"device:eq0", (IInterface **)&g_pEQ);
    if (FAILED(ec)) {
        g_pBattery->Release();
        return 1;
    }
    EzEvNotify(EVENT_BATTERY, 0, &nBatStatus);

    EzAddNotify(EVENT_BATTERY, (const void*)notitest);

    getchar();

    g_pBattery->Release();
    g_pEventQueues->Release();
    g_pNotiCenter->Release();
    g_pEQ->Release();
    BufferOf<Byte>::FreeByteBuf(ebbData);

    return 0;
}
