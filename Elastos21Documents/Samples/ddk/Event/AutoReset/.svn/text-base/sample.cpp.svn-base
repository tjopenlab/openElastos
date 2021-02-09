//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==========================================================================
// Description  : 这个程序演示了自动清除风格的Event对象
//                程序中主线程等待Event对象，收到通知后，Event对
//                象自动清除，主线程再次等待；通知线程两次以不同
//                的通知码通知事件以示区别。
//                使用Event的Wait, Notify和Event方法
//==========================================================================
#include <ddk.h>

ECode DoCreateEvent(DzEvent **ppEvent)
{
    if (NULL == ppEvent) {
        return E_INVALID_ARGUMENT;
    }

    //Create a Event object, cleared automatically, initial not signaled.
    *ppEvent = new DzEvent(FALSE, UNSIGNALED);
    if (NULL == *ppEvent) {
        kprintf("Create event failed\n");

        return E_FAIL;
    }

    return NOERROR;
}

//==============================================================
// Description  : The thread function of the notifyer.
//                The thread notifies with 1 first, and then
//                with 2.
//==============================================================
ECode NotifyerFunc(void* arg)
{
    DzEvent* pEvent = reinterpret_cast<DzEvent*>(arg);

    DzSleep(2000, NULL);//let main thread wait
    // Notify with 1.
    kprintf("Notifies, state is %d.\n", 1);
    pEvent->Notify(1);

    DzSleep(2000, NULL);

    // Notify with 2.
    kprintf("Notifies again, state is %d.\n", 2);
    pEvent->Notify(2);

    return NOERROR;
}


//==============================================================
// Description  : The main function, also the main thread.
//                Waits for event twice. The event is cleared
//                automically. So the notifyer thread notifies
//                twice. The main thread receives the notifications,
//                and prints the notification state.
//==============================================================
ECode DoWaitEvent(DzEvent *pEvent)
{
    uint_t uiState;        
    WaitResult wr;

    if (NULL == pEvent) {
        return E_INVALID_ARGUMENT;
    }

    // Wait for notification the first time.
    kprintf("Wait for notification...\n");
    pEvent->Wait(&wr, &uiState);

    kprintf("Receive the notification, state is %d, "
           "the event has been cleared automatically.\n", uiState);

    // Wait for notification the second time.
    kprintf("Wait for notification again...\n");
    pEvent->Wait(&wr, &uiState);

    kprintf("Receive the notification again, state is %d.\n", uiState);

    return NOERROR;
}

ECode DoMain()
{
    ECode ec;
    DzEvent *pEvent = NULL;
    IThread *pThread = NULL; 
    

    ec = DoCreateEvent(&pEvent);
    if (FAILED(ec)) {
        kprintf("Create Event failed. ec = 0x%08x\n", ec);
        return ec;
    }

    ec = DzCreateKernelThread(NotifyerFunc, (void *)pEvent, 0, PriorityRank_Normal, &pThread);
    if (FAILED(ec)) {
        kprintf("Create kernel thread failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    ec = DoWaitEvent(pEvent);
    if (FAILED(ec)) {
        kprintf("Wait event failed. ec = 0x%08x\n", ec);

        goto Exit;
    }

    ec = pThread->Join(INFINITE, NULL);
    if (FAILED(ec)) {
        kprintf("Join failed. ec = 0x%08x\n", ec);
    }

Exit:
    if (pEvent) {
        delete pEvent;
    }

    if (pThread) {
        pThread->Release();
    }

    return ec;
}

