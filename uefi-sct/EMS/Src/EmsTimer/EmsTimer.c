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
  
    EmsTimer.c
    
Abstract:

  Implementation of EMS Timer functions

--*/

#include <windows.h>
#include "EmsTimer.h"

STATIC
DWORD
WINAPI
EmsTimerThread (
  LPVOID Arg
  )
/*++

Routine Description:

  The thread of EMS timer to wait and do callback function

Arguments:

  Arg - The parameter of callback function

Returns:

  0

--*/
{
  EmsTimer  *Timer;

  Timer = (EmsTimer *) Arg;
  Sleep (Timer->Timeout);
  if (Timer->TimerValid == TRUE) {
    (Timer->Func) (Timer->Arg);
  }

  free (Timer);
  return 0;
}

VOID
EmsDelTimer (
  EmsTimer *Timer
  )
/*++

Routine Description:

  The implementation of deleting an EMS timer

Arguments:

  Timer - The EMS timer to be deleted

Returns:

  None

--*/
{
  Timer->TimerValid = FALSE;
}

EmsTimer *
EmsSetTimer (
  UINT32     Timeout,
  VOID (*HandleTimeout) (VOID *),
  VOID *Arg
  )
/*++

Routine Description:

  The implementation of creating an EMS timer

Arguments:

  Timeout        - The maximum seconds the timer will wait
  HandleTimeout  - The callback function if timer timeout
  Arg            - The parameter of callback function

Returns:

  The new EMS timer

--*/
{
  DWORD     ThreadId;
  EmsTimer  *Timer;

  if (NULL == (Timer = (EmsTimer *) malloc (sizeof (EmsTimer)))) {
    printf ("EmsSetTimer malloc EmsTimer Error\n");
    exit (-1);
  }

  Timer->Func       = HandleTimeout;
  Timer->Arg        = Arg;
  Timer->TimerValid = TRUE;
  Timer->Timeout    = Timeout;

  if (CreateThread (NULL, 0, EmsTimerThread, (LPVOID) Timer, 0, &ThreadId) == NULL) {
    printf ("EmsSetTimer CreateThread Error\n");
    exit (-1);
  }

  return Timer;
}
