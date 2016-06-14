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
BBTestCheckEvent_Conf_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCheckEvent_Func_Sub1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCheckEvent_Func_Sub2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCheckEvent_Func_Sub3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

EFI_STATUS
BBTestCheckEvent_Func_Sub4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Functions
//

EFI_STATUS
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
