//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

// FUNCTION: Test the basic function of video card
//           Including testing baseplane and overlay.
// NOTENOTE: This sample only support 19 bits RGB color now! (RGBT6:6:6)

#include <elastos.h>
#include <stdio.h>
#include <display.h>

void *pBasePlaneBufAddr = NULL; // base plane framebuffer

// overlay framebuffer
void *pOverlay1BufAddr = NULL;
unsigned int uOverlay1BufSize;

int ScreenWidth, ScreenHeight;
IDriver *pDevice = NULL;

static IDriver *s_pTouch;


BOOL  InitFrameBuf()
{
    BufferOf_<Byte, 32>      ezbModeName;
    BufferOf_<Byte, 32>      ezbOutMode;
    BufferOf_<Byte, 32>      ezbOutAddr;
    BufferOf_<Byte, sizeof(FrameBufferFormat)>     ezbOutFbFmt;
    FrameBufferFormat *pFbFmt;

    /////////////////////////////////////////////
    // Only used for x86
    ezbModeName.Copy(L"800*600*16", 10);
    pDevice->Control(2, ezbModeName, ezbOutMode, NULL);

    /////////////////////////////////////////////
    // Get baseplane framebuffer address, Param ezbOutMode only used for x86
    if (NOERROR != pDevice->Control(3, ezbOutMode, ezbOutAddr, NULL))
        return NULL;
    pBasePlaneBufAddr = (void *)(*(int *)(wchar_t *)ezbOutAddr);
    printf("pBasePlaneBufAddr = %x %x\n", pBasePlaneBufAddr, *(int *)(wchar_t *)ezbOutAddr);

    // Get the detail information of baseplane
    pDevice->Control(7, EZBYTEBUF_NULL, ezbOutFbFmt, NULL);
    pFbFmt = (FrameBufferFormat *)(wchar_t *)ezbOutFbFmt;

    if (pFbFmt->Color != COLOR_RGBT666) {
        printf("This sample must run with color format RGBT666!\n");
        return FALSE;
    }

    ScreenWidth = pFbFmt->Width;
    ScreenHeight = pFbFmt->Height;

    return TRUE;
}

BOOL InitOverlay()
{
    OverlayFormat *pOverlayFmt;
    BufferOf_<Byte, sizeof(OverlayFormat)>     ezbInFbFmt;
    BufferOf_<Byte, sizeof(OverlayFormat)>     ezbOutFbFmt;

    pOverlayFmt = (OverlayFormat *)(wchar_t *)ezbInFbFmt;
    pOverlayFmt->Enable = TRUE;
    pOverlayFmt->Color = COLOR_RGBT666;
    pOverlayFmt->Layer = 1; // Use overlay1
    pOverlayFmt->Bpp = 19; //
    pOverlayFmt->Width = ScreenWidth;
    pOverlayFmt->Height = ScreenHeight;
    pOverlayFmt->PosX = 0;
    pOverlayFmt->PosY = 0;
    ezbInFbFmt.SetUsed(sizeof(OverlayFormat));

    if (NOERROR != pDevice->Control(8, ezbInFbFmt, ezbOutFbFmt, NULL)) {
        return FALSE;
    }

    pOverlayFmt = (OverlayFormat *)(wchar_t *)ezbOutFbFmt;

    pOverlay1BufAddr = pOverlayFmt->pChannelFb[0];
    uOverlay1BufSize = pOverlayFmt->ChannelSize[0];

    assert(pOverlayFmt->Width == ScreenWidth);
    assert(pOverlayFmt->Height == ScreenHeight);

    return TRUE;
}

void DrawPanel()
{
    for (int i = 0; i <= ScreenHeight - 1; i++) {
        for (int j = 0; j <= ScreenWidth - 1; j++) {
            ((DWORD *)pBasePlaneBufAddr)[i * ScreenWidth + j] = 0x00003f;
        }
    }
}

void SetMode(int mode)
{
    BufferOf_<Byte, sizeof(int)> handParamBuf;
    *(int *)(char *)handParamBuf = mode;
    handParamBuf.SetUsed(sizeof(int));
    s_pTouch->Control(4, handParamBuf, EZBYTEBUF_NULL, NULL);
}

int main(int argc, char ** argv)
{
    HRESULT hr;

    hr = CSystem::FindRunningObject(
            L"device:display0", (IInterface **)&pDevice);
    if (FAILED(hr)) {
        printf("ERROR: Can't find Service: display, hr = 0x%08x\n", hr);
        return 1;
    }

    if (!InitFrameBuf()) {
        printf("Cann't init frame buffer.\n");
        return 1;
    }
    printf("Init frame buffer OK!\n");

    hr = CSystem::FindRunningObject(
            L"device:touch", (IInterface **)&s_pTouch);
    if (FAILED(hr)) {
        printf("ERROR: Can't find Service: touch, hr = 0x%08x\n", hr);
        return 1;
    }
    printf("Init touch OK!\n");

    printf("open handwriting\n");
    DrawPanel();

    int option;
    while (1) {
		printf("*******HANDINPUT TESTING*******\n");
		printf("0. Mode 0\n");
	    printf("1. Mode 1\n");
	    printf("9. Quit\n");

	    printf("Your Choice:");

	    scanf("%d", &option);
		switch (option) {
		    case 0:
                SetMode(0);
		    	break;

		    case 1:
                SetMode(1);
		    	break;

            case 9:
                // Quit camera
                goto _exit;

		    default:
		    	break;
        }
        getchar(); // Avoid bugs for scanf
	}

_exit:
    printf("quit handwriting\n");
//    s_pTouch->Control(5, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);

    if (!InitFrameBuf()) {
        printf("Cann't init frame buffer.\n");
        return 1;
    }

    return 0;
}
