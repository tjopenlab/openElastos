//==========================================================================
// ������̩���ͿƼ����޹�˾ ��Ȩ���� 2000��--2003��
// Copyright (c) 2000-2003,  KoreTide Corp.  All Rights Reserved.
//==========================================================================

#include "CHello.h"
#include "_CHello.cpp"

DECLARE_CLASSFACTORY(CHello)

HRESULT CHello::Hello(
        /* [in] */ EzStr inStr,
        /* [out] */ EzStrBuf outStrBuf)
{
    outStrBuf.Copy(inStr);
    outStrBuf.Append(L" world!");
    return NOERROR;
}

