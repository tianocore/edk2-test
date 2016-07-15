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
                                                                
  Copyright 2006 - 2016 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2014 - 2016, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    AdapterInfoBBTestConformance.c

Abstract:
    for EFI Adapter Information Protocol's conformance Test

--*/
#include "AdapterInfoBBTestMain.h"


EFI_STATUS
BBTestGetInformationConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  
EFI_STATUS
BBTestGetInformationConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );

EFI_STATUS
BBTestGetInformationConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  

  
EFI_STATUS
BBTestSetInformationConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  
EFI_STATUS
BBTestSetInformationConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );


  
EFI_STATUS
BBTestGetSupportedTypesConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  
EFI_STATUS
BBTestGetSupportedTypesConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  
  
//
//Test Cases
//
EFI_STATUS
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
