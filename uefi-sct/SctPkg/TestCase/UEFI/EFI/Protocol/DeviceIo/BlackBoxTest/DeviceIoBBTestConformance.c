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

  DeviceIoBBTestConformance.c

Abstract:

  conformance test source file Device Io protocol

--*/

#include "SctLib.h"
#include "DeviceIoBBTestMain.h"
#include "DeviceIoBBTestSupport.h"

#define  SECTION_NAME_MEMREAD_CONFORM_TEST   L"MemRead_Conf"
#define  SECTION_NAME_MEMWRITE_CONFORM_TEST  L"MemWrite_Conf"

#define  SECTION_NAME_IOREAD_CONFORM_TEST    L"IoRead_Conf"
#define  SECTION_NAME_IOWRITE_CONFORM_TEST   L"IoWrite_Conf"

#define  SECTION_NAME_PCIREAD_CONFORM_TEST   L"PciRead_Conf"
#define  SECTION_NAME_PCIWRITE_CONFORM_TEST  L"PciWrite_Conf"

#define SECTION_NAME_ALLOCATEBUFFER_CONFORM_TEST  L"AllocateBuffer_Conf"
#define SECTION_NAME_PCIDEVICEPATH_CONFORM_TEST   L"PciDevicePath_Conf"

/**
 *  Entrypoint for Mem.Read() conformance Automatically Test.
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
MemRead_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            ValidWidth;
  EFI_IO_WIDTH                            InvalidWidth;
  UINTN                                   Index;
  VOID                                    *Buffer;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  BOOLEAN                                 HasValidAddress;

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


  Buffer = SctAllocatePool (64);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
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
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - no found profile",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_MEMREAD_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - no item found for this test case",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  HasValidAddress = FALSE;
  BaseAddress     = 0;
  ValidWidth      = IO_UINT8;

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get DevicePath from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
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

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for Valid BaseAddress.
    //
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_CONFORM_TEST,
               Index,
               &BaseAddress
               );
    if (!EFI_ERROR(Status)) {
      HasValidAddress = TRUE;
    } else if (!HasValidAddress) {
      continue;
    }

    //
    //call Mem.Read with Width as IO_WIDTH_MAXIMUM and -1.
    //

    Status = DeviceIo->Mem.Read (
                             DeviceIo,
                             IO_WIDTH_MAXIMUM,
                             BaseAddress,
                             1,
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
                     gDeviceIoBBTestConformanceAssertionGuid001,
                     L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - With Width as IO_WIDTH_MAXIMUM return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    Status = DeviceIo->Mem.Read (
                             DeviceIo,
                             -1,
                             BaseAddress,
                             1,
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
                     gDeviceIoBBTestConformanceAssertionGuid002,
                     L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - With Width as -1 return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );


    //
    //get use input for Invalid Width.
    //
    InvalidWidth  = IO_WIDTH_MAXIMUM;

    Status = GetInvalidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMREAD_CONFORM_TEST,
               Index,
               &InvalidWidth
               );

    if (!EFI_ERROR(Status)) {
      //
      // call with the invalid width for this system assigned by tester.
      //
      Status = DeviceIo->Mem.Read (
                               DeviceIo,
                               InvalidWidth,
                               BaseAddress,
                               1,
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
                     gDeviceIoBBTestConformanceAssertionGuid003,
                     L"EFI_DEVICE_IO_PROTOCOL.Mem.Read - With Invalid Width return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r,Width - %08xh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     InvalidWidth
                     );
    }
  }

  //
  //done successfully.
  //

  gtBS->FreePool (Buffer);
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Mem.Write() conformance Automatically Test.
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
MemWrite_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            ValidWidth;
  EFI_IO_WIDTH                            InvalidWidth;
  UINTN                                   Index;
  VOID                                    *Buffer;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  BOOLEAN                                 HasValidAddress;

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


  Buffer = SctAllocatePool (64);
  if (Buffer == NULL) {
    gtBS->FreePool (DevIoDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
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
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Write - no found profile",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_MEMWRITE_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Mem.Write - not found item for this test case",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  HasValidAddress = FALSE;
  BaseAddress     = 0;
  ValidWidth      = IO_UINT8;

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get DevicePath from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
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

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for Valid BaseAddress.
    //
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_CONFORM_TEST,
               Index,
               &BaseAddress
               );
    if (!EFI_ERROR(Status)) {
      HasValidAddress = TRUE;
    } else if (!HasValidAddress) {
      continue;
    }

    //
    //call Mem.Write with Width as IO_WIDTH_MAXIMUM and -1.
    //

    Status = DeviceIo->Mem.Write (
                             DeviceIo,
                             IO_WIDTH_MAXIMUM,
                             BaseAddress,
                             1,
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
                     gDeviceIoBBTestConformanceAssertionGuid004,
                     L"EFI_DEVICE_IO_PROTOCOL.Mem.Write - With Width as IO_WIDTH_MAXIMUM return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    Status = DeviceIo->Mem.Write (
                             DeviceIo,
                             -1,
                             BaseAddress,
                             1,
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
                     gDeviceIoBBTestConformanceAssertionGuid005,
                     L"EFI_DEVICE_IO_PROTOCOL.Mem.Write - With Width as -1 return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );


    //
    //get use input for Invalid Width.
    //
    InvalidWidth  = IO_WIDTH_MAXIMUM;

    Status = GetInvalidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_MEMWRITE_CONFORM_TEST,
               Index,
               &InvalidWidth
               );

    if (!EFI_ERROR(Status)) {
      //
      // call with the invalid width for this system assigned by tester.
      //
      Status = DeviceIo->Mem.Write (
                               DeviceIo,
                               InvalidWidth,
                               BaseAddress,
                               1,
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
                     gDeviceIoBBTestConformanceAssertionGuid006,
                     L"EFI_DEVICE_IO_PROTOCOL.Mem.Write - With Invalid Width return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r,Width - %08xh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     InvalidWidth
                     );
    }
  }

  //
  //done successfully.
  //

  gtBS->FreePool (Buffer);
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Io.Read() conformance Automatically Test.
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
IoRead_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            ValidWidth;
  EFI_IO_WIDTH                            InvalidWidth;
  UINTN                                   Index;
  VOID                                    *Buffer;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  BOOLEAN                                 HasValidAddress;

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


  Buffer = SctAllocatePool (64);
  if (Buffer == NULL) {
    gtBS->FreePool (DevIoDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
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
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Read - no found profile",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_IOREAD_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Read - no item found for this test case",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  HasValidAddress = FALSE;
  BaseAddress     = 0;
  ValidWidth      = IO_UINT8;

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get DevicePath from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
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

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for Valid BaseAddress.
    //
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_IOREAD_CONFORM_TEST,
               Index,
               &BaseAddress
               );
    if (!EFI_ERROR(Status)) {
      HasValidAddress = TRUE;
    } else if (!HasValidAddress) {
      continue;
    }

    //
    //call Io.Read with Width as IO_UINT64 + 1 and -1.
    //

    Status = DeviceIo->Io.Read (
                            DeviceIo,
                            IO_UINT64 + 1,
                            BaseAddress,
                            1,
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
                     gDeviceIoBBTestConformanceAssertionGuid007,
                     L"EFI_DEVICE_IO_PROTOCOL.Io.Read - With Width as IO_UINT64 +1 return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    Status = DeviceIo->Io.Read (
                            DeviceIo,
                            -1,
                            BaseAddress,
                            1,
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
                   gDeviceIoBBTestConformanceAssertionGuid008,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Read - With Width as -1 return Status Must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    //
    //get use input for Invalid Width and.
    //
    InvalidWidth  = IO_UINT64 + 1;

    Status = GetInvalidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOREAD_CONFORM_TEST,
               Index,
               &InvalidWidth
               );

    if (!EFI_ERROR(Status)) {
      //
      // call with the invalid width for this system assigned by tester.
      //
      Status = DeviceIo->Io.Read (
                              DeviceIo,
                              InvalidWidth,
                              BaseAddress,
                              1,
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
                     gDeviceIoBBTestConformanceAssertionGuid009,
                     L"EFI_DEVICE_IO_PROTOCOL.Io.Read - With Invalid Width return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r,Width - %08xh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     InvalidWidth
                     );
    }

  }

  //
  //done successfully.
  //

  gtBS->FreePool (Buffer);
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Io.Write() conformance Automatically Test.
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
IoWrite_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            ValidWidth;
  EFI_IO_WIDTH                            InvalidWidth;
  UINTN                                   Index;
  VOID                                    *Buffer;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  BOOLEAN                                 HasValidAddress;

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


  Buffer = SctAllocatePool (64);
  if (Buffer == NULL) {
    gtBS->FreePool (DevIoDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
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
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Write - not found profile",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_IOWRITE_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Write - no item found for this test case",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  HasValidAddress = FALSE;
  BaseAddress     = 0;
  ValidWidth      = IO_UINT8;

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get DevicePath from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
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

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for Valid BaseAddress.
    //
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_CONFORM_TEST,
               Index,
               &BaseAddress
               );
    if (!EFI_ERROR(Status)) {
      HasValidAddress = TRUE;
    } else if (!HasValidAddress) {
      continue;
    }

    //
    //call Io.Write with Width as IO_UINT64 + 1 and -1.
    //

    Status = DeviceIo->Io.Write (
                            DeviceIo,
                            IO_UINT64 + 1,
                            BaseAddress,
                            1,
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
                     gDeviceIoBBTestConformanceAssertionGuid010,
                     L"EFI_DEVICE_IO_PROTOCOL.Io.Write - With Width as IO_UINT64 +1 return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

    Status = DeviceIo->Io.Write (
                            DeviceIo,
                            -1,
                            BaseAddress,
                            1,
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
                   gDeviceIoBBTestConformanceAssertionGuid011,
                   L"EFI_DEVICE_IO_PROTOCOL.Io.Write - With Width as -1 return Status Must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    //
    //get use input for Invalid Width.
    //
    InvalidWidth  = IO_UINT64 + 1;

    Status = GetInvalidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_IOWRITE_CONFORM_TEST,
               Index,
               &InvalidWidth
               );

    if (!EFI_ERROR(Status)) {
      //
      // call with the invalid width for this system assigned by tester.
      //
      Status = DeviceIo->Io.Write (
                              DeviceIo,
                              InvalidWidth,
                              BaseAddress,
                              1,
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
                     gDeviceIoBBTestConformanceAssertionGuid012,
                     L"EFI_DEVICE_IO_PROTOCOL.Io.Write - With Invalid Width return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r,Width - %08xh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     InvalidWidth
                     );
    }
  }

  //
  //done successfully.
  //

  gtBS->FreePool (Buffer);
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for Pci.Read() conformance Automatically Test.
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
PciRead_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            ValidWidth;
  EFI_IO_WIDTH                            InvalidWidth;
  UINTN                                   Index;
  VOID                                    *Buffer;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  BOOLEAN                                 HasValidAddress;

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


  Buffer = SctAllocatePool (64);
  if (Buffer == NULL) {
    gtBS->FreePool (DevIoDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
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
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - not found profile",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_PCIREAD_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - no item found for this test case",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  HasValidAddress = FALSE;
  BaseAddress     = 0;
  ValidWidth      = IO_UINT8;

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get DevicePath from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
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

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for Valid BaseAddress.
    //
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_CONFORM_TEST,
               Index,
               &BaseAddress
               );
    if (!EFI_ERROR(Status)) {
      HasValidAddress = TRUE;
    } else if (!HasValidAddress) {
      continue;
    }

    //
    //call Pci.Read with Width as IO_UINT64 + 1 and -1.
    //

    Status = DeviceIo->Pci.Read (
                             DeviceIo,
                             IO_UINT64 + 1,
                             BaseAddress,
                             1,
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
                   gDeviceIoBBTestConformanceAssertionGuid013,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - With Width as IO_UINT64 +1 return Status Must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Status = DeviceIo->Pci.Read (
                             DeviceIo,
                             -1,
                             BaseAddress,
                             1,
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
                   gDeviceIoBBTestConformanceAssertionGuid014,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - With Width as -1 return Status Must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    //
    //get use input for Invalid Width.
    //
    InvalidWidth  = IO_UINT64 + 1;

    Status = GetInvalidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_PCIREAD_CONFORM_TEST,
               Index,
               &InvalidWidth
               );

    if (!EFI_ERROR(Status)) {
      //
      // call with the invalid width for this system assigned by tester.
      //
      Status = DeviceIo->Pci.Read (
                               DeviceIo,
                               InvalidWidth,
                               BaseAddress,
                               1,
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
                     gDeviceIoBBTestConformanceAssertionGuid015,
                     L"EFI_DEVICE_IO_PROTOCOL.Pci.Read - With Invalid Width return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r,Width - %08xh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     InvalidWidth
                     );
    }
  }
  //
  //done successfully.
  //

  gtBS->FreePool (Buffer);
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for Pci.Write() conformance Automatically Test.
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
PciWrite_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  EFI_IO_WIDTH                            ValidWidth;
  EFI_IO_WIDTH                            InvalidWidth;
  UINTN                                   Index;
  VOID                                    *Buffer;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;
  BOOLEAN                                 HasValidAddress;

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


  Buffer = SctAllocatePool (64);
  if (Buffer == NULL) {
    gtBS->FreePool (DevIoDevicePathStr);
    return EFI_OUT_OF_RESOURCES;
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
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Write - not found profile",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  MaxOrder = 0;
  Status = FileHandle->GetOrderNum (
                         FileHandle,
                         SECTION_NAME_PCIWRITE_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Write - no item found for this test case",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  HasValidAddress = FALSE;
  BaseAddress     = 0;
  ValidWidth      = IO_UINT8;

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get DevicePath from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
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

    if (SctStriCmp (DevIoDevicePathStr, TempDevicePathStr) != 0) {
      gtBS->FreePool (TempDevicePathStr);
      continue;
    }

    gtBS->FreePool (TempDevicePathStr);

    //
    //get use input for Valid BaseAddress.
    //
    Status = GetValidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_CONFORM_TEST,
               Index,
               &BaseAddress
               );
    if (!EFI_ERROR(Status)) {
      HasValidAddress = TRUE;
    } else if (!HasValidAddress) {
      continue;
    }

    //
    //call Pci.Write with Width as IO_UINT64 + 1 and -1.
    //

    Status = DeviceIo->Pci.Write (
                             DeviceIo,
                             IO_UINT64 + 1,
                             BaseAddress,
                             1,
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
                   gDeviceIoBBTestConformanceAssertionGuid016,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Write - With Width as IO_UINT64 +1 return Status Must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    Status = DeviceIo->Pci.Write (
                             DeviceIo,
                             -1,
                             BaseAddress,
                             1,
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
                   gDeviceIoBBTestConformanceAssertionGuid017,
                   L"EFI_DEVICE_IO_PROTOCOL.Pci.Write - With Width as -1 return Status Must be EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    //
    //get user input for Invalid Width.
    //
    InvalidWidth  = IO_UINT64 + 1;

    Status = GetInvalidEfiIoWidthByFile (
               FileHandle,
               SECTION_NAME_PCIWRITE_CONFORM_TEST,
               Index,
               &InvalidWidth
               );

    if (!EFI_ERROR(Status)) {
      //
      // call with the invalid width for this system assigned by tester.
      //
      Status = DeviceIo->Pci.Write (
                               DeviceIo,
                               InvalidWidth,
                               BaseAddress,
                               1,
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
                     gDeviceIoBBTestConformanceAssertionGuid018,
                     L"EFI_DEVICE_IO_PROTOCOL.Pci.Write - With Invalid Width return Status Must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r,Width - %08xh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     InvalidWidth
                     );
    }
  }
  //
  //done successfully.
  //

  gtBS->FreePool (Buffer);
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for map() conformance Automatically Test.
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
Map_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  EFI_PHYSICAL_ADDRESS                    HostAddress;
  EFI_PHYSICAL_ADDRESS                    DeviceAddress;
  UINTN                                   NumberOfBytes;
  VOID                                    *Mapping;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  VOID                                    *Buffer;

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
  Status = GetDevIoDevicePathStr (DeviceIo, NULL);

  if (EFI_ERROR(Status)) {
    return Status;
  }


  Buffer = SctAllocatePool (128);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  HostAddress = (EFI_PHYSICAL_ADDRESS)(UINTN)Buffer;
  NumberOfBytes = 128;

  //
  //call Map with Operation as EfiBusMasterCommonBuffer + 1 and -1 respectively.
  //

  Status = DeviceIo->Map (
                       DeviceIo,
                       EfiBusMasterCommonBuffer + 1,
                       &HostAddress,
                       &NumberOfBytes,
                       &DeviceAddress,
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
                 gDeviceIoBBTestConformanceAssertionGuid019,
                 L"EFI_DEVICE_IO_PROTOCOL.Map - With operation as EfiBusMasterCommonBuffer + 1 the returned Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  NumberOfBytes = 128;
  Status = DeviceIo->Map (
                       DeviceIo,
                       -1,
                       &HostAddress,
                       &NumberOfBytes,
                       &DeviceAddress,
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
                 gDeviceIoBBTestConformanceAssertionGuid020,
                 L"EFI_DEVICE_IO_PROTOCOL.Map - With operation as -1 the returned Status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  // This 4GB should not be a limitation on IPF and IA32E
  //

  //
  //done successfully.
  //
  gtBS->FreePool (Buffer);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for AllocateBuffer() conformance automatically Test.
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
AllocateBuffer_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_STATUS                            EfiStatus;
  EFI_DEVICE_IO_PROTOCOL                *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_PHYSICAL_ADDRESS                  HostAddress;
  EFI_PHYSICAL_ADDRESS                  BaseAddress;
  EFI_PHYSICAL_ADDRESS                  OldBaseAddress;
  UINTN                                 Index;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 InvalidMemoryTypeNum;
  EFI_INI_FILE_HANDLE                   FileHandle;
  UINTN                                 MaxOrder;
  CHAR16                                *DevIoDevicePathStr;
  CHAR16                                *TempDevicePathStr;

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
  //call allocate buffer with invalid memory types.
  //
  EfiStatus = EFI_INVALID_PARAMETER;
  InvalidMemoryTypeNum = 15;
  for (Index = 0; Index < InvalidMemoryTypeNum; Index++) {

    Status = DeviceIo->AllocateBuffer (
                         DeviceIo,
                         AllocateAnyPages,
                         InvalidMemoryType[Index],
                         1,
                         (VOID **) &HostAddress
                         );

    //
    //record message
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - with invalid Memory type Status must be EFI_INVALID_PARAMETER.\n"
                   L"%a:%d:Status - %r,Memory Type - %d",
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
                 gDeviceIoBBTestConformanceAssertionGuid022,
                 L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - with Invalid memory type the  status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiStatus
                 );


  //
  //get user input for Unsupported address on this system.
  //

  //
  //open the ini file.
  //

  Status = OpenTestIniFile (ProfileLib, &FileHandle);

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - Not Found the Profile.",
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
                         SECTION_NAME_ALLOCATEBUFFER_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - Not found item for this test case.",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index++) {
    //
    //get device path from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
               FileHandle,
               SECTION_NAME_ALLOCATEBUFFER_CONFORM_TEST,
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
    //get use input for InvalidBaseAddress
    //
    BaseAddress = 0;
    Status = GetInvalidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_ALLOCATEBUFFER_CONFORM_TEST,
               Index,
               &BaseAddress
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    OldBaseAddress = BaseAddress;
    //
    //call AllocateBuffer with unsupported address.
    //
    Status = DeviceIo->AllocateBuffer (
                         DeviceIo,
                         AllocateAddress,
                         EfiBootServicesData,
                         1,
                         (VOID **) &BaseAddress
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
                   gDeviceIoBBTestConformanceAssertionGuid023,
                   L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - with Unsupported memory address the  status must be EFI_UNSUPPORTED",
                   L"%a:%d:Status - %r, Address - %lXh,returned Address - %lXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   OldBaseAddress,
                   BaseAddress
                   );
  }

  //
  //done successfully.
  //
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for  FreeBuffer() conformance automatically Test.
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
FreeBuffer_Conf (
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
  EFI_PHYSICAL_ADDRESS                  HostAddress;
  UINTN                                 AllocatedPages;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 PageSize;

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
  Status = GetDevIoDevicePathStr (DeviceIo, NULL);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //these check points are added after the EFI 1.10 spec has been updated.
  //call FreeBuffer with a Physical address that is not allocted from
  //AllocateBuffer() it will return EFI_NOT_FOUND.
  //
  //
  //first call allocatebuffer allocate 5 pages.
  //
  AllocatedPages = 5;
  PageSize = 4 * 1024;
  Status = DeviceIo->AllocateBuffer (
                       DeviceIo,
                       AllocateAnyPages,
                       EfiBootServicesData,
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
                 gTestGenericFailureGuid,
                 L"EFI_DEVICE_IO_PROTOCOL.AllocateBuffer - the status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r,AllocatedPages -%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AllocatedPages
                 );

  if (EFI_ERROR(Status)) {
    return Status;
  }
  //
  // free these buffer with un-aligned address
  //

  Status = DeviceIo->FreeBuffer (
                       DeviceIo,
                       AllocatedPages,
                       HostAddress + 1
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
                 gDeviceIoBBTestConformanceAssertionGuid024,
                 L"EFI_DEVICE_IO_PROTOCOL.FreeBuffer - with address + 1 the returned status must be EFI_INVALID_PARAMETER",
                 L"%a:%d:Status - %r, Original Address - %lXh, Free Address - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HostAddress,
                 HostAddress + 1
                 );

  if (EFI_ERROR(Status)) {
    //
    // free these buffer with un-aligned address
    //
    Status = DeviceIo->FreeBuffer (
                         DeviceIo,
                         AllocatedPages,
                         HostAddress - 1
                         );
    if ((Status == EFI_NOT_FOUND) || (Status == EFI_INVALID_PARAMETER)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    //record assertion
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gDeviceIoBBTestConformanceAssertionGuid025,
                   L"EFI_DEVICE_IO_PROTOCOL.FreeBuffer - with address - 1 the returned status must be EFI_NOT_FOUND or EFI_INVALID_PARAMETER",
                   L"%a:%d:Status - %r, Original Address - %lXh, Free Address - %lXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   HostAddress,
                   HostAddress - 1
                   );

    if (EFI_ERROR(Status)) {
      //
      // free these buffer with un-aligned address
      //
      Status = DeviceIo->FreeBuffer (
                           DeviceIo,
                           AllocatedPages,
                           HostAddress + PageSize - 1
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
                     gDeviceIoBBTestConformanceAssertionGuid026,
                     L"EFI_DEVICE_IO_PROTOCOL.FreeBuffer - with address + pageSize - 1 the returned status must be EFI_INVALID_PARAMETER",
                     L"%a:%d:Status - %r, Original Address - %lXh, Free Address - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     HostAddress,
                     HostAddress + PageSize - 1
                     );

      if (EFI_ERROR(Status)) {
        //
        //free these pages
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
                       L"EFI_DEVICE_IO_PROTOCOL.FreeBuffer - with correct Pages and HostAddress the returned status must be EFI_SUCCESS",
                       L"%a:%d:Status - %r, Allocated Pages - %d, Host Address - %lXh",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       AllocatedPages,
                       HostAddress
                       );
      }
    }
  }

  //
  //free these pages again
  //
  Status = DeviceIo->FreeBuffer (
                       DeviceIo,
                       AllocatedPages,
                       HostAddress
                       );
  if (Status == EFI_NOT_FOUND) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gDeviceIoBBTestConformanceAssertionGuid027,
                 L"EFI_DEVICE_IO_PROTOCOL.FreeBuffer - with correct Pages and HostAddress again the returned status must be EFI_NOT_FOUND",
                 L"%a:%d:Status - %r, Allocated Pages - %d, Host Address - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 AllocatedPages,
                 HostAddress
                 );

  //
  //done successfully
  //

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for PciDevicePath ()conformance automatically Test.
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
PciDevicePath_Conf (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                              Status;
  UINT64                                  BaseAddress;
  EFI_DEVICE_IO_PROTOCOL                  *DeviceIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL      *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL      *ProfileLib;
  UINTN                                   Index;
  CHAR16                                  *DevIoDevicePathStr;
  CHAR16                                  *TempDevicePathStr;
  EFI_DEVICE_PATH_PROTOCOL                *DevicePath;
  EFI_TEST_ASSERTION                      AssertionType;
  EFI_INI_FILE_HANDLE                     FileHandle;
  UINTN                                   MaxOrder;

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
                   L"EFI_DEVICE_IO_PROTOCOL.PciDevicePath - Not Found the Profile.",
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
                         SECTION_NAME_PCIDEVICEPATH_CONFORM_TEST,
                         (UINT32 *)&MaxOrder
                         );

  if (EFI_ERROR(Status)) {
    CloseTestIniFile (ProfileLib, FileHandle);
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_DEVICE_IO_PROTOCOL.PciDevicePath - No item found for this test case.",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    gtBS->FreePool (DevIoDevicePathStr);
    return Status;
  }

  for (Index = 0; Index < MaxOrder; Index++) {

    //
    //get DevicePath from profile.
    //
    TempDevicePathStr = NULL;
    Status = GetSystemDevicePathStrByFile (
               FileHandle,
               SECTION_NAME_PCIDEVICEPATH_CONFORM_TEST,
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
    //get use input for Invalid BaseAddress.
    //
    Status = GetInvalidBaseAddressByFile (
               FileHandle,
               SECTION_NAME_PCIDEVICEPATH_CONFORM_TEST,
               Index,
               &BaseAddress
               );
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    //call PciDevicePath with InvalidAddress.
    //
    Status = DeviceIo->PciDevicePath (
                         DeviceIo,
                         BaseAddress,
                         &DevicePath
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
                   gDeviceIoBBTestConformanceAssertionGuid028,
                   L"EFI_DEVICE_IO_PROTOCOL.PciDevicePath - With Unsupported PciAddress return Status Must be EFI_UNSUPPORTED",
                   L"%a:%d:Status - %r,PciAddress - %lXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BaseAddress
                   );
  }

  //
  //done successfully.
  //
  gtBS->FreePool (DevIoDevicePathStr);
  CloseTestIniFile (ProfileLib, FileHandle);
  return EFI_SUCCESS;
}

