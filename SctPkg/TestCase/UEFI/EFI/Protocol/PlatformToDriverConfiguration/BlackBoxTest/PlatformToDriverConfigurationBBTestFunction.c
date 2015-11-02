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
                                                                
  Copyright (c) 2010 - 2012, Byosoft Corporation. All rights reserved.<BR>   
   
--*/
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
                   &StandardLib
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
                                         &ParameterClpBlock,
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
                   &StandardLib
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
                                         &ParameterClpBlock,
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
