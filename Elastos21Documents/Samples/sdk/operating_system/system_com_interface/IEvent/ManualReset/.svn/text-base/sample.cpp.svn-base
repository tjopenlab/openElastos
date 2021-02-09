//==========================================================================
// Copyright (c) 2000-2004,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

//==============================================================
// Description  : 这个程序演示了手动清除风格的Event对象
//                程序中主线程两次等待Event对象，收到通知后，Event
//                对象手清除通知，主线程再次等待；通知线程两次以不
//                同的通知码通知事以示区别。
//==============================================================


#include <stdio.h>
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
// Description  : The flag is true if the notification is cleared.
//==============================================================
bool g_bCleared = false;


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

    // Waits for the notification cleared.
    while (!g_bCleared)
        ;

    // Notifies with 2.
    CThread::Sleep(1000, NULL);
    printf("Notifies again, state is %d.\n", 2);
    iEvent->Notify(2);

    return NOERROR;
}

//==============================================================
// Description  : The main function, also the main thread.
//                Waits for the notification twice, and then clears
//                the notifications manually. Waits for the
//                notification the third time.The main thread
//                receives the notifications, and prints the
//                notification state.
//==============================================================
int main()
{
    ECode ec;
    IEvent*  iEvent;
    IThread* iNotifyer;
    EventState eventState;
    WaitResult wr;

    // Creates event, cleared manually, initial not signaled.
    ec = CEvent::New(TRUE, 0, &iEvent);
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
    ec = iEvent->Wait(&wr, &eventState);
    if (FAILED(ec)) {
        HandleError("Wait failed", ec);
    }
    else {
        printf("Receives the notification, state is %d, "
               "the event is manual, keeps signaled.\n", eventState);
    }

    // Waits for notification the second time.
    printf("Waits for notification again...\n");
    ec = iEvent->Wait(&wr, &eventState);
    if (FAILED(ec)) {
        HandleError("Wait failed", ec);
    }
    else {
        printf("Receives the notification again, state is %d.\n", eventState);
    }

    // Clears the notification.
    ec = iEvent->Clear();
    if (FAILED(ec)) {
        HandleError("Clear failed", ec);
    }
    else {
        printf("Clear event\n");
    }
    g_bCleared = true;

    // Waits for notification the third time.
    printf("Waits for notification the third time...\n");
    ec = iEvent->Wait(&wr, &eventState);
    if (FAILED(ec)) {
        HandleError("Wait failed", ec);
    }
    else {
        printf("Receives the notification the third time, state is %d.\n", eventState);
    }

    // Joins the child thread.
    iNotifyer->Join(INFINITE, NULL);

    // Releases the objects.
    iEvent->Release();
    iNotifyer->Release();

    return 0;
}

/*output:

    Waits for notification...
    Notifies, state is 1.
    Receives the notification, state is 1, the event is manual, keeps signaled.
    Waits for notification again...
    Receives the notification again, state is 1.
    Clear event
    Waits for notification the third time...
    Notifies again, state is 2.
    Receives the notification the third time, state is 2.
*/
