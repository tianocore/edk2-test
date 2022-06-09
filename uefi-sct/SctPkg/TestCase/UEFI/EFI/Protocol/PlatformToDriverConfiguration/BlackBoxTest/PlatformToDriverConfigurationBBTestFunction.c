/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Byosoft Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  PlatformToDriverConfigurationBBTestFunction.c

Abstract:

  Interface Function Test Cases of PlatformToDriverConfiguration Protocol

--*/


#include "SctLib.h"
#include "PlatformToDriverConfigurationBBTestMain.h"


/**
 *  Entrypoint for EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID.Query Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS
//
EFI_STATUS
EFIAPI
BBTestQueryFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL             *StandardLib;
  EFI_STATUS                                     Status;
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL  *PlatformToDriverConfiguration;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_HANDLE                                         *CtrlerHandles;
  UINTN                                                  CtrlerHandleNo;
  UINTN                                                  CtrlerHandleIndex;
  EFI_HANDLE                                         ChildHandle;
  UINTN                                          *Instance;
  EFI_GUID                                     *ParameterTypeGuid=NULL;
  UINTN                                          *ParameterBlockSize=0;
  EFI_CONFIGURE_CLP_PARAMETER_BLK                                           *ParameterClpBlock;
  
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  PlatformToDriverConfiguration = (EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *)ClientInterface;

  //
  // Assertion Point
  // Invoke Query() of the platform to driver configuration protocol,EFI_NOT_FOUND is expected.
  //

  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &CtrlerHandleNo, &CtrlerHandles);

  *ParameterTypeGuid =gBlackBoxEfiPlatformToDriverConfigurationClpGuid;
  *ParameterBlockSize = sizeof( EFI_CONFIGURE_CLP_PARAMETER_BLK );
  ChildHandle =NULL;
  
  Status = gtBS->AllocatePool (EfiBootServicesData,*ParameterBlockSize,(VOID **)&ParameterClpBlock);
  if(EFI_ERROR(Status)){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool memory for ParameterClpBlock",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  //
  //retrieve the protocol Instance
  //
  Status = gtBS->LocateProtocol (
                         &gBlackBoxEfiPlatformToDriverConfigurationProtocolGuid,
                         NULL,
                         (VOID **) &Instance
                         );
  if( EFI_ERROR(Status) ){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }
  
  //check point
  //Invoke Query(), EFI_NOT_FOUND should be returned while instance not found.
  //
 
  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++) {
    while(!EFI_ERROR(Status)) {
      Status = PlatformToDriverConfiguration->Query (
                                         PlatformToDriverConfiguration,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         &ParameterTypeGuid,
                                         (VOID **) &ParameterClpBlock,
                                         ParameterBlockSize
                                         );
      if(Status == EFI_SUCCESS){
        Status = PlatformToDriverConfiguration->Response (
                                         PlatformToDriverConfiguration,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         ParameterTypeGuid,
                                         &ParameterClpBlock,
                                         *ParameterBlockSize,
                                         EfiPlatformConfigurationActionNone
                                         );			
        Instance++;
      }
    }

    if( Status == EFI_NOT_FOUND ) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPlatformToDriverConfigurationBBTestFunctionAssertionGuid001,
                   L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query() and verify interface correctness",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }

  if (CtrlerHandles) {
    SctFreePool (CtrlerHandles);
  }
  
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID.Response Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS
//
EFI_STATUS
EFIAPI
BBTestResponseFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL             *StandardLib;
  EFI_STATUS                                     Status;
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL  *PlatformToDriverConfiguration;
  EFI_TEST_ASSERTION                             AssertionType;
  EFI_HANDLE                                         *CtrlerHandles;
  UINTN                                                  CtrlerHandleNo;
  UINTN                                                  CtrlerHandleIndex;
  EFI_HANDLE                                         ChildHandle;
  UINTN                                          *Instance=0;
  EFI_GUID                                     *ParameterTypeGuid=NULL;
  UINTN                                          *ParameterBlockSize=0;
  EFI_CONFIGURE_CLP_PARAMETER_BLK                                           *ParameterClpBlock;
  EFI_PLATFORM_CONFIGURATION_ACTION                         ConfigurationAction;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if ( EFI_ERROR(Status) ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  PlatformToDriverConfiguration = (EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *)ClientInterface;

  //
  // Assertion Point
  // Invoke Query() and Response() of the platform to driver configuration protocol,EFI_NOT_FOUND is expected.
  //

  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &CtrlerHandleNo, &CtrlerHandles);

  *ParameterTypeGuid = gBlackBoxEfiPlatformToDriverConfigurationClpGuid;
  *ParameterBlockSize = sizeof( EFI_CONFIGURE_CLP_PARAMETER_BLK );
  ChildHandle =NULL;

  Status = gtBS->AllocatePool (EfiBootServicesData,*ParameterBlockSize,(VOID **)&ParameterClpBlock);
  if(EFI_ERROR(Status)){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool memory for ParameterClpBlock",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  //
  //retrieve the protocol Instance
  //
  Status = gtBS->LocateProtocol (
                         &gBlackBoxEfiPlatformToDriverConfigurationProtocolGuid,
                         NULL,
                         (VOID **) &Instance
                         );
  if( EFI_ERROR(Status) ){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
    return Status;
  }

  //check point
  // invoke query and response, EFI_NOT_FOUND is expected.
  //
  
  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++) {
    while(!EFI_ERROR(Status)) {
      Status = PlatformToDriverConfiguration->Query (
                                         PlatformToDriverConfiguration,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         &ParameterTypeGuid,
                                         (VOID **) &ParameterClpBlock,
                                         ParameterBlockSize
                                         );
	  
      ConfigurationAction = EfiPlatformConfigurationActionNone;
      if(Status == EFI_SUCCESS){
        Status = PlatformToDriverConfiguration->Response (
                                         PlatformToDriverConfiguration,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         ParameterTypeGuid,
                                         &ParameterClpBlock,
                                         *ParameterBlockSize,
                                         ConfigurationAction
                                         );			
        Instance++;
      }
    }

    if ( Status == EFI_NOT_FOUND ) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPlatformToDriverConfigurationBBTestFunctionAssertionGuid002,
                   L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Response - Invoke Response() and verify interface correctness",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   __LINE__,
                   Status
                   );
  }

  if (CtrlerHandles) {
    SctFreePool (CtrlerHandles);
  }

  return EFI_SUCCESS;
}
