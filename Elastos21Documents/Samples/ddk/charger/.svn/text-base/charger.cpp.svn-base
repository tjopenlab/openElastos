//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <stdlib.h>
// #include <mdrivers.h>

//Battery reference control macro
#define PCF_DUMP_STATUS                 6677
#define PCF_BATCHARGE_ENABLE            6678
#define PCF_BATCHARGE_DISABLE           6679
#define PCF_SET_RECHARGE_VOL            6680
#define PCF_SET_INFOPOST_INTERVAL       6681
#define PCF_CHANGE_LED_SETTING          6682
#define PCF_NORMAL_LED_SETTING          6683
#define PCF_CHARGE_LED_ON               6684
#define PCF_CHARGE_LED_OFF              6685
#define PCF_NORMAL_LED_ON               6686
#define PCF_NORMAL_LED_OFF              6687

//Led repetition period
#define  LEDPED_04S 0x00//0.4 s 000
#define  LEDPED_10S 0x01//1.0 s 001
#define  LEDPED_12S 0x02//1.2 s 010
#define  LEDPED_20S 0x03//2.0 s 011
#define  LEDPED_26S 0x04//2.6 s 100
#define  LEDPED_40S 0x05//4.0 s 101
#define  LEDPED_60S 0x06//6.0 s 110
#define  LEDPED_80S 0x07//8.0 s 111

//Led pattern
#define ON_050MS 0x00//000 ON = 50 ms, OFF for rest of repetition period
#define ON_100MS 0x01//001 ON = 100 ms, OFF for rest of repetition period
#define ON_200MS 0x02//010 ON = 200 ms, OFF for rest of repetition period
#define ON_500MS 0x03//011 ON= 500 ms, OFF for rest of repetition period
#define OFO050MS 0x04//100 ON = 50 ms, OFF = 50 ms, ON = 50 ms, OFF for rest of repetition period
#define OFO100MS 0x05//101 ON = 100 ms, OFF = 100 ms, ON = 100 ms, OFF for rest of repetition period
#define OFO200MS 0x06//110 ON = 200 ms, OFF = 200 ms, ON = 200 ms, OFF for rest of repetition period
#define ON_INFMS 0x07//111 LED is continuously ON

IDriver *g_pBattery = NULL;
IDriver *g_pPowerMgn = NULL;

void help(char *cmd)
{
    printf("\n%s:\n \
           \r 1 : Dump PCF Working Status!\n \
           \r 2 : Enable PCF Main Battery Charge!\n \
           \r 3 : Disable PCF Main Battery Charge!\n \
           \r 4 : Change the re-charge voltage 4100mv (3700mv ~ 4100mv)!\n \
           \r 5 : Change the battery info post interval 10 second!\n \
           \r 6 : Change Charge Led Style Setting!\n \
           \r 7 : Change Normal Led Style Setting!\n \
           \r 8 : Turn Off The Charge Led!\n \
           \r 9 : Turn Off The Normal Led!\n \
           \r a : Turn On The Charge Led!\n \
           \r b : Turn On The Normal Led!\n \
           \r c : Custom the GPOC3 control reg!\n \
           \r d : Custom the GPOC1 control reg!\n \
           \r e : Custom the GPOC4 control reg!\n \
           \r f : Custom the GPOC5 control reg!\n \
           \r g : Custom the GPOC2 control reg!\n \
           \r h : Disable Watch Dog Reset!\n \
           \r i : Disable OnKey 1S ShutDown!\n \
           \r j : Enable OnKey 1S ShutDown!\n", cmd);
}

void ledtip()
{
    printf( "Led Pattern:\n \
            \r0 ON = 50 ms, OFF for rest of repetition period\n \
            \r1 ON = 100 ms, OFF for rest of repetition period\n \
            \r2 ON = 200 ms, OFF for rest of repetition period\n \
            \r3 ON= 500 ms, OFF for rest of repetition period\n \
            \r4 ON = 50 ms, OFF = 50 ms, ON = 50 ms, OFF for rest of repetition period\n \
            \r5 ON = 100 ms, OFF = 100 ms, ON = 100 ms, OFF for rest of repetition period\n \
            \r6 ON = 200 ms, OFF = 200 ms, ON = 200 ms, OFF for rest of repetition period\n \
            \r7 LED is continuously ON\n");
    printf( "Led Repeatition:\n \
             \r 0 0.4 s\n \
             \r 1 1.0 s\n \
             \r 2 1.2 s\n \
             \r 3 2.0 s\n \
             \r 4 2.6 s\n \
             \r 5 4.0 s\n \
             \r 6 6.0 s\n \
             \r 7 8.0 s\n");
}

int main(int argc, char** argv)
{
    char InData[4];
    int a, b;
    BufferOf<Byte> ebbInData = ByteArray_Box((char*)InData, 4, 0);
    ECode ec = CSystem::FindRunningObject(
                L"device:battery0", (IInterface **)&g_pBattery);
    if (FAILED(ec)) {
        printf("can not find battery\n");
        return 1;
    }

    ec = CSystem::FindRunningObject(
                L"device:powermanager", (IInterface **)&g_pPowerMgn);
    if (FAILED(ec)) {
        printf("can not find powermanager\n");
        return 1;
    }
    // Get the current battery voltage, in millivolts (mV).
    if (argc == 1) {
        help(argv[0]);
        goto pcf_exit;
    }

    switch(argv[1][0]) {
        case '1':
            printf("Dump PCF Working Status!");
            g_pBattery->Control(PCF_DUMP_STATUS, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
            break;

        case '2':
            printf("Enable PCF Main Battery Charge!\n");
            g_pBattery->Control(PCF_BATCHARGE_ENABLE, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
            break;

        case '3':
            printf("Disable PCF Main Battery Charge!\n");
            g_pBattery->Control(PCF_BATCHARGE_DISABLE, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
            break;

        case '4':
            printf("Change the re-charge voltage 4100mv (3700mv ~ 4100mv)!\n");
            *((int*)InData) = 4100;
            ebbInData.SetUsed(4);
            g_pBattery->Control(PCF_SET_RECHARGE_VOL, ebbInData, EZBYTEBUF_NULL, NULL);
            break;

        case '5':
            printf("Change the battery info post interval 10 second!\n");
            *((int*)InData) = 10;
            ebbInData.SetUsed(4);
            g_pBattery->Control(PCF_SET_INFOPOST_INTERVAL, ebbInData, EZBYTEBUF_NULL, NULL);
            break;

        case '6':
            printf("Change Charge LED Style Setting, Input the new repeatition period and pattern!\n");
            ledtip();
            scanf("%d %d", &a, &b);
            InData[0] = (char)a;
            InData[1] = (char)b;
            printf("New Period %d Pattern %d\n", InData[0], InData[1]);
            ebbInData.SetUsed(4);
            g_pBattery->Control(PCF_CHANGE_LED_SETTING, ebbInData, EZBYTEBUF_NULL, NULL);
            break;

        case '7':
            printf("Change Normal LED Style Setting, Input the new repeatition period and pattern!\n");
            ledtip();
            scanf("%d %d", &a, &b);
            InData[0] = (char)a;
            InData[1] = (char)b;
            printf("New Period %d Pattern %d\n", InData[0], InData[1]);
            ebbInData.SetUsed(4);
            g_pBattery->Control(PCF_NORMAL_LED_SETTING, ebbInData, EZBYTEBUF_NULL, NULL);
            break;

        case '8':
            printf("Turn Off The Charge Led!\n");
            g_pBattery->Control(PCF_CHARGE_LED_OFF, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
            break;

        case '9':
            printf("Turn Off The Normal led\n");
            g_pBattery->Control(PCF_NORMAL_LED_OFF, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
            break;

        case 'a':
        case 'A':
            printf("Turn ON The Charge Led!\n");
            g_pBattery->Control(PCF_CHARGE_LED_ON, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
            break;

        case 'b':
        case 'B':
            printf("Turn ON The Normal led!\n");
            g_pBattery->Control(PCF_NORMAL_LED_ON, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
            break;

        case 'c':
        case 'C':
            printf("Custom the GPOC3 control reg!\n");
            scanf("%d", &a);
            InData[0] = (char)a;
            printf("GPOC3 : %d\n", InData[0]);
            ebbInData.SetUsed(1);
            g_pBattery->Control(7686, ebbInData, EZBYTEBUF_NULL, NULL);
            break;

        case 'd':
        case 'D':
            printf("Custom the GPOC1 control reg!\n");
            scanf("%d", &b);
            InData[0] = (char)b;
            printf("GPOC1 : %d\n", InData[0]);
            ebbInData.SetUsed(1);
            g_pBattery->Control(7687, ebbInData, EZBYTEBUF_NULL, NULL);
            break;

        case 'e':
        case 'E':
            printf("Custom the GPOC4 control reg!\n");
            scanf("%d", &a);
            InData[0] = (char)a;
            printf("GPOC4 : %d\n", InData[0]);
            ebbInData.SetUsed(1);
            g_pBattery->Control(7688, ebbInData, EZBYTEBUF_NULL, NULL);
            break;

        case 'f':
        case 'F':
            printf("Custom the GPOC5 control reg!\n");
            scanf("%d", &b);
            InData[0] = (char)b;
            printf("GPOC5 : %d\n", InData[0]);
            ebbInData.SetUsed(1);
            g_pBattery->Control(7689, ebbInData, EZBYTEBUF_NULL, NULL);
            break;

        case 'g':
        case 'G':
            printf("Custom the GPOC2 control reg!\n");
            scanf("%d", &b);
            InData[0] = (char)b;
            printf("GPOC2 : %d\n", InData[0]);
            ebbInData.SetUsed(1);
            g_pBattery->Control(7690, ebbInData, EZBYTEBUF_NULL, NULL);
            break;

        case 'h':
        case 'H':
            printf("Disable Watch Dog Reset!\n");
            g_pPowerMgn->Control(207, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
            break;

        case 'i':
        case 'I':
            printf("Disable OnKey 1S ShutDown!\n");
            g_pPowerMgn->Control(205, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
            break;

        case 'j':
        case 'J':
            printf("Enable OnKey 1S ShutDown!\n");
            g_pPowerMgn->Control(206, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
            break;

        default:
            help(argv[0]);
    }

pcf_exit:
    g_pBattery->Release();
    g_pPowerMgn->Release();
    return 0;
}
