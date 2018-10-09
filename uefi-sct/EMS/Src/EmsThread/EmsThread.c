/** @file
 
  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
    EmsThread.c
    
Abstract:

  Implementation of EMS Thread functions

--*/

#include "EmsThread.h"
#include "EmsTclCleanup.h"

#define THREADHASHTABLESIZE 0x8
#define HASH(IDX)           (((UINT32) (IDX)) % THREADHASHTABLESIZE)

STATIC EmsThread  *EmsMainThread  = NULL;
UINT32            EmsThreadNum    = 0;

STATIC EmsThread  *EmsThreadHashTable[THREADHASHTABLESIZE];
STATIC HANDLE     ThreadHashTableMutex;

STATIC HANDLE     ThreadCreateEvent;
STATIC HANDLE     EmsThreadLock;

EmsEventMng       EmsThreadEventMng;

VOID
EmsPutOneEvent (
  EmsEvent           *Event,
  EmsEventMng        *EventMng
  )
/*++

Routine Description:

  Put one EMS event to the event list

Arguments:

  Event     - The event node
  EventMng  - The data structure of event lists

Returns:

  None

--*/
{
#ifdef EMSEVENTDEBUG
  EventMng->EmsEventNum++;
#endif

  if (EventMng->EmsEventListHead == NULL) {
    EventMng->EmsEventListHead = EventMng->EmsEventListTail = Event;
    Event->Next = NULL;
    return ;
  }

  EventMng->EmsEventListTail->Next  = Event;
  EventMng->EmsEventListTail        = Event;
  Event->Next                       = NULL;

}

VOID
EmsGetOneEvent (
  EmsEvent    **Event,
  EmsEventMng *EventMng
  )
/*++

Routine Description:

  Get one Event node from event list

Arguments:

  Event     - The new event node
  EventMng  - The data structure of event lists

Returns:

  None

--*/
{
  *Event = EventMng->EmsEventListHead;
  if (EventMng->EmsEventListHead == EventMng->EmsEventListTail) {
    EventMng->EmsEventListHead  = NULL;
    EventMng->EmsEventListTail  = NULL;
  } else {
    EventMng->EmsEventListHead = EventMng->EmsEventListHead->Next;
  }
  (*Event)->Next = NULL;
#ifdef EMSEVENTDEBUG
  EventMng->EmsEventNum--;
#endif
}

#ifdef EMSEVENTDEBUG
VOID
PrintEmsEventNum (
  EmsEventMng *EventMng
  )
/*++

Routine Description:

  Print the number of node in the EMS event list

Arguments:

  EventMng  - The data structure of event lists

Returns:

  None

--*/
{
  printf ("======EMS DEBUG======\n");
  EmsEventQueueLock (EventMng);
  printf ("%s : Event list num: %d\n", EventMng->EmsEventMngName, EventMng->EmsEventNum);
  EmsEventQueueUnlock (EventMng);
  printf ("=====================\n\n");
}

VOID
PrintEmsEventList (
  EmsEventMng *EventMng
  )
/*++

Routine Description:

  Print the EMS event list

Arguments:

  EventMng  - The data structure of event lists

Returns:

  None

--*/
{
  EmsEvent  *Node;
  Node = NULL;
  printf ("======EMS DEBUG======\n");
  printf ("%s : Event list:\n", EventMng->EmsEventMngName);
  EmsEventQueueLock (EventMng);
  for (Node = EventMng->EmsEventListHead; Node != NULL; Node = Node->Next) {
    printf ("==>%s", Node->ScriptString);
  }

  EmsEventQueueUnlock (EventMng);
  printf ("\n=====================\n\n");
}

VOID
PrintEmsFreeEventList (
  EmsEventMng *EventMng
  )
/*++

Routine Description:

  Print the EMS event free list

Arguments:

  EventMng  - The data structure of event lists

Returns:

  None

--*/
{
  EmsEvent  *Node;
  Node = NULL;

  printf ("======EMS DEBUG======\n");
  printf ("%s : Event list:\n", EventMng->EmsEventMngName);
  WaitForSingleObject (EventMng->EmsEventFreeListMutex, INFINITE);
  for (Node = EventMng->EmsEventFreeList; Node != NULL; Node = Node->Next) {
    printf ("==>%s", Node->ScriptString);
  }

  ReleaseMutex (EventMng->EmsEventFreeListMutex);
  printf ("=====================\n\n");
}

VOID
PrintEmsFreeEventNum (
  EmsEventMng *EventMng
  )
/*++

Routine Description:

  Print the number of node in the EMS free event list

Arguments:

  EventMng  - The data structure of event lists

Returns:

  None

--*/
{
  printf ("======EMS DEBUG======\n");
  WaitForSingleObject (EventMng->EmsEventFreeListMutex, INFINITE);
  printf ("%s : Event free list num: %d\n", EventMng->EmsEventMngName, EventMng->EmsFreeEventNum);
  ReleaseMutex (EventMng->EmsEventFreeListMutex);
  printf ("=====================\n\n");
}
#endif

STATIC
EmsEvent *
EmsEventFreeListPop (
  EmsEventMng *EventMng
  )
/*++

Routine Description:

  Pop one event node from the EMS event free list

Arguments:

  EventMng  - The data structure of event lists

Returns:

  The popped event node

--*/
{
  EmsEvent  *Event;
  Event = EventMng->EmsEventFreeList;

  if (EventMng->EmsEventFreeList) {
    EventMng->EmsEventFreeList = EventMng->EmsEventFreeList->Next;
    EventMng->EmsFreeEventNum--;
  }

  return Event;
}

STATIC
VOID
EmsEventFreeListPush (
  EmsEvent    *Event,
  EmsEventMng *EventMng
  )
/*++

Routine Description:

  Push one event node to the EMS event free list

Arguments:

  Event     - The event node to be pushed
  EventMng  - The data structure of event lists

Returns:

  None

--*/
{
  Event->Next                 = EventMng->EmsEventFreeList;
  EventMng->EmsEventFreeList  = Event;
  EventMng->EmsFreeEventNum++;
}

EFI_STATUS
EmsAllocEventObj (
  EmsEvent    **Event,
  EmsEventMng *EventMng
  )
/*++

Routine Description:

  Alloc an EMS event object

Arguments:

  Event     - The pointer's pointer for return an new event object
  EventMng  - The data structure of event lists

Returns:

  EFI_SUCCESS or EFI_INVALID_PARAMETER

--*/
{
  WaitForSingleObject (EventMng->EmsEventFreeListMutex, INFINITE);
  if (EventMng->EmsEventFreeList) {
    *Event = EmsEventFreeListPop (EventMng);
    ReleaseMutex (EventMng->EmsEventFreeListMutex);
  } else {
    ReleaseMutex (EventMng->EmsEventFreeListMutex);
    *Event = (EmsEvent *) malloc (sizeof (EmsEvent));
  }

  if(*Event != NULL) {
    memset (*Event, 0x0, sizeof (EmsEvent));
	return EFI_SUCCESS;
  }
  return EFI_OUT_OF_RESOURCES;
}

VOID
EmsFreeEventObj (
  EmsEvent    *Event,
  EmsEventMng *EventMng
  )
/*++

Routine Description:

  Free an evnet object

Arguments:

  Event     - The event object to be free
  EventMng  - The data structure of event lists

Returns:

  None

--*/
{
#ifdef EMSEVENTDEBUG
  if (Event->ScriptString) {
    free (Event->ScriptString);
  }
#endif
  WaitForSingleObject (EventMng->EmsEventFreeListMutex, INFINITE);
  EmsEventFreeListPush (Event, EventMng);
  ReleaseMutex (EventMng->EmsEventFreeListMutex);
}

VOID
EmsEventQueueInit (
  EmsEventMng *EventMng
  )
/*++

Routine Description:

  The routine for EMS event queue initialization

Arguments:

  EventMng  - The data structure of event lists

Returns:

  None

--*/
{
  EventMng->EmsEventListHead      = NULL;
  EventMng->EmsEventListTail      = NULL;
  EventMng->EmsEventFreeList      = NULL;
  EventMng->EmsEventListMutex     = CreateMutex (NULL, FALSE, NULL);
  EventMng->EmsEventFreeListMutex = CreateMutex (NULL, FALSE, NULL);
  EventMng->EmsFreeEventNum = 0;
#ifdef EMSEVENTDEBUG
  EventMng->EmsEventMngName = "EmsThreadEventMng";
  EventMng->EmsEventNum     = 0;
#endif
}

STATIC
VOID
EmsEventQueueDelete (
  EmsEventMng *EventMng
  )
/*++

Routine Description:

  The destructor of the EMS event queue

Arguments:

  EventMng  - The data structure of event lists

Returns:

  None

--*/
{
  EmsEvent  *Node;

  Node = NULL;

  WaitForSingleObject (EventMng->EmsEventListMutex, INFINITE);
  while (NULL != EventMng->EmsEventListHead) {
    Node                        = EventMng->EmsEventListHead;
    EventMng->EmsEventListHead  = EventMng->EmsEventListHead->Next;
    Tcl_DecrRefCount (Node->Script);
    free (Node);
  }

  ReleaseMutex (EventMng->EmsEventListMutex);
  WaitForSingleObject (EventMng->EmsEventFreeListMutex, INFINITE);
  while (NULL != EventMng->EmsEventFreeList) {
    Node                        = EventMng->EmsEventFreeList;
    EventMng->EmsEventFreeList  = EventMng->EmsEventFreeList->Next;
    free (Node);
  }

  ReleaseMutex (EventMng->EmsEventFreeListMutex);
  CloseHandle (EventMng->EmsEventListMutex);
  CloseHandle (EventMng->EmsEventFreeListMutex);
}

/*-------------------------------------------------------------------------*/
STATIC
VOID
ThreadHashTableInit (
  VOID
  )
/*++

Routine Description:

  The routine for EMS thread hash table initialization

Arguments:

  None

Returns:

  None

--*/
{
  UINT32  Idx;
  ThreadHashTableMutex = CreateMutex (NULL, FALSE, NULL);
  for (Idx = 0; Idx < THREADHASHTABLESIZE; Idx++) {
    EmsThreadHashTable[Idx] = NULL;
  }
}

STATIC
VOID
ThreadHashAdd (
  EmsThread *Thread
  )
/*++

Routine Description:

  Add a new thread to the EMS thread hash table

Arguments:

  Thread  - The new thread to be added to the hash table

Returns:

  None

--*/
{
  UINT32  Idx;

  Idx = HASH (Thread->ThreadId);

  WaitForSingleObject (ThreadHashTableMutex, INFINITE);
  Thread->Next            = EmsThreadHashTable[Idx];
  EmsThreadHashTable[Idx] = Thread;
  ReleaseMutex (ThreadHashTableMutex);
}

STATIC
VOID
ThreadHashDel (
  EmsThread *Thread
  )
/*++

Routine Description:

  Delete a thread from the EMS thread hash table

Arguments:

  Thread  - The thread to be deleted from hash table

Returns:

  None

--*/
{
  UINT32    Idx;
  EmsThread **Head;
  Idx = HASH (Thread->ThreadId);

  WaitForSingleObject (ThreadHashTableMutex, INFINITE);
  Head = &EmsThreadHashTable[Idx];
  if (*Head == Thread) {
    *Head = (*Head)->Next;
  } else {
    for (; (*Head) && (*Head)->Next != Thread; Head = &(*Head)->Next)
      ;
    if (*Head) {
      (*Head)->Next = (*Head)->Next->Next;
    }
  }

  ReleaseMutex (ThreadHashTableMutex);
}

STATIC
VOID
ThreadHashTableExit (
  VOID
  )
/*++

Routine Description:

  The destructor of the EMS thread hash table

Arguments:

  None

Returns:

  None

--*/
{
  UINT32    Idx;
  EmsThread *Tmp;
  DWORD     Result;
  Tmp = NULL;

  WaitForSingleObject (ThreadHashTableMutex, INFINITE);
  for (Idx = 0; Idx < THREADHASHTABLESIZE; Idx++) {
    if (Tmp = EmsThreadHashTable[Idx]) {
      if (Tmp != EmsMainThread) {
        EmsThreadCancel (Tmp, &Result);
      }

      ThreadHashDel (Tmp);
    }
  }

  ReleaseMutex (ThreadHashTableMutex);
}

/*------------------------------------------------------------------------------*/
STATIC EmsThread  *EmsThreadStructPool    = NULL;
STATIC UINT32     EmsThreadStructPoolNum  = 0;
STATIC HANDLE     EmsThreadStructPoolMutex;

#define EmsThreadStructPoolMaxNum 0x20
STATIC
EmsThread *
EmsThreadStructAlloc (
  VOID
  )
/*++

Routine Description:

  Alloc an EMS thread TCB object.

Arguments:

  None

Returns:

  The new EMS thread TCB

--*/
{
  EmsThread *T;
  T = NULL;

  WaitForSingleObject (EmsThreadStructPoolMutex, INFINITE);
  if (NULL != EmsThreadStructPool) {
    T                   = EmsThreadStructPool;
    EmsThreadStructPool = EmsThreadStructPool->Next;
    EmsThreadStructPoolNum--;
  } else {
    T = (EmsThread *) malloc (sizeof (EmsThread));
  }

  ReleaseMutex (EmsThreadStructPoolMutex);
  return T;
}

STATIC
VOID
EmsThreadStructFree (
  EmsThread *Thread
  )
/*++

Routine Description:

  Free an EMS thread TCB

Arguments:

  Thread  - The EMS TCB to be free

Returns:

  None

--*/
{
  WaitForSingleObject (EmsThreadStructPoolMutex, INFINITE);
  if (EmsThreadStructPoolNum >= EmsThreadStructPoolMaxNum) {
    free (Thread);
  } else {
    Thread->Next        = EmsThreadStructPool;
    EmsThreadStructPool = Thread;
    EmsThreadStructPoolNum++;
  }

  ReleaseMutex (EmsThreadStructPoolMutex);
}

STATIC
VOID
EmsThreadStructPoolDelete (
  VOID
  )
/*++

Routine Description:

  The destructor of the EMS thread TCBs' pool

Arguments:

  None

Returns:

  None

--*/
{
  EmsThread *Tmp;
  Tmp = NULL;

  WaitForSingleObject (EmsThreadStructPoolMutex, INFINITE);
  while (EmsThreadStructPool) {
    Tmp                 = EmsThreadStructPool;
    EmsThreadStructPool = EmsThreadStructPool->Next;
    free (Tmp);
  }

  ReleaseMutex (EmsThreadStructPoolMutex);
  CloseHandle (EmsThreadStructPoolMutex);
}

#undef EmsThreadStructPoolMaxNum

/*------------------------------------------------------------------------------*/
BOOLEAN
EmsThreadValid (
  EmsThread *Thread
  )
/*++

Routine Description:

  Check whether the thread is an EMS thread

Arguments:

  Thread  - The TCB of the thread to be checked

Returns:

  TRUE or FALSE

--*/
{
  EmsThread *Tmp;
  UINT32    Idx;
  Tmp = NULL;
  Idx = 0;

  if (Thread == NULL) {
    return FALSE;
  }

  Idx = Thread->ThreadId;
  WaitForSingleObject (ThreadHashTableMutex, INFINITE);
  for (Tmp = EmsThreadHashTable[HASH (Idx)]; Tmp != Thread; Tmp = Tmp->Next)
    ;
  ReleaseMutex (ThreadHashTableMutex);
  return Tmp ? TRUE : FALSE;
}

EmsThread *
EmsThreadSelf (
  VOID
  )
/*++

Routine Description:

  Get the current EMS thread

Arguments:

  None

Returns:

  Return the current EMS thread

--*/
{
  EmsThread *Self;
  UINT32    Idx;
  Self  = NULL;
  Idx   = GetCurrentThreadId ();

  WaitForSingleObject (ThreadHashTableMutex, INFINITE);
  for (Self = EmsThreadHashTable[HASH (Idx)]; Self && Self->ThreadId != Idx; Self = Self->Next)
    ;
  ReleaseMutex (ThreadHashTableMutex);
  return Self;
}

#undef HASH

VOID
EmsThreadInterpReset (
  INT32 (*InitHook) (Tcl_Interp *)
  )
/*++

Routine Description:

  Reset the current EMS thread's Tcl Interp. All of the EMS 
  thread has one Tcl Interp which be recorded in their TCB 
  for evaluating Tcl scripts

Arguments:

  InitHook - The Hook routine to initialize the EMS thread's 
             Interp

Returns:

  None

--*/
{
  EmsThread *Self;

  Self = EmsThreadSelf ();

  Tcl_DeleteInterp (Self->Interp);
  Self->Interp = Tcl_CreateInterp ();
  if (Tcl_Init (Self->Interp) == TCL_ERROR) {
    goto InterpResetError;

  }

  if (Self->InitScript) {
    Tcl_EvalObj (Self->Interp, Self->InitScript);

  }

  if ((*InitHook) (Self->Interp) != TCL_OK) {
    printf ("EmsThreadInterpReset failure\n");
  }

  return ;

InterpResetError:
  Tcl_DeleteInterp (Self->Interp);
}

EFI_STATUS
EmsThreadSuspend (
  EmsThread *Thread
  )
/*++

Routine Description:

  Suspend an EMS thread

Arguments:

  Thread  - The EMS thread to be suspended

Returns:

  EFI_SUCCESS or EFI_INVALID_PARAMETER

--*/
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  WaitForSingleObject(EmsThreadLock, INFINITE);
  if (Thread == EmsThreadSelf()) {
  	ReleaseMutex(EmsThreadLock);
	SuspendThread (Thread->ThreadHdl);
	return Status;
  } else {
    if (EmsThreadValid(Thread)) {
      SuspendThread (Thread->ThreadHdl);
    } else {
      Status = EFI_INVALID_PARAMETER;
    }
  }
  ReleaseMutex(EmsThreadLock);

  return Status;
}

EFI_STATUS
EmsThreadResume (
  EmsThread *Thread
  )
/*++

Routine Description:

  Resume an EMS thread

Arguments:

  Thread  - The EMS thread to be resumed

Returns:

  EFI_SUCCESS or EFI_INVALID_PARAMETER

--*/
{
  EFI_STATUS Status;

  Status = EFI_INVALID_PARAMETER;
  WaitForSingleObject(EmsThreadLock, INFINITE);
  if (EmsThreadValid(Thread)) {
  	ResumeThread (Thread->ThreadHdl);
	Status = EFI_SUCCESS;
  }
  ReleaseMutex(EmsThreadLock);
  return Status;
}

EFI_STATUS
EmsThreadWait (
  VOID
  )
/*++

Routine Description:

  The EMS thread block itself until another thread signal it

Arguments:

  None

Returns:

  EFI_SUCCESS

--*/
{
  WaitForSingleObject (EmsThreadSelf()->Block, INFINITE);
  return EFI_SUCCESS;
}

EFI_STATUS
EmsThreadSignal (
  EmsThread *Thread
  )
/*++

Routine Description:

  One EMS thread signal another blocked EMS thread to run

Arguments:

  Thread  - The EMS thread to be signaled

Returns:

  EFI_SUCCESS or EFI_INVALID_PARAMETER

--*/
{
  EFI_STATUS Status;

  Status = EFI_INVALID_PARAMETER;
  WaitForSingleObject(EmsThreadLock, INFINITE);
  if (EmsThreadValid(Thread)) {
    SetEvent (Thread->Block);
	Status = EFI_SUCCESS;
  }
  ReleaseMutex(EmsThreadLock);
  return Status;
}

EFI_STATUS
EmsThreadJoin (
  EmsThread *Thread,
  DWORD     *ExitCode
  )
/*++

Routine Description:

  Implementation of EMS thread join

Arguments:

  Thread    - The TCB of the target thread
  ExitCode  - The result of target thread execution

Returns:

  EFI_SUCCESS or EFI_INVALID_PARAMETER

--*/
{
  WaitForSingleObject(EmsThreadLock, INFINITE);
  if (EmsThreadValid(Thread) != TRUE) {
    ReleaseMutex(EmsThreadLock);
	return EFI_INVALID_PARAMETER;
  }
  ReleaseMutex(EmsThreadLock);
  WaitForSingleObject (Thread->ThreadHdl, INFINITE);
  GetExitCodeThread (Thread->ThreadHdl, ExitCode);
  return EFI_SUCCESS;
}

STATIC
VOID
EmsThreadDataCleanup (
  EmsThread *Thread
  )
/*++

Routine Description:

  clean up the EMS thread's private data.

Arguments:

  Thread  - The thread to be cleanup

Returns:

  None

--*/
{
  ThreadHashDel (Thread);
//  Tcl_DeleteInterp (Thread->Interp);
  if (Thread->InitScript) {
    Tcl_DecrRefCount (Thread->InitScript);
  }

  CloseHandle (Thread->Block);
  EmsThreadStructFree (Thread);
}

EFI_STATUS
EmsThreadCancel (
  EmsThread *Thread,
  DWORD     *Result
  )
/*++

Routine Description:

  Implementation of EMS thread cancel

Arguments:

  Thread  - The thread to be cancelled.
  Result  - The result of target thread execution

Returns:

  EFI_SUCCESS

--*/
{
  WaitForSingleObject (EmsThreadLock, INFINITE);
  if (EmsThreadValid (Thread) && Thread->Exit != TRUE) {
    TerminateThread (Thread->ThreadHdl, 0);
    EmsThreadDataCleanup (Thread);
  }
  ReleaseMutex (EmsThreadLock);
  *Result = 0;
  return EFI_SUCCESS;
}

VOID
EmsThreadExit (
  DWORD ExitCode
  )
/*++

Routine Description:

  The EMS thread finish running and exit

Arguments:

  ExitCode  - The result of target thread execution

Returns:

  None

--*/
{
  EmsThread *Self;
  Self = EmsThreadSelf ();

  WaitForSingleObject (EmsThreadLock, INFINITE);
  Self->Exit = TRUE;
  EmsThreadDataCleanup (Self);
  ReleaseMutex (EmsThreadLock);
  EmsThreadNum--;
#ifdef EMSTHREADDEBUG
  printf ("======EmsThreadExit EmsThreadNum:%d\n", EmsThreadNum);
#endif
  ExitThread (ExitCode);
}

VOID RivlTclInit (Tcl_Interp *Interp);

DWORD
WINAPI
EmsThreadInit (
  LPVOID Parameter
  )
/*++

Routine Description:

  The common entry of all the EMS threads

Arguments:

  Parameter - Point to the TCB of current EMS thread

Returns:

  0

--*/
{
  EmsThread *Thread     = (EmsThread *)Parameter;
  VOID (*Entry)(VOID *) = Thread->Entry;
  VOID *Arg             = Thread->Arg;

  Thread->ThreadId = GetCurrentThreadId ();
  ThreadHashAdd (Thread);
  SetEvent (ThreadCreateEvent);

  RivlTclInit (Thread->Interp);

  if (Thread->InitScript) {
    Tcl_EvalObj (Thread->Interp, Thread->InitScript);

  }

  if (Entry) {
    (*Entry) (Arg);
  }

  EmsThreadExit (0);

  return 0;
}

EFI_STATUS
EmsCreateThread (
  EmsThread  **New,
  VOID (*Proc)(VOID *),
  VOID *Arg,
  Tcl_Interp *Interp,
  INT8 *InitScript
  )
/*++

Routine Description:

  Implementation of creating an EMS thread

Arguments:

  New         - Point to the new thread's TCB
  Proc        - The new thread's routine for execution
  Arg         - The parameter of the new thread's routine
  Interp      - The TCL Interp 
  InitScript  - The init TCL script for new thread

Returns:

  EFI_SUCCESS, EFI_CREATE_ERROR or EFI_OUT_OF_RESOURCES

--*/
{
  DWORD ThreadId;

  if (NULL == (*New = EmsThreadStructAlloc ())) {
    printf ("EmsCreateThread malloc EmsThread Failure\n");
    return EFI_OUT_OF_RESOURCES;
  }

  (*New)->Entry = Proc;
  (*New)->Arg   = Arg;
  if (Interp) {
    (*New)->Interp = Interp;
  } else {
    (*New)->Interp = Tcl_CreateInterp ();
    Tcl_Init ((*New)->Interp);
  }
  (*New)->Exit        = FALSE;
  (*New)->Block       = CreateEvent (0, FALSE, FALSE, NULL);
  (*New)->Next        = NULL;

  (*New)->InitScript  = NULL;
  if (InitScript) {
    (*New)->InitScript = Tcl_NewObj ();
    Tcl_AppendStringsToObj ((*New)->InitScript, InitScript, NULL);
    Tcl_IncrRefCount ((*New)->InitScript);
  }

  if (((*New)->ThreadHdl = CreateThread (
                            NULL,
                            0,
                            EmsThreadInit,
                            (VOID *) (*New),
                            0,
                            &ThreadId
                            )) == NULL) {
    goto CreateThreadError;

  }

  EmsThreadNum++;
  WaitForSingleObject (ThreadCreateEvent, INFINITE);

  return EFI_SUCCESS;
CreateThreadError:
  CloseHandle ((*New)->Block);
  EmsThreadStructFree (*New);
  return EFI_CREATE_ERROR;
}

EFI_STATUS
ThreadCommand (
  EmsThread    *Target,
  INT8         *CmdString,
  EMS_CMD_TYPE Type,
  INT8         *Result
  )
/*++

Routine Description:

  Create an EMS thread to execute a command

Arguments:

  Target    - The target thread which will execute command
  CmdString - The string of the command
  Type      - The type of the command synchronization or asynchronism
  Result    - The result of the command execution

Returns:

  EFI_SUCCESS or EFI_OUT_OF_RESOURCES

--*/
{
  EFI_STATUS Status;
  Tcl_Obj    *CmdObj;
  EmsEvent   *Event;

  Status = EFI_SUCCESS;
  Event  = NULL;

  if (NULL == CmdString) {
  	printf("######ThreadCommand CmdString is NULL\n");
  	return EFI_INVALID_PARAMETER;
  }

  Status = EmsAllocEventObj (&Event, &EmsThreadEventMng);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  CmdObj = Tcl_NewObj ();
  Tcl_AppendStringsToObj (CmdObj, CmdString, NULL);
  Tcl_IncrRefCount (CmdObj);

  Event->Script     = CmdObj;
  Event->Result     = NULL;
  Event->Type       = Type;
  Event->SrcThread  = EmsThreadSelf ();
  Event->ExecThread = Target;
#ifdef EMSEVENTDEBUG
  if (Event->ScriptString = (INT8 *) malloc (strlen (CmdString) + 1)) {
    strcpy (Event->ScriptString, CmdString);
  }
#endif

  WaitForSingleObject (EmsThreadEventMng.EmsEventListMutex, INFINITE);
  EmsPutOneEvent (Event, &EmsThreadEventMng);
  Tcl_Sleep(10);
  ReleaseMutex (EmsThreadEventMng.EmsEventListMutex);

  switch (Type) {
  case CMD_WAIT:
#ifdef EMSEVENTDEBUG
    printf ("======ThreadCommand wait for Cmd %s\n", Event->ScriptString);
#endif
    EmsThreadWait ();
#ifdef EMSEVENTDEBUG
    printf ("======ThreadCommand Resume from Cmd %s\n", Event->ScriptString);
#endif
    if (Result) {
      strcpy (Result, Tcl_GetStringFromObj (Event->Result, NULL));
    }
    EmsFreeEventObj (Event, &EmsThreadEventMng);
    break;

  case CMD_NOWAIT:
  default:
    ;
  }

  return Status;
}

EFI_STATUS
EmsThreadEnable (
  EmsThread  *MainThread,
  Tcl_Interp *Interp
  )
/*++

Routine Description:

  Enable the EMS thread utility

Arguments:

  MainThread  - The main thread of the application
  Interp      - The TCL Interp of the main thread

Returns:

  EFI_SUCCESS or EFI_OUT_OF_RESOURCES

--*/
{
  EmsTclResMng  *Res;

  Res = NULL;

  if (NULL == (Res = (EmsTclResMng *) malloc (sizeof (EmsTclResMng)))) {
    printf ("EmsThreadEnable malloc EmsTclResMng Failure\n");
    return EFI_OUT_OF_RESOURCES;
  }

  ThreadCreateEvent = CreateEvent (0, FALSE, FALSE, NULL);
  EmsThreadLock     = CreateMutex (0, FALSE, NULL);

  EmsEventQueueInit (&EmsThreadEventMng);

  EmsMainThread         = MainThread;
  MainThread->ThreadId  = GetCurrentThreadId ();
  MainThread->ThreadHdl = GetCurrentThread ();
  MainThread->Interp    = Interp;
  MainThread->Exit      = FALSE;
  MainThread->Next      = NULL;
  ThreadHashTableInit ();
  ThreadHashAdd (MainThread);

  Res->CleanupFunc  = EmsThreadDisable;
  Res->Res          = NULL;
  EmsTclResStackPush (Res);

  return EFI_SUCCESS;
}

VOID *
EmsThreadDisable (
  VOID *Arg
  )
/*++

Routine Description:

  Disable the EMS thread utility

Arguments:

  Arg - No use

Returns:

  NULL

--*/
{
#ifdef EMSEVENTDEBUG
  printf ("======Enter EmsThreadDisable\n");
#endif
  ThreadHashTableExit ();
  CloseHandle (EmsThreadLock);
  CloseHandle (ThreadHashTableMutex);
  CloseHandle (ThreadCreateEvent);
  EmsEventQueueDelete (&EmsThreadEventMng);
  EmsThreadStructPoolDelete ();
#ifdef EMSEVENTDEBUG
  printf ("======Exit EmsThreadDisable\n");
#endif
  return NULL;
}
