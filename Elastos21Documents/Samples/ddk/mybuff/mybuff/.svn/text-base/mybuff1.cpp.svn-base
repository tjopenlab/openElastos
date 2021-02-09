//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#include <ddk.h>
#include "mybuff1.h"

MyBuffDriver g_myBuff1;

MyBuffDriver::MyBuffDriver():m_uiSize(2048u)
{
    m_pLock = NULL;
    m_pBuffer = NULL;
}

MyBuffDriver::~MyBuffDriver()
{
    if (m_pLock) {
        delete m_pLock;
        m_pLock = NULL;
    }

    if (m_pBuffer) {
        free(m_pBuffer);
        m_pBuffer = NULL;
    }
}

ECode MyBuffDriver::Init()
{
    if (m_pLock) {
        delete m_pLock;
        m_pLock = NULL;
    }
    m_pLock = new DzReaderWriterLock();
    if (NULL == m_pLock) {
        kprintf("ERROR:There have no enough memory, %s, %d\n",
                         __FILE__, __LINE__);

        return E_FAIL;
    }

    if (m_pBuffer) {
        free(m_pBuffer);
        m_pBuffer = NULL;
    }
    m_pBuffer = (BYTE *) malloc(m_uiSize * sizeof(BYTE));
    if (NULL == m_pBuffer) {
        kprintf("ERROR:There have no enough memory, %s, %d\n",
                        __FILE__, __LINE__);

        return E_FAIL;
    }

    return NOERROR;
}

ECode MyBuffDriver::Read(
        /* [in] */ UINT64 u64Offset,
        /* [in] */ UINT uNumberOfBytesToRead,
        /* [out] */ BufferOf<Byte> ebbData,
        /* [out] */ IEvent * * ppCompletionEvent)
{
    if (ppCompletionEvent) {
        *ppCompletionEvent = 0;
    }

    if (u64Offset > m_uiSize) {
        return E_FAIL;
    }

    if (u64Offset + uNumberOfBytesToRead > m_uiSize) {
        uNumberOfBytesToRead = m_uiSize - u64Offset;
    }

    if (ebbData.Capacity() - ebbData.Used() < (int)uNumberOfBytesToRead) {
        return E_FAIL;
    }

    WaitResult wr;
    m_pLock->ReaderLock(&wr);

    ebbData.Copy(m_pBuffer + u64Offset, uNumberOfBytesToRead);

    m_pLock->ReaderUnlock();
    return NOERROR;
}

ECode MyBuffDriver::Write(
    /* [in] */ UINT64 u64Offset,
    /* [in] */ BufferOf<Byte> ebbData,
    /* [out] */ UINT * puNumberOfBytesWritten,
    /* [out] */ IEvent * * ppCompletionEvent)
{
    UINT i;
    UINT uNumberOfBytesToWrite;
    BYTE* pData;
    WaitResult wr;

    if (puNumberOfBytesWritten) {
        *puNumberOfBytesWritten = 0;
    }

    if (ppCompletionEvent) {
        *ppCompletionEvent = 0;
    }

    if (u64Offset > m_uiSize) {
        return E_FAIL;
    }

    uNumberOfBytesToWrite = ebbData.Used();
    if (u64Offset + uNumberOfBytesToWrite > m_uiSize) {
        uNumberOfBytesToWrite = m_uiSize - u64Offset;
    }

    m_pLock->WriterLock(&wr);

    pData = (BYTE*)(char*)ebbData;
    for (i = 0; i < uNumberOfBytesToWrite; ++i) {
        m_pBuffer[i + u64Offset] = pData[i];
    }
    m_pLock->WriterUnlock();

    if (puNumberOfBytesWritten) {
        *puNumberOfBytesWritten = uNumberOfBytesToWrite;
    }

    return NOERROR;
}

ECode MyBuffDriver::Control(
    /* [in] */ INT nControlCode,
    /* [in] */ BufferOf<Byte> ebbInData,
    /* [out] */ BufferOf<Byte> ebbOutData,
    /* [out] */ IEvent * * ppCompletionEvent)
{
    if (ppCompletionEvent) {
        ppCompletionEvent = NULL;
    }

    WaitResult wr;
    switch(nControlCode) {
        case 0: {//get the buff size
            if (ebbOutData.Capacity()-ebbOutData.Used() < (int)sizeof(UINT)) {
                return E_INVALID_ARGUMENT;
            }

            m_pLock->ReaderLock(&wr);

            ebbOutData.Copy(&m_uiSize, sizeof(UINT));

            m_pLock->ReaderUnlock();
            break;
        }

        case 1: {//set the buff size
            if (ebbInData.Used() != sizeof(UINT)) {
                return E_INVALID_ARGUMENT;
            }

            m_pLock->WriterLock(&wr);

            int size = *(int *)(char *)ebbInData;
            if (size < 0) {
                return E_INVALID_ARGUMENT;
            }

            if (m_pBuffer) {
                free(m_pBuffer);
                m_uiSize = size;
                m_pBuffer = (BYTE *)malloc(m_uiSize * sizeof(BYTE));
                if (NULL == m_pBuffer) {
                    kprintf("ERROR:There have no enough memory, %s, %d\n",
                                  __FILE__, __LINE__);

                    return E_FAIL;
                }
            }

            m_pLock->WriterUnlock();

            if (ebbOutData.Capacity()-ebbOutData.Used() >= (int)sizeof(UINT))
                ebbOutData.Copy(&m_uiSize, sizeof(UINT));

            break;
        }

        default: {
            return E_NOT_IMPLEMENTED;
        }
    }

   return NOERROR;
}

void MyBuffDriver::Dispose()
{
}

EXTERN IDriver * CDECL CreateMyBuff1()
{
    ECode ec = g_myBuff1.Init();
    if (FAILED(ec)) {
        return NULL;
    }

    return &g_myBuff1;
}
