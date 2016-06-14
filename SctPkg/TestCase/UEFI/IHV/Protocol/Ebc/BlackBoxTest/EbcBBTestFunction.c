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

  EbcBBTestFunction.c

Abstract:

  Basic Test Cases of Ebc Protocol

--*/

#include "EbcBBTestMain.h"

/**
 *  Entrypoint for EFI_EBC_PROTOCOL.CreateThunk() Basic Test.
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
BBTestCreateThunkBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_EBC_PROTOCOL                      *EbcInterface;
  VOID                                  *EbcEntryPoint;
  EFI_IMAGE_ENTRY_POINT                 ThunkEntryPoint;
  VOID                                  *EbcDriverInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_EBC_PROTOCOL Protocol interface to be tested
  //
  EbcInterface = (EFI_EBC_PROTOCOL *)ClientInterface;

  //
  // Register a callback for flushing the instruction cache so that created
  // thunks can be flushed.
  //
  Status = EbcInterface->RegisterICacheFlush (EbcInterface, FlushICache);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_EBC_PROTOCOL.RegisterICacheFlush - Can't register callback function",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // 3.1.2.1 CreateThunk() Basic Functionality
  //

  //
  // Load Ebc Driver
  //
  Status = LoadEbcDriver (&EbcEntryPoint);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"LoadEbcDriver - Can't load Ebc Driver and get the entry point",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    UnloadEbcDriver();
    return Status;
  }

  //
  // Create a thunk for the image's entry point. This will be the new
  // entry point for the image.
  //
  Status = EbcInterface->CreateThunk (
                           EbcInterface,
                           gDummyImageHandle,
                           EbcEntryPoint,
                           (VOID **)&ThunkEntryPoint
                           );
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEbcBBTestFunctionAssertionGuid001,
                 L"EFI_EBC_PROTOCOL.CreateThunk - Call CreateThunk to create ebc thunk",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (Status == EFI_SUCCESS) {
    ThunkEntryPoint (gDummyImageHandle, gtST);

    Status = gtBS->HandleProtocol (
                    gDummyImageHandle,
                    &gBlackBoxEfiEbcDriverProtocolGuid,
                    &EbcDriverInterface
                    );

    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEbcBBTestFunctionAssertionGuid002,
                   L"EFI_EBC_PROTOCOL.CreateThunk - Ebc entry point invoked",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Status = EbcInterface->UnloadImage (EbcInterface, gDummyImageHandle);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"EFI_EBC_PROTOCOL.UnloadImage - Can't unload the ebc thunk",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      UnloadEbcDriver();
      return Status;
    }
  }

  UnloadEbcDriver();

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EBC_PROTOCOL.UnloadImage() Basic Test.
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
BBTestUnloadImageBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_EBC_PROTOCOL                      *EbcInterface;
  VOID                                  *EbcEntryPoint;
  EFI_IMAGE_ENTRY_POINT                 ThunkEntryPoint;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  // Get the EFI_EBC_PROTOCOL Protocol interface to be tested
  //
  EbcInterface = (EFI_EBC_PROTOCOL *)ClientInterface;

  //
  // Register a callback for flushing the instruction cache so that created
  // thunks can be flushed.
  //
  Status = EbcInterface->RegisterICacheFlush (EbcInterface, FlushICache);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_EBC_PROTOCOL.RegisterICacheFlush - Can't register callback function",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Load Ebc Driver
  //
  Status = LoadEbcDriver (&EbcEntryPoint);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"LoadEbcDriver - Can't load Ebc Driver and get the entry point",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    UnloadEbcDriver();
    return Status;
  }

  //
  // Create a thunk for the image's entry point. This will be the new
  // entry point for the image.
  //
  Status = EbcInterface->CreateThunk (
                           EbcInterface,
                           gDummyImageHandle,
                           EbcEntryPoint,
                           (VOID **)&ThunkEntryPoint
                            );
  if (EFI_ERROR(Status == EFI_SUCCESS)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_EBC_PROTOCOL.CreateThunk - Can't create ebc thunk",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    UnloadEbcDriver();
    return Status;
  }

  ThunkEntryPoint (gDummyImageHandle, gtST);

  //
  // 3.2.2.1 UnloadImage() Basic Functionality
  //
  Status = EbcInterface->UnloadImage (EbcInterface, gDummyImageHandle);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEbcBBTestFunctionAssertionGuid003,
                 L"EFI_EBC_PROTOCOL.UnloadImage - Call UnloadImage to unload ebc thunk",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  UnloadEbcDriver();

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EBC_PROTOCOL.RegisterICacheFlush() Basic Test.
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
BBTestRegisterICacheFlushBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_EBC_PROTOCOL                      *EbcInterface;
  VOID                                  *EbcEntryPoint;
  EFI_IMAGE_ENTRY_POINT                 ThunkEntryPoint;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_EBC_PROTOCOL Protocol interface to be tested
  //
  EbcInterface = (EFI_EBC_PROTOCOL *)ClientInterface;

  //
  // 3.3.2.1 RegisterICacheFlush() Basic Functionality
  //

  //
  // Register a callback for flushing the instruction cache so that created
  // thunks can be flushed.
  //
  Status = EbcInterface->RegisterICacheFlush (EbcInterface, TestFlushICache);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEbcBBTestFunctionAssertionGuid004,
                 L"EFI_EBC_PROTOCOL.RegisterICacheFlush - Call RegisterICacheFlush to register ebc callback function",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Load Ebc Driver
  //
  Status = LoadEbcDriver (&EbcEntryPoint);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"LoadEbcDriver - Can't load Ebc Driver and get the entry point",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    UnloadEbcDriver();
    return Status;
  }

  gFlushICache = FALSE;
  //
  // Create a thunk for the image's entry point. This will be the new
  // entry point for the image.
  //
  Status = EbcInterface->CreateThunk (
                           EbcInterface,
                           gDummyImageHandle,
                           EbcEntryPoint,
                           (VOID **)&ThunkEntryPoint
                           );
  if (EFI_ERROR(Status == EFI_SUCCESS)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_EBC_PROTOCOL.CreateThunk - Can't create ebc thunk",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    UnloadEbcDriver();
    return Status;
  }

  if (gFlushICache) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEbcBBTestFunctionAssertionGuid005,
                 L"EFI_EBC_PROTOCOL.RegisterICacheFlush - Callback function should be called after CreateThunk",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  ThunkEntryPoint (gDummyImageHandle, gtST);

  Status = EbcInterface->UnloadImage (EbcInterface, gDummyImageHandle);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_EBC_PROTOCOL.UnloadImage - Can't unload the ebc thunk",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    UnloadEbcDriver();
    return Status;
  }

  UnloadEbcDriver();

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_EBC_PROTOCOL.GetVersion() Basic Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 3.4
//
EFI_STATUS
BBTestGetVersionBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EBC_PROTOCOL                     *EbcInterface;
  UINT64                               Version;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_EBC_PROTOCOL Protocol interface to be tested
  //
  EbcInterface = (EFI_EBC_PROTOCOL *)ClientInterface;

  //
  // 3.4.2.1 GetVersion() Basic Functionality
  //
  Status = EbcInterface->GetVersion (EbcInterface, &Version);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gEbcBBTestFunctionAssertionGuid006,
                 L"EFI_EBC_PROTOCOL.GetVersion - Call GetVersion to get ebc interpreter version",
                 L"%a:%d:Status - %r, Version - 0x%lx",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Version
                 );

  return EFI_SUCCESS;
}
