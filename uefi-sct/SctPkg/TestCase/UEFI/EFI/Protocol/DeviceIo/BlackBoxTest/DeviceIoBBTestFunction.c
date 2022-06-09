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

  DeviceIoBBTestFunction.c

Abstract:

  function test source file for Device Io protocol

--*/

#include "SctLib.h"
#include "DeviceIoBBTestMain.h"
#include EFI_PROTOCOL_DEFINITION (PciIo)
#include "DeviceIoBBTestSupport.h"

#define  SECTION_NAME_MEMREAD_BASIC_TEST       L"MemRead_Func"
#define  SECTION_NAME_MEMWRITE_BASIC_TEST      L"MemWrite_Func"
#define  SECTION_NAME_IOREAD_BASIC_TEST        L"IoRead_Func"
#define  SECTION_NAME_IOWRITE_BASIC_TEST       L"IoWrite_Func"
#define  SECTION_NAME_PCIREAD_BASIC_TEST       L"PciRead_Func"
#define  SECTION_NAME_PCIWRITE_BASIC_TEST      L"PciWrite_Func"

/**
 *  Entrypoint for Mem.Read()Interface Automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.1
//
EFI_STATUS
EFIAPI
MemRead_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  UINT32                                  AddressLength;
  EFI_DEVICE_IO_PROTOCOL                 *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            EfiIoWidth;
  UINT32                                  UnitLength;
  UINTN                                   Index;
  VOID                                    *BackupBuffer;
  VOID                                    *ReadBuffer;
  UINTN                                   Count;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;


  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  //
  // Get the test Supported Library Interface
  //

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  //
  //print the device path.
  //
  Status = GetDevIoDevicePathStr (DeviceIo, &DevIoDevicePathStr);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //open the ini file.
  //

  Status = OpenTestIniFile (ProfileLib, &FileHandle);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - Not Found the Profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_MEMREAD_BASIC_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - Not found item for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index ++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_BASIC_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for BaseAddress, Width and Length.
    //
    BaseAddress = 0;
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_BASIC_TEST,
               Index,
               &BaseAddress
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    Status = GetValidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_BASIC_TEST,
               Index,
               &EfiIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (EfiIoWidth) {
      case IO_UINT8:
        UnitLength  = 1;
        break;

      case IO_UINT16:
        UnitLength  = 2;
        break;

      case IO_UINT32:
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
               SECTION_NAME_MEMREAD_BASIC_TEST,
               Index,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }

    AddressLength = (UINT32)(Count * UnitLength);

    //
    //allocate read buffer.
    //

    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //allocate BackupBuffer.
    //

    BackupBuffer = NULL;
    BackupBuffer = SctAllocatePool (AddressLength);
    if (BackupBuffer == NULL) {
      gtBS->FreePool (ReadBuffer);
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //first read the data out.
    //

    Status = DeviceIo->Mem.Read (
                             DeviceIo,
                             EfiIoWidth,
                             BaseAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid001,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - Read data out",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );

    //
    //then read out the data in destination address range.
    //

    Status =DeviceIo->Mem.Read (
                            DeviceIo,
                            EfiIoWidth,
                            BaseAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid002,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - read out the data from the address space",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );
    //
    //the data read out must be the same as previous.
    //
    if (SctCompareMem (ReadBuffer, BackupBuffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestFunctionAssertionGuid003,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - the data read out must be the same as previous",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    //free resource.
    //

    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (ReadBuffer);
  }

  //
  //done successfully.
  //
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Mem.Write()Interface Automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.2
//
EFI_STATUS
EFIAPI
MemWrite_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  UINT32                                  AddressLength;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            EfiIoWidth;
  UINT32                                  UnitLength;
  UINTN                                   SubIndex;
  UINTN                                   Index;
  UINT8                                   *Buffer;
  VOID                                    *BackupBuffer;
  VOID                                    *ReadBuffer;
  UINTN                                   Count;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;


  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  //
  // Get the test Supported Library Interface
  //

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  //
  //print the device path.
  //
  Status = GetDevIoDevicePathStr (DeviceIo, &DevIoDevicePathStr);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //open the ini file.
  //

  Status = OpenTestIniFile (ProfileLib, &FileHandle);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Write - Not Found the Profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_MEMWRITE_BASIC_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Write - Not found item for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index ++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_BASIC_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for BaseAddress, Width and Length.
    //
    BaseAddress = 0;
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_BASIC_TEST,
               Index,
               &BaseAddress
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    Status = GetValidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_BASIC_TEST,
               Index,
               &EfiIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (EfiIoWidth) {
      case IO_UINT8:
        UnitLength  = 1;
        break;

      case IO_UINT16:
        UnitLength  = 2;
        break;

      case IO_UINT32:
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
               SECTION_NAME_MEMWRITE_BASIC_TEST,
               Index,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }

    AddressLength = (UINT32)(Count * UnitLength);

    //
    //create data units by program.
    //

    Buffer = (UINT8 *)SctAllocatePool (AddressLength + UnitLength);
    if (Buffer == NULL) {
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
      return EFI_OUT_OF_RESOURCES;
    }

    for (SubIndex = 0; SubIndex < AddressLength; SubIndex ++) {
      Buffer[SubIndex] = (UINT8)(SubIndex & 0xFF);
    }


    //
    //allocate read buffer.
    //

    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      gtBS->FreePool (Buffer);
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
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
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //first read the data out.
    //

    Status = DeviceIo->Mem.Read (
                             DeviceIo,
                             EfiIoWidth,
                             BaseAddress,
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
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - Read data out",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );

    //
    // write the buffer into destination address range.
    //

    Status =DeviceIo->Mem.Write (
                            DeviceIo,
                            EfiIoWidth,
                            BaseAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid004,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Write - Write data to memory address space",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );

    //
    //then read out the data in destination address range.
    //

    Status =DeviceIo->Mem.Read (
                            DeviceIo,
                            EfiIoWidth,
                            BaseAddress,
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
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - read out the data from the address space",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );
    //
    //the data read out must be the same as write into.
    //
    if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestFunctionAssertionGuid005,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Write - the data read out must be the same as what written",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );


    //
    //at last restore the data
    //

    Status =DeviceIo->Mem.Write (
                            DeviceIo,
                            EfiIoWidth,
                            BaseAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid006,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Write - Write back Data.",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );

    //
    //free resource.
    //

    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (Buffer);
  }

  //
  //done successfully.
  //
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Io.Read()Interface Automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.3
//
EFI_STATUS
EFIAPI
IoRead_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  UINT32                                  AddressLength;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            EfiIoWidth;
  UINT32                                  UnitLength;
  UINTN                                   Index;
  VOID                                    *BackupBuffer;
  VOID                                    *ReadBuffer;
  UINTN                                   Count;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;


  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  //
  // Get the test Supported Library Interface
  //

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  //
  //print the device path.
  //
  Status = GetDevIoDevicePathStr (DeviceIo, &DevIoDevicePathStr);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //open the ini file.
  //

  Status = OpenTestIniFile (ProfileLib, &FileHandle);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Read - Not Found the Profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_IOREAD_BASIC_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Read - no Item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index ++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
               FileHandle,
               SECTION_NAME_IOREAD_BASIC_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for BaseAddress, Width and Length.
    //
    BaseAddress = 0;
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_IOREAD_BASIC_TEST,
               Index,
               &BaseAddress
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    Status = GetValidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOREAD_BASIC_TEST,
               Index,
               &EfiIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (EfiIoWidth) {
      case IO_UINT8:
        UnitLength  = 1;
        break;

      case IO_UINT16:
        UnitLength  = 2;
        break;

      case IO_UINT32:
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
               SECTION_NAME_IOREAD_BASIC_TEST,
               Index,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }

    AddressLength = (UINT32)(Count * UnitLength);

    //
    //allocate read buffer.
    //

    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //allocate BackupBuffer.
    //

    BackupBuffer = NULL;
    BackupBuffer = SctAllocatePool (AddressLength);

    if (BackupBuffer == NULL) {
      gtBS->FreePool (ReadBuffer);
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //first read the data out.
    //

    Status = DeviceIo->Io.Read (
                            DeviceIo,
                            EfiIoWidth,
                            BaseAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid007,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Read - Read data out",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );

    //
    //then read out the data in destination address range.
    //

    Status =DeviceIo->Io.Read (
                           DeviceIo,
                           EfiIoWidth,
                           BaseAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid008,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Read - read out the data from the address space",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );
    //
    //the data read out must be the same as previous.
    //
    if (SctCompareMem (ReadBuffer, BackupBuffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestFunctionAssertionGuid009,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Read - the data read out must be the same as previous",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    //free resource.
    //

    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (ReadBuffer);
  }

  //
  //done successfully.
  //
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Io.Write ()Interface Automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.4
//
EFI_STATUS
EFIAPI
IoWrite_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  UINT32                                  AddressLength;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            EfiIoWidth;
  UINT32                                  UnitLength;
  UINTN                                   SubIndex;
  UINTN                                   Index;
  UINT8                                   *Buffer;
  VOID                                    *BackupBuffer;
  VOID                                    *ReadBuffer;
  UINTN                                   Count;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;


  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  //
  // Get the test Supported Library Interface
  //

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  //
  //print the device path.
  //
  Status = GetDevIoDevicePathStr (DeviceIo, &DevIoDevicePathStr);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //open the ini file.
  //

  Status = OpenTestIniFile (ProfileLib, &FileHandle);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Write - Not Found the Profile.",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_IOWRITE_BASIC_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Write - no Item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index ++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_BASIC_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for BaseAddress, Width and Length.
    //
    BaseAddress = 0;
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_BASIC_TEST,
               Index,
               &BaseAddress
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    Status = GetValidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_BASIC_TEST,
               Index,
               &EfiIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (EfiIoWidth) {
      case IO_UINT8:
        UnitLength  = 1;
        break;

      case IO_UINT16:
        UnitLength  = 2;
        break;

      case IO_UINT32:
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
               SECTION_NAME_IOWRITE_BASIC_TEST,
               Index,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }

    AddressLength = (UINT32)(Count * UnitLength);

    //
    //create data units by program.
    //

    Buffer = (UINT8 *)SctAllocatePool (AddressLength + UnitLength);
    if (Buffer == NULL) {
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
      return EFI_OUT_OF_RESOURCES;
    }

    for (SubIndex = 0; SubIndex < AddressLength; SubIndex ++) {
      Buffer[SubIndex] = (UINT8)(SubIndex & 0xFF);
    }


    //
    //allocate read buffer.
    //

    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      gtBS->FreePool (Buffer);
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
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
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //first read the data out.
    //

    Status = DeviceIo->Io.Read (
                            DeviceIo,
                            EfiIoWidth,
                            BaseAddress,
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
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Read - Read data out",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );

    //
    // write the buffer into destination address range.
    //

    Status =DeviceIo->Io.Write (
                           DeviceIo,
                           EfiIoWidth,
                           BaseAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid010,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Write - Write data to Io address space",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );

    //
    //then read out the data in destination address range.
    //

    Status =DeviceIo->Io.Read (
                           DeviceIo,
                           EfiIoWidth,
                           BaseAddress,
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
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Read - read out the data from the address space",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );
    //
    //the data read out must be the same as write into.
    //

    if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestFunctionAssertionGuid011,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Write - the data read out must be the same as what written",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );


    //
    //at last restore the data
    //

    Status =DeviceIo->Io.Write (
                           DeviceIo,
                           EfiIoWidth,
                           BaseAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid012,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Write - Write back Data.",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );

    //
    //free resource.
    //

    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (Buffer);
  }

  //
  //done successfully.
  //
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Pci.Read()Interface Automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.5
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
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  UINT32                                  AddressLength;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            EfiIoWidth;
  UINT32                                  UnitLength;
  UINTN                                   Index;
  UINT8                                   *Buffer;
  VOID                                    *ReadBuffer;
  UINTN                                   Count;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;


  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  //
  // Get the test Supported Library Interface
  //

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  //
  //print the device path.
  //
  Status = GetDevIoDevicePathStr (DeviceIo, &DevIoDevicePathStr);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //open the ini file.
  //

  Status = OpenTestIniFile (ProfileLib, &FileHandle);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - Not Found the Profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_PCIREAD_BASIC_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - No Item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index ++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_BASIC_TEST,
               Index,
               &TempDevicePathStr
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for BaseAddress, Width and Length.
    //
    BaseAddress = 0;
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_BASIC_TEST,
               Index,
               &BaseAddress
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    Status = GetValidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_BASIC_TEST,
               Index,
               &EfiIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (EfiIoWidth) {
      case IO_UINT8:
        UnitLength  = 1;
        break;

      case IO_UINT16:
        UnitLength  = 2;
        break;

      case IO_UINT32:
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
               SECTION_NAME_PCIREAD_BASIC_TEST,
               Index,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }

    AddressLength = (UINT32)(Count * UnitLength);

    //
    //get user input data unit.
    //
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_BASIC_TEST,
               Index,
               AddressLength,
               &Buffer
               );

    if(EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - Error in get user input data units",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    //allocate read buffer.
    //

    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      gtBS->FreePool (Buffer);
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
      return EFI_OUT_OF_RESOURCES;
    }


    //
    //then read out the data in destination address range.
    //

    Status =DeviceIo->Pci.Read (
                            DeviceIo,
                            EfiIoWidth,
                            BaseAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid013,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - read out the data from the address space",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );
    //
    //the data read out must be the same as assigned data units
    //

    if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestFunctionAssertionGuid014,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - the data read out must be the same as assgnged data units",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );


    //
    //free resource.
    //

    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (Buffer);
  }

  //
  //done successfully.
  //
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Pci.Write() Interface Automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.6
//
EFI_STATUS
EFIAPI
PciWrite_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  UINT32                                  AddressLength;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            EfiIoWidth;
  UINT32                                  UnitLength;
  UINTN                                   Index;
  UINT8                                   *Buffer;
  VOID                                    *BackupBuffer;
  VOID                                    *ReadBuffer;
  UINTN                                   Count;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;

  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  //
  // Get the test Supported Library Interface
  //

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  //
  //print the device path.
  //
  Status = GetDevIoDevicePathStr (DeviceIo, &DevIoDevicePathStr);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //open the ini file.
  //

  Status = OpenTestIniFile (ProfileLib, &FileHandle);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Write - Not Found the Profile.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_PCIWRITE_BASIC_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Write - no item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index ++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_BASIC_TEST,
               Index,
               &TempDevicePathStr
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //if the device path not equal then ignore this test section.
    //

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for BaseAddress, Width and Length.
    //
    BaseAddress = 0;
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_BASIC_TEST,
               Index,
               &BaseAddress
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //get width
    //

    Status = GetValidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_BASIC_TEST,
               Index,
               &EfiIoWidth
               );

    if (EFI_ERROR(Status)) {
      continue;
    }

    switch (EfiIoWidth) {
      case IO_UINT8:
        UnitLength  = 1;
        break;

      case IO_UINT16:
        UnitLength  = 2;
        break;

      case IO_UINT32:
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
               SECTION_NAME_PCIWRITE_BASIC_TEST,
               Index,
               &AddressLength
               );

    Count  = 0;
    Count  = AddressLength / UnitLength;
    if (Count == 0) {
      continue;
    }

    AddressLength = (UINT32)(Count * UnitLength);

    //
    //create data units by program.
    //
    //
    //get user input data unit.
    //
    Status = GetDataUnitsByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_BASIC_TEST,
               Index,
               AddressLength,
               &Buffer
               );

    if(EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"EFI_DEVICE_IO_PROTOCOL.Pci.Write - Error in get user input data units",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      continue;
    }

    //
    //allocate read buffer.
    //

    ReadBuffer = NULL;
    ReadBuffer = SctAllocatePool (AddressLength);
    if (ReadBuffer == NULL) {
      gtBS->FreePool (Buffer);
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
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
      CloseTestIniFile (ProfileLib, FileHandle);
      gtBS->FreePool (DevIoDevicePathStr);
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //first read the data out.
    //

    Status = DeviceIo->Pci.Read (
                             DeviceIo,
                             EfiIoWidth,
                             BaseAddress,
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
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - Read data out",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );

    //
    // write the buffer into destination address range.
    //

    Status =DeviceIo->Pci.Write (
                            DeviceIo,
                            EfiIoWidth,
                            BaseAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid015,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Write - Write data to Pci Configuration address space",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );

    //
    //then read out the data in destination address range.
    //

    Status =DeviceIo->Pci.Read (
                            DeviceIo,
                            EfiIoWidth,
                            BaseAddress,
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
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - read out the data from the address space",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );
    //
    //the data read out must be the same as write into.
    //

    if (SctCompareMem (ReadBuffer, Buffer, AddressLength) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }  else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestFunctionAssertionGuid016,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Write - the data read out must be the same as what written",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );


    //
    //at last restore the data
    //

    Status =DeviceIo->Pci.Write (
                            DeviceIo,
                            EfiIoWidth,
                            BaseAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid017,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Write - Write back Data.",
                   L"%a:%d:Status - %r, Address - %lXh, Width - %08xh, Count - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress,
                   EfiIoWidth,
                   Count
                   );

    //
    //free resource.
    //

    gtBS->FreePool (BackupBuffer);
    gtBS->FreePool (ReadBuffer);
    gtBS->FreePool (Buffer);
  }

  //
  //done successfully.
  //
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Map() interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.7
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
  EFI_STATUS                                   Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL           *ProfileLib;
  EFI_PHYSICAL_ADDRESS                         HostAddress;
  UINTN                                        NumberOfBytes;
  EFI_PHYSICAL_ADDRESS                         DeviceAddress;
  VOID                                         *Mapping;
  EFI_IO_OPERATION_TYPE                        Operation;
  UINTN                                        Index;
  UINTN                                        Count;
  UINT8                                        *Buffer;
  UINTN                                        BufferSize;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_DEVICE_IO_PROTOCOL                       *DeviceIo;

  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  for(Count = 0; Count < 2; Count++) {
    switch (Count) {
      case 0:
        BufferSize = 1;
        break;
      case 1:
        BufferSize = 2;
        break;
/*
      case 2:
        BufferSize = 1023;
        break;
      case 3:
        BufferSize = 1024;
        break;
      case 4:
        BufferSize = 1025;
        break;
*/
      default:
        BufferSize = 1;
    }

    //
    //check point 4.1.7.2.1 Map() with Bus Master Read.
    //

    //
    //allocate a buffer
    //

    Buffer = NULL;
    Buffer = (UINT8 *)SctAllocatePool (BufferSize);
    if (Buffer == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    //fill in this buffer with some data.
    //

    for (Index = 0; Index < BufferSize; Index ++) {
      Buffer[Index] = (UINT8)(Index & 0xFF);
    }

    NumberOfBytes = BufferSize;
    Operation     = EfiBusMasterRead;
    HostAddress   = (UINT64)Buffer;

    Status = DeviceIo->Map (
                         DeviceIo,
                         Operation,
                         &HostAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid018,
                   L"EFI_DEVICE_IO_PROTOCOL.Map - Map with Bus Master Read",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if ((NumberOfBytes == 0) && (BufferSize > 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestFunctionAssertionGuid019,
                   L"EFI_DEVICE_IO_PROTOCOL.Map - NumberOfByte should not be zero except map zero buffer",
                   L"%a:%d:NumberOfBytes - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   NumberOfBytes
                   );

    if (NumberOfBytes > BufferSize) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestFunctionAssertionGuid020,
                   L"EFI_DEVICE_IO_PROTOCOL.Map - NumberOfByte should not greater than bufferSize",
                   L"%a:%d:NumberOfBytes - %08xh, BufferSize - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   NumberOfBytes,
                   BufferSize
                   );

    //
    // Remove the memory values checking since we cannot make the assumption
    // that the mapped address returned from the device is the same as the CPU
    // IO address. Large systems may have more than one way of accessing the
    // IO space from the CPU or from the device.
    //
    /*
    if (SctCompareMem ((VOID*)Buffer, (VOID*)(UINTN)DeviceAddress, NumberOfBytes) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestFunctionAssertionGuid021,
                   L"EFI_DEVICE_IO_PROTOCOL.Map - the mapped data must be the same as original data",
                   L"%a:%d",
                   __FILE__,
                   __LINE__
                   );
    */

    //
    //Unmap this area.
    //
    if (!EFI_ERROR(Status)) {
      Status = DeviceIo->Unmap (
                           DeviceIo,
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
                     L"EFI_DEVICE_IO_PROTOCOL.Unmap - Unmap area Mapped with Bus Master Read",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
    gtBS->FreePool (Buffer);

    //
    //check point 4.1.7.2.2 Map() with Bus Master Write.
    //

    //
    //allocate a buffer
    //

    Buffer = NULL;
    Buffer = (UINT8 *)SctAllocatePool (BufferSize);
    if (Buffer == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    NumberOfBytes = BufferSize;
    Operation     = EfiBusMasterWrite;
    HostAddress   = (UINT64)Buffer;
    gtBS->SetMem (Buffer, BufferSize, 0);

    Status = DeviceIo->Map (
                         DeviceIo,
                         Operation,
                         &HostAddress,
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
                   gDeviceIoBBTestFunctionAssertionGuid022,
                   L"EFI_DEVICE_IO_PROTOCOL.Map - Map with Bus Master Write",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    if ((NumberOfBytes == 0) && (BufferSize > 0)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestFunctionAssertionGuid023,
                   L"EFI_DEVICE_IO_PROTOCOL.Map - NumberOfBytes should not be zero except map zero buffer",
                   L"%a:%d:NumberOfBytes - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   NumberOfBytes
                   );

    if (NumberOfBytes > BufferSize) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestFunctionAssertionGuid024,
                   L"EFI_DEVICE_IO_PROTOCOL.Map - NumberOfBytes should not greater than BufferSize",
                   L"%a:%d:NumberOfBytes - %08xh, BufferSize - %08xh",
                   __FILE__,
                   (UINTN)__LINE__,
                   NumberOfBytes,
                   BufferSize
                   );

    //
    //original area data remain unchanged after mapping
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for (Index = 0 ;Index < NumberOfBytes; Index ++) {
      if (Buffer[Index] != (UINT8)0) {
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
                   gDeviceIoBBTestFunctionAssertionGuid025,
                   L"EFI_DEVICE_IO_PROTOCOL.Map - the original area should remain unchanged just after mapping.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    //Unmap this area.
    //
    if (!EFI_ERROR(Status)) {
      Status = DeviceIo->Unmap (
                           DeviceIo,
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
                     L"EFI_DEVICE_IO_PROTOCOL.Unmap - Unmap area Mapped with Bus Master Write",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
    gtBS->FreePool (Buffer);
  }
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Unmap() Interface automatically Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.1.8
//
EFI_STATUS
Unmap_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                                   Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL           *ProfileLib;
  EFI_PHYSICAL_ADDRESS                         HostAddress;
  UINTN                                        NumberOfBytes;
  EFI_PHYSICAL_ADDRESS                         DeviceAddress;
  VOID                                         *Mapping;
  EFI_IO_OPERATION_TYPE                        Operation;
  UINTN                                        Index;
  UINT8                                        *Buffer;
  UINTN                                        BufferSize;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_DEVICE_IO_PROTOCOL                       *DeviceIo;

  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  //
  //check point 4.1.8.2.1 Unmap() area that mapped with Bus Master Read.
  //

  //
  //allocate a buffer (1K Bytes)
  //
  BufferSize = 2;
  Buffer = NULL;
  Buffer = (UINT8 *)SctAllocatePool (BufferSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //fill in this buffer with some data.
  //

  for (Index = 0; Index < BufferSize; Index ++) {
    Buffer[Index] = (UINT8)(Index & 0xFF);
  }

  NumberOfBytes = BufferSize;
  Operation     = EfiBusMasterRead;
  HostAddress   = (UINT64)Buffer;

  Status = DeviceIo->Map (
                       DeviceIo,
                       Operation,
                       &HostAddress,
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
                 L"EFI_DEVICE_IO_PROTOCOL.Map - Map with Bus Master Read",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //Unmap this area.
  //

  Status = DeviceIo->Unmap (
                       DeviceIo,
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
                 gDeviceIoBBTestFunctionAssertionGuid032,
                 L"EFI_DEVICE_IO_PROTOCOL.Unmap - Unmap area Mapped with Bus Master Read",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //the content of buffer will not be changed.
  //

  AssertionType = EFI_TEST_ASSERTION_PASSED;

  for (Index = 0; Index < BufferSize; Index ++) {
    if(Buffer[Index] != (UINT8)(Index & 0xFF)) {
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
                 gDeviceIoBBTestFunctionAssertionGuid033,
                 L"EFI_DEVICE_IO_PROTOCOL.Unmap - the data in original area remain unchanged after Unmap",
                 L"%a:%d:",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  gtBS->FreePool (Buffer);

  //
  //check point 4.1.8.2.2 Unmap() area that mapped with Bus Master Write.
  //

  //
  //allocate a buffer (1K Bytes)
  //
  BufferSize = 2;
  Buffer = NULL;
  Buffer = (UINT8 *)SctAllocatePool (BufferSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  NumberOfBytes = BufferSize;
  Operation     = EfiBusMasterWrite;
  HostAddress   = (UINT64)Buffer;

  Status = DeviceIo->Map (
                       DeviceIo,
                       Operation,
                       &HostAddress,
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
                 L"EFI_DEVICE_IO_PROTOCOL.Map - Map with Bus Master Write",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //fill in maped address some data.
  //
  if (NumberOfBytes > 0) {
    for (Index = 0 ;Index < NumberOfBytes; Index ++) {
      ((UINT8 *)(UINTN)DeviceAddress)[Index] = (UINT8)(Index & 0xFF);
    }
  }
  //
  //Unmap this area.
  //
  Status = DeviceIo->Unmap (
                       DeviceIo,
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
                 gDeviceIoBBTestFunctionAssertionGuid034,
                 L"EFI_DEVICE_IO_PROTOCOL.Unmap - Unmap area Mapped with Bus Master Write",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //the content of buffer will be changed.
  //
  AssertionType = EFI_TEST_ASSERTION_PASSED;

  for (Index = 0; Index < NumberOfBytes; Index ++) {
    if(Buffer[Index] != (UINT8)(Index & 0xFF)) {
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
                 gDeviceIoBBTestFunctionAssertionGuid035,
                 L"EFI_DEVICE_IO_PROTOCOL.Unmap - the data in original area should be same as the data in mapped area after unmap",
                 L"%a:%d",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  gtBS->FreePool (Buffer);

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for AllocateBuffer() Interface automatically Test.
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
AllocateBuffer_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                                   Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL           *ProfileLib;
  EFI_PHYSICAL_ADDRESS                         HostAddress;
  UINT8                                        *Buffer;
  EFI_PHYSICAL_ADDRESS                         OriginalHostAddress;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_ALLOCATE_TYPE                            AllocateType[3];
  EFI_MEMORY_TYPE                              MemoryType[2];
  UINTN                                        AllocateTypeNum;
  UINTN                                        MemoryTypeNum;
  EFI_DEVICE_IO_PROTOCOL                       *DeviceIo;
  CHAR16                                       *DevIoDevicePathStr;
  UINTN                                        AllocatedPages;


  AllocateType[0] = AllocateAnyPages;
  AllocateType[1] = AllocateMaxAddress;
  AllocateType[2] = AllocateAddress;

  MemoryType[0] = EfiBootServicesData;
  MemoryType[1] = EfiRuntimeServicesData;

  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  //
  // Get the test Supported Library Interface
  //

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  //
  //print the device path.
  //
  Status = GetDevIoDevicePathStr (DeviceIo, &DevIoDevicePathStr);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  AllocatedPages = 1;

  for (AllocateTypeNum = 0; AllocateTypeNum < 3; AllocateTypeNum++)     {
    for (MemoryTypeNum = 0; MemoryTypeNum < 2; MemoryTypeNum ++)      {
      OriginalHostAddress = 0;

      if (AllocateType[AllocateTypeNum] == AllocateAddress ||
          AllocateType[AllocateTypeNum] == AllocateMaxAddress  ) {

        //
        //allocate buffer using AllocateAnyPages type and then free it
        //
        Buffer = NULL;

        Status = DeviceIo->AllocateBuffer (
                             DeviceIo,
                             AllocateAnyPages,
                             MemoryType[MemoryTypeNum],
                             AllocatedPages,
                             (VOID **) &HostAddress
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
                       gDeviceIoBBTestFunctionAssertionGuid038,
                       L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS.",
                       L"%a:%d:Status - %r,AllocateType:%d,MemoryType:%d,AllocatedPage:%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       (UINT32)AllocateAnyPages,
                       (UINT32)MemoryType[MemoryTypeNum],
                       AllocatedPages
                       );

        if (EFI_ERROR(Status)) {
          continue;
        }

        OriginalHostAddress = HostAddress;

        Status = DeviceIo->FreeBuffer (
                             DeviceIo,
                             AllocatedPages,
                             HostAddress
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
                       L"EFI_DEVICE_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS.",
                       L"%a:%d:Status - %r,AllocateType:%d,MemoryType:%d,AllocatedPage:%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       (UINT32)AllocateAnyPages,
                       (UINT32)MemoryType[MemoryTypeNum],
                       AllocatedPages
                       );

        //
        //if allocate Max Address the Buffer point to uppermost of the address
        //

        if (AllocateType[AllocateTypeNum] == AllocateMaxAddress) {
          HostAddress = HostAddress + 4096 - 1;
          OriginalHostAddress = HostAddress;
        }
      }

      Status = DeviceIo->AllocateBuffer (
                           DeviceIo,
                           AllocateType[AllocateTypeNum],
                           MemoryType[MemoryTypeNum],
                           AllocatedPages,
                           (VOID **) &HostAddress
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
                     gDeviceIoBBTestFunctionAssertionGuid039,
                     L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS.",
                     L"%a:%d:Status - %r, AllocateType:%d, MemoryType:%d, AllocatedPage:%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     (UINT32)AllocateType[AllocateTypeNum],
                     (UINT32)MemoryType[MemoryTypeNum],
                     AllocatedPages
                     );
      if (EFI_ERROR(Status)) {
        continue;
      }

      if (AllocateType[AllocateTypeNum] == AllocateMaxAddress) {
        if (HostAddress > OriginalHostAddress) {
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
                       gDeviceIoBBTestFunctionAssertionGuid040,
                       L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - Adress must be less or equal given value.",
                       L"%a:%d:Status - %r, AllocateType:%d, MemoryType:%d, AllocatedPage:%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       AllocateType[AllocateTypeNum],
                       MemoryType[MemoryTypeNum],
                       AllocatedPages
                       );

      }
      if (AllocateType[AllocateTypeNum] == AllocateAddress) {
        if (HostAddress != OriginalHostAddress) {
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
                       gDeviceIoBBTestFunctionAssertionGuid041,
                       L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - HostAddress must not be changed.",
                       L"%a:%d:Status - %r, AllocateType:%d, MemoryType:%d, AllocatedPage:%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       (UINT32)AllocateType[AllocateTypeNum],
                       (UINT32)MemoryType[MemoryTypeNum],
                       AllocatedPages
                       );

      }

      //
      //free the buffer.
      //
      Status = DeviceIo->FreeBuffer (
                           DeviceIo,
                           AllocatedPages,
                           HostAddress
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
                     L"EFI_DEVICE_IO_PROTOCOL.FreePool - the status must be EFI_SUCCESS.",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    }
  }


  //
  //done successfully
  //
  return EFI_SUCCESS;

}

/**
 *  Entrypoint for FreeBuffer() Interface automatically Test.
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
FreeBuffer_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                                   Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL           *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL           *ProfileLib;
  EFI_PHYSICAL_ADDRESS                         HostAddress;
  UINT8                                        *Buffer;
  EFI_PHYSICAL_ADDRESS                         OriginalHostAddress;
  EFI_TEST_ASSERTION                           AssertionType;
  EFI_ALLOCATE_TYPE                            AllocateType[3];
  EFI_MEMORY_TYPE                              MemoryType[2];
  UINTN                                        AllocateTypeNum;
  UINTN                                        MemoryTypeNum;
  EFI_DEVICE_IO_PROTOCOL                       *DeviceIo;
  CHAR16                                       *DevIoDevicePathStr;

  AllocateType[0] = AllocateAnyPages;
  AllocateType[1] = AllocateMaxAddress;
  AllocateType[2] = AllocateAddress;

  MemoryType[0] = EfiBootServicesData;
  MemoryType[1] = EfiRuntimeServicesData;

  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  //
  // Get the test Supported Library Interface
  //

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  //
  //print the device path.
  //
  Status = GetDevIoDevicePathStr (DeviceIo, &DevIoDevicePathStr);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  for (AllocateTypeNum = 0; AllocateTypeNum < 3; AllocateTypeNum++)     {
    for (MemoryTypeNum = 0; MemoryTypeNum < 2; MemoryTypeNum ++)      {
      OriginalHostAddress = 0;

      if (AllocateType[AllocateTypeNum] == AllocateAddress ||
          AllocateType[AllocateTypeNum] == AllocateMaxAddress  ) {

        //
        //allocate buffer using AllocateAnyPages type and then free it
        //
        Buffer = NULL;

        Status = DeviceIo->AllocateBuffer (
                             DeviceIo,
                             AllocateAnyPages,
                             MemoryType[MemoryTypeNum],
                             1,
                             (VOID **) &HostAddress
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
                       L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS.",
                       L"%a:%d:Status - %r, AllocateType:%d, MemoryType:%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       (UINT32)AllocateAnyPages,
                       (UINT32)MemoryType[MemoryTypeNum]
                       );

        if (EFI_ERROR(Status)) {
          continue;
        }

        OriginalHostAddress = HostAddress;

        Status = DeviceIo->FreeBuffer (
                             DeviceIo,
                             1,
                             HostAddress
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
                       gDeviceIoBBTestFunctionAssertionGuid042,
                       L"EFI_DEVICE_IO_PROTOCOL.FreeBuffer - Status must be EFI_SUCCESS.",
                       L"%a:%d:Status - %r, AllocateType:%d, MemoryType:%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       (UINT32)AllocateAnyPages,
                       (UINT32)MemoryType[MemoryTypeNum]
                       );

        //
        //if allocate Max Address the Buffer point to uppermost of the address
        //

        if (AllocateType[AllocateTypeNum] == AllocateMaxAddress) {
          HostAddress = HostAddress + 4096 - 1;
          OriginalHostAddress = HostAddress;
        }
      }

      Status = DeviceIo->AllocateBuffer (
                           DeviceIo,
                           AllocateType[AllocateTypeNum],
                           MemoryType[MemoryTypeNum],
                           1,
                           (VOID **) &HostAddress
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
                     L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - Status must be EFI_SUCCESS.",
                     L"%a:%d:Status - %r, AllocateType:%d, MemoryType:%d",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     (UINT32)AllocateType[AllocateTypeNum],
                     (UINT32)MemoryType[MemoryTypeNum]
                     );
      if (EFI_ERROR(Status)) {
        continue;
      }

      //
      //free the buffer.
      //
      Status = DeviceIo->FreeBuffer (
                           DeviceIo,
                           1,
                           HostAddress
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
                     gDeviceIoBBTestFunctionAssertionGuid043,
                     L"EFI_DEVICE_IO_PROTOCOL.FreePool - the status must be EFI_SUCCESS.",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    }
  }
  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Flush() Interface automatically Test.
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
Flush_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_DEVICE_IO_PROTOCOL                *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_TEST_ASSERTION                    AssertionType;


  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  //
  //print the device path.
  //
  Status = GetDevIoDevicePathStr (DeviceIo, NULL);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = DeviceIo->Flush (DeviceIo);

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
                 gDeviceIoBBTestFunctionAssertionGuid044,
                 L"EFI_DEVICE_IO_PROTOCOL.Flush - the status must be EFI_SUCCESS.",
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
 *  Entrypoint for PciDevicePath() Interface automatically Test.
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
PciDevicePath_Func (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_DEVICE_IO_PROTOCOL                *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                  HandleNum;
  UINT64                                PciAddress;
  EFI_HANDLE                            *HandleBuffer;
  CHAR16                                *DevIoDevicePathStr;
  CHAR16                                *TempDevPathStr;
  CHAR16                                *PciDevPathStr;
  UINTN                                 DevicePathStrLength;
  EFI_DEVICE_PATH_PROTOCOL              *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL              *PciDevicePath;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  UINTN                                 Index;
  UINTN                                 Segment;
  UINTN                                 Bus;
  UINTN                                 Dev;
  UINTN                                 Func;


  //
  //get tested interface.
  //
  DeviceIo = (EFI_DEVICE_IO_PROTOCOL *)ClientInterface;

  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib
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

  InitializeSupportEnvironment ();

  //
  //print the device path.
  //
  Status = GetDevIoDevicePathStr (DeviceIo, &DevIoDevicePathStr);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  DevicePathStrLength = SctStrLen (DevIoDevicePathStr);

  //
  //get all pci Io Protocol Interface.
  //

  HandleNum     = 0;
  HandleBuffer = NULL;

  Status = SctLocateHandle(
             ByProtocol,
             &gBlackBoxEfiPciIoProtocolGuid,
             NULL,
             &HandleNum,
             &HandleBuffer
             );

  if (EFI_ERROR(Status) || HandleNum == 0) {
    return EFI_SUCCESS;
  }

  for (Index = 0; Index < HandleNum; Index ++) {

    //
    //locate PciIo protocol
    //
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiPciIoProtocolGuid,
                     (VOID **) &PciIo
                     );
    if (EFI_ERROR(Status)) {
      continue;
    }
    //
    //locate DevicePath
    //
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gEfiDevicePathProtocolGuid,
                     (VOID **) &DevicePath
                     );

    if (EFI_ERROR(Status)) {
      continue;
    }

    TempDevPathStr = SctDevicePathToStr (DevicePath);

    if (SctCompareMem (TempDevPathStr,
                    DevIoDevicePathStr,
                    DevicePathStrLength * sizeof(CHAR16)) != 0) {
      gtBS->FreePool (TempDevPathStr);
      continue;
    }

    Status = PciIo->GetLocation (
                      PciIo,
                      &Segment,
                      &Bus,
                      &Dev,
                      &Func
                      );

    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_WARNING,
                     gTestGenericFailureGuid,
                     L"EFI_PCI_IO_PROTOCOL.GetLocation - the status must be EFI_SUCCESS.",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      gtBS->FreePool (TempDevPathStr);
      continue;
    }

    PciAddress = SctLShiftU64 (Segment, 32) | Bus << 24 | Dev << 16 | Func << 8;

    Status = DeviceIo->PciDevicePath (
                         DeviceIo,
                         PciAddress,
                         &PciDevicePath
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
                   gDeviceIoBBTestFunctionAssertionGuid045,
                   L"EFI_DEVICE_IO_PROTOCOL.PciDevicePath - the status must be EFI_SUCCESS.",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    PciDevPathStr = SctDevicePathToStr (PciDevicePath);

    if (SctCompareMem (TempDevPathStr,
                    PciDevPathStr,
                    SctStrLen (TempDevPathStr) * sizeof(CHAR16)) == 0) {
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
                   gDeviceIoBBTestFunctionAssertionGuid046,
                   L"EFI_DEVICE_IO_PROTOCOL.PciDevicePath - the DevicePath must equal with the DevicePath located in DeviceHandle.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (TempDevPathStr);
    gtBS->FreePool (PciDevPathStr);
    gtBS->FreePool (PciDevicePath);

  }
  //
  //free the resources.
  //
  gtBS->FreePool (HandleBuffer);
  gtBS->FreePool (DevIoDevicePathStr);

  //
  //done successfully.
  //
  return EFI_SUCCESS;
}
