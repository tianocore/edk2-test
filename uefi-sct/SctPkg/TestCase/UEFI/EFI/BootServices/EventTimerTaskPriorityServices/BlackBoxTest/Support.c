/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2019, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Support.c

Abstract:

  Test Driver of Event and Timer and Task Priority Services

--*/

#include "EventTimerTaskPriorityServicesBBTestMain.h"


VOID
EFIAPI
NotifyFunction (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  UINTN     *Buffer;

  if (Context != NULL) {
    Buffer = Context;

    Buffer[1]++;
    if (Buffer[1] <= Buffer[0]) {
      Buffer[1 + Buffer[1]] = (UINTN) Event;
    }
  }

  return;
}

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
VOID
EFIAPI
NotifyFunctionTplEx(
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  UINTN     *Buffer;
  EFI_TPL   OldTpl;
  UINTN     EventIndex;
  UINTN     Index;

  if (Context != NULL) {
    Buffer = Context;

    EventIndex = Buffer[0];

    //
    // The event's context is offset by EventIndex from the true buffer start.
    // Skip over the MAX_TEST_EVENT_NUM leading index entries.
    // A maximum of MAX_TEST_EVENT_NUM events can be recorded.
    //
    for (Index = MAX_TEST_EVENT_NUM-EventIndex;
         Index < 3*MAX_TEST_EVENT_NUM-EventIndex; Index += 2) {
      if (Buffer[Index] == (UINTN)(SIGNAL_CONTEXT)) {
        OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
        gtBS->RestoreTPL (OldTpl);

        Buffer[Index] = EventIndex;
        Buffer[Index+1] = OldTpl;
        return;
      }
    }
  }
}
#endif

VOID
EFIAPI
NotifyFunctionTpl (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  UINTN     *Buffer;
  EFI_TPL   OldTpl;

  if (Context != NULL) {
    Buffer = Context;

    OldTpl = gtBS->RaiseTPL (TPL_HIGH_LEVEL);
    gtBS->RestoreTPL (OldTpl);

    Buffer[1]++;
    if (Buffer[1] <= Buffer[0]) {
      Buffer[1 + Buffer[1]] = (UINTN) OldTpl;
    }
  }

  return;
}


VOID
EFIAPI
NotifyFunctionSignal (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  gtBS->SignalEvent (Event);
  return;
}

VOID
EFIAPI
NotifyFunctionNoSignal (
  IN EFI_EVENT                  Event,
  IN VOID                       *Context
  )
{
  return;
}
