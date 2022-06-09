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

  UgaDrawBBTestConformance.c

Abstract:

  Conformance Test Cases of UGA Draw Protocol

--*/


#include "SctLib.h"
#include "UgaDrawBBTestMain.h"


/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.GetMode() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2.1
//
EFI_STATUS
EFIAPI
BBTestGetModeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;

  EFI_TEST_ASSERTION                   AssertionType;

  UINT32                               HorizontalResolution;
  UINT32                               VerticalResolution;
  UINT32                               ColorDepth;
  UINT32                               RefreshRate;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  UgaDraw = (EFI_UGA_DRAW_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Uga_Draw_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromUgaDraw (UgaDraw, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    //
    // Console Splitter/UgaDraw
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/UgaDraw"
                   );
#ifdef TEST_CHIPSET_UGA_ONLY
    return EFI_SUCCESS;
#endif
  }

  //
  // Assertion Point 4.2.1.2.1
  // GetMode should not succeed with invalid parameter
  //

  //
  // Call GetMode with HorizontalResolution being NULL
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      NULL,
                      &VerticalResolution,
                      &ColorDepth,
                      &RefreshRate
                      );
  if (Status!=EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUgaDrawConformanceTestAssertionGuid001,
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode() with HorizontalResolution being NULL",
                 L"%a:%d:Status:%r, Expected:%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_INVALID_PARAMETER
                 );


  //
  // Call GetMode with VerticalResolution being NULL
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolution,
                      NULL,
                      &ColorDepth,
                      &RefreshRate
                      );
  if (Status!=EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUgaDrawConformanceTestAssertionGuid002,
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode() with VerticalResolution being NULL",
                 L"%a:%d:Status:%r, Expected:%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_INVALID_PARAMETER
                 );

  //
  // Call GetMode with RefreshRate being NULL
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolution,
                      &VerticalResolution,
                      &ColorDepth,
                      NULL
                      );
  if (Status!=EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUgaDrawConformanceTestAssertionGuid003,
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode() with RefreshRate being NULL",
                 L"%a:%d:Status:%r, Expected:%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_INVALID_PARAMETER
                 );


  //
  // Call GetMode with ColorDepth being NULL
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolution,
                      &VerticalResolution,
                      NULL,
                      &RefreshRate
                      );
  if (Status!=EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUgaDrawConformanceTestAssertionGuid004,
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode() with ColorDepth being NULL",
                 L"%a:%d:Status:%r, Expected:%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_INVALID_PARAMETER
                 );

  return EFI_SUCCESS;
}



/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.Blt() Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2.2
//
EFI_STATUS
EFIAPI
BBTestBltConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;

  EFI_TEST_ASSERTION                   AssertionType;

  EFI_UGA_PIXEL                        BltBuffer[10];
  UINTN                                SourceX, SourceY;
  UINTN                                DestinationX, DestinationY;
  UINTN                                Width, Height;
  UINTN                                Delta;
  UINTN                                Index;
  EFI_UGA_BLT_OPERATION                BltOperation;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  SourceX      = 0;
  SourceY      = 0;
  DestinationX = 0;
  DestinationY = 0;
  Width        = 1;
  Height       = 1;
  Delta        = 0;



  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  UgaDraw = (EFI_UGA_DRAW_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Uga_Draw_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromUgaDraw (UgaDraw, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    //
    // Console Splitter/UgaDraw
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/UgaDraw"
                   );
#ifdef TEST_CHIPSET_UGA_ONLY
    return EFI_SUCCESS;
#endif
  }

  //
  // Assertion Point 4.2.2.2.1
  // Blt should not succeed with invalid parameter
  //
  for (Index = 0; Index < 6; Index++) {
    switch (Index) {
      case 0:
        BltOperation = EfiUgaBltMax;
        break;
      case 1:
        BltOperation = EfiUgaBltMax + 1;
        break;
      case 2:
        BltOperation = EfiUgaBltMax + 10;
        break;
      case 3:
        BltOperation = EfiUgaBltMax + 100;
        break;
      case 4:
        BltOperation = EfiUgaBltMax + 1000;
        break;
      case 5:
        BltOperation = -1;
        break;
      default:
        BltOperation = EfiUgaBltMax - 1;
        break;
    }

    //
    // test data verification
    //

    Status = UgaDraw->Blt (
                        UgaDraw,
                        BltBuffer,
                        BltOperation,
                        SourceX,
                        SourceY,
                        DestinationX,
                        DestinationY,
                        Width,
                        Height,
                        Delta
                        );

    if (Status!=EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUgaDrawConformanceTestAssertionGuid005,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt - Blt() with invalid BltOperation",
                   L"%a:%d: Status = %r,Expected = %r, Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d,BltOperation=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_INVALID_PARAMETER,
                   DestinationX,
                   DestinationY,
                   0,
                   0,
                   Width,
                   Height,
                   Delta,
                   BltOperation
                   );
  }

  return EFI_SUCCESS;
}


