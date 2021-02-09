//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

// CAMERA TEST CODE
// NOTE: USE RGBT666 in Base Plane
//       USE YCbCr422 in Overlay2

#include <elastos.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <display.h>
#include <camera.h>

#define DisplayName L"dev/display"
#define CameraName L"dev/Camera"

#ifdef _gingko
#define YUVDATA_FILE "YCbCr%d.dat" // Improve write speed
#define CameraColor USHORT
#define BasicColor 0x8000
#elif defined( _techfaith)
#define YUVDATA_FILE "YCbCr%d.dat" // Improve write speed
#define CameraColor UINT
#define BasicColor 0x40000
#else
#define YUVDATA_FILE "YCbCr%d.dat"
#define CameraColor USHORT
#define BasicColor 0x8000
#endif

int g_nScreenWidth = 240;
int g_nScreenHeight = 320;

// Size of camera preview window
#define CAMERA_WIN_POSX 0
#define CAMERA_WIN_POSY 0
#define CAMERA_WIN_WIDTH g_nScreenWidth
#define CAMERA_WIN_HEIGHT g_nScreenHeight

static void * g_FrameBuffer; // Baseplane framebuffer address

// Overlay2 framebuffer address of 3 channels
static void *g_pOverlayYBufAddr;
static void *g_pOverlayCbBufAddr;
static void *g_pOverlayCrBufAddr;
// Overlay2 framebuffer size of 3 channels
static UINT g_uOverlayYBufSize;
static UINT g_uOverlayCbBufSize;
static UINT g_uOverlayCrBufSize;

IDriver *g_pDisplay = NULL;
IDriver *g_pCamera = NULL;

static IEvent *g_pRecordEvent = NULL;
static BOOL g_bRecording = FALSE;
static BOOL g_bThreadRun = FALSE;
static BYTE *g_pVideoBuffer = NULL;
static int g_recVideoWidth, g_recVideoHeight;

// If you use graphics system, you should not write this function again.
// Because this code is included in GDI system.
BOOL  InitFrameBuf()
{
    BufferOf_<Byte, 32>      ezbModeName;
    BufferOf_<Byte, 32>      ezbOutMode;
    BufferOf_<Byte, 32>      ezbOutAddr;
    BufferOf_<Byte, sizeof(FrameBufferFormat)>     ezbOutFbFmt;
    FrameBufferFormat *pFbFmt;

    ECode ec = CSystem::FindRunningObject(
            L"device:display0", (IInterface **)&g_pDisplay);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: display, ec = 0x%08x\n", ec);
        return FALSE;
    }

    /////////////////////////////////////////////
    // Only used for x86
    ezbModeName.Copy(L"800*600*16", 10);
    g_pDisplay->Control(2, ezbModeName, ezbOutMode, NULL);

    /////////////////////////////////////////////
    // Get baseplane framebuffer address, Param ezbOutMode only used for x86
    if (NOERROR != g_pDisplay->Control(3, ezbOutMode, ezbOutAddr, NULL))
        return NULL;
    g_FrameBuffer = (void *)(*(int *)(wchar_t *)ezbOutAddr);
    printf("g_FrameBuffer = %x %x\n", g_FrameBuffer, *(int *)(wchar_t *)ezbOutAddr);

    // Get the detail information of baseplane
    g_pDisplay->Control(7, EZBYTEBUF_NULL, ezbOutFbFmt, NULL);
    pFbFmt = (FrameBufferFormat *)(wchar_t *)ezbOutFbFmt;

//    if (pFbFmt->Color != COLOR_RGBT666) {
//        printf("This sample must run with color format RGBT666!\n");
//        return FALSE;
//    }

    g_nScreenWidth = pFbFmt->Width;
    g_nScreenHeight = pFbFmt->Height;

    return TRUE;
}

void FrameBufferSet(CameraColor *pBuf, UINT Color, UINT Size)
{
    UINT i = 0;

    while (i++ < Size) {
        *pBuf++ = Color;
    }
}

void ClearOverlay2(void)
{
    // g_pOverlayYBufAddr is already a virtual address
    memset(g_pOverlayYBufAddr, 0xFF, g_uOverlayYBufSize);
    memset(g_pOverlayCbBufAddr, 0x80, g_uOverlayCbBufSize);
    memset(g_pOverlayCrBufAddr, 0x80, g_uOverlayCrBufSize);
}

int saveYCbCrdata(BYTE *pSnapFrame, int nSize)
{
    char szBmpFilePath[_MAX_PATH];
    static int FileIndex = 0;
    assert(pSnapFrame != NULL);

    sprintf(szBmpFilePath, YUVDATA_FILE, FileIndex++);
    printf("File name : %s\n", szBmpFilePath);
    FILE *fp = fopen(szBmpFilePath, "wb");

    if (fp == NULL) {
        wprintf(L"Cannot open data file!\n");
        return 1;
    }

    fwrite(pSnapFrame, 1, nSize, fp);

    fclose(fp);

    return 0;
}

BOOL ConfigureOverlay2()
{
    OverlayFormat *pOverlayFmt;
    BufferOf_<Byte, sizeof(OverlayFormat)>     ezbInFbFmt;
    BufferOf_<Byte, sizeof(OverlayFormat)>     ezbOutFbFmt;

    pOverlayFmt = (OverlayFormat *)(wchar_t *)ezbInFbFmt;


    pOverlayFmt->Enable = TRUE;
    pOverlayFmt->Color = COLOR_YCbCr422; // MUST
    pOverlayFmt->Flag = 1;
    pOverlayFmt->Layer = 2; // Use overlay2
    pOverlayFmt->Bpp = 16; // YCrCb422
    pOverlayFmt->Width = CAMERA_WIN_WIDTH;
    pOverlayFmt->Height = CAMERA_WIN_HEIGHT;

    pOverlayFmt->PosX = CAMERA_WIN_POSX;
    pOverlayFmt->PosY = CAMERA_WIN_POSY;

    ezbInFbFmt.SetUsed(sizeof(OverlayFormat));

    if (NOERROR != g_pDisplay->Control(8, ezbInFbFmt, ezbOutFbFmt, NULL)) {
        return FALSE;
    }

    // Get the whole information about overlay2
    pOverlayFmt = (OverlayFormat *)(wchar_t *)ezbOutFbFmt;

    g_pOverlayYBufAddr = pOverlayFmt->pChannelFb[0];
    g_pOverlayCbBufAddr = pOverlayFmt->pChannelFb[1];
    g_pOverlayCrBufAddr = pOverlayFmt->pChannelFb[2];

    g_uOverlayYBufSize = pOverlayFmt->ChannelSize[0];
    g_uOverlayCbBufSize = pOverlayFmt->ChannelSize[1];
    g_uOverlayCrBufSize = pOverlayFmt->ChannelSize[2];

    assert(pOverlayFmt->Width == g_nScreenWidth);
//    assert(pOverlayFmt->Height == g_nScreenHeight);

    ClearOverlay2();

    return TRUE;
}

BOOL ConfigureDisplay()
{
    InitFrameBuf();
    assert(g_FrameBuffer);

    // Clear base plane
    FrameBufferSet((CameraColor *)g_FrameBuffer, 0, g_nScreenWidth * g_nScreenHeight);

    // Set the preview window transparency in base plane.
    // NOTE: To use this simple way, the conditions should be satisfied:
    // 1. CAMERA_WIN_POSX == 0
    // 2. CAMERA_WIN_WIDTH == g_nScreenWidth
    FrameBufferSet((CameraColor *)g_FrameBuffer + CAMERA_WIN_POSY * g_nScreenWidth,
        BasicColor, CAMERA_WIN_WIDTH * CAMERA_WIN_HEIGHT);

    return ConfigureOverlay2();
}

BOOL ConfigureCamera()
{
    ECode ec;

    ec = CSystem::FindRunningObject(
            L"device:camera0", (IInterface **)&g_pCamera);
    if (FAILED(ec)) {
        printf("ERROR: Can't find Service: camera, ec = 0x%08x\n", ec);
        return FALSE;
    }

    // Initialize camera device
    ec = g_pCamera->Control(0, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
    if (FAILED(ec)) {
        printf("ERROR: Can't init camera, ec = 0x%08x\n", ec);
        return FALSE;
    }

    return TRUE;
}

void ReleaseDisplay()
{
    if (g_pDisplay) g_pDisplay->Release();
}

void ReleaseCamera()
{
    if (g_pCamera) {
        // Quit camera device
        g_pCamera->Control(1, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
        g_pCamera->Release();
    }
}

void AdjustBrightness()
{
    ECode ec;
    unsigned long value;

    printf("Input the brightness(0 ~ 255):");
    scanf("%d", &value);

    if (value <= 255) {
        BufferOf_<Byte, sizeof(Camera_Format)>  ezbInFmt;
        Camera_Format *pFormat;

        pFormat = (Camera_Format *)(char *)ezbInFmt;
        pFormat->nID = CAMERA_FORMAT_BRIGHTNESS;
        pFormat->wParam = value;
        pFormat->lParam = 0;
        ezbInFmt.SetUsed(sizeof(Camera_Format));

        ec = g_pCamera->Control(6, ezbInFmt, EZBYTEBUF_NULL, NULL);
        if (FAILED(ec)) {
            printf("Error in setting format for camera. ec = 0x%08x.\n", ec);
            return;
        }
    }
    else {
        printf("Plese input the right value for brightness.\n");
    }
}

void AdjustContrast()
{
    ECode ec;
    unsigned long value;

    printf("Input the contrast(0 ~ 255):");
    scanf("%d", &value);

    if (value <= 255) {
        BufferOf_<Byte, sizeof(Camera_Format)>  ezbInFmt;
        Camera_Format *pFormat;

        pFormat = (Camera_Format *)(char *)ezbInFmt;
        pFormat->nID = CAMERA_FORMAT_CONTRAST;
        pFormat->wParam = value;
        pFormat->lParam = 0;
        ezbInFmt.SetUsed(sizeof(Camera_Format));

        ec = g_pCamera->Control(6, ezbInFmt, EZBYTEBUF_NULL, NULL);
        if (FAILED(ec)) {
            printf("Error in setting format for camera. ec = 0x%08x.\n", ec);
            return;
        }
    }
    else {
        printf("Plese input the right value for contrast.\n");
    }
}

void AdjustSharpness()
{
    ECode ec;
    unsigned long value;

    printf("Input the sharpness(0 ~ 6):");
    scanf("%d", &value);

    if (value < 7) {
        BufferOf_<Byte, sizeof(Camera_Format)>  ezbInFmt;
        Camera_Format *pFormat;

        pFormat = (Camera_Format *)(char *)ezbInFmt;
        pFormat->nID = CAMERA_FORMAT_SHARPNESS;
        pFormat->wParam = value;
        pFormat->lParam = 0;
        ezbInFmt.SetUsed(sizeof(Camera_Format));

        ec = g_pCamera->Control(6, ezbInFmt, EZBYTEBUF_NULL, NULL);
        if (FAILED(ec)) {
            printf("Error in setting format for camera. ec = 0x%08x.\n", ec);
            return;
        }
    }
    else {
        printf("Plese input the right value for sharpness.\n");
    }
}

void AdjustWhiteBalance()
{
    ECode ec;
    unsigned long value;

    printf("Input the white balance(0 ~ 4):");
    scanf("%d", &value);

    if (value < 5) {
        BufferOf_<Byte, sizeof(Camera_Format)>  ezbInFmt;
        Camera_Format *pFormat;

        pFormat = (Camera_Format *)(char *)ezbInFmt;
        pFormat->nID = CAMERA_FORMAT_WHITEBALANCE;
        pFormat->wParam = value;
        pFormat->lParam = 0;
        ezbInFmt.SetUsed(sizeof(Camera_Format));

        ec = g_pCamera->Control(6, ezbInFmt, EZBYTEBUF_NULL, NULL);
        if (FAILED(ec)) {
            printf("Error in setting format for camera. ec = 0x%08x.\n", ec);
            return;
        }
    }
    else {
        printf("Plese input the right value for sharpness.\n");
    }
}

void AdjustCamera_ColorMode()
{
    ECode ec;
    unsigned long value;

    printf("Input the color mode(0 ~ 8):");
    scanf("%d", &value);

    BufferOf_<Byte, sizeof(Camera_Format)>  ezbInFmt;
    Camera_Format *pFormat;

    pFormat = (Camera_Format *)(char *)ezbInFmt;
    pFormat->nID = CAMERA_FORMAT_COLORMODE;
    pFormat->wParam = value;
    pFormat->lParam = 0;
    ezbInFmt.SetUsed(sizeof(Camera_Format));

    ec = g_pCamera->Control(6, ezbInFmt, EZBYTEBUF_NULL, NULL);
    if (FAILED(ec)) {
        printf("Error in setting format for camera. ec = 0x%08x.\n", ec);
    }

}

void AdjustCamera_SceneMode()
{
    ECode ec;
    unsigned long value;

    printf("Input the scene mode(0 ~ 5):");
    scanf("%d", &value);

    BufferOf_<Byte, sizeof(Camera_Format)>  ezbInFmt;
    Camera_Format *pFormat;

    pFormat = (Camera_Format *)(char *)ezbInFmt;
    pFormat->nID = CAMERA_FORMAT_SCENEMODE;
    pFormat->wParam = value;
    pFormat->lParam = 0;
    ezbInFmt.SetUsed(sizeof(Camera_Format));

    ec = g_pCamera->Control(6, ezbInFmt, EZBYTEBUF_NULL, NULL);
    if (FAILED(ec)) {
        printf("Error in setting format for camera. ec = 0x%08x.\n", ec);
        return;
    }

}

void AdjustCamera_PhotoResolution()
{
    ECode ec;
    unsigned long value;

    printf("Input the photo quality(0 ~ 2):");
    scanf("%d", &value);

    BufferOf_<Byte, sizeof(Camera_Format)>  ezbInFmt;
    Camera_Format *pFormat;

    pFormat = (Camera_Format *)(char *)ezbInFmt;
    pFormat->nID = CAMERA_FORMAT_PHOTO_RESOLUTION;
    pFormat->wParam = value;
    pFormat->lParam = 0;
    ezbInFmt.SetUsed(sizeof(Camera_Format));

    ec = g_pCamera->Control(6, ezbInFmt, EZBYTEBUF_NULL, NULL);
    if (FAILED(ec)) {
        printf("Error in setting format for camera. ec = 0x%08x.\n", ec);
        return;
    }

}

void AdjustCamera_VideoResolution()
{
    ECode ec;
    unsigned long value;

    printf("Input the video quality(0 ~ 1):");
    scanf("%d", &value);

    BufferOf_<Byte, sizeof(Camera_Format)>  ezbInFmt;
    Camera_Format *pFormat;

    pFormat = (Camera_Format *)(char *)ezbInFmt;
    pFormat->nID = CAMERA_FORMAT_VIDEO_RESOLUTION;
    pFormat->wParam = value;
    pFormat->lParam = 0;
    ezbInFmt.SetUsed(sizeof(Camera_Format));

    ec = g_pCamera->Control(6, ezbInFmt, EZBYTEBUF_NULL, NULL);
    if (FAILED(ec)) {
        printf("Error in setting format for camera. ec = 0x%08x.\n", ec);
        return;
    }

}

void AdjustDigitalZoom()
{
    ECode ec;
    unsigned long value;

    printf("Input the digital zoom(1 ~ 4):");
    scanf("%d", &value);

    if (value > 0 && value <= 4) {
        // NOTE: Zoom = wParam / lParam
        // So lParam should be set 1
        BufferOf_<Byte, sizeof(Camera_Format)>  ezbInFmt;
        Camera_Format *pFormat;

        pFormat = (Camera_Format *)(char *)ezbInFmt;
        pFormat->nID = CAMERA_FORMAT_ZOOM;
        pFormat->wParam = value;
        pFormat->lParam = 1;
        ezbInFmt.SetUsed(sizeof(Camera_Format));
        ec = g_pCamera->Control(6, ezbInFmt, EZBYTEBUF_NULL, NULL);
        if (FAILED(ec)) {
            printf("Error in setting format for camera. ec = 0x%08x.\n", ec);
            return;
        }
    }
    else {
        printf("Plese input the right value for digital zoom.\n");
    }
}

void AdjustContinuousSnap()
{
    ECode ec;
    unsigned long value;

    printf("Input the continuous snap(1 ~ 16):");
    scanf("%d", &value);

    BufferOf_<Byte, sizeof(Camera_Format)>  ezbInFmt;
    Camera_Format *pFormat;

    pFormat = (Camera_Format *)(char *)ezbInFmt;
    pFormat->nID = CAMERA_FORMAT_CONTINUOUS_SNAP;
    pFormat->wParam = value;
    pFormat->lParam = 0;
    ezbInFmt.SetUsed(sizeof(Camera_Format));
    ec = g_pCamera->Control(6, ezbInFmt, EZBYTEBUF_NULL, NULL);

    if (FAILED(ec)) {
        printf("Plese input the right value for continuous snap.\n");
    }
}

void StartPreview()
{
    BufferOf_<Byte, sizeof(RECT)>  ezbInRect;
    RECT *pRect = (RECT *)(char *)ezbInRect;
    pRect->left = CAMERA_WIN_POSX;
    pRect->top = CAMERA_WIN_POSY;
    pRect->right = CAMERA_WIN_POSX + CAMERA_WIN_WIDTH - 1;
    pRect->bottom = CAMERA_WIN_POSY + CAMERA_WIN_HEIGHT - 1;
    ezbInRect.SetUsed(sizeof(RECT));

    g_pCamera->Control(3, ezbInRect, EZBYTEBUF_NULL, NULL);
}

void StopPreview()
{
    g_pCamera->Control(4, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
}

void CapturePhotos()
{
    ECode ec;
    BYTE *pSnapFrame;
    int PhotoWidth, PhotoHeight;

    // Get actual photo width & height
    BufferOf_<Byte, sizeof(int)> ezbInID;
    BufferOf_<Byte, sizeof(Camera_Format)>  ezbOutFmt;

    *(int *)(char *)ezbInID = CAMERA_FORMAT_PHOTO_GETSIZE;
    ezbInID.SetUsed(sizeof(int));

    ec = g_pCamera->Control(7, ezbInID, ezbOutFmt, NULL);
    if (ec != NOERROR) {
        printf("Can't get the actual photo size.\n");
        return;
    }
    Camera_Format *pFormat = (Camera_Format *)(char *)ezbOutFmt;
    PhotoWidth = pFormat->wParam;
    PhotoHeight = pFormat->lParam;
    // Get photo data
    BufferOf_<Byte, sizeof(Camera_Format)>  ezbPhoto;
    ec = g_pCamera->Control(2, EZBYTEBUF_NULL, ezbPhoto, NULL);

    if (SUCCEEDED(ec)) {
        unsigned int i;
        Camera_Photo *pPhoto = (Camera_Photo *)(char *)ezbPhoto;
        pSnapFrame = (BYTE *)pPhoto->pBuffer;

        printf("pPhoto->Number=%d, PhotoWidth=%d, PhotoHeight=%d, pPhoto->pBuffer=%x\n",
        pPhoto->Number,PhotoWidth,PhotoHeight, pPhoto->pBuffer);

        for (i = 0; i < pPhoto->Number; i++) {
            saveYCbCrdata(pSnapFrame,
                PhotoWidth * PhotoHeight * 2);
            pSnapFrame += pPhoto->SingleBufferSize;
        }
        // Free memory
        g_pCamera->Control(5, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
    }
    else {
        printf("Can't capture still image, ec = 0x%x\n", ec);
    }
}

void EnterVideoMode()
{
    BufferOf_<Byte, sizeof(BOOL)>  ebbInBuf;
    BOOL *pVideo = (BOOL *)(char *)ebbInBuf;
    *pVideo = 1;
    ebbInBuf.SetUsed(sizeof(BOOL));

    g_pCamera->Control(8, ebbInBuf, EZBYTEBUF_NULL, NULL);
    StopPreview();
    StartPreview();
}

void EnterPhotoMode()
{
    BufferOf_<Byte, sizeof(BOOL)>  ebbInBuf;
    BOOL *pVideo = (BOOL *)(char *)ebbInBuf;
    *pVideo = 0;
    ebbInBuf.SetUsed(sizeof(BOOL));

    g_pCamera->Control(8, ebbInBuf, EZBYTEBUF_NULL, NULL);
    StopPreview();
    StartPreview();
}

#define RECORDING_FRAMES 100
//ECode __stdcall RecordThread(void *arg)
ECode RecordThread(void *arg)
{
    BufferOf_<Byte, sizeof(Camera_ImageFrame)>  ezbFrame;
    Camera_ImageFrame *pFrame = (Camera_ImageFrame *)(char *)ezbFrame;
    BYTE *pBufferPos;
    int totalBufferSize;
    ECode ec;

    // Get actual video width & height
    BufferOf_<Byte, sizeof(int)> ezbInID;
    BufferOf_<Byte, sizeof(Camera_Format)>  ezbOutFmt;

    *(int *)(char *)ezbInID = CAMERA_FORMAT_VIDEO_GETSIZE;
    ezbInID.SetUsed(sizeof(int));

    ec = g_pCamera->Control(7, ezbInID, ezbOutFmt, NULL);
    if (ec != NOERROR) {
        printf("Can't get the actual video frame size.\n");
        return ec;
    }
    Camera_Format *pFormat = (Camera_Format *)(char *)ezbOutFmt;
    g_recVideoWidth = pFormat->wParam;
    g_recVideoHeight = pFormat->lParam;
    printf("Recording start... Video Width: %d, Video Height: %d\n",
        g_recVideoWidth, g_recVideoHeight);

    totalBufferSize = g_recVideoWidth * g_recVideoHeight * 2 * RECORDING_FRAMES;
    g_pVideoBuffer = (BYTE *)realloc(g_pVideoBuffer, totalBufferSize);
    if (NULL == g_pVideoBuffer) {
        printf("Alloc video buffer error!\n");
        return E_OUT_OF_MEMORY;
    }
    pBufferPos = g_pVideoBuffer;
    g_bThreadRun =  TRUE;

    ec = g_pCamera->Control(9, EZBYTEBUF_NULL, EZBYTEBUF_NULL, &g_pRecordEvent);
    if (FAILED(ec)) {
        printf("Please enter record mode to record!\n");
        return ec;
    }

    g_bRecording = TRUE;

    while (g_bRecording) {
        WaitResult wr;
        g_pRecordEvent->Wait(&wr, NULL);
        g_pCamera->Control(11, EZBYTEBUF_NULL, ezbFrame, NULL);
        printf("Get a video frame:\n");
        printf("nID = %d\n", pFrame->nID);
        printf("FrameSize = %d\n", pFrame->FrameSize);
        printf("pBuffer = 0x%x\n", pFrame->pBuffer);
        printf("\n");

        if (pFrame->FrameSize > totalBufferSize) {
            printf("Frame error.\n");
            g_bThreadRun = FALSE;
            return E_OUT_OF_MEMORY;
        }

        if (pFrame->nID < RECORDING_FRAMES) {
            memcpy(pBufferPos, pFrame->pBuffer, pFrame->FrameSize);
            pBufferPos += pFrame->FrameSize;
        }
    }
    g_bThreadRun =  FALSE;

    g_pRecordEvent->Release();

    printf("Recording finish!\n");
    return 0;
}

void StartRecording()
{
    CThread::New(RecordThread, NULL, 0, NULL);
}

void StopRecording()
{
    g_bRecording = FALSE;
    while (g_bThreadRun) CThread::Sleep(10, NULL);
    g_pCamera->Control(10, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
}

void PlayVideo()
{
    OverlayFormat *pOverlayFmt;
    BufferOf_<Byte, sizeof(OverlayFormat)>     ezbInFbFmt;
    BufferOf_<Byte, sizeof(OverlayFormat)>     ezbOutFbFmt;
    void *pOverlayYBufAddr, *pOverlayCbBufAddr, *pOverlayCrBufAddr;
    UINT uOverlayYBufSize, uOverlayCbBufSize, uOverlayCrBufSize;
    BYTE *pBuffer;

    if (g_recVideoWidth >= g_nScreenWidth || (g_recVideoHeight >= g_nScreenHeight)) {
        printf("Sorry, this movie should be played by an advanced player...\n");
        return;
    }

    // First disable overlay2
    g_pDisplay->Control(10, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);

    // Then enable overlay2 using new format to play video

    pOverlayFmt = (OverlayFormat *)(wchar_t *)ezbInFbFmt;

    pOverlayFmt->Enable = TRUE;
    pOverlayFmt->Color = COLOR_YCbCr422; // MUST
    pOverlayFmt->Layer = 2; // Use overlay2
    pOverlayFmt->Bpp = 16; // YCrCb422
    pOverlayFmt->Width = g_recVideoWidth;
    pOverlayFmt->Height = g_recVideoHeight;

    pOverlayFmt->PosX = (g_nScreenWidth - g_recVideoWidth) / 2;
    pOverlayFmt->PosY = (g_nScreenHeight - g_recVideoHeight) / 2;

    ezbInFbFmt.SetUsed(sizeof(OverlayFormat));

    if (NOERROR != g_pDisplay->Control(8, ezbInFbFmt, ezbOutFbFmt, NULL)) {
        printf("Set overlay2 error!\n");
        goto Resume_Overlay2;
    }

    // Get the whole information about overlay2
    pOverlayFmt = (OverlayFormat *)(wchar_t *)ezbOutFbFmt;

    pOverlayYBufAddr = pOverlayFmt->pChannelFb[0];
    pOverlayCbBufAddr = pOverlayFmt->pChannelFb[1];
    pOverlayCrBufAddr = pOverlayFmt->pChannelFb[2];

    uOverlayYBufSize = pOverlayFmt->ChannelSize[0];
    uOverlayCbBufSize = pOverlayFmt->ChannelSize[1];
    uOverlayCrBufSize = pOverlayFmt->ChannelSize[2];

    printf("Playing start...\n");

    pBuffer = g_pVideoBuffer;
    // Using a simple way
    int i;
    for (i = 0; i  < RECORDING_FRAMES; i++) {
        memcpy(pOverlayYBufAddr, pBuffer, uOverlayYBufSize);
        pBuffer += uOverlayYBufSize;
        memcpy(pOverlayCbBufAddr, pBuffer, uOverlayCbBufSize);
        pBuffer += uOverlayCbBufSize;
        memcpy(pOverlayCrBufAddr, pBuffer, uOverlayCrBufSize);
        pBuffer += uOverlayCrBufSize;
        CThread::Sleep(66, NULL);
    }

    printf("Playing finish!\n");

Resume_Overlay2:
    g_pDisplay->Control(10, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
    ConfigureOverlay2();
}

void QuitCamera()
{
    // Stop preview
    g_pCamera->Control(4, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
    ClearOverlay2();
    // disable overlay2
    g_pDisplay->Control(10, EZBYTEBUF_NULL, EZBYTEBUF_NULL, NULL);
    free(g_pVideoBuffer);
}

int main(int argc, char *argv[])
{
    unsigned long option;

    if (!ConfigureDisplay()) return 1;

    if (!ConfigureCamera()) return 1;

    while (1) {
		printf("*******CAMERA TESTING*******\n");
	    printf("1. Start camera preview\n");
	    printf("2. Capture photos\n");
	    printf("3. Adjust brightness\n");
	    printf("4. Adjust contrast\n");
        printf("5. Adjust color mode\n");
        printf("6. Adjust scence mode\n");
        printf("7. Adjust photo resolution\n");
        printf("8. Adjust digital zoom\n");
        printf("9. Adjust continuous snap\n");
        printf("10. Adjust sharpness\n");
        printf("11. Adjust white balance\n");
        printf("12. Enter video mode\n");
        printf("13. Enter photo mode\n");
        printf("14. Adjust video resolution\n");
        printf("15. Start video recording\n");
        printf("16. Stop video recording\n");
        printf("17. Play recording video\n");
        printf("99. Stop camera preview\n");
    	printf("0. Exit\n");
	    printf("Your Choice:");

	    scanf("%d", &option);
		switch (option) {
		    case 1:
                //start camera preview
                StartPreview();
		    	break;

		    case 2:
                //capture still image on g_overlay2
                CapturePhotos();
		    	break;

		    case 3:
		        // Adjust brightness
		        AdjustBrightness();
		        break;

		    case 4:
		        // Adjust contrast
		        AdjustContrast();
		        break;

		    case 5:
		        // Adjust color mode
		        AdjustCamera_ColorMode();
		        break;
		    case 6:
		        // Adjust scence mode
		        AdjustCamera_SceneMode();
		        break;

		    case 7:
		        // Adjust photo quality
		        AdjustCamera_PhotoResolution();
		        break;

		    case 8:
		        // Adjust digital zoom
		        AdjustDigitalZoom();
	        break;

		    case 9:
		        // Adjust continuous snap
		        AdjustContinuousSnap();
		        break;

		    case 10:
		        // Adjust continuous snap
		        AdjustSharpness();
		        break;

		    case 11:
		        // Adjust white balance
		        AdjustWhiteBalance();
		        break;

            case 12:
		        // Enter video mode
		        EnterVideoMode();
		        break;

	        case 13:
		        // Enter photo mode
		        EnterPhotoMode();
		        break;

		    case 14:
		        // Adjust video resolution
		        AdjustCamera_VideoResolution();
		        break;

		    case 15:
		        // Start video recording
		        StartRecording();
		        break;

            case 16:
		        // Stop video recording
		        StopRecording();
		        break;

            case 17:
		        // Play recording video
		        PlayVideo();
		        break;

		    case 99:
                // Stop camera preview
                StopPreview();
		    	break;

            case 0:
                // Quit camera
                QuitCamera();
                goto _exit;

		    default:
		    	break;
        }
        getchar(); // Avoid bugs for scanf
	}

_exit:
    ReleaseDisplay();
    ReleaseCamera();
    return 0;
}
