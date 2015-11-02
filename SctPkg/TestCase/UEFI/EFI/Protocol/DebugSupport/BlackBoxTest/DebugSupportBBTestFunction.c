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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  DebugSupportBBTestFunction.c

Abstract:

  Interface Function Test Cases of Debug Support Protocol

--*/


#include "DebugSupportBBTestMain.h"

extern volatile  UINTN InvokedPeriodicCallback;

/**
 *  Entrypoint for EFI_DEBUG_SUPPORT_PROTOCOL.Isa Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.1
//
EFI_STATUS
BBTestIsaFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DEBUG_SUPPORT_PROTOCOL           *DebugSupport;
  EFI_TEST_ASSERTION                   AssertionType;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  DebugSupport = (EFI_DEBUG_SUPPORT_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.1.2.1
  // Isa should be one of IsaIa32, IsaIpf, or IsaEbc.
  //
  if ((DebugSupport->Isa == IsaIa32) ||
      (DebugSupport->Isa == IsaX64)  ||  	
      (DebugSupport->Isa == IsaIpf)  ||
      (DebugSupport->Isa == IsaEbc)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid001,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.Isa - Check the correctness of Isa",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_DEBUG_SUPPORT_PROTOCOL.GetMaximumProcessorIndex() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.2
//
EFI_STATUS
BBTestGetMaximumProcessorIndexFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DEBUG_SUPPORT_PROTOCOL           *DebugSupport;
  EFI_TEST_ASSERTION                   AssertionType;

  UINTN                                MaxProcessorIndex;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  DebugSupport = (EFI_DEBUG_SUPPORT_PROTOCOL *)ClientInterface;

  //
  // Assertion Point 3.2.2.1
  // Invoke GetMaximumProcessorIndex and verify interface correctness.
  //
  Status = DebugSupport->GetMaximumProcessorIndex (DebugSupport, &MaxProcessorIndex);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid002,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.GetMaximumProcessorIndex - Invoke this function and verify interface correctness",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

volatile  UINTN TimerNotifyInvokedSecond;

//
// Prototypes
//
VOID
TimerNotifyFunction1 (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

/**
 *  Entrypoint for EFI_DEBUG_SUPPORT_PROTOCOL.RegisterPeriodicCallback() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.3
//
EFI_STATUS
BBTestRegisterPeriodicCallbackFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_DEBUG_SUPPORT_PROTOCOL           *DebugSupport;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EVENT                            TimeEvent;
  UINTN                                MaxProcessorIndex;
  UINTN                                ProcessorIndex;

  DebugSupport = (EFI_DEBUG_SUPPORT_PROTOCOL *)ClientInterface;

  if (DebugSupport->Isa != PlatformIsa) {
    return EFI_SUCCESS;
  }

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  DebugSupport = (EFI_DEBUG_SUPPORT_PROTOCOL *)ClientInterface;

  Status = DebugSupport->GetMaximumProcessorIndex (DebugSupport, &MaxProcessorIndex);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_DEBUG_SUPPORT_PROTOCOL.GetMaximumProcessorIndex",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  InvokedPeriodicCallback = FALSE;
  for (ProcessorIndex = 0; ProcessorIndex <= MaxProcessorIndex; ProcessorIndex++) {

    //
    // Assertion Point 3.3.2.1
    // Invoke RegisterPeriodicCallback() to install an interrupt handler function.
    //
    Status = DebugSupport->RegisterPeriodicCallback (DebugSupport, ProcessorIndex, PeriodicCallback);

    if ((Status == EFI_SUCCESS) || (Status == EFI_ALREADY_STARTED)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDebugSupportBBTestFunctionAssertionGuid003,
                   L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterPeriodicCallback - Invoke this function and verify interface correctness",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    // If the callback function is already registed, return
    //
    if (EFI_ERROR(Status)) {
      return EFI_SUCCESS;
    }
  }

  //
  // Test the callback function registed.
  //

  //
  // Wait the PeriodicCallback to be invoked.
  //
  gtBS->Stall (500000);
  if (InvokedPeriodicCallback == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid004,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterPeriodicCallback - Verify the callback function was invoked.(Verify 1)",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Assertion Point 3.3.2.2
  // Invoke RegisterPeriodicCallback() to install an interrupt handler function.
  //

  //
  // Create Event for time service
  //
  Status = gtBS->CreateEvent (
                   EVT_TIMER | EVT_NOTIFY_SIGNAL,
                   TPL_CALLBACK,
                   TimerNotifyFunction1,
                   NULL,
                   &TimeEvent
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InvokedPeriodicCallback = FALSE;

  // Start the Timer.
  gtBS->SetTimer (TimeEvent, TimerPeriodic, 1);

  gtBS->Stall (500000);

  if (TimerNotifyInvokedSecond == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid005,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterPeriodicCallback - Verify the callback function was invoked firstly.(Verify 2)",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Close the Timer
  gtBS->SetTimer (TimeEvent, TimerCancel, 1);

  for (ProcessorIndex = 0; ProcessorIndex <= MaxProcessorIndex; ProcessorIndex++) {

    //
    // Assertion Point 3.3.2.3
    // Invoke RegisterPeriodicCallback() to install another interrupt handler function.
    //
    Status = DebugSupport->RegisterPeriodicCallback (DebugSupport, ProcessorIndex, PeriodicCallback1);

    if (Status != EFI_ALREADY_STARTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDebugSupportBBTestFunctionAssertionGuid006,
                   L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterPeriodicCallback - Register another callback function.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  for (ProcessorIndex = 0; ProcessorIndex <= MaxProcessorIndex; ProcessorIndex++) {

    //
    // Assertion Point 3.3.2.4
    // Invoke RegisterPeriodicCallback() to unstall the interrupt handler function.
    //
    Status = DebugSupport->RegisterPeriodicCallback (DebugSupport, ProcessorIndex, NULL);

    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDebugSupportBBTestFunctionAssertionGuid007,
                   L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterPeriodicCallback - Invoke this function to uninstall the interrupt handler function.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  InvokedPeriodicCallback = FALSE;

  //
  // Wait the PeriodicCallback to be invoked.
  //
  gtBS->Stall (500000);

  if (InvokedPeriodicCallback != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDebugSupportBBTestFunctionAssertionGuid008,
                 L"EFI_DEBUG_SUPPORT_PROTOCOL.RegisterPeriodicCallback - Verify the callback function wasn't invoked.(Verify 3)",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->CloseEvent (TimeEvent);

  return EFI_SUCCESS;
}

VOID
TimerNotifyFunction1 (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  if (InvokedPeriodicCallback == TRUE) {
    TimerNotifyInvokedSecond = TRUE;
  } else {
    TimerNotifyInvokedSecond = FALSE;
  }

  return;
}
