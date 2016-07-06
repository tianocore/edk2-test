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
                                                                
  Copyright 2006 - 2015 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2013 - 2015, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
    AdapterInfoBBTestFunction.c

Abstract:
    for EFI Adapter Information Protocol's function Test

--*/
#include "AdapterInfoBBTestMain.h"




  
EFI_STATUS
BBTestGetInformationFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo 
  );



EFI_STATUS
BBTestSetInformationFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  

EFI_STATUS
BBTestGetSupportedTypesFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );                                       


//
//Test Cases
//

EFI_STATUS
BBTestGetInformationFunctionTest (
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
  BBTestGetInformationFunctionTestCheckpoint1( StandardLib, AdapterInfo );

  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestSetInformationFunctionTest (
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
  BBTestSetInformationFunctionTestCheckpoint1( StandardLib, AdapterInfo );
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetSupportedTypesFunctionTest (
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
  BBTestGetSupportedTypesFunctionTestCheckpoint1( StandardLib, AdapterInfo );
  
  return EFI_SUCCESS;
}


//
//Check Points
//

EFI_STATUS
BBTestGetInformationFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
                        
  VOID                  *InformationBlock;
  UINTN                 InformationBlockSize;
  EFI_GUID              *InfoTypesBuffer;
  UINTN                 InfoTypesBufferCount;
  EFI_GUID              *InformationType;
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
  
  for ( Index = 0; Index < InfoTypesBufferCount; ++Index)
  {
    Status = AdapterInfo->GetInformation(
                              AdapterInfo,
                              InformationType,
                              &InformationBlock,
                              &InformationBlockSize
                              );
  
    if ( EFI_SUCCESS == Status && InformationBlock != NULL ) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    
    StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gAdapterInfoBBTestFunctionAssertionGuid001,
                     L"EFI_ADAPTER_INFORMATION_PROTOCOL.GetInformation - GetInformation() returns EFI_SUCCESS.",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    if (InfoTypeAndBlockSizeCmp( *InformationType, InformationBlockSize))
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED;

    StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gAdapterInfoBBTestFunctionAssertionGuid002,
                     L"EFI_ADAPTER_INFORMATION_PROTOCOL.GetInformation - GetInformation() returns correct InformationBlockSize.",
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
  
  if (  InfoTypesBuffer != NULL ){
    gtBS->FreePool ( InfoTypesBuffer );
    InfoTypesBuffer = NULL;
  }
  
  return EFI_SUCCESS;
}



EFI_STATUS
BBTestSetInformationFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
                        
  UINT8                 *InformationBlockGet1;
  UINT8                 *InformationBlockGet2;
  UINTN                 InformationBlockSize1;
  UINTN                 InformationBlockSize2;
  EFI_GUID              *InfoTypesBuffer;
  EFI_GUID              *InfoType;
  UINTN                 InfoTypesBufferCount;
  
  UINTN                 IndexI;
  UINTN                 IndexJ;
  
  InfoTypesBuffer       = NULL;
  InformationBlockGet1  = NULL;
  InformationBlockGet2  = NULL;

  Status = AdapterInfo->GetSupportedTypes (
                            AdapterInfo,
                            &InfoTypesBuffer,
                            &InfoTypesBufferCount
                            );
  
  if ( EFI_SUCCESS != Status || InfoTypesBuffer == NULL ) {
    if ( InfoTypesBuffer != NULL ){
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

  InfoType = InfoTypesBuffer;
  
  for ( IndexI = 0; IndexI < InfoTypesBufferCount; ++IndexI){
    Status = AdapterInfo->GetInformation(
                              AdapterInfo,
                              InfoType,
                              &InformationBlockGet1,
                              &InformationBlockSize1
                              );
    
    if ( EFI_SUCCESS != Status || InformationBlockGet1 == NULL ) {

      if ( InformationBlockGet1 != NULL ) {
        gtBS->FreePool (InformationBlockGet1);
        InformationBlockGet1 = NULL;
      }

      if (  InfoTypesBuffer != NULL ){
        gtBS->FreePool ( InfoTypesBuffer );
        InfoTypesBuffer = NULL;
      }

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
                             InfoType,
                             InformationBlockGet1,
                             InformationBlockSize1
                             );

    if (Status == EFI_SUCCESS || Status ==  EFI_WRITE_PROTECTED)
      AssertionType = EFI_TEST_ASSERTION_PASSED;  
    else
      AssertionType = EFI_TEST_ASSERTION_FAILED; 
    
    StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gAdapterInfoBBTestFunctionAssertionGuid003,
                     L"EFI_ADAPTER_INFORMATION_PROTOCOL.SetInformation - SetInformation() returns EFI_SUCCESS or EFI_WRITE_PROTECTED with valid InformationType.",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    if (AssertionType == EFI_TEST_ASSERTION_FAILED ){
      if ( InformationBlockGet1 != NULL ) {
        gtBS->FreePool (InformationBlockGet1);
        InformationBlockGet1 = NULL;
      }

      if (  InfoTypesBuffer != NULL ){
        gtBS->FreePool ( InfoTypesBuffer );
        InfoTypesBuffer = NULL;
      }
      return Status;
    }
 
    //
    //Call GetInformation to check 
    //
    if (Status == EFI_SUCCESS){
      Status = AdapterInfo->GetInformation(
                                AdapterInfo,
                                InfoType,
                                &InformationBlockGet2,
                                &InformationBlockSize2
                                );
      
      AssertionType = EFI_TEST_ASSERTION_PASSED;                       
      
      if ( Status != EFI_SUCCESS || InformationBlockGet2 == NULL ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else if(InformationBlockSize1 != InformationBlockSize2) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
         for (IndexJ = 0; IndexJ < InformationBlockSize1; ++IndexJ){
            if (InformationBlockGet1[IndexJ] != InformationBlockGet2[IndexJ]){
              AssertionType = EFI_TEST_ASSERTION_FAILED;
              break;
            }
         }
      }
      
      StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gAdapterInfoBBTestFunctionAssertionGuid004,
                       L"EFI_ADAPTER_INFORMATION_PROTOCOL.SetInformation - SetInformation() returns EFI_SUCCESS and check with valid InformationType.",
                       L"%a:%d: Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
      
      if ( InformationBlockGet1 != NULL ) {
        gtBS->FreePool (InformationBlockGet1);
        InformationBlockGet1 = NULL;
      }
    
      if ( InformationBlockGet2 != NULL ) {
        gtBS->FreePool (InformationBlockGet2);
        InformationBlockGet2 = NULL;
      }
    }  

    InfoType++;
  }
  
  if (  InfoTypesBuffer != NULL ){
    gtBS->FreePool ( InfoTypesBuffer );
    InfoTypesBuffer = NULL;
  }
  
  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetSupportedTypesFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  )
{
  EFI_STATUS              Status;
  EFI_TEST_ASSERTION      AssertionType;
                          
  EFI_GUID                *InfoTypesBuffer;
  EFI_GUID                *InfoType;
  UINTN                   InfoTypesBufferCount;
  UINT8                   Index;
                          
  InfoTypesBuffer         = NULL;
  InfoType                = NULL;
  InfoTypesBufferCount    = 0;

  //
  // Call GetSupportedTypes to config a priority
  //
  Status = AdapterInfo->GetSupportedTypes(
                            AdapterInfo,
                            &InfoTypesBuffer,
                            &InfoTypesBufferCount
                            );
  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  
  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAdapterInfoBBTestFunctionAssertionGuid005,
                   L"EFI_ADAPTER_INFORMATION_PROTOCOL.GetSupportedTypes - GetSupportedTypes() returns EFI_SUCCESS.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  InfoType = InfoTypesBuffer;
  
  for ( Index = 0; Index < InfoTypesBufferCount; Index++){
    
    if (!GuidCmp (*InfoType, gEfiAdapterInfoMediaStateGuid) || 
        !GuidCmp (*InfoType, gEfiAdapterInfoNetworkBootGuid)  || 
        !GuidCmp (*InfoType, gEfiAdapterInfoSanMacAddressGuid) ||
        !GuidCmp (*InfoType, gEfiAdapterInfoUndiIPv6SupportGuid))
        AssertionType = EFI_TEST_ASSERTION_PASSED;
    else
        AssertionType = EFI_TEST_ASSERTION_WARNING;

    InfoType++;
  }

  StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gAdapterInfoBBTestFunctionAssertionGuid006,
                   L"EFI_ADAPTER_INFORMATION_PROTOCOL.GetSupportedTypes - GetSupportedTypes() returns valid InfoTypes.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );  

  if(InfoTypesBuffer != NULL){
    gtBS->FreePool(InfoTypesBuffer);
    InfoTypesBuffer = NULL;
  }
  return EFI_SUCCESS;
}

