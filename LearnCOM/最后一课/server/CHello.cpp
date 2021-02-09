//==========================================================================
// 北京科泰世纪科技有限公司 版权所有 2000年--2003年
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

