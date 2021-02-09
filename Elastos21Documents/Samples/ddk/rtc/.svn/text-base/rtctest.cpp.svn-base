//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

// FUNCTION: Test the rtc from pmic

#include <elastos.h>
#include <stdio.h>
#include <time.h>

ECode SetRTCDateTime(SystemTime *pTime)
{
    IDriver *pDevice;
    ECode ec = CSystem::FindRunningObject(
            L"device:rtc0", (IInterface **)&pDevice);
    if (FAILED(ec)) return ec;

    ec = pDevice->Control(10/*SetRTCDateTime*/,
        ByteArray_Box(pTime, sizeof(SystemTime)), EZBYTEBUF_NULL, NULL);
    pDevice->Release();
    return NOERROR;
}

ECode SetRTCDate(int w, int y, int md, int d)
{
    IDriver *pDevice;
    ECode ec = CSystem::FindRunningObject(
            L"device:rtc0", (IInterface **)&pDevice);
    if (FAILED(ec)) return ec;

    BufferOf_<Byte, 16> ebbData;
    ebbData.Copy(&w, sizeof(int));
    ebbData.Append(&y, sizeof(int));
    ebbData.Append(&md, sizeof(int));
    ebbData.Append(&d, sizeof(int));
    pDevice->Control(7/*SetRTCDate*/, ebbData, EZBYTEBUF_NULL, NULL);
    pDevice->Release();
    return NOERROR;
}

ECode SetRTCTime(int h, int m, int s)
{
    IDriver *pDevice;
    ECode ec = CSystem::FindRunningObject(
            L"device:rtc0", (IInterface **)&pDevice);
    if (FAILED(ec)) return ec;

    BufferOf_<Byte, 12> ebbData;
    ebbData.Copy(&h, sizeof(int));
    ebbData.Append(&m, sizeof(int));
    ebbData.Append(&s, sizeof(int));
    pDevice->Control(6/*SetRTCTime*/, ebbData, EZBYTEBUF_NULL, NULL);
    pDevice->Release();
    return NOERROR;
}

IDriver *pDevice = NULL;
void printcommand()
{
    printf("0:enable rtc alarm(default)\n");//rtc alarm was enabled,by default
    printf("1:disable rtc alarm\n");
    printf("2:get rtc time info\n");
    printf("3:get rtc date info\n");
    printf("4:get rtc alarm timeinfo\n");
    printf("5:get rtc alarm date info\n");
    printf("6:set rtc timeinfo\n");
    printf("7:set rtc date info\n");
    printf("8:set rtc alarm timeinfo\n");
    printf("9:set rtc alarm date info\n");
    printf("q:quit\n");
    printf(">");
}

int main()
{
    ECode ec = CSystem::FindRunningObject(
            L"device:rtc0", (IInterface **)&pDevice);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: rtc, ec = 0x%08x\n", ec);
        return 1;
    }

    wprintf(L"findService rtc OK! Now start to handle your command!\n");
    printcommand();
    while(true)
    {
        char c=getchar();
        if(c=='q')break;
        switch(c)
        {
            case '0': {
                pDevice->Control(0/*EnableRTCAlarm*/, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;
            }
            case '1': {
                pDevice->Control(1/*DisableRTCAlarm*/, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;
            }
            case '2': {
                BufferOf_<Byte, 12> ebbHandle;
                pDevice->Control(2, EZBYTEBUF_NULL, ebbHandle, NULL);
                int * p = (int *)(char *)ebbHandle;
                printf("rtc time %d:%d:%d\n",p[0],p[1],p[2]);
                break;
            }
            case '3': {
                BufferOf_<Byte, 16> ebbHandle;
                pDevice->Control(3, EZBYTEBUF_NULL, ebbHandle, NULL);
                int * p = (int *)(char *)ebbHandle;
                printf("date weekday:%d   %d:%d:%d\n",p[0],p[1],p[2],p[3]);
                break;
            }
            case '4': {
                BufferOf_<Byte, 12> ebbHandle;
                pDevice->Control(4, EZBYTEBUF_NULL, ebbHandle, NULL);
                int * p = (int *)(char *)ebbHandle;
                printf("rtc alarm time %d:%d:%d\n",p[0],p[1],p[2]);
                break;
            }
            case '5': {
                BufferOf_<Byte, 16> ebbHandle;
                pDevice->Control(5, EZBYTEBUF_NULL, ebbHandle, NULL);
                int * p = (int *)(char *)ebbHandle;
                printf("alarm date weekday:%d   %d:%d:%d\n",p[0],p[1],p[2],p[3]);
                break;
            }
            case '6': {
                int h,m,s;
                printf("input hour[0-23]\n");
                scanf("%d",&h);
                printf("input minute[0-59]\n");
                scanf("%d",&m);
                printf("input second[0-59]\n");
                scanf("%d",&s);
                printf("SetRTCTime %d:%d:%d\n", h, m, s);
                SetRTCTime(h, m, s);
                break;
            }
            case '7': {
                int w,y,md,d;
                printf("input weekday[0~6]\n");
                scanf("%d",&w);
                printf("input year[2000~2037]\n");
                scanf("%d",&y);
                printf("input month[1-12]\n");
                scanf("%d",&md);
                printf("input day[1-31]\n");
                scanf("%d",&d);
                printf("SetRTCDdate %d %d:%d:%d\n", w, y, md, d);
                SetRTCDate(w, y, md, d);
                break;
            }
             case '8': {
                int h,m,s;
                printf("input hour[0-23]\n");
                scanf("%d",&h);
                printf("input minute[0-59]\n");
                scanf("%d",&m);
                printf("input second[0-59]\n");
                scanf("%d",&s);
                BufferOf_<Byte, 12> ebbHandle;
                ebbHandle.Copy(&h, sizeof(int));
                ebbHandle.Append(&m, sizeof(int));
                ebbHandle.Append(&s, sizeof(int));
                pDevice->Control(8/*SetRTCAlarmTime*/, ebbHandle, EZBYTEBUF_NULL, NULL);
                break;
            }
            case '9': {
                int w,y,mt,d;
                printf("input weekday[0~6]\n");
                scanf("%d",&w);
                printf("input year[00~99]\n");
                scanf("%d",&y);
                printf("input month[1-12]\n");
                scanf("%d",&mt);
                printf("input day[1-31]\n");
                scanf("%d",&d);
                BufferOf_<Byte, 16> ebbHandle;
                ebbHandle.Copy(&w, sizeof(int));
                ebbHandle.Append(&y, sizeof(int));
                ebbHandle.Append(&mt, sizeof(int));
                ebbHandle.Append(&d, sizeof(int));
                pDevice->Control(9/*SetRTCAlarmDate*/, ebbHandle, EZBYTEBUF_NULL, NULL);
                break;
            }
            case 'A' :
            case 'a' : {
                int y,md,d,h,m,s;
                printf("input year[2000~2037]\n");
                scanf("%d",&y);
                printf("input month[1-12]\n");
                scanf("%d",&md);
                printf("input day[1-31]\n");
                scanf("%d",&d);
                printf("input local hour[0-23]\n");
                scanf("%d",&h);
                printf("input minute[0-59]\n");
                scanf("%d",&m);
                printf("input second[0-59]\n");
                scanf("%d",&s);
                printf("SetRTCTime %d:%d:%d\n");
                printf("SetRTCDdate %d:%d:%d %d:%d:%d\n", y, md, d, h, m, s);

                struct tm localTime;
                localTime.tm_year = y - 1900;
                localTime.tm_mon = md - 1;
                localTime.tm_mday = d;
                localTime.tm_hour = h;
                localTime.tm_min = m;
                localTime.tm_sec = s;
                SystemTime curTime;
                curTime.m_seconds = mktime(&localTime);//covert system time
                curTime.m_microseconds = 0;
                SetRTCDateTime(&curTime);
                break;
            }
            case 'B' :
            case 'b' : {
                BufferOf_<Byte, 12> ebbHandle;
                pDevice->Control(2, EZBYTEBUF_NULL, ebbHandle, NULL);
                int * p = (int *)(char *)ebbHandle;
                int h = p[0];int m = p[1];int s = p[2];
                SetRTCTime(h, m, s);
                break;
            }
            case 'U' :
            case 'u' : {
                pDevice->Control(11, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;
            }
            default:break;
        }
        printf("\n>");
    }
    pDevice->Release();
    return 0;
}
