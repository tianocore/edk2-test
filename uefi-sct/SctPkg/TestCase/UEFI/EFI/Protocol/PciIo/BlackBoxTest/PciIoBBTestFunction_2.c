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

  PciIoBBTestFunction_2.c

Abstract:

  function test case source file for PciIo Protocol

--*/

#include "SctLib.h"
#include "PciIoBBTestMain.h"
#include "PciIoBBTestSupport.h"

#define SECTION_NAME_PCIREAD_TEST            L"PciRead_Func"
#define SECTION_NAME_PCIWRITE_TEST           L"PciWrite_Func"
#define SECTION_NAME_COPYMEM_TEST            L"CopyMem_Func"


/**
 *  Entrypoint for PciIo->Pci->Read() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.9
//
EFI_STATUS
EFIAPI
PciRead_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             SecondWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             ThirdWidth;
  UINT32                                AddressLength;
  UINT32                                UnitLength;
  UINTN                                 Index;
  UINTN                                 RepeatIndex;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  VOID                                  *ReadBuffer;
  VOID                                  *BackupBuffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
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
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read - not found the Profile.",
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
                         SECTION_NAME_PCIREAD_TEST,
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
               SECTION_NAME_PCIREAD_TEST,
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
    //get Offset and width.
    //
    AddressOffset = 0;
    Status = GetAddressOffsetByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_TEST,
               RepeatIndex,
               &AddressOffset
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get width
    //
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_TEST,
               RepeatIndex,
               &PciIoWidth
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    switch (PciIoWidth) {
      case EfiPciIoWidthUint8:
        UnitLength  = 1;
        SecondWidth = EfiPciIoWidthFifoUint8;
        ThirdWidth  = EfiPciIoWidthFillUint8;
        break;
      case EfiPciIoWidthUint16:
        UnitLength  = 2;
        SecondWidth = EfiPciIoWidthFifoUint16;
        ThirdWidth  = EfiPciIoWidthFillUint16;
        break;
      case EfiPciIoWidthUint32:
        UnitLength  = 4;
        SecondWidth = EfiPciIoWidthFifoUint32;
        ThirdWidth  = EfiPciIoWidthFillUint32;
        break;
      default:
        UnitLength  = 8;
        SecondWidth = EfiPciIoWidthFifoUint64;
        ThirdWidth  = EfiPciIoWidthFillUint64;
        break;
    }
    //
    //get address length.
    //
    AddressLength = 0;
    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_TEST,
               RepeatIndex,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }
    AddressLength = (UINT32)(Count * UnitLength);
    //
    //verify the Offset and length are valid for pci config space.
    //
    if ((AddressOffset + AddressLength) > PCI_MAX_CONFIG_OFFSET) {
      //
      //log message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"the Offset/Length are invalid for this pci config space.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      continue;
    }

    //
    //get Data Units.
    //
    Buffer = NULL;
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_TEST,
               RepeatIndex,
               AddressLength,
               &Buffer
               );
    if (EFI_ERROR(Status)) {
      Buffer = (UINT8 *)SctAllocatePool (AddressLength);
      if (Buffer == NULL) {
        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );
        return EFI_OUT_OF_RESOURCES;
      }
      for (Index = 0; Index < AddressLength; Index++) {
        Buffer[Index] = (UINT8) (Index & 0xFF);
      }
    }
    //
    //allocate read buffer.
    //

    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );
      return EFI_OUT_OF_RESOURCES;
    }

    BackupBuffer = NULL;
    BackupBuffer = SctAllocatePool (AddressLength);
    if (BackupBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (ReadBuffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );
      return EFI_OUT_OF_RESOURCES;
    }
    //
    //record test envionment.
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PciRead env. \r\n"
                   L"%a:%d:AddressOffset - %lXh, PciIoWidth - %s, Count - %xh\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   AddressOffset,
                   WidthCode[PciIoWidth],
                   (UINT32)Count
                   );

    //
    //first read data out.
    //
    Status =PciIo->Pci.Read (
                         PciIo,
                         PciIoWidth,
                         (UINT32)AddressOffset,
                         Count,
                         BackupBuffer
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
                   gPciIoBBTestFunction_2AssertionGuid001,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read - Read data out into backup buffer.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    //then write the buffer into destination address range.
    //
    Status =PciIo->Pci.Write (
                         PciIo,
                         PciIoWidth,
                         (UINT32)AddressOffset,
                         Count,
                         Buffer
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
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - Write data to pci config space",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    //
    //then read out the data in destination address range.
    //
    Status =PciIo->Pci.Read (
                         PciIo,
                         PciIoWidth,
                         (UINT32)AddressOffset,
                         Count,
                         ReadBuffer
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
                   gPciIoBBTestFunction_2AssertionGuid002,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read - read out the data from pci config space",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );

    //
    //the data read out must be the same as write into.
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciIoBBTestFunction_2AssertionGuid003,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read - read out the data from pci config space with PciIoWidthUintX the data must equal with what written",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    //read out the data using EfiPciIoWidthFifoUintX.
    //
    Status =PciIo->Pci.Read (
                         PciIo,
                         SecondWidth,
                         (UINT32)AddressOffset,
                         Count,
                         ReadBuffer
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
                   gPciIoBBTestFunction_2AssertionGuid004,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read - read out the data with EfiPciIoWidthFifoX",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[SecondWidth]
                   );

    //
    //the data read out must be the same as the first data unit.
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for (Index = 0; Index < Count; Index++) {
      if (SctCompareMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        break;
      }
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciIoBBTestFunction_2AssertionGuid005,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read - read out the data with EfiPciIoWidthFifoX the data read out must be the same as the first data unit",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    //make the readbuffer units all with the same value as the first unit in buffer
    //by force.
    //

    for (Index = 0; Index < Count; Index++) {
      SctCopyMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength);
    }

    //
    //read out the data using EfiPciIoWidthFillUintX.
    //
    Status =PciIo->Pci.Read (
                         PciIo,
                         ThirdWidth,
                         (UINT32)AddressOffset,
                         Count,
                         ReadBuffer
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
                   gPciIoBBTestFunction_2AssertionGuid006,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read - read out the data with EfiPciIoWidthFillX",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[ThirdWidth]
                   );

    //
    //the data read out first unit in buffer must equal last unit in address space
    //and the other unit unchange.
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;

    if (SctCompareMem ((UINT8 *)ReadBuffer, (UINT8 *)Buffer + (Count -1) * UnitLength, UnitLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    for (Index = 1; Index < Count; Index++) {
      if (SctCompareMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        break;
      }
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciIoBBTestFunction_2AssertionGuid007,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read - read out the data with EfiPciIoWidthFillX the First data unit must equal with the last Data Unit in Destination address range",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    //restore the data back.
    //

    Status =PciIo->Pci.Write (
                         PciIo,
                         PciIoWidth,
                         (UINT32)AddressOffset,
                         Count,
                         BackupBuffer
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
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - write back the data.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    //free resource.
    //
    gtBS->FreePool (Buffer);
    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (BackupBuffer);
  }

  //
  //free resources.
  //
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
 *  Entrypoint for PciIo->Pci.Write() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.10
//
EFI_STATUS
EFIAPI
PciWrite_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT64                                AddressOffset;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             SecondWidth;
  EFI_PCI_IO_PROTOCOL_WIDTH             ThirdWidth;
  UINT32                                AddressLength;
  UINT32                                UnitLength;
  UINTN                                 Index;
  UINTN                                 RepeatIndex;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  VOID                                  *ReadBuffer;
  VOID                                  *BackupBuffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
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
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - not found the Profile.",
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
                         SECTION_NAME_PCIWRITE_TEST,
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
               SECTION_NAME_PCIWRITE_TEST,
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
    //get Offset length and width.
    //
    AddressOffset = 0;
    Status = GetAddressOffsetByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_TEST,
               RepeatIndex,
               &AddressOffset
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get width
    //
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_TEST,
               RepeatIndex,
               &PciIoWidth
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    switch (PciIoWidth) {
      case EfiPciIoWidthUint8:
        UnitLength  = 1;
        SecondWidth = EfiPciIoWidthFifoUint8;
        ThirdWidth  = EfiPciIoWidthFillUint8;
        break;
      case EfiPciIoWidthUint16:
        UnitLength  = 2;
        SecondWidth = EfiPciIoWidthFifoUint16;
        ThirdWidth  = EfiPciIoWidthFillUint16;
        break;
      case EfiPciIoWidthUint32:
        UnitLength  = 4;
        SecondWidth = EfiPciIoWidthFifoUint32;
        ThirdWidth  = EfiPciIoWidthFillUint32;
        break;
      default:
        UnitLength  = 8;
        SecondWidth = EfiPciIoWidthFifoUint64;
        ThirdWidth  = EfiPciIoWidthFillUint64;
        break;
    }
    //
    //get address length.
    //
    AddressLength = 0;
    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_TEST,
               RepeatIndex,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }
    AddressLength = (UINT32)(Count * UnitLength);
    //
    //verify the Offset and Length is valid for Pci config space.
    //
    if ((AddressOffset + AddressLength) > PCI_MAX_CONFIG_OFFSET) {
      //
      //log message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"the Offset and Length are invalid for Pci config space.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      continue;
    }

    //
    //get Data Units.
    //
    Buffer = NULL;
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_TEST,
               RepeatIndex,
               AddressLength,
               &Buffer
               );
    if (EFI_ERROR(Status)) {
      Buffer = (UINT8 *)SctAllocatePool (AddressLength);
      if (Buffer == NULL) {
        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );
        return EFI_OUT_OF_RESOURCES;
      }
      for (Index = 0; Index < AddressLength; Index++) {
        Buffer[Index] = (UINT8) (Index & 0xFF);
      }
    }
    //
    //allocate read buffer.
    //

    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //allocate BackupBuffer.
    //
    BackupBuffer = NULL;
    BackupBuffer = SctAllocatePool (AddressLength);

    if (BackupBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (ReadBuffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );

      return EFI_OUT_OF_RESOURCES;
    }
    //
    //record test envionment.
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PciWrite env. \r\n"
                   L"%a:%d:AddressOffset - %lXh,PciIoWidth - %s,Count - %x\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   AddressOffset,
                   WidthCode[PciIoWidth],
                   (UINT32)Count
                   );

    //
    //first read the data out.
    //
    Status = PciIo->Pci.Read (
                          PciIo,
                          PciIoWidth,
                          (UINT32)AddressOffset,
                          Count,
                          BackupBuffer
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
                   L"EFI_PCI_IO_PROTOCOL.Pci.Read - Read data out",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    //write the buffer into destination address range useing common width.
    //
    Status = PciIo->Pci.Write (
                          PciIo,
                          PciIoWidth,
                          (UINT32)AddressOffset,
                          Count,
                          Buffer
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
                   gPciIoBBTestFunction_2AssertionGuid008,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - Write data to Pci config space",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[PciIoWidth]
                   );
    //
    //then read out the data in destination address range.
    //
    PciIo->Pci.Read (
                 PciIo,
                 PciIoWidth,
                 (UINT32)AddressOffset,
                 Count,
                 ReadBuffer
                 );

    AssertionType = EFI_TEST_ASSERTION_PASSED;

    //
    //the data read out must be the same as write into.

    if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //check point 2.
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciIoBBTestFunction_2AssertionGuid009,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - read out the data from pci config space with PciIoWidthUintX the data must equal with what written",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    //
    //write the data using EfiPciIoWidthFifoUintX.
    //
    Status =PciIo->Pci.Write (
                         PciIo,
                         SecondWidth,
                         (UINT32)AddressOffset,
                         Count,
                         Buffer
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
                   gPciIoBBTestFunction_2AssertionGuid010,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - write the data with EfiPciIoWidthFifoX",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[SecondWidth]
                   );

    //
    //read the data out again using EfiPciIoWidthUintX.
    //
    PciIo->Pci.Read (
                 PciIo,
                 PciIoWidth,
                 (UINT32)AddressOffset,
                 Count,
                 ReadBuffer
                 );

    //
    //the first data unit must be the last data unit and
    //the other data unchange.
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;

    if (SctCompareMem ((UINT8 *)ReadBuffer, (UINT8 *)Buffer + (Count - 1) * UnitLength, UnitLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    if (Count > 1) {
      if (SctCompareMem ((UINT8 *)ReadBuffer + UnitLength, (UINT8 *)Buffer + UnitLength, AddressLength - UnitLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciIoBBTestFunction_2AssertionGuid011,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - with PciIoWidthFifoUintX the first data unit must be the last data unit and the other data unchange.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    //write the data using EfiPciIoWidthFillUintX.
    //
    Status =PciIo->Pci.Write (
                         PciIo,
                         ThirdWidth,
                         (UINT32)AddressOffset,
                         Count,
                         Buffer
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
                   gPciIoBBTestFunction_2AssertionGuid012,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - write the data with EfiPciIoWidthFillX",
                   L"%a:%d:Status - %r, Width - %s",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   WidthCode[ThirdWidth]
                   );


    //
    //read out the data using EfiPciIoWidthUintX.
    //
    PciIo->Pci.Read (
                 PciIo,
                 PciIoWidth,
                 (UINT32)AddressOffset,
                 Count,
                 ReadBuffer
                 );

    AssertionType = EFI_TEST_ASSERTION_PASSED;
    //
    //all the data unit read out must be the first data unit in the address  space.
    //

    for (Index = 0; Index < Count; Index++) {
      if (SctCompareMem ((UINT8 *)ReadBuffer + Index * UnitLength, Buffer, UnitLength) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        break;
      }
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPciIoBBTestFunction_2AssertionGuid013,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - with PciIoWidthFillX all the data unit read out must be the first data unit in the address space",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    //at last write the data back.
    //
    Status = PciIo->Pci.Write (
                          PciIo,
                          PciIoWidth,
                          (UINT32)AddressOffset,
                          Count,
                          BackupBuffer
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
                   gPciIoBBTestFunction_2AssertionGuid014,
                   L"EFI_PCI_IO_PROTOCOL.Pci.Write - write data back with EfiPciIoWidthX",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    //free resource.
    //
    gtBS->FreePool (Buffer);
    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (BackupBuffer);
  }

  //
  //free resources.
  //
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
 *  Entrypoint for PciIo->CopyMem () Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.11
//
EFI_STATUS
EFIAPI
CopyMem_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  UINT64                                SrcAddressOffset;
  UINT64                                DestAddressOffset;
  UINT8                                 SrcBarIndex;
  UINT8                                 DestBarIndex;
  EFI_PCI_IO_PROTOCOL_WIDTH             PciIoWidth;
  UINT32                                AddressLength;
  UINT32                                UnitLength;
  UINTN                                 Index;
  UINTN                                 SubIndex;
  UINTN                                 RepeatIndex;
  UINTN                                 RepeatNum;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  UINT32                                BufferSize;
  VOID                                  *ReadBuffer;
  UINTN                                 Count;
  EFI_TEST_ASSERTION                    AssertionType;
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
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.CopyMem - not found the Profile.",
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
                         SECTION_NAME_COPYMEM_TEST,
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
               SECTION_NAME_COPYMEM_TEST,
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
    //get SrcBarIndex and Offset.
    //
    SrcBarIndex = 0;
    Status = GetSrcBarIndexByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_TEST,
               RepeatIndex,
               &SrcBarIndex
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    SrcAddressOffset = 0;
    Status = GetSrcAddressOffsetByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_TEST,
               RepeatIndex,
               &SrcAddressOffset
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //get DestBarIndex and Offset.
    //

    DestBarIndex = 0;
    Status = GetDestBarIndexByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_TEST,
               RepeatIndex,
               &DestBarIndex
               );
    if (EFI_ERROR(Status)) {
      DestBarIndex = SrcBarIndex;
    }
    if (DestBarIndex == SrcBarIndex) {
      DestAddressOffset = SrcAddressOffset;
    } else {
      DestAddressOffset = 0;
      Status = GetDestAddressOffsetByFile (
                 FileHandle,
                 SECTION_NAME_COPYMEM_TEST,
                 RepeatIndex,
                 &DestAddressOffset
                 );
      if (EFI_ERROR(Status)) {
        continue;
      }
    }
    //
    //get Width.
    //
    PciIoWidth = 0;
    Status = GetPciIoWidthByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_TEST,
               RepeatIndex,
               &PciIoWidth
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    switch (PciIoWidth) {
      case EfiPciIoWidthUint8:
        UnitLength  = 1;
        break;
      case EfiPciIoWidthUint16:
        UnitLength  = 2;
        break;
      case EfiPciIoWidthUint32:
        UnitLength  = 4;
        break;
      default:
        UnitLength  = 8;
        break;
    }
    //
    //get address length.
    //
    AddressLength = 0;
    Status = GetAddressLengthByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_TEST,
               RepeatIndex,
               &AddressLength
               );
    if (EFI_ERROR(Status)) {
      continue;
    }
    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }
    AddressLength = (UINT32)(Count * UnitLength);

    if (SrcBarIndex == DestBarIndex) {
      if (Count < 3) {
        continue;
      }
      BufferSize    = AddressLength / 2;
      Count      = BufferSize / UnitLength;
      BufferSize = (UINT32)(Count * UnitLength);
      if (Count == 0) {
        continue;
      }
    } else {
      BufferSize = AddressLength;
    }
    //
    //verify the BarIndex and Offset is valid for this device.
    //
    if (!CheckBarAndRange (PciIoDevice, CHECK_TYPE_MEM, SrcBarIndex, SrcAddressOffset + AddressLength) ||
        !CheckBarAndRange (PciIoDevice, CHECK_TYPE_MEM, DestBarIndex, DestAddressOffset + AddressLength)) {
      //
      //log message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"the BarIndex/Offset is invalid for this Pci Device.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      continue;
    }

    //
    //get Data Units.
    //
    Buffer = NULL;

    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_COPYMEM_TEST,
               RepeatIndex,
               BufferSize,
               &Buffer
               );
    if (EFI_ERROR(Status)) {
      Buffer = (UINT8 *)SctAllocatePool (BufferSize);
      if (Buffer == NULL) {
        gtBS->FreePool (PciDevicePathStr);
        ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );
        return EFI_OUT_OF_RESOURCES;
      }
      //
      //else fill the buffer with rondom data.
      //
      for (Index = 0; Index < BufferSize; Index++) {
        Buffer[Index] = (UINT8)(Index & 0xFF);
      }
    }
    //
    //allocate read buffer.
    //
    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (BufferSize);
    if (ReadBuffer == NULL) {
      gtBS->FreePool (Buffer);
      gtBS->FreePool (PciDevicePathStr);
      ProfileLib->EfiIniClose (
                    ProfileLib,
                    FileHandle
                    );
      return EFI_OUT_OF_RESOURCES;
    }
    RepeatNum = 1;
    if (SrcBarIndex >= 0 && SrcBarIndex <=5) {
      RepeatNum = 2;
    }

    for (SubIndex = 0; SubIndex < RepeatNum; SubIndex++) {
      if (SubIndex == 1) {
        SrcAddressOffset  = PciIoDevice->BarAddress[SrcBarIndex] + SrcAddressOffset;
        SrcBarIndex   = EFI_PCI_IO_PASS_THROUGH_BAR;
        if (DestBarIndex >= 0 && DestBarIndex<= 5) {
          DestAddressOffset = PciIoDevice->BarAddress[DestBarIndex] + DestAddressOffset;
          DestBarIndex  = EFI_PCI_IO_PASS_THROUGH_BAR;
        }
      }

      if ((SrcBarIndex == DestBarIndex) && (SrcBarIndex != EFI_PCI_IO_PASS_THROUGH_BAR)) {
        //
        //check point for 4.1.11.2.1 .CopyMem within the same BAR.
        //

        //
        //first write the buffer into the beginning address.
        //
        Status = PciIo->Mem.Write (
                              PciIo,
                              PciIoWidth,
                              SrcBarIndex,
                              SrcAddressOffset,
                              Count,
                              Buffer
                              );

        if (EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTestGenericFailureGuid,
                       L"EFI_PCI_IO_PROTOCOL.Mem.Write - Write data to memory address space",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );

        //
        //Copying Data between non-overlapping regions.
        //
        Status = PciIo->CopyMem (
                          PciIo,
                          PciIoWidth,
                          DestBarIndex,
                          DestAddressOffset + BufferSize,
                          SrcBarIndex,
                          SrcAddressOffset,
                          Count
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
                       gPciIoBBTestFunction_2AssertionGuid015,
                       L"EFI_PCI_IO_PROTOCOL.CopyMem - Copying Data between non-overlapping regions.",
                       L"%a:%d:Status - %r, SrcBarIndex - %2xh, SrcOffset - %lXh, DstBarIndex - %2xh, DstOffset - %lXh, PciIoWidth - %s, Count - %xh",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       SrcBarIndex,
                       SrcAddressOffset,
                       DestBarIndex,
                       DestAddressOffset + BufferSize,
                       WidthCode[PciIoWidth],
                       (UINT32)Count
                       );
        //
        //then read out the data compare if they are equal with what have been write.
        //
        Status =PciIo->Mem.Read (
                             PciIo,
                             PciIoWidth,
                             DestBarIndex,
                             DestAddressOffset + BufferSize,
                             Count,
                             ReadBuffer
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
                       L"EFI_PCI_IO_PROTOCOL.Mem.Read - read out copied data.",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );

        AssertionType = EFI_TEST_ASSERTION_PASSED;
        if (SctCompareMem (ReadBuffer, Buffer, BufferSize) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        //
        //record assertion
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gPciIoBBTestFunction_2AssertionGuid016,
                       L"EFI_PCI_IO_PROTOCOL.CopyMem - Copying Data between non-overlapping regions the data should be equal",
                       L"%a:%d",
                       __FILE__,
                       (UINTN)__LINE__
                       );
        //
        //copy data between overlap regions with destination address > source address.
        //

        Status = PciIo->CopyMem (
                          PciIo,
                          PciIoWidth,
                          DestBarIndex,
                          DestAddressOffset + BufferSize / 2,
                          SrcBarIndex,
                          SrcAddressOffset,
                          Count
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
                       gPciIoBBTestFunction_2AssertionGuid017,
                       L"EFI_PCI_IO_PROTOCOL.CopyMem - Copying Data between overlapping regions dest address > source address.",
                       L"%a:%d:Status - %r, SrcBarIndex - %2xh, SrcOffset - %lXh, DstBarIndex - %2xh, DstOffset - %lXh, PciIoWidth - %s, Count - %xh",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status ,
                       SrcBarIndex,
                       SrcAddressOffset,
                       DestBarIndex,
                       DestAddressOffset + BufferSize/2,
                       WidthCode[PciIoWidth],
                       (UINT32)Count
                       );
        //
        //then read out the data compare if they are equal with what have been copied.
        //
        Status =PciIo->Mem.Read (
                             PciIo,
                             PciIoWidth,
                             DestBarIndex,
                             DestAddressOffset + BufferSize / 2,
                             Count,
                             ReadBuffer
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
                       L"EFI_PCI_IO_PROTOCOL.Mem.Read - read out copied data.",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );

        AssertionType = EFI_TEST_ASSERTION_PASSED;
        if (SctCompareMem (ReadBuffer, Buffer, BufferSize) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        //
        //record assertion
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gPciIoBBTestFunction_2AssertionGuid018,
                       L"EFI_PCI_IO_PROTOCOL.CopyMem - Copying Data between overlapping regions (Dest > source) the data should be really copied",
                       L"%a:%d",
                       __FILE__,
                       (UINTN)__LINE__
                       );

        //
        //copy data between over-lapping region with dest address < src address.
        //
        Status = PciIo->CopyMem (
                          PciIo,
                          PciIoWidth,
                          DestBarIndex,
                          DestAddressOffset,
                          SrcBarIndex,
                          SrcAddressOffset + BufferSize / 2,
                          Count
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
                       gPciIoBBTestFunction_2AssertionGuid019,
                       L"EFI_PCI_IO_PROTOCOL.CopyMem - Copying Data between overlapping regions dest address < source address.",
                       L"%a:%d:Status - %r, SrcBarIndex - %2xh, SrcOffset - %lXh, DstBarIndex - %2xh, DstOffset - %lXh, PciIoWidth - %s, Count - %xh",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       SrcBarIndex,
                       SrcAddressOffset + BufferSize / 2,
                       DestBarIndex,
                       DestAddressOffset,
                       WidthCode[PciIoWidth],
                       (UINT32)Count
                       );
        //
        //then read out the data compare if they are equal with what have been write.
        //
        Status =PciIo->Mem.Read (
                             PciIo,
                             PciIoWidth,
                             DestBarIndex,
                             DestAddressOffset,
                             Count,
                             ReadBuffer
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
                       L"EFI_PCI_IO_PROTOCOL.Mem.Read - read out copied data.",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );

        AssertionType = EFI_TEST_ASSERTION_PASSED;
        if (SctCompareMem (ReadBuffer, Buffer, BufferSize) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        //
        //record assertion
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gPciIoBBTestFunction_2AssertionGuid020,
                       L"EFI_PCI_IO_PROTOCOL.CopyMem - Copying Data between overlapping regions (Dest < source) the data should be really copied",
                       L"%a:%d",
                       __FILE__,
                       (UINTN)__LINE__
                       );
      } else {
        //
        //check point 4.1.11.2.2 copy memory between addresses in different BARs.
        //

        //
        //first write the buffer into Src address.
        //
        Status = PciIo->Mem.Write (
                              PciIo,
                              PciIoWidth,
                              SrcBarIndex,
                              SrcAddressOffset,
                              Count,
                              Buffer
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
                       EFI_TEST_ASSERTION_PASSED,
                       gTestGenericFailureGuid,
                       L"EFI_PCI_IO_PROTOCOL.Mem.Write - Write data to memory address space",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );

        //
        //Copying Data between different BARs.
        //
        Status = PciIo->CopyMem (
                          PciIo,
                          PciIoWidth,
                          DestBarIndex,
                          DestAddressOffset,
                          SrcBarIndex,
                          SrcAddressOffset,
                          Count
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
                       gPciIoBBTestFunction_2AssertionGuid021,
                       L"EFI_PCI_IO_PROTOCOL.CopyMem - Copying Data between different BARs.",
                       L"%a:%d:Status - %r, SrcBarIndex - %2xh, SrcOffset - %lXh, DstBarIndex - %2xh, DstOffset - %lXh, PciIoWidth - %s, Count - %xh",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status ,
                       SrcBarIndex,
                       SrcAddressOffset,
                       DestBarIndex,
                       DestAddressOffset,
                       WidthCode[PciIoWidth],
                       (UINT32)Count
                       );
        //
        //then read out the data compare if they are equal
        //with what have been write.
        //
        Status =PciIo->Mem.Read (
                             PciIo,
                             PciIoWidth,
                             DestBarIndex,
                             DestAddressOffset,
                             Count,
                             ReadBuffer
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
                       L"EFI_PCI_IO_PROTOCOL.Mem.Read - read out copied data.",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );

        AssertionType = EFI_TEST_ASSERTION_PASSED;
        if (SctCompareMem (ReadBuffer, Buffer, BufferSize) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        //
        //record assertion
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gPciIoBBTestFunction_2AssertionGuid022,
                       L"EFI_PCI_IO_PROTOCOL.CopyMem - Copying Data between different BARs the data should be really copied",
                       L"%a:%d",
                       __FILE__,
                       (UINTN)__LINE__
                       );

      }
      //
      //end else.
      //

    }

    //
    //free resource.
    //
    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (Buffer);

  }

  //
  //free resource.
  //

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
 *  Entrypoint for PciIo->Map() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.12
//
EFI_STATUS
EFIAPI
Map_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  VOID                                  *HostAddress;
  UINTN                                 NumberOfBytes;
  EFI_PHYSICAL_ADDRESS                  DeviceAddress;
  VOID                                  *Mapping;
  EFI_PCI_IO_PROTOCOL_OPERATION         Operation;
  UINTN                                 Index;
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
  //check point 4.1.12.2.1 Map() wih Bus Master Read.
  //

  //
  //allocate a buffer (4K + 1 Bytes)
  //
  BufferSize = 4 * 1024 + 1;
  Buffer = NULL;
  Buffer = (UINT8 *)SctAllocatePool (BufferSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //fill in this buffer with some data.
  //
  for (Index = 0; Index < BufferSize; Index++) {
    Buffer[Index] = (UINT8)(Index & 0xFF);
  }

  NumberOfBytes = BufferSize;
  Operation     = EfiPciIoOperationBusMasterRead;
  HostAddress   = (void *)Buffer;
  Status = PciIo->Map (
                    PciIo,
                    Operation,
                    HostAddress,
                    &NumberOfBytes,
                    (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                    &Mapping
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
                 gPciIoBBTestFunction_2AssertionGuid023,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Read",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (NumberOfBytes > 0) {
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
                 gPciIoBBTestFunction_2AssertionGuid024,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Read mapped bytes should > 0",
                 L"%a:%d:NumberOfBytes - %lxh",
                 __FILE__,
                 (UINTN)__LINE__,
                 (UINT64)NumberOfBytes
                 );

  if (SctCompareMem ((VOID *)Buffer, (VOID *)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_2AssertionGuid025,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Read the mapped area should equal with original area",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  //
  //Unmap this area.
  //
  Status = PciIo->Unmap (
                    PciIo,
                    Mapping
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
                 L"EFI_PCI_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Read",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (Buffer);

  //
  //check point 4.1.12.2.2 Map() wih Bus Master Write.
  //

  //
  //allocate a buffer (4K + 1 Bytes)
  //
  BufferSize = 4 * 1024 + 1;
  Buffer = NULL;
  Buffer = (UINT8 *)SctAllocatePool (BufferSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  NumberOfBytes = BufferSize;
  Operation     = EfiPciIoOperationBusMasterWrite;
  HostAddress   = (void *)Buffer;
  gtBS->SetMem (HostAddress, BufferSize, 0x0);

  Status = PciIo->Map (
                    PciIo,
                    Operation,
                    HostAddress,
                    &NumberOfBytes,
                    (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                    &Mapping
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
                 gPciIoBBTestFunction_2AssertionGuid026,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Write",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  if (NumberOfBytes > 0) {
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
                 gPciIoBBTestFunction_2AssertionGuid027,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Write mapped bytes should > 0",
                 L"%a:%d:NumberOfBytes - %lxh",
                 __FILE__,
                 (UINTN)__LINE__,
                 (UINT64)NumberOfBytes
                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index = 0 ;Index < BufferSize; Index++) {
    if (Buffer[Index] != (UINT8)0x0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      break;
    }
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_2AssertionGuid028,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Write original data remain unchanged just after mapped",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  //
  //Unmap this area.
  //
  Status = PciIo->Unmap (
                    PciIo,
                    Mapping
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
                 L"EFI_PCI_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Write",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  gtBS->FreePool (Buffer);

  //
  //check point 4.1.12.2.3 Map() with Bus Master Common Buffer
  //

  //
  //first allocate 2 page with Pci Io protocol.
  //
  Buffer = NULL;
  Status = PciIo->AllocateBuffer (
                    PciIo,
                    AllocateAnyPages,
                    EfiBootServicesData,
                    2,
                    (VOID **) &Buffer,
                    0
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  BufferSize = 2 * 4 * 1024;
  //
  //fill in buffer with some fixed  data.
  //
  gtBS->SetMem (Buffer, BufferSize, 0x0);

  //
  //map with operation as EfiPciIoOperationBusMasterCommonBuffer.
  //
  NumberOfBytes = BufferSize;
  Operation     = EfiPciIoOperationBusMasterCommonBuffer;
  HostAddress   = (void *)Buffer;

  Status = PciIo->Map (
                    PciIo,
                    Operation,
                    HostAddress,
                    &NumberOfBytes,
                    (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                    &Mapping
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
                 gPciIoBBTestFunction_2AssertionGuid030,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Common Buffer",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (NumberOfBytes > 0) {
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
                 gPciIoBBTestFunction_2AssertionGuid031,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Common Buffer mapped bytes should > 0",
                 L"%a:%d:NumberOfBytes - %lxh",
                 __FILE__,
                 (UINTN)__LINE__,
                 (UINT64)NumberOfBytes
                 );

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (SctCompareMem ((VOID *)Buffer, (VOID *)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_2AssertionGuid032,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Common Buffer the mapped area should equal with the original area after mapped",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );
  //
  //Fill in Mapped address with some fixed data.
  //
  gtBS->SetMem ((VOID *)(UINTN)DeviceAddress, NumberOfBytes, 0x1);

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (SctCompareMem ((VOID *)Buffer, (VOID *)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_2AssertionGuid033,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Common Buffer the original area should sync with the mapped area",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  //
  //Fill in original address with some fixed data.
  //
  gtBS->SetMem (Buffer, NumberOfBytes, 0x0);

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (SctCompareMem ((VOID *)Buffer, (VOID *)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }


  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_2AssertionGuid034,
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Common Buffer the mapped area should sync with original area",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  //
  //Unmap this area.
  //
  Status = PciIo->Unmap (
                    PciIo,
                    Mapping
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
                 L"EFI_PCI_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Common Read",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //at last free buffer
  //
  PciIo->FreeBuffer (
           PciIo,
           2,
           Buffer
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS.",
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
 *  Entrypoint for PciIo->Unmap() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.13
//
EFI_STATUS
EFIAPI
Unmap_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  VOID                                  *HostAddress;
  UINTN                                 NumberOfBytes;
  EFI_PHYSICAL_ADDRESS                  DeviceAddress;
  VOID                                  *Mapping;
  EFI_PCI_IO_PROTOCOL_OPERATION         Operation;
  UINTN                                 Index;
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
  //check point 4.1.13.2.1 Unmap() area that mapped wih Bus Master Read.
  //

  //
  //allocate a buffer (4K + 1 Bytes)
  //
  BufferSize = 4 * 1024 + 1;
  Buffer = NULL;
  Buffer = (UINT8 *)SctAllocatePool (BufferSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  //
  //fill in this buffer with some data.
  //
  gtBS->SetMem (Buffer, BufferSize, 0x0);

  NumberOfBytes = BufferSize;
  Operation     = EfiPciIoOperationBusMasterRead;
  HostAddress   = (void *)Buffer;

  Status = PciIo->Map (
                    PciIo,
                    Operation,
                    HostAddress,
                    &NumberOfBytes,
                    (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                    &Mapping
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
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Read",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //Unmap this area.
  //
  Status = PciIo->Unmap (
                    PciIo,
                    Mapping
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
                 gPciIoBBTestFunction_2AssertionGuid035,
                 L"EFI_PCI_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Read",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //the content of buffer will not be changed.
  //
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index = 0; Index < BufferSize; Index++) {
    if (Buffer[Index] != (UINT8)0x0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      break;
    }
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_2AssertionGuid036,
                 L"EFI_PCI_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Read the original area should remain unchanged after Unmap",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );


  gtBS->FreePool (Buffer);

  //
  //check point 4.1.13.2.2 Unmap() area that mapped wih Bus Master Write.
  //

  //
  //allocate a buffer (4K + 1 Bytes)
  //
  BufferSize = 4 * 1024 + 1;
  Buffer = NULL;
  Buffer = (UINT8 *)SctAllocatePool (BufferSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  NumberOfBytes = BufferSize;
  Operation     = EfiPciIoOperationBusMasterWrite;
  HostAddress   = (void *)Buffer;

  Status = PciIo->Map (
                    PciIo,
                    Operation,
                    HostAddress,
                    &NumberOfBytes,
                    (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                    &Mapping
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
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Write",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //fill in maped address some data.
  //

  for (Index = 0 ;Index < NumberOfBytes; Index++) {
    ((UINT8 *)(UINTN)DeviceAddress)[Index] = (UINT8)(Index & 0xFF);
  }

  //
  //Unmap this area.
  //
  Status = PciIo->Unmap (
                    PciIo,
                    Mapping
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
                 gPciIoBBTestFunction_2AssertionGuid037,
                 L"EFI_PCI_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Write",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //the content of buffer will be changed.
  //

  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index = 0; Index < NumberOfBytes; Index++) {
    if (Buffer[Index] != (UINT8)(Index & 0xFF)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      break;
    }
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_2AssertionGuid038,
                 L"EFI_PCI_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Write the original area should equal with the data written in mapped area",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  gtBS->FreePool (Buffer);

  //
  //check point 4.1.13.2.3 Unmap() area that mapped with Bus Master Common Buffer
  //

  //
  //first allocate 2 page with Pci Io protocol.
  //
  Buffer = NULL;
  Status = PciIo->AllocateBuffer (
                    PciIo,
                    AllocateAnyPages,
                    EfiBootServicesData,
                    2,
                    (VOID **) &Buffer,
                    0
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  BufferSize = 2 * 4 * 1024;
  //
  //fill in buffer with some fixed  data.
  //
  gtBS->SetMem (Buffer, BufferSize, 0x0);

  //
  //map with operation as EfiPciIoOperationBusMasterCommonBuffer.
  //
  NumberOfBytes = BufferSize;
  Operation     = EfiPciIoOperationBusMasterCommonBuffer;
  HostAddress   = (VOID *)Buffer;
  Status = PciIo->Map (
                    PciIo,
                    Operation,
                    HostAddress,
                    &NumberOfBytes,
                    (EFI_PHYSICAL_ADDRESS *)&DeviceAddress,
                    &Mapping
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
                 L"EFI_PCI_IO_PROTOCOL.Map - Map wih Bus Master Common Buffer",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //Fill in Mapped address with some fixed data.
  //
  gtBS->SetMem ((UINT8 *)(UINTN)DeviceAddress, NumberOfBytes, 0x01);

  if (SctCompareMem (Buffer, (VOID *)(UINTN)DeviceAddress, NumberOfBytes) == 0) {
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
                 L"EFI_PCI_IO_PROTOCOL.Map - CommonBuffer the Data in original area should sync with the mapped area",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  //
  //Unmap this area.
  //
  Status = PciIo->Unmap (
                    PciIo,
                    Mapping
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
                 gPciIoBBTestFunction_2AssertionGuid039,
                 L"EFI_PCI_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Common Read",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //the content of buffer will not be changed.
  //
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  for (Index = 0; Index < NumberOfBytes; Index++) {
    if (Buffer[Index] != (UINT8)0x01) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      break;
    }
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_2AssertionGuid040,
                 L"EFI_PCI_IO_PROTOCOL.Unmap - Unmap area Mapped wih Bus Master Common Read the original area should remain unchanged after Unmap",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  //
  //at last free buffer
  //
  PciIo->FreeBuffer (
           PciIo,
           2,
           Buffer
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
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS.",
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
 *  Entrypoint for PciIo->AllocateBuffer() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.14
//
EFI_STATUS
EFIAPI
AllocateBuffer_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_STATUS                            EfiStatus;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_MEMORY_TYPE                       MemoryType[2];
  UINT64                                Attributes[4];
  UINTN                                 MemoryTypeIndex;
  UINTN                                 AttributesIndex;


  MemoryType[0] = EfiBootServicesData;
  MemoryType[1] = EfiRuntimeServicesData;

  Attributes[0] = 0;
  Attributes[1] = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE;
  Attributes[2] = EFI_PCI_ATTRIBUTE_MEMORY_CACHED;
  Attributes[3] = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE | EFI_PCI_ATTRIBUTE_MEMORY_CACHED;

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

  EfiStatus = EFI_SUCCESS;

  for (MemoryTypeIndex = 0; MemoryTypeIndex < 2; MemoryTypeIndex++) {
    for (AttributesIndex = 0; AttributesIndex < 4; AttributesIndex++) {

      Status = PciIo->AllocateBuffer (
                        PciIo,
                        0,
                        MemoryType[MemoryTypeIndex],
                        2,
                        (VOID **) &Buffer,
                        Attributes[AttributesIndex]
                        );

      //
      //record message
      //
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"EFI_PCI_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS.\r\n"
                     L"%a:%d:Status - %r, MemoryType - %p, Attributes - %lx\r\n",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     (VOID*)MemoryTypeCode[MemoryType[MemoryTypeIndex]],
                     (UINT64)Attributes[AttributesIndex]
                     );

      if (EFI_ERROR(Status)) {
        EfiStatus = Status;
      } else {
        PciIo->FreeBuffer (PciIo, 2, Buffer);
      }
    }
  }

  if (!EFI_ERROR(EfiStatus)) {
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
                 gPciIoBBTestFunction_2AssertionGuid041,
                 L"EFI_PCI_IO_PROTOCOL.AllocateBuffer - with corrent Parameter Status must be EFI_SUCCESS.",
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
 *  Entrypoint for PciIo->FreeBuffer() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.15
//
EFI_STATUS
EFIAPI
FreeBuffer_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_STATUS                            EfiStatus;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  UINT8                                 *Buffer;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_MEMORY_TYPE                       MemoryType[2];
  UINT64                                Attributes[4];
  UINTN                                 MemoryTypeIndex;
  UINTN                                 AttributesIndex;


  MemoryType[0] = EfiBootServicesData;
  MemoryType[1] = EfiRuntimeServicesData;

  Attributes[0] = 0;
  Attributes[1] = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE;
  Attributes[2] = EFI_PCI_ATTRIBUTE_MEMORY_CACHED;
  Attributes[3] = EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE | EFI_PCI_ATTRIBUTE_MEMORY_CACHED;

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

  EfiStatus = EFI_SUCCESS;

  for (MemoryTypeIndex = 0; MemoryTypeIndex < 2; MemoryTypeIndex++) {
    for (AttributesIndex = 0; AttributesIndex < 4; AttributesIndex++) {

      Status = PciIo->AllocateBuffer (
                        PciIo,
                        0,
                        MemoryType[MemoryTypeIndex],
                        2,
                        (VOID **) &Buffer,
                        Attributes[AttributesIndex]
                        );


      if (!EFI_ERROR(Status)) {
        Status = PciIo->FreeBuffer (PciIo, 2, Buffer);

        //
        //record message
        //
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"EFI_PCI_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS.\r\n"
                       L"%a:%d:Status - %r, MemoryType - %p, Attributes - %lx\r\n",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       (VOID *)MemoryTypeCode[MemoryType[MemoryTypeIndex]],
                       (UINT64)Attributes[AttributesIndex]
                       );

        if (EFI_ERROR(Status)) {
          EfiStatus = Status;
        }
      }
    }
  }

  if (!EFI_ERROR(EfiStatus)) {
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
                 gPciIoBBTestFunction_2AssertionGuid042,
                 L"EFI_PCI_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS.",
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
 *  Entrypoint for PciIo->Flush() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.16
//
EFI_STATUS
EFIAPI
Flush_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
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

  Status = PciIo->Flush(PciIo);

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
                 gPciIoBBTestFunction_2AssertionGuid043,
                 L"EFI_PCI_IO_PROTOCOL.Flush - the status must be EFI_SUCCESS.",
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
 *  Entrypoint for PciIo->GetLocation() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.17
//
EFI_STATUS
EFIAPI
GetLocation_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
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

  Status = PciIo->GetLocation (
                    PciIo,
                    &SegNumber,
                    &BusNumber,
                    &DevNumber,
                    &FuncNumber
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
                 gPciIoBBTestFunction_2AssertionGuid044,
                 L"EFI_PCI_IO_PROTOCOL.GetLocation - the status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (BusNumber < 256) {
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
                 gPciIoBBTestFunction_2AssertionGuid045,
                 L"EFI_PCI_IO_PROTOCOL.GetLocation - Bus Number < 256.",
                 L"%a:%d:Bus Number - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 BusNumber
                 );

  if (DevNumber < 32) {
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
                 gPciIoBBTestFunction_2AssertionGuid046,
                 L"EFI_PCI_IO_PROTOCOL.GetLocation - Device Number < 32.",
                 L"%a:%d:Device Number - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 DevNumber
                 );
  if (FuncNumber < 8) {
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
                 gPciIoBBTestFunction_2AssertionGuid047,
                 L"EFI_PCI_IO_PROTOCOL.GetLocation - Function Number < 8.",
                 L"%a:%d:Function Number - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 FuncNumber
                 );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->Attributes() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.18
//
EFI_STATUS
EFIAPI
Attributes_Func (
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
  UINT64                                SupportedAttributes;
  UINT64                                OriginalAttributes;
  UINT64                                CommonAttributes;

  UINT64                                ThisAttributes1;
  UINT64                                ThisAttributes2;
  UINT64                                ThisAttributes3;
  UINT64                                ThisAttributes4;

  EFI_STATUS                            StatusSet1;
  EFI_STATUS                            StatusSet2;
  EFI_STATUS                            StatusEnable1;
  EFI_STATUS                            StatusDisable1;

  UINT64                                AttributesGet1;
  UINT64                                AttributesGet2;
  UINT64                                AttributesGet3;
  UINT64                                AttributesGet4;
  CHAR16                               *DevicePathStr;

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
//  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
//  if (EFI_ERROR(Status)) {
//    return Status;
//  }


  DevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);
  if (DevicePathStr == NULL) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCannot get DevicePath"
                   );
  } else {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: %s",
                   DevicePathStr
                   );
    gtBS->FreePool (DevicePathStr);
  }

  //
  //call Attributes with operation EfiPciIoAttributeOperationGet to
  //get current attributes.
  //
  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationGet,
                    0,
                    &OriginalAttributes
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
                 gPciIoBBTestFunction_2AssertionGuid048,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Get current attribute status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r, Current Attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 OriginalAttributes
                 );
  //
  //call Attribtes with operation EfiPciIoAttributeOperationSupported to
  //get the supported attributes of the pci controller.
  //

  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationSupported,
                    0,
                    &SupportedAttributes
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
                 gPciIoBBTestFunction_2AssertionGuid049,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Get supported attribute status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r, Supported Attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 SupportedAttributes
                 );

  if ((OriginalAttributes & SupportedAttributes) == OriginalAttributes) {
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
                 gPciIoBBTestFunction_2AssertionGuid050,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - current attriutes should in supported attributes",
                 L"%a:%d:Current Attributes - %lXh, Supported Attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 OriginalAttributes,
                 SupportedAttributes
                 );

  //
  //call Attributes to Set all the supportd attributes.
  //
  ThisAttributes1 = SupportedAttributes;

  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationSet,
                    ThisAttributes1,
                    NULL
                    );
  //
  //call Attributes to get current attribute to verify the attributes is really
  //set
  //
  PciIo->Attributes (
           PciIo,
           EfiPciIoAttributeOperationGet,
           0,
           &CommonAttributes
           );

  if (!EFI_ERROR(Status) && ThisAttributes1 == CommonAttributes) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //set original attributes before output to console
  //
  PciIo->Attributes (
           PciIo,
           EfiPciIoAttributeOperationSet,
           OriginalAttributes,
           NULL
           );
  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPciIoBBTestFunction_2AssertionGuid051,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Set Attributes as Supported attributes rerutn status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r, Supported Attributes - %lXh, Set attributes - %lXh, Current Attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 SupportedAttributes,
                 ThisAttributes1,
                 CommonAttributes
                 );

  //
  // Clear all attributes will affect the IDE system. So the LOG information
  // will be recorded after the attributes recovered.
  //

  //
  //call Attributes to clear all the attributes.
  //
  ThisAttributes1 = 0;

  StatusSet1 = PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationSet,
                        ThisAttributes1,
                        NULL
                        );

  //
  //call Attributes to get current attribute to verify the attributes is really
  //clear
  //
  PciIo->Attributes (
           PciIo,
           EfiPciIoAttributeOperationGet,
           0,
           &AttributesGet1
           );

  //
  //call Attributes to enable original attributes
  //
  ThisAttributes2 = OriginalAttributes;

  StatusEnable1 = PciIo->Attributes (
                           PciIo,
                           EfiPciIoAttributeOperationEnable,
                           ThisAttributes2,
                           NULL
                           );

  //
  //call Attributes to get current attribute to verify the attributes is really
  //Enabled
  //
  PciIo->Attributes (
           PciIo,
           EfiPciIoAttributeOperationGet,
           0,
           &AttributesGet2
           );

  //
  //call Attributes to Disable original attributes
  //
  ThisAttributes3 = OriginalAttributes;

  StatusDisable1 = PciIo->Attributes (
                            PciIo,
                            EfiPciIoAttributeOperationDisable,
                            ThisAttributes3,
                            NULL
                            );

  //
  //call Attributes to get current attribute to verify the attributes is really
  //Disabled
  //
  PciIo->Attributes (
           PciIo,
           EfiPciIoAttributeOperationGet,
           0,
           &AttributesGet3
           );

  //
  //call Attributes to restore original attributes.
  //
  ThisAttributes4 = OriginalAttributes;

  StatusSet2 = PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationSet,
                        ThisAttributes4,
                        NULL
                        );

  //
  //call Attributes to get current attribute to verify the attributes is really
  //Set
  //
  PciIo->Attributes (
           PciIo,
           EfiPciIoAttributeOperationGet,
           0,
           &AttributesGet4
           );

  //
  // Start to record all LOG information
  //

  if (!EFI_ERROR(StatusSet1)) {
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
                 gPciIoBBTestFunction_2AssertionGuid053,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Set Attributes as 0 rerutn status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusSet1
                 );

  if (ThisAttributes1 == AttributesGet1) {
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
                 gPciIoBBTestFunction_2AssertionGuid054,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Set attribute as 0 the attributes should really be cleared",
                 L"%a:%d:Set attributes - %lXh, Current Attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 ThisAttributes1,
                 AttributesGet1
                 );

  if (!EFI_ERROR(StatusEnable1)) {
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
                 gPciIoBBTestFunction_2AssertionGuid055,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Enable Attributes as original attributes rerutn status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusEnable1
                 );

  if (ThisAttributes2 == AttributesGet2) {
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
                 gPciIoBBTestFunction_2AssertionGuid056,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Enable attribute as original attributes the attributes should really be enabled",
                 L"%a:%d:Original Attributes - %lXh, Enabled attributes - %lXh, Current Attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 OriginalAttributes,
                 ThisAttributes2,
                 AttributesGet2
                 );

  if (!EFI_ERROR(StatusDisable1)) {
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
                 gPciIoBBTestFunction_2AssertionGuid057,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Disable original attributes rerutn status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusDisable1
                 );

  if (AttributesGet3 == 0) {
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
                 gPciIoBBTestFunction_2AssertionGuid058,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Disable original attributes the attributes should really be disabled",
                 L"%a:%d:Original Attributes - %lXh, Disabled attributes - %lXh, Current Attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 OriginalAttributes,
                 ThisAttributes3,
                 AttributesGet3
                 );

  if (!EFI_ERROR(StatusSet2)) {
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
                 gPciIoBBTestFunction_2AssertionGuid059,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Set original attributes rerutn status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 StatusSet2
                 );

  if (ThisAttributes4 == AttributesGet4) {
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
                 gPciIoBBTestFunction_2AssertionGuid060,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Set original attributes the attributes should really be set",
                 L"%a:%d:Original Attributes - %lXh, Set attributes - %lXh, Current Attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 OriginalAttributes,
                 ThisAttributes4,
                 AttributesGet4
                 );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->GetBarAttributes() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.19
//
EFI_STATUS
EFIAPI
GetBarAttributes_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 Index;
  UINT8                                 BarIndex;
  UINT64                                DevSupportedAttributes;
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
  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  InitializeCaseEnvironment ();

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //check point 4.1.19.2.1 call GetBarAttributes to get Bar Resources.
  //

  //
  //found a Bar.
  //
  BarIndex = REGNUM;

  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index]) {
      BarIndex = (UINT8)Index;
      break;
    }
  }

  if (BarIndex == REGNUM) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.SetBarAttributes - Not found a valid Bar.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return EFI_SUCCESS;
  }

  BarOriginalAttributes = 0;
  Resources = NULL;

  Status = PciIo->GetBarAttributes (
                    PciIo,
                    BarIndex,
                    &BarOriginalAttributes,
                    &Resources
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
                 gPciIoBBTestFunction_2AssertionGuid061,
                 L"EFI_PCI_IO_PROTOCOL.GetBarAttributes - return status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 BarIndex
                 );

  Status = PciIo->GetBarAttributes (
                    PciIo,
                    BarIndex,
                    NULL,
                    &Resources
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
                 gPciIoBBTestFunction_2AssertionGuid062,
                 L"EFI_PCI_IO_PROTOCOL.GetBarAttributes - with only Supports is NULL, return status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 BarIndex
                 );

  Status = PciIo->GetBarAttributes (
                    PciIo,
                    BarIndex,
                    &BarOriginalAttributes,
                    NULL
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
                 gPciIoBBTestFunction_2AssertionGuid063,
                 L"EFI_PCI_IO_PROTOCOL.GetBarAttributes - with only Resource is NULL, return status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r, BarIndex - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 BarIndex
                 );

  if (IsValidResourceDescrptor (Resources)) {
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
                 gPciIoBBTestFunction_2AssertionGuid064,
                 L"EFI_PCI_IO_PROTOCOL.GetBarAttributes - the Resource Descriptor List must be valid",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  //
  //free the resources if necessory.
  //
  if (!EFI_ERROR(Status)) {
    gtBS->FreePool (Resources);
  }

  //
  //get device supported attributes.
  //
  Status =  PciIo->Attributes (
                     PciIo,
                     EfiPciIoAttributeOperationSupported,
                     0,
                     &DevSupportedAttributes
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
                 L"EFI_PCI_IO_PROTOCOL.Attributes - get supported attribute the status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ((BarOriginalAttributes & DevSupportedAttributes) == BarOriginalAttributes) {
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
                 gPciIoBBTestFunction_2AssertionGuid065,
                 L"EFI_PCI_IO_PROTOCOL.GetBarAttributes - the attributes must in Device Supported Attributes.",
                 L"%a:%d:Supported Attributes - %lXh, Bar Attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 DevSupportedAttributes,
                 BarOriginalAttributes
                 );

  //
  //done successfully
  //

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->SetBarAttributes() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.20
//
EFI_STATUS
EFIAPI
SetBarAttributes_Func (
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
  VOID                                  *Resources;
  UINT64                                ThisAttributes;


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
  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  InitializeCaseEnvironment ();

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //check point 4.1.20.2.1 call SetBarAttributes to set Bar Resources attribute.
  //
  BarIndex = 6;
  for (Index = 0; Index < REGNUM; Index++) {
    if (PciIoDevice->BarHasEffect[Index]) {
      BarIndex = (UINT8)Index;
      break;
    }
  }

  if (BarIndex == 6) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PCI_IO_PROTOCOL.SetBarAttributes - Not found a valid Bar.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return EFI_SUCCESS;
  }

  BarOriginalAttributes = 0;
  Resources = NULL;

  Status = PciIo->GetBarAttributes (
                    PciIo,
                    BarIndex,
                    &BarOriginalAttributes,
                    &Resources
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
                 L"EFI_PCI_IO_PROTOCOL.GetBarAttributes - return status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //free the resources if necessory.
  //
  if (!EFI_ERROR(Status)) {
    gtBS->FreePool (Resources);
  }

  //
  //call SetBarAttributes with Bar supported attributes
  //
  AddressOffset = 0;
  AddressLength = PciIoDevice->BarLength[BarIndex];
  ThisAttributes = BarOriginalAttributes;
  if (ThisAttributes != 0) {

    Status = PciIo->SetBarAttributes (
                      PciIo,
                      ThisAttributes,
                      BarIndex,
                      &AddressOffset,
                      &AddressLength
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
                   gPciIoBBTestFunction_2AssertionGuid066,
                   L"EFI_PCI_IO_PROTOCOL.SetBarAttributes - Set Bar supported attributes return Staus Must be EFI_SUCCESS.",
                   L"%a:%d:Status - %r, SetAttributes - %lXh, Bar Supported Attributes - %lXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   ThisAttributes,
                   BarOriginalAttributes
                   );
  } else {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"EFI_PCI_IO_PROTOCOL.SetBarAttributes -bar supported attributes is 0.\r\n"
                   L"%a:%d:BarIndex - %02xh, Supported Attributes - %lXh.\r\n",
                   __FILE__,
                   (UINTN)__LINE__,
                   BarIndex,
                   BarOriginalAttributes
                   );

  }
  //
  //done successfully
  //
  return EFI_SUCCESS;
}
