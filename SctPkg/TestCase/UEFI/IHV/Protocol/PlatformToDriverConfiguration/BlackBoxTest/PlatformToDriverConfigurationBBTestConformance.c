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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2014, Byosoft Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  PlatformToDriverConfigurationBBTestConformance.c

Abstract:

  Conformance Test Cases of Platform To Driver Configuration Protocol

--*/


#include "SctLib.h"
#include "PlatformToDriverConfigurationBBTestMain.h"

/**
 *  Entrypoint for EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID.Query Conformance Test.
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
BBTestQueryConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_STATUS                             Status;
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL  *PlatformToDriverConfiguration;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_HANDLE                                         *CtrlerHandles;
  UINTN                                                  CtrlerHandleNo;
  UINTN                                                  CtrlerHandleIndex;
  //EFI_HANDLE                                         ChildHandle;
  UINTN                                          *Instance;
  EFI_GUID                                     *ParameterTypeGuid;
  UINTN                                          *ParameterClpBlockSize=NULL;
  EFI_CONFIGURE_CLP_PARAMETER_BLK                                           *ParameterClpBlock;

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
                   __LINE__,
                   Status
                   );
    return Status;
  }

  PlatformToDriverConfiguration = (EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *)ClientInterface;
  
  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &CtrlerHandleNo, &CtrlerHandles);
  
  ParameterTypeGuid = &gBlackBoxEfiPlatformToDriverConfigurationClpGuid;
  *ParameterClpBlockSize = sizeof( EFI_CONFIGURE_CLP_PARAMETER_BLK );

  Status = gtBS->AllocatePool (EfiBootServicesData,*ParameterClpBlockSize,(VOID **)&ParameterClpBlock);
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
                         &Instance
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
  
  //Assertion Point
 
  //check point 1
  // EFI_INVALID_PARAMETER returned with ContrllerHandle invalid
  //
  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++) {
    Status = PlatformToDriverConfiguration->Query (
                                         PlatformToDriverConfiguration,
                                         NULL,
                                         NULL,
                                         Instance,
                                         &ParameterTypeGuid,
                                         &ParameterClpBlock,
                                         ParameterClpBlockSize
                                         );
    if(Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
       AssertionType = EFI_TEST_ASSERTION_FAILED;
       }

    StandardLib->RecordAssertion (
             StandardLib,
             AssertionType,
             gPlatformToDriverConfigurationBBTestConformanceAssertionGuid001,
             L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query() with invalid controller handle",
             L"%a:%d:Status - %r",
             __FILE__,
             __LINE__,
             Status
             );
  }
  /*
  // check point 2
  // EFI_DEVICE_ERROR returned with ParameterClpBlock invalid
  //
  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++){

   Status = PlatformToDriverConfiguration->Query (
                                         PlatformToDriverConfiguration,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         NULL,
                                         Instance,
                                         &ParameterTypeGuid,
                                         NULL,
                                         ParameterClpBlockSize
                                         );
  if(Status == EFI_DEVICE_ERROR) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
       AssertionType = EFI_TEST_ASSERTION_FAILED;
       }

  StandardLib->RecordAssertion (
             StandardLib,
             AssertionType,
             gPlatformToDriverConfigurationBBTestConformanceAssertionGuid002,
             L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query() with invalid ParameterBlock",
             L"%a:%d:Status - %r",
             __FILE__,
             __LINE__,
             Status
             );
  }

  //check point 3
  // EFI_OUT_OF_RESOURCES returned with ParameterClpBlockSize is NULL
  //
  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++){

   Status = PlatformToDriverConfiguration->Query (
                                         PlatformToDriverConfiguration,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         NULL,
                                         Instance,
                                         &ParameterTypeGuid,
                                         &ParameterClpBlock,
                                         NULL
                                         );
  if(Status == EFI_OUT_OF_RESOURCES) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
       AssertionType = EFI_TEST_ASSERTION_FAILED;
       }

  StandardLib->RecordAssertion (
             StandardLib,
             AssertionType,
             gPlatformToDriverConfigurationBBTestConformanceAssertionGuid003,
             L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query() with invalid ParameterBlockSize",
             L"%a:%d:Status - %r",
             __FILE__,
             __LINE__,
             Status
             );
  }
*/
  
  //
  // Check Point 4
  // Invoke Query() with invalide Instance=NULL
  // EFI_INVALID_PARAMETER is expected
  //

  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++) {

   Status = PlatformToDriverConfiguration->Query (
                                         PlatformToDriverConfiguration,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         NULL,
                                         NULL,
                                         &ParameterTypeGuid,
                                         &ParameterClpBlock,
                                         ParameterClpBlockSize
                                         );
  if(Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
       AssertionType = EFI_TEST_ASSERTION_FAILED;
       }

  StandardLib->RecordAssertion (
             StandardLib,
             AssertionType,
             gPlatformToDriverConfigurationBBTestConformanceAssertionGuid004,
             L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query() with invalid Instance",
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
 *  Entrypoint for EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID.Response Conformance Test.
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
BBTestResponseConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_STATUS                             Status;
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL  *PlatformToDriverConfiguration;
  EFI_TEST_ASSERTION                     AssertionType,RAssertionType;
  EFI_HANDLE                                         *CtrlerHandles;
  UINTN                                                  CtrlerHandleNo;
  UINTN                                                  CtrlerHandleIndex;
 // EFI_HANDLE                                         ChildHandle;
  UINTN                                          *Instance;
  EFI_GUID                                     *ParameterTypeGuid;
  UINTN                                          *ParameterClpBlockSize=NULL;
  EFI_CONFIGURE_CLP_PARAMETER_BLK                                           *ParameterClpBlock;
  EFI_PLATFORM_CONFIGURATION_ACTION                         ConfigurationAction;

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
                   __LINE__,
                   Status
                   );
    return Status;
  }

  PlatformToDriverConfiguration = (EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *)ClientInterface;

  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &CtrlerHandleNo, &CtrlerHandles);
  
  ParameterTypeGuid = &gBlackBoxEfiPlatformToDriverConfigurationClpGuid;
  *ParameterClpBlockSize = sizeof( EFI_CONFIGURE_CLP_PARAMETER_BLK );
  
  Status = gtBS->AllocatePool (EfiBootServicesData,*ParameterClpBlockSize,(VOID **)&ParameterClpBlock);
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
                         &Instance
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
 // Assertion Point
 
  //check point 1
  //invalide controller handle and ChildHandle is NULL
  //return EFI_INVALID_PARAMETER
  //
  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++) {
    Status = PlatformToDriverConfiguration->Query (
                                         PlatformToDriverConfiguration,
                                         NULL,
                                         NULL,
                                         Instance,
                                         &ParameterTypeGuid,
                                         &ParameterClpBlock,
                                         ParameterClpBlockSize
                                         );
    if(Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
         AssertionType = EFI_TEST_ASSERTION_FAILED;
         }

    StandardLib->RecordAssertion (
             StandardLib,
             AssertionType,
             gPlatformToDriverConfigurationBBTestConformanceAssertionGuid005,
             L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query() with invalid controller handle",
             L"%a:%d:Status - %r",
             __FILE__,
             __LINE__,
             Status
             );
    ConfigurationAction = EfiPlatformConfigurationActionNone;
    Status = PlatformToDriverConfiguration->Response(
                                         PlatformToDriverConfiguration,
                                         NULL,
                                         NULL,
                                         Instance,
                                         ParameterTypeGuid,
                                         ParameterClpBlock,
                                         *ParameterClpBlockSize,
                                         ConfigurationAction
                                         );
    if(Status == EFI_INVALID_PARAMETER) {
      RAssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
         RAssertionType = EFI_TEST_ASSERTION_FAILED;
         }

    StandardLib->RecordAssertion (
             StandardLib,
             RAssertionType,
             gPlatformToDriverConfigurationBBTestConformanceAssertionGuid006,
             L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Response - Invoke Response() with invalid controller handle",
             L"%a:%d:Status - %r",
             __FILE__,
             __LINE__,
             Status
             );
  }
/*
  //
  // Check Point 2
  // Invoke Response() with Instance=0 
  //

  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++) {
    Status = PlatformToDriverConfiguration->Query (
                                         PlatformToDriverConfiguration,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         NULL,
                                         NULL,
                                         &ParameterTypeGuid,
                                         &ParameterClpBlock,
                                         ParameterClpBlockSize
                                         );
    if(Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
         AssertionType = EFI_TEST_ASSERTION_FAILED;
         }

    StandardLib->RecordAssertion (
             StandardLib,
             AssertionType,
             gPlatformToDriverConfigurationBBTestConformanceAssertionGuid007,
             L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query() with invalid instance",
             L"%a:%d:Status - %r",
             __FILE__,
             __LINE__,
             Status
             );
  
    ConfigurationAction = EfiPlatformConfigurationActionNone;
    Status = PlatformToDriverConfiguration->Response(
                                         PlatformToDriverConfiguration,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         NULL,
                                         0,
                                         ParameterTypeGuid,
                                         ParameterClpBlock,
                                         *ParameterClpBlockSize,
                                         ConfigurationAction
                                         );
    if(Status == EFI_INVALID_PARAMETER) {
      RAssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
         RAssertionType = EFI_TEST_ASSERTION_FAILED;
         }
	  
    StandardLib->RecordAssertion (
             StandardLib,
             RAssertionType,
             gPlatformToDriverConfigurationBBTestConformanceAssertionGuid008,
             L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Response - Invoke Response() with instance value is zero",
             L"%a:%d:Status - %r",
             __FILE__,
             __LINE__,
             Status
             );
  }
*/
  if (CtrlerHandles) {
    SctFreePool (CtrlerHandles);
  }

  return EFI_SUCCESS;
}
