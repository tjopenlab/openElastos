//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==============================================================
// Description  : 这个程序演示了自动清除风格的Event对象
//                程序中主线程等待Event对象，收到通知后，Event对
//                象自动清除，主线程再次等待；通知线程两次以不同
//                的通知码通知事件以示区别。
//==============================================================


#include <stdio.h>
#include <eladef.h>
#include <elastos.h>
using namespace Elastos;

//==============================================================
// Description  : Error Handler
//==============================================================
void HandleError(const char* msg, ECode ec)
{
    printf("%s (ec = 0x%08x)\n", msg, ec);
}


//==============================================================
// Description  : The thread function of the notifyer.
//                The thread notifies with 1 first, and then
//                with 2.
//==============================================================
ECode NotifyerFunc(void* arg)
{
    IEvent* iEvent = (IEvent*)(arg);

    // Notifies with 1.
    printf("Notifies, state is %d.\n", 1);
    iEvent->Notify(1);

    CThread::Sleep(2000, NULL);

    // Notifies with 2.
    printf("Notifies again, state is %d.\n", 2);
    iEvent->Notify(2);

    return NOERROR;
}


//==============================================================
// Description  : The main function, also the main thread.
//                Waits for event twice. The event is cleared
//                automically. So the notifyer thread notifies
//                twice. The main thread receives the notifications,
//                and prints the notification state.
//==============================================================
int main()
{
    ECode ec;
    IEvent* iEvent;
    IThread* iNotifyer;
    EventState eventState;
    WaitResult wr;

    // Creates event, cleared automatically, initial not signaled.
    ec = CEvent::New(FALSE, UNSIGNALED, &iEvent);
    if (FAILED(ec)) {
        HandleError("Create event failed", ec);
        return 1;
    }

    // Creates a notifyer thread.
    ec = CThread::New(NotifyerFunc, iEvent, 0, &iNotifyer);
    if (FAILED(ec)) {
        HandleError("Create notifyer thread failed", ec);
        iEvent->Release();
        return 1;
    }

    // Waits for notification the first time.
    printf("Waits for notification...\n");
    iEvent->Wait(&wr, &eventState);
    printf("Receives the notification, state is %d, "
           "the event has been cleared automatically.\n", eventState);

    // Waits for notification the second time.
    printf("Waits for notification again...\n");
    iEvent->Wait(&wr, &eventState);
    printf("Receives the notification again, state is %d.\n", eventState);

    // Joins the child thread.
    iNotifyer->Join(INFINITE, NULL);

    // Releases objects.
    iEvent->Release();
    iNotifyer->Release();

    return 0;
}

//==========================================================================
//  OutPut:
//
//     Waits for notification again...
//     Notifies, state is 1.
//     Receives the notification, state is 1, the event has been cleared automatically.
//
//     Waits for notification again...
//     Notifies again, state is 2.
//     Receives the notification again, state is 2.
//==========================================================================
