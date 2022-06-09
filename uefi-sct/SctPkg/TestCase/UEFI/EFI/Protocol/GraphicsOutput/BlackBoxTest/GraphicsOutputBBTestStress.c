/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  GraphicsOutputBBTestStress.c

Abstract:

  Extensive Test Cases of Graphics Output Protocol

References:
  UEFI 2.0 Specification
  Graphics Output Protocol Test Design Specification
  UEFI/Tiano DXE Test Case Writer's Guide

Revision History

--*/
#include "SctLib.h"
#include "GraphicsOutputBBTest.h"

//
// TDS 4.3.1
//
EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputBltVideoFillStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoFill/VideoToBuffer Extensive Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
{
  EFI_STATUS                          Status;
  EFI_STATUS                          Status1;
  EFI_STATUS                          Status2;

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_GRAPHICS_OUTPUT_PROTOCOL        *GraphicsOutput;

  UINT32                              Index;

  UINT32                              MaxMode;
  UINT32                              CurrentMode;

  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer2;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *Blt;

  UINTN                               HorizontalResolution;
  UINTN                               VerticalResolution;
  UINTN                               SourceX;
  UINTN                               SourceY;
  UINTN                               DestinationX;
  UINTN                               DestinationY;
  UINTN                               Width;
  UINTN                               Height;
  UINTN                               Delta;
  UINTN                               Size;
  UINTN                               m;
  UINTN                               indexmode;

  SourceX       = 0;
  SourceY       = 0;
  DestinationX  = 0;
  DestinationY  = 0;
  Delta         = 0;

  GraphicsOutput = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) ClientInterface;

  if ((Status = InitTestEnv (SupportHandle, &StandardLib, GraphicsOutput)) != EFI_SUCCESS) {
    return Status;

  }

  CurrentMode = GraphicsOutput->Mode->Mode;
  MaxMode     = GraphicsOutput->Mode->MaxMode;

  //
  //  Test Blt Operations in All mode support by Graphics Output Device
  //
  for (Index = 0; Index < MaxMode; Index++) {

    Status                = GraphicsOutput->SetMode (GraphicsOutput, Index);

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      return Status;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                   L"%a:%d: Mode index=%d,Status:%r, Expected:EFI_SUCCESS, Resolution=(%d * %d)",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Index,
                   (UINTN) Status,
                   (UINTN) HorizontalResolution,
                   (UINTN) VerticalResolution
                   );

    for (indexmode = 0;
         indexmode < DEMO_SOURCE_POSITION_ENUM *
         DEMO_DESTINATION_POSITION_ENUM *
         DEMO_DELTA_ENUM *
         DEMO_WIDTH_HEIGHT_ENUM;
       indexmode++
        ) {
      //
      // Prepare test data
      //
      GetTestData (
        indexmode,
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
        Delta = Width * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
      }

      Status = GraphicsOutputClearScreen (
                 GraphicsOutput,
                 HorizontalResolution,
                 VerticalResolution
                 );
      if (EFI_ERROR (Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTestGenericFailureGuid,
                       L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer stress auto test - GraphicsOutputClearScreen",
                       L"%a:%d: Status = %r",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__,
                       (UINTN) Status
                       );
        return Status;
      }

      Size        = Width * Height * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);

      BltBuffer   = NULL;
      BltBuffer2  = NULL;
      Status = gtBS->AllocatePool (
                       EfiBootServicesData,
                       Size,
                       (VOID **) &BltBuffer
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.AllocatePool - Allocate pool",
                       L"%a:%d:Status - %r",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__,
                       (UINTN) Status
                       );
        return Status;
      }

      SctZeroMem (BltBuffer, Size);

      Status = gtBS->AllocatePool (
                       EfiBootServicesData,
                       Size,
                       (VOID **) &BltBuffer2
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.AllocatePool - Allocate pool",
                       L"%a:%d:Status - %r",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__,
                       (UINTN) Status
                       );
        return Status;
      }              
                     
      SctZeroMem (BltBuffer2, Size);

      //
      //  Allocate BltBuffer for Blt Operations Test
      //
      //  The BltBuffer only needed in Blt Operation
      //
      //
      //
      Blt           = BltBuffer;
      Blt->Blue     = 0xFF;
      Blt->Green    = 0x00;
      Blt->Red      = 0x00;
      Blt->Reserved = 0;

      //
      // Call Blt() with BltOperation being EfiUgaVideo Fill
      //
      Status1 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer,
                                  EfiBltVideoFill,
                                  SourceX,
                                  SourceY,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  Delta
                                  );

      //
      // Call Blt() with BltOperation being EfiUgaVideoToBltBuffer
      // to retrieve rectangles drawn by last EfiUgaVideoFill operation
      //
      Status2 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer2,
                                  EfiBltVideoToBltBuffer,
                                  DestinationX,
                                  DestinationY,
                                  0,
                                  0,
                                  Width,
                                  Height,
                                  0
                                  );

      //
      // All the retrieve rectangle should be with same pixel!
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      for (m = 0; m < Width * Height; m++) {

        if (((*((UINT32 *) BltBuffer2 + m)) | 0xFF000000) != ((*((UINT32 *) Blt)) | 0xFF000000)) {
          //
          // Assertion failed
          //
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          m++;
          break;
        }
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gGraphicsOutputBltVideoFillStressAutoTestAssertionGuid001,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFill - Blt/EfiBltVideoFill, pixel verification",
                     L"%a:%d: Status = %r, Mode index = %d, Pixel Index = %d, Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Pixel Get = 0x%8x, Pixel expected = 0x%8x, Delta=%d, Blt=%d",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status,
                     (UINTN) Index,
                     (UINTN) m,
                     (UINTN) SourceX,
                     (UINTN) SourceY,
                     (UINTN) DestinationX,
                     (UINTN) DestinationY,
                     (UINTN) Width,
                     (UINTN) Height,
                     (UINTN) *((UINT32 *) BltBuffer2 + m - 1) | 0xFF000000,
                     (UINTN) *((UINT32 *) Blt) | 0xFF000000,
                     (UINTN) Delta,
                     (UINTN) *((UINT32 *) Blt)
                     );

      if (EFI_ERROR (Status1)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gGraphicsOutputBltVideoFillStressAutoTestAssertionGuid002,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiBltVideoFill",
                     L"%a:%d: Status = %r, Mode index = %d,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status1,
                     (UINTN) Index,
                     (UINTN) SourceX,
                     (UINTN) SourceY,
                     (UINTN) DestinationX,
                     (UINTN) DestinationY,
                     (UINTN) Width,
                     (UINTN) Height,
                     (UINTN) Delta
                     );
      if (EFI_ERROR (Status2)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gGraphicsOutputBltVideoFillStressAutoTestAssertionGuid003,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer",
                     L"%a:%d: Status = %r, Mode index = %d, Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status2,
                     (UINTN) Index,
                     (UINTN) DestinationX,
                     (UINTN) DestinationY,
                     (UINTN) 0,
                     (UINTN) 0,
                     (UINTN) Width,
                     (UINTN) Height,
                     (UINTN) Delta
                     );

      if (BltBuffer != NULL) {
        tBS->FreePool (BltBuffer);
      }

      if (BltBuffer2 != NULL) {
        tBS->FreePool (BltBuffer2);
      }
      //
      // Wait for some time
      //
      gtBS->Stall (15000);

    }
  }
  //
  // restore the orignal Mode
  //
  Status = GraphicsOutput->SetMode (GraphicsOutput, CurrentMode);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test,restore the orignal Mode",
                 L"%a:%d: Mode index = %d, Status:%r, Expected:EFI_SUCCESS",
                 (UINTN) __FILE__,
                 (UINTN) (UINTN)__LINE__,
                 (UINTN) CurrentMode,
                 (UINTN) Status
                 );

  return EFI_SUCCESS;

}

//
// TDS 4.3.2
//
EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputBltVideoBltBufferStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoToBuffer/BltBufferToVideo Extensive Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

 --*/
{

  EFI_STATUS                          Status;
  EFI_STATUS                          Status1;
  EFI_STATUS                          Status2;

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_GRAPHICS_OUTPUT_PROTOCOL        *GraphicsOutput;

  UINT32                              Index;

  UINT32                              MaxMode;
  UINT32                              CurrentMode;

  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer2;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer3;

  UINTN                               SourceX;
  UINTN                               SourceY;
  UINTN                               DestinationX;
  UINTN                               DestinationY;
  UINTN                               Width;
  UINTN                               Wt;
  UINTN                               Height;
  UINTN                               Ht;
  UINTN                               Delta;
  UINTN                               Size;
  UINTN                               m;
  UINTN                               indexmode;
  UINTN                               IndexWidth;
  UINTN                               IndexHeight;
  UINTN                               IndexPos;
  UINT32                              HorizontalResolution;
  UINT32                              VerticalResolution;

  SourceX       = 0;
  SourceY       = 0;
  DestinationX  = 0;
  DestinationY  = 0;
  Delta         = 0;

  GraphicsOutput = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) ClientInterface;

  if ((Status = InitTestEnv (SupportHandle, &StandardLib, GraphicsOutput)) != EFI_SUCCESS) {
    return Status;

  }

  CurrentMode = GraphicsOutput->Mode->Mode;
  MaxMode     = GraphicsOutput->Mode->MaxMode;

  BltBuffer   = NULL;
  BltBuffer2  = NULL;
  BltBuffer3  = NULL;

  //
  //  Test Blt Operations in All mode support by Graphics Output Device
  //
  for (Index = 0; Index < MaxMode; Index++) {

    Status                = GraphicsOutput->SetMode (GraphicsOutput, Index);

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      return Status;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                   L"%a:%d: Mode index=%d,Status:%r, Expected:EFI_SUCCESS, Resolution=(%d * %d)",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Index,
                   (UINTN) Status,
                   (UINTN) HorizontalResolution,
                   (UINTN) VerticalResolution
                   );

    for (indexmode = 0;
         indexmode < DEMO_SOURCE_POSITION_ENUM *
         DEMO_DESTINATION_POSITION_ENUM *
         DEMO_DELTA_ENUM *
         DEMO_WIDTH_HEIGHT_ENUM;
       indexmode++
        ) {
      //
      // Prepare test data
      //
      GetTestData (
        indexmode,
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
        Delta = Width * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
      }

      Status = GraphicsOutputClearScreen (
                GraphicsOutput,
                HorizontalResolution,
                VerticalResolution
                );
      if (EFI_ERROR (Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTestGenericFailureGuid,
                       L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer stress auto test - GraphicsOutputClearScreen",
                       L"%a:%d: Status = %r",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__,
                       (UINTN) Status
                       );
        return Status;
      }
      //
      // Prepare a bitmap(150*150) displaying
      //
      Status = LoadBmp (&BltBuffer3, &Wt, &Ht);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoTOBltBuffer auto test - LoadBmp failure",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }

      if (SourceX + Wt > HorizontalResolution) {
        continue;
      }

      if (SourceY + Ht > VerticalResolution) {
        continue;
      }
      //
      // display it to the video
      //
      Status = GraphicsOutput->Blt (
                                 GraphicsOutput,
                                 BltBuffer3,
                                 EfiBltBufferToVideo,
                                 0,
                                 0,
                                 SourceX,
                                 SourceY,
                                 Wt,
                                 Ht,
                                 Wt * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                 );

      if (EFI_ERROR (Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid001,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo - Blt/EfiBltBufferToVideo",
                     L"%a:%d: Status = %r,Mode index = %d,Source=(0 x 0), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d ",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status,
                     (UINTN) Index,
                     (UINTN) SourceX,
                     (UINTN) SourceY,
                     (UINTN) Wt,
                     (UINTN) Ht,
                     (UINTN) Wt * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                     );
      if (BltBuffer3 != NULL) {
        gtBS->FreePool (BltBuffer3);
      }
      //
      // Allocate Buffer for BltBuffer & BltBuffer2
      // BltBuffer should be large than (Width+DestinationX)*(Height+DestinationY)
      //
      BltBuffer   = NULL;
      BltBuffer2  = NULL;
      Size        = (Width + DestinationX) * (Height + DestinationY) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
      Status = gtBS->AllocatePool (
                       EfiBootServicesData,
                       Size,
                       (VOID **) &BltBuffer
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.AllocatePool - Allocate pool",
                       L"%a:%d:Status - %r",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__,
                       (UINTN) Status
                       );
        return Status;
      }

      SctZeroMem (BltBuffer, Size);

      Size = Width * Height * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
      Status = gtBS->AllocatePool (
                       EfiBootServicesData,
                       Size,
                       (VOID **) &BltBuffer2
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.AllocatePool - Allocate pool",
                       L"%a:%d:Status - %r",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__,
                       (UINTN) Status
                       );
        if (BltBuffer != NULL) {
          gtBS->FreePool (BltBuffer);
        }

        return Status;
      }

      SctZeroMem (BltBuffer2, Size);
      //
      // Delta should reflect the length of a row correctly
      //
      Delta = (Width + DestinationX) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);

      //
      // Call Blt() with BltOperation being EfiBltVideoToBltBuffer
      // Operation to be tested! (1)
      //
      Status = GraphicsOutput->Blt (
                                 GraphicsOutput,
                                 BltBuffer,
                                 EfiBltVideoToBltBuffer,
                                 SourceX,
                                 SourceY,
                                 DestinationX,
                                 DestinationY,
                                 Width,
                                 Height,
                                 Delta
                                 );

      if (EFI_ERROR (Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid002,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer",
                     L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status,
                     (UINTN) Index,
                     (UINTN) SourceX,
                     (UINTN) SourceY,
                     (UINTN) DestinationX,
                     (UINTN) DestinationY,
                     (UINTN) Width,
                     (UINTN) Height,
                     (UINTN) Delta
                     );
                     
      //
      // Clear screen
      //
      Status = GraphicsOutputClearScreen (
                GraphicsOutput,
                HorizontalResolution,
                VerticalResolution
                );
      if (EFI_ERROR (Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTestGenericFailureGuid,
                       L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - GraphicsOutputClearScreen",
                       L"%a:%d: Status = %r",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__,
                       (UINTN) Status
                       );
        if (BltBuffer != NULL) {
          Status    = gtBS->FreePool (BltBuffer);
          BltBuffer = NULL;
        }

        if (BltBuffer2 != NULL) {
          Status      = gtBS->FreePool (BltBuffer2);
          BltBuffer2  = NULL;
        }

        return Status;
      }
      //
      // Call Blt() with BltOperation being EfiBltBufferToVideo to
      // re-draw Buffer into display
      // Note: Source and Destination should reverse with that of BltVideoToBltBuffer operation
      //
      //
      // Operation to be tested! (2)
      //
      Status1 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer,
                                  EfiBltBufferToVideo,
                                  DestinationX,
                                  DestinationY,
                                  SourceX,
                                  SourceY,
                                  Width,
                                  Height,
                                  Delta
                                  );

      gtBS->Stall (50000);
      //
      // Call Blt() with BltOperatoin being EfiBltVideoToBltBuffer again
      // This time, use BltBuffer2 and save it
      //
      Status2 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer2,
                                  EfiBltVideoToBltBuffer,
                                  SourceX,
                                  SourceY,
                                  0,
                                  0,
                                  Width,
                                  Height,
                                  0
                                  );
      if (EFI_ERROR (Status2)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid003,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer",
                     L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d ",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status2,
                     (UINTN) Index,
                     (UINTN) SourceX,
                     (UINTN) SourceY,
                     (UINTN) 0,
                     (UINTN) 0,
                     (UINTN) Width,
                     (UINTN) Height,
                     (UINTN) 0
                     );

      if (EFI_ERROR (Status1)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid004,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo - Blt/EfiBltBufferToVideo",
                     L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d ",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status1,
                     (UINTN) Index,
                     (UINTN) DestinationX,
                     (UINTN) DestinationY,
                     (UINTN) SourceX,
                     (UINTN) SourceY,
                     (UINTN) Width,
                     (UINTN) Height,
                     (UINTN) Delta
                     );
      //
      // Compare BltBuffer with BltBuffer2 the two should be same
      // Operation to be tested! (3)
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      for (m = 0; m < Width * Height; m++) {
        IndexWidth  = m % Width;
        IndexHeight = m / Width + DestinationY;
        IndexPos    = IndexWidth + DestinationX + IndexHeight * (Delta / sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

        if (((*((UINT32 *) BltBuffer + IndexPos)) | 0xFF000000) != ((*((UINT32 *) BltBuffer2 + m)) | 0xFF000000)) {
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
                     gEfiGraphicsOutputBltVideoBltBufferStressAutoTestAssertionGuid005,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/(EfiBltVideoToBltBuffer,EfiBltBufferToVideo) - Blt/EfiBltVideoToBltBuffer,EfiBltBufferToVideo), Pixel verification",
                     L"%a:%d: Status = %r,Mode index = %d, Video Source=(%dx%d),Buffer Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status,
                     (UINTN) Index,
                     (UINTN) SourceX,
                     (UINTN) SourceY,
                     (UINTN) DestinationX,
                     (UINTN) DestinationY,
                     (UINTN) Width,
                     (UINTN) Height,
                     (UINTN) Delta
                     );

      //
      // Free Buffer for next test data
      //
      if (BltBuffer != NULL) {
        Status = gtBS->FreePool (BltBuffer);
      }

      if (BltBuffer2 != NULL) {
        Status = gtBS->FreePool (BltBuffer2);
      }
    }
  }
  //
  // restore the orignal Mode
  //
  Status = GraphicsOutput->SetMode (GraphicsOutput, CurrentMode);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test,restore the orignal Mode",
                 L"%a:%d: Mode index = %d,Status:%r, Expected:EFI_SUCCESS",
                 (UINTN) __FILE__,
                 (UINTN) (UINTN)__LINE__,
                 (UINTN) CurrentMode,
                 (UINTN) Status
                 );
                 
  return EFI_SUCCESS;

}

//
// TDS 4.3.3
//
EFI_STATUS
EFIAPI
BBTestEfiGraphicsOutputBltVideoToVideoStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoToVideo Extensive Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
{

  EFI_STATUS                          Status;
  EFI_STATUS                          Status1;
  EFI_STATUS                          Status2;

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_GRAPHICS_OUTPUT_PROTOCOL        *GraphicsOutput;

  UINT32                              Index;

  UINT32                              MaxMode;
  UINT32                              CurrentMode;

  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer2;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer3;

  UINTN                               SourceX;
  UINTN                               SourceY;
  UINTN                               DestinationX;
  UINTN                               DestinationY;
  UINTN                               Width;
  UINTN                               Wt;
  UINTN                               Height;
  UINTN                               Ht;
  UINTN                               Delta;
  UINTN                               Size;
  UINT32                              HorizontalResolution;
  UINT32                              VerticalResolution;
  UINTN                               m;
  UINTN                               indexmode;

  SourceX       = 0;
  SourceY       = 0;
  DestinationX  = 0;
  DestinationY  = 0;
  Delta         = 0;

  GraphicsOutput = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) ClientInterface;

  if ((Status = InitTestEnv (SupportHandle, &StandardLib, GraphicsOutput)) != EFI_SUCCESS) {
    return Status;

  }

  CurrentMode = GraphicsOutput->Mode->Mode;
  MaxMode     = GraphicsOutput->Mode->MaxMode;

  //
  //  Test Blt Operations in All mode support by Graphics Output Device
  //
  for (Index = 0; Index < MaxMode; Index++) {

    Status                = GraphicsOutput->SetMode (GraphicsOutput, Index);

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      return Status;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                   L"%a:%d: Mode index=%d,Status:%r, Expected:EFI_SUCCESS, Resolution=(%d * %d)",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Index,
                   (UINTN) Status,
                   (UINTN) HorizontalResolution,
                   (UINTN) VerticalResolution
                   );

    for (indexmode = 0;
         indexmode < DEMO_SOURCE_POSITION_ENUM *
         DEMO_DESTINATION_POSITION_ENUM *
         DEMO_DELTA_ENUM *
         DEMO_WIDTH_HEIGHT_ENUM;
       indexmode++
        ) {
      //
      // Prepare test data
      //
      GetTestData (
        indexmode,
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
        Delta = Width * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
      }
      //
      // Clear screen
      //
      Status = GraphicsOutputClearScreen (
                 GraphicsOutput,
                 HorizontalResolution,
                 VerticalResolution
                 );
      if (EFI_ERROR (Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gTestGenericFailureGuid,
                       L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToVideo stress auto test - GraphicsOutputClearScreen",
                       L"%a:%d: Status = %r",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__,
                       (UINTN) Status
                       );
        return Status;
      }
      //
      // Prepare a bitmap(150*150) for displaying
      //
      Status = LoadBmp (&BltBuffer3, &Wt, &Ht);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoTOBltBuffer auto test - LoadBmp failure",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      //
      // display the bitmap to the video
      //
      Status = GraphicsOutput->Blt (
                                 GraphicsOutput,
                                 BltBuffer3,
                                 EfiBltBufferToVideo,
                                 0,
                                 0,
                                 SourceX,
                                 SourceY,
                                 Wt,
                                 Ht,
                                 Wt * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                 );

      if (EFI_ERROR (Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid001,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo - Blt/EfiBltBufferToVideo",
                     L"%a:%d: Status = %r,Mode index = %d, Source=(0 x 0), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d ",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status,
                     (UINTN) Index,
                     (UINTN) SourceX,
                     (UINTN) SourceY,
                     (UINTN) Wt,
                     (UINTN) Ht,
                     (UINTN) Wt * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                     );
      if (BltBuffer3 != NULL) {
        gtBS->FreePool (BltBuffer3);
      }
      //
      // Allocate Buffer for BltBuffer & BltBuffer2
      //
      BltBuffer   = NULL;
      BltBuffer2  = NULL;
      Size        = Width * Height * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
      Status = gtBS->AllocatePool (
                       EfiBootServicesData,
                       Size,
                       (VOID **) &BltBuffer
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.AllocatePool - Allocate pool",
                       L"%a:%d:Status - %r",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__,
                       (UINTN) Status
                       );
        return Status;
      }

      SctZeroMem (BltBuffer, Size);

      Size = Width * Height * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
      Status = gtBS->AllocatePool (
                       EfiBootServicesData,
                       Size,
                       (VOID **) &BltBuffer2
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.AllocatePool - Allocate pool",
                       L"%a:%d:Status - %r",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__,
                       (UINTN) Status
                       );
        if (BltBuffer != NULL) {
          Status = gtBS->FreePool (BltBuffer);
        }

        return Status;
      }

      SctZeroMem (BltBuffer2, Size);

      //
      // Call Blt() with BltOperation being EfiBltVideoToBltBuffer
      // to save original screen
      //
      Status1 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer,
                                  EfiBltVideoToBltBuffer,
                                  SourceX,
                                  SourceY,
                                  0,
                                  0,
                                  Width,
                                  Height,
                                  0
                                  );

      //
      // Call Blt() with BltOperation being EfibltVideoToVideo to copy screen
      //
      Status2 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer2,
                                  EfiBltVideoToVideo,
                                  SourceX,
                                  SourceY,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  Delta
                                  );

      gtBS->Stall (5000);
      //
      // Call Blt() with BltOperatoin being EfiBltVideoToBltBuffer again
      // This time, use BltBuffer2, and the retrieved area should be destination rectangle
      //
      Status = GraphicsOutput->Blt (
                                 GraphicsOutput,
                                 BltBuffer2,
                                 EfiBltVideoToBltBuffer,
                                 DestinationX,
                                 DestinationY,
                                 0,
                                 0,
                                 Width,
                                 Height,
                                 0
                                 );

      if (EFI_ERROR (Status)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid004,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer",
                     L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status,
                     (UINTN) Index,
                     (UINTN) DestinationX,
                     (UINTN) DestinationY,
                     (UINTN) 0,
                     (UINTN) 0,
                     (UINTN) Width,
                     (UINTN) Height,
                     (UINTN) Delta
                     );

      if (EFI_ERROR (Status1)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid002,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer",
                     L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status1,
                     (UINTN) Index,
                     (UINTN) SourceX,
                     (UINTN) SourceY,
                     (UINTN) 0,
                     (UINTN) 0,
                     (UINTN) Width,
                     (UINTN) Height,
                     (UINTN) Delta
                     );

      if (EFI_ERROR (Status2)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid003,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToVideo - Blt/EfiBltVideoToVideo",
                     L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status2,
                     (UINTN) Index,
                     (UINTN) SourceX,
                     (UINTN) SourceY,
                     (UINTN) DestinationX,
                     (UINTN) DestinationY,
                     (UINTN) Width,
                     (UINTN) Height,
                     (UINTN) Delta
                     );

      //
      // Compare BltBuffer with BltBuffer2
      // the two should be same
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      for (m = 0; m < Width * Height; m++) {
        if ((0xFF000000 | (*((UINT32 *) BltBuffer + m))) != (0xFF000000 | (*((UINT32 *) BltBuffer2 + m)))) {
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
                     gEfiGraphicsOutputBltVideoToVideoStressAutoTestAssertionGuid005,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToVideo - Blt/EfiBltVideoToVideo, Pixel verification",
                     L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status,
                     (UINTN) Index,
                     (UINTN) SourceX,
                     (UINTN) SourceY,
                     (UINTN) DestinationX,
                     (UINTN) DestinationY,
                     (UINTN) Width,
                     (UINTN) Height,
                     (UINTN) Delta
                     );

      //
      // Free Buffer for next test data
      //
      if (BltBuffer != NULL) {
        Status = gtBS->FreePool (BltBuffer);
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"BS.FreePool - Free pool",
                         L"%a:%d: Status - %r",
                         (UINTN) __FILE__,
                         (UINTN) (UINTN)__LINE__,
                         (UINTN) Status
                         );
        }
      }

      if (BltBuffer2 != NULL) {
        Status = gtBS->FreePool (BltBuffer2);
        if (EFI_ERROR (Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"BS.FreePool - Free pool",
                         L"%a:%d: Status - %r",
                         (UINTN) __FILE__,
                         (UINTN) (UINTN)__LINE__,
                         (UINTN) Status
                          );
        }               
      }                 
    }                   
  }                     
  //                    
  // restore the orignal Mode
  //                    
  Status = GraphicsOutput->SetMode (GraphicsOutput, CurrentMode);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test,restore the orignal Mode",
                 L"%a:%d:Status:%r,  Mode index = %d, Expected:EFI_SUCCESS",
                 (UINTN) __FILE__,
                 (UINTN) (UINTN)__LINE__,
                 (UINTN) Status,
                 (UINTN) CurrentMode
                 );

  return EFI_SUCCESS;

}

//
// TDS 4.3.4
//
EFI_STATUS
EFIAPI
BBTestVideoFillBufferToVideoManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoFill& BltBufferToVideo Manual Stress Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
{
  EFI_STATUS                          Status;
  EFI_STATUS                          Status1;
  EFI_STATUS                          Status2;

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_TEST_ASSERTION                  FillAssertion;
  EFI_TEST_ASSERTION                  BufferToVideoAssertion;
  EFI_GRAPHICS_OUTPUT_PROTOCOL        *GraphicsOutput;

  UINT32                              Index;

  UINT32                              MaxMode;
  UINT32                              CurrentMode;

  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       Blt;

  UINTN                               HorizontalResolution;
  UINTN                               VerticalResolution;
  UINTN                               SourceX;
  UINTN                               SourceY;
  UINTN                               DestinationX;
  UINTN                               DestinationY;
  UINTN                               Width;
  UINTN                               Height;
  UINTN                               Delta;

  SourceX                     = 0;
  SourceY                     = 0;
  DestinationX                = 0;
  DestinationY                = 0;
  Delta                       = 0;

  Status                      = Status2 = Status1 = EFI_SUCCESS;

  GraphicsOutput = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) ClientInterface;

  if ((Status = InitTestEnv (SupportHandle, &StandardLib, GraphicsOutput)) != EFI_SUCCESS) {
    return Status;

  }

  CurrentMode = GraphicsOutput->Mode->Mode;
  MaxMode     = GraphicsOutput->Mode->MaxMode;

  //
  // Prepare a bitmap(150*150) for displaying, then Width=150, Height=150
  //
  Status = LoadBmp (&BltBuffer, &Width, &Height);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFillBufferToVideo manual test - LoadBmp failure",
                   L"%a:%d:Status - %r",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status
                   );
    return Status;
  }
  //
  //  Test Blt Operations in All mode support by Graphics Output Device
  //
  for (Index = 0; Index < MaxMode; Index++) {
    Status                = GraphicsOutput->SetMode (GraphicsOutput, Index);

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      return Status;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                   L"%a:%d: Mode index=%d,Status:%r, Expected:EFI_SUCCESS, Resolution=(%d * %d)",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Index,
                   (UINTN) Status,
                   (UINTN) HorizontalResolution,
                   (UINTN) VerticalResolution
                   );
    //
    // Clear screen
    //
    Status = GraphicsOutputClearScreen (
              GraphicsOutput,
              HorizontalResolution,
              VerticalResolution
              );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFillBufferToVideo manual test - GraphicsOutputClearScreen",
                     L"%a:%d: Status = %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      return Status;
    }

    Delta         = Width * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    SourceX       = 0;
    SourceY       = 0;
    DestinationX  = 0;
    DestinationY  = 0;
    Width -= SourceX;
    Height -= SourceY;
    //
    // Move DestinationXY from upper left-hand corner to upper right-hand corner
    //
    FillAssertion           = EFI_TEST_ASSERTION_PASSED;
    BufferToVideoAssertion  = EFI_TEST_ASSERTION_PASSED;

    for (; DestinationX + Width + STEP_WIDTH < HorizontalResolution; DestinationX += STEP_WIDTH) {
      //
      // Use BltBufferToVideo to display .bmp file
      // DestinationXY is the upper left of Video frame in this case
      //
      Status1 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer,
                                  EfiBltBufferToVideo,
                                  SourceX,
                                  SourceY,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  Delta
                                  );
      if (EFI_ERROR (Status1)) {
        BufferToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
      }

      gtBS->Stall (100000);
      //
      // Call Blt() with BltOperation being EfiBltVideoFill
      // to clear the rectangle in the last call of EfiBltBufferToVideo
      //
      Blt.Blue  = 0;
      Blt.Red   = 0;
      Blt.Green = 0;
      Status2 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  &Blt,
                                  EfiBltVideoFill,
                                  0,
                                  0,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  0
                                  );

      if (EFI_ERROR (Status2)) {
        FillAssertion = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // wait some time
      //
      gtBS->Stall (5000);
    }
    //
    // Rotate from upper left to right
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   BufferToVideoAssertion,
                   gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid001,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo - Blt/EfiBltBufferToVideo",
                   L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status1,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   FillAssertion,
                   gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid002,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiBltVideoFill",
                   L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d),Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status2,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );
    //
    // Move DestinationXY from upper right-hand corner to lower right-hand corner
    //
    FillAssertion           = EFI_TEST_ASSERTION_PASSED;
    BufferToVideoAssertion  = EFI_TEST_ASSERTION_PASSED;
    //
    //   DestinationX-=STEP_WIDTH;
    //
    for (DestinationY = 0; DestinationY + Height + STEP_WIDTH < VerticalResolution; DestinationY += STEP_WIDTH) {
      //
      // Use BltBufferToVideo to display .bmp file
      // DestinationXY is the upper left of Video frame in this case
      //
      Status1 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer,
                                  EfiBltBufferToVideo,
                                  SourceX,
                                  SourceY,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  Delta
                                  );
      if (EFI_ERROR (Status1)) {
        BufferToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
      }

      gtBS->Stall (100000);
      //
      // Call Blt() with BltOperation being EfiBltVideoFill
      // to clear the rectangle in the last call of EfiBltBufferToVideo
      //
      Blt.Blue  = 0;
      Blt.Red   = 0;
      Blt.Green = 0;
      Status2 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  &Blt,
                                  EfiBltVideoFill,
                                  0,
                                  0,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  0
                                  );

      if (EFI_ERROR (Status2)) {
        FillAssertion = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // wait some time
      //
      gtBS->Stall (5000);
    }
    //
    // Rotate from upper right to lower right
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   BufferToVideoAssertion,
                   gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid003,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo - Blt/EfiBltBufferToVideo",
                   L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d),Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status1,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   FillAssertion,
                   gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid004,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo - Blt/EfiBltBufferToVideo",
                   L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d),Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status2,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );
    //
    // Move DestinationXY from lower right-hand corner to lower left-hand corner
    //
    FillAssertion           = EFI_TEST_ASSERTION_PASSED;
    BufferToVideoAssertion  = EFI_TEST_ASSERTION_PASSED;
    //
    //      DestinationY-=STEP_WIDTH;
    //
    for (; DestinationX > STEP_WIDTH; DestinationX -= STEP_WIDTH) {
      //
      // Use BltBufferToVideo to display .bmp file
      // DestinationXY is the upper left of Video frame in this case
      //
      Status1 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer,
                                  EfiBltBufferToVideo,
                                  SourceX,
                                  SourceY,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  Delta
                                  );
      if (EFI_ERROR (Status1)) {
        BufferToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
      }

      gtBS->Stall (100000);
      //
      // Call Blt() with BltOperation being EfiBltVideoFill
      // to clear the rectangle in the last call of EfiBltBufferToVideo
      //
      Blt.Blue  = 0;
      Blt.Red   = 0;
      Blt.Green = 0;
      Status2 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  &Blt,
                                  EfiBltVideoFill,
                                  0,
                                  0,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  0
                                  );

      if (EFI_ERROR (Status2)) {
        FillAssertion = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // wait some time
      //
      gtBS->Stall (5000);
    }
    //
    // Rotate from lower right to left
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   BufferToVideoAssertion,
                   gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid005,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo - Blt/EfiBltBufferToVideo",
                   L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d),Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status1,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   FillAssertion,
                   gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid006,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFill - Blt/EfiBltVideoFill",
                   L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d),Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status2,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );
    //
    // Move DestinationXY from lower left-hand corner to upper left-hand corner
    //
    FillAssertion           = EFI_TEST_ASSERTION_PASSED;
    BufferToVideoAssertion  = EFI_TEST_ASSERTION_PASSED;

    for (; DestinationY > STEP_WIDTH; DestinationY -= STEP_WIDTH) {
      //
      // Use BltBufferToVideo to display .bmp file
      // DestinationXY is the upper left of Video frame in this case
      //
      Status1 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer,
                                  EfiBltBufferToVideo,
                                  SourceX,
                                  SourceY,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  Delta
                                  );
      if (EFI_ERROR (Status1)) {
        BufferToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
      }

      gtBS->Stall (100000);
      //
      // Call Blt() with BltOperation being EfiBltVideoFill
      // to clear the rectangle in the last call of EfiBltBufferToVideo
      //
      Blt.Blue  = 0;
      Blt.Red   = 0;
      Blt.Green = 0;
      Status2 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  &Blt,
                                  EfiBltVideoFill,
                                  0,
                                  0,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  0
                                  );

      if (EFI_ERROR (Status2)) {
        FillAssertion = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // wait some time
      //
      gtBS->Stall (5000);
    }
    //
    // Rotate from lower right to left
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   BufferToVideoAssertion,
                   gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid007,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo - Blt/EfiBltBufferToVideo",
                   L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d),Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status1,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );
                   
    StandardLib->RecordAssertion (
                   StandardLib,
                   FillAssertion,
                   gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid008,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo - Blt/EfiBltVideoFill",
                   L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d),Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status2,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );
    //
    // Ask for user's to judge whether the rotation of the BMP file correctly
    //
    //
    // Clear screen
    //
    Status = GraphicsOutputClearScreen (
               GraphicsOutput,
               HorizontalResolution,
               VerticalResolution
               );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFillBufferToVideo manual test - GraphicsOutputClearScreen",
                     L"%a:%d: Status = %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      return Status;
    }

    if (AutoJudgeGop (100, 120, 60, TRUE, L"Logo rotates correctly?") != TRUE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiGraphicsOutputBltVideoFillBufferToVideoStressManualTestAssertionGuid009,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()/VideoFill&BltBufferToVideo - Blt()/VideoFill&BltBufferToVideo - user's view",
                   L"%a:%d: Status = %r, Resolution=(%dx%d)",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status,
                   HorizontalResolution,
                   VerticalResolution
                   );

  }
  //
  // end for all modes
  //
  // Free Buffer for next test data
  //
  if (BltBuffer != NULL) {
    Status = gtBS->FreePool (BltBuffer);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.FreePool - Free pool",
                     L"%a:%d: Status - %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
    }
  }
  //
  // restore the orignal Mode
  //
  Status = GraphicsOutput->SetMode (GraphicsOutput, CurrentMode);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test,restore the orignal Mode",
                 L"%a:%d:Mode index=%d,Status:%r,  Expected:EFI_SUCCESS",
                 (UINTN) __FILE__,
                 (UINTN) (UINTN)__LINE__,
                 (UINTN) CurrentMode,
                 (UINTN) Status
                 );

  return EFI_SUCCESS;
}

//
// TDS 4.3.5
//
EFI_STATUS
EFIAPI
BBTestVideoFillVideoToVideoManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoToVideo Manual Stress Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
{
  EFI_STATUS                          Status;
  EFI_STATUS                          Status1;
  EFI_STATUS                          Status2;

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_TEST_ASSERTION                  FillAssertion;
  EFI_TEST_ASSERTION                  VideoToVideoAssertion;
  EFI_GRAPHICS_OUTPUT_PROTOCOL        *GraphicsOutput;

  UINT32                              Index;

  UINT32                              MaxMode;
  UINT32                              CurrentMode;

  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       Blt;

  UINTN                               HorizontalResolution;
  UINTN                               VerticalResolution;
  UINTN                               SourceX;
  UINTN                               SourceY;
  UINTN                               DestinationX;
  UINTN                               DestinationY;
  UINTN                               Width;
  UINTN                               Height;
  UINTN                               Delta;

  SourceX                     = 0;
  SourceY                     = 0;
  DestinationX                = 0;
  DestinationY                = 0;
  Delta                       = 0;

  Status                      = Status2 = Status1 = EFI_SUCCESS;

  GraphicsOutput = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) ClientInterface;

  if ((Status = InitTestEnv (SupportHandle, &StandardLib, GraphicsOutput)) != EFI_SUCCESS) {
    return Status;

  }

  CurrentMode = GraphicsOutput->Mode->Mode;
  MaxMode     = GraphicsOutput->Mode->MaxMode;

  //
  // Prepare a bitmap(150*150) for displaying, then Width=150, Height=150
  //
  Status = LoadBmp (&BltBuffer, &Width, &Height);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFillBufferToVideo manual test - LoadBmp failure",
                   L"%a:%d:Status - %r",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status
                   );
    return Status;
  }

  Delta         = Width * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
  SourceX       = 0;
  SourceY       = 0;
  DestinationX  = 0;
  DestinationY  = 0;
  Width -= SourceX;
  Height -= SourceY;

  Blt.Blue  = 0;
  Blt.Red   = 0;
  Blt.Green = 0;
  //
  //  Test Blt Operations in All mode support by Graphics Output Device
  //
  for (Index = 0; Index < MaxMode; Index++) {
    Status                = GraphicsOutput->SetMode (GraphicsOutput, Index);

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      return Status;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                   L"%a:%d: Mode index=%d,Status:%r, Expected:EFI_SUCCESS, Resolution=(%d * %d)",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Index,
                   (UINTN) Status,
                   (UINTN) HorizontalResolution,
                   (UINTN) VerticalResolution
                   );
    //
    // Clear screen
    //
    Status = GraphicsOutputClearScreen (
              GraphicsOutput,
              HorizontalResolution,
              VerticalResolution
              );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFillBufferToVideo manual test - GraphicsOutputClearScreen",
                     L"%a:%d: Status = %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      return Status;
    }
    //
    // Use BltBufferToVideo to display .bmp file
    // DestinationXY is the upper left of Video frame in this case
    //
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               BltBuffer,
                               EfiBltBufferToVideo,
                               0,
                               0,
                               0,
                               0,
                               Width,
                               Height,
                               Delta
                               );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid001,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo",
                   L"%a:%d: Status = %r,Mode index = %d, Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status,
                   (UINTN) Index,
                   (UINTN) 0,
                   (UINTN) 0,
                   (UINTN) 0,
                   (UINTN) 0,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );
    gtBS->Stall (50000);

    SourceX       = 0;
    SourceY       = 0;
    DestinationX  = 0;
    DestinationY  = 0;

    //
    // Move DestinationXY from upper left-hand corner to upper right-hand corner
    //
    FillAssertion         = EFI_TEST_ASSERTION_PASSED;
    VideoToVideoAssertion = EFI_TEST_ASSERTION_PASSED;

    for (DestinationX = DestinationX + STEP_WIDTH;
         DestinationX + Width + STEP_WIDTH < HorizontalResolution;
         DestinationX += STEP_WIDTH
        ) {
      //
      // Call Blt() with BltOperation being EfiBltVideoFill
      // to clear the rectangle in the last call of EfiBltBufferToVideo
      //
      SourceX = DestinationX - STEP_WIDTH;
      SourceY = DestinationY;

      Status1 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer,
                                  EfiBltVideoToVideo,
                                  SourceX,
                                  SourceY,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  0
                                  );

      Status2 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  &Blt,
                                  EfiBltVideoFill,
                                  0,
                                  0,
                                  SourceX,
                                  SourceY,
                                  STEP_WIDTH < Width ? STEP_WIDTH : Width,
                                  Height,
                                  0
                                  );

      if (EFI_ERROR (Status1)) {
        VideoToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
      }

      if (EFI_ERROR (Status2)) {
        FillAssertion = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // wait some time
      //
      gtBS->Stall (5000);
    }
    //
    // Rotate from upper left to right
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   VideoToVideoAssertion,
                   gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid002,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToVideo",
                   L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status1,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   FillAssertion,
                   gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid003,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFill",
                   L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d),Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status2,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );
    //
    // Move DestinationXY from upper right-hand corner to lower right-hand corner
    //
    FillAssertion         = EFI_TEST_ASSERTION_PASSED;
    VideoToVideoAssertion = EFI_TEST_ASSERTION_PASSED;

    SourceX               = DestinationX - STEP_WIDTH;
    DestinationX          = SourceX;

    for (DestinationY += STEP_WIDTH;
         DestinationY + Height + STEP_WIDTH < VerticalResolution;
         DestinationY += STEP_WIDTH
        ) {
      //
      // Use BltBufferToVideo to display .bmp file
      // DestinationXY is the upper left of Video frame in this case
      //
      SourceY = DestinationY - STEP_WIDTH;

      Status1 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer,
                                  EfiBltVideoToVideo,
                                  SourceX,
                                  SourceY,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  0
                                  );

      Status2 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  &Blt,
                                  EfiBltVideoFill,
                                  0,
                                  0,
                                  SourceX,
                                  SourceY,
                                  Width,
                                  STEP_WIDTH < Height ? STEP_WIDTH : Height,
                                  0
                                  );

      if (EFI_ERROR (Status1)) {
        VideoToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
      }

      if (EFI_ERROR (Status2)) {
        FillAssertion = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // wait some time
      //
      gtBS->Stall (5000);
    }
    //
    // Rotate from upper right to lower right
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   VideoToVideoAssertion,
                   gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid004,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToVideo",
                   L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status1,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   FillAssertion,
                   gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid005,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFill",
                   L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d),Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status2,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );
    //
    // Move DestinationXY from lower right-hand corner to lower left-hand corner
    //
    FillAssertion         = EFI_TEST_ASSERTION_PASSED;
    VideoToVideoAssertion = EFI_TEST_ASSERTION_PASSED;

    SourceY               = DestinationY - STEP_WIDTH;
    DestinationY -= STEP_WIDTH;
    for (DestinationX = DestinationX - STEP_WIDTH; DestinationX > STEP_WIDTH; DestinationX -= STEP_WIDTH) {
      //
      // Use BltBufferToVideo to display .bmp file
      // DestinationXY is the upper left of Video frame in this case
      //
      SourceX = DestinationX + STEP_WIDTH;

      Status1 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer,
                                  EfiBltVideoToVideo,
                                  SourceX,
                                  SourceY,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  0
                                  );

      Status2 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  &Blt,
                                  EfiBltVideoFill,
                                  0,
                                  0,
                                  STEP_WIDTH < Width ? (DestinationX + Width) : SourceX,
                                  SourceY,
                                  STEP_WIDTH < Width ? STEP_WIDTH : Width,
                                  Height,
                                  0
                                  );

      if (EFI_ERROR (Status1)) {
        VideoToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
      }

      if (EFI_ERROR (Status2)) {
        FillAssertion = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // wait some time
      //
      gtBS->Stall (5000);

    }
    //
    // Rotate from lower right to left
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   VideoToVideoAssertion,
                   gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid006,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToVideo",
                   L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status1,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   FillAssertion,
                   gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid007,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFill",
                   L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d),Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status2,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );
    //
    // Move DestinationXY from lower left-hand corner to upper left-hand corner
    //
    FillAssertion         = EFI_TEST_ASSERTION_PASSED;
    VideoToVideoAssertion = EFI_TEST_ASSERTION_PASSED;

    DestinationX          = SourceX - STEP_WIDTH;
    SourceX               = DestinationX;

    for (DestinationY -= STEP_WIDTH; DestinationY > STEP_WIDTH; DestinationY -= STEP_WIDTH) {
      //
      // Use BltVideoToVideo to copy .bmp file
      // DestinationXY is the upper left of Video frame in this case
      //
      SourceY = DestinationY + STEP_WIDTH;

      Status1 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  BltBuffer,
                                  EfiBltVideoToVideo,
                                  SourceX,
                                  SourceY,
                                  DestinationX,
                                  DestinationY,
                                  Width,
                                  Height,
                                  0
                                  );

      Status2 = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  &Blt,
                                  EfiBltVideoFill,
                                  0,
                                  0,
                                  SourceX,
                                  STEP_WIDTH < Height ? (DestinationY + Height) : SourceY,
                                  Width,
                                  STEP_WIDTH < Height ? STEP_WIDTH : Height,
                                  0
                                  );

      if (EFI_ERROR (Status1)) {
        VideoToVideoAssertion = EFI_TEST_ASSERTION_FAILED;
      }

      if (EFI_ERROR (Status2)) {
        FillAssertion = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // wait some time
      //
      gtBS->Stall (5000);
    }
    //
    // Rotate from lower right to left
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   VideoToVideoAssertion,
                   gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid008,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToVideo",
                   L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status1,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   FillAssertion,
                   gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid009,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFill",
                   L"%a:%d: Status = %r,Mode index = %d,Source=(%dx%d), Destination=(%dx%d),Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status2,
                   (UINTN) Index,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );

    //
    // Ask for user's to judge whether the rotation of the BMP file correctly
    //
    //
    // Clear screen
    //
    Status = GraphicsOutputClearScreen (
               GraphicsOutput,
               HorizontalResolution,
               VerticalResolution
               );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFillVideoToVideo manual test - GraphicsOutputClearScreen",
                     L"%a:%d: Status = %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      return Status;
    }

    if (AutoJudgeGop (100, 120, 60, TRUE, L"Logo rotates correctly?") != TRUE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiGraphicsOutputBltVideoFillVideoToVideoStressManualTestAssertionGuid010,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()/VideoFill&BltVideoToVideo - Blt()/VideoFill&BltVideoToVideo - user's view",
                   L"%a:%d: Status = %r, Mode index = %d,Resolution=(%dx%d)",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status,
                   (UINTN) Index,
                   HorizontalResolution,
                   VerticalResolution
                   );
                   
  }
  //
  // end for all modes
  //
  // Free Buffer for next test data
  //
  if (BltBuffer != NULL) {
    Status = gtBS->FreePool (BltBuffer);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.FreePool - Free pool",
                     L"%a:%d: Status - %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
    }
  }
  //
  // restore the orignal Mode
  //
  Status = GraphicsOutput->SetMode (GraphicsOutput, CurrentMode);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test,restore the orignal Mode",
                 L"%a:%d:Status:%r,Mode index = %d, Expected:EFI_SUCCESS",
                 (UINTN) __FILE__,
                 (UINTN) (UINTN)__LINE__,
                 (UINTN) CurrentMode,
                 (UINTN) Status
                 );

  return EFI_SUCCESS;
}

//
// TDS 4.3.6
//
EFI_STATUS
EFIAPI
BBTestVideoToBltBufferExtensiveAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()-EfiBltVideoToBltBuffer Extensive Auto Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
{
  EFI_STATUS                          Status;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_TEST_ASSERTION                  VideoToBufferAssertion;
  EFI_GRAPHICS_OUTPUT_PROTOCOL        *GraphicsOutput;

  UINTN                               Size;
  UINT32                              Index;

  UINT32                              MaxMode;
  UINT32                              CurrentMode;

  UINTN                               HorizontalResolution;
  UINTN                               VerticalResolution;

  UINTN                               SourceX;
  UINTN                               BmpSourceX;
  UINTN                               SourceY;
  UINTN                               BmpSourceY;
  UINTN                               DestinationX;
  UINTN                               DestinationY;
  UINTN                               Width;
  UINTN                               BmpWidth;
  UINTN                               Height;
  UINTN                               BmpHeight;
  UINTN                               Delta;
  UINTN                               BmpDelta;

  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBuffer;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBufferWhole;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       *BltBufferWhole2;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       Blt;

  UINTN                               m;
  UINTN                               IndexPos;

  GraphicsOutput = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) ClientInterface;

  if ((Status = InitTestEnv (SupportHandle, &StandardLib, GraphicsOutput)) != EFI_SUCCESS) {
    return Status;

  }

  BltBuffer       = NULL;
  BltBufferWhole  = NULL;
  BltBufferWhole2 = NULL;

  CurrentMode     = GraphicsOutput->Mode->Mode;
  MaxMode         = GraphicsOutput->Mode->MaxMode;

  //
  // Prepare a bitmap(150*150) for displaying, then Width=150, Height=150
  //
  Status = LoadBmp (&BltBuffer, &Width, &Height);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFillBufferToVideo manual test - LoadBmp failure",
                   L"%a:%d:Status - %r",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status
                   );
    return Status;
  }

  Blt.Blue      = 0;
  Blt.Red       = 0;
  Blt.Green     = 0;

  Delta         = Width * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
  SourceX       = 100;
  SourceY       = 100;
  DestinationX  = 0;
  DestinationY  = 0;
  Width -= SourceX;
  Height -= SourceY;

  BmpSourceX  = SourceX;
  BmpSourceY  = SourceY;
  BmpDelta    = Delta;
  BmpWidth    = Width;
  BmpHeight   = Height;

  //
  // for all mode, try it..
  //
  for (Index = 0; Index < MaxMode; Index++) {
    //
    // switch screen into specified mode
    //
    Status = GraphicsOutput->SetMode (
                              GraphicsOutput,
                              Index
                              );

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      return Status;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                   L"%a:%d: Mode index=%d,Status:%r, Expected:EFI_SUCCESS, Resolution=(%d * %d)",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Index,
                   (UINTN) Status,
                   (UINTN) HorizontalResolution,
                   (UINTN) VerticalResolution
                   );

    //
    // ClearScreen
    //
    Status = GraphicsOutputClearScreen (
              GraphicsOutput,
              HorizontalResolution,
              VerticalResolution
              );
    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoFillVideoToVideo manual test - GraphicsOutputClearScreen",
                     L"%a:%d: Status = %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
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
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               BltBuffer,
                               EfiBltBufferToVideo,
                               BmpSourceX,
                               BmpSourceY,
                               0,
                               0,
                               BmpWidth,
                               BmpHeight,
                               BmpDelta
                               );

    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               BltBuffer,
                               EfiBltBufferToVideo,
                               BmpSourceX,
                               BmpSourceY,
                               HorizontalResolution / 2,
                               VerticalResolution / 2,
                               BmpWidth,
                               BmpHeight,
                               BmpDelta
                               );

    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               BltBuffer,
                               EfiBltBufferToVideo,
                               BmpSourceX,
                               BmpSourceY,
                               HorizontalResolution / 2,
                               0,
                               BmpWidth,
                               BmpHeight,
                               BmpDelta
                               );

    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               BltBuffer,
                               EfiBltBufferToVideo,
                               BmpSourceX,
                               BmpSourceY,
                               0,
                               VerticalResolution / 2,
                               BmpWidth,
                               BmpHeight,
                               BmpDelta
                               );

    if (EFI_ERROR (Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiGraphicsOutputBltVideoToBufferBBTestExtensiveAssertionGuid001,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo - Blt/EfiBltBufferToVideo",
                   L"%a:%d: Status = %r, Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d)",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta,
                   (UINTN) HorizontalResolution,
                   (UINTN) VerticalResolution
                   );

    //
    // Call Blt() with BltOperation being EfiBltVideoToBltBuffer
    // to retrieve whole screen to a large BltBuffer
    //
    BltBufferWhole  = NULL;
    BltBufferWhole2 = NULL;
    Size            = HorizontalResolution * VerticalResolution * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     Size,
                     (VOID **) &BltBufferWhole
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
                     (VOID **) &BltBufferWhole2
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

    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               BltBufferWhole,
                               EfiBltVideoToBltBuffer,
                               0,
                               0,
                               0,
                               0,
                               HorizontalResolution,
                               VerticalResolution,
                               0
                               );
    DestinationX  = 0;
    DestinationY  = 0;
    Delta         = 0;
    //
    // Change SourceX from 0 to HorizontalResolution by steps
    // Change SourceY from 0 to VerticalResolution by steps
    //
    VideoToBufferAssertion  = EFI_TEST_ASSERTION_PASSED;
    AssertionType           = EFI_TEST_ASSERTION_PASSED;

    for (SourceX = 0; SourceX + Width < HorizontalResolution; SourceX += STEP_WIDTH_BUFFER) {
      for (SourceY = 0; SourceY + Height < VerticalResolution; SourceY += STEP_WIDTH_BUFFER) {

        Status = GraphicsOutput->Blt (
                                   GraphicsOutput,
                                   BltBuffer,
                                   EfiBltVideoToBltBuffer,
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
        if (EFI_ERROR (Status)) {
          VideoToBufferAssertion = EFI_TEST_ASSERTION_FAILED;
          break;
        }

        Status = GraphicsOutput->Blt (
                                   GraphicsOutput,
                                   BltBufferWhole2,
                                   EfiBltVideoToBltBuffer,
                                   SourceX,
                                   SourceY,
                                   SourceX,
                                   SourceY,
                                   Width,
                                   Height,
                                   HorizontalResolution * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                   );

        //
        // Status Check
        //
        if (EFI_ERROR (Status)) {
          VideoToBufferAssertion = EFI_TEST_ASSERTION_FAILED;
          break;
        }
        //
        // Verify BltBuffer with portion in BltBufferWhole
        //
        for (m = 0; m < Width * Height; m++) {
          IndexPos = SourceX + m % Width + (m / Width + SourceY) * HorizontalResolution;

          if (((*((UINT32 *) BltBuffer + m)) | 0xFF000000) != ((*((UINT32 *) BltBufferWhole + IndexPos)) | 0xFF000000)) {
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

          if (((*((UINT32 *) BltBufferWhole2 + IndexPos)) | 0xFF000000) !=
                ((*((UINT32 *) BltBufferWhole + IndexPos)) | 0xFF000000)
                ) {
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
    // record assertion.
    //
    StandardLib->RecordAssertion (
                   StandardLib,
                   VideoToBufferAssertion,
                   gEfiGraphicsOutputBltVideoToBufferBBTestExtensiveAssertionGuid002,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer",
                   L"%a:%d: Status = %r, Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d)",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta,
                   (UINTN) HorizontalResolution,
                   (UINTN) VerticalResolution
                   );

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiGraphicsOutputBltVideoToBufferBBTestExtensiveAssertionGuid003,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer, Pixel verification",
                   L"%a:%d: Status = %r, Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d)",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta,
                   (UINTN) HorizontalResolution,
                   (UINTN) VerticalResolution
                   );

    //
    // Free Buffer for next test data
    //
    if (BltBufferWhole != NULL) {
      Status = gtBS->FreePool (BltBufferWhole);
      if (EFI_ERROR (Status)) {
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
      if (EFI_ERROR (Status)) {
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

  if (BltBuffer != NULL) {
    Status = gtBS->FreePool (BltBuffer);
    if (EFI_ERROR (Status)) {
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
  // restore the orignal Mode
  //
  Status = GraphicsOutput->SetMode (GraphicsOutput, CurrentMode);

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test,restore the orignal Mode",
                 L"%a:%d:Status:%r,Mode index = %d, Expected:EFI_SUCCESS",
                 (UINTN) __FILE__,
                 (UINTN) (UINTN)__LINE__,
                 (UINTN) CurrentMode,
                 (UINTN) Status
                 );

  return EFI_SUCCESS;
}
