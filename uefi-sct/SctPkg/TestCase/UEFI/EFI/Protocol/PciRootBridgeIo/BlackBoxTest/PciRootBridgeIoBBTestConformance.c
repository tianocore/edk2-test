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

  PciRootBridgeIoBBTestConformance.c

Abstract:

  conformance test case source file for Pci Root Bridge Io Protocol Interface.

--*/


#include "SctLib.h"
#include "PciRootBridgeIoBBTestMain.h"
#include "PciRootBridgeIoBBTestSupport.h"

#define SECTION_NAME_MEMREAD_CONFORM_TEST   L"MemRead_Conf"
#define SECTION_NAME_MEMWRITE_CONFORM_TEST  L"MemWrite_Conf"
#define SECTION_NAME_IOREAD_CONFORM_TEST    L"IoRead_Conf"
#define SECTION_NAME_IOWRITE_CONFORM_TEST   L"IoWrite_Conf"
#define SECTION_NAME_PCIREAD_CONFORM_TEST   L"PciRead_Conf"
#define SECTION_NAME_PCIWRITE_CONFORM_TEST  L"PciWrite_Conf"
#define SECTION_NAME_COPYMEM_CONFORM_TEST   L"CopyMem_Conf"

STATIC CONST UINT64       mAllAttributes[14] = {
    EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO,
    EFI_PCI_ATTRIBUTE_ISA_IO,
    EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO,
    EFI_PCI_ATTRIBUTE_VGA_MEMORY,
    EFI_PCI_ATTRIBUTE_VGA_IO,
    EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO,
    EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO,
    EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE,
    EFI_PCI_ATTRIBUTE_MEMORY_CACHED,
    EFI_PCI_ATTRIBUTE_MEMORY_DISABLE,
    EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE,
    EFI_PCI_ATTRIBUTE_ISA_IO_16,
    EFI_PCI_ATTRIBUTE_VGA_IO_16,
    EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO_16
  };

/**
 *  Entrypoint for PollMem() conformance automatic test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.1
//
EFI_STATUS
EFIAPI
PollMem_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                                   Status;
  EFI_STATUS                                   EfiStatus;
  UINT64                                       Address;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  UINT64                                       Mask;
  UINT64                                       TargetValue;
  VOID                                         *Result;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH        BridgeIoWidth;

  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  InitializeCaseEnvironment ();

  //
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //set valid value.
  //

  Address = 0;

  Status = GetValidMemoryAddress (RBDev, &Address);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem() - the root bridge has no valid memory range",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Mask         = 0xFF;
  TargetValue  = 0x01;

  Result = SctAllocatePool (32);

  //
  //Call PollMem with Width as EfiPciWidthMaximum.
  //
  BridgeIoWidth = EfiPciWidthMaximum;

  Status = RootBridgeIo->PollMem (
                           RootBridgeIo,
                           BridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
                           5 * 10000000,
                           Result
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid001,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem() - With Width as EfiPciWidthMaximum the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[BridgeIoWidth]
                 );
  //
  //Call PollMem with Width as EfiPciWidthFifoUintX.
  //
  EfiStatus = EFI_INVALID_PARAMETER;

  for (BridgeIoWidth = EfiPciWidthFifoUint8; BridgeIoWidth <= EfiPciWidthFifoUint64; BridgeIoWidth++) {

    Status = RootBridgeIo->PollMem (
                             RootBridgeIo,
                             BridgeIoWidth,
                             Address,
                             Mask,
                             TargetValue & Mask,
                             5 * 10000000,
                             Result
                             );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
    }

    //
    //record message.
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem -with invalid Width return status should be EFI_INVALID_PARAMETER.\n"
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[BridgeIoWidth]
                   );


  }

  if (EfiStatus == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid002,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem() - With Width as EfiPciWidthFifoUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //Call PollMem with Width as EfiPciWidthFillUintX.
  //
  EfiStatus = EFI_INVALID_PARAMETER;

  for (BridgeIoWidth = EfiPciWidthFillUint8; BridgeIoWidth <= EfiPciWidthFillUint64; BridgeIoWidth++) {

    Status = RootBridgeIo->PollMem (
                             RootBridgeIo,
                             BridgeIoWidth,
                             Address,
                             Mask,
                             TargetValue & Mask,
                             5 * 10000000,
                             Result
                             );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
    }

    //
    //record message.
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem -with invalid Width return status should be EFI_INVALID_PARAMETER.\n"
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[BridgeIoWidth]
                   );


  }

  if (EfiStatus == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid003,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem() - With Width as EfiPciWidthFillUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //Call PollMem with Width as -1.
  //
  BridgeIoWidth = -1;
  Status = RootBridgeIo->PollMem (
                           RootBridgeIo,
                           BridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
                           5 * 10000000,
                           Result
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid004,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem() - With Width as -1 the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 BridgeIoWidth
                 );

  //
  //call PollMem with Result as NULL.
  //
  BridgeIoWidth = EfiPciWidthUint32;

  Status = RootBridgeIo->PollMem (
                           RootBridgeIo,
                           BridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
                           5 * 10000000,
                           NULL
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid005,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollMem() - With Result as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[BridgeIoWidth]
                 );
  //
  //done successfully
  //
  SctFreePool (Result);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PollIo() conformance automatic test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.2
//
EFI_STATUS
EFIAPI
PollIo_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                                   Status;
  EFI_STATUS                                   EfiStatus;
  UINT64                                       Address;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  UINT64                                       Mask;
  UINT64                                       TargetValue;
  VOID                                         *Result;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH        BridgeIoWidth;

  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  InitializeCaseEnvironment ();

  //
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //set valid value.
  //

  Address = RBDev->IOBase;

  if (RBDev->IOLength == 0) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo() - the root bridge has no valid Io range",
                   L"%a:%d: the root bridge has no valid Io range",
                   __FILE__,
                   (UINTN)__LINE__
                   );
  return Status;
  }

  Mask         = 0xFF;
  TargetValue  = 0x01;

  Result = SctAllocatePool (32);
  //
  //Call PollIo with Width as EfiPciWidthMaximum.
  //
  BridgeIoWidth = EfiPciWidthMaximum;

  Status = RootBridgeIo->PollIo (
                           RootBridgeIo,
                           BridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
                           5 * 10000000,
                           Result
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid006,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo() - With Width as EfiPciWidthMaximum the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[BridgeIoWidth]
                 );
  //
  //Call PollIo with Width as EfiPciWidthFifoUintX.
  //
  EfiStatus = EFI_INVALID_PARAMETER;

  for (BridgeIoWidth = EfiPciWidthFifoUint8; BridgeIoWidth <= EfiPciWidthFifoUint64; BridgeIoWidth++) {

    Status = RootBridgeIo->PollIo (
                             RootBridgeIo,
                             BridgeIoWidth,
                             Address,
                             Mask,
                             TargetValue & Mask,
                             5 * 10000000,
                             Result
                             );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
    }

    //
    //record message.
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo -with invalid Width return status should be EFI_INVALID_PARAMETER.\n"
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[BridgeIoWidth]
                   );


  }

  if (EfiStatus == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid007,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo() - With Width as EfiPciWidthFifoUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //Call PollIo with Width as EfiPciWidthFillUintX.
  //
  EfiStatus = EFI_INVALID_PARAMETER;

  for (BridgeIoWidth = EfiPciWidthFillUint8; BridgeIoWidth <= EfiPciWidthFillUint64; BridgeIoWidth++) {

    Status = RootBridgeIo->PollIo (
                             RootBridgeIo,
                             BridgeIoWidth,
                             Address,
                             Mask,
                             TargetValue & Mask,
                             5 * 10000000,
                             Result
                             );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
    }

    //
    //record message.
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo -with invalid Width return status should be EFI_INVALID_PARAMETER.\n"
                   L"%a:%d:Status - %r,Width -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[BridgeIoWidth]
                   );


  }

  if (EfiStatus == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid008,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo() - With Width as EfiPciWidthFillUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //Call PollIo with Width as -1.
  //
  BridgeIoWidth = -1;
  Status = RootBridgeIo->PollIo (
                           RootBridgeIo,
                           BridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
                           5 * 10000000,
                           Result
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid009,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo() - With Width as -1 the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 BridgeIoWidth
                 );

  //
  //call PollIo with Result as NULL.
  //
  BridgeIoWidth = EfiPciWidthUint32;

  Status = RootBridgeIo->PollIo (
                           RootBridgeIo,
                           BridgeIoWidth,
                           Address,
                           Mask,
                           TargetValue & Mask,
                           5 * 10000000,
                           NULL
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid010,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.PollIo() - With Result as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[BridgeIoWidth]
                 );
  //
  //done successfully
  //
  SctFreePool (Result);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for MemRead() conformance automatic test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.3
//
EFI_STATUS
EFIAPI
MemRead_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                                   Status;
  UINT64                                       Address;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL           *ProfileLib;
  VOID                                         *DataBuffer;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH        RootBridgeIoWidth;
  UINTN                                        Index;
  UINTN                                        MaxOrder;
  EFI_INI_FILE_HANDLE                          FileHandle;
  CHAR16                                       *FilePath;
  CHAR16                                       *PciDevicePathStr;
  CHAR16                                       *TempDevicePathStr;


  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //set valid value.
  //

  Address    = 0;
  Status = GetValidMemoryAddress (RBDev, &Address);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read() - the root bridge has no valid memory range",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  DataBuffer = SctAllocatePool (32);
  //
  //Call Mem.Read with Width as EfiPciWidthMaximum.
  //
  RootBridgeIoWidth = EfiPciWidthMaximum;
  Status = RootBridgeIo->Mem.Read (
                           RootBridgeIo,
                           RootBridgeIoWidth,
                           Address,
                           1,
                           DataBuffer
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid011,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read() - With Width as EfiPciWidthMaximum the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );

  //
  //Call Mem.Read with Width as -1.
  //
  RootBridgeIoWidth = -1;
  Status = RootBridgeIo->Mem.Read (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               DataBuffer
                               );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid012,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read() - With Width as -1 the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%d,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 RootBridgeIoWidth,
                 Address
                 );

  //
  //call Mem.Read with buffer as NULL.
  //

  RootBridgeIoWidth = EfiPciWidthUint8;
  Status = RootBridgeIo->Mem.Read (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               NULL
                               );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid013,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read() - With Result as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );


  //
  //based on the Profile to test the unsupported width.
  //

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
     SctFreePool (DataBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //open the profile.
  //
  Status = ProfileLib->EfiIniOpen (
                         ProfileLib,
                         gDevicePath,
                         FilePath,
                         &FileHandle
                         );

  //
  //free the file path not to be used.
  //
  gtBS->FreePool (FilePath);

  if (EFI_ERROR(Status)) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_MEMREAD_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    SctFreePool (DataBuffer);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_CONFORM_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //
    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for width.
    //
    RootBridgeIoWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_CONFORM_TEST,
               Index,
               &RootBridgeIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Mem.Read with the appointed width.
    //

    Status = RootBridgeIo->Mem.Read (
                                 RootBridgeIo,
                                 RootBridgeIoWidth,
                                 Address,
                                 1,
                                 DataBuffer
                                 );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid014,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Read() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[RootBridgeIoWidth],
                   Address
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  SctFreePool (DataBuffer);
  //
  //done successfully
  //
  return EFI_SUCCESS;
}
/**
 *  Entrypoint for Mem.Write() conformance automatic test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.4
//
EFI_STATUS
EFIAPI
MemWrite_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                                   Status;
  UINT64                                       Address;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL           *ProfileLib;
  VOID                                         *DataBuffer;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH        RootBridgeIoWidth;
  UINTN                                        Index;
  UINTN                                        MaxOrder;
  EFI_INI_FILE_HANDLE                          FileHandle;
  CHAR16                                       *FilePath;
  CHAR16                                       *PciDevicePathStr;
  CHAR16                                       *TempDevicePathStr;


  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //set valid value.
  //

  Address    = 0;
  Status = GetValidMemoryAddress (RBDev, &Address);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write() - the root bridge has no valid memory range",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  DataBuffer = SctAllocatePool (32);
  //
  //Call Mem.Write with Width as EfiPciWidthMaximum.
  //
  RootBridgeIoWidth = EfiPciWidthMaximum;
  Status = RootBridgeIo->Mem.Write (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               DataBuffer
                               );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid015,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write() - With Width as EfiPciWidthMaximum the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );

  //
  //Call Mem.Write with Width as -1.
  //
  RootBridgeIoWidth = -1;
  Status = RootBridgeIo->Mem.Write (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               DataBuffer
                               );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid016,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write() - With Width as -1 the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%d,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 RootBridgeIoWidth,
                 Address
                 );

  //
  //call Mem.Write with buffer as NULL.
  //

  RootBridgeIoWidth = EfiPciWidthUint8;
  Status = RootBridgeIo->Mem.Write (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               NULL
                               );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid017,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write() - With Result as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );

  //
  //based on the Profile to test the unsupported width.
  //

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    SctFreePool (DataBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //open the profile.
  //
  Status = ProfileLib->EfiIniOpen (
                         ProfileLib,
                         gDevicePath,
                         FilePath,
                         &FileHandle
                         );

  //
  //free the file path not to be used.
  //
  gtBS->FreePool (FilePath);

  if (EFI_ERROR(Status)) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_MEMWRITE_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_CONFORM_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //
    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for width.
    //
    RootBridgeIoWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_CONFORM_TEST,
               Index,
               &RootBridgeIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Mem.Write with the appointed width.
    //

    Status = RootBridgeIo->Mem.Write (
                                 RootBridgeIo,
                                 RootBridgeIoWidth,
                                 Address,
                                 1,
                                 DataBuffer
                                 );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid018,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Mem.Write() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[RootBridgeIoWidth],
                   Address
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );
  SctFreePool (DataBuffer);
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Io.Read() conformance automatic test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.5
//
EFI_STATUS
EFIAPI
IoRead_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                                   Status;
  UINT64                                       Address;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL           *ProfileLib;
  VOID                                         *DataBuffer;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH        RootBridgeIoWidth;
  UINTN                                        Index;
  UINTN                                        MaxOrder;
  EFI_INI_FILE_HANDLE                          FileHandle;
  CHAR16                                       *FilePath;
  CHAR16                                       *PciDevicePathStr;
  CHAR16                                       *TempDevicePathStr;


  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //set valid value.
  //

  Address = RBDev->IOBase;

  if (RBDev->IOLength == 0) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read() - the root bridge has no valid Io range",
                   L"%a:%d: the root bridge has no valid Io range",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  DataBuffer = SctAllocatePool (32);
  //
  //Call Io.Read with Width as EfiPciWidthMaximum.
  //
  RootBridgeIoWidth = EfiPciWidthMaximum;
  Status = RootBridgeIo->Io.Read (
                              RootBridgeIo,
                              RootBridgeIoWidth,
                              Address,
                              1,
                              DataBuffer
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid019,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read() - With Width as EfiPciWidthMaximum the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );

  //
  //Call Io.Read with Width as -1.
  //
  RootBridgeIoWidth = -1;
  Status = RootBridgeIo->Io.Read (
                              RootBridgeIo,
                              RootBridgeIoWidth,
                              Address,
                              1,
                              DataBuffer
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid020,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read() - With Width as -1 the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%d, Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 RootBridgeIoWidth,
                 Address
                 );

  //
  //call Io.Read with buffer as NULL.
  //

  RootBridgeIoWidth = EfiPciWidthUint8;
  Status = RootBridgeIo->Io.Read (
                              RootBridgeIo,
                              RootBridgeIoWidth,
                              Address,
                              1,
                              NULL
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid021,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read() - With Result as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );

  //
  //based on the Profile to test the unsupported width.
  //

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    SctFreePool (DataBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //open the profile.
  //
  Status = ProfileLib->EfiIniOpen (
                         ProfileLib,
                         gDevicePath,
                         FilePath,
                         &FileHandle
                         );

  //
  //free the file path not to be used.
  //
  gtBS->FreePool (FilePath);

  if (EFI_ERROR(Status)) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_IOREAD_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_IOREAD_CONFORM_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //
    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for width.
    //
    RootBridgeIoWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOREAD_CONFORM_TEST,
               Index,
               &RootBridgeIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Io.Read with the appointed width.
    //

    Status = RootBridgeIo->Io.Read (
                                RootBridgeIo,
                                RootBridgeIoWidth,
                                Address,
                                1,
                                DataBuffer
                                );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid022,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[RootBridgeIoWidth],
                   Address
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  SctFreePool (DataBuffer);
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Io.Write() conformance automatic test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.6
//
EFI_STATUS
EFIAPI
IoWrite_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                                   Status;
  UINT64                                       Address;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL           *ProfileLib;
  VOID                                         *DataBuffer;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH        RootBridgeIoWidth;
  UINTN                                        Index;
  UINTN                                        MaxOrder;
  EFI_INI_FILE_HANDLE                          FileHandle;
  CHAR16                                       *FilePath;
  CHAR16                                       *PciDevicePathStr;
  CHAR16                                       *TempDevicePathStr;


  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //set valid value.
  //

  Address = RBDev->IOBase;

  if (RBDev->IOLength == 0) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Read() - the root bridge has no valid Io range",
                   L"%a:%d:the root bridge has no valid Io range",
                   __FILE__,
                   (UINTN)__LINE__
                   );
  return Status;
  }
  DataBuffer = SctAllocatePool (32);
  //
  //Call Io.Write with Width as EfiPciWidthMaximum.
  //
  RootBridgeIoWidth = EfiPciWidthMaximum;
  Status = RootBridgeIo->Io.Write (
                              RootBridgeIo,
                              RootBridgeIoWidth,
                              Address,
                              1,
                              DataBuffer
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid023,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write() - With Width as EfiPciWidthMaximum the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );

  //
  //Call Io.Write with Width as -1.
  //
  RootBridgeIoWidth = -1;
  Status = RootBridgeIo->Io.Write (
                              RootBridgeIo,
                              RootBridgeIoWidth,
                              Address,
                              1,
                              DataBuffer
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid024,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write() - With Width as -1 the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%d,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 RootBridgeIoWidth,
                 Address
                 );

  //
  //call Io.Write with buffer as NULL.
  //

  RootBridgeIoWidth = EfiPciWidthUint8;
  Status = RootBridgeIo->Io.Write (
                              RootBridgeIo,
                              RootBridgeIoWidth,
                              Address,
                              1,
                              NULL
                              );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid025,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write() - With Result as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );

  //
  //based on the Profile to test the unsupported width.
  //

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    SctFreePool (DataBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //open the profile.
  //
  Status = ProfileLib->EfiIniOpen (
                         ProfileLib,
                         gDevicePath,
                         FilePath,
                         &FileHandle
                         );

  //
  //free the file path not to be used.
  //
  gtBS->FreePool (FilePath);

  if (EFI_ERROR(Status)) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_IOWRITE_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_CONFORM_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //
    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for width.
    //
    RootBridgeIoWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_CONFORM_TEST,
               Index,
               &RootBridgeIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Io.Write with the appointed width.
    //

    Status = RootBridgeIo->Io.Write (
                                RootBridgeIo,
                                RootBridgeIoWidth,
                                Address,
                                1,
                                DataBuffer
                                );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid026,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Io.Write() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[RootBridgeIoWidth],
                   Address
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  SctFreePool (DataBuffer);
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Pci.Read() conformance automatic test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.7
//
EFI_STATUS
EFIAPI
PciRead_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                                   Status;
  UINT64                                       Address;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL           *ProfileLib;
  VOID                                         *DataBuffer;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH        RootBridgeIoWidth;
  UINTN                                        Index;
  UINTN                                        MaxOrder;
  EFI_INI_FILE_HANDLE                          FileHandle;
  CHAR16                                       *FilePath;
  CHAR16                                       *PciDevicePathStr;
  CHAR16                                       *TempDevicePathStr;

  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //set valid value.
  //

  Address = SctLShiftU64 (RBDev->PriBus, 24);
  DataBuffer = SctAllocatePool (32);
  //
  //Call Pci.Read with Width as EfiPciWidthMaximum.
  //
  RootBridgeIoWidth = EfiPciWidthMaximum;
  Status = RootBridgeIo->Pci.Read (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               DataBuffer
                               );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid027,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read() - With Width as EfiPciWidthMaximum the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );

  //
  //Call Pci.Read with Width as -1.
  //
  RootBridgeIoWidth = -1;
  Status = RootBridgeIo->Pci.Read (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               DataBuffer
                               );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid028,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read() - With Width as -1 the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%d,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 RootBridgeIoWidth,
                 Address
                 );


  //
  //call Pci.Read with buffer as NULL.
  //
  RootBridgeIoWidth = EfiPciWidthUint8;
  Status = RootBridgeIo->Pci.Read (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               NULL
                               );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid029,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read() - With Result as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );

  //
  //based on the Profile to test the unsupported width.
  //

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    SctFreePool (DataBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //open the profile.
  //

  Status =ProfileLib->EfiIniOpen (
                        ProfileLib,
                        gDevicePath,
                        FilePath,
                        &FileHandle
                        );

  //
  //free the file path not to be used.
  //

  gtBS->FreePool (FilePath);

  if (EFI_ERROR(Status)) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_PCIREAD_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_CONFORM_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //

    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for width.
    //

    RootBridgeIoWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_CONFORM_TEST,
               Index,
               &RootBridgeIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Pci.Read with the appointed width.
    //

    Status = RootBridgeIo->Pci.Read (
                                 RootBridgeIo,
                                 RootBridgeIoWidth,
                                 Address,
                                 1,
                                 DataBuffer
                                 );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid030,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Read() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[RootBridgeIoWidth],
                   Address
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  SctFreePool (DataBuffer);
  //
  //done successfully
  //
  return EFI_SUCCESS;
}
/**
 *  Entrypoint for Pci.Write() conformance automatic test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.8
//
EFI_STATUS
EFIAPI
PciWrite_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                                   Status;
  UINT64                                       Address;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL           *ProfileLib;
  VOID                                         *DataBuffer;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH        RootBridgeIoWidth;
  UINTN                                        Index;
  UINTN                                        MaxOrder;
  EFI_INI_FILE_HANDLE                          FileHandle;
  CHAR16                                       *FilePath;
  CHAR16                                       *PciDevicePathStr;
  CHAR16                                       *TempDevicePathStr;

  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //set valid value.
  //

  Address = SctLShiftU64 (RBDev->PriBus, 24);
  DataBuffer = SctAllocatePool (32);

  //
  //Call Pci.Write with Width as EfiPciWidthMaximum.
  //
  RootBridgeIoWidth = EfiPciWidthMaximum;
  Status = RootBridgeIo->Pci.Write (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               DataBuffer
                               );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid031,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write() - With Width as EfiPciWidthMaximum the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );

  //
  //Call Pci.Write with Width as -1.
  //
  RootBridgeIoWidth = -1;
  Status = RootBridgeIo->Pci.Write (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               DataBuffer
                               );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid032,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write() - With Width as -1 the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%d,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 RootBridgeIoWidth,
                 Address
                 );


  //
  //call Pci.Write with buffer as NULL.
  //
  RootBridgeIoWidth = EfiPciWidthUint8;
  Status = RootBridgeIo->Pci.Write (
                               RootBridgeIo,
                               RootBridgeIoWidth,
                               Address,
                               1,
                               NULL
                               );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid033,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write() - With Result as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address
                 );

  //
  //based on the Profile to test the unsupported width.
  //

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    SctFreePool (DataBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //open the profile.
  //

  Status =ProfileLib->EfiIniOpen (
                        ProfileLib,
                        gDevicePath,
                        FilePath,
                        &FileHandle
                        );

  //
  //free the file path not to be used.
  //

  gtBS->FreePool (FilePath);

  if (EFI_ERROR(Status)) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_PCIWRITE_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    SctFreePool (DataBuffer);
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_CONFORM_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //

    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for width.
    //

    RootBridgeIoWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_CONFORM_TEST,
               Index,
               &RootBridgeIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Pci.Write with the appointed width.
    //

    Status = RootBridgeIo->Pci.Write (
                                 RootBridgeIo,
                                 RootBridgeIoWidth,
                                 Address,
                                 1,
                                 DataBuffer
                                 );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid034,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Pci.Write() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r,Width -%s,Address -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[RootBridgeIoWidth],
                   Address
                   );

  }

  SctFreePool (DataBuffer);
  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for CopyMem() conformance automatic test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.9
//
EFI_STATUS
EFIAPI
CopyMem_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                                   Status;
  EFI_STATUS                                   EfiStatus;
  UINT64                                       Address;
  UINT64                                       DstAddress;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL           *ProfileLib;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE                *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH        RootBridgeIoWidth;
  UINTN                                        Index;
  UINTN                                        MaxOrder;
  EFI_INI_FILE_HANDLE                          FileHandle;
  CHAR16                                       *FilePath;
  CHAR16                                       *PciDevicePathStr;
  CHAR16                                       *TempDevicePathStr;


  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //set valid value.
  //

  Address    = 0;
  Status = GetValidMemoryAddress (RBDev, &Address);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem() - the root bridge has no valid memory range",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  DstAddress = Address + 16;

  //
  //Call CopyMem with Width as EfiPciWidthMaximum.
  //
  RootBridgeIoWidth = EfiPciWidthMaximum;
  Status = RootBridgeIo->CopyMem (
                           RootBridgeIo,
                           RootBridgeIoWidth,
                           DstAddress,
                           Address,
                           1
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid035,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem() - With Width as EfiPciWidthMaximum the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%s,Src Address -%LXh,Dst Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 WidthCode[RootBridgeIoWidth],
                 Address,
                 DstAddress
                 );

  //
  //Call CopyMem with Width as -1.
  //
  RootBridgeIoWidth = -1;
  Status = RootBridgeIo->CopyMem (
                           RootBridgeIo,
                           RootBridgeIoWidth,
                           DstAddress,
                           Address,
                           1
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid036,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem() - With Width as -1 the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Width -%d,Src Address -%LXh,Dst Address -%LXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 RootBridgeIoWidth,
                 Address,
                 DstAddress
                 );

  //
  //Call CopyMem with Width as EfiPciWidthFifoUintX.
  //
  EfiStatus = EFI_INVALID_PARAMETER;

  for (RootBridgeIoWidth = EfiPciWidthFifoUint8; RootBridgeIoWidth <= EfiPciWidthFifoUint64; RootBridgeIoWidth++) {

    Status = RootBridgeIo->CopyMem (
                             RootBridgeIo,
                             RootBridgeIoWidth,
                             DstAddress,
                             Address,
                             1
                             );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
    }

    //
    //record message.
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem -with invalid Width return status should be EFI_INVALID_PARAMETER.\n"
                   L"%a:%d:Status - %r,Width -%s,Src Address -%LXh,Dst Address-%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[RootBridgeIoWidth],
                   Address,
                   DstAddress
                   );


  }

  if (EfiStatus == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid037,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem() - With Width as EfiPciWidthFifoUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //Call CopyMem with Width as EfiPciWidthFillUintX.
  //
  EfiStatus = EFI_INVALID_PARAMETER;

  for (RootBridgeIoWidth = EfiPciWidthFillUint8; RootBridgeIoWidth <= EfiPciWidthFillUint64; RootBridgeIoWidth++) {

    Status = RootBridgeIo->CopyMem (
                             RootBridgeIo,
                             RootBridgeIoWidth,
                             DstAddress,
                             Address,
                             1
                             );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
    }

    //
    //record message.
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem -with invalid Width return status should be EFI_INVALID_PARAMETER.\n"
                   L"%a:%d:Status - %r,Width -%s,Src Address -%LXh,Dst Address-%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[RootBridgeIoWidth],
                   Address,
                   DstAddress
                   );


  }

  if (EfiStatus == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid038,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem() - With Width as EfiPciWidthFillUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //based on the Profile to test the unsupported width.
  //

  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (RBDev->DevicePath);

  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_ROOT_BRIDGE_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    gtBS->FreePool (PciDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //open the profile.
  //

  Status =ProfileLib->EfiIniOpen (
                        ProfileLib,
                        gDevicePath,
                        FilePath,
                        &FileHandle
                        );

  //
  //free the file path not to be used.
  //

  gtBS->FreePool (FilePath);

  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_COPYMEM_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_CONFORM_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //

    if (SctStriCmp (PciDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for width.
    //

    RootBridgeIoWidth = 0;
    Status = GetRootBridgeIoWidthByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_CONFORM_TEST,
               Index,
               &RootBridgeIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call CopyMem with the appointed width.
    //
    Status = RootBridgeIo->CopyMem (
                             RootBridgeIo,
                             RootBridgeIoWidth,
                             DstAddress,
                             Address,
                             1
                             );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid039,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.CopyMem() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r,Width -%s,Src Address -%LXh,Dst Address -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[RootBridgeIoWidth],
                   Address,
                   DstAddress
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Map() conformance automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.10
//
EFI_STATUS
EFIAPI
Map_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{

  EFI_STATUS                                   Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL              *RootBridgeIo;
  VOID                                         *HostAddress;
  UINTN                                        NumberOfBytes;
  EFI_PHYSICAL_ADDRESS                         DeviceAddress;
  VOID                                         *Mapping;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION    Operation;
  UINT8                                        *Buffer;
  UINTN                                        BufferSize;
  EFI_TEST_ASSERTION                           AssertionType;

  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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


  InitializeCaseEnvironment ();

  //
  //check point 4.2.10.2.1 call Map() wih Invalid parameters.
  //

  //
  //allocate a buffer (4K Bytes)
  //

  BufferSize = 4 * 1024;
  Buffer = NULL;
  Buffer = (UINT8 *)SctAllocatePool (BufferSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  HostAddress   = (VOID *)Buffer;

  //
  //call Map with invalid Operation: EfiPciOperationMaximum.
  //

  Operation     = EfiPciOperationMaximum;
  NumberOfBytes = BufferSize;

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid040,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih invalid Operation the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Operation - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //call Map with  invalid Operation: -1.
  //
  Operation  = -1;
  NumberOfBytes = BufferSize;
  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid041,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih invalid Operation the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r,Operation - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //set valid Operation.
  //
  Operation = EfiPciOperationBusMasterRead;

  //
  //call Map with HostAddress As NULL.
  //
  NumberOfBytes = BufferSize;

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           NULL,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid042,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih HostAddress as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );
  //
  //call Map with NumberOfBytes As NULL.
  //

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           NULL,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           &Mapping
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid043,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih NumberOfBytes as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  //call Map with DeviceAddress As NULL.
  //

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           NULL,
                           &Mapping
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid044,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih DeviceAddress as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );
  //
  //call Map with Mapping As NULL.
  //

  Status = RootBridgeIo->Map (
                           RootBridgeIo,
                           Operation,
                           HostAddress,
                           &NumberOfBytes,
                           (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                           NULL
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid045,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.Map - Map wih Mapping as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r,Operation -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Operation
                 );

  //
  // This 4GB should not be a limitation to IPF and EM64T IA32
  //

  //
  //at last free the buffer.
  //

  gtBS->FreePool (Buffer);

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for Unmap() conformance automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.11
//


/**
 *  Entrypoint for AllocateBuffer() conformance automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.11
//
EFI_STATUS
EFIAPI
AllocateBuffer_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_STATUS                            EfiStatus;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  VOID                                  *HostAddress;
  UINT64                                ThisAttribute;
  UINTN                                 Index;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 InvalidMemoryTypeNum;
  UINTN                                 AttributesNum;

  UINT64 ValidAllocateBufferAttributes = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE|
                                         EFI_PCI_ATTRIBUTE_MEMORY_CACHED|
                                         EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE;



  EFI_MEMORY_TYPE InvalidMemoryType[14] = {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiRuntimeServicesCode,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiMaxMemoryType,
    -1
  };

  //
  //get tested interface.
  //
  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  InitializeCaseEnvironment ();

  //
  //call allocate buffer with invalid memory types -1.
  //

  Status = RootBridgeIo->AllocateBuffer (
                           RootBridgeIo,
                           0,
                           InvalidMemoryType[13],
                           1,
                           (VOID **) &HostAddress,
                           0
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid051,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - with Invalid memory type -1 the status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r memory type - %xh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 InvalidMemoryType[13]
                 );

  InvalidMemoryTypeNum = 13;

  EfiStatus = EFI_INVALID_PARAMETER;
  for (Index = 0; Index < InvalidMemoryTypeNum; Index++) {

    Status = RootBridgeIo->AllocateBuffer (
                             RootBridgeIo,
                             0,
                             InvalidMemoryType[Index],
                             1,
                             (VOID **) &HostAddress,
                             0
                             );

    //
    //recod message
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer -with invalid Memory Type return status should be EFI_INVALID_PARAMETER.\n"
                   L"%a:%d:Status - %r,MemoryType -%s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   MemoryTypeCode[(InvalidMemoryType[Index])]
                   );
    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
    }
  }

  if (EfiStatus == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
   AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid052,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - with Invalid memory type status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call allocatebuffer with HostAddress as NULL.
  //

  Status = RootBridgeIo->AllocateBuffer (
                           RootBridgeIo,
                           0,
                           EfiBootServicesData,
                           1,
                           (VOID **) NULL,
                           0
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid053,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - with HostAddress as NULL the status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //call AllocateBuffer with Attributes Having bits other then
  // EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE and EFI_PCI_ATTRIBUTE_MEMORY_CACHED
  //EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE set the return status must be
  //EFI_UNSUPPORTED.
  //

  AttributesNum = 14;
  EfiStatus = EFI_UNSUPPORTED;

  for (Index = 0; Index < AttributesNum; Index++) {
    ThisAttribute = mAllAttributes[Index];

    if ((ThisAttribute & ValidAllocateBufferAttributes) == ThisAttribute) {
      continue;
    }

    Status = RootBridgeIo->AllocateBuffer (
                             RootBridgeIo,
                             0,
                             EfiBootServicesData,
                             1,
                             (VOID **) &HostAddress,
                             ThisAttribute
                             );
    //
    //recod message
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer -with invalid Attribute return status should be EFI_UNSUPPORTED.\n"
                   L"%a:%d:Status - %r,Attribute -%lXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute
                   );

    if (Status != EFI_UNSUPPORTED) {
      EfiStatus = Status;
    }
  }


  if (EfiStatus == EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid054,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - with invalid Attributes the status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //done successfully.
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for FreeBuffer() conformance automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.12
//


/**
 *  Entrypoint for GetAttributes() Conformance
 *  automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.14
//
EFI_STATUS
EFIAPI
GetAttributes_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;

  //
  //get tested interface.
  //

  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  InitializeCaseEnvironment ();


  //
  //call GetAttributes With both Attributes and Supports as NULL
  //return Status must be EFI_INVALID_PARAMETER.
  //

  Status = RootBridgeIo->GetAttributes (
                           RootBridgeIo,
                           NULL,
                           NULL
                           );

  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciRootBridgeIoBBTestConformanceAssertionGuid058,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.GetAttributes - with both Supprts and Atttributes as NULL the return status must be EFI_INVALID_PARAMETER.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for SetAttributes() Conformance
 *  automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.13
//
EFI_STATUS
EFIAPI
SetAttributes_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE         *RBDev;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT64                                SupportedAttributes;
  UINT64                                CommonAttributes;
  UINT64                                CurrentAttributes;
  UINT64                                ThisAttribute;
  UINTN                                 Index;
  UINT64                                ResourceBase;
  UINT64                                ResourceLength;
  UINTN                                 AttributesNumber;
  BOOLEAN                               FoundAttribute;

  UINT64 RequireResourceAttributes = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE |
                                     EFI_PCI_ATTRIBUTE_MEMORY_CACHED |
                                     EFI_PCI_ATTRIBUTE_MEMORY_DISABLE;

  //
  //get tested interface.
  //

  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

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

  InitializeCaseEnvironment ();

  //
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }


  //
  //call GetAttributes to get supported attributes.
  //

  Status = RootBridgeIo->GetAttributes (
                           RootBridgeIo,
                           &SupportedAttributes,
                           &CommonAttributes
                           );

  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.GetAttributes - Get Supported attributes return Status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //check point 4.2.15.2.1 call SetAttributes with Invalid Parameter.
  //

  //
  //Call SetAttributes with unsupported atttibutes that not need resource.
  //

  AttributesNumber = 14;
  FoundAttribute = FALSE;
  ThisAttribute = 0;
  for (Index = 0; Index < AttributesNumber; Index++) {
    ThisAttribute = mAllAttributes[Index];
    if ((ThisAttribute & SupportedAttributes) == 0) {
      if (ThisAttribute & RequireResourceAttributes) {
        continue;
      } else {
         FoundAttribute = TRUE;
         break;
      }
    }
  }

  if (FoundAttribute) {
    //
    //first get current attributes
    //
    RootBridgeIo->GetAttributes (
                    RootBridgeIo,
                    NULL,
                    &CurrentAttributes
                    );

    //
    //call SetAttributes with unspported attributes.
    //
    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             NULL,
                             NULL
                             );

    if (Status == EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid059,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - with unsupported attributes the return status must be EFI_UNSUPPORTED.",
                   L"%a:%d:Status - %r,Set Attributes - %LXh,Supported Attribute -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute,
                   SupportedAttributes
                   );
    //
    //call GetAttribute to verify the Attributes not been set.
    //
    RootBridgeIo->GetAttributes (
                    RootBridgeIo,
                    NULL,
                    &CommonAttributes
                    );

    if (CommonAttributes == CurrentAttributes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - Set Unsupported Attributes the attributes should remain unchanged.",
                   L"%a:%d:Attributes before Set -%LXh,Set Attributes -%LXh,Current Attributes -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   CurrentAttributes,
                   ThisAttribute,
                   CommonAttributes
                   );
  }

  //
  //Call SetAttributes with unsupported atttibutes that need resource.
  //

  //
  //first get some valid memory resource controlled by this Root Bridge.
  //
  Status = GetSomeMemeryResource (
             RBDev,
             &ResourceBase,
             &ResourceLength
             );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes-not found valid memory resource.\n"
                   L"%a:%d.\n",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return EFI_SUCCESS;
  }

  AttributesNumber = 14;
  FoundAttribute = FALSE;
  ThisAttribute = 0;
  for (Index = 0; Index < AttributesNumber; Index++) {
    ThisAttribute = mAllAttributes[Index];
    if ((ThisAttribute & SupportedAttributes) == 0) {
      if (ThisAttribute & RequireResourceAttributes) {
        FoundAttribute = TRUE;
        break;
      } else {
        continue;
      }
    }
  }

  if (FoundAttribute) {
    //
    //first get current attributes
    //
    RootBridgeIo->GetAttributes (
                    RootBridgeIo,
                    NULL,
                    &CurrentAttributes
                    );

    //
    //call SetAttributes with unspported attributes that need resource.
    //
    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             &ResourceBase,
                             &ResourceLength
                             );

    if (Status == EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid060,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - with unsupported attributes the return status must be EFI_UNSUPPORTED.",
                   L"%a:%d:Status - %r,Set Attributes - %LXh,Supported Attribute -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute,
                   SupportedAttributes
                   );
    //
    //call GetAttribute to verify the Attributes not been set.
    //
    RootBridgeIo->GetAttributes (
                    RootBridgeIo,
                    NULL,
                    &CommonAttributes
                    );

    if (CommonAttributes == CurrentAttributes) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - Set Unsupported Attributes the attributes should remain unchanged.",
                   L"%a:%d:Attributes before Set -%LXh,Set Attributes -%LXh,Current Attributes -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   CurrentAttributes,
                   ThisAttribute,
                   CommonAttributes
                   );
  }

  //
  //call SetAttributes with multiple attributes that need a resource.
  //
  AttributesNumber = 0;
  ThisAttribute = 0;

  if (EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE & SupportedAttributes) {
    ThisAttribute |= EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE;
    AttributesNumber++;
  }

  if (EFI_PCI_ATTRIBUTE_MEMORY_CACHED & SupportedAttributes) {
     ThisAttribute |= EFI_PCI_ATTRIBUTE_MEMORY_CACHED;
    AttributesNumber++;
  }

  if (EFI_PCI_ATTRIBUTE_MEMORY_DISABLE & SupportedAttributes) {
     ThisAttribute |= EFI_PCI_ATTRIBUTE_MEMORY_DISABLE;
    AttributesNumber++;
  }

  if (AttributesNumber > 1) {
    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             &ResourceBase,
                             &ResourceLength
                             );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid061,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - with more than one attributes that need a resource the return status must be EFI_INVALID_PARAMETER.",
                   L"%a:%d:Status - %r,Set Attributes - %LXh,Require Resource Attributes -%LXh,Supported Attribute -%LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute,
                   RequireResourceAttributes,
                   SupportedAttributes
                   );
  }


  //
  //if MEMORY_WRITE_COMBINE,MEMORY_CACHED,MEMORY_DISABLE
  //were supported by root bridge call SetAttrbutes with ResourceBase or
  //ResourceLength as NULL.
  //

  ThisAttribute = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE;
  if ((ThisAttribute & SupportedAttributes) == ThisAttribute) {

    //
    //call SetAttributes with ResourceBase as NULL.
    //
    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             NULL,
                             &ResourceLength
                             );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid062,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - MEMORY_WRITE_COMBINE with ResourceBase as NULL the return status must be EFI_INVALID_PARAMETER.",
                   L"%a:%d:Status - %r:Set Attributes - %LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute
                   );

    //
    //call SetAttributes with ResourceLength as NULL.
    //

    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             &ResourceBase,
                             NULL
                             );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid063,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - MEMORY_WRITE_COMBINE with ResourceLength as NULL the return status must be EFI_INVALID_PARAMETER.",
                   L"%a:%d:Status - %r:Set Attributes - %LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute
                   );

  }

  ThisAttribute = EFI_PCI_ATTRIBUTE_MEMORY_CACHED;
  if ((ThisAttribute & SupportedAttributes) == ThisAttribute) {

    //
    //call SetAttributes with ResourceBase as NULL.
    //
    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             NULL,
                             &ResourceLength
                             );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid064,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - MEMORY_CACHED with ResourceBase as NULL the return status must be EFI_INVALID_PARAMETER.",
                   L"%a:%d:Status - %r:Set Attributes - %LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute
                   );

    //
    //call SetAttributes with ResourceLength as NULL.
    //

    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             &ResourceBase,
                             NULL
                             );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid065,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - MEMORY_CACHED with ResourceLength as NULL the return status must be EFI_INVALID_PARAMETER.",
                   L"%a:%d:Status - %r:Set Attributes - %LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute
                   );

  }


  ThisAttribute = EFI_PCI_ATTRIBUTE_MEMORY_DISABLE;
  if ((ThisAttribute & SupportedAttributes) == ThisAttribute) {

    //
    //call SetAttributes with ResourceBase as NULL.
    //
    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             NULL,
                             &ResourceLength
                             );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid066,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - MEMORY_DISABLE with ResourceBase as NULL the return status must be EFI_INVALID_PARAMETER.",
                   L"%a:%d:Status - %r:Set Attributes - %LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute
                   );

    //
    //call SetAttributes with ResourceLength as NULL.
    //

    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             &ResourceBase,
                             NULL
                             );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciRootBridgeIoBBTestConformanceAssertionGuid067,
                   L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - MEMORY_DISABLE with ResourceLength as NULL the return status must be EFI_INVALID_PARAMETER.",
                   L"%a:%d:Status - %r:Set Attributes - %LXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttribute
                   );
  }

  //
  //done successfully
  //
  return EFI_SUCCESS;
}
