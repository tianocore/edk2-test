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
  
    EmsThread.h
    
Abstract:

    Incude header files for EMS TCL Thread functions

--*/

#ifndef __EMSTHREADS__
#define __EMSTHREADS__

#include <tcl.h>
#include <windows.h>
#include <EmsTypes.h>
#include <EmsMain.h>

typedef enum {
  CMD_NOWAIT,
  CMD_WAIT
} EMS_CMD_TYPE;

typedef struct EmsThreadStruct {
  DWORD   ThreadId;
  HANDLE  ThreadHdl;
  VOID (*Entry) (VOID *);
  VOID                    *Arg;
  struct EmsThreadStruct  *Next;

  Tcl_Interp              *Interp;
  Tcl_Obj                 *InitScript;

  BOOLEAN                 Exit;

  HANDLE                  Block;
} EmsThread;

typedef struct EmsEventStruct {
#ifdef EMSEVENTDEBUG
  INT8                  *ScriptString;
#endif
  EMS_CMD_TYPE          Type;
  Tcl_Obj               *Script;
  Tcl_Obj               *Result;
  EmsThread             *SrcThread;
  EmsThread             *ExecThread;
  struct EmsEventStruct *Next;
} EmsEvent;

typedef struct EmsEventMngStruct {
#ifdef EMSEVENTDEBUG
  INT8      *EmsEventMngName;
  UINT32    EmsEventNum;
#endif
  EmsEvent  *EmsEventListHead;
  EmsEvent  *EmsEventListTail;
  HANDLE    EmsEventListMutex;

  UINT32    EmsFreeEventNum;
  EmsEvent  *EmsEventFreeList;
  HANDLE    EmsEventFreeListMutex;
} EmsEventMng;

#define EmsEventListIsEmpty(Mng)  ((Mng)->EmsEventListHead == NULL)

#define EmsEventQueueLock(E)      (WaitForSingleObject ((E)->EmsEventListMutex, INFINITE))
#define EmsEventQueueUnlock(E)    (ReleaseMutex ((E)->EmsEventListMutex))

#define EmsEventWait(Event)       ((Event)->Type == CMD_WAIT)

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
;

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
;

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
;

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
;

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
;

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
;

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
;

EFI_STATUS
EmsThreadCancel (
  EmsThread   *Thread,
  DWORD       *Result
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
;

EFI_STATUS
EmsCreateThread (
  EmsThread  **New,
  VOID
    (
  *Proc)(
      VOID *
    ),
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
;

EFI_STATUS
ThreadCommand (
  EmsThread    *Target,
  INT8         *CmdString,
  EMS_CMD_TYPE Priority,
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
;

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
;

VOID                *
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
;

VOID
EmsPutOneEvent (
  EmsEvent    *Event,
  EmsEventMng *EventMng
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
;

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
;

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
;

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
;

extern EmsEventMng  EmsThreadEventMng;

extern UINT32       EmsThreadNum;

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
;

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
;

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
;

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
;
#endif

#endif
