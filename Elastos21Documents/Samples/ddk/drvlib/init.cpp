//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <stdlib.h>
#include <mdrivers.h>

typedef void (*NOTIPROC)(int id, int nCode, void *pParam);

typedef struct {
    int EventType;
    NOTIPROC pNotiProc;
}NotiInfo;

static IDriver *g_pEventQueues = NULL;
static ECode __stdcall NotiProc(void * pArg)
{
    assert(pArg != NULL);
    NotiInfo Info;
    memcpy(&Info, pArg, sizeof(NotiInfo));
    free(pArg);

    while(1) {
        //GetEvent
        //CThread::Sleep(200);
        BufferOf_<Byte, 256> ebbData;
        ECode ec = g_pEventQueues->Read(Info.EventType, 0,
                ebbData, NULL);
        if (FAILED(ec)) {
            printf("No Data\n");
            continue;
        }
        //CallHook
        (Info.pNotiProc)(Info.EventType, 5/*test*/, (char *)ebbData);
    }

    printf("exit NotiProc\n");

    return 0;
}

ECode EzAddNotify(int EventType, const void *pNotiProc)
{
    ECode ec = NOERROR;
    if (!g_pEventQueues) {
        CSystem::FindRunningObject(
                L"device:eq0", (IInterface **)&g_pEventQueues);
        assert(SUCCEEDED(ec));
    }

    NotiInfo *pInfo = (NotiInfo *)malloc(sizeof(NotiInfo));
    pInfo->EventType = EventType;
    pInfo->pNotiProc = (NOTIPROC)pNotiProc;
    ec = CThread::New(NotiProc, pInfo, 0, NULL);
    return ec;
}

static IDriver *g_pNotiCenter = NULL;
EZAPI EzNotify(int eType, int nCode, void *pParam)//callback from app
{
    ECode ec = NOERROR;
    if (!g_pNotiCenter) {
        ec = CSystem::FindRunningObject(
                L"device:nc0", (IInterface **)&g_pNotiCenter);
        assert(SUCCEEDED(ec));
    }

    int BufSize = -1;
    switch(eType) {
        case EVENT_KEYPAD:
            BufSize = 8/*sizeof(KPD_DATA)*/;
            break;
        case EVENT_TOUCH:
            BufSize = 6/*sizeof(TOUCH_DATA)*/;
            break;
        default:
            break;
    }
    if (-1 == BufSize) {
        assert(0);
        return E_ACCESS_DENIED;
    }
    BufferOf<Byte> ebbData = ByteArray_Box(pParam, BufSize, BufSize);
    g_pNotiCenter->Control(eType, ebbData, EZBYTEBUF_NULL, NULL);
    return ec;
}

/////////////////////////////////////////////////////////////////////
//global
/////////////////////////////////////////////////////////////////////
IDriver *gpGenDev = NULL;

static void __cdecl term(void)
{
    if (NULL != gpGenDev) {
        wprintf(L"Release general device 0x%08x.\n", gpGenDev);
        gpGenDev->Release();
        gpGenDev = NULL;
    }
    return;
}

static void __cdecl init(void)
//EXTERN_C BOOL __stdcall DllMain(HANDLE pPcb, DWORD Op,  PVOID Arg3)
{
    // Get general device
    ECode ec;

    wprintf(L"Get general device ...\n");

    ec = CSystem::FindRunningObject(
            L"device:general0", (IInterface **)&gpGenDev);
    if (FAILED(ec)) goto errorexit;

    assert(NULL != gpGenDev);
    wprintf(L"Bind general device 0x%08x OK\n", gpGenDev);

//    return true;

errorexit:
    return;
//    return false;
}

typedef void (__cdecl *PF)(void);

#if defined(_GNUC)
PF initdfns[] __attribute__((section(".ctors"),
        aligned(sizeof(PF)))) = { init };
PF termdfns[] __attribute__((section(".dtors"),
        aligned(sizeof(PF)))) = { term };

#else
#pragma data_seg(".CRT$XCD", "DATA")
PF initdfns[] = { init };

#pragma data_seg(".CRT$XTD", "DATA")
PF termdfns[] = { term };

#endif
