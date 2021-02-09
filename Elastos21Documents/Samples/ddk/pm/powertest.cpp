//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

// FUNCTION: Test the power manager,
//           Including entering idle,sleeping and resuming,and etc.

#include <elastos.h>
#include <stdio.h>

IDriver *pDevice = NULL;
void printcommand()
{
    printf("0:force cpu sleep\n");
    printf("1:reset gpio pin\n");
    printf("2:power status report\n");
    printf("3:enable cpu sleep\n");
    printf("4:disable cpu sleep\n");
    printf("5:cpu sleep auto test\n");
    printf("6:cancle cpu sleep auto test\n");
    printf("7:set lcd power policy\n");
    printf("8:get lcd power Policy\n");
    printf("9:notify power manager an input event oucur!\n");
    printf("a:notify power manager lock screen oucur!\n");
    printf("b:power function test\n");
    printf("c:power rtc test\n");
    printf("d:get doc uid\n");
    printf("e:get boot status\n");
    printf("f:dump ac97 registers\n");
    printf("g:read logo and print\n");
    printf("h:write logo and print\n");
    printf("i:dump gpio register\n");
    printf("j:dump pcf register\n");
    printf("k:get cpu speed\n");
    printf("m:reboot\n");
    printf("n:shutdown\n");
    printf("q:quit\n");
    printf(">");
}

int main()
{
    ECode ec = CSystem::FindRunningObject(
            L"device:powermanager", (IInterface **)&pDevice);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: powermanager, ec = 0x%08x\n", ec);
        return 1;
    }

    wprintf(L"findService power manager OK! Now start to handle your command!\n");
    printcommand();
    while(true)
    {
        char c=getchar();
        if(c=='q')break;
        switch(c)
        {
            case '0':pDevice->Control(0, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);break;
            case '1':pDevice->Control(1, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);break;
            case '2':pDevice->Control(50, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);break;
            case '3':pDevice->Control(3, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);break;
            case '4':pDevice->Control(4, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);break;
            case '5': {
                ECode ec = CSystem::FindRunningObject(L"device:power", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: power, ec = 0x%08x\n", ec);
                    return 1;
                }
                pDevice->Control(5, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);break;
            }
            case '6':pDevice->Control(6, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);break;
            case '7': {
                int uInterval;
                printf("input your choice, [-1]:always power on; [0]:restore old interval;\n"
                        "[n]:set normal interval seconds\n");
                scanf("%d",&uInterval);
                BufferOf_<Byte, 4> ebbHandle;
                ebbHandle.Copy(&uInterval, sizeof(int));
                pDevice->Control(100/*SetLCDPolicy*/, ebbHandle, EZBYTEBUF_NULL, NULL);
                break;
            }
            case '8': {
                BufferOf_<Byte, 4> ebbData;
                ECode ec = pDevice->Control(102/*GetLCDPolicy*/, EZBYTEBUF_NULL, ebbData, NULL);
                if (FAILED(ec)) break;
                int uPolicy = *(int *)(char *)ebbData;
                printf("Current LCD Power Policy: %s\n", (uPolicy==0)?"Normal":"AlwaysOn");
                break;
            }
            case '9': {
                static IDriver * g_pNotiCenter = NULL;
                if (NULL == g_pNotiCenter) {
                    ECode ec = CSystem::FindRunningObject(L"device:nc0", (IInterface **)&g_pNotiCenter);
                    if (FAILED(ec)) break;
                }
                g_pNotiCenter->Control((1<<16)+83/*EVENT_INPUT*/,
                                        EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;
            }
            case 'a': {
                long bLock;
                printf("input your choice, [0]:unclock screen;\n"
                        "[1]:lock screen\n");
                scanf("%d",&bLock);
                BufferOf_<Byte, 4> ebbHandle;
                ebbHandle.Copy(&bLock, sizeof(int));
                pDevice->Control(103/*LockScreen*/, ebbHandle, EZBYTEBUF_NULL, NULL);
                break;
            }
            case 'b': {
                ECode ec = CSystem::FindRunningObject(L"device:power", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: power, ec = 0x%08x\n", ec);
                    return 1;
                }
                long choice;
                printf("input your choice:0,sleep;1,idle;2,min(13mhz);3,low(104mhz);4,high(208mhz);5,max(312mhz)\n");
                scanf("%d",&choice);
                BufferOf_<Byte, 4> ebbHandle;
                ebbHandle.Copy(&choice, sizeof(int));
                pDevice->Control(100/*LockScreen*/, ebbHandle, EZBYTEBUF_NULL, NULL);
                break;
            }
            case 'c': {
                ECode ec = CSystem::FindRunningObject(L"device:power", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: power, ec = 0x%08x\n", ec);
                    return 1;
                }
                long mdur;
                printf("? minutes later it will alarm\n");
                scanf("%d",&mdur);
                BufferOf_<Byte, 4> ebbHandle;
                ebbHandle.Copy(&mdur, sizeof(int));
                pDevice->Control(101/*LockScreen*/, ebbHandle, EZBYTEBUF_NULL, NULL);
                break;
            }
            case 'd': {
                ECode ec = CSystem::FindRunningObject(L"device:docstorage0", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: docstorage, ec = 0x%08x\n", ec);
                    return 1;
                }
                BufferOf_<Byte, 16> ebbHandle;
                pDevice->Control(0x1000000a/*GetDocUID*/, EZBYTEBUF_NULL, ebbHandle, NULL);
                int * puid =(int *)(char *)ebbHandle;
                printf("uid:%x   %x   %x   %x\n",puid[0],puid[1],puid[2],puid[3]);
                break;
            }
            case 'e': {
                BufferOf_<Byte, 4> ebbData;
                ECode ec = pDevice->Control(104/*GetBootStatus*/, EZBYTEBUF_NULL, ebbData, NULL);
                if (FAILED(ec)) break;
                unsigned long  status = *(unsigned long *)(char *)ebbData;
                printf("booting status: ");
                if(status == 1)printf("alarm match,your rtc alarm match\n");
                else if(status == 2)printf("charger insertion,start charging battery\n");
                else printf("normal,you press onkey\n");
                break;
            }
            case 'f': {
                ECode ec = CSystem::FindRunningObject(L"device:wave0", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: wave, ec = 0x%08x\n", ec);
                    return 1;
                }
                ec = pDevice->Control(0x101/*dump ac97*/, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;
            }
            case 'g': {
                ECode ec = CSystem::FindRunningObject(L"device:docstorage0", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: docstorage, ec = 0x%08x\n", ec);
                    return 1;
                }
                char * temp = new char[320*240*2];
                BufferOf<Byte> ebbHandle = ByteArray_Box(temp,320*240*2,320*240*2);
                pDevice->Control(0x10000012/*ReadLogo*/, EZBYTEBUF_NULL, ebbHandle, NULL);
                int * puid =(int *)(char *)ebbHandle;
                printf("first 4 bytes:%x   %x   %x   %x   %x\n",puid[0],puid[1],puid[2],puid[3],puid[24000]);
                printf("last 4 bytes:%x   %x   %x   %x   %x\n",puid[38386],puid[38387],puid[38388],puid[38389],puid[24000]);
                break;
            }

            case 'h': {
                ECode ec = CSystem::FindRunningObject(L"device:docstorage0", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: docstorage, ec = 0x%08x\n", ec);
                    return 1;
                }
                char * temp = new char[320*240*2];
                BufferOf<Byte> ebbHandle = ByteArray_Box(temp,320*240*2,320*240*2);
                int * puid =(int *)(char *)ebbHandle;
                puid[0]=100;
                puid[1]=1000;
                puid[2]=10000;
                puid[3]=100000;
                puid[24000]=1982;
                pDevice->Control(0x10000013/*WriteLogo*/, ebbHandle, EZBYTEBUF_NULL, NULL);
                break;
            }
            case 'i' : {
                ECode ec = CSystem::FindRunningObject(L"device:power", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: power, ec = 0x%08x\n", ec);
                    return 1;
                }
                pDevice->Control(102, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;
            }
            case 'j' : {
                ECode ec = CSystem::FindRunningObject(L"device:power", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: power, ec = 0x%08x\n", ec);
                    return 1;
                }
                pDevice->Control(103, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;
            }
            case 'k' : {
                ECode ec = CSystem::FindRunningObject(L"device:power", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: power, ec = 0x%08x\n", ec);
                    return 1;
                }
                pDevice->Control(104, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;
            }
            case 'm' : {
                ECode ec = CSystem::FindRunningObject(L"device:powermanager", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: powermanager, ec = 0x%08x\n", ec);
                    return 1;
                }
                int mSec;
                printf("? ms later it will reboot\n");
                scanf("%d",&mSec);
                BufferOf_<Byte, 4> ebbHandle;
                ebbHandle.Copy(&mSec, sizeof(int));
                pDevice->Control(105, ebbHandle, EZBYTEBUF_NULL, NULL);
                break;
            }
            case 'n' : {
                ECode ec = CSystem::FindRunningObject(L"device:powermanager", (IInterface **)&pDevice);
                if (FAILED(ec)) {
                    printf("ERROR: Can't find Service: powermanager, ec = 0x%08x\n", ec);
                    return 1;
                }
                pDevice->Control(106, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;
            }
            default:break;
        }
        printf("\n>");
    }
    pDevice->Release();
    return 0;
}
