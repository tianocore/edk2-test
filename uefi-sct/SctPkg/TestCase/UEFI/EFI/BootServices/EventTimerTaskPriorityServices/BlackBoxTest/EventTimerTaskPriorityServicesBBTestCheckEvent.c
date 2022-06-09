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

  EventTimerTaskPriorityServicesBBTestCheckEvent.c

Abstract:

  Test Driver of CheckEvent() of Event and Timer and Task Priority Services

--*/

#include "SctLib.h"
#include "EventTimerTaskPriorityServicesBBTestMain.h"

//
// Declarations
//

EFI_STATUS
EFIAPI
BBTestCheckEvent_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCheckEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCheckEvent_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCheckEvent_Func_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestCheckEvent_Func_Sub4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Functions
//

EFI_STATUS
EFIAPI
BBTestCheckEvent_Conf (
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
  // CheckEvent() returns EFI_INVALID_PARAMETER with an event of type
  // EVT_NOTIFY_SIGNAL.
  //
  BBTestCheckEvent_Conf_Sub1 (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestCheckEvent_Func (
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
  // CheckEvent() returns EFI_NOT_READY with an event that has not notified
  // function.
  //
  BBTestCheckEvent_Func_Sub1 (StandardLib);

  //
  // CheckEvent() returns EFI_NOT_READY with an event which the notify function
  // does not signal itself.
  //
  BBTestCheckEvent_Func_Sub2 (StandardLib);

  //
  // CheckEvent() returns EFI_SUCCESS with a signaled event.
  //
  BBTestCheckEvent_Func_Sub3 (StandardLib);

  //
  // CheckEvent() returns EFI_SUCCESS with an event which the notify function
  // would signal itself.
  //
  BBTestCheckEvent_Func_Sub4 (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


//
// Sub Functions
//

EFI_STATUS
EFIAPI
BBTestCheckEvent_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Create an event with type being EVT_NOTIFY_SIGNAL
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY,
                   NotifyFunction,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.CheckEvent - Create event", Status);
    return Status;
  }

  //
  // Check this event
  //
  Status = gtBS->CheckEvent (Event);

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestCheckEventAssertionGuid003,
                 L"BS.CheckEvent - Check event with invalid event type.",
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
BBTestCheckEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Create an event without notify function
  //
  Status = gtBS->CreateEvent (
                   EVT_TIMER,
                   TPL_NOTIFY,
                   NULL,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.CheckEvent - Create event", Status);
    return Status;
  }

  //
  // Check this event
  //
  Status = gtBS->CheckEvent (Event);

  if (Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestCheckEventAssertionGuid004,
                 L"BS.CheckEvent - Check event without notify function.",
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
BBTestCheckEvent_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Create an event with notify function, which does not signal itself
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_WAIT,
                   TPL_NOTIFY,
                   NotifyFunctionNoSignal,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.CheckEvent - Create event", Status);
    return Status;
  }

  //
  // Check this event
  //
  Status = gtBS->CheckEvent (Event);

  if (Status == EFI_NOT_READY) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestCheckEventAssertionGuid005,
                 L"BS.CheckEvent - Check event with notify function (no signal).",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Close event
  //
  gtBS->CloseEvent (Event);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestCheckEvent_Func_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Create an event with notify function
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_WAIT,
                   TPL_NOTIFY,
                   NotifyFunctionSignal,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.CheckEvent - Create event", Status);
    return Status;
  }

  //
  // Signal the event
  //
  Status = gtBS->SignalEvent (Event);
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.CheckEvent - Signal event", Status);
    return Status;
  }

  //
  // Check this event
  //
  Status = gtBS->CheckEvent (Event);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestCheckEventAssertionGuid001,
                 L"BS.CheckEvent - Check signaled event.",
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
BBTestCheckEvent_Func_Sub4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Create an event with notify function, which signals itself
  //
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_WAIT,
                   TPL_NOTIFY,
                   NotifyFunctionSignal,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.CheckEvent - Create event", Status);
    return Status;
  }

  //
  // Check this event
  //
  Status = gtBS->CheckEvent (Event);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestCheckEventAssertionGuid002,
                 L"BS.CheckEvent - Check event with notify function (signal).",
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
