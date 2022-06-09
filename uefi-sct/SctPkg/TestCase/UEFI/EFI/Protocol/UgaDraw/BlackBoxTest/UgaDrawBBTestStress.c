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

  UgaDrawBBTestStress.c

Abstract:

  Extensive Test Cases of UGA Draw Protocol

--*/


#include "SctLib.h"
#include "UgaDrawBBTestMain.h"


/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.Blt()-EfiUgaVideoFill/BufferToVideo Extensive Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3.1
//
EFI_STATUS
EFIAPI
BBTestVideoFillBufferToVideoManualTest (
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
  EFI_TEST_ASSERTION                   FillAssertion, BufferToVideoAssertion;
  EFI_CONSOLE_CONTROL_PROTOCOL         *Console;

  EFI_HANDLE                           *HandleBuffer;
  UINTN                                Size;

  UINT32                               HorizontalResolution, HorizontalResolutionOrg;
  UINT32                               VerticalResolution, VerticalResolutionOrg;
  UINT32                               ColorDepth, ColorDepthOrg;
  UINT32                               RefreshRate, RefreshRateOrg;
  EFI_CONSOLE_CONTROL_SCREEN_MODE      ModeOrg;

  UINTN                                SourceX;
  UINTN                                SourceY;
  UINTN                                DestinationX;
  UINTN                                DestinationY;
  UINTN                                Width;
  UINTN                                Height;
  UINTN                                Delta;
  EFI_UGA_PIXEL                        *BltBuffer, Blt;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  UINTN                                i, j, k;

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
  // Get ConsoleControl interface
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   NULL,
                   &Size,
                   &HandleBuffer
                   );

  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->LocateHandleBuffer - Locate Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    return Status;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   (VOID **) &Console
                   );

  if (EFI_ERROR (Status)) {
    gtBS->FreePool (HandleBuffer);
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->HandleProtocol - Handle Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  gtBS->FreePool (HandleBuffer);


  //
  // Back screen mode and
  // Switch screen into Graphics Mode
  //
  Status = Console->GetMode (Console, &ModeOrg, NULL, NULL);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.GetMode - GetMode ",
                   L"%a:%d: Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeOrg,
                   Status
                   );
    return Status;

  }

  Status = Console->SetMode (Console, EfiConsoleControlScreenGraphics);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into graphics mode",
                   L"%a:%d: Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EfiConsoleControlScreenGraphics,
                   Status
                   );
    return Status;
  }

  //
  // Backup video mode
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolutionOrg,
                      &VerticalResolutionOrg,
                      &ColorDepthOrg,
                      &RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve video device information",
                 L"%a:%d: Mode=%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 ModeOrg,
                 Status
                 );

  //
  // for all demo mode, try it..
  //
  for (i = 0; i < DemoResolutionMax; i++) {
    HorizontalResolution = DemoResolution[i].HorizontalResolution;
    VerticalResolution = DemoResolution[i].VerticalResolution;
    for (j = 0; j < DemoRefreshRateMax; j++){
      RefreshRate = DemoRefreshRate[j];
      for (k = 0; k < DemoColorDepthMax; k++){
        ColorDepth = DemoColorDepth[k];

        //
        // switch screen into this demo mode
        //
        Status = UgaDraw->SetMode (
                            UgaDraw,
                            HorizontalResolution,
                            VerticalResolution,
                            ColorDepth,
                            RefreshRate
                            );

        if (Status == EFI_UNSUPPORTED || Status == EFI_SUCCESS)  {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTestGenericFailureGuid,
                       L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to switch video device's mode",
                       L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        if (EFI_ERROR(Status)) {
          continue;
        }

        //
        // Load BltBuffer from some .bmp file, and set width&heigth
        //

        Status = LoadBmp (&BltBuffer, &Width, &Height);
        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"UgaDraw - LoadBmp failure",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          return Status;
        }

        Delta = Width * sizeof (EFI_UGA_PIXEL);
        SourceX = 0;
        SourceY = 0;
        DestinationX = 0;
        DestinationY = 0;
        Width -= SourceX;
        Height -= SourceY;

        //
        // ClearScreen
        //
        Status = UgaDrawClearScreen (
                   UgaDraw,
                   HorizontalResolution,
                   VerticalResolution
                   );
        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"UgaDraw - Clear Screen failure",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          return Status;
        }
        //
        // Move DestinationXY from upper left-hand corner to right-hand corner
        //
        FillAssertion          = EFI_TEST_ASSERTION_PASSED;
        BufferToVideoAssertion = EFI_TEST_ASSERTION_PASSED;

        for (; DestinationX + Width + STEP_WIDTH < HorizontalResolution; DestinationX += STEP_WIDTH){
          //
          // Use BltBufferToVideo to display .bmp file
          // DestinationXY is the upper left of Video frame in this case
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaBltBufferToVideo,
                              SourceX,
                              SourceY,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              Delta
                              );

          if (EFI_ERROR(Status)) {
            BufferToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
          }
           gtBS->Stall (15000);
          //
          // Call Blt() with BltOperation being EfiUgaVideoFill
          // to clear the rectangle in the last call of EfiUgaBufferToVideo
          //
          Blt.Blue  = 0;
          Blt.Red   = 0;
          Blt.Green = 0;
          Status = UgaDraw->Blt (
                              UgaDraw,
                              &Blt,
                              EfiUgaVideoFill,
                              0,
                              0,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            FillAssertion = EFI_TEST_ASSERTION_FAILED;
          }

          //
          // wait some time
          //

        }// Rotate from upper left to right

        StandardLib->RecordAssertion (
                       StandardLib,
                       BufferToVideoAssertion,
                       gUgaDrawExtensiveTestAssertionGuid007,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaBltBufferToVideo - Blt/EfiUgaBltBufferToVideo",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       FillAssertion,
                       gUgaDrawExtensiveTestAssertionGuid008,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );


        //
        // Move DestinationXY from upper right-hand corner to lower right-hand corner
        //
        FillAssertion          = EFI_TEST_ASSERTION_PASSED;
        BufferToVideoAssertion = EFI_TEST_ASSERTION_PASSED;

        for (DestinationY = 0; DestinationY + Height + STEP_WIDTH < VerticalResolution; DestinationY+=STEP_WIDTH){
          //
          // Use BltBufferToVideo to display .bmp file
          // DestinationXY is the upper left of Video frame in this case
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaBltBufferToVideo,
                              SourceX,
                              SourceY,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              Delta
                              );

          if (EFI_ERROR(Status)) {
            BufferToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
          }
          gtBS->Stall (15000);
          //
          // Call Blt() with BltOperation being EfiUgaVideoFill
          // to clear the rectangle in the last call of EfiUgaBufferToVideo
          //
          Blt.Blue  = 0;
          Blt.Red   = 0;
          Blt.Green = 0;
          Status = UgaDraw->Blt (
                              UgaDraw,
                              &Blt,
                              EfiUgaVideoFill,
                              0,
                              0,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            FillAssertion = EFI_TEST_ASSERTION_FAILED;
          }

          //
          // wait some time
          //
          gtBS->Stall (5000);
        }// Rotate from upper right to lower right

        StandardLib->RecordAssertion (
                       StandardLib,
                       BufferToVideoAssertion,
                       gUgaDrawExtensiveTestAssertionGuid009,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaBltBufferToVideo - Blt/EfiUgaBltBufferToVideo",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       FillAssertion,
                       gUgaDrawExtensiveTestAssertionGuid010,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        //
        // Move DestinationXY from lower right-hand corner to left-hand corner
        //
        FillAssertion          = EFI_TEST_ASSERTION_PASSED;
        BufferToVideoAssertion = EFI_TEST_ASSERTION_PASSED;

        for (; DestinationX > STEP_WIDTH; DestinationX -= STEP_WIDTH){
          //
          // Use BltBufferToVideo to display .bmp file
          // DestinationXY is the upper left of Video frame in this case
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaBltBufferToVideo,
                              SourceX,
                              SourceY,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              Delta
                              );

          if (EFI_ERROR(Status)) {
            BufferToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
          }
          gtBS->Stall (15000);
          //
          // Call Blt() with BltOperation being EfiUgaVideoFill
          // to clear the rectangle in the last call of EfiUgaBufferToVideo
          //
          Blt.Blue  = 0;
          Blt.Red   = 0;
          Blt.Green = 0;
          Status = UgaDraw->Blt (
                              UgaDraw,
                              &Blt,
                              EfiUgaVideoFill,
                              0,
                              0,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            FillAssertion = EFI_TEST_ASSERTION_FAILED;
          }

          //
          // wait some time
          //
          gtBS->Stall (5000);
        }// Rotate from lower right to left


        StandardLib->RecordAssertion (
                       StandardLib,
                       BufferToVideoAssertion,
                       gUgaDrawExtensiveTestAssertionGuid011,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaBltBufferToVideo - Blt/EfiUgaBltBufferToVideo",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

       StandardLib->RecordAssertion (
                      StandardLib,
                      FillAssertion,
                      gUgaDrawExtensiveTestAssertionGuid012,
                      L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill",
                      L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                      __FILE__,
                      (UINTN)__LINE__,
                      Status,
                      Width,
                      Height,
                      Delta,
                      HorizontalResolution,
                      VerticalResolution,
                      ColorDepth,
                      RefreshRate
                      );

        //
        // Move DestinationXY from lower left-hand corner to upper left-hand corner
        //
        FillAssertion          = EFI_TEST_ASSERTION_PASSED;
        BufferToVideoAssertion = EFI_TEST_ASSERTION_PASSED;

        for (; DestinationY > STEP_WIDTH; DestinationY -= STEP_WIDTH){
          //
          // Use BltBufferToVideo to display .bmp file
          // DestinationXY is the upper left of Video frame in this case
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaBltBufferToVideo,
                              SourceX,
                              SourceY,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              Delta
                              );

          if (EFI_ERROR(Status)) {
            BufferToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
          }
          gtBS->Stall (15000);
          //
          // Call Blt() with BltOperation being EfiUgaVideoFill
          // to clear the rectangle in the last call of EfiUgaBufferToVideo
          //
          Blt.Blue  = 0;
          Blt.Red   = 0;
          Blt.Green = 0;
          Status = UgaDraw->Blt (
                              UgaDraw,
                              &Blt,
                              EfiUgaVideoFill,
                              0,
                              0,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            FillAssertion = EFI_TEST_ASSERTION_FAILED;
          }

          //
          // wait some time
          //
          gtBS->Stall (5000);
        }// Rotate from lower left to upper left

        StandardLib->RecordAssertion (
                       StandardLib,
                       BufferToVideoAssertion,
                       gUgaDrawExtensiveTestAssertionGuid013,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaBltBufferToVideo - Blt/EfiUgaBltBufferToVideo",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       FillAssertion,
                       gUgaDrawExtensiveTestAssertionGuid014,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );
        //
        // Free Buffer for next test data
        //
        if (BltBuffer != NULL) {
          Status = gtBS->FreePool (BltBuffer);
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
          }
        }

        //
        // Ask for user's to judge whether the rotation of the BMP file correctly
        //
        Status = UgaDrawClearScreen (
                   UgaDraw,
                   HorizontalResolution,
                   VerticalResolution
                   );
        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"UgaDraw - Clear screen failure",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          return Status;
        }

        if (AutoJudgeUga (10, 120, 10, TRUE, L"Logo rotates correctly?") != TRUE) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gUgaDrawExtensiveTestAssertionGuid015,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt()/VideoFill&BltBufferToVideo - Blt()/VideoFill&BltBufferToVideo - user's view",
                       L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

      }//
    }  // For all mode
  }    //


  //
  // Restore video mode
  //
  Status = UgaDraw->SetMode (
                      UgaDraw,
                      HorizontalResolutionOrg,
                      VerticalResolutionOrg,
                      ColorDepthOrg,
                      RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to restore original video mode",
                 L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HorizontalResolutionOrg,
                 VerticalResolutionOrg,
                 ColorDepthOrg,
                 RefreshRateOrg
                 );


  //
  // Switch screen mode into original mode
  //
  Status = Console->SetMode (Console, ModeOrg);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into original mode",
                   L"%a:%d: Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeOrg,
                   Status
                   );
  }

  return EFI_SUCCESS;
}



/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.Blt()-EfiUgaVideoFill/VideoToVideo Extensive Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3.2
//
EFI_STATUS
EFIAPI
BBTestVideoFillVideoToVideoManualTest (
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
  EFI_TEST_ASSERTION                   VideoToVideoAssertion, FillAssertion;
  EFI_CONSOLE_CONTROL_PROTOCOL         *Console;

  EFI_HANDLE                           *HandleBuffer;
  UINTN                                Size;

  UINT32                               HorizontalResolution, HorizontalResolutionOrg;
  UINT32                               VerticalResolution, VerticalResolutionOrg;
  UINT32                               ColorDepth, ColorDepthOrg;
  UINT32                               RefreshRate, RefreshRateOrg;
  EFI_CONSOLE_CONTROL_SCREEN_MODE      ModeOrg;

  UINTN                                SourceX;
  UINTN                                SourceY;
  UINTN                                DestinationX;
  UINTN                                DestinationY;
  UINTN                                Width;
  UINTN                                Height;
  UINTN                                Delta;
  EFI_UGA_PIXEL                        *BltBuffer, Blt;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  UINTN                                i, j, k;





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
                     L", Current Device: %s",
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
                   L", Current Device: ConsoleSplitter/UgaDraw"
                   );
#ifdef TEST_CHIPSET_UGA_ONLY
    return EFI_SUCCESS;
#endif
  }

  //
  // Get ConsoleControl interface
  //

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   NULL,
                   &Size,
                   &HandleBuffer
                   );

  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->LocateHandleBuffer - Locate Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    return Status;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   (VOID **) &Console
                   );

  if (EFI_ERROR (Status)) {
    gtBS->FreePool (HandleBuffer);
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->HandleProtocol - Handle Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  gtBS->FreePool (HandleBuffer);

  //
  // Back screen mode and
  // Switch screen into Graphics Mode
  //
  Status = Console->GetMode (Console, &ModeOrg, NULL, NULL);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.GetMode - GetMode ",
                   L"%a:%d: Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeOrg,
                   Status
                   );
    return Status;

  }

  Status = Console->SetMode (Console, EfiConsoleControlScreenGraphics);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into graphics mode",
                   L"%a:%d: Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EfiConsoleControlScreenGraphics,
                   Status
                   );
    return Status;
  }

  //
  // Backup video mode
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolutionOrg,
                      &VerticalResolutionOrg,
                      &ColorDepthOrg,
                      &RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve video device information",
                 L"%a:%d: Mode=%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 ModeOrg,
                 Status
                 );

  //
  // Load BltBuffer from some .bmp file, and set width&heigth
  //
  Status = LoadBmp (&BltBuffer, &Width, &Height);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"UgaDraw - LoadBmp failure",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Delta = Width * sizeof (EFI_UGA_PIXEL);
  SourceX = 0;
  SourceY = 0;
  DestinationX = 0;
  DestinationY = 0;
  Width -= SourceX;
  Height -= SourceY;
  //        Delta = 0;

  Blt.Blue  = 0;
  Blt.Red   = 0;
  Blt.Green = 0;

  //
  // for all demo mode, try it..
  //
  for (i = 0; i < DemoResolutionMax; i++) {
    HorizontalResolution = DemoResolution[i].HorizontalResolution;
    VerticalResolution = DemoResolution[i].VerticalResolution;
    for (j = 0; j < DemoRefreshRateMax; j++){
      RefreshRate = DemoRefreshRate[j];
      for (k = 0; k < DemoColorDepthMax; k++){
        ColorDepth = DemoColorDepth[k];
        //
        // switch screen into this demo mode
        //

        Status = UgaDraw->SetMode (
                            UgaDraw,
                            HorizontalResolution,
                            VerticalResolution,
                            ColorDepth,
                            RefreshRate
                            );

        if (Status == EFI_UNSUPPORTED || Status == EFI_SUCCESS)  {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTestGenericFailureGuid,
                       L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to switch video device's mode",
                       L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );


        if (EFI_ERROR(Status)) {
          continue;
        }

        //
        // ClearScreen
        //
        Status = UgaDrawClearScreen (
                   UgaDraw,
                   HorizontalResolution,
                   VerticalResolution
                    );
        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"UgaDraw - Clear screen failure",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (BltBuffer != NULL) {
            Status = gtBS->FreePool (BltBuffer);
            BltBuffer = NULL;
          }
          return Status;
        }
        //
        // Use BltBufferToVideo to display .bmp file
        // DestinationXY is the upper left of Video frame in this case
        //
        SourceX = 0;
        SourceY = 0;
        DestinationX = 0;
        DestinationY = 0;

        Status = UgaDraw->Blt (
                            UgaDraw,
                            BltBuffer,
                            EfiUgaBltBufferToVideo,
                            SourceX,
                            SourceY,
                            DestinationX,
                            DestinationY,
                            Width,
                            Height,
                            Delta
                            );

        if (EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawExtensiveTestAssertionGuid024,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaBltBufferToVideo - Blt/EfiUgaBltBufferToVideo",
                         L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         SourceX,
                         SourceY,
                         DestinationX,
                         DestinationY,
                         Width,
                         Height,
                         Delta,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );
        }
        //
        // Move DestinationXY from upper left-hand corner to right-hand corner
        //
        VideoToVideoAssertion = EFI_TEST_ASSERTION_PASSED;
        FillAssertion         = EFI_TEST_ASSERTION_PASSED;

        for (DestinationX = DestinationX + STEP_WIDTH; DestinationX + Width + STEP_WIDTH < HorizontalResolution; DestinationX += STEP_WIDTH){
          //
          // Use BltVideoToVideo to Copy .bmp file
          // DestinationXY is the upper left of Video frame in this case
          //
          SourceX = DestinationX - STEP_WIDTH;
          SourceY = DestinationY;
          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaVideoToVideo,
                              SourceX,
                              SourceY,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              Delta
                              );

          if (EFI_ERROR(Status)) {
            VideoToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
          }

          //
          // Call Blt() with BltOperation being EfiUgaVideoFill
          // to clear the rectangle in the last call of EfiUgaBufferToVideo
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              &Blt,
                              EfiUgaVideoFill,
                              0,
                              0,
                              SourceX,
                              SourceY,
                              STEP_WIDTH < Width ? STEP_WIDTH : Width,
                              Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            FillAssertion = EFI_TEST_ASSERTION_FAILED;
          }

          //
          // wait some time
          //
          gtBS->Stall (5000);
        }// Rotate from upper left to right

        StandardLib->RecordAssertion (
                       StandardLib,
                       VideoToVideoAssertion,
                       gUgaDrawExtensiveTestAssertionGuid025,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToVideo - Blt/EfiUgaVideoToVideo",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       FillAssertion,
                       gUgaDrawExtensiveTestAssertionGuid026,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       STEP_WIDTH < Width ? STEP_WIDTH : Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );
        //
        // Move DestinationXY from upper right-hand corner to lower right-hand corner
        //
        VideoToVideoAssertion = EFI_TEST_ASSERTION_PASSED;
        FillAssertion         = EFI_TEST_ASSERTION_PASSED;

        SourceX = DestinationX - STEP_WIDTH;
        DestinationX = SourceX;

        for (DestinationY = DestinationY + STEP_WIDTH; DestinationY + Height + STEP_WIDTH < VerticalResolution; DestinationY += STEP_WIDTH){
          //
          // Use BltVideoToVideo to Copy .bmp file
          // DestinationXY is the upper left of Video frame in this case
          //

          SourceY = DestinationY - STEP_WIDTH;
          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaVideoToVideo,
                              SourceX,
                              SourceY,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              Delta
                              );

          if (EFI_ERROR(Status)) {
            VideoToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
          }
          //
          // Call Blt() with BltOperation being EfiUgaVideoFill
          // to clear the rectangle in the last call of EfiUgaBufferToVideo
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              &Blt,
                              EfiUgaVideoFill,
                              0,
                              0,
                              SourceX,
                              SourceY,
                              Width,
                              STEP_WIDTH < Height ? STEP_WIDTH : Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            FillAssertion = EFI_TEST_ASSERTION_FAILED;
          }

          //
          // wait some time
          //
          gtBS->Stall (5000);
        }// Rotate from upper right to lower right

        StandardLib->RecordAssertion (
                       StandardLib,
                       VideoToVideoAssertion,
                       gUgaDrawExtensiveTestAssertionGuid027,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToVideo - Blt/EfiUgaVideoToVideo",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       FillAssertion,
                       gUgaDrawExtensiveTestAssertionGuid028,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       STEP_WIDTH < Height ? STEP_WIDTH : Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );
        //
        // Move DestinationXY from lower right-hand corner to left-hand corner
        //
        VideoToVideoAssertion = EFI_TEST_ASSERTION_PASSED;
        FillAssertion         = EFI_TEST_ASSERTION_PASSED;

        SourceY = DestinationY - STEP_WIDTH;
        DestinationY = SourceY;

        for (DestinationX = DestinationX - STEP_WIDTH; DestinationX > STEP_WIDTH; DestinationX -= STEP_WIDTH){
          //
          // Use BltVideoToVideo to Copy .bmp file
          // DestinationXY is the upper left of Video frame in this case
          //
          SourceX = DestinationX + STEP_WIDTH;

          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaVideoToVideo,
                              SourceX,
                              SourceY,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              Delta
                              );

          if (EFI_ERROR(Status)) {
            VideoToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
          }

          //
          // Call Blt() with BltOperation being EfiUgaVideoFill
          // to clear the rectangle in the last call of EfiUgaBufferToVideo
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              &Blt,
                              EfiUgaVideoFill,
                              0,
                              0,
                              STEP_WIDTH < Width ? (DestinationX + Width) : SourceX,
                              SourceY,
                              STEP_WIDTH < Width ? STEP_WIDTH : Width,
                              Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            FillAssertion = EFI_TEST_ASSERTION_FAILED;
          }

          //
          // wait some time
          //
          gtBS->Stall (5000);
        }// Rotate from lower right to left

        StandardLib->RecordAssertion (
                       StandardLib,
                       VideoToVideoAssertion,
                       gUgaDrawExtensiveTestAssertionGuid029,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToVideo - Blt/EfiUgaVideoToVideo",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       FillAssertion,
                       gUgaDrawExtensiveTestAssertionGuid030,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       STEP_WIDTH < Width ? STEP_WIDTH : Width,
                       Height,
                       0,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );
        //
        // Move DestinationXY from lower left - hand corner to upper left-hand corner
        //
        VideoToVideoAssertion = EFI_TEST_ASSERTION_PASSED;
        FillAssertion         = EFI_TEST_ASSERTION_PASSED;

        DestinationX = SourceX - STEP_WIDTH;
        SourceX = DestinationX;
        for (DestinationY = DestinationY - STEP_WIDTH; DestinationY > STEP_WIDTH; DestinationY -= STEP_WIDTH){
          //
          // Use BltVideoToVideo to Copy .bmp file
          // DestinationXY is the upper left of Video frame in this case
          //

          SourceY = DestinationY + STEP_WIDTH;
          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaVideoToVideo,
                              SourceX,
                              SourceY,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              Delta
                              );

          if (EFI_ERROR(Status)) {
            VideoToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
          }

          //
          // Call Blt() with BltOperation being EfiUgaVideoFill
          // to clear the rectangle in the last call of EfiUgaBufferToVideo
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              &Blt,
                              EfiUgaVideoFill,
                              0,
                              0,
                              SourceX,
                              STEP_WIDTH < Width ? (DestinationY + Height) : SourceY,
                              Width,
                              STEP_WIDTH < Width ? STEP_WIDTH : Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            FillAssertion = EFI_TEST_ASSERTION_FAILED;
          }

          //
          // wait some time
          //
          gtBS->Stall (5000);
        }// Rotate from lower left to upper left
        StandardLib->RecordAssertion (
                       StandardLib,
                       VideoToVideoAssertion,
                       gUgaDrawExtensiveTestAssertionGuid031,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToVideo - Blt/EfiUgaVideoToVideo",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );
         StandardLib->RecordAssertion (
                        StandardLib,
                        FillAssertion,
                        gUgaDrawExtensiveTestAssertionGuid032,
                        L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill",
                        L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                        __FILE__,
                        (UINTN)__LINE__,
                        Status,
                        Width,
                        STEP_WIDTH < Width ? STEP_WIDTH : Height,
                        Delta,
                        HorizontalResolution,
                        VerticalResolution,
                        ColorDepth,
                        RefreshRate
                        );

        //
        // Ask for user's to judge whether the rotation of the BMP file correctly
        //
        Status = UgaDrawClearScreen (
                   UgaDraw,
                   HorizontalResolution,
                   VerticalResolution
                   );
        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"UgaDraw - Clear screen failure",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (BltBuffer != NULL) {
            Status = gtBS->FreePool (BltBuffer);
            BltBuffer = NULL;
          }
          return Status;
        }

        if (AutoJudgeUga (10, 120, 10, TRUE, L"Logo rotates correctly?") != TRUE) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gUgaDrawExtensiveTestAssertionGuid033,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt()/VideoFill&BltBufferToVideo - Blt()/VideoFill&VideoToVideo - user's view",
                       L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

      }//
    }  // For all mode
  }    //


  //
  // Free Buffer for next test data
  //
  if (BltBuffer!=NULL) {
    Status = gtBS->FreePool (BltBuffer);
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
    }
  }

  //
  // Restore video mode
  //
  Status = UgaDraw->SetMode (
                      UgaDraw,
                      HorizontalResolutionOrg,
                      VerticalResolutionOrg,
                      ColorDepthOrg,
                      RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to restore original video mode",
                 L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HorizontalResolutionOrg,
                 VerticalResolutionOrg,
                 ColorDepthOrg,
                 RefreshRateOrg
                 );


  //
  // Switch screen mode into original mode
  //
  Status = Console->SetMode (Console, ModeOrg);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into original mode",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeOrg,
                   Status
                   );
  }

  return EFI_SUCCESS;
}



/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.Blt()-EfiUgaVideoToBltBuffer Extensive Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3.3
//
EFI_STATUS
EFIAPI
BBTestVideoToBltBufferAutoTest (
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
  EFI_TEST_ASSERTION                   VideoToBufferAssertion;
  EFI_CONSOLE_CONTROL_PROTOCOL         *Console;

  EFI_HANDLE                           *HandleBuffer;
  UINTN                                Size;

  UINT32                               HorizontalResolution, HorizontalResolutionOrg;
  UINT32                               VerticalResolution, VerticalResolutionOrg;
  UINT32                               ColorDepth, ColorDepthOrg;
  UINT32                               RefreshRate, RefreshRateOrg;
  EFI_CONSOLE_CONTROL_SCREEN_MODE      ModeOrg;

  UINTN                                SourceX, BmpSourceX;
  UINTN                                SourceY, BmpSourceY;
  UINTN                                DestinationX;
  UINTN                                DestinationY;
  UINTN                                Width, BmpWidth;
  UINTN                                Height, BmpHeight;
  UINTN                                Delta, BmpDelta;
  EFI_UGA_PIXEL                        *BltBuffer, *BltBufferWhole, *BltBufferWhole2, Blt;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  UINTN                                i, j, k, m, IndexPos;


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
  // Get ConsoleControl interface
  //

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   NULL,
                   &Size,
                   &HandleBuffer
                   );

  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->LocateHandleBuffer - Locate Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    return Status;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   (VOID **) &Console
                   );

  if (EFI_ERROR (Status)) {
    gtBS->FreePool (HandleBuffer);
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->HandleProtocol - Handle Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  gtBS->FreePool (HandleBuffer);




  //
  // Back screen mode and
  // Switch screen into Graphics Mode
  //
  Status = Console->GetMode (Console, &ModeOrg, NULL, NULL);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.GetMode - GetMode ",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeOrg,
                   Status
                   );
    return Status;

  }

  Status = Console->SetMode (Console, EfiConsoleControlScreenGraphics);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into graphics mode",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EfiConsoleControlScreenGraphics,
                   Status
                   );
    return Status;
  }

  //
  // Backup video mode
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolutionOrg,
                      &VerticalResolutionOrg,
                      &ColorDepthOrg,
                      &RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve video device information",
                 L"%a:%d:Mode=%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 ModeOrg,
                 Status
                 );

  Blt.Blue  = 0;
  Blt.Red   = 0;
  Blt.Green = 0;

  //
  // Load BltBuffer from some .bmp file, and set width&heigth
  //
  Status = LoadBmp (&BltBuffer, &Width, &Height);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"UgaDraw - LoadBmp failure",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Delta = Width * sizeof (EFI_UGA_PIXEL);
  SourceX = 100;
  SourceY = 100;
  DestinationX = 0;
  DestinationY = 0;
  Width -=SourceX;
  Height -= SourceY;

  BmpSourceX = SourceX;
  BmpSourceY = SourceY;
  BmpDelta = Delta;
  BmpWidth = Width;
  BmpHeight = Height;

  //
  // for all demo mode, try it..
  //
  for (i = 0; i < DemoResolutionMax; i++) {
    HorizontalResolution = DemoResolution[i].HorizontalResolution;
    VerticalResolution = DemoResolution[i].VerticalResolution;
    for (j = 0; j < DemoRefreshRateMax; j++){
      RefreshRate = DemoRefreshRate[j];
      for (k = 0; k < DemoColorDepthMax; k++){
        ColorDepth = DemoColorDepth[k];
        //
        // switch screen into this demo mode
        //
        Status = UgaDraw->SetMode (
                            UgaDraw,
                            HorizontalResolution,
                            VerticalResolution,
                            ColorDepth,
                            RefreshRate
                            );

        if (Status == EFI_UNSUPPORTED || Status == EFI_SUCCESS)  {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTestGenericFailureGuid,
                       L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to switch video device's mode",
                       L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        if (EFI_ERROR(Status)) {
          continue;
        }

        //
        // ClearScreen
        //
        Status = UgaDrawClearScreen (
                   UgaDraw,
                   HorizontalResolution,
                   VerticalResolution
                   );
        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"UgaDraw - Clear screen failure",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (BltBuffer != NULL) {
            gtBS->FreePool (BltBuffer);
            BltBuffer = NULL;
          }
          return Status;
        }
        //
        // Don't check the return status
        //

        //
        // Use BltBufferToVideo to display .bmp file
        // DestinationXY is the upper left of Video frame in this case
        //
        Status = UgaDraw->Blt (
                            UgaDraw,
                            BltBuffer,
                            EfiUgaBltBufferToVideo,
                            BmpSourceX,
                            BmpSourceY,
                            0,
                            0,
                            BmpWidth,
                            BmpHeight,
                            BmpDelta
                            );

        Status = UgaDraw->Blt (
                            UgaDraw,
                            BltBuffer,
                            EfiUgaBltBufferToVideo,
                            BmpSourceX,
                            BmpSourceY,
                            HorizontalResolution/2,
                            VerticalResolution/2,
                            BmpWidth,
                            BmpHeight,
                            BmpDelta
                            );

        Status = UgaDraw->Blt (
                            UgaDraw,
                            BltBuffer,
                            EfiUgaBltBufferToVideo,
                            BmpSourceX,
                            BmpSourceY,
                            HorizontalResolution/2,
                            0,
                            BmpWidth,
                            BmpHeight,
                            BmpDelta
                            );

        Status = UgaDraw->Blt (
                            UgaDraw,
                            BltBuffer,
                            EfiUgaBltBufferToVideo,
                            BmpSourceX,
                            BmpSourceY,
                            0,
                            VerticalResolution/2,
                            BmpWidth,
                            BmpHeight,
                            BmpDelta
                            );

        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_PASSED,
                       gUgaDrawExtensiveTestAssertionGuid042,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaBltBufferToVideo - Blt/EfiUgaBltBufferToVideo",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        //
        // Call Blt() with BltOperation being EfiUgaVideoToBltBuffer
        // to retrieve whole screen to a large BltBuffer
        //

        BltBufferWhole = NULL;
        BltBufferWhole2 = NULL;
        Size = HorizontalResolution * VerticalResolution * sizeof (EFI_UGA_PIXEL);
        Status = gtBS->AllocatePool (
                         EfiBootServicesData,
                         Size,
                         (VOID **)&BltBufferWhole
                         );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"BS.AllocatePool - Allocate pool",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (BltBuffer != NULL) {
            gtBS->FreePool (BltBuffer);
            BltBuffer = NULL;
          }
          return Status;
        }
        SctZeroMem (BltBufferWhole, Size);

        Status = gtBS->AllocatePool (
                         EfiBootServicesData,
                         Size,
                         (VOID **)&BltBufferWhole2
                         );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"BS.AllocatePool - Allocate pool",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (BltBuffer != NULL) {
            gtBS->FreePool (BltBuffer);
            BltBuffer = NULL;
          }
          if (BltBufferWhole != NULL) {
            gtBS->FreePool (BltBufferWhole);
            BltBufferWhole = NULL;
          }
          return Status;
        }
        SctZeroMem (BltBufferWhole2, Size);

        Status = UgaDraw->Blt (
                            UgaDraw,
                            BltBufferWhole,
                            EfiUgaVideoToBltBuffer,
                            0,
                            0,
                            0,
                            0,
                            HorizontalResolution,
                            VerticalResolution,
                            0
                            );


        DestinationX = 0;
        DestinationY = 0;
        Delta = 0;
        //
        // Change SourceX from 0 to HorizontalResolution by steps
        // Change SourceY from 0 to VerticalResolution by steps
        //
        VideoToBufferAssertion = EFI_TEST_ASSERTION_PASSED;
        AssertionType          = EFI_TEST_ASSERTION_PASSED;

        for (SourceX = 0; SourceX + Width < HorizontalResolution; SourceX += STEP_WIDTH_BUFFER)  {
          for (SourceY = 0; SourceY + Height < VerticalResolution; SourceY += STEP_WIDTH_BUFFER)  {

            Status = UgaDraw->Blt (
                                UgaDraw,
                                BltBuffer,
                                EfiUgaVideoToBltBuffer,
                                SourceX,
                                SourceY,
                                DestinationX,
                                DestinationY,
                                Width,
                                Height,
                                Delta
                                );

            //
            // Status check
            //
            if (EFI_ERROR(Status)) {
              VideoToBufferAssertion = EFI_TEST_ASSERTION_FAILED;
              break;
            }

            Status = UgaDraw->Blt (
                                UgaDraw,
                                BltBufferWhole2,
                                EfiUgaVideoToBltBuffer,
                                SourceX,
                                SourceY,
                                SourceX,
                                SourceY,
                                Width,
                                Height,
                                HorizontalResolution * sizeof (EFI_UGA_PIXEL)
                                );

            //
            // Status Check
            //
            if (EFI_ERROR(Status)) {
              VideoToBufferAssertion = EFI_TEST_ASSERTION_FAILED;
              break;
            }

            //
            // Verify BltBuffer with portion in BltBufferWhole
            //

            for (m = 0; m < Width * Height; m++) {
              IndexPos = SourceX + m % Width + (m / Width + SourceY) * HorizontalResolution;

              if (((*((UINT32 *)BltBuffer + m)) | 0xFF000000) != ((*((UINT32 *)BltBufferWhole + IndexPos)) | 0xFF000000)){

                //
                // Assertion failed
                //
                AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }
            }

            //
            // Verify BltBufferWhole2 with portion in BltBufferWhole
            //
            for (m = 0; m < Width * Height; m++) {
              IndexPos = SourceX + m % Width + (m / Width + SourceY) * HorizontalResolution;

              if (((*((UINT32 *)BltBufferWhole2 + IndexPos)) | 0xFF000000) != ((*((UINT32 *)BltBufferWhole + IndexPos)) | 0xFF000000)){
                //
                // Assertion failed
                //
                AssertionType = EFI_TEST_ASSERTION_FAILED;
                break;
              }
            }
          }
        }

        //
        //record assertion.
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       VideoToBufferAssertion,
                       gUgaDrawExtensiveTestAssertionGuid044,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d , Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       HorizontalResolution * sizeof(EFI_UGA_PIXEL),
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gUgaDrawExtensiveTestAssertionGuid045,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer, Pixel verification",
                       L"%a:%d: Status = %r,Width=%d, Height=%d, Delta=%d,Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       Width,
                       Height,
                       Delta,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        //
        // Free Buffer for next test data
        //
        if (BltBufferWhole != NULL) {
          Status = gtBS->FreePool (BltBufferWhole);
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
          }
        }

        if (BltBufferWhole2 != NULL) {
          Status = gtBS->FreePool (BltBufferWhole2);
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
          }
        }

      }//
    }  // For all mode
  }    //


  //
  // Restore video mode
  //
  Status = UgaDraw->SetMode (
                      UgaDraw,
                      HorizontalResolutionOrg,
                      VerticalResolutionOrg,
                      ColorDepthOrg,
                      RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to restore original video mode",
                 L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HorizontalResolutionOrg,
                 VerticalResolutionOrg,
                 ColorDepthOrg,
                 RefreshRateOrg
                 );


  //
  // Switch screen mode into original mode
  //
  Status = Console->SetMode (Console, ModeOrg);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into original mode",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeOrg,
                   Status
                   );
  }
  if (BltBuffer != NULL) {
          Status = gtBS->FreePool (BltBuffer);
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
          }
  }
  return EFI_SUCCESS;
}


//
// Addition test case
//

/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.Blt()  - EfiUgaVideoFill Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3.4
//
EFI_STATUS
EFIAPI
BBTestEfiUgaVideoFillStressAutoTest (
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
  EFI_CONSOLE_CONTROL_PROTOCOL         *Console;

  EFI_HANDLE                           *HandleBuffer;
  UINTN                                Size;

  UINT32                               HorizontalResolution, HorizontalResolutionOrg;
  UINT32                               VerticalResolution, VerticalResolutionOrg;
  UINT32                               ColorDepth, ColorDepthOrg;
  UINT32                               RefreshRate, RefreshRateOrg;
  EFI_CONSOLE_CONTROL_SCREEN_MODE      ModeOrg;

  UINTN                                SourceX;
  UINTN                                SourceY;
  UINTN                                DestinationX;
  UINTN                                DestinationY;
  UINTN                                Width;
  UINTN                                Height;
  UINTN                                Delta;
  EFI_UGA_PIXEL                        *BltBuffer, *BltBuffer2, *Blt;

  UINTN                                i, j, k, m, Index, IndexDemo;

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
  // Get ConsoleControl interface
  //

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   NULL,
                   &Size,
                   &HandleBuffer
                   );

  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->LocateHandleBuffer - Locate Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    return Status;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   (VOID **) &Console
                   );

  if (EFI_ERROR (Status)) {
    gtBS->FreePool (HandleBuffer);
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->HandleProtocol - Handle Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  gtBS->FreePool (HandleBuffer);

  //
  // Back screen mode and
  // Switch screen into Graphics Mode
  //
  Status = Console->GetMode (Console, &ModeOrg, NULL, NULL);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.GetMode - GetMode ",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeOrg,
                   Status
                   );
    return Status;

  }

  Status = Console->SetMode (Console, EfiConsoleControlScreenGraphics);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into graphics mode",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EfiConsoleControlScreenGraphics,
                   Status
                   );
    return Status;
  }

  //
  // Backup video mode
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolutionOrg,
                      &VerticalResolutionOrg,
                      &ColorDepthOrg,
                      &RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve video device information",
                 L"%a:%d:Mode=%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 ModeOrg,
                 Status
                 );

  //
  // for all demo mode, try it..
  //
  for (i = 0; i < DemoResolutionMax; i++) {
    HorizontalResolution = DemoResolution[i].HorizontalResolution;
    VerticalResolution = DemoResolution[i].VerticalResolution;
    for (j = 0; j < DemoRefreshRateMax; j++){
      RefreshRate = DemoRefreshRate[j];
      for (k = 0; k < DemoColorDepthMax; k++){
        ColorDepth = DemoColorDepth[k];

        //
        // switch screen into this demo mode
        //
        Status = UgaDraw->SetMode (
                            UgaDraw,
                            HorizontalResolution,
                            VerticalResolution,
                            ColorDepth,
                            RefreshRate
                            );

        if (Status == EFI_UNSUPPORTED || Status == EFI_SUCCESS) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTestGenericFailureGuid,
                       L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to switch video device's mode",
                       L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        if (EFI_ERROR(Status)) {
          continue;
        }


        for (IndexDemo = 0; IndexDemo < DEMO_SOURCE_POSITION_ENUM * DEMO_DESTINATION_POSITION_ENUM * DEMO_DELTA_ENUM * DEMO_WIDTH_HEIGHT_ENUM ; IndexDemo++) {
          //
          // Prepare test data
          //
          Index = IndexDemo;
          GetTestData (
            Index,
            &Width,
            &Height,
            &SourceX,
            &SourceY,
            &DestinationX,
            &DestinationY,
            &Delta,
            HorizontalResolution,
            VerticalResolution
            );


          //
          // Test data verification
          //
          if (DestinationX + Width > HorizontalResolution) {
            continue;
          }

          if (DestinationY + Height > VerticalResolution) {
            continue;
          }

          if (Width == 0 || Height == 0) {
            continue;
          }

          if (Delta == 0) {
            Delta = Width * sizeof (EFI_UGA_PIXEL);
          }

          //
          // Clear Screen
          //
          Status = UgaDrawClearScreen (
                     UgaDraw,
                     HorizontalResolution,
                     VerticalResolution
                     );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"UgaDraw - Clear screen failure",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            return Status;
          }

          //
          // Allocate Buffer for BltBuffer & BltBuffer2
          //
          BltBuffer = NULL;
          BltBuffer2 = NULL;
          Size = Width * Height * sizeof (EFI_UGA_PIXEL);
          Status = gtBS->AllocatePool (
                           EfiBootServicesData,
                           Size,
                           (VOID **)&BltBuffer
                           );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.AllocatePool - Allocate pool",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            return Status;
          }
          SctZeroMem (BltBuffer, Size);

          Size = Width * Height * sizeof (EFI_UGA_PIXEL);
          Status = gtBS->AllocatePool (
                           EfiBootServicesData,
                           Size,
                           (VOID **)&BltBuffer2
                           );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.AllocatePool - Allocate pool",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            if (BltBuffer != NULL) {
              gtBS->FreePool (BltBuffer);
            }
            return Status;
          }
          SctZeroMem (BltBuffer2, Size);

          //Blt = (EFI_UGA_PIXEL*)((UINT8*)BltBuffer+SourceY*Delta+SourceX*sizeof(EFI_UGA_PIXEL)) ;
          Blt = BltBuffer;
          Blt->Blue  = 0xFF;
          Blt->Green = 0x00;
          Blt->Red   = 0x00;
          Blt->Reserved = 0;
          //
          // Call Blt() with BltOperation being EfiUgaVideo Fill
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaVideoFill,
                              SourceX,
                              SourceY,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              Delta
                              );

          if (EFI_ERROR(Status)) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawInterfaceTestAssertionGuid020,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill",
                         L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d,, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         SourceX,
                         SourceY,
                         DestinationX,
                         DestinationY,
                         Width,
                         Height,
                         Delta,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );

          //
          // Call Blt() with BltOperation being EfiUgaVideoToBltBuffer
          // to retrieve rectangles drawn by last EfiUgaVideoFill operation
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer2,
                              EfiUgaVideoToBltBuffer,
                              DestinationX,
                              DestinationY,
                              0,
                              0,
                              Width,
                              Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawInterfaceTestAssertionGuid021,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                         L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         DestinationX,
                         DestinationY,
                         0, 0,
                         Width,
                         Height,
                         Delta,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );

          //
          // All the retrieve rectangle should be with same pixel!
          //
          AssertionType = EFI_TEST_ASSERTION_PASSED;
          for (m = 0; m < Width * Height; m++) {
            if (((*((UINT32 *)BltBuffer2 + m)) | 0xFF000000) != ((*((UINT32 *)Blt)) | 0xFF000000)){

              //
              // Assertion failed
              //
              AssertionType = EFI_TEST_ASSERTION_FAILED;
              break;
            }
          }

          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawInterfaceTestAssertionGuid023,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill, Pixel verification",
                         L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Blt=%d,, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         DestinationX,
                         DestinationY,
                         0, 0,
                         Width,
                         Height,
                         Delta,
                         *((UINT32 *)Blt),
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );

          //
          // Free Buffer for next test data
          //
          if (BltBuffer != NULL) {
            Status = gtBS->FreePool (BltBuffer);
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
            }
          }

          if (BltBuffer2 != NULL) {
            Status = gtBS->FreePool (BltBuffer2);
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
            }
          }
        }
      }//
    }  // This is for prepared mode
  }    //

  //
  // Restore video mode
  //
  Status = UgaDraw->SetMode (
                      UgaDraw,
                      HorizontalResolutionOrg,
                      VerticalResolutionOrg,
                      ColorDepthOrg,
                      RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to restore original video mode",
                 L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HorizontalResolutionOrg,
                 VerticalResolutionOrg,
                 ColorDepthOrg,
                 RefreshRateOrg
                 );


  //
  // Switch screen mode into original mode
  //
  Status = Console->SetMode (Console, ModeOrg);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gTestGenericFailureGuid,
                    L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into original mode",
                    L"%a:%d:Mode=%d, Status = %r",
                    __FILE__,
                    (UINTN)__LINE__,
                    ModeOrg,
                    Status
                    );
  }

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.Blt()  - EfiUgaVideoToBltBuffer/EfiUgaBltBufferToVideo Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3.5
//
EFI_STATUS
EFIAPI
BBTestEfiUgaVideoBltBufferStressAutoTest (
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
  EFI_CONSOLE_CONTROL_PROTOCOL         *Console;

  EFI_HANDLE                           *HandleBuffer;
  UINTN                                Size;

  UINT32                               HorizontalResolution, HorizontalResolutionOrg;
  UINT32                               VerticalResolution, VerticalResolutionOrg;
  UINT32                               ColorDepth, ColorDepthOrg;
  UINT32                               RefreshRate, RefreshRateOrg;
  EFI_CONSOLE_CONTROL_SCREEN_MODE      ModeOrg;

  UINTN                                SourceX;
  UINTN                                SourceY;
  UINTN                                DestinationX;
  UINTN                                DestinationY;
  UINTN                                Width;
  UINTN                                Height;
  UINTN                                Delta;
  EFI_UGA_PIXEL                        *BltBuffer, *BltBuffer2;
  EFI_UGA_PIXEL                        *BltBuffer3, *BltBuffer4;

  UINTN                                i, j, k, m, Index, IndexDemo;
  UINTN                                IndexWidth, IndexHeight, IndexPos;

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
  // Get ConsoleControl interface
  //

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   NULL,
                   &Size,
                   &HandleBuffer
                   );

  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->LocateHandleBuffer - Locate Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    return Status;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   (VOID **) &Console
                   );

  if (EFI_ERROR (Status)) {
    gtBS->FreePool (HandleBuffer);
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->HandleProtocol - Handle Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  gtBS->FreePool (HandleBuffer);

  //
  // Back screen mode and
  // Switch screen into Graphics Mode
  //
  Status = Console->GetMode (Console, &ModeOrg, NULL, NULL);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.GetMode - GetMode ",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeOrg,
                   Status
                   );
    return Status;

  }

  Status = Console->SetMode (Console, EfiConsoleControlScreenGraphics);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into graphics mode",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EfiConsoleControlScreenGraphics,
                   Status
                   );
    return Status;
  }

  //
  // Backup video mode
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolutionOrg,
                      &VerticalResolutionOrg,
                      &ColorDepthOrg,
                      &RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve video device information",
                 L"%a:%d:Mode=%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 ModeOrg,
                 Status
                 );

  //
  // for all demo mode, try it..
  //
  for (i = 0; i < DemoResolutionMax; i++) {
    HorizontalResolution = DemoResolution[i].HorizontalResolution;
    VerticalResolution = DemoResolution[i].VerticalResolution;
    for (j = 0; j < DemoRefreshRateMax; j++){
      RefreshRate = DemoRefreshRate[j];
      for (k = 0; k < DemoColorDepthMax; k++){
        ColorDepth = DemoColorDepth[k];
        //
        // switch screen into this demo mode
        //

        Status = UgaDraw->SetMode (
                            UgaDraw,
                            HorizontalResolution,
                            VerticalResolution,
                            ColorDepth,
                            RefreshRate
                            );

        if (Status == EFI_UNSUPPORTED || Status == EFI_SUCCESS)  {
          AssertionType = EFI_TEST_ASSERTION_PASSED;

        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTestGenericFailureGuid,
                       L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to switch video device's mode",
                       L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        if (EFI_ERROR(Status)) {
          continue;
        }

        //
        // Load BltBuffer from some .bmp file, and set width&heigth
        //
        Status = LoadBmp (&BltBuffer3, &Width, &Height);
        if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"UgaDraw - LoadBmp failure",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          return Status;
        }

        SourceX = 0;
        SourceY = 0;
        DestinationX = 0;
        DestinationY = 0;
        Delta = 0;

        //
        // Use BltBufferToVideo to display .bmp file
        // SourceXY is the upper left of Video frame in this case
        //

        Delta = Width * sizeof (EFI_UGA_PIXEL);
        Status = UgaDraw->Blt (
                            UgaDraw,
                            BltBuffer3,
                            EfiUgaBltBufferToVideo,
                            0,
                            0,
                            SourceX,
                            SourceY,
                            Width,
                            Height,
                            Delta
                            );

        if (EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gUgaDrawInterfaceTestAssertionGuid032,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                       L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       0,
                       0,
                       SourceX,
                       SourceY,
                       Width,
                       Height,
                       Delta
                       );


        //
        // Allocate buffer for BltBuffer4
        //
        //BltBuffer4 = SctAllocateZeroPool (Width * Height * sizeof (EFI_UGA_PIXEL));
        Size = Width * Height * sizeof (EFI_UGA_PIXEL);
        Status = gtBS->AllocatePool (
                         EfiBootServicesData,
                         Size,
                         (VOID **)&BltBuffer4
                         );
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"BS.AllocatePool - Allocate pool",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (BltBuffer3!=NULL) {
            Status = gtBS->FreePool (BltBuffer3);
            BltBuffer3 = NULL;
          }
          return Status;
        }
        SctZeroMem (BltBuffer4, Size);
        //
        // Use BltVideoToBuffer to retrieve screen in to BltBuffer
        // This time, use BltBuffer4
        //

        Status = UgaDraw->Blt (
                            UgaDraw,
                            BltBuffer4,
                            EfiUgaVideoToBltBuffer,
                            SourceX,
                            SourceY,
                            0,
                            0,
                            Width,
                            Height,
                            Delta
                            );

        if (EFI_ERROR(Status)) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gUgaDrawInterfaceTestAssertionGuid033,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                       L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       SourceX,
                       SourceY,
                       0,
                       0,
                       Width,
                       Height,
                       Delta
                       );

        //
        // Compare BltBuffer3 with BltBuffer4 the two should be same
        //
        AssertionType = EFI_TEST_ASSERTION_PASSED;
        for (m = 0; m < Width * Height; m++) {
          if (((*((UINT32 *)BltBuffer3 + m)) | 0xFF000000) != ((*((UINT32 *)BltBuffer4 + m)) | 0xFF000000)){
            //
            // Assertion failed
            //
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
          }
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gUgaDrawInterfaceTestAssertionGuid034,
                       L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer, Pixel verification",
                       L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       SourceX,
                       SourceY,
                       0, 0,
                       Width,
                       Height,
                       Delta
                       );

        if (BltBuffer3 != NULL) {
          Status = gtBS->FreePool (BltBuffer3);
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
          }
          BltBuffer3 = NULL;
        }

        if (BltBuffer4 != NULL) {
          Status = gtBS->FreePool (BltBuffer4);
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
          }
          BltBuffer4 = NULL;
        }

        for (IndexDemo = 0; IndexDemo < DEMO_SOURCE_POSITION_ENUM * DEMO_DESTINATION_POSITION_ENUM * DEMO_DELTA_ENUM * DEMO_WIDTH_HEIGHT_ENUM ; IndexDemo++) {
          //
          // Prepare test data
          //
          Index = IndexDemo;
          GetTestData (
            Index,
            &Width,
            &Height,
            &SourceX,
            &SourceY,
            &DestinationX,
            &DestinationY,
            &Delta,
            HorizontalResolution,
            VerticalResolution
            );

          //
          // Test data verification
          // Here SourceXY is the Upper left hand of Video
          // DestinationXY is the Upper left hand fo BltBuffer
          //
          if (SourceX + Width > HorizontalResolution) {
            continue;
          }

          if (SourceY + Height > VerticalResolution) {
            continue;
          }

          if (Width == 0 || Height == 0) {
            continue;
          }

          if (Delta == 0) {
            Delta = Width * sizeof (EFI_UGA_PIXEL);
          }

          //
          // Clear Screen
          //
          Status = UgaDrawClearScreen (
                     UgaDraw,
                     HorizontalResolution,
                     VerticalResolution
                     );

          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"UgaDraw - Clear screen failure",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            return Status;
          }

          //
          // Allocate Buffer for BltBuffer & BltBuffer2
          // BltBuffer should be large than (Width+DestinationX)*(Height+DestinationY)
          //
          BltBuffer = NULL;
          BltBuffer2 = NULL;
          Size = (Width + DestinationX)* (Height + DestinationY) * sizeof (EFI_UGA_PIXEL);
          Status = gtBS->AllocatePool (
                           EfiBootServicesData,
                           Size,
                           (VOID **)&BltBuffer
                           );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.AllocatePool - Allocate pool",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            return Status;
          }
          SctZeroMem (BltBuffer, Size);

          Size = Width * Height * sizeof (EFI_UGA_PIXEL);
          Status = gtBS->AllocatePool (
                           EfiBootServicesData,
                           Size,
                           (VOID **)&BltBuffer2
                           );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.AllocatePool - Allocate pool",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            if (BltBuffer != NULL) {
              gtBS->FreePool (BltBuffer);
              BltBuffer = NULL;
            }
            return Status;
          }
          SctZeroMem (BltBuffer2, Size);

          //
          // Delta should reflect the length of a row correctly
          //
          Delta = (Width + DestinationX) * sizeof (EFI_UGA_PIXEL);


          //
          // Actually, should output screen with some picture.
          //
          Status = OutputScreen (UgaDraw, SourceX, SourceY, DestinationX, DestinationY);
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"UgaDraw - Output screen failure",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            if (BltBuffer != NULL) {
              Status = gtBS->FreePool (BltBuffer);
              BltBuffer = NULL;
            }
            if (BltBuffer2 != NULL) {
              Status = gtBS->FreePool (BltBuffer2);
              BltBuffer2 = NULL;
            }
            return Status;
          }
          //
          // Call Blt() with BltOperation being EfiUgaVideoToBltBuffer
          // Operation to be tested! (1)
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaVideoToBltBuffer,
                              SourceX,
                              SourceY,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              Delta
                              );


          if (EFI_ERROR(Status)) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawInterfaceTestAssertionGuid036,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                         L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         SourceX,
                         SourceY,
                         DestinationX,
                         DestinationY,
                         Width,
                         Height,
                         Delta,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );
          Status = UgaDrawClearScreen (
                     UgaDraw,
                     HorizontalResolution,
                     VerticalResolution
                     );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"UgaDraw - Clear screen failure",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            if (BltBuffer != NULL) {
              Status = gtBS->FreePool (BltBuffer);
              BltBuffer = NULL;
            }
            if (BltBuffer2 != NULL) {
              Status = gtBS->FreePool (BltBuffer2);
              BltBuffer2 = NULL;
            }
            return Status;
          }

          //
          // Call Blt() with BltOperation being EfiUgaBltBufferToVideo to
          // re-draw Buffer into display
          // Note: Source and Destination should reverse with that of VideoToBltBuffer operation
          //

          //
          // Operation to be tested! (2)
          //

          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaBltBufferToVideo,
                              DestinationX,
                              DestinationY,
                              SourceX,
                              SourceY,
                              Width,
                              Height,
                              Delta
                              );

          if (EFI_ERROR(Status)) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawInterfaceTestAssertionGuid037,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                         L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         DestinationX,
                         DestinationY,
                         SourceX,
                         SourceY,
                         Width,
                         Height,
                         Delta,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );

          //
          // Call Blt() with BltOperatoin being EfiUgaVideoToBltBuffer again
          // This time, use BltBuffer2 and save it
          //

          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer2,
                              EfiUgaVideoToBltBuffer,
                              SourceX,
                              SourceY,
                              0,
                              0,
                              Width,
                              Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawInterfaceTestAssertionGuid038,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                         L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         SourceX,
                         SourceY,
                         0,
                         0,
                         Width,
                         Height,
                         0,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );

          //
          // Compare BltBuffer with BltBuffer2 the two should be same
          // Operation to be tested! (3)
          //
          AssertionType = EFI_TEST_ASSERTION_PASSED;
          for (m = 0; m < Width * Height; m++) {
            IndexWidth  = m % Width;
            IndexHeight = m / Width + DestinationY;
            IndexPos = IndexWidth + DestinationX + IndexHeight * (Delta / sizeof (EFI_UGA_PIXEL));

            if (((*((UINT32 *)BltBuffer + IndexPos)) | 0xFF000000) != ((*((UINT32 *)BltBuffer2 + m)) | 0xFF000000)){
              //
              // Assertion failed
              //
              AssertionType = EFI_TEST_ASSERTION_FAILED;
              break;
            }
          }

          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawInterfaceTestAssertionGuid040,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer, Pixel verification",
                         L"%a:%d: Status = %r,Video Source=(%dx%d),Buffer Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         SourceX,
                         SourceY,
                         DestinationX,
                         DestinationY,
                         Width,
                         Height,
                         Delta,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );

          //
          // Free Buffer for next test data
          //
          if (BltBuffer != NULL) {
            Status = gtBS->FreePool (BltBuffer);
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
            }
          }

          if (BltBuffer2 != NULL) {
            Status = gtBS->FreePool (BltBuffer2);
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
            }
          }
        }
      }//
    }  // This is for prepared mode
  }    //

  //
  // Restore video mode
  //
  Status = UgaDraw->SetMode (
                      UgaDraw,
                      HorizontalResolutionOrg,
                      VerticalResolutionOrg,
                      ColorDepthOrg,
                      RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to restore original video mode",
                 L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HorizontalResolutionOrg,
                 VerticalResolutionOrg,
                 ColorDepthOrg,
                 RefreshRateOrg
                 );


  //
  // Switch screen mode into original mode
  //
  Status = Console->SetMode (Console, ModeOrg);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into original mode",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeOrg,
                   Status
                   );
  }

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.Blt()  - EfiUgaVideoToVideo Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3.6
//
EFI_STATUS
EFIAPI
BBTestEfiUgaVideoToVideoStressAutoTest (
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
  EFI_CONSOLE_CONTROL_PROTOCOL         *Console;

  EFI_HANDLE                           *HandleBuffer;
  UINTN                                Size;

  UINT32                               HorizontalResolution, HorizontalResolutionOrg;
  UINT32                               VerticalResolution, VerticalResolutionOrg;
  UINT32                               ColorDepth, ColorDepthOrg;
  UINT32                               RefreshRate, RefreshRateOrg;
  EFI_CONSOLE_CONTROL_SCREEN_MODE      ModeOrg;

  UINTN                                SourceX;
  UINTN                                SourceY;
  UINTN                                DestinationX;
  UINTN                                DestinationY;
  UINTN                                Width;
  UINTN                                Height;
  UINTN                                Delta;
  EFI_UGA_PIXEL                        *BltBuffer, *BltBuffer2;

  UINTN                                i, j, k, m, Index, IndexDemo;

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
  // Get ConsoleControl interface
  //

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   NULL,
                   &Size,
                   &HandleBuffer
                   );

  if (EFI_ERROR (Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->LocateHandleBuffer - Locate Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    return Status;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gBlackBoxEfiConsoleControlProtocolGuid,
                   (VOID **) &Console
                   );

  if (EFI_ERROR (Status)) {
    gtBS->FreePool (HandleBuffer);
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"tBS->HandleProtocol - Handle Console Control Protocol",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  gtBS->FreePool (HandleBuffer);

  //
  // Back screen mode and
  // Switch screen into Graphics Mode
  //
  Status = Console->GetMode (Console, &ModeOrg, NULL, NULL);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.GetMode - GetMode ",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeOrg,
                   Status
                   );
    return Status;

  }

  Status = Console->SetMode (Console, EfiConsoleControlScreenGraphics);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into graphics mode",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   EfiConsoleControlScreenGraphics,
                   Status
                   );
    return Status;
  }

  //
  // Backup video mode
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolutionOrg,
                      &VerticalResolutionOrg,
                      &ColorDepthOrg,
                      &RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve video device information",
                 L"%a:%d:Mode=%d, Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 ModeOrg,
                 Status
                 );

  //
  // for all demo mode, try it..
  //
  for (i = 0; i < DemoResolutionMax; i++) {
    HorizontalResolution = DemoResolution[i].HorizontalResolution;
    VerticalResolution = DemoResolution[i].VerticalResolution;
    for (j = 0; j < DemoRefreshRateMax; j++){
      RefreshRate = DemoRefreshRate[j];
      for (k = 0; k < DemoColorDepthMax; k++){
        ColorDepth = DemoColorDepth[k];
        //
        // switch screen into this demo mode
        //
        Status = UgaDraw->SetMode (
                            UgaDraw,
                            HorizontalResolution,
                            VerticalResolution,
                            ColorDepth,
                            RefreshRate
                            );
        if (Status == EFI_UNSUPPORTED || Status == EFI_SUCCESS)  {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        } else {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }

        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTestGenericFailureGuid,
                       L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to switch video device's mode",
                       L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

        if (EFI_ERROR(Status)) {
          continue;
        }

        for (IndexDemo = 0; IndexDemo < DEMO_SOURCE_POSITION_ENUM * DEMO_DESTINATION_POSITION_ENUM * DEMO_DELTA_ENUM * DEMO_WIDTH_HEIGHT_ENUM ; IndexDemo++) {
          //
          // Prepare test data
          //
          Index = IndexDemo;
          GetTestData (
            Index,
            &Width,
            &Height,
            &SourceX,
            &SourceY,
            &DestinationX,
            &DestinationY,
            &Delta,
            HorizontalResolution,
            VerticalResolution
            );

          //
          // Test data verification
          //
          if (DestinationX + Width > HorizontalResolution) {
            continue;
          }

          if (DestinationY + Height > VerticalResolution) {
            continue;
          }

          if (SourceX + Width > HorizontalResolution) {
            continue;
          }

          if (SourceY + Height > VerticalResolution) {
            continue;
          }

          if (SourceX == DestinationX && SourceY == DestinationY) {
            continue;
          }

          if (Width == 0 || Height == 0) {
            continue;
          }

          if (Delta == 0) {
            Delta = Width * sizeof (EFI_UGA_PIXEL);
          }

          //
          // Clear Screen
          //
          Status = UgaDrawClearScreen (
                     UgaDraw,
                     HorizontalResolution,
                     VerticalResolution
                     );
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"UgaDraw - Clear Screen failure",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            return Status;
          }
          //
          // Allocate Buffer for BltBuffer & BltBuffer2
          //
          BltBuffer = NULL;
          BltBuffer2 = NULL;
          Size = Width * Height * sizeof (EFI_UGA_PIXEL);
          Status = gtBS->AllocatePool (
                           EfiBootServicesData,
                           Size,
                           (VOID **)&BltBuffer
                           );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.AllocatePool - Allocate pool",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            return Status;
          }
          SctZeroMem (BltBuffer, Size);

          Size = Width * Height * sizeof (EFI_UGA_PIXEL);
          Status = gtBS->AllocatePool (
                           EfiBootServicesData,
                           Size,
                           (VOID **)&BltBuffer2
                           );
          if (EFI_ERROR (Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"BS.AllocatePool - Allocate pool",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            if (BltBuffer != NULL) {
              gtBS->FreePool (BltBuffer);
            }
            return Status;
          }
          SctZeroMem (BltBuffer2, Size);

          //
          // Actually, should output screen with some picture.
          //

          Status = OutputScreen (UgaDraw, SourceX, SourceY, DestinationX, DestinationY);
          if (EFI_ERROR(Status)) {
            StandardLib->RecordAssertion (
                           StandardLib,
                           EFI_TEST_ASSERTION_FAILED,
                           gTestGenericFailureGuid,
                           L"UgaDraw - Output screen failure",
                           L"%a:%d:Status - %r",
                           __FILE__,
                           (UINTN)__LINE__,
                           Status
                           );
            if (BltBuffer != NULL) {
              Status = gtBS->FreePool (BltBuffer);
              BltBuffer = NULL;
            }
            if (BltBuffer2 != NULL) {
              Status = gtBS->FreePool (BltBuffer2);
              BltBuffer2 = NULL;
            }
            return Status;
          }
          //
          // Call Blt() with BltOperation being EfiUgaVideoToBltBuffer
          //
          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer,
                              EfiUgaVideoToBltBuffer,
                              SourceX,
                              SourceY,
                              0,
                              0,
                              Width,
                              Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawInterfaceTestAssertionGuid049,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                         L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         SourceX,
                         SourceY,
                         0,
                         0,
                         Width,
                         Height,
                         Delta,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );

          //
          // Call Blt() with BltOperation being EfiUgaVideoToVideo to copy screen
          //

          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer2,
                              EfiUgaVideoToVideo,
                              SourceX,
                              SourceY,
                              DestinationX,
                              DestinationY,
                              Width,
                              Height,
                              Delta
                              );

          if (EFI_ERROR(Status)) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawInterfaceTestAssertionGuid050,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToVideo - Blt/EfiUgaVideoToVideo",
                         L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         SourceX,
                         SourceY,
                         DestinationX,
                         DestinationY,
                         Width,
                         Height,
                         Delta,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );

          //
          // Call Blt() with BltOperatoin being EfiUgaVideoToBltBuffer again
          // This time, use BltBuffer2, and the retrieved area should be destination rectangle
          //

          Status = UgaDraw->Blt (
                              UgaDraw,
                              BltBuffer2,
                              EfiUgaVideoToBltBuffer,
                              DestinationX,
                              DestinationY,
                              0,
                              0,
                              Width,
                              Height,
                              0
                              );

          if (EFI_ERROR(Status)) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
          } else {
            AssertionType = EFI_TEST_ASSERTION_PASSED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawInterfaceTestAssertionGuid051,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                         L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         DestinationX,
                         DestinationY,
                         0, 0,
                         Width,
                         Height,
                         Delta,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );

          //
          // Compare BltBuffer with BltBuffer2
          // the two should be same
          //
          AssertionType = EFI_TEST_ASSERTION_PASSED;
          for (m = 0; m < Width * Height; m++) {
            if (((*((UINT32 *)BltBuffer + m)) | 0xFF000000) != ((*((UINT32 *)BltBuffer2 + m)) | 0xFF000000)){
              //
              // Assertion failed
              //
              AssertionType = EFI_TEST_ASSERTION_FAILED;
              break;
            }
          }

          StandardLib->RecordAssertion (
                         StandardLib,
                         AssertionType,
                         gUgaDrawInterfaceTestAssertionGuid053,
                         L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToVideo - Blt/EfiUgaVideoToVideo, Pixel verification",
                         L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d ,, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         SourceX,
                         SourceY,
                         DestinationX,
                         DestinationY,
                         Width,
                         Height,
                         Delta,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );


          //
          // Free Buffer for next test data
          //
          if (BltBuffer != NULL) {
            Status = gtBS->FreePool (BltBuffer);
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
            }
          }

          if (BltBuffer2 != NULL) {
            Status = gtBS->FreePool (BltBuffer2);
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
            }
          }
        }
      }//
    }  // This is for prepared mode
  }    //

  //
  // Restore video mode
  //
  Status = UgaDraw->SetMode (
                      UgaDraw,
                      HorizontalResolutionOrg,
                      VerticalResolutionOrg,
                      ColorDepthOrg,
                      RefreshRateOrg
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
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to restore original video mode",
                 L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HorizontalResolutionOrg,
                 VerticalResolutionOrg,
                 ColorDepthOrg,
                 RefreshRateOrg
                 );


  //
  // Switch screen mode into original mode
  //
  Status = Console->SetMode (Console, ModeOrg);
  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_CONSOLE_CONTROL_PROTOCOL.SetMode - SetMode to switch into original mode",
                   L"%a:%d:Mode=%d, Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   ModeOrg,
                   Status
                   );
  }

  return EFI_SUCCESS;
}