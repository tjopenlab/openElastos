//==========================================================================
// Copyright (c) 2000-2005,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#ifndef __DISPLAY_H__
#define __DISPLAY_H__

typedef struct {
    BYTE Enable;                    // 1: enable overlay2  0: disable overlay2
    BYTE Bpp;
    WORD Width;
    WORD Height;
    WORD PosX;
    WORD PosY;
    WORD Layer; // Reserved Now
    DWORD ChanY_FrameBuffer;        //Channel Y FrameBuffer Virtual Address
    unsigned int ChanYFB_SIZE;
    DWORD ChanCb_FrameBuffer;       //Channel Cb FrameBuffer Virtual Address
    unsigned int ChanCbFB_SIZE;
    DWORD ChanCr_FrameBuffer;       //Channel Cr FrameBuffer Virtual Address
    unsigned int ChanCrFB_SIZE;
} OverlayFormat;

#endif//__DISPLAY_H__
