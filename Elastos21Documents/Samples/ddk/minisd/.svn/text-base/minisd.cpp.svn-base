//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define T_SIZE      (1024 * 1024 * 40)
#define T_R_OFFSET  (1024 * 1024 * 4)
#define T_W_OFFSET  (1024 * 1024 * 4)

IDriver *pDevice = NULL;

void DumpGpio(long* value)
{
    printf("GPLR0 : %08x\n", value[0]);
    printf("GPLR1 : %08x\n", value[1]);
    printf("GPLR2 : %08x\n", value[2]);
    printf("GPLR3 : %08x\n", value[3]);

    printf("GPDR0 : %08x\n", value[4]);
    printf("GPDR1 : %08x\n", value[5]);
    printf("GPDR2 : %08x\n", value[6]);
    printf("GPDR3 : %08x\n", value[7]);

    printf("GRER0 : %08x\n", value[8]);
    printf("GRER1 : %08x\n", value[9]);
    printf("GRER2 : %08x\n", value[10]);
    printf("GRER3 : %08x\n", value[11]);

    printf("GFER0 : %08x\n", value[12]);
    printf("GFER1 : %08x\n", value[13]);
    printf("GFER2 : %08x\n", value[14]);
    printf("GFER3 : %08x\n", value[15]);

    printf("GEDR0 : %08x\n", value[16]);
    printf("GEDR1 : %08x\n", value[17]);
    printf("GEDR2 : %08x\n", value[18]);
    printf("GEDR3 : %08x\n", value[19]);
}

void __cdecl outs(byte* buf, UINT buflen)
{
    printf("\n");
    int linCnt = buflen >> 4;
    int line, clum = 0;
    for (line = 0; line < linCnt; line++) {
        if ((line % 0x20) == 0) {
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        }
        printf("%04x\t", line*0x10);
        for(clum = 0; clum < 0x10; clum++)
            printf("%02x ", buf[line*0x10+clum]);
        printf("\n");
    }
    printf("line number : %d, clum : %d, Bytes : %d\n",
        line, clum, line*clum);
}

void seqread(byte *pBuf, UINT off, UINT siz, UINT blklen)
{
    UINT Size = siz;
    int tmp[2];
    time_t t1,t2;
    ECode hr;
    time(&t1);
    ByteArray_Box ebbCapData((void*)tmp, 8, 0);
    pDevice->Control(212, \
        EZBYTEBUF_NULL, ebbCapData, NULL);
    ByteArray_Box ebbData(pBuf, blklen, 0);
    while(Size > 0) {
        hr = pDevice->Read(off, blklen, ebbData, NULL);
        if (FAILED(hr) || (ebbData.Used() != (int)blklen)) {
            printf("Read Failed\n");
            return;
        }
        off += blklen;
        Size -= blklen;
        if (( Size % 0x20000) == 0)
            printf("\r%d", Size);
    }
    time(&t2);
    outs(pBuf, blklen);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("offset sector %d\n", (off>>9));
    printf("t2 - t1 = %d sec\n", t2 - t1);
    printf("seqread Speed %.2f bytes/s\n", (siz) / (t2 - t1));
}


void seqwrite(byte *pBuf, UINT off, UINT siz, UINT blklen)
{
    UINT result = 0, Size = siz;
    time_t t1,t2;
    ECode hr;
    time(&t1);
    ByteArray_Box ebbData(pBuf, blklen, blklen);
    while(Size > 0) {
        hr = pDevice->Write(off, ebbData, &result, NULL);
        if (FAILED(hr) || (result != blklen)) {
            printf("write Failed\n");
            return;
        }
        off += blklen;
        Size -= blklen;
        if (( Size % 0x20000) == 0)
            printf("\r%d", Size);
    }
    time(&t2);
    outs(pBuf, blklen);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("offset sector %d\n", (off>>9));
    printf("t2 - t1 = %d sec\n", t2 - t1);
    printf("seqwrite Speed %.2f bytes/s\n", (siz) / (t2 - t1));
}

void seqmix(byte *pBuf, UINT off, UINT siz, UINT blklen)
{
    UINT result = 0, Size = siz;
    time_t t1,t2;
    ECode hr;
    time(&t1);
    ByteArray_Box ebbData(pBuf, blklen, 0);
    while(Size > 0) {
        hr = pDevice->Read(off - T_R_OFFSET , blklen, ebbData, NULL);
        if (FAILED(hr) || (ebbData.Used() != (int)blklen)) {
            printf("read Failed\n");
            return;
        }
        hr = pDevice->Write(off, ebbData, &result, NULL);
        if (FAILED(hr) || (result != blklen)) {
            printf("write Failed\n");
            return;
        }
        ebbData.SetUsed(0);
        off += blklen;
        Size -= blklen;
        if (( Size % 0x20000) == 0)
            printf("\r%d", Size);
    }
    time(&t2);
    outs(pBuf, blklen);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("offset sector %d\n", (off>>9));
    printf("t2 - t1 = %d sec\n", t2 - t1);
    printf("seqwrite Speed %.2f bytes/s\n", (siz) / (t2 - t1));
}

void StressTest(byte* pInBuf, byte* pOutBuf, UINT off, UINT siz, UINT blklen)
{
    UINT result = 0, Size = siz;
    time_t t1,t2;
    ECode hr;
    time(&t1);
    ByteArray_Box ebbInData(pInBuf, blklen);
    ByteArray_Box ebbOutData(pOutBuf, blklen, 0);
    while(Size > 0) {
        hr = pDevice->Write(off, ebbInData, &result, NULL);
        if (FAILED(hr) || (result != blklen)) {
            printf("write Failed\n");
            return;
        }
        ebbOutData.SetUsed(0);
        hr = pDevice->Read(off, blklen, ebbOutData, NULL);
        if (FAILED(hr) || (ebbOutData.Used() != (int)blklen)) {
            printf("read Failed\n");
            return;
        }

        if (memcmp(pInBuf, pOutBuf, blklen)) {
            printf("read write not equal!\n");
            goto __Exit;
        }
        off += blklen;
        Size -= blklen;
        if (( Size % 0x20000) == 0)
            printf("\r%d", Size);
    }
__Exit:
    time(&t2);
    outs(pOutBuf, blklen);
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("offset sector %d\n", (off>>9));
    printf("t2 - t1 = %d sec\n", t2 - t1);
    printf("seqwrite Speed %.2f bytes/s\n", (siz) / (t2 - t1));
}

void help(char * str)
{
    printf("%s \n \
               \r -r test seq read\n \
               \r -b test seq read boot sector\n \
               \r -w test seq write\n \
               \r -m test mix r/w\n \
               \r -s strees test\n \
               \r -n not align test\n \
               \r -1 SD Bus Suspend\n \
               \r -2 SD Bus Resume\n \
               \r -3 SD Bus Power On\n \
               \r -4 Initialize MiniSD Card\n \
               \r -5 Dump GPIO Registers Value\n", str);
}

void setBuffer( byte* buffer, byte* sign, int buflen, int signlen)
{
    byte *Buf = buffer;
    int len = buflen, Cnt = 0;
    while (len) {
        Cnt = (len > signlen) ? signlen : len;
        memcpy(Buf, sign, Cnt);
        len -= Cnt;
        Buf += Cnt;
    }
}

int main(int argc, char *argv[])
{
    ECode hr;
    char *sign = "This My Signature";
    byte Buffer[4096 * 4];
    byte Obuf[4096 * 4];
    ByteArray_Box ebbOutData(Obuf, 4096, 0);

    if (argc != 2) {
        help(argv[0]);
        goto exit;
    }

    hr = CSystem::FindRunningObject(
        L"device:minisdbus", (IInterface **)&pDevice);
    if (FAILED(hr)) {
        printf("ERROR: Can't find Service: usbser, hr = 0x%08x\n", hr);
        goto exit;
    }

    printf("find Service minisdbus OK!\n");



    if ( ( argv[1][0] == '-' ) && ( argv[1][2] == '\0' ) ) {
        switch(argv[1][1]) {
            case 'r':
            case 'R':
                /*****
                 *  test read
                 *
                *****/
                seqread(Buffer, T_R_OFFSET, T_SIZE, 4096);
                break;

            case 'b':
            case 'B':
                /*****
                 *  test read
                 *
                *****/
                seqread(Buffer, 0, 4096, 4096);
                break;

            case 'w':
            case 'W':
                /*****
                 *  test write
                 *
                *****/
                memset(Buffer, 0x44, 4096);
                seqwrite(Buffer, T_W_OFFSET, T_SIZE, 4096);
                break;

            case 'm':
            case 'M':
                /*****
                 *  test mix read write
                 *
                *****/
                memset(Buffer, 0xFF, 4096 * 2);
                seqmix(Buffer, T_W_OFFSET, T_SIZE, 4096 *2);
                break;

            case 's':
            case 'S':
                /*****
                 *  test stress align
                 *
                *****/
                setBuffer(Buffer, (byte*)sign, 4096, strlen(sign));
                StressTest(Buffer, Obuf, T_W_OFFSET, T_SIZE, 4096);
                break;

            case 'n':
            case 'N':
                /*****
                 *  test stress not align
                 *
                *****/
                setBuffer(Buffer + 1, (byte*)sign, 4096, strlen(sign));
                StressTest(Buffer+1, Obuf, T_W_OFFSET, T_SIZE, 4096);
                break;

            case '1'://Suspend
                printf("Test SD Bus Suspend ... !\n");
                pDevice->Control(1000, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;

            case '2'://Resume
                printf("Test SD Bus Resume ... !\n");
                pDevice->Control(1001, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;

            case '3'://Power On
                printf("Test SD Bus Power On ... !\n");
                pDevice->Control(1002, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;

            case '4'://Initialize MiniSD CARD
                printf("Test SD Bus Mount SD Card & Initialize ... !\n");
                pDevice->Control(200, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
                break;

            case '5'://Dump GPIO
                printf("Dump GPIO Registers:\n");
                pDevice->Control(2006, EZBYTEBUF_NULL, ebbOutData, NULL);
                DumpGpio((long*)((char*)ebbOutData));
                break;

            default:
                help(argv[0]);
        }
    }
    else {
        help(argv[0]);
    }

exit:
    if (NULL != pDevice)
        pDevice->Release();

    return 0;
}

