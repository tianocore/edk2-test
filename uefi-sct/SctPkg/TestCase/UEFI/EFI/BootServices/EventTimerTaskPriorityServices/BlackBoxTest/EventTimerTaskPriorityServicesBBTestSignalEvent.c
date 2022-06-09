/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EventTimerTaskPriorityServicesBBTestSignalEvent.c

Abstract:

  Test Driver of SignalEvent() of Event and Timer and Task Priority Services

--*/

#include "SctLib.h"
#include "EventTimerTaskPriorityServicesBBTestMain.h"

//
// Declarations
//

EFI_STATUS
EFIAPI
BBTestSignalEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Functions
//

EFI_STATUS
EFIAPI
BBTestSignalEvent_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;

  //
  // Locate standard test library
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **)&StandardLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // SignalEvent() returns EFI_SUCCESS with all valid parameters.
  //
  BBTestSignalEvent_Func_Sub1 (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Sub functions
//

EFI_STATUS
EFIAPI
BBTestSignalEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_STATUS          Status1;
  EFI_STATUS          Status2;
  UINTN               Index;
  UINTN               SubIndex;
  EFI_TPL             OldTpl;
  UINT32              EventTypes[] = {
                        EVT_NOTIFY_SIGNAL,
                        0
                      };
  EFI_TPL             NotifyTpls[] = {
                        TPL_CALLBACK,
                        TPL_NOTIFY,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;
  UINTN               Buffer[2];

  //
  // Walk through common event types and notify TPLs
  //
  for (Index = 0; EventTypes[Index] != 0; Index++) {
    for (SubIndex = 0; NotifyTpls[SubIndex] != 0; SubIndex++) {
      //
      // Create event with valid parameters
      //
      Buffer[0] = 0;
      Buffer[1] = 0;
      Status = gtBS->CreateEvent (
                       EventTypes[Index],
                       NotifyTpls[SubIndex],
                       NotifyFunction,
                       Buffer,
                       &Event
                       );
      if (EFI_ERROR (Status)) {
        EFI_TEST_GENERIC_FAILURE (L"BS.SignalEvent - Create event", Status);
        return Status;
      }

      //
      // Signal event in the TPL_CALLBACK
      //
      OldTpl  = gtBS->RaiseTPL (TPL_CALLBACK);
      Status1 = gtBS->SignalEvent (Event);
      Status2 = gtBS->SignalEvent (Event);
      gtBS->RestoreTPL (OldTpl);

      if ((Status1   == EFI_SUCCESS) &&
          (Status2   == EFI_SUCCESS) &&
          (((NotifyTpls[SubIndex] >  TPL_CALLBACK) && (Buffer[1] == 2)) ||
           ((NotifyTpls[SubIndex] <= TPL_CALLBACK) && (Buffer[1] == 1))
          )) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEventTimerTaskPriorityServicesBBTestSignalEventAssertionGuid001,
                     L"BS.SignalEvent - Signal event with valid parameters.",
                     L"%a:%d:Status1 - %r, Status2 - %r, EventType - 0x%08x, NotifyTpl - %d, Count - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status1,
                     Status2,
                     EventTypes[Index],
                     NotifyTpls[SubIndex],
                     Buffer[1]
                     );

      //
      // Close the event
      //
      gtBS->CloseEvent (Event);
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
