/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
BBTestSetTimer_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestSetTimer_Conf_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestSetTimer_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestSetTimer_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestSetTimer_Func_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestSetTimer_Func_Sub4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestSetTimer_Func_Sub5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestSetTimer_Func_Sub6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Functions
//

EFI_STATUS
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
