/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    AdapterInfoBBTestFunction.c

Abstract:
    for EFI Adapter Information Protocol's function Test

--*/
#include "AdapterInfoBBTestMain.h"




  
EFI_STATUS
EFIAPI
BBTestGetInformationFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo 
  );



EFI_STATUS
EFIAPI
BBTestSetInformationFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );
  

EFI_STATUS
EFIAPI
BBTestGetSupportedTypesFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_ADAPTER_INFORMATION_PROTOCOL      *AdapterInfo
  );                                       


//
//Test Cases
//

EFI_STATUS
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
EFIAPI
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
                              (VOID **) &InformationBlockGet1,
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
                                (VOID **) &InformationBlockGet2,
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
EFIAPI
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
        !GuidCmp (*InfoType, gEfiAdapterInfoUndiIPv6SupportGuid) ||
        !GuidCmp (*InfoType, gEfiAdapterInfoMediaTypeGuid))
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

