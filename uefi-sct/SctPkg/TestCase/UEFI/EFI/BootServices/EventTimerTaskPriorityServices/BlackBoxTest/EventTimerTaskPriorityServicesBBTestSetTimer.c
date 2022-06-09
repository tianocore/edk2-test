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

  EventTimerTaskPriorityServicesBBTestSetTimer.c

Abstract:

  Test Driver of SetTimer() of Event and Timer and Task Priority Services

--*/

#include "SctLib.h"
#include "EventTimerTaskPriorityServicesBBTestMain.h"

//
// Declarations
//

EFI_STATUS
EFIAPI
BBTestSetTimer_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestSetTimer_Conf_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestSetTimer_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestSetTimer_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestSetTimer_Func_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestSetTimer_Func_Sub4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestSetTimer_Func_Sub5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
EFIAPI
BBTestSetTimer_Func_Sub6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Functions
//

EFI_STATUS
EFIAPI
BBTestSetTimer_Conf (
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
  // SetTimer() returns EFI_INVALID_PARAMETER with an event which type does not
  // include EVT_TIMER.
  //
  BBTestSetTimer_Conf_Sub1 (StandardLib);

  //
  // SetTimer() returns EFI_INVALID_PARAMETER with invalid timer type.
  //
  BBTestSetTimer_Conf_Sub2 (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetTimer_Func (
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
  // SetTimer() with type of TimerRelative, the notify function will be invoked
  // once.
  //
  BBTestSetTimer_Func_Sub1 (StandardLib);

  //
  // SetTimer() with type of TimerPeriodic, the notify function will be invoked
  // more than once.
  //
  BBTestSetTimer_Func_Sub2 (StandardLib);

  //
  // SetTimer() with type of TimerCancel, the notify function will not be
  // invoked.
  //
  BBTestSetTimer_Func_Sub3 (StandardLib);

  //
  // The notify function will be invoked correctly after the timer type is
  // changed by SetTimer().
  //
  BBTestSetTimer_Func_Sub4 (StandardLib);

  //
  // SetTimer() returns EFI_SUCCESS with TriggerTime being 0.
  //
  BBTestSetTimer_Func_Sub5 (StandardLib);

  //
  // SetTimer() with type of TimerPeriodic, the notify function will be invoked
  // more than once.
  //
  BBTestSetTimer_Func_Sub6 (StandardLib);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetTimer_Stress (
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
BBTestSetTimer_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  UINT32              EventTypes[] = {
                        EVT_NOTIFY_WAIT,
                        EVT_NOTIFY_SIGNAL,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Walk through the event types without EVT_TIMER
  //
  for (Index = 0; EventTypes[Index] != 0; Index++) {
    //
    // Create an event
    //
    Status = gtBS->CreateEvent (
                     EventTypes[Index],
                     TPL_NOTIFY,
                     NotifyFunction,
                     NULL,
                     &Event
                     );
    if (EFI_ERROR (Status)) {
      EFI_TEST_GENERIC_FAILURE (L"BS.SetTimer - Create event", Status);
      return Status;
    }

    //
    // Set timer with the invalid event type
    //
    Status = gtBS->SetTimer (
                     Event,
                     TimerPeriodic,
                     1
                     );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEventTimerTaskPriorityServicesBBTestSetTimerAssertionGuid007,
                   L"BS.SetTimer - Set timer with invalid event type.",
                   L"%a:%d:Status - %r, EventType - 0x%08x",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EventTypes[Index]
                   );

    //
    // Close the event
    //
    gtBS->CloseEvent (Event);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetTimer_Conf_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  UINTN               Index;
  EFI_TIMER_DELAY     InvalidTimerTypes[] = {
                        TimerRelative + 1, //OM: Add a condition on the UEFI spec version
                        -1,
                        0
                      };
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;

  //
  // Walk through the invalid timer types
  //
  for (Index = 0; InvalidTimerTypes[Index] != 0; Index++) {
    //
    // Create an event
    //
    Status = gtBS->CreateEvent (
                     EVT_TIMER | EVT_NOTIFY_SIGNAL,
                     TPL_NOTIFY,
                     NotifyFunction,
                     NULL,
                     &Event
                     );
    if (EFI_ERROR (Status)) {
      EFI_TEST_GENERIC_FAILURE (L"BS.SetTimer - Create event", Status);
      return Status;
    }

    //
    // Set timer with the invalid timer type
    //
    Status = gtBS->SetTimer (
                     Event,
                     InvalidTimerTypes[Index],
                     1
                     );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEventTimerTaskPriorityServicesBBTestSetTimerAssertionGuid008,
                   L"BS.SetTimer - Set timer with invalid timer type.",
                   L"%a:%d:Status - %r, TimerType - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   InvalidTimerTypes[Index]
                   );

    //
    // Close the event
    //
    gtBS->CloseEvent (Event);
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetTimer_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;
  UINTN               Buffer[2];

  //
  // Create an event
  //
  Buffer[0] = 0;  // Max
  Buffer[1] = 0;  // Used
  Status = gtBS->CreateEvent (
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY,
                   NotifyFunction,
                   Buffer,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.SetTimer - Create event", Status);
    return Status;
  }

  //
  // Set timer as relative timer
  //
  Status = gtBS->SetTimer (
                   Event,
                   TimerRelative,
                   10000000           // 1 second
                   );

  gtBS->Stall (3000000);              // 3 seconds

  if ((Status == EFI_SUCCESS) && (Buffer[1] == 1)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestSetTimerAssertionGuid001,
                 L"BS.SetTimer - Set TimerRelative timer.",
                 L"%a:%d:Status - %r, Count - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Buffer[1]
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
BBTestSetTimer_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;
  UINTN               Buffer[2];

  //
  // Create an event
  //
  Buffer[0] = 0;  // Max
  Buffer[1] = 0;  // Used
  Status = gtBS->CreateEvent (
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY,
                   NotifyFunction,
                   Buffer,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.SetTimer - Create event", Status);
    return Status;
  }

  //
  // Set timer as periodic timer
  //
  Status = gtBS->SetTimer (
                   Event,
                   TimerPeriodic,
                   10000000           // 1 second
                   );

  gtBS->Stall (3000000);              // 3 seconds

  if ((Status == EFI_SUCCESS) && (Buffer[1] > 1)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestSetTimerAssertionGuid002,
                 L"BS.SetTimer - Set TimerPeriodic timer.",
                 L"%a:%d:Status - %r, Count - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Buffer[1]
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
BBTestSetTimer_Func_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;
  UINTN               Buffer[2];

  //
  // Create an event
  //
  Buffer[0] = 0;  // Max
  Buffer[1] = 0;  // Used
  Status = gtBS->CreateEvent (
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY,
                   NotifyFunction,
                   Buffer,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.SetTimer - Create event", Status);
    return Status;
  }

  //
  // Set timer as periodic and then cancel it
  //
  Status = gtBS->SetTimer (
                   Event,
                   TimerPeriodic,
                   10000000           // 1 second
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.SetTimer - Set timer", Status);
    return Status;
  }

  Status = gtBS->SetTimer (
                   Event,
                   TimerCancel,
                   0
                   );

  gtBS->Stall (3000000);              // 3 seconds

  if ((Status == EFI_SUCCESS) && (Buffer[1] == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestSetTimerAssertionGuid003,
                 L"BS.SetTimer - Set TimerCancel timer.",
                 L"%a:%d:Status - %r, Count - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Buffer[1]
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
BBTestSetTimer_Func_Sub4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;
  UINTN               Buffer[2];

  //
  // Create an event
  //
  Buffer[0] = 0;  // Max
  Buffer[1] = 0;  // Used
  Status = gtBS->CreateEvent (
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY,
                   NotifyFunction,
                   Buffer,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.SetTimer - Create event", Status);
    return Status;
  }

  //
  // Set timer as periodic and then change it to relative
  //
  Status = gtBS->SetTimer (
                   Event,
                   TimerPeriodic,
                   10000000           // 1 second
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.SetTimer - Set periodic timer", Status);
    return Status;
  }

  Status = gtBS->SetTimer (
                   Event,
                   TimerRelative,
                   5000000            // 0.5 second
                   );

  gtBS->Stall (3000000);              // 3 seconds

  if ((Status == EFI_SUCCESS) && (Buffer[1] == 1)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestSetTimerAssertionGuid010,
                 L"BS.SetTimer - Change timer type.",
                 L"%a:%d:Status - %r, Count - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Buffer[1]
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
BBTestSetTimer_Func_Sub5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;
  UINTN               Buffer[2];

  //
  // Create an event
  //
  Buffer[0] = 0;  // Max
  Buffer[1] = 0;  // Used
  Status = gtBS->CreateEvent (
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY,
                   NotifyFunction,
                   Buffer,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.SetTimer - Create event", Status);
    return Status;
  }

  //
  // Set as a timer event
  //
  Status = gtBS->SetTimer (
                   Event,
                   TimerRelative,
                   0                  // 0 second
                   );

  gtBS->Stall (3000000);              // 3 seconds

  if ((Status == EFI_SUCCESS) && (Buffer[1] == 1)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestSetTimerAssertionGuid009,
                 L"BS.SetTimer - Set with special trigger time.",
                 L"%a:%d:Status - %r, Count - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Buffer[1]
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
BBTestSetTimer_Func_Sub6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS          Status;
  EFI_TEST_ASSERTION  AssertionType;
  EFI_EVENT           Event;
  UINTN               Buffer[2];

  //
  // Create an event
  //
  Buffer[0] = 0;  // Max
  Buffer[1] = 0;  // Used
  Status = gtBS->CreateEvent (
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY,
                   NotifyFunction,
                   Buffer,
                   &Event
                   );
  if (EFI_ERROR (Status)) {
    EFI_TEST_GENERIC_FAILURE (L"BS.SetTimer - Create event", Status);
    return Status;
  }

  //
  // Set timer as periodic timer
  //
  Status = gtBS->SetTimer (
                   Event,
                   TimerPeriodic,
                   0           // the timer event will be signaled on the every timer tick
                   );

  gtBS->Stall (1000000);              // 1 seconds

  if ((Status == EFI_SUCCESS) && (Buffer[1] > 1)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEventTimerTaskPriorityServicesBBTestSetTimerAssertionGuid002,
                 L"BS.SetTimer - Set TimerPeriodic timer.",
                 L"%a:%d:Status - %r, Count - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Buffer[1]
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
