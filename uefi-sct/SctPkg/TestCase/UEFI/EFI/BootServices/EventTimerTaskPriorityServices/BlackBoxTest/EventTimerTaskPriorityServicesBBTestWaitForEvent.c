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

  EventTimerTaskPriorityServicesBBTestWaitForEvent.c

Abstract:

  Test Driver of WaitForEvent() of Event and Timer and Task Priority Services

--*/

#include "SctLib.h"
#include "EventTimerTaskPriorityServicesBBTestMain.h"

//
// Declarations
//

EFI_STATUS
EFIAPI
BBTestWaitForEvent_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestWaitForEvent_Conf_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestWaitForEvent_Conf_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestWaitForEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestWaitForEvent_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Functions
//

EFI_STATUS
EFIAPI
BBTestWaitForEvent_Conf (
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
  // WaitForEvent() returns EFI_UNSUPPORTED from invalid TPL.
  //
  BBTestWaitForEvent_Conf_Sub1 (StandardLib);

  //
  // WaitForEvent() returns EFI_INVALID_PARAMETER with an event of type
  // EVT_NOTIFY_SIGNAL.
  //
  BBTestWaitForEvent_Conf_Sub2 (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestWaitForEvent_Func (
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
  // WaitForEvent() gets the correct index with signaled event.
  //
  BBTestWaitForEvent_Func_Sub1 (StandardLib);

  //
  // WaitForEvent() gets the correct index with unsignaled event.
  //
  BBTestWaitForEvent_Func_Sub2 (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestWaitForEvent_Stress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  return EFI_SUCCESS;
}

//
// Sub functions
//

EFI_STATUS
EFIAPI
BBTestWaitForEvent_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  EFI_TPL             OldTpl;
  EFI_TPL             CheckTpls[] = {
                        TPL_CALLBACK,
                        TPL_NOTIFY,
                        TPL_HIGH_LEVEL,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;
  UINTN               EventIndex;

  //
  // Create an event
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_WAIT,
                   TPL_NOTIFY,
                   NotifyFunction,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.WaitForEvent - Create event", Status);
    return Status;
  }

  //
  // Wait for event at invalid TPLs
  //
  for (Index = 0; CheckTpls[Index] != 0; Index++) {
    OldTpl = gtBS->RaiseTPL (CheckTpls[Index]);
    Status = gtBS->WaitForEvent (1, &Event, &EventIndex);
    gtBS->RestoreTPL (OldTpl);

    if (Status == EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEventTimerTaskPriorityServicesBBTestWaitForEventAssertionGuid004,
                   L"BS.WaitForEvent - Invoke WaitForEvent from invalid TPL.",
                   L"%a:%d:Status - %r, TPL - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   CheckTpls[Index]
                   );
  }

  //
  // Close the event
  //
  gtBS->CloseEvent (Event);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestWaitForEvent_Conf_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;
  UINTN               EventIndex;

  //
  // Create an event
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY,
                   NotifyFunction,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.WaitForEvent - Create event", Status);
    return Status;
  }

  //
  // Wait for event with invalid event type
  //
  Status = gtBS->WaitForEvent (1, &Event, &EventIndex);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestWaitForEventAssertionGuid005,
                 L"BS.WaitForEvent - Invoke WaitForEvent with invalid event type.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Close the event
  //
  gtBS->CloseEvent (Event);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestWaitForEvent_Conf_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;
  UINTN               EventIndex;

  //
  // Create an event
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_WAIT,
                   TPL_NOTIFY,
                   NotifyFunction,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.WaitForEvent - Create event", Status);
    return Status;
  }

  //
  // Wait for event with invalid event number
  //
  Status = gtBS->WaitForEvent (0, &Event, &EventIndex);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestWaitForEventAssertionGuid006,
                 L"BS.WaitForEvent - Invoke WaitForEvent with invalid event number.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Close the event
  //
  gtBS->CloseEvent (Event);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestWaitForEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;
  UINTN               EventIndex;

  //
  // Create an event
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_WAIT,
                   TPL_NOTIFY,
                   NotifyFunction,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.WaitForEvent - Create event", Status);
    return Status;
  }

  //
  // Signal the event
  //
  Status = gtBS->SignalEvent (Event);
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.WaitForEvent - Signal event", Status);
    return Status;
  }

  //
  // Wait for event with signaled event
  //
  Status = gtBS->WaitForEvent (1, &Event, &EventIndex);

  if ((Status     == EFI_SUCCESS) &&
      (EventIndex == 0          )) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestWaitForEventAssertionGuid001,
                 L"BS.WaitForEvent - Invoke WaitForEvent with signaled event.",
                 L"%a:%d:Status - %r, EventIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EventIndex
                 );

  //
  // Close the event
  //
  gtBS->CloseEvent (Event);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestWaitForEvent_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event[2];
  UINTN               EventIndex;

  //
  // Create an event
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_WAIT,
                   TPL_NOTIFY,
                   NotifyFunction,
                   NULL,
                   &Event[0]
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.WaitForEvent - Create event", Status);
    return Status;
  }

  //
  // Create a timer event and set it
  //
  Status = gtBS->CreateEvent (
                   EVT_TIMER,
                   TPL_NOTIFY,
                   NotifyFunction,
                   NULL,
                   &Event[1]
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.WaitForEvent - Create timer event", Status);
    gtBS->CloseEvent (Event[0]);
    return Status;
  }

  Status = gtBS->SetTimer (
                   Event[1],
                   TimerRelative,
                   10000000           // 1 second
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.WaitForEvent - Set timer", Status);
    gtBS->CloseEvent (Event[0]);
    gtBS->CloseEvent (Event[1]);
    return Status;
  }

  //
  // Wait for event with signaled event
  //
  Status = gtBS->WaitForEvent (2, Event, &EventIndex);

  if ((Status     == EFI_SUCCESS) &&
      (EventIndex == 1          )) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestWaitForEventAssertionGuid002,
                 L"BS.WaitForEvent - Invoke WaitForEvent with timer event.",
                 L"%a:%d:Status - %r, EventIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EventIndex
                 );

  //
  // Close the event
  //
  gtBS->CloseEvent (Event[0]);
  gtBS->CloseEvent (Event[1]);

  //
  // Done
  //
  return EFI_SUCCESS;
}
