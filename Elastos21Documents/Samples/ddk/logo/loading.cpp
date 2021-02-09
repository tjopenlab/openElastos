//==========================================================================
// 科泰世纪科技有限公司 版权所有 2000年--2004年
// Copyright (c) 2000-2004,  KoreTide Corp.  All Rights Reserved.
//==========================================================================
#include <elastos.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "display.h"


#define PIC_FILE "screen.bmp"

#if defined(_techfaith)
#define MobileBits  19
#else
#define MobileBits  16
#endif

#define MobileWidth     240
#define MobileHeight    320
#define Color32To19(color32) (DWORD)(/*0x00040000 |*/ (((color32) & 0xFC0000) >> 6) | \
                                (((color32) & 0x00FC00) >> 4) | \
                                (((color32) & 0x0000FC) >> 2))

#define Color32To16(color32) (WORD)((((color32) & 0xF80000) >> 8) | \
                                (((color32) & 0x00FC00) >> 5) | \
                                (((color32) & 0x0000F8) >> 3))
IDriver *pDevice = NULL;

static ADDRESS g_FrameBuffer;

void ShowPic(byte *pSrc, int nBmpBufSize, int nByteCount, DWORD *target)
{
#if MobileBits == 16
    WORD *pPixels = (WORD *)target;
#else
    DWORD *pPixels = (DWORD *)target;
#endif
    printf("width %d,nByteCount %d\n",MobileBits,nByteCount);
    int nBytesPerLine = MobileWidth * nByteCount;
    byte *pLine;
    int i, j;

    if (nByteCount == 4) {
        memcpy(pPixels, pSrc, nBmpBufSize);
    }
    else {
        for (i = 0; i < MobileHeight; i++) {
            pLine = pSrc + (MobileHeight - i - 1) * nBytesPerLine;
            for (j = 0; j < MobileWidth; j++, pLine += 3) {
                DWORD Value = 0;
                memcpy(&Value, pLine, 3);
#if MobileBits == 16
                *pPixels++ = Color32To16(Value);
#else
                *pPixels++ = Color32To19(Value);
#endif
            }
        }
    }
    //printf("byte 0,1,2,3 is %x %x %x %x \n",target[38386],target[38387],target[38388],target[38389]);
    return;
}

int open(char * file, DWORD *target)
{
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    byte *pBmp;
    int nBmpBufSize, nByteCount;

    printf("Open [%s]\n", file);

    FILE *fp = fopen(file, "rb");

    if (!fp) {
        wprintf(L"Cannot load picture from file!\n");
        goto Error;
    }

    if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp) != 1) {
        wprintf(L"Cannot read picture info from file!\n");
        goto Error;
    }

    if (fileHeader.bfType != ((WORD)('M' << 8) | 'B')) {
        wprintf(L"Cannot read picture info from file!\n");
        goto Error;
    }

    if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp) != 1) {
        wprintf(L"Cannot read picture info from file!\n");
        goto Error;
    }

    wprintf(L"biBitCount %d\n", infoHeader.biBitCount);

    if (infoHeader.biBitCount != 24
        //&&infoHeader.biBitCount != 16 && infoHeader.biBitCount != 32
        ) {
        wprintf(L"Doesn't support the color format of the file!\n");
        goto Error;
    }

    if (infoHeader.biWidth != MobileWidth && infoHeader.biHeight != MobileHeight) {
        wprintf(L"The width of picture read from file is not correct!\n");
        goto Error;
    }

    if (fseek(fp, fileHeader.bfOffBits, SEEK_SET) != 0) {
        wprintf(L"Cannot read picture info from file!\n");
        goto Error;
    }

    nByteCount = infoHeader.biBitCount / 8;
    nBmpBufSize = MobileWidth * MobileHeight * nByteCount;
    pBmp = new byte[nBmpBufSize];
    printf("size %d\n",nBmpBufSize);
    fread(pBmp, nBmpBufSize, 1, fp);

    ShowPic(pBmp, nBmpBufSize, nByteCount, target);
    fclose(fp);

    delete pBmp;

Error:
    if (fp) fclose(fp);
    return 0;
}

int main(int argc, char *argv[])
{
    ECode ec;
    BufferOf<Byte> ebbData;
    char * temp;
    if(argc!=2) {
        printf("usage :logo logo.bmp\n");
        return 0;
    }
    char * file = argv[1];
    if (argc > 1) {
        file = argv[1];
    }

    ec = CSystem::FindRunningObject(
            L"device:docstorage0", (IInterface **)&pDevice);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: display, ec = 0x%08x\n", ec);
        goto _exit;
    }

    wprintf(L"CSystem::FindRunningObject docstorage0 OK!\n");

    // Get display virtual address
    temp = new char[320*240*2];
    ebbData = ByteArray_Box(temp,320*240*2,320*240*2);
    printf("Lcd Base Address %08x\n", temp);
    g_FrameBuffer = (int)temp;
    printf("g_FrameBuffer addr = %x\n", g_FrameBuffer);
    open(file, (DWORD *)g_FrameBuffer);
    pDevice->Control(0x10000013/*WriteLogo*/, ebbData, EZBYTEBUF_NULL, NULL);
    printf("Setting loading logo done !\n");


    getchar();

_exit:
    delete temp;
    if (pDevice) pDevice->Release();
    return 0;
}
