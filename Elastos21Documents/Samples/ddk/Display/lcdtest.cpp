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
static ADDRESS g_Overlay2Buffer_ChanY;
static ADDRESS g_Overlay2Buffer_ChanCb;
static ADDRESS g_Overlay2Buffer_ChanCr;

void zee_video_cleanup(void)
{
    BufferOf_<Byte, 1> buf;
    pDevice->Control(0, buf, buf, NULL);//set default
    // clean screen
    memset((UINT *)g_FrameBuffer, 0x00040000, (MobileWidth * MobileHeight)>>5);

    return;
}

void zee_lay2_cleanup(void)
{
    // clean screen
    BYTE *pPixels = (BYTE *)g_Overlay2Buffer_ChanY;
    BYTE *pPixels1 = (BYTE *)g_Overlay2Buffer_ChanCb;
    BYTE *pPixels2 = (BYTE *)g_Overlay2Buffer_ChanCr;
    DWORD Value = 0;

    memset(pPixels, Value, 320 * 240);
    memset(pPixels1, Value, 320 * 120);
    memset(pPixels2, Value, 320 * 120);
}

void ShowPic(byte *pSrc, int nBmpBufSize, int nByteCount, DWORD *target)
{
#if MobileBits == 16
    WORD *pPixels = (WORD *)target;
#else
    DWORD *pPixels = (DWORD *)target;
#endif
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
        wprintf(L"This simulator doesn't support the color format of the file!\n");
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
//    char option;
    OverlayFormat overlay2;
    UINT32 lcd_base;
    char * file = PIC_FILE;
    if (argc > 1) {
        file = argv[1];
    }

    ec = CSystem::FindRunningObject(
            L"device:display0", (IInterface **)&pDevice);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: display, ec = 0x%08x\n", ec);
        return 1;
    }

    wprintf(L"CSystem::FindRunningObject display OK!\n");

    // Get display virtual address
    BufferOf<Byte> ebbData = BufferOf<Byte>::AllocByteBuf(10);
    ec = pDevice->Control( 3, ebbData, ebbData, NULL );
    char *tmp = (char *)ebbData;
    UINT32 *eData = (UINT32*)tmp;
    if (FAILED(ec)) {
        printf("Get LCD BASE Address Failed!\n");
        goto _exit;
    }

    lcd_base = eData[0];
    printf("Lcd Base Address %08x\n", lcd_base);
    g_FrameBuffer = lcd_base;
    printf("g_FrameBuffer addr = %x\n", g_FrameBuffer);

    overlay2.Bpp = 16;
    overlay2.Width = MobileWidth;
    overlay2.Height = MobileHeight;
    overlay2.PosX = overlay2.PosY = 0;
    zee_video_cleanup();
    // Set LCD panel GSMode
//    pDevice->SetSize(18);
    open(file, (DWORD *)g_FrameBuffer);

//    zee_video_cleanup();
        // Set LCD panel GSMode
        //pDevice->SetSize(18);

    printf("Setting brightness done !\n");


    getchar();

_exit:
    BufferOf<Byte>::FreeByteBuf(ebbData);
    pDevice->Release();
    return 0;
}
