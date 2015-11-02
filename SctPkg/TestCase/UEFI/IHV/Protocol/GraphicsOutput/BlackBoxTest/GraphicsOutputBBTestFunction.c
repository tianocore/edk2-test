/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  GraphicsOutputBBTestFunction.c

Abstract:

  Function Test Cases of Graphics Output Protocol
  
References:

  UEFI 2.0 Specification
  Graphics Output Protocol Test Design Specification
  UEFI/Tiano DXE Test Case Writer's Guide

--*/
#include "SctLib.h"
#include "GraphicsOutputBBTest.h"

//
// TDS 4.1.1
//
EFI_STATUS
BBTestEfiGraphicsOutputQueryModeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode() function Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
{
  EFI_STATUS                            Status;

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  *Info;
  UINTN                                 SizeofInfo;
  UINT32                                Index;
  UINT32                                CurrentMode;
  UINT32                                MaxMode;
  UINT32                                PixelElementSize;

  GraphicsOutput = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) ClientInterface;

  if ((Status = InitTestEnv (SupportHandle, &StandardLib, GraphicsOutput)) != EFI_SUCCESS) {
    return Status;
  }

  CurrentMode = GraphicsOutput->Mode->Mode;
  MaxMode     = GraphicsOutput->Mode->MaxMode;

  //
  //  Assertion Point
  //  QueryMode Should get the current Mode and return EFI_SUCCESS
  //
  SizeofInfo = 0;
  for (Index = 0; Index < MaxMode; Index++) {

    Status = GraphicsOutput->SetMode (
                               GraphicsOutput,
                               Index
                               );

    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() with valid mode",
                     L"%a:%d: mode:%d,Status = %r,Expected = EFI_SUCCESS ",
                     __FILE__,
                     (UINTN)__LINE__,
                     Index,
                     Status
                     );
      continue;
    }
    //
    // Check the content of info
    //
    SizeofInfo = 0;
    Info       = NULL;
    Status = GraphicsOutput->QueryMode (
                               GraphicsOutput,
                               Index,
                               &SizeofInfo,
                               &Info
                               );
    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (Info != NULL) {
        if (SctCompareMem ((VOID *) Info,
            (void *) GraphicsOutput->Mode->Info,
            sizeof (EFI_GRAPHICS_OUTPUT_MODE_INFORMATION)
            ) != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
    }

    if (Info != NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputQueryModeBBTestFunctionAssertionGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode - SetMode() then QueryMode(), compare Info structure",
                     L"%a:%d: dump of query result:ver:%d, hRes:%d, VRes:%d, PixelFmt:%d, RMsk:%x,GMsk:%x,BMsk:%x,ReserveMask:%x,PixelPerScanline:%d\n dump of GOP->Info:ver:%d, hRes:%d, VRes:%d, PixelFmt:%d, RMsk:%x,GMsk:%x,BMsk:%x,ReserveMask:%x,PixelPerScanline:%d",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Info->Version,
                     (UINTN) Info->HorizontalResolution,
                     (UINTN) Info->VerticalResolution,
                     (UINTN) Info->PixelFormat,
                     (UINTN) Info->PixelInformation.RedMask,
                     (UINTN) Info->PixelInformation.GreenMask,
                     (UINTN) Info->PixelInformation.BlueMask,
                     (UINTN) Info->PixelInformation.ReservedMask,
                     (UINTN) Info->PixelsPerScanLine,
                     (UINTN) GraphicsOutput->Mode->Info->Version,
                     (UINTN) GraphicsOutput->Mode->Info->HorizontalResolution,
                     (UINTN) GraphicsOutput->Mode->Info->VerticalResolution,
                     (UINTN) GraphicsOutput->Mode->Info->PixelFormat,
                     (UINTN) GraphicsOutput->Mode->Info->PixelInformation.RedMask,
                     (UINTN) GraphicsOutput->Mode->Info->PixelInformation.GreenMask,
                     (UINTN) GraphicsOutput->Mode->Info->PixelInformation.BlueMask,
                     (UINTN) GraphicsOutput->Mode->Info->PixelInformation.ReservedMask,
                     (UINTN) GraphicsOutput->Mode->Info->PixelsPerScanLine
                     );
      gtBS->FreePool (Info);
    } else {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputQueryModeBBTestFunctionAssertionGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode - SetMode() then QueryMode(), compare Info structure",
                     L"%a:%d: Status",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     Status
                     );

    }

    //
    //  One checkpoint to validate the GraphicsOutput->Mode->FrameBufferSize
    //
    if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
      switch (GraphicsOutput->Mode->Info->PixelFormat) {
        case PixelBitMask:
          PixelElementSize = 0;
          break;

        case PixelBlueGreenRedReserved8BitPerColor:
        case PixelRedGreenBlueReserved8BitPerColor:
          PixelElementSize = sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
          break;


        default:
          PixelElementSize = 0;
          break;
      }

      if (PixelElementSize != 0) {
        if (GraphicsOutput->Mode->FrameBufferSize != GraphicsOutput->Mode->Info->PixelsPerScanLine * 
          GraphicsOutput->Mode->Info->VerticalResolution * PixelElementSize) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gEfiGraphicsOutputQueryModeBBTestFunctionAssertionGuid,
                       L"EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode - SetMode() then QueryMode(), compare FrameBufferSize",
                       L"%a:%d: Status",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__
                       );
      }
    }
    
  }
  //
  // restore
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
                 L"%a:%d:Status:%r, Expected:EFI_SUCCESS",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  return EFI_SUCCESS;

}

//
// TDS 4.1.2
//
EFI_STATUS
BBTestEfiGraphicsOutputSetModeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode() function Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
{
  EFI_STATUS                            Status;

  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;
  UINT32                                Mode;
  UINT32                                ModeOrig;
  UINT32                                Index;
  UINTN                                 m;
  UINT32                                HorizontalResolution;
  UINT32                                VerticalResolution;
  UINTN                                 Size;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL         *BltBuffer;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL         *Blt;

  GraphicsOutput = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) ClientInterface;

  if ((Status = InitTestEnv (SupportHandle, &StandardLib, GraphicsOutput)) != EFI_SUCCESS) {
    return Status;

  }
  //
  // backup the orignal mode
  //
  ModeOrig = GraphicsOutput->Mode->Mode;

  //
  //  Try to validate that SetMode() clears the visible portions of the output display to black.
  //
  Mode = GraphicsOutput->Mode->MaxMode;

  if (Mode != 1) {
    if (ModeOrig > 0) {
      Index = 0;
    } else {
      Index = Mode - 1;
    }

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;
    Size                  = HorizontalResolution * VerticalResolution * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    BltBuffer             = NULL;
    
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
    BltBuffer->Blue     = 0xFF;
    BltBuffer->Green    = 0;
    BltBuffer->Red      = 0;
    BltBuffer->Reserved = 0;
    
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               BltBuffer,
                               EfiBltVideoFill,
                               0,
                               0,
                               0,
                               0,
                               HorizontalResolution,
                               VerticalResolution,
                               0
                               );

    if (BltBuffer != NULL)
        gBS->FreePool (BltBuffer);
    
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"GraphicsOutput.Blt - fill screen with one pixel(0,0)",
                     L"%a:%d:Status - %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      return Status;
    }
    
    Status = GraphicsOutput->SetMode (GraphicsOutput, Index);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Status != EFI_SUCCESS) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputSetModeBBTestFunctionAssertionGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                     L"%a:%d:Status:%r, Expected:EFI_SUCCESS",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      return Status;
    }

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;
    Size                  = HorizontalResolution * VerticalResolution * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    BltBuffer             = NULL;
    
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

    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               BltBuffer,
                               EfiBltVideoToBltBuffer,
                               0,
                               0,
                               0,
                               0,
                               HorizontalResolution,
                               VerticalResolution,
                               0
                               );

    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"GraphicsOutput.Blt - Read data from screen to BltBuffer",
                     L"%a:%d:Status - %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      if (BltBuffer != NULL)
        gBS->FreePool (BltBuffer);
      return Status;
    }   

    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for (m = 0; m < HorizontalResolution * VerticalResolution; m++) {
      Blt = BltBuffer + m;
      if ((Blt->Blue != 0x00) || (Blt->Green != 0x00) || (Blt->Red != 0x00)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        break;
      }
    }    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiGraphicsOutputSetModeBBTestFunctionAssertionGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                   L"%a:%d, The visible portions of the output screen should be black",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__
                   );
    
    if (BltBuffer != NULL) {
      gBS->FreePool (BltBuffer);
    }
    
  }

  //
  //  Assertion Point
  //  SetMode Should able to set the display Mode and return EFI_SUCCESS
  //
  for (Index = 0; Index < Mode; Index++) {
    Status = GraphicsOutput->SetMode (GraphicsOutput, Index);

    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiGraphicsOutputSetModeBBTestFunctionAssertionGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                   L"%a:%d:Status:%r, Expected:EFI_SUCCESS",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status
                   );

    if (Status != EFI_SUCCESS)
      return Status;

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;
    Size                  = HorizontalResolution * VerticalResolution * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    BltBuffer             = NULL;
    
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
    BltBuffer->Blue     = 0xFF;
    BltBuffer->Green    = 0;
    BltBuffer->Red      = 0;
    BltBuffer->Reserved = 0;
    
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               BltBuffer,
                               EfiBltVideoFill,
                               0,
                               0,
                               0,
                               0,
                               HorizontalResolution,
                               VerticalResolution,
                               0
                               );
    
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"GraphicsOutput.Blt - fill screen with one pixel(0,0)",
                     L"%a:%d:Status - %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      if (BltBuffer != NULL)
        gBS->FreePool (BltBuffer);
      return Status;
    }
    
    Status = GraphicsOutput->SetMode (GraphicsOutput, Index);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (Status != EFI_SUCCESS) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gEfiGraphicsOutputSetModeBBTestFunctionAssertionGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                     L"%a:%d:Status:%r, Expected:EFI_SUCCESS",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );    
      if (BltBuffer != NULL)
        gBS->FreePool (BltBuffer);
      return Status;
    }

    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               BltBuffer,
                               EfiBltVideoToBltBuffer,
                               0,
                               0,
                               0,
                               0,
                               HorizontalResolution,
                               VerticalResolution,
                               0
                               );

    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"GraphicsOutput.Blt - Read data from screen to BltBuffer",
                     L"%a:%d:Status - %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      if (BltBuffer != NULL)
        gBS->FreePool (BltBuffer);
      return Status;
    }   

    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for (m = 0; m < HorizontalResolution * VerticalResolution; m++) {
      Blt = BltBuffer + m;
      if ((Blt->Blue != 0x00) || (Blt->Green != 0x00) || (Blt->Red != 0x00)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        break;
      }
    }    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiGraphicsOutputSetModeBBTestFunctionAssertionGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                   L"%a:%d, The visible portions of the output screen should be black",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__
                   );
    
    if (BltBuffer != NULL) {
      gBS->FreePool (BltBuffer);
    }

  };

  //
  // restore the orignal Mode
  //
  Status = GraphicsOutput->SetMode (GraphicsOutput, ModeOrig);

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
                 L"%a:%d:Status:%r, Expected:EFI_SUCCESS",
                 (UINTN) __FILE__,
                 (UINTN) (UINTN)__LINE__,
                 (UINTN) Status
                 );

  return EFI_SUCCESS;

}

//
// TDS 4.1.3
//
EFI_STATUS
BBTestEfiGraphicsOutputBltVideoFillFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt()- BltVideoFill operation function Test

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

    Status = GraphicsOutput->SetMode (GraphicsOutput, Index);

    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                     L"%a:%d:Status:%r, Expected:%r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      return Status;
    }

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;
    Width                 = HorizontalResolution / 2;
    Height                = VerticalResolution / 2;

    Size                  = (Width + DestinationX) * (Height + DestinationY) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);

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
    // Call Blt() with BltOperation being EfiBltVideo Fill
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
    // Call Blt() with BltOperation being EfiBltVideoToBltBuffer
    // to retrieve rectangles drawn by last EfiUgaVideoFill operation
    //
    Status2 = GraphicsOutput->Blt (
                                GraphicsOutput,
                                BltBuffer2,
                                EfiBltVideoToBltBuffer,
                                DestinationX,
                                DestinationY,
                                SourceX,
                                SourceY,
                                Width,
                                Height,
                                Delta
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
                   gEfiGraphicsOutputBltVideoFillBBTestFunctionAssertionGuid001,
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
                   gEfiGraphicsOutputBltVideoFillBBTestFunctionAssertionGuid002,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiBltVideoFill",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status1,
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
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status2,
                   (UINTN) DestinationX,
                   (UINTN) DestinationY,
                   (UINTN) 0,
                   (UINTN) 0,
                   (UINTN) Width,
                   (UINTN) Height,
                   (UINTN) Delta
                   );
                   
    if (BltBuffer != NULL) {
      gBS->FreePool (BltBuffer);
    }

    if (BltBuffer2 != NULL) {
      gBS->FreePool (BltBuffer2);
    }
    //
    // Wait for some time
    //
    gtBS->Stall (100000);

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
                 L"%a:%d:Status:%r, Expected:EFI_SUCCESS",
                 (UINTN) __FILE__,
                 (UINTN) (UINTN)__LINE__,
                 (UINTN) Status
                 );

  return EFI_SUCCESS;

}

//
// TDS 4.1.4
//
EFI_STATUS
BBTestEfiGraphicsOutputBltVideoBltBufferFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt() - BltVideoToBltBuffer & BltBufferToVideo function Test

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

  UINTN                               SourceX;
  UINTN                               SourceY;
  UINTN                               DestinationX;
  UINTN                               DestinationY;
  UINTN                               Width;
  UINTN                               Height;
  UINTN                               Delta;
  UINTN                               Size;
  UINTN                               m;
  UINTN                               IndexWidth;
  UINTN                               IndexHeight;
  UINTN                               IndexPos;
  UINT32                              HorizontalResolution;
  UINT32                              VerticalResolution;
  UINT32                              *DwordPtr;

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

    Status = GraphicsOutput->SetMode (GraphicsOutput, Index);

    if (Status != EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;

      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gTestGenericFailureGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                     L"%a:%d:Status:%r, Expected:EFI_SUCCESS",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      return Status;
    }

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;

    Width                 = HorizontalResolution / 2;
    Height                = VerticalResolution / 2;
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
    // Call Blt() with BltOperation being EfiUgaVideoToBltBuffer
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
                   gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid001,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status,
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
    // Initialize the buffer content.
    //
    DwordPtr = (UINT32 *) BltBuffer;
    for (m = 0; m < Size / 4; m++) {
      *DwordPtr = (UINT32) m * 0x12345678;
      DwordPtr++;
    }
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
                   gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid002,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d ",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status2,
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
                   gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid003,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltBufferToVideo - Blt/EfiBltBufferToVideo",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d ",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status1,
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
#if 1
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

#else
    m = IndexWidth = IndexHeight = IndexPos = 0;
#endif
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gEfiGraphicsOutputBltVideoBltBufferBBTestFunctionAssertionGuid004,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/(EfiBltVideoToBltBuffer,EfiBltBufferToVideo) - Blt/EfiBltVideoToBltBuffer,EfiBltBufferToVideo), Pixel verification",
                   L"%a:%d: Status = %r,Video Source=(%dx%d),Buffer Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status,
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
                 L"%a:%d:Status:%r, Expected:EFI_SUCCESS",
                 (UINTN) __FILE__,
                 (UINTN) (UINTN)__LINE__,
                 (UINTN) Status
                 );

  return EFI_SUCCESS;

}
//
// TDS 4.1.5
//
EFI_STATUS
BBTestEfiGraphicsOutputBltVideoToVideoFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL   *This,
  IN VOID                   *ClientInterface,
  IN EFI_TEST_LEVEL         TestLevel,
  IN EFI_HANDLE             SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt() - BltVideoToVideo function Test

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

  UINTN                               SourceX;
  UINTN                               SourceY;
  UINTN                               DestinationX;
  UINTN                               DestinationY;
  UINTN                               Width;
  UINTN                               Height;
  UINTN                               Delta;
  UINTN                               Size;
  UINT32                              HorizontalResolution;
  UINT32                              VerticalResolution;
  UINTN                               m;

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
    Status = GraphicsOutput->SetMode (GraphicsOutput, Index);

    if (Status != EFI_SUCCESS) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() Function Test",
                     L"%a:%d:Status:%r, Expected:%r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      continue;
    }

    HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
    VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;

    Width                 = HorizontalResolution / 2;
    Height                = VerticalResolution / 2;

    //
    // Clear Screen
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
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt - GraphicsOutputClearScreen",
                     L"%a:%d: Status = %r",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) Status
                     );
      continue;
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

    Blt           = BltBuffer;
    Blt->Blue     = 0xFF;
    Blt->Green    = 0x00;
    Blt->Red      = 0x00;
    Blt->Reserved = 0;

    //
    // Call Blt() with BltOperation being EfiUgaVideo Fill
    //
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               BltBuffer,
                               EfiBltVideoFill,
                               0,
                               0,
                               SourceX,
                               SourceY,
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
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToVideo - Blt/EfiBltVideoFill",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status,
                   (UINTN) 0,
                   (UINTN) 0,
                   (UINTN) SourceX,
                   (UINTN) SourceY,
                   (UINTN) Width,
                   (UINTN) Height
                   );
    gtBS->Stall (5000);
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

    gtBS->Stall (50000);
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
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status,
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
                   gTestGenericFailureGuid,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToBltBuffer - Blt/EfiBltVideoToBltBuffer",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status1,
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
                   gEfiGraphicsOutputBltVideoVideoBBTestFunctionAssertionGuid001,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToVideo - Blt/EfiBltVideoToVideo",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status2,
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
                   gEfiGraphicsOutputBltVideoVideoBBTestFunctionAssertionGuid002,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt/EfiBltVideoToVideo - Blt/EfiBltVideoToVideo, Pixel verification",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) Status,
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
                 L"%a:%d:Status:%r, Expected:EFI_SUCCESS",
                 (UINTN) __FILE__,
                 (UINTN) (UINTN)__LINE__,
                 (UINTN) Status
                 );

  return EFI_SUCCESS;

}
