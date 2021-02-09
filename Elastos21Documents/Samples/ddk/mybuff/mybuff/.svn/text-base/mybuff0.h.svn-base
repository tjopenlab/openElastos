//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#ifndef _MY_BUFF0_H
#define _MY_BUFF0_H

#include <ddk.h>

class MyBuffDriver0 : public Driver {

public:
    MyBuffDriver0();

    ~MyBuffDriver0();

    ULONG AddRef();

    ULONG Release();

    CARAPI Read(
        /* [in] */ UINT64 u64Offset,
        /* [in] */ UINT uNumberOfBytesToRead,
        /* [out] */ BufferOf<Byte> ebbData,
        /* [out] */ IEvent * * ppCompletionEvent);

    CARAPI Write(
        /* [in] */ UINT64 u64Offset,
        /* [in] */ BufferOf<Byte> ebbData,
        /* [out] */ UINT * puNumberOfBytesWritten,
        /* [out] */ IEvent * * ppCompletionEvent);

    CARAPI Control(
        /* [in] */ INT nControlCode,
        /* [in] */ BufferOf<Byte> ebbInData,
        /* [out] */ BufferOf<Byte> ebbOutData,
        /* [out] */ IEvent * * ppCompletionEvent);

    virtual void Dispose();

    ECode Init();

private:
    enum { BUF_SIZE = 4096 };
    BYTE  m__byBuffer[BUF_SIZE];

    DzReaderWriterLock* m_iLock;
};

extern MyBuffDriver0 g_myBuff0;

#endif // _MY_BUFF0_H
