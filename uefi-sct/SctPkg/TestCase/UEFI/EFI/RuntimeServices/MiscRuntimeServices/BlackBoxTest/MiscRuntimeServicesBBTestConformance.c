/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  MiscRuntimeServicesBBTestFunction.c

Abstract:

  Interface Test Cases of Miscellaneous Runtime Services

--*/

#include "SctLib.h"
#include "MiscRuntimeServicesBBTestMain.h"

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)

EFI_STATUS
EFIAPI
BBTestUpdateCapsuleConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                           Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                *AllocatedBuffer;
  EFI_CAPSULE_HEADER                  *CapsuleHeaderArray[2];

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (FALSE == CheckBBTestCanRunAndRecordAssertion (
                  StandardLib, 
                  L"RT.UpdateCapsule_Conf- UpdateCapsule_Conf it's not Supported in EFI",
                  __FILE__,
                  (UINTN)__LINE__
                  )) {
    return EFI_SUCCESS;
  }

  AllocatedBuffer = (UINT8 *)SctAllocatePool (sizeof(EFI_CAPSULE_HEADER));
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"RT.UpdateCapsule_conf - Allocate pages for EFI_CAPSULE_HEADER",
                   L"%a:%d,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  CapsuleHeaderArray[0] = (EFI_CAPSULE_HEADER *) (UINTN)AllocatedBuffer;
  CapsuleHeaderArray[0]->CapsuleGuid = mEfiCapsuleHeaderGuid;
  CapsuleHeaderArray[0]->HeaderSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[0]->CapsuleImageSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[1] = NULL;
  CapsuleHeaderArray[0]->Flags = CAPSULE_FLAGS_PERSIST_ACROSS_RESET;


  // When CapsuleCount is 0, the return status code should be EFI_INVALID_PARAMETER
  Status = gtRT->UpdateCapsule(
  	             CapsuleHeaderArray,
  	             0, // invaild
  	             (EFI_PHYSICAL_ADDRESS ) 0
  	             );
  if (Status == EFI_INVALID_PARAMETER) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestConformanceAssertionGuid001,
                 L"RT.UpdateCapsule - invoke UpdateCapsule with invalid CapsuleCount - 0",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );
                
  //
  // when the flag is CAPSULE_FLAGS_PERSIST_ACROSS_RESET, ScatterGatherList can't be NULL.
  //

  CapsuleHeaderArray[0] = (EFI_CAPSULE_HEADER *) (UINTN)AllocatedBuffer;
  CapsuleHeaderArray[0]->CapsuleGuid = mEfiCapsuleHeaderGuid;
  CapsuleHeaderArray[0]->HeaderSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[0]->CapsuleImageSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[1] = NULL;
  CapsuleHeaderArray[0]->Flags = CAPSULE_FLAGS_PERSIST_ACROSS_RESET | CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE;

  Status = gtRT->UpdateCapsule(
  	             CapsuleHeaderArray,
  	             1,
  	             (EFI_PHYSICAL_ADDRESS ) 0
  	             );
  if (Status == EFI_INVALID_PARAMETER) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestConformanceAssertionGuid002,
                 L"RT.UpdateCapsule - invoke UpdateCapsule with invalid ScatterGatherList",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 __LINE__,
                 Status
                 );


  //
  // A capsule which has the CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE flag must have
  // CAPSULE_FLAGS_PERSIST_ACROSS_RESET set in its header as well.
  //
  CapsuleHeaderArray[0] = (EFI_CAPSULE_HEADER *) (UINTN)AllocatedBuffer;
  CapsuleHeaderArray[0]->CapsuleGuid = mEfiCapsuleHeaderGuid;
  CapsuleHeaderArray[0]->HeaderSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[0]->CapsuleImageSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[1] = NULL;
  CapsuleHeaderArray[0]->Flags = CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE;

  Status = gtRT->UpdateCapsule(
  	             CapsuleHeaderArray,
  	             1,
  	             (EFI_PHYSICAL_ADDRESS ) 0
  	             );
  if (Status == EFI_INVALID_PARAMETER) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestConformanceAssertionGuid003,
                 L"RT.UpdateCapsule - invoke UpdateCapsule with invalid Flags",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // A capsule which has the CAPSULE_FLAGS_INITIATE_RESET Flag must have 
  // CAPSULE_FLAGS_PERSIST_ACROSS_RESET set in its header as well.
  //
  CapsuleHeaderArray[0] = (EFI_CAPSULE_HEADER *) (UINTN)AllocatedBuffer;
  CapsuleHeaderArray[0]->CapsuleGuid = mEfiCapsuleHeaderGuid;
  CapsuleHeaderArray[0]->HeaderSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[0]->CapsuleImageSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[1] = NULL;
  CapsuleHeaderArray[0]->Flags = CAPSULE_FLAGS_INITIATE_RESET;

  Status = gtRT->UpdateCapsule(
  	             CapsuleHeaderArray,
  	             1,
  	             (EFI_PHYSICAL_ADDRESS ) 0
  	             );
  if (Status == EFI_INVALID_PARAMETER) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestConformanceAssertionGuid005,
                 L"RT.UpdateCapsule - invoke UpdateCapsule with invalid Flags",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  SctFreePool (AllocatedBuffer);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestQueryCapsuleCapabilitiesConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                           Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_TEST_ASSERTION                   AssertionType;
  UINT8                                *AllocatedBuffer;
  EFI_CAPSULE_HEADER                  *CapsuleHeaderArray[2];
  EFI_RESET_TYPE                       ResetType;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (FALSE == CheckBBTestCanRunAndRecordAssertion(
                  StandardLib, 
                  L"RT.QueryCapsuleCapabilities_Conf - QueryCapsuleCapabilities_Conf it's not Supported in EFI",
                  __FILE__,
                  (UINTN)__LINE__
                  )) {
    return EFI_SUCCESS;
  }

  AllocatedBuffer = (UINT8 *)SctAllocatePool (sizeof(EFI_CAPSULE_HEADER));
  if (AllocatedBuffer == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"RT.QueryCapsuleCapabilities_Conf - Allocate zero pool for EFI_CAPSULE_HEADER",
                   L"%a:%d,Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  CapsuleHeaderArray[0] = (EFI_CAPSULE_HEADER *) (UINTN)AllocatedBuffer;
  CapsuleHeaderArray[0]->CapsuleGuid = mEfiCapsuleHeaderGuid;
  CapsuleHeaderArray[0]->HeaderSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[0]->CapsuleImageSize = sizeof(EFI_CAPSULE_HEADER);
  CapsuleHeaderArray[1] = NULL;
// When the flag is CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE and CAPSULE_FLAGS_PERSIST_ACROSS_RESET, platform will ignore the CapsuleGuid   
  CapsuleHeaderArray[0]->Flags = CAPSULE_FLAGS_PERSIST_ACROSS_RESET | CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE;

  Status = gtRT->QueryCapsuleCapabilities(
  	               CapsuleHeaderArray, 
  	               1, 
  	               NULL, //invalid
  	               &ResetType);
  if ((Status == EFI_INVALID_PARAMETER) || (Status == EFI_UNSUPPORTED)) {
  	AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gMiscRuntimeServicesBBTestConformanceAssertionGuid004,
                 L"RT.QueryCapsuleCapabilities - invoke QueryCapsuleCapabilities with invalid MaxiumCapsuleSize",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  SctFreePool (AllocatedBuffer);
  return EFI_SUCCESS;
}

#endif
