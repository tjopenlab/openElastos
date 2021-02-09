//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
//
// Description : This sample demonstrates how to use the Event::NotifyByIsr.
//
//==========================================================================

#include <ddk.h>

//
// a driver for test
//
class Test : public Driver {
public:
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

public:
    void Isr();
    ECode Initialize();

public:
    DzEvent       m_Event;
    // Other data
    //...
};

STATIC void CDECL TestIsr(
        irq_t irq, void *pvDevice, InterruptContext *pContext)
{
    assert(pvDevice);
    ((Test *)pvDevice)->Isr();
}


ECode Initialize()
{
    // Do something
    //...

    // Registers corresponding interrupt service routine for
    // specified hardware interrupt
    RegisterIsr(IRQ, IPL, &TestIsr, this);


    return NOERROR;
}


ECode Test::Isr()
{
    // Do something
    //...

    // Sets Event object as a concrete notified state
    // (used in the interrupted service routine)
    pEvent->NotifyByIsr(1);

    return NOERROR;
}

// Other functions
//....

