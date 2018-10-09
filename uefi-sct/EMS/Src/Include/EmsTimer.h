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
  
    EmsTimer.h
    
Abstract:

    Incude header files for EMS TCL Timer functions

--*/

#ifndef __EMSTIMER__
#define __EMSTIMER__

#include <tcl.h>
#include <EmsTypes.h>

typedef struct EmsTimerStruct {
  UINT32  Timeout;
  BOOLEAN TimerValid;
  VOID (*Func) (VOID *Arg);
  VOID  *Arg;
} EmsTimer;

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
;

EmsTimer  *
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
;

#endif
