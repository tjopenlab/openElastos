//==========================================================================
// ������̩���ͿƼ����޹�˾ ��Ȩ���� 2000��--2003��
// Copyright (c) 2000-2003,  KoreTide Corp.  All Rights Reserved.
//==========================================================================

#include <stdio.h>
#import <hello.dll>

int __cdecl main()
{
    CHelloRef cHello;
    HRESULT hr = cHello.Instantiate();
    //HRESULT hr = cHello.Instantiate(CTX_DIFF_DOMAIN);
    if (FAILED(hr)) {
        assert(0 && "Can't create cHello");
        return 1;
    }

    EzStrBuf_<64> outStrBuf;
    hr = cHello.Hello(EZCSTR("Hello,"), outStrBuf);
    if (FAILED(hr)) {
        assert(0 && "Call Hello() failed");
        return 1;
    }

    printf("%S\n", (wchar_t*)outStrBuf);
    return 0;
}
