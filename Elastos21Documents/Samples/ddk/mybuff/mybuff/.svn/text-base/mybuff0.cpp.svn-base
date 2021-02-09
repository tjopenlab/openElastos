//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include "mybuff0.h"

MyBuffDriver0 g_myBuff0;

ULONG MyBuffDriver0::AddRef()
{
    return 2;
}

ULONG MyBuffDriver0::Release()
{
    return 1;
}

MyBuffDriver0::MyBuffDriver0()
{
    m_iLock = NULL;
}

MyBuffDriver0::~MyBuffDriver0()
{
    if (m_iLock)
        delete m_iLock;
}

ECode MyBuffDriver0::Read(
        /* [in] */ UINT64 u64Offset,
        /* [in] */ UINT uNumberOfBytesToRead,
        /* [out] */ BufferOf<Byte> ebbData,
        /* [out] */ IEvent * * ppCompletionEvent)
{
    if (ppCompletionEvent)
        *ppCompletionEvent = 0;

    if (u64Offset > BUF_SIZE) {
        return E_FAIL;
    }

    if (u64Offset + uNumberOfBytesToRead > BUF_SIZE)
        uNumberOfBytesToRead = BUF_SIZE - u64Offset;

    if (ebbData.Capacity() - ebbData.Used() < (int)uNumberOfBytesToRead)
        return E_FAIL;

   	WaitResult wr;
    m_iLock->ReaderLock(&wr);
    if (WaitResult_OK != wr) {
        return E_FAIL;
    }

    ebbData.Copy(m__byBuffer + u64Offset, uNumberOfBytesToRead);

    m_iLock->ReaderUnlock();
    return NOERROR;
}

ECode MyBuffDriver0::Write(
    /* [in] */ UINT64 u64Offset,
    /* [in] */ BufferOf<Byte> ebbData,
    /* [out] */ UINT * puNumberOfBytesWritten,
    /* [out] */ IEvent * * ppCompletionEvent)
{
    UINT i;
    UINT uNumberOfBytesToWrite;
    BYTE* pData;
    WaitResult wr;

    if (puNumberOfBytesWritten)
        *puNumberOfBytesWritten = 0;

    if (ppCompletionEvent)
        *ppCompletionEvent = 0;

    if (u64Offset > BUF_SIZE) {
        return E_FAIL;
    }

    uNumberOfBytesToWrite = ebbData.Used();
    if (u64Offset + uNumberOfBytesToWrite > BUF_SIZE)
        uNumberOfBytesToWrite = BUF_SIZE - u64Offset;

    m_iLock->WriterLock(&wr);
    if (WaitResult_OK != wr)
        return E_FAIL;

    pData = (BYTE*)(char*)ebbData;
    for (i = 0; i < uNumberOfBytesToWrite; ++i) {
        m__byBuffer[i + u64Offset] = pData[i];
    }
    m_iLock->WriterUnlock();

    if (puNumberOfBytesWritten)
        *puNumberOfBytesWritten = uNumberOfBytesToWrite;

    return NOERROR;
}

ECode MyBuffDriver0::Control(
    /* [in] */ INT nControlCode,
    /* [in] */ BufferOf<Byte> ebbInData,
    /* [out] */ BufferOf<Byte> ebbOutData,
    /* [out] */ IEvent * * ppCompletionEvent)
{
    return NOERROR;
}

void MyBuffDriver0::Dispose()
{
}

ECode MyBuffDriver0::Init()
{
    if (NULL == m_iLock)
    {
        m_iLock = new DzReaderWriterLock();
        if (NULL == m_iLock) {
            kprintf("ERROR:There have no enough memory, %s, %d\n",
                __FILE__, __LINE__);
            return E_OUT_OF_MEMORY;
        }
    }

    return NOERROR;
}
