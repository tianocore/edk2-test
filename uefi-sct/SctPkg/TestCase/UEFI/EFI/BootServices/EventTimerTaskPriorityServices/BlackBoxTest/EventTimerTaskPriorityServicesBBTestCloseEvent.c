/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EventTimerTaskPriorityServicesBBTestCloseEvent.c

Abstract:

  Test Driver of CloseEvent() of Event and Timer and Task Priority Services

--*/

#include "SctLib.h"
#include "EventTimerTaskPriorityServicesBBTestMain.h"

//
// Declarations
//

EFI_STATUS
EFIAPI
BBTestCloseEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Functions
//

EFI_STATUS
EFIAPI
BBTestCloseEvent_Func (
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
  // CloseEvents() returns EFI_SUCCESS with all valid parameters.
  //
  BBTestCloseEvent_Func_Sub1 (StandardLib);

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
BBTestCloseEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINTN               SubIndex;
  UINT32              EventTypes[] = {
                        EVT_TIMER,
                        EVT_NOTIFY_WAIT,
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

  //
  // Walk through the common event types and notify TPLs
  //
  for (Index = 0; EventTypes[Index] != 0; Index++) {
    for (SubIndex = 0; NotifyTpls[SubIndex] != 0; SubIndex++) {
      //
      // Create an event
      //
      Status = gtBS->CreateEvent (
                       EventTypes[Index],
                       NotifyTpls[SubIndex],
                       NotifyFunction,
                       NULL,
                       &Event
                       );
      if (EFI_ERROR (Status)) {
        EFI_TEST_GENERIC_FAILURE (L"BS.CloseEvent - Create event", Status);
        return Status;
      }

      //
      // Close the event
      //
      Status = gtBS->CloseEvent (Event);

      if (Status == EFI_SUCCESS) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEventTimerTaskPriorityServicesBBTestCloseEventAssertionGuid001,
                     L"BS.CloseEvent - Close event with valid parameters.",
                     L"%a:%d:Status - %r, EventType - 0x%08x, NotifyTpl - %d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     EventTypes[Index],
                     NotifyTpls[SubIndex]
                     );
    }
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}
