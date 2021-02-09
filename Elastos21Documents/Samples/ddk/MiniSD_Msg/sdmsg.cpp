//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <mdrivers.h>

IDriver *g_pMiniSD = NULL, *g_pEQ = NULL;
static IDriver *g_pEventQueues = NULL;
static IDriver *g_pNotiCenter = NULL;
typedef void (*NOTIPROC)(int id, int nCode, void *pParam);

typedef struct {
    int EventType;
    NOTIPROC pNotiProc;
}NotiInfo;

NotiInfo g_Info;

BOOL IsDeviceStab(UINT Status)
{
    BufferOf_<Byte, 256> ebbData;
    int cbMsg = 0;
    char *pbData = NULL;
    CThread::Sleep(100, NULL);
    ECode ec = g_pEQ->Control(EVENT_MiniSD, EZBYTEBUF_NULL, ebbData, NULL);
    if (FAILED(ec)) {
        printf("No Data\n");
        return FALSE;
    }
    cbMsg = ebbData.Used();
    if (0 == cbMsg) {
        printf("No New Msg Stab Device Status!\n");
        return TRUE;//is stab
    }
    pbData = (char*)ebbData;
    if (Status == (*(UINT*)(pbData + cbMsg - 4))) {
        printf("New Msg But Stab Device Status!\n");
        return TRUE;
    }
    printf("New Msg But UnStab Device Status!\n");
    return FALSE;
}

EZAPI notitest(int id, int nCode, void *pParam)
{
    UINT sdplug = 0;
    BufferOf_<Byte, 32> ebbData;
    printf("notitest %d %08x\n", nCode, *(UINT*)pParam);
    if (4 == nCode) {
        sdplug = *(UINT*)pParam;
        if (0xC0000001 == sdplug) {
            if(TRUE == IsDeviceStab(0xC0000001)) {
                if (FAILED(\
                    g_pMiniSD->Control(200, EZBYTEBUF_NULL, ebbData, NULL) )) {
                    printf("ReMount MiniSD Card Failed!\n");
                }
                else {
                    printf("ReMount MiniSD Card Succeeded!\n");
                    //Disk mount
                }
            }
            else {
                printf("Ignore This Msg!\n");
            }
        }
        else {
            //Disk unmount
        }
    }
    return NOERROR;
}


static ECode __stdcall NotiProc(void * pArg)
{
    assert(pArg != NULL);
    NotiInfo Info;
    memcpy(&Info, pArg, sizeof(NotiInfo));

    BufferOf_<Byte, 256> ebbData;
    while(1) {
        //GetEvent
        //CThread::Sleep(200);

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
        case EVENT_KEYPAD:
            BufSize = 8/*sizeof(KPD_DATA)*/;
            break;
        case EVENT_TOUCH:
            BufSize = 6/*sizeof(TOUCH_DATA)*/;
            break;
        case EVENT_MiniSD:
            BufSize = 4/*sizeof(UINT)*/;
            break;
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
    UINT SdPlus = 0;
    ECode ec = CSystem::FindRunningObject(
                L"device:minisdbus", (IInterface **)&g_pMiniSD);
    if (FAILED(ec)) {
        return 1;
    }
    ec = CSystem::FindRunningObject(
                L"device:eq0", (IInterface **)&g_pEQ);
    if (FAILED(ec)) {
        g_pMiniSD->Release();
        return 1;
    }
    EzEvNotify(EVENT_MiniSD, 0, &SdPlus);

    //StartVibration();
    EzAddNotify(EVENT_MiniSD, (const void*)notitest);
    getchar();
    g_pMiniSD->Release();
    g_pEventQueues->Release();
    g_pNotiCenter->Release();
    return 0;
}
