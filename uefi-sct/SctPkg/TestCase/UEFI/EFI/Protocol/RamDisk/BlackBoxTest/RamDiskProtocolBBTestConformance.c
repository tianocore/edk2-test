/** @file

  Copyright 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    RamDiskProtocolBBTestConformance.c

Abstract:
    for EFI RamDisk Protocol's Conformance Test

--*/
#include "RamDiskProtocolBBTestMain.h"


MEDIA_RAM_DISK_DEVICE_PATH  mRamDiskDeviceNodeTemplate = {
  {
    MEDIA_DEVICE_PATH,
    MEDIA_RAM_DISK_DP,
    {
      (UINT8) (sizeof (MEDIA_RAM_DISK_DEVICE_PATH)),
      (UINT8) ((sizeof (MEDIA_RAM_DISK_DEVICE_PATH)) >> 8)
    }
  }
};

STATIC
UINT64
WriteUnaligned64 (
  OUT UINT64                    *Buffer,
  IN  UINT64                    Value
  )
{
  ASSERT (Buffer != NULL);

  return *Buffer = Value;
}

EFI_STATUS
EFIAPI
BBTestRegisterRamDiskConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RAM_DISK_PROTOCOL                 *RamDisk
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  UINT64                                      RamDiskBufferSize;
  VOID                                        *RamDiskBuffer;
  EFI_GUID                                    *RamDiskType;
  EFI_DEVICE_PATH_PROTOCOL                    *DevicePath;

  RamDiskBufferSize = 128;
  RamDiskBuffer = SctAllocateZeroPool ((UINTN) RamDiskBufferSize);
  if( !RamDiskBuffer ) {
    return EFI_OUT_OF_RESOURCES;
  }
  
  RamDiskType = &gBlackBoxEfiVirtualDiskGuid;

  //
  // With RamDiskBufferSize being 0.
  //
  RamDiskBufferSize = 0;
  Status = RamDisk->Register (
             (UINT64) RamDiskBuffer,
             RamDiskBufferSize,
             RamDiskType,
             NULL,
             &DevicePath
             );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegisterRamDiskBBTestConformanceAssertionGuid001,
                 L"EFI_RAM_DISK_PROTOCOL.Register - Register() returns EFI_INVALID_PARAMETER with ZERO RamDiskSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (RamDiskBuffer);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRegisterRamDiskConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RAM_DISK_PROTOCOL                 *RamDisk
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  UINT64                                      RamDiskBufferSize;
  VOID                                        *RamDiskBuffer;
  EFI_GUID                                    *RamDiskType;
  EFI_DEVICE_PATH_PROTOCOL                    *DevicePath;

  RamDiskBufferSize = 128;
  RamDiskBuffer = SctAllocateZeroPool ((UINTN) RamDiskBufferSize);
  if( !RamDiskBuffer ) {
    return EFI_OUT_OF_RESOURCES;
  }
  
  //
  // With RamDiskType being NULL.
  //
  RamDiskType = NULL;
  Status = RamDisk->Register (
             (UINT64) RamDiskBuffer,
             RamDiskBufferSize,
             RamDiskType,
             NULL,
             &DevicePath
             );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegisterRamDiskBBTestConformanceAssertionGuid002,
                 L"EFI_RAM_DISK_PROTOCOL.Register - Register() returns EFI_INVALID_PARAMETER with NULL RamDiskType.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (RamDiskBuffer);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRegisterRamDiskConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RAM_DISK_PROTOCOL                 *RamDisk
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  UINT64                                      RamDiskBufferSize;
  VOID                                        *RamDiskBuffer;
  EFI_GUID                                    *RamDiskType;
  EFI_DEVICE_PATH_PROTOCOL                    **DevicePath;

  RamDiskBufferSize = 128;
  RamDiskBuffer = SctAllocateZeroPool ((UINTN) RamDiskBufferSize);
  if( !RamDiskBuffer ) {
    return EFI_OUT_OF_RESOURCES;
  }

  RamDiskType = &gBlackBoxEfiVirtualCdGuid;
  
  //
  // With DevicePath being NULL.
  //
  DevicePath = NULL;
  Status = RamDisk->Register (
             (UINT64) RamDiskBuffer,
             RamDiskBufferSize,
             RamDiskType,
             NULL,
             DevicePath
             );
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegisterRamDiskBBTestConformanceAssertionGuid003,
                 L"EFI_RAM_DISK_PROTOCOL.Register - Register() returns EFI_INVALID_PARAMETER with NULL DevicePath.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (RamDiskBuffer);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRegisterRamDiskConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RAM_DISK_PROTOCOL                 *RamDisk
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  UINT64                                      RamDiskBufferSize;
  VOID                                        *RamDiskBuffer;
  EFI_GUID                                    *RamDiskType;
  EFI_DEVICE_PATH_PROTOCOL                    *DevicePath;

  RamDiskBufferSize = 128;
  RamDiskBuffer = SctAllocateZeroPool ((UINTN) RamDiskBufferSize);
  if( !RamDiskBuffer ) {
    return EFI_OUT_OF_RESOURCES;
  }
  
  RamDiskType = &gBlackBoxEfiPersistentVirtualDiskGuid;

  //
  // Register a Device Path Protocol instance 
  //
  Status = RamDisk->Register (
             (UINT64) RamDiskBuffer,
             RamDiskBufferSize,
             RamDiskType,
             NULL,
             &DevicePath
             );
  if( EFI_ERROR(Status) ) {
    gtBS->FreePool (RamDiskBuffer);
    return Status;
  }

  //
  // Register the same Device Path Protocol instance again
  //
  Status = RamDisk->Register (
             (UINT64) RamDiskBuffer,
             RamDiskBufferSize,
             RamDiskType,
             NULL,
             &DevicePath
             );
  if (EFI_ALREADY_STARTED == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegisterRamDiskBBTestConformanceAssertionGuid004,
                 L"EFI_RAM_DISK_PROTOCOL.Register - Register() returns EFI_ALREADY_STARTED with the same Device Path Protocol instance.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (RamDiskBuffer);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRegisterRamDiskConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_RAM_DISK_PROTOCOL                 *RamDisk;

  //
  // Init
  //
  RamDisk = (EFI_RAM_DISK_PROTOCOL *) ClientInterface;

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
  
  BBTestRegisterRamDiskConformanceTestCheckpoint1 (StandardLib, RamDisk);

  BBTestRegisterRamDiskConformanceTestCheckpoint2 (StandardLib, RamDisk);
  
  BBTestRegisterRamDiskConformanceTestCheckpoint3 (StandardLib, RamDisk);

  BBTestRegisterRamDiskConformanceTestCheckpoint4 (StandardLib, RamDisk);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterRamDiskConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RAM_DISK_PROTOCOL                 *RamDisk
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  MEDIA_RAM_DISK_DEVICE_PATH                  *RamDiskDevNode;
  UINT64                                      RamDiskBufferSize;
  VOID                                        *RamDiskBuffer;
  UINT64                                      RamDiskBase;
  

  //
  // Generate device path information
  //
  RamDiskDevNode = SctAllocateCopyPool (
                     sizeof (MEDIA_RAM_DISK_DEVICE_PATH), 
                     &mRamDiskDeviceNodeTemplate
                     );
  if (NULL == RamDiskDevNode) {
    return EFI_OUT_OF_RESOURCES;
  }

  RamDiskBufferSize = 128;
  RamDiskBuffer = SctAllocateZeroPool ((UINTN) RamDiskBufferSize);
  if( !RamDiskBuffer ) {
    gtBS->FreePool (RamDiskDevNode);
    return EFI_OUT_OF_RESOURCES;
  }

  RamDiskBase = (UINT64) RamDiskBuffer;

  WriteUnaligned64 (
    (UINT64 *) &(RamDiskDevNode->StartingAddr[0]),
    RamDiskBase
    );
  
  WriteUnaligned64 (
    (UINT64 *) &(RamDiskDevNode->EndingAddr[0]),
    RamDiskBase + RamDiskBufferSize - 1
    );
  
  RamDiskDevNode->TypeGuid = gBlackBoxEfiVirtualDiskGuid;
  
  RamDiskDevNode->Instance = 0;
  
  //
  // Unregister one DevicePath not existed 
  //
  Status = RamDisk->Unregister ((EFI_DEVICE_PATH_PROTOCOL *) RamDiskDevNode);
  if (EFI_NOT_FOUND == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUnregisterRamDiskBBTestConformanceAssertionGuid001,
                 L"EFI_RAM_DISK_PROTOCOL.Unregister - Unregister() returns EFI_NOT_FOUND with DevicePath not existed.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (RamDiskDevNode);
  
  gtBS->FreePool (RamDiskBuffer);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterRamDiskConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RAM_DISK_PROTOCOL                 *RamDisk
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  EFI_DEVICE_PATH_PROTOCOL                    *DevicePath;
 
  //
  // With DevicePath being NULL.
  //
  DevicePath = NULL;
  Status = RamDisk->Unregister (DevicePath);
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUnregisterRamDiskBBTestConformanceAssertionGuid002,
                 L"EFI_RAM_DISK_PROTOCOL.Unregister - Unregister() returns EFI_INVALID_PARAMETER with DevicePath is NULL.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterRamDiskConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_RAM_DISK_PROTOCOL                 *RamDisk
  )
{
  EFI_STATUS                                  Status;
  EFI_TEST_ASSERTION                          AssertionType;
  MEDIA_RAM_DISK_DEVICE_PATH                  *RamDiskDevNode;
  EFI_DEVICE_PATH_PROTOCOL                    *DevicePath;

  //
  // Generate device path information
  //
  RamDiskDevNode = SctAllocateCopyPool (
                     sizeof (MEDIA_RAM_DISK_DEVICE_PATH), 
                     &mRamDiskDeviceNodeTemplate
                     );
  if (NULL == RamDiskDevNode) {
    return EFI_OUT_OF_RESOURCES;
  }
  
  //
  // Unregister an invalid Ramdisk DevicePath 
  //
  RamDiskDevNode->Header.SubType = MEDIA_CDROM_DP;

  DevicePath = SctAppendDevicePathNode (
                 NULL,
                 (EFI_DEVICE_PATH_PROTOCOL *) RamDiskDevNode
                 );
  if (NULL == DevicePath) {
    gtBS->FreePool (RamDiskDevNode);
    return  EFI_OUT_OF_RESOURCES;
  }
  
  Status = RamDisk->Unregister (DevicePath);
  if (EFI_UNSUPPORTED == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUnregisterRamDiskBBTestConformanceAssertionGuid003,
                 L"EFI_RAM_DISK_PROTOCOL.Unregister - Unregister() returns EFI_UNSUPPORTED with an invalid Ramdisk DevicePath.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (RamDiskDevNode);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterRamDiskConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_RAM_DISK_PROTOCOL                 *RamDisk;

  //
  // Init
  //
  RamDisk = (EFI_RAM_DISK_PROTOCOL *) ClientInterface;

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
  
  BBTestUnregisterRamDiskConformanceTestCheckpoint1 (StandardLib, RamDisk);

  BBTestUnregisterRamDiskConformanceTestCheckpoint2 (StandardLib, RamDisk);

  BBTestUnregisterRamDiskConformanceTestCheckpoint3 (StandardLib, RamDisk);
  
  return EFI_SUCCESS;
}

