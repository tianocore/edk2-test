/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2014 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    AdapterInfoBBTestConformance.c

Abstract:
    for EFI Adapter Information Protocol's conformance Test

--*/
#include "AdapterInfoBBTestMain.h"


EFI_STATUS
EFIAPI
BBTestGetInformationConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  
EFI_STATUS
EFIAPI
BBTestGetInformationConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );

EFI_STATUS
EFIAPI
BBTestGetInformationConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  

  
EFI_STATUS
EFIAPI
BBTestSetInformationConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  
EFI_STATUS
EFIAPI
BBTestSetInformationConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );


  
EFI_STATUS
EFIAPI
BBTestGetSupportedTypesConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  
EFI_STATUS
EFIAPI
BBTestGetSupportedTypesConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestGetInformationConformanceTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo;

  //
  // init
  //
  AdapterInfo = (EFI_ADAPTER_INFORMATION_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                     SupportHandle,
                     &gEfiStandardTestLibraryGuid,
                     (VOID **) &StandardLib
                     );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetInformationConformanceTestCheckpoint1( StandardLib, AdapterInfo );
  
  BBTestGetInformationConformanceTestCheckpoint2( StandardLib, AdapterInfo );
  
  BBTestGetInformationConformanceTestCheckpoint3( StandardLib, AdapterInfo );

  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetInformationConformanceTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo;
                                        
  //
  // init
  //
  AdapterInfo = (EFI_ADAPTER_INFORMATION_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                     SupportHandle,
                     &gEfiStandardTestLibraryGuid,
                     (VOID **) &StandardLib
                     );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestSetInformationConformanceTestCheckpoint1( StandardLib, AdapterInfo );
  
  BBTestSetInformationConformanceTestCheckpoint2( StandardLib, AdapterInfo );
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetSupportedTypesConformanceTest (
  IN EFI_BB_TEST_PROTOCOL    *This,
  IN VOID                    *ClientInterface,
  IN EFI_TEST_LEVEL          TestLevel,
  IN EFI_HANDLE              SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo;
                                        
  //
  // init
  //
  AdapterInfo = (EFI_ADAPTER_INFORMATION_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                     SupportHandle,
                     &gEfiStandardTestLibraryGuid,
                     (VOID **) &StandardLib
                     );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }

  //
  //Call check points
  //
  BBTestGetSupportedTypesConformanceTestCheckpoint1( StandardLib, AdapterInfo );
  
  BBTestGetSupportedTypesConformanceTestCheckpoint2( StandardLib, AdapterInfo );
  
  return EFI_SUCCESS;
}


//
//Check Points
//

EFI_STATUS
EFIAPI
BBTestGetInformationConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  )
{ 
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
                        
  VOID                  *InformationBlock;
  UINTN                 InformationBlockSize;
                        
  InformationBlock      = NULL;

  
 

  //
  //Call GetInformation to check 
  //
  Status = AdapterInfo->GetInformation(
                            AdapterInfo,
                            &gEfiUnSupportedGuid,
                            &InformationBlock,
                            &InformationBlockSize
                            );
  
  AssertionType = EFI_TEST_ASSERTION_PASSED;                       
      
  if ( Status != EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAdapterInfoBBTestConformanceAssertionGuid001,
                   L"EFI_ADAPTER_INFORMATION_PROTOCOL.GetInformation - GetInformation() returns EFI_UNSUPPORTED with unknown InformationType.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  
  if ( InformationBlock != NULL ) {
    gtBS->FreePool (InformationBlock);
    InformationBlock = NULL;
  }
     
  return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
BBTestGetInformationConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  )
{
  
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
                        
  UINTN                 InformationBlockSize;
  EFI_GUID              *InfoTypesBuffer;
  EFI_GUID              *InformationType;
  UINTN                 InfoTypesBufferCount;
  UINTN                 Index;
  
  
  InfoTypesBuffer       = NULL;
  
  Status = AdapterInfo->GetSupportedTypes (
                            AdapterInfo,
                            &InfoTypesBuffer,
                            &InfoTypesBufferCount
                            );
  
  if ( EFI_SUCCESS != Status || InfoTypesBuffer == NULL ) {
    if (  InfoTypesBuffer != NULL ){
      gtBS->FreePool ( InfoTypesBuffer );
      InfoTypesBuffer = NULL;
    }

    StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"GetSupportedTypes---Failed",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    return Status;  
  } 
  
  InformationType = InfoTypesBuffer;
  
  for(Index=0; Index < InfoTypesBufferCount; Index++){
     
    //
    //Call GetInformation to check 
    //
    Status = AdapterInfo->GetInformation(
                              AdapterInfo,
                              InformationType,
                              NULL,
                              &InformationBlockSize
                              );
  
    AssertionType = EFI_TEST_ASSERTION_PASSED;                       
      
    if ( Status != EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gAdapterInfoBBTestConformanceAssertionGuid002,
                     L"EFI_ADAPTER_INFORMATION_PROTOCOL.GetInformation - GetInformation() returns EFI_INVALID_PARAMETER with NULL InformationBlock.",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    InformationType++;	
  } 
  
  if(InfoTypesBuffer != NULL){
    gtBS->FreePool(InfoTypesBuffer);
    InfoTypesBuffer = NULL;
  }
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetInformationConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL           *AdapterInfo
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
                        
  EFI_GUID              *InformationType;
  VOID                  *InformationBlock;
  EFI_GUID              *InfoTypesBuffer;
  UINTN                 InfoTypesBufferCount;
  UINTN                 Index;
                        
  InformationBlock      = NULL;
                        
  InfoTypesBuffer       = NULL;
    
  Status = AdapterInfo->GetSupportedTypes (
                            AdapterInfo,
                            &InfoTypesBuffer,
                            &InfoTypesBufferCount
                            );
    
  if ( EFI_SUCCESS != Status || InfoTypesBuffer == NULL ) {
    if (  InfoTypesBuffer != NULL ){
      gtBS->FreePool ( InfoTypesBuffer );
      InfoTypesBuffer = NULL;
    }
  
    StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"GetSupportedTypes---Failed",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    return Status;  
  } 

  InformationType = InfoTypesBuffer;
    
  for( Index = 0; Index < InfoTypesBufferCount; Index++){
     
    //
    //Call GetInformation to check 
    //
    Status = AdapterInfo->GetInformation(
                              AdapterInfo,
                              InformationType,
                              &InformationBlock,
                              NULL
                              );
  
    AssertionType = EFI_TEST_ASSERTION_PASSED;                       
      
    if ( Status != EFI_INVALID_PARAMETER ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gAdapterInfoBBTestConformanceAssertionGuid003,
                     L"EFI_ADAPTER_INFORMATION_PROTOCOL.GetInformation - GetInformation() returns EFI_INVALID_PARAMETER with NULL InformationBlockSize.",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
  
    if ( InformationBlock != NULL ) {
      gtBS->FreePool (InformationBlock);
      InformationBlock = NULL;
    }

    InformationType++;
  } 
  
  if(InfoTypesBuffer != NULL){
    gtBS->FreePool(InfoTypesBuffer);
    InfoTypesBuffer = NULL;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetInformationConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  
  UINT8                 InformationBlockSet;
  UINTN                 InformationBlockSize;
  
  InformationBlockSize  = 0;  
  //
  // Call SetInformation to config an adapter
  //
  Status = AdapterInfo->SetInformation(
                           AdapterInfo,
                           &gEfiUnSupportedGuid,
                           (VOID *)&InformationBlockSet,
                           InformationBlockSize
                           );
    
  if ( Status != EFI_UNSUPPORTED ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
    
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAdapterInfoBBTestConformanceAssertionGuid004,
                   L"EFI_ADAPTER_INFORMATION_PROTOCOL.SetInformation - SetInformation() returns EFI_UNSOPPORTED with unknown InformationType.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  return EFI_SUCCESS;

}

EFI_STATUS
EFIAPI
BBTestSetInformationConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
                        
  UINTN                 InformationBlockSize;
                        
  EFI_GUID              *InfoTypesBuffer;
  EFI_GUID              *InformationType;
  VOID                  *InformationBlock;
  UINTN                 InfoTypesBufferCount;
  UINTN                 Index;
  

  InfoTypesBuffer       = NULL;
  InformationType       = NULL;
  
  Status = AdapterInfo->GetSupportedTypes (
                            AdapterInfo,
                            &InfoTypesBuffer,
                            &InfoTypesBufferCount
                            );
  
  if ( EFI_SUCCESS != Status || InfoTypesBuffer == NULL ) {
    if (  InfoTypesBuffer != NULL ){
      gtBS->FreePool ( InfoTypesBuffer );
      InfoTypesBuffer = NULL;
    }

    StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"GetSupportedTypes---Failed",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    return Status;  
  } 
  
  InformationType = InfoTypesBuffer;
  
  for(Index = 0; Index < InfoTypesBufferCount; Index++){

    Status = AdapterInfo->GetInformation(
                              AdapterInfo,
                              InformationType,
                              &InformationBlock,
                              &InformationBlockSize
                              );

    if (EFI_SUCCESS != Status ) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"GetInformation---Failed",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;       
    }

    //
    // Call SetInformation to config an adapter
    //
    Status =AdapterInfo->SetInformation(
                           AdapterInfo,
                           InformationType,
                           NULL,
                           InformationBlockSize
                           );
      
    if ( Status != EFI_INVALID_PARAMETER && Status != EFI_WRITE_PROTECTED) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gAdapterInfoBBTestConformanceAssertionGuid005,
                     L"EFI_ADAPTER_INFORMATION_PROTOCOL.SetInformation - SetInformation() returns EFI_INVALID_PARAMETER or EFI_WRITE_PROTECTED with NULL InformationBlock.",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    if ( InformationBlock != NULL ){
      gtBS->FreePool (InformationBlock);
      InformationBlock = NULL;
    }

    InformationType++;
  }

  if (InfoTypesBuffer != NULL){
    gtBS->FreePool ( InfoTypesBuffer );
    InfoTypesBuffer = NULL;
  }
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetSupportedTypesConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
                        
  UINTN                 InfoTypesBufferCount;

  //
  // Call GetSupportedTypes with NULL InfoTypesBuffer
  //
  Status = AdapterInfo->GetSupportedTypes(
                            AdapterInfo,
                            NULL,
                            &InfoTypesBufferCount
                            );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gAdapterInfoBBTestConformanceAssertionGuid006,
                   L"ADAPTER_INFORMATION_PROTOCOL.GetSupportedTypes - GetSupportedTypes() returns EFI_INVALID_PARAMETER with NULL InfoTypesBuffer.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  return EFI_SUCCESS;
}




EFI_STATUS
EFIAPI
BBTestGetSupportedTypesConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
                        
  EFI_GUID              *InfoTypesBuffer;


  //
  // Call GetSupportedTypes with NULL InfoTypesBufferCount
  //
  Status = AdapterInfo->GetSupportedTypes(
                            AdapterInfo,
                            &InfoTypesBuffer,
                            NULL
                            );

  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gAdapterInfoBBTestConformanceAssertionGuid007,
                   L"ADAPTER_INFORMATION_PROTOCOL.GetSupportedTypes - GetSupportedTypes() returns EFI_INVALID_PARAMETER with NULL InfoTypesBufferCount.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  return EFI_SUCCESS;
}
