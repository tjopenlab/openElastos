//==========================================================================
// ������̩���ͿƼ����޹�˾ ��Ȩ���� 2000��--2003��
// Copyright (c) 2000-2003,  KoreTide Corp.  All Rights Reserved.
//==========================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(_CHELLO_H_)
#define _CHELLO_H_

#include "_CHello.h"

class CHello : public _CHello
{
public:
    STDMETHODIMP Hello(
        /* [in] */ EzStr inStr,
        /* [out] */ EzStrBuf outStrBuf);
};

#endif //!(_CHELLO_H_)
