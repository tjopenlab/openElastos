//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#ifndef MYBUFFDRIVER_H
#define MYBUFFDRIVER_H

class MyBuffDriver : public Driver {

public:
    MyBuffDriver();

    ~MyBuffDriver();

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

    CARAPI Init();

private:
    UINT m_uiSize;
    BYTE  *m_pBuffer;

    DzReaderWriterLock* m_pLock;
};

extern MyBuffDriver g_myBuff1;

EXTERN IDriver * CDECL CreateMyBuff1();

#endif
