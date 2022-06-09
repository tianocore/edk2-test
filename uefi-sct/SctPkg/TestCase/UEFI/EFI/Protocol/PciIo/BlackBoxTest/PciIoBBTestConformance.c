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

  PciIoBBTestConformancet.c

Abstract:

  conformance test case source file for PciIo protocol

--*/

#include "SctLib.h"
#include "PciIoBBTestMain.h"
#include "PciIoBBTestSupport.h"

#define SECTION_NAME_POLLMEM_CONFORM_TEST           L"PollMem_Conf"
#define SECTION_NAME_POLLIO_CONFORM_TEST            L"PollIo_Conf"
#define SECTION_NAME_MEMREAD_CONFORM_TEST           L"MemRead_Conf"
#define SECTION_NAME_MEMWRITE_CONFORM_TEST          L"MemWrite_Conf"
#define SECTION_NAME_IOREAD_CONFORM_TEST            L"IoRead_Conf"
#define SECTION_NAME_IOWRITE_CONFORM_TEST           L"IoWrite_Conf"
#define SECTION_NAME_PCIREAD_CONFORM_TEST           L"PciRead_Conf"
#define SECTION_NAME_PCIWRITE_CONFORM_TEST          L"PciWrite_Conf"
#define SECTION_NAME_COPYMEM_CONFORM_TEST           L"CopyMem_Conf"

/**
 *  Entrypoint for PciIo->PollMem() conformance automatic test.
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
  EFI_STATUS                            Status;
  EFI_STATUS                            EfiStatus;
  UINT8                                 IoBarIndex;
  UINT8                                 MemBarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINT32                                AddressLength;
  UINTN                                 Index;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT64                                Mask;
  UINT64                                TargetValue;
  UINT8                                 Buffer[32];
  UINT64                                *Result;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 RepeatIndex;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }
  //
  //get a valid Mem type Bar.
  //
  MemBarIndex = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x00  ) {
      MemBarIndex = (UINT8)Index;
      break;
    }
  }
  if (MemBarIndex == 255) {
    return EFI_SUCCESS;
  }

  //
  //set valid value.
  //
  AddressLength = PciIoDevice->BarLength[MemBarIndex];
  AddressOffset = 0;
  PciIoWidth    = EfiPciIoWidthUint8;
  Mask          = 0xFF;
  TargetValue   = 0x01;
  Result = (UINT64 *)((((UINTN)Buffer + 7)/8)*8);

  //
  //Call PollMem with Width as EfiPciWidthMaximum.
  //
  Status = PciIo->PollMem (
                    PciIo,
                    EfiPciWidthMaximum,
                    MemBarIndex,
                    AddressOffset,
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
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestConformanceAssertionGuid001,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - With Width as EfiPciWidthMaximum the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //Call PollMem with Width as EfiPciWidthFifoUintX.
  //
  EfiStatus =  EFI_INVALID_PARAMETER;

  for (PciIoWidth = EfiPciIoWidthFifoUint8; PciIoWidth <= EfiPciIoWidthFifoUint64; PciIoWidth++) {

    Status = PciIo->PollMem (
                      PciIo,
                      PciIoWidth,
                      MemBarIndex,
                      AddressOffset,
                      Mask,
                      TargetValue & Mask,
                      5 * 10000000,
                      Result
                      );
    //
    //record message
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"EFI_PCI_IO_PROTOCOL.PollMem - Status must be EFI_INVALID_PARAMETER.\r\n"
                   L"%a:%d:Status - %r, Width - %s\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
      break;
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
                 gPciIoBBTestConformanceAssertionGuid002,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - With Width as EfiPciWidthFifoUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //Call PollMem with Width as EfiPciWidthFillUintX.
  //
  EfiStatus =  EFI_INVALID_PARAMETER;

  for (PciIoWidth = EfiPciIoWidthFillUint8; PciIoWidth <= EfiPciIoWidthFillUint64; PciIoWidth++) {

    Status = PciIo->PollMem (
                      PciIo,
                      PciIoWidth,
                      MemBarIndex,
                      AddressOffset,
                      Mask,
                      TargetValue & Mask,
                      5 * 10000000,
                      Result
                      );
    //
    //record message
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"EFI_PCI_IO_PROTOCOL.PollMem - Status must be EFI_INVALID_PARAMETER.\r\n"
                   L"%a:%d:Status - %r, Width - %s\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
      break;
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
                 gPciIoBBTestConformanceAssertionGuid003,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - With Width as EfiPciWidthFillUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //Call PollMem with Width as -1.
  //
  Status = PciIo->PollMem (
                    PciIo,
                    -1,
                    MemBarIndex,
                    AddressOffset,
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
                 gPciIoBBTestConformanceAssertionGuid004,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - With Width as -1 the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call PollMem with Result as NULL.
  //
  Status = PciIo->PollMem (
                    PciIo,
                    EfiPciIoWidthUint8,
                    MemBarIndex,
                    AddressOffset,
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
                 gPciIoBBTestConformanceAssertionGuid005,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - With Result as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call PollMem with Offset beyond the Memory Address range supported by this
  //BAR.
  //
  Status = PciIo->PollMem (
                    PciIo,
                    EfiPciIoWidthUint8,
                    MemBarIndex,
                    AddressLength,
                    Mask,
                    TargetValue & Mask,
                    5 * 10000000,
                    Result
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
                 gPciIoBBTestConformanceAssertionGuid006,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - With Offset beyond the range of BAR the return Status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call PollMem with an Invalid Bar Index.
  //
  Status = PciIo->PollMem (
                    PciIo,
                    EfiPciIoWidthUint8,
                    REGNUM,
                    AddressOffset,
                    Mask,
                    TargetValue & Mask,
                    5 * 10000000,
                    Result
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
                 gPciIoBBTestConformanceAssertionGuid007,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - With invalid BarIndex the return Status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 REGNUM
                 );

  //
  //get a valid Io Bar type.
  //
  IoBarIndex = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x01  ) {
      IoBarIndex = (UINT8)Index;
      break;
    }
  }
  if (IoBarIndex == 255) {
    return EFI_SUCCESS;
  }

  //
  //call PollMem with an Io Bar Index.
  //
  Status = PciIo->PollMem (
                    PciIo,
                    EfiPciIoWidthUint8,
                    IoBarIndex,
                    AddressOffset,
                    Mask,
                    TargetValue & Mask,
                    5 * 10000000,
                    Result
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
                 gPciIoBBTestConformanceAssertionGuid008,
                 L"EFI_PCI_IO_PROTOCOL.PollMem() - With Io Bar Index the return Status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, IoBarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 IoBarIndex
                 );

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
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  //based on the Profile to test the unsupported width.
  //

  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);

  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
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
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.PollMem - not found the profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_POLLMEM_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.PollMem - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_POLLMEM_CONFORM_TEST,
               RepeatIndex,
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
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_POLLMEM_CONFORM_TEST,
               RepeatIndex,
               &PciIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call PollIo with the appointed width.
    //

    Status = PciIo->PollMem (
                      PciIo,
                      PciIoWidth,
                      MemBarIndex,
                      AddressOffset,
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
                   gPciIoBBTestConformanceAssertionGuid101,
                   L"EFI_PCI_IO_PROTOCOL.PollMem() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
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
 *  Entrypoint for PciIo->PollIo() conformance automatically Test.
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

  EFI_STATUS                            Status;
  EFI_STATUS                            EfiStatus;
  UINT8                                 IoBarIndex;
  UINT8                                 MemBarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINT32                                AddressLength;
  UINTN                                 Index;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT64                                Mask;
  UINT64                                TargetValue;
  UINT8                                 Buffer[32];
  UINT64                                *Result;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 RepeatIndex;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }
  //
  //get a valid Io type Bar.
  //
  IoBarIndex = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x01  ) {
      IoBarIndex = (UINT8)Index;
      break;
    }
  }
  if (IoBarIndex == 255) {
    return EFI_SUCCESS;
  }
  //
  //set valid value.
  //
  AddressLength = PciIoDevice->BarLength[IoBarIndex];
  AddressOffset = 0;
  PciIoWidth    = EfiPciIoWidthUint8;
  Mask          = 0xFF;
  TargetValue   = 0x01;

  Result = (UINT64 *)((((UINTN)Buffer + 7)/8)*8);
  //
  //Call PollIo with Width as EfiPciWidthMaximum.
  //
  Status = PciIo->PollIo (
                    PciIo,
                    EfiPciWidthMaximum,
                    IoBarIndex,
                    AddressOffset,
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
                 gPciIoBBTestConformanceAssertionGuid009,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - With Width as EfiPciWidthMaximum the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //Call PollIo with Width as EfiPciWidthFifoUintX.
  //
  EfiStatus =  EFI_INVALID_PARAMETER;

  for (PciIoWidth = EfiPciIoWidthFifoUint8; PciIoWidth <= EfiPciIoWidthFifoUint64; PciIoWidth++) {

    Status = PciIo->PollIo (
                      PciIo,
                      PciIoWidth,
                      IoBarIndex,
                      AddressOffset,
                      Mask,
                      TargetValue & Mask,
                      5 * 10000000,
                      Result
                      );
    //
    //record message
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"EFI_PCI_IO_PROTOCOL.PollIo - Status must be EFI_INVALID_PARAMETER.\r\n"
                   L"%a:%d:Status - %r, Width - %s\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
      break;
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
                 gPciIoBBTestConformanceAssertionGuid010,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - With Width as EfiPciWidthFifoUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //Call PollIo with Width as EfiPciWidthFillUintX.
  //
  EfiStatus =  EFI_INVALID_PARAMETER;

  for (PciIoWidth = EfiPciIoWidthFifoUint8; PciIoWidth <= EfiPciIoWidthFifoUint64; PciIoWidth++) {

    Status = PciIo->PollIo (
                      PciIo,
                      PciIoWidth,
                      IoBarIndex,
                      AddressOffset,
                      Mask,
                      TargetValue & Mask,
                      5 * 10000000,
                      Result
                      );
    //
    //record message
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"EFI_PCI_IO_PROTOCOL.PollIo - Status must be EFI_INVALID_PARAMETER.\r\n"
                   L"%a:%d:Status - %r, Width - %s\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
      break;
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
                 gPciIoBBTestConformanceAssertionGuid011,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - With Width as EfiPciWidthFillUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );


  //
  //Call PollIo with Width as -1.
  //
  Status = PciIo->PollIo (
                    PciIo,
                    -1,
                    IoBarIndex,
                    AddressOffset,
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
                 gPciIoBBTestConformanceAssertionGuid012,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - With Width as -1 the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call PollIo with Result as NULL.
  //
  Status = PciIo->PollIo (
                    PciIo,
                    EfiPciIoWidthUint8,
                    IoBarIndex,
                    AddressOffset,
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
                 gPciIoBBTestConformanceAssertionGuid013,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - With Result as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call PollIo with Offset beyond the Io Address range supported by this
  //BAR.
  //
  Status = PciIo->PollIo (
                    PciIo,
                    EfiPciIoWidthUint8,
                    IoBarIndex,
                    AddressLength,
                    Mask,
                    TargetValue & Mask,
                    5 * 10000000,
                    Result
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
                 gPciIoBBTestConformanceAssertionGuid014,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - With Offset beyond the range of BAR the return Status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call PollIo with an Invalid Bar Index.
  //
  Status = PciIo->PollIo (
                    PciIo,
                    EfiPciIoWidthUint8,
                    REGNUM,
                    AddressOffset,
                    Mask,
                    TargetValue & Mask,
                    5 * 10000000,
                    Result
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
                 gPciIoBBTestConformanceAssertionGuid015,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - With Invalid BarIndex the return Status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 REGNUM
                 );
  //
  //get a valid Mem Bar type.
  //
  MemBarIndex = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x00  ) {
      MemBarIndex = (UINT8)Index;
      break;
    }
  }
  if (MemBarIndex == 255) {
    return EFI_SUCCESS;
  }
  //
  //call PollIo with an Mem Bar Index.
  //
  Status = PciIo->PollIo (
                    PciIo,
                    EfiPciIoWidthUint8,
                    MemBarIndex,
                    AddressOffset,
                    Mask,
                    TargetValue & Mask,
                    5 * 10000000,
                    Result
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
                 gPciIoBBTestConformanceAssertionGuid016,
                 L"EFI_PCI_IO_PROTOCOL.PollIo() - With Mem Bar Index the return Status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, MemBarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 MemBarIndex
                 );

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
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  //based on the Profile to test the unsupported width.
  //

  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);

  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
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
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.PollIo - not found the profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return Status;
  }

  //
  //get max section number.
  //
  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_POLLIO_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.PollIo - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_POLLIO_CONFORM_TEST,
               RepeatIndex,
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
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_POLLIO_CONFORM_TEST,
               RepeatIndex,
               &PciIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call PollIo with the appointed width.
    //

    Status = PciIo->PollIo (
                      PciIo,
                      PciIoWidth,
                      IoBarIndex,
                      AddressOffset,
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
                   gPciIoBBTestConformanceAssertionGuid102,
                   L"EFI_PCI_IO_PROTOCOL.PollIo() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
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
 *  Entrypoint for PciIo->Mem->Read() conformance automatically Test.
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
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT8                                 IoBarIndex;
  UINT8                                 MemBarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINT32                                AddressLength;
  UINTN                                 Index;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 RepeatIndex;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //get a valid Mem type Bar.
  //
  MemBarIndex = 255;

  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x00  ) {
      MemBarIndex = (UINT8)Index;
      break;
    }
  }

  if (MemBarIndex == 255) {
    return EFI_SUCCESS;
  }

  //
  //set valid value.
  //
  AddressLength = PciIoDevice->BarLength[MemBarIndex];
  AddressOffset = 0;
  PciIoWidth    = EfiPciIoWidthUint8;
  Count         = 16;
  //
  //first allocate a buffer.
  //
  Buffer = NULL;
  Buffer = SctAllocatePool (Count);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }


  //
  //call Mem.Read with Width as EfiPciIoWidthMaximum.
  //
  Status = PciIo->Mem.Read (
                        PciIo,
                        EfiPciIoWidthMaximum,
                        MemBarIndex,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid017,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Read - with Width as EfiPciIoWidthMaximum the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 MemBarIndex
                 );
  //
  //call Mem.Read with Width as -1.
  //
  Status = PciIo->Mem.Read (
                        PciIo,
                        -1,
                        MemBarIndex,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid018,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Read - with invalid Width type -1 the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //call Mem.Read with Buffer as NULL.
  //
  Status = PciIo->Mem.Read (
                        PciIo,
                        PciIoWidth,
                        MemBarIndex,
                        AddressOffset,
                        Count,
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
                 gPciIoBBTestConformanceAssertionGuid019,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Read - with Buffer as NULL the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 MemBarIndex
                 );

  //
  //call Mem.Read with Offset + Count * Width Beyond the address range supported
  //by this BAR.
  //
  Status = PciIo->Mem.Read (
                        PciIo,
                        PciIoWidth,
                        MemBarIndex,
                        AddressLength - 2,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid020,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Read - With address out of bar range the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Bar Address Length - %8xh, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AddressLength,
                 AddressLength - 2,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );

  PciIoWidth = EfiPciIoWidthUint16;
  Count      = 8;
  Status = PciIo->Mem.Read (
                        PciIo,
                        PciIoWidth,
                        MemBarIndex,
                        AddressLength - 2,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid021,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Read - with address out of Bar range the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Bar Address Length - %8xh, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AddressLength,
                 AddressLength - 2,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );


   //
   //call Mem.Read with a Invalid Bar Index.
   //
  PciIoWidth    = EfiPciIoWidthUint8;
  Count         = 16;
  AddressOffset = 0;

  Status = PciIo->Mem.Read (
                        PciIo,
                        PciIoWidth,
                        REGNUM,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid022,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Read - with invalid BarIndex the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 REGNUM
                 );

  //
  //get a valid Io Bar type.
  //
  IoBarIndex = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x01  ) {
      IoBarIndex = (UINT8)Index;
      break;
    }
  }
  if (IoBarIndex != 255) {

    //
    //call Mem.Read with an Io bar Index.
    //
    Status = PciIo->Mem.Read (
                          PciIo,
                          PciIoWidth,
                          IoBarIndex,
                          AddressOffset,
                          Count,
                          Buffer
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
                   gPciIoBBTestConformanceAssertionGuid023,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Read - with Io Type Bar the return status must be EFI_UNSUPPORTED",
                   L"%a:%d:Status - %r, IoBarIndex - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   IoBarIndex
                   );
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
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  //based on the Profile to test the unsupported width.
  //

  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);

  if (PciDevicePathStr == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    gtBS->FreePool (Buffer);
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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Read - not found the profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Read - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_CONFORM_TEST,
               RepeatIndex,
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
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_CONFORM_TEST,
               RepeatIndex,
               &PciIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Mem.Read with the appointed width.
    //

    AddressOffset = 0;
    Count         = 1;
    Status = PciIo->Mem.Read (
                          PciIo,
                          PciIoWidth,
                          MemBarIndex,
                          AddressOffset,
                          Count,
                          Buffer
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
                   gPciIoBBTestConformanceAssertionGuid103,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Read() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  gtBS->FreePool (Buffer);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->Mem->Write() conformance automatically Test.
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
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT8                                 IoBarIndex;
  UINT8                                 MemBarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINT32                                AddressLength;
  UINTN                                 Index;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 RepeatIndex;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //get a valid Mem type Bar.
  //
  MemBarIndex = 255;

  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x00  ) {
      MemBarIndex = (UINT8)Index;
      break;
    }
  }

  if (MemBarIndex == 255) {
    return EFI_SUCCESS;
  }

  //
  //set valid value.
  //
  AddressLength = PciIoDevice->BarLength[MemBarIndex];
  AddressOffset = 0;
  PciIoWidth    = EfiPciIoWidthUint8;
  Count         = 16;
  //
  //first allocate a buffer.
  //
  Buffer = NULL;
  Buffer = SctAllocatePool (Count);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }


  //
  //call Mem.Write with Width as EfiPciIoWidthMaximum.
  //
  Status = PciIo->Mem.Write (
                        PciIo,
                        EfiPciIoWidthMaximum,
                        MemBarIndex,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid024,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Write - with Width as EfiPciIoWidthMaximum the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 MemBarIndex
                 );
  //
  //call Mem.Write with Width as -1.
  //
  Status = PciIo->Mem.Write (
                        PciIo,
                        -1,
                        MemBarIndex,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid025,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Write - with invalid Width type -1 the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //call Mem.Write with Buffer as NULL.
  //
  Status = PciIo->Mem.Write (
                        PciIo,
                        PciIoWidth,
                        MemBarIndex,
                        AddressOffset,
                        Count,
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
                 gPciIoBBTestConformanceAssertionGuid026,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Write - with Buffer as NULL the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 MemBarIndex
                 );

  //
  //call Mem.Write with Offset + Count * Width Beyond the address range supported
  //by this BAR.
  //
  Status = PciIo->Mem.Write (
                        PciIo,
                        PciIoWidth,
                        MemBarIndex,
                        AddressLength - 2,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid027,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Write - With address out of bar range the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Bar Address Length - %8xh, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AddressLength,
                 AddressLength - 2,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );

  PciIoWidth = EfiPciIoWidthUint16;
  Count      = 8;
  Status = PciIo->Mem.Write (
                        PciIo,
                        PciIoWidth,
                        MemBarIndex,
                        AddressLength - 2,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid028,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Write - with address out of Bar range the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Bar Address Length - %8xh, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AddressLength,
                 AddressLength - 2,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );


   //
   //call Mem.Write with a Invalid Bar Index.
   //
  PciIoWidth    = EfiPciIoWidthUint8;
  Count         = 16;
  AddressOffset = 0;

  Status = PciIo->Mem.Write (
                        PciIo,
                        PciIoWidth,
                        REGNUM,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid029,
                 L"EFI_PCI_IO_PROTOCOL.Mem.Write - with invalid BarIndex the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 REGNUM
                 );

  //
  //get a valid Io Bar type.
  //
  IoBarIndex = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x01  ) {
      IoBarIndex = (UINT8)Index;
      break;
    }
  }
  if (IoBarIndex != 255) {

    //
    //call Mem.Write with an Io bar Index.
    //
    Status = PciIo->Mem.Write (
                          PciIo,
                          PciIoWidth,
                          IoBarIndex,
                          AddressOffset,
                          Count,
                          Buffer
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
                   gPciIoBBTestConformanceAssertionGuid030,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Write - with Io Type Bar the return status must be EFI_UNSUPPORTED",
                   L"%a:%d:Status - %r, IoBarIndex - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   IoBarIndex
                   );
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
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  //based on the Profile to test the unsupported width.
  //

  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);

  if (PciDevicePathStr == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    gtBS->FreePool (Buffer);
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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Write - not found the profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Write - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_CONFORM_TEST,
               RepeatIndex,
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
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_CONFORM_TEST,
               RepeatIndex,
               &PciIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Mem.Write with the appointed width.
    //

    AddressOffset = 0;
    Count         = 1;
    Status = PciIo->Mem.Write (
                          PciIo,
                          PciIoWidth,
                          MemBarIndex,
                          AddressOffset,
                          Count,
                          Buffer
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
                   gPciIoBBTestConformanceAssertionGuid104,
                   L"EFI_PCI_IO_PROTOCOL.Mem.Write() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  gtBS->FreePool (Buffer);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->Io->Read() conformance automatically Test.
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
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT8                                 IoBarIndex;
  UINT8                                 MemBarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINT32                                AddressLength;
  UINTN                                 Index;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 RepeatIndex;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }


  //
  //get a valid Io type Bar.
  //
  IoBarIndex = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x01  ) {
      IoBarIndex = (UINT8)Index;
      break;
    }
  }
  if (IoBarIndex == 255) {
    return EFI_SUCCESS;
  }
  //
  //set valid value.
  //
  AddressLength = PciIoDevice->BarLength[IoBarIndex];
  AddressOffset = 0;
  PciIoWidth    = EfiPciIoWidthUint8;
  Count         = 4;
  //
  //first allocate a buffer.
  //
  Buffer = NULL;
  Buffer = SctAllocatePool (Count);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //call Io.Read with Width as -1.
  //
  Status = PciIo->Io.Read (
                       PciIo,
                       -1,
                       IoBarIndex,
                       AddressOffset,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid031,
                 L"EFI_PCI_IO_PROTOCOL.Io.Read - with invalid Width type -1 the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call Io.Read with Width as EfiPciIoWidthMaximum.
  //
  Status = PciIo->Io.Read (
                       PciIo,
                       EfiPciIoWidthMaximum,
                       IoBarIndex,
                       AddressOffset,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid032,
                 L"EFI_PCI_IO_PROTOCOL.Io.Read - with invalid Width EfiPciIoWidthMaximum the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call Io.Read with Buffer as NULL.
  //
  Status = PciIo->Io.Read (
                       PciIo,
                       PciIoWidth,
                       IoBarIndex,
                       AddressOffset,
                       Count,
                       NULL
                       );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestConformanceAssertionGuid033,
                 L"EFI_PCI_IO_PROTOCOL.Io.Read - with Buffer as NULL the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //call Io.Read with Offset + Count * Width Beyond the address range supported
  //by this BAR.
  //
  Status = PciIo->Io.Read (
                       PciIo,
                       PciIoWidth,
                       IoBarIndex,
                       AddressLength - 2,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid034,
                 L"EFI_PCI_IO_PROTOCOL.Io.Read - with address out of Bar range the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Bar Address Length - %8xh, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AddressLength,
                 AddressLength - 2,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );


  PciIoWidth = EfiPciIoWidthUint16;
  Count      = 2;
  Status = PciIo->Io.Read (
                       PciIo,
                       PciIoWidth,
                       IoBarIndex,
                       AddressLength - 2,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid035,
                 L"EFI_PCI_IO_PROTOCOL.Io.Read - with address out of Bar range the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Bar Address Length - %8xh, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AddressLength,
                 AddressLength - 2,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );


   //
   //call Io.Read with a Invalid Bar Index.
   //
  PciIoWidth    = EfiPciIoWidthUint8;
  Count         = 4;
  AddressOffset = 0;

  Status = PciIo->Io.Read (
                       PciIo,
                       PciIoWidth,
                       REGNUM,
                       AddressOffset,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid036,
                 L"EFI_PCI_IO_PROTOCOL.Io.Read - with invalid BarIndex the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 REGNUM
                 );

  //
  //get a valid Mem Bar type.
  //
  MemBarIndex = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x00  ) {
      MemBarIndex = (UINT8)Index;
      break;
    }
  }
  if (MemBarIndex == 255) {
    gtBS->FreePool (Buffer);
    return EFI_SUCCESS;
  }
  //
  //call Io.Read with a memory bar Index.
  //
  Status = PciIo->Io.Read (
                       PciIo,
                       PciIoWidth,
                       MemBarIndex,
                       AddressOffset,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid037,
                 L"EFI_PCI_IO_PROTOCOL.Io.Read - with Mem Type Bar the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, MemBarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 MemBarIndex
                 );

  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  //based on the Profile to test the unsupported width.
  //

  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);

  if (PciDevicePathStr == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    gtBS->FreePool (Buffer);
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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Io.Read - not found the profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Io.Read - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_IOREAD_CONFORM_TEST,
               RepeatIndex,
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
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOREAD_CONFORM_TEST,
               RepeatIndex,
               &PciIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Io.Read with the appointed width.
    //

    AddressOffset = 0;
    Count         = 1;
    Status = PciIo->Io.Read (
                         PciIo,
                         PciIoWidth,
                         IoBarIndex,
                         AddressOffset,
                         Count,
                         Buffer
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
                   gPciIoBBTestConformanceAssertionGuid105,
                   L"EFI_PCI_IO_PROTOCOL.Io.Read() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  gtBS->FreePool (Buffer);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->Io->Write() conformance automatically Test.
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
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT8                                 IoBarIndex;
  UINT8                                 MemBarIndex;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINT32                                AddressLength;
  UINTN                                 Index;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 RepeatIndex;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //get a valid Io type Bar.
  //
  IoBarIndex = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x01  ) {
      IoBarIndex = (UINT8)Index;
      break;
    }
  }
  if (IoBarIndex == 255) {
    return EFI_SUCCESS;
  }
  //
  //set valid value.
  //
  AddressLength = PciIoDevice->BarLength[IoBarIndex];
  AddressOffset = 0;
  PciIoWidth    = EfiPciIoWidthUint8;
  Count         = 4;
  //
  //first allocate a buffer.
  //
  Buffer = NULL;
  Buffer = SctAllocatePool (Count);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //call Io.Write with Width as -1.
  //
  Status = PciIo->Io.Write (
                       PciIo,
                       -1,
                       IoBarIndex,
                       AddressOffset,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid038,
                 L"EFI_PCI_IO_PROTOCOL.Io.Write - with invalid Width type -1 the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call Io.Write with Width as EfiPciIoWidthMaximum.
  //
  Status = PciIo->Io.Write (
                       PciIo,
                       EfiPciIoWidthMaximum,
                       IoBarIndex,
                       AddressOffset,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid039,
                 L"EFI_PCI_IO_PROTOCOL.Io.Write - with invalid Width EfiPciIoWidthMaximum the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call Io.Write with Buffer as NULL.
  //
  Status = PciIo->Io.Write (
                       PciIo,
                       PciIoWidth,
                       IoBarIndex,
                       AddressOffset,
                       Count,
                       NULL
                       );
  if (Status == EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //Record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestConformanceAssertionGuid040,
                 L"EFI_PCI_IO_PROTOCOL.Io.Write - with Buffer as NULL the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //call Io.Write with Offset + Count * Width Beyond the address range supported
  //by this BAR.
  //
  Status = PciIo->Io.Write (
                       PciIo,
                       PciIoWidth,
                       IoBarIndex,
                       AddressLength - 2,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid041,
                 L"EFI_PCI_IO_PROTOCOL.Io.Write - with address out of Bar range the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Bar Address Length - %8xh, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AddressLength,
                 AddressLength - 2,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );


  PciIoWidth = EfiPciIoWidthUint16;
  Count      = 2;
  Status = PciIo->Io.Write (
                       PciIo,
                       PciIoWidth,
                       IoBarIndex,
                       AddressLength - 2,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid042,
                 L"EFI_PCI_IO_PROTOCOL.Io.Write - with address out of Bar range the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Bar Address Length - %8xh, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AddressLength,
                 AddressLength - 2,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );


   //
   //call Io.Write with a Invalid Bar Index.
   //
  PciIoWidth    = EfiPciIoWidthUint8;
  Count         = 4;
  AddressOffset = 0;

  Status = PciIo->Io.Write (
                       PciIo,
                       PciIoWidth,
                       REGNUM,
                       AddressOffset,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid043,
                 L"EFI_PCI_IO_PROTOCOL.Io.Write - with invalid BarIndex the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 REGNUM
                 );

  //
  //get a valid Mem Bar type.
  //
  MemBarIndex = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x00  ) {
      MemBarIndex = (UINT8)Index;
      break;
    }
  }
  if (MemBarIndex == 255) {
    gtBS->FreePool (Buffer);
    return EFI_SUCCESS;
  }
  //
  //call Io.Write with a memory bar Index.
  //
  Status = PciIo->Io.Write (
                       PciIo,
                       PciIoWidth,
                       MemBarIndex,
                       AddressOffset,
                       Count,
                       Buffer
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
                 gPciIoBBTestConformanceAssertionGuid044,
                 L"EFI_PCI_IO_PROTOCOL.Io.Write - with Mem Type Bar the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, MemBarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 MemBarIndex
                 );


  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  //based on the Profile to test the unsupported width.
  //

  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);

  if (PciDevicePathStr == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    gtBS->FreePool (Buffer);
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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Io.Write - not found the profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Io.Write - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_CONFORM_TEST,
               RepeatIndex,
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
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_CONFORM_TEST,
               RepeatIndex,
               &PciIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Io.Write with the appointed width.
    //

    AddressOffset = 0;
    Count         = 1;
    Status = PciIo->Io.Write (
                         PciIo,
                         PciIoWidth,
                         IoBarIndex,
                         AddressOffset,
                         Count,
                         Buffer
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
                   gPciIoBBTestConformanceAssertionGuid106,
                   L"EFI_PCI_IO_PROTOCOL.Io.Write() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  gtBS->FreePool (Buffer);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for PciIo->Pci->Read() conformance automatically Test.
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
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT32                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 RepeatIndex;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //set some valid values.
  //
  PciIoWidth    = EfiPciIoWidthUint8;
  AddressOffset = 64;
  Count         = 8;
  Buffer        = NULL;
  Buffer = SctAllocatePool (64);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //call Pci.Read with Width as -1.
  //
  Status = PciIo->Pci.Read (
                        PciIo,
                        -1,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid045,
                 L"EFI_PCI_IO_PROTOCOL.Pci.Read - Read with invalid Width as -1 the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //call Pci.Read with Width as EfiPciIoWidthMaximum.
  //
  Status = PciIo->Pci.Read (
                        PciIo,
                        EfiPciIoWidthMaximum,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid046,
                 L"EFI_PCI_IO_PROTOCOL.Pci.Read - Read with Width as EfiPciIoWidthMaximum the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call Pci.Read with Buffer as NULL.
  //
  Status = PciIo->Pci.Read (
                        PciIo,
                        PciIoWidth,
                        AddressOffset,
                        Count,
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
                 gPciIoBBTestConformanceAssertionGuid047,
                 L"EFI_PCI_IO_PROTOCOL.Pci.Read - Read with Buffer as NULL the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  /*

  Offset + Count * Width > 255 could be supported in PCI Express supported
  implementation. So even this bounary check is described in the EFI spec, but
  the bounary value could be implementation specific. So here we just comment
  these checkpoints.

  //
  //call Pci.Read with Offset + Count * Width > 255.
  //
  AddressOffset = 200;
  Count         = 64;
  PciIoWidth    = EfiPciIoWidthUint8;
  Status = PciIo->Pci.Read (
                        PciIo,
                        PciIoWidth,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid048,
                 L"EFI_PCI_IO_PROTOCOL.Pci.Read - Read with Offset + Count * Width > 255  the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 __LINE__,
                 Status,
                 AddressOffset,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );

  AddressOffset = 200;
  Count         = 32;
  PciIoWidth    = EfiPciIoWidthUint16;
  Status = PciIo->Pci.Read (
                        PciIo,
                        PciIoWidth,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid049,
                 L"EFI_PCI_IO_PROTOCOL.Pci.Read - Read with Offset + Count * Width > 255  the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 __LINE__,
                 Status,
                 AddressOffset,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );
  */

  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  //based on the Profile to test the unsupported width.
  //

  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);

  if (PciDevicePathStr == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    gtBS->FreePool (Buffer);
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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read - not found the profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_CONFORM_TEST,
               RepeatIndex,
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
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_CONFORM_TEST,
               RepeatIndex,
               &PciIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Pci.Read with the appointed width.
    //

    AddressOffset = 0;
    Count         = 1;
    Status = PciIo->Pci.Read (
                          PciIo,
                          PciIoWidth,
                          AddressOffset,
                          Count,
                          Buffer
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
                   gPciIoBBTestConformanceAssertionGuid107,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  gtBS->FreePool (Buffer);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->Pci->Write() conformance automatically Test.
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
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT32                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 RepeatIndex;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //set some valid values.
  //
  PciIoWidth    = EfiPciIoWidthUint8;
  AddressOffset = 64;
  Count         = 8;
  Buffer        = NULL;
  Buffer = SctAllocatePool (64);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //call Pci.Write with Width as -1.
  //
  Status = PciIo->Pci.Write (
                        PciIo,
                        -1,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid050,
                 L"EFI_PCI_IO_PROTOCOL.Pci.Write - Read with invalid Width as -1 the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //call Pci.Write with Width as EfiPciIoWidthMaximum.
  //
  Status = PciIo->Pci.Write (
                        PciIo,
                        EfiPciIoWidthMaximum,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid051,
                 L"EFI_PCI_IO_PROTOCOL.Pci.Write - Read with Width as EfiPciIoWidthMaximum the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call Pci.Write with Buffer as NULL.
  //
  Status = PciIo->Pci.Write (
                        PciIo,
                        PciIoWidth,
                        AddressOffset,
                        Count,
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
                 gPciIoBBTestConformanceAssertionGuid052,
                 L"EFI_PCI_IO_PROTOCOL.Pci.Write - Read with Buffer as NULL the return status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  /*

  Offset + Count * Width > 255 could be supported in PCI Express supported
  implementation. So even this bounary check is described in the EFI spec, but
  the bounary value could be implementation specific. So here we just comment
  these checkpoints.

  //
  //call Pci.Write with Offset + Count * Width > 255.
  //
  AddressOffset = 200;
  Count         = 64;
  PciIoWidth    = EfiPciIoWidthUint8;
  Status = PciIo->Pci.Write (
                        PciIo,
                        PciIoWidth,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid053,
                 L"EFI_PCI_IO_PROTOCOL.Pci.Write - Read with Offset + Count * Width > 255  the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 __LINE__,
                 Status,
                 AddressOffset,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );

  AddressOffset = 200;
  Count         = 32;
  PciIoWidth    = EfiPciIoWidthUint16;
  Status = PciIo->Pci.Write (
                        PciIo,
                        PciIoWidth,
                        AddressOffset,
                        Count,
                        Buffer
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
                 gPciIoBBTestConformanceAssertionGuid054,
                 L"EFI_PCI_IO_PROTOCOL.Pci.Write - Read with Offset + Count * Width > 255  the return status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, Offset - %8xh, Count - %xh, PciIoWidth - %s",
                 __FILE__,
                 __LINE__,
                 Status,
                 AddressOffset,
                 (UINT32)Count,
                 WidthCode[PciIoWidth]
                 );
  */

  //
  // Get the profile Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestProfileLibraryGuid,
                   (VOID **) &ProfileLib
                   );

  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = GetSystemData (ProfileLib);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  //
  //based on the Profile to test the unsupported width.
  //

  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);

  if (PciDevicePathStr == NULL) {
    gtBS->FreePool (Buffer);
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    gtBS->FreePool (Buffer);
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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - not found the profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

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
    gtBS->FreePool (Buffer);
    gtBS->FreePool (PciDevicePathStr);
    ProfileLib->EfiIniClose (
                  ProfileLib,
                  FileHandle
                  );
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_CONFORM_TEST,
               RepeatIndex,
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
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_CONFORM_TEST,
               RepeatIndex,
               &PciIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call Pci.Write with the appointed width.
    //

    AddressOffset = 0;
    Count         = 1;
    Status = PciIo->Pci.Write (
                          PciIo,
                          PciIoWidth,
                          AddressOffset,
                          Count,
                          Buffer
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
                   gPciIoBBTestConformanceAssertionGuid108,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write() - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

  }

  gtBS->FreePool (PciDevicePathStr);
  ProfileLib->EfiIniClose (
                ProfileLib,
                FileHandle
                );

  gtBS->FreePool (Buffer);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->CopyMem () conformance automatically Test.
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
  EFI_STATUS                            Status;
  EFI_STATUS                            EfiStatus;
  UINT64                                SrcAddressOffset;
  UINT64                                DestAddressOffset;
  UINT32                                Length;
  UINT8                                 MemBarIndex1;
  UINT8                                 IoBarIndex;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINTN                                 Index;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 RepeatIndex;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_INI_FILE_HANDLE                   FileHandle;
  CHAR16                                *FilePath;
  UINTN                                 MaxOrder;
  CHAR16                                *PciDevicePathStr;
  CHAR16                                *TempDevicePathStr;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //get a valid Mem type Bar.
  //
  MemBarIndex1 = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x00  ) {
      MemBarIndex1 = (UINT8)Index;
      break;
    }
  }
  if (MemBarIndex1 == 255) {
    return EFI_SUCCESS;
  }
  //
  //set some valid value.
  //
  PciIoWidth        = EfiPciIoWidthUint8;
  Length            = PciIoDevice->BarLength[MemBarIndex1];
  SrcAddressOffset  = 0;
  DestAddressOffset = Length / 2;
  Count             = 1;


  //
  //call CopyMem with Width as -1.
  //
  Status = PciIo->CopyMem (
                    PciIo,
                    -1,
                    MemBarIndex1,
                    DestAddressOffset,
                    MemBarIndex1,
                    SrcAddressOffset,
                    Count
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
                 gPciIoBBTestConformanceAssertionGuid055,
                 L"EFI_PCI_IO_PROTOCOL.CopyMem - with Width as -1 the return status must be EFI_INVALID_PARAMETER.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call CopyMem with Width as EfiPciIoWidthMaximum.
  //
  Status = PciIo->CopyMem (
                    PciIo,
                    EfiPciIoWidthMaximum,
                    MemBarIndex1,
                    DestAddressOffset,
                    MemBarIndex1,
                    SrcAddressOffset,
                    Count
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
                 gPciIoBBTestConformanceAssertionGuid056,
                 L"EFI_PCI_IO_PROTOCOL.CopyMem - with Width as EfiPciIoWidthMaximum the return status must be EFI_INVALID_PARAMETER.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //Call CopyMem with Width as EfiPciWidthFifoUintX.
  //
  EfiStatus =  EFI_INVALID_PARAMETER;

  for (PciIoWidth = EfiPciIoWidthFifoUint8; PciIoWidth <= EfiPciIoWidthFifoUint64; PciIoWidth++) {

    Status = PciIo->CopyMem (
                      PciIo,
                      PciIoWidth,
                      MemBarIndex1,
                      DestAddressOffset,
                      MemBarIndex1,
                      SrcAddressOffset,
                      Count
                      );
    //
    //record message
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"EFI_PCI_IO_PROTOCOL.CopyMem - Status must be EFI_INVALID_PARAMETER.\r\n"
                   L"%a:%d:Status - %r, Width - %d\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
      break;
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
                 gPciIoBBTestConformanceAssertionGuid057,
                 L"EFI_PCI_IO_PROTOCOL.CopyMem () - With Width as EfiPciWidthFifoUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //Call CopyMem with Width as EfiPciWidthFillUintX.
  //
  EfiStatus =  EFI_INVALID_PARAMETER;

  for (PciIoWidth = EfiPciIoWidthFillUint8; PciIoWidth <= EfiPciIoWidthFillUint64; PciIoWidth++) {

    Status = PciIo->CopyMem (
                      PciIo,
                      PciIoWidth,
                      MemBarIndex1,
                      DestAddressOffset,
                      MemBarIndex1,
                      SrcAddressOffset,
                      Count
                      );
    //
    //record message
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"EFI_PCI_IO_PROTOCOL.CopyMem - Status must be EFI_INVALID_PARAMETER.\r\n"
                   L"%a:%d:Status - %r, Width - %d\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

    if (Status != EFI_INVALID_PARAMETER) {
      EfiStatus = Status;
      break;
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
                 gPciIoBBTestConformanceAssertionGuid058,
                 L"EFI_PCI_IO_PROTOCOL.CopyMem () - With Width as EfiPciWidthFillUintX the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //Call CopyMem with SrcOffset  + Count * Width beyond the Memory Address range
  //supported by Source BAR.
  //
  PciIoWidth        = EfiPciIoWidthUint8;
  SrcAddressOffset  = (Length / 4) * 3;
  DestAddressOffset = 0;
  Count             = Length / 2;

  Status = PciIo->CopyMem (
                    PciIo,
                    PciIoWidth,
                    MemBarIndex1,
                    DestAddressOffset,
                    MemBarIndex1,
                    SrcAddressOffset,
                    Count
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
                 gPciIoBBTestConformanceAssertionGuid059,
                 L"EFI_PCI_IO_PROTOCOL.CopyMem - with Src Address area out of Bar range return status must be EFI_UNSUPPORTED.",
                 L"%a:%d:Status - %r, Bar Address Length - %08xh, Count - %xh, PciIoWidth - %d, Src Offset - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Length,
                 (UINT32)Count,
                 PciIoWidth,
                 SrcAddressOffset
                 );

  //
  //Call CopyMem with DestOffset  + Count * Width beyond the Memory Address range
  //supported by Dest BAR.
  //
  PciIoWidth        = EfiPciIoWidthUint8;
  SrcAddressOffset  = 0;
  DestAddressOffset = (Length / 4) * 3;
  Count             = Length / 2;

  Status = PciIo->CopyMem (
                    PciIo,
                    PciIoWidth,
                    MemBarIndex1,
                    DestAddressOffset,
                    MemBarIndex1,
                    SrcAddressOffset,
                    Count
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
                 gPciIoBBTestConformanceAssertionGuid060,
                 L"EFI_PCI_IO_PROTOCOL.CopyMem - with Dst Address area out of Bar range return status must be EFI_UNSUPPORTED.",
                 L"%a:%d:Status - %r, Bar Address Length - %xh, Count - %xh, PciIoWidth - %d, Dst Offset - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Length,
                 (UINT32)Count,
                 PciIoWidth,
                 DestAddressOffset
                 );

  //
  //Call CopyMem with SrcBarIndex or DestBarIndex as an invalid BarIndex.
  //
  PciIoWidth        = EfiPciIoWidthUint8;
  SrcAddressOffset  = 0 ;
  DestAddressOffset = Length / 2;
  Count             = 1;
  Status = PciIo->CopyMem (
                    PciIo,
                    PciIoWidth,
                    MemBarIndex1,
                    DestAddressOffset,
                    REGNUM,
                    SrcAddressOffset,
                    Count
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
                 gPciIoBBTestConformanceAssertionGuid061,
                 L"EFI_PCI_IO_PROTOCOL.CopyMem - with invalid SrcBarIndex = 6 return status must be EFI_UNSUPPORTED.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call with DestBarIndex as Invalid Bar Index.
  //
  Status = PciIo->CopyMem (
                    PciIo,
                    PciIoWidth,
                    REGNUM,
                    DestAddressOffset,
                    MemBarIndex1,
                    SrcAddressOffset,
                    Count
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
                 gPciIoBBTestConformanceAssertionGuid062,
                 L"EFI_PCI_IO_PROTOCOL.CopyMem - with invalid DestBarIndex = 6 return status must be EFI_UNSUPPORTED.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //get a valid Io type Bar.
  //
  IoBarIndex = 255;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0 &&
       (PciIoDevice->BarAttrib[Index] & 0x01) == 0x01  ) {
      IoBarIndex = (UINT8)Index;
      break;
    }
  }
  if (IoBarIndex == 255) {
    return EFI_SUCCESS;
  }
  //
  //call CopyMem with SrcBarIndex as IO Bar Index.
  //
  Status = PciIo->CopyMem (
                    PciIo,
                    PciIoWidth,
                    MemBarIndex1,
                    DestAddressOffset,
                    IoBarIndex,
                    SrcAddressOffset,
                    Count
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
                 gPciIoBBTestConformanceAssertionGuid063,
                 L"EFI_PCI_IO_PROTOCOL.CopyMem - with SrcBarIndex as an IO type Bar return status must be EFI_UNSUPPORTED.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //call CopyMem with DestBarIndex as IO Bar Index.
  //
  Status = PciIo->CopyMem (
                    PciIo,
                    PciIoWidth,
                    IoBarIndex,
                    DestAddressOffset,
                    MemBarIndex1,
                    SrcAddressOffset,
                    Count
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
                 gPciIoBBTestConformanceAssertionGuid064,
                 L"EFI_PCI_IO_PROTOCOL.CopyMem - with DestBarIndex as an IO type Bar return status must be EFI_UNSUPPORTED.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
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

  //
  //based on the Profile to test the unsupported width.
  //

  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  PciDevicePathStr = NULL;
  PciDevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);

  if (PciDevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PCI_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
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
    gtBS->FreePool (PciDevicePathStr);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.CopyMem - not found the profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

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
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.CopyMem - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  for (RepeatIndex = 0; RepeatIndex < MaxOrder; RepeatIndex++) {

    //
    //get device path from profile.
    //

    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_CONFORM_TEST,
               RepeatIndex,
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
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_CONFORM_TEST,
               RepeatIndex,
               &PciIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call CopyMem with the appointed width.
    //

    Length            = PciIoDevice->BarLength[MemBarIndex1];
    SrcAddressOffset  = 0;
    DestAddressOffset = Length / 2;
    Count             = 1;
    Status = PciIo->CopyMem (
                      PciIo,
                      PciIoWidth,
                      MemBarIndex1,
                      DestAddressOffset,
                      MemBarIndex1,
                      SrcAddressOffset,
                      Count
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
                   gPciIoBBTestConformanceAssertionGuid109,
                   L"EFI_PCI_IO_PROTOCOL.CopyMem () - With invalid Width the return Status must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
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
 *  Entrypoint for PciIo->Map() conformance automatically Test.
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

  EFI_STATUS                            Status;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  VOID                                  *HostAddress;
  UINTN                                 NumberOfBytes;
  EFI_PHYSICAL_ADDRESS                  DeviceAddress;
  VOID                                  *Mapping;
  EFI_PCI_IO_PROTOCOL_OPERATION         Operation;
  UINT8                                 *Buffer;
  UINTN                                 BufferSize;
  EFI_TEST_ASSERTION                    AssertionType;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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

  NumberOfBytes = BufferSize;
  HostAddress   = (void *)Buffer;
  //
  //call Map with invalid Operation: EfiPciIoOperationMaximum.
  //
  Operation     = EfiPciIoOperationMaximum;

  Status = PciIo->Map (
                    PciIo,
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
                 gPciIoBBTestConformanceAssertionGuid065,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih invalid Operation the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Operation - %d, Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation,
                 Status
                 );

  //
  //call Map with  invalid Operation: EfiPciIoOperationMaximum + 1.
  //
  Operation     = EfiPciIoOperationMaximum + 1;

  Status = PciIo->Map (
                    PciIo,
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
                 gPciIoBBTestConformanceAssertionGuid066,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih invalid Operation the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Operation - %d, Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation,
                 Status
                 );

  //
  //call Map with  invalid Operation: -1.
  //
  Operation  = -1;

  Status = PciIo->Map (
                    PciIo,
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
                 gPciIoBBTestConformanceAssertionGuid067,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih invalid Operation the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Operation - %d, Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Operation,
                 Status
                 );

  //
  //set valid Operation.
  //
  Operation = EfiPciIoOperationBusMasterRead;

  //
  //call Map with HostAddress As NULL.
  //
  Status = PciIo->Map (
                    PciIo,
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
                 gPciIoBBTestConformanceAssertionGuid068,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih HostAddress as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call Map with NumberOfBytes As NULL.
  //
  Status = PciIo->Map (
                    PciIo,
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
                 gPciIoBBTestConformanceAssertionGuid069,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih NumberOfBytes as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //call Map with DeviceAddress As NULL.
  //
  Status = PciIo->Map (
                    PciIo,
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
                 gPciIoBBTestConformanceAssertionGuid070,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih DeviceAddress as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call Map with Mapping As NULL.
  //
  Status = PciIo->Map (
                    PciIo,
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
                 gPciIoBBTestConformanceAssertionGuid071,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Mapping as NULL the return Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // This 4GB should not be a limitation on IPF and EM64T IA32
  //

  //
  //at last free the buffer.
  //

  gtBS->FreePool (Buffer);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->AllocateBuffer() conformance automatically Test.
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
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_STATUS                            EfiStatus;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  VOID                                  *HostAddress;
  UINT64                                Attributes;
  UINTN                                 Index;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 InvalidMemoryTypeNum;
  UINTN                                 AttributesNum;

  EFI_MEMORY_TYPE InvalidMemoryType[15] = {
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
    EfiMaxMemoryType + 1,
    -1
  };

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //call allocate buffer with invalid memory types.
  //

  InvalidMemoryTypeNum = 15;
  EfiStatus = EFI_INVALID_PARAMETER;

  for (Index = 0; Index < InvalidMemoryTypeNum; Index++) {

    Status = PciIo->AllocateBuffer (
                      PciIo,
                      0,
                      InvalidMemoryType[Index],
                      1,
                      (VOID **) &HostAddress,
                      0
                      );

    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"EFI_PCI_IO_PROTOCOL.AllocateBuffer - with invalid Memory type Status must be EFI_INVALID_PARAMETER.\r\n"
                   L"%a:%d:Status - %r, Memory Type - %d\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   InvalidMemoryType[Index]
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
                 gPciIoBBTestConformanceAssertionGuid075,
                 L"EFI_PCI_IO_PROTOCOL.AllocateBuffer - with Invalid memory type the  status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );

  //
  //call allocatebuffer with HostAddress as NULL.
  //
  Status = PciIo->AllocateBuffer (
                    PciIo,
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
                 gPciIoBBTestConformanceAssertionGuid076,
                 L"EFI_PCI_IO_PROTOCOL.AllocateBuffer - with HostAddress as NULL the status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call AllocateBuffer with Attributes Having bits other then
  // EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE and EFI_PCI_ATTRIBUTE_MEMORY_CACHED
  //set the return status must be EFI_UNSUPPORTED.
  //
  AttributesNum = 19;
  EfiStatus = EFI_UNSUPPORTED;

  for (Index = 0; Index < AttributesNum; Index++) {
    Attributes = (UINT64) (1 << Index);

    if (Attributes != EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE &&
        Attributes != EFI_PCI_ATTRIBUTE_MEMORY_CACHED  ) {
      Status = PciIo->AllocateBuffer (
                        PciIo,
                        AllocateAnyPages,
                        EfiBootServicesData,
                        1,
                        (VOID **) &HostAddress,
                        Attributes
                        );

      //
      //record message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"EFI_PCI_IO_PROTOCOL.AllocateBuffer - with invalid Attributes Status must be EFI_INVALID_PARAMETER.\r\n"
                     L"%a:%d:Status - %r, Attributes - %lXh\r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Attributes
                     );

      if (Status != EFI_UNSUPPORTED) {
        EfiStatus = Status;
      }
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
                 gPciIoBBTestConformanceAssertionGuid077,
                 L"EFI_PCI_IO_PROTOCOL.AllocateBuffer - with invalid Attributes the status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );


  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->GetLocation() conformance automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.12
//
EFI_STATUS
EFIAPI
GetLocation_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 SegNumber;
  UINTN                                 BusNumber;
  UINTN                                 DevNumber;
  UINTN                                 FuncNumber;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //call GetLocation four time with SegmentNumber, BusNumber,DeviceNumber,
  //FunctionNumber as NULL respectively.
  //

  Status = PciIo->GetLocation (
                    PciIo,
                    NULL,
                    &BusNumber,
                    &DevNumber,
                    &FuncNumber
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
                 gPciIoBBTestConformanceAssertionGuid082,
                 L"EFI_PCI_IO_PROTOCOL.GetLocation - with SegmentNumber as NULL the status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = PciIo->GetLocation (
                    PciIo,
                    &SegNumber,
                    NULL,
                    &DevNumber,
                    &FuncNumber
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
                 gPciIoBBTestConformanceAssertionGuid083,
                 L"EFI_PCI_IO_PROTOCOL.GetLocation - with BusNumber as NULL the status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = PciIo->GetLocation (
                    PciIo,
                    &SegNumber,
                    &BusNumber,
                    NULL,
                    &FuncNumber
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
                 gPciIoBBTestConformanceAssertionGuid084,
                 L"EFI_PCI_IO_PROTOCOL.GetLocation - with DeviceNumber as NULL the status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = PciIo->GetLocation (
                    PciIo,
                    &SegNumber,
                    &BusNumber,
                    &DevNumber,
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
                 gPciIoBBTestConformanceAssertionGuid085,
                 L"EFI_PCI_IO_PROTOCOL.GetLocation - with FunctionNumber as NULL the status must be EFI_INVALID_PARAMETER",
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
 *  Entrypoint for PciIo->Attributes() conformance automatically Test.
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
Attributes_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT64                                CurrentAttributes;
  UINT64                                CommonAttributes;
  UINTN                                 AttributesNumber;
  UINT64                                ThisAttributes;
  UINT64                                SupportedAttributes;
  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //call Attributes with Operations as EfiPciIoAttributeOperationMaximum,
  //EfiPciIoAttributeOperationMaximum + 1 ,and - 1
  //
  CurrentAttributes = 0;
  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationMaximum,
                    CurrentAttributes,
                    &CommonAttributes
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
                 gPciIoBBTestConformanceAssertionGuid086,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - with Operation as EfiPciIoAttributeOperationMaximum status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationMaximum + 1,
                    CurrentAttributes,
                    &CommonAttributes
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
                 gPciIoBBTestConformanceAssertionGuid087,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - with Operation as EfiPciIoAttributeOperationMaximum + 1 status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

 Status = PciIo->Attributes (
                   PciIo,
                   -1,
                   CurrentAttributes,
                   &CommonAttributes
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
                 gPciIoBBTestConformanceAssertionGuid088,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - with Operation as -1 the status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call Attributes with EfiPciIoAttributeOperationGet and Results as NULL.
  //
  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationGet,
                    CurrentAttributes,
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
                 gPciIoBBTestConformanceAssertionGuid089,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - with Operation as EfiPciIoAttributeOperationGet and Results as NULL then the status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call Attributes with EfiPciIoAttributeOperationSupported and Results as NULL.
  //
  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationSupported,
                    CurrentAttributes,
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
                 gPciIoBBTestConformanceAssertionGuid090,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - with Operation as EfiPciIoAttributeOperationSupported and Results as NULL then the status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //get device supported attributes
  //
  PciIo->Attributes (
           PciIo,
           EfiPciIoAttributeOperationSupported,
           CurrentAttributes,
           &SupportedAttributes
           );

  //
  //find a unsupported attributes by this device
  //and do the set/enable/disable operation
  //
  ThisAttributes  = 0;

  for (AttributesNumber = 0; AttributesNumber < 19; AttributesNumber++) {
    ThisAttributes = (UINT64) (1 << AttributesNumber);
    if ((ThisAttributes & SupportedAttributes) == 0) {

      //
      //call Attributes to set Unsupported attributes for this device.
      //

      Status = PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationSet,
                        ThisAttributes,
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
                     gPciIoBBTestConformanceAssertionGuid091,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - Set Unsupported Attributes the status must be EFI_UNSUPPORTED",
                     L"%a:%d:Status - %r, Set Attributes - %lXh, Supported Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ThisAttributes,
                     SupportedAttributes
                     );

      //
      //call Attributes to Enable Unsupported attributes for this device.
      //

      Status = PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationEnable,
                        ThisAttributes,
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
                     gPciIoBBTestConformanceAssertionGuid092,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - enable Unsupported Attributes the status must be EFI_UNSUPPORTED",
                     L"%a:%d:Status - %r, Enabled Attributes - %lXh, Supported Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ThisAttributes,
                     SupportedAttributes
                     );

      //
      //call Attributes to Disable Unsupported attributes for this device.
      //

      Status = PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationDisable,
                        ThisAttributes,
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
                     gPciIoBBTestConformanceAssertionGuid093,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - Disable Unsupported Attributes the status must be EFI_UNSUPPORTED",
                     L"%a:%d:Status - %r, Disable Attributes - %lXh, Supported Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ThisAttributes,
                     SupportedAttributes
                     );

    }
  }

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->GetBarAttributes() conformance automatically Test.
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
GetBarAttributes_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                            Status;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT8                                 BarIndex;
  UINT64                                BarOriginalAttributes;
  VOID                                  *Resources;

  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }
  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //4.2.14.2.1 call getbarAttributes with an invalid BarIndex.
  //
  BarIndex  = 6;
  Resources = NULL;
  BarOriginalAttributes  = 0;

  Status = PciIo->GetBarAttributes (
                    PciIo,
                    BarIndex,
                    &BarOriginalAttributes,
                    &Resources
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
                 gPciIoBBTestConformanceAssertionGuid094,
                 L"EFI_PCI_IO_PROTOCOL.GetBarAttributes - with invalid BarIndex the status must be EFI_UNSUPPORTED",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 BarIndex
                 );

  BarIndex = 0;

  //
  //call GetBarAttributes with both Supports and Resources as NULL.
  //
  Status = PciIo->GetBarAttributes (
                    PciIo,
                    BarIndex,
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
                 gPciIoBBTestConformanceAssertionGuid095,
                 L"EFI_PCI_IO_PROTOCOL.GetBarAttributes - with both Supports and Resources as NULL status must be EFI_INVALID_PARAMETER ",
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
 *  Entrypoint for PciIo->SetBarAttributes() conformance automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.2.15
//
EFI_STATUS
EFIAPI
SetBarAttributes_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                            Status;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 Index;
  UINT8                                 BarIndex;
  UINT64                                BarOriginalAttributes;
  UINT64                                AddressOffset;
  UINT64                                AddressLength;
  UINT64                                ThisAttributes;
  UINTN                                 AttributesNumber;
  BOOLEAN                               FoundAttributes;


  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

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
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }
  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //4.2.15.2.1 call SetBarAttributes with an invalid parameter.
  //

  //
  //found a valid Bar.
  //
  BarIndex = REGNUM;

  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index] && PciIoDevice->BarLength[Index] > 0) {
      BarIndex = (UINT8)Index;
      break;
    }
  }

  if (BarIndex == REGNUM) {
    return EFI_ABORTED;
  }

  //
  //first get this bar attributes
  //
  PciIo->GetBarAttributes (
           PciIo,
           BarIndex,
           &BarOriginalAttributes,
           NULL
           );

  //
  //call SetBarAttributes with invalid Bar Index.
  //
  AddressOffset = 0;
  AddressLength = PciIoDevice->BarLength[BarIndex];

  Status = PciIo->SetBarAttributes (
                    PciIo,
                    BarOriginalAttributes,
                    REGNUM,
                    &AddressOffset,
                    &AddressLength
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
                 gPciIoBBTestConformanceAssertionGuid096,
                 L"EFI_PCI_IO_PROTOCOL.SetBarAttributes - with invalid BarIndex the status must be EFI_UNSUPPORTED.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call SetBarAttributes with Offset as NULL.
  //

  Status = PciIo->SetBarAttributes (
                    PciIo,
                    BarOriginalAttributes,
                    BarIndex,
                    NULL,
                    &AddressLength
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
                 gPciIoBBTestConformanceAssertionGuid097,
                 L"EFI_PCI_IO_PROTOCOL.SetBarAttributes - with Offset as NULL the status must be EFI_INVALID_PARAMETER.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call SetBarAttributes with Length as NULL.
  //
  Status = PciIo->SetBarAttributes (
                    PciIo,
                    BarOriginalAttributes,
                    BarIndex,
                    &AddressOffset,
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
                 gPciIoBBTestConformanceAssertionGuid098,
                 L"EFI_PCI_IO_PROTOCOL.SetBarAttributes - with Length as NULL the status must be EFI_INVALID_PARAMETER.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //call SetBarAttributes with AddressOffet + Length out of the Bar resource.
  //

  AddressOffset = 0;
  AddressLength = (UINT64)PciIoDevice->BarLength[BarIndex] + 1024;

  Status = PciIo->SetBarAttributes (
                    PciIo,
                    BarOriginalAttributes,
                    BarIndex,
                    &AddressOffset,
                    &AddressLength
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
                 gPciIoBBTestConformanceAssertionGuid099,
                 L"EFI_PCI_IO_PROTOCOL.SetBarAttributes - with Offset + Length out the Bar resourcde range the status must be EFI_UNSUPPORTED.",
                 L"%a:%d:Status - %r, OffSet - %lXh, Length - %lXh, Bar Resource Length - %lxh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AddressOffset,
                 AddressLength,
                 PciIoDevice->BarLength[BarIndex]
                 );

  //
  //find a unsupported attributes by this device
  //
  ThisAttributes  = 0;
  FoundAttributes = FALSE;

  for (AttributesNumber = 0; AttributesNumber < 19; AttributesNumber++) {
    ThisAttributes = (UINT64) (1 << AttributesNumber);
    if ((ThisAttributes & BarOriginalAttributes) == 0) {
      FoundAttributes = TRUE;
      break;
    }
  }

  if (!FoundAttributes) {
    return EFI_SUCCESS;
  }

  //
  //call SetBarAttributes with Attributes not supported by this Bar.
  //

  AddressLength = PciIoDevice->BarLength[BarIndex];

  Status = PciIo->SetBarAttributes (
                    PciIo,
                    ThisAttributes,
                    BarIndex,
                    &AddressOffset,
                    &AddressLength
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
                 gPciIoBBTestConformanceAssertionGuid100,
                 L"EFI_PCI_IO_PROTOCOL.SetBarAttributes - With Unsupported attributes the status must be EFI_UNSUPPORTED.",
                 L"%a:%d:Status - %r, Set Attributes - %lXh, Bar Supported Attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 ThisAttributes,
                 BarOriginalAttributes
                 );
  //
  //done successfully
  //
  return EFI_SUCCESS;
}
