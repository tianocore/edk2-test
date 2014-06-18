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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
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
BBTestWaitForEvent_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestWaitForEvent_Conf_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestWaitForEvent_Conf_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestWaitForEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestWaitForEvent_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Functions
//

EFI_STATUS
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
