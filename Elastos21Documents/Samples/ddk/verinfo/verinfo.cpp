//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INFO_GETVENDERID  0xA001
#define INFO_GETMODEL     0xA002
#define INFO_GETFIRMVER   0xA003
#define INFO_GETFIRMDATE  0xA004
#define INFO_GETSOFTVER   0xA005
#define INFO_GETSOFTDATE  0xA006
#define INFO_GETHARDVER   0xA007
#define INFO_GETHARDDATE  0xA008

#define CONV(PTR, EBUF)  ((PTR)((char*)EBUF))
#define SETBUF(TYPE, NUM, EBUF) (EBUF.SetUsed(sizeof(TYPE) * NUM))
#define LOADBUF(EBUF) (EBUF.Used())

IDriver *pVerSys = NULL;

void help(char* Cmd)
{
    printf("%s \n \
                \r /1 get manufacturer id!\n \
                \r /2 get phone model id!\n \
                \r /3 get Firmware version!\n \
                \r /4 get Firmware Date!\n \
                \r /5 get Software version!\n \
                \r /6 get Software Date!\n \
                \r /7 get Hardware version!\n \
                \r /8 get Hardware Date!\n",
                Cmd);
}

int RequestMsg(int qid, char* buf, int len)
{
    ECode ec;
    ByteArray_Box ebbOutData((void*)buf, len, 0);
    ec = pVerSys->Control(qid, EZBYTEBUF_NULL, ebbOutData, NULL);
    if (FAILED(ec)) {
        return 1;
    }
    printf("info sys : %s\n", buf);
    return 0;
}

// get manufacturer id
int AlInfo_getMan(char* buf, int bufLen)
{
    return RequestMsg(INFO_GETVENDERID, buf, bufLen);
}
// get phone model id
int AlInfo_getModel(char* buf, int bufLen)
{
    return RequestMsg(INFO_GETMODEL, buf, bufLen);
}


// get Firmware info (optional)
int AlInfo_getFirmVer(char* buf, int bufLen)
{
    return RequestMsg(INFO_GETFIRMVER, buf, bufLen);
}

int AlInfo_getFirmDate(char* buf, int bufLen)
{
    return RequestMsg(INFO_GETFIRMDATE, buf, bufLen);
}


// get Software info (optional)
int AlInfo_getSoftVer(char* buf, int bufLen)
{
    return RequestMsg(INFO_GETSOFTVER, buf, bufLen);
}

int AlInfo_getSoftDate(char* buf, int bufLen)
{
    return RequestMsg(INFO_GETSOFTDATE, buf, bufLen);
}


// get Hardware info (optional)
int AlInfo_getHardVer(char* buf, int bufLen)
{
    return RequestMsg(INFO_GETHARDVER, buf, bufLen);
}

int AlInfo_getHardDate(char* buf, int bufLen)
{
    return RequestMsg(INFO_GETHARDDATE, buf, bufLen);
}


int __cdecl main(int argc, char *argv[])
{
    ECode ec = NOERROR;
    char buf[32];

    ec = CSystem::FindRunningObject(
       L"device:verinfo", (IInterface **)&pVerSys);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: verinfo, ec = 0x%08x\n", ec);
        goto __Exit;
    }

//    printf("Find Device Succeeded!\n");

    if (argc < 2) {
        help(argv[0]);
        goto __Exit;
    }


    if ( ( argv[1][0] == '/' ) && ( argv[1][2] == '\0' ) ) {
        switch(argv[1][1]) {
            case '1':
                AlInfo_getMan(buf, 32);
                break;

            case '2':
                AlInfo_getModel(buf, 32);
                break;

            case '3':
                AlInfo_getFirmVer(buf, 32);
                break;

            case '4':
                AlInfo_getFirmDate(buf, 32);
                break;

            case '5':
                AlInfo_getSoftVer(buf, 32);
                break;

            case '6':
                AlInfo_getSoftDate(buf, 32);
                break;

            case '7':
                AlInfo_getHardVer(buf, 32);
                break;

            case '8':
                AlInfo_getHardDate(buf, 32);
                break;

            default:
                help(argv[0]);
        }
    }
    else {
        help(argv[0]);
    }

__Exit:
    if (NULL != pVerSys) {
        pVerSys->Release();
    }
    return 0;
}

