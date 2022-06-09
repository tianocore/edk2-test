/** @file

  Copyright 2016 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    RamDiskProtocolBBTestFunction.c

Abstract:
    for EFI Driver RamDisk Protocol's function Test

--*/
#include "RamDiskProtocolBBTestMain.h"

EFI_STATUS
EFIAPI
BBTestRegisterRamDiskFunctionTestCheckpoint1 (
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
  // Register a Device Path Protocol instance 
  //
  Status = RamDisk->Register (
             (UINT64)(UINTN)RamDiskBuffer,
             RamDiskBufferSize,
             RamDiskType,
             NULL,
             &DevicePath
             );
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gRegisterRamDiskBBTestFunctionAssertionGuid001,
                 L"EFI_RAM_DISK_PROTOCOL.Register - Register() returns EFI_SUCCESS valid parameters.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (EFI_SUCCESS == Status) { 
    //
    // Unregister DevicePath 
    //
    Status = RamDisk->Unregister (DevicePath);
    if( EFI_ERROR(Status) ) {
      gtBS->FreePool (RamDiskBuffer);
      return Status;
    }
  }
  
  gtBS->FreePool (RamDiskBuffer);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRegisterRamDiskFunctionTest (
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
   
  BBTestRegisterRamDiskFunctionTestCheckpoint1 (StandardLib, RamDisk);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterRamDiskFunctionTestCheckpoint1 (
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
  
  RamDiskType = &gBlackBoxEfiPersistentVirtualCdGuid;

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
  // Unregister DevicePath 
  //
  Status = RamDisk->Unregister (DevicePath);
  if (EFI_SUCCESS == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUnregisterRamDiskBBTestFunctionAssertionGuid001,
                 L"EFI_RAM_DISK_PROTOCOL.Unregister - Unregister() returns EFI_SUCCESS with valid parameters.",
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
BBTestUnregisterRamDiskFunctionTest (
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
  
  BBTestUnregisterRamDiskFunctionTestCheckpoint1 (StandardLib, RamDisk);
  
  return EFI_SUCCESS;
}
