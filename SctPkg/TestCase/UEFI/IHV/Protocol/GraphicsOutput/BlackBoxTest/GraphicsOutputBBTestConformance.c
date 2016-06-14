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

  GraphicsOutputBBTestConformance.c

Abstract:

  Conformance Test Cases of Graphics Output Protocol
  
References:

  UEFI 2.0 Specification
  Graphics Output Protocol Test Design Specification
  UEFI/Tiano DXE Test Case Writer's Guide

--*/

#include "SctLib.h"
#include "GraphicsOutputBBTest.h"

//
// TDS 4.2.1
//
EFI_STATUS
BBTestQueryModeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode() Conformance Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  *info;
  UINTN                                 sizeofInfo;
  UINT32                                mode;

  GraphicsOutput = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) ClientInterface;

  if ((Status = InitTestEnv (SupportHandle, &StandardLib, GraphicsOutput)) != EFI_SUCCESS) {
    return Status;
  }

  info       = NULL;
  sizeofInfo = 0;
  //
  // Assertion Point
  // QueryMode should not succeed with invalid parameter
  //
  //
  // mode number is invalid
  //
  mode        = GraphicsOutput->Mode->MaxMode;

  sizeofInfo  = sizeof (EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);

  Status = GraphicsOutput->QueryMode (
                             GraphicsOutput,
                             mode,
                             &sizeofInfo,
                             &info
                             );
  if (Status != EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gGraphicsOutputQueryModeConformanceTestAssertionGuid001,
                 L"EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode - QueryMode() with MaxMode",
                 L"%a:%d:maxmode: %d,Status:%r, Expected:%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 mode,
                 Status,
                 EFI_INVALID_PARAMETER
                 );

  mode = GraphicsOutput->Mode->Mode;

  //
  // &sizeofInfo is invalid
  //
  Status = GraphicsOutput->QueryMode (
                             GraphicsOutput,
                             mode,
                             NULL,
                             &info
                             );
  if (Status != EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gGraphicsOutputQueryModeConformanceTestAssertionGuid002,
                 L"EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode - QueryMode() with NULL &SizeofInfo",
                 L"%a:%d: Input invalide &SizeofInfo,Status:%r, Expected:%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_INVALID_PARAMETER
                 );

  //
  // &info is invalid
  //
  Status = GraphicsOutput->QueryMode (
                             GraphicsOutput,
                             mode,
                             &sizeofInfo,
                             NULL
                             );
  if (Status != EFI_INVALID_PARAMETER) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gGraphicsOutputQueryModeConformanceTestAssertionGuid003,
                 L"EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode - QueryMode() with NULL &info",
                 L"%a:%d:, Input invalid &Info, Status:%r, Expected:%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 EFI_INVALID_PARAMETER
                 );

  //
  //
  //
  for (mode = 0; mode < GraphicsOutput->Mode->MaxMode; mode++) {
    sizeofInfo = 0;
    info       = NULL;
    Status = GraphicsOutput->QueryMode (
                               GraphicsOutput,
                               mode,
                               &sizeofInfo,
                               &info
                               );
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    if (info == NULL) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    if (sizeofInfo != sizeof (EFI_GRAPHICS_OUTPUT_MODE_INFORMATION)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gGraphicsOutputQueryModeConformanceTestAssertionGuid004,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode - QueryMode() with valid ModeNumber",
                   L"%a:%d:,size_out:%d,ModeNumber:%d,Status:%r, Expected:any value except %r",
                   (UINTN) __FILE__,
                   (UINTN) (UINTN)__LINE__,
                   (UINTN) sizeofInfo,
                   (UINTN) mode,
                   (UINTN) Status,
                   EFI_INVALID_PARAMETER
                   );
    if (info != NULL) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gGraphicsOutputQueryModeConformanceTestAssertionGuid005,
                     L"EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode - QueryMode() with ModeNumber, dump info structure",
                     L"%a:%d:,ModeNumber:%d,dump of info: version:%d, horizonResolution:%d, VerticalResolution:%d, PixelFormat:%d, RedMask:%x,GreenMask:%x,BlueMask:%x,ReserveMask:%x,PixelPerScanline:%d",
                     (UINTN) __FILE__,
                     (UINTN) (UINTN)__LINE__,
                     (UINTN) mode,
                     (UINTN) info->Version,
                     (UINTN) info->HorizontalResolution,
                     (UINTN) info->VerticalResolution,
                     (UINTN) info->PixelFormat,
                     (UINTN) info->PixelInformation.RedMask,
                     (UINTN) info->PixelInformation.GreenMask,
                     (UINTN) info->PixelInformation.BlueMask,
                     (UINTN) info->PixelInformation.ReservedMask,
                     (UINTN) info->PixelsPerScanLine
                     );
      gtBS->FreePool ((VOID *)info);
    }
  }
  //
  // Check the mode structure
  //
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if (GraphicsOutput->Mode == NULL) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gGraphicsOutputQueryModeConformanceTestAssertionGuid006,
                 L"EFI_GRAPHICS_OUTPUT_PROTOCOL.QueryMode - Dump the Mode structure",
                 L"%a:%d:, dump of Mode: MaxMode:%d, current mode:%d, Info addre:%x, sizeofInfo:%d, frameBufferBase:%x, FrameBufferSize:%x",
                 (UINTN) __FILE__,
                 (UINTN) (UINTN)__LINE__,
                 (UINTN) GraphicsOutput->Mode->MaxMode,
                 (UINTN) GraphicsOutput->Mode->Mode,
                 (UINTN) GraphicsOutput->Mode->Info,
                 (UINTN) GraphicsOutput->Mode->SizeOfInfo,
                 (UINTN) GraphicsOutput->Mode->FrameBufferBase,
                 (UINTN) GraphicsOutput->Mode->FrameBufferSize
                 );

  return EFI_SUCCESS;
}

//
// TDS 4.2.3
//
EFI_STATUS
BBTestBltConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt() Conformance Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_GRAPHICS_OUTPUT_PROTOCOL        *GraphicsOutput;

  EFI_TEST_ASSERTION                  AssertionType;

  EFI_GRAPHICS_OUTPUT_BLT_PIXEL       BltBuffer[10];

  UINTN                               SourceX;
  UINTN                               SourceY;
  UINTN                               DestinationX;
  UINTN                               DestinationY;
  UINTN                               Width;
  UINTN                               Height;
  UINTN                               Delta;
  UINTN                               Index;
  EFI_GRAPHICS_OUTPUT_BLT_OPERATION   BltOperation;

  SourceX         = 0;
  SourceY         = 0;
  DestinationX    = 0;
  DestinationY    = 0;
  Width           = 1;
  Height          = 1;
  Delta           = 0;

  GraphicsOutput  = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) ClientInterface;

  if ((Status = InitTestEnv (SupportHandle, &StandardLib, GraphicsOutput)) != EFI_SUCCESS) {
    return Status;

  }
  //
  // Assertion Point
  // Blt should not succeed with invalid parameter
  //
  for (Index = 0; Index < 6; Index++) {
    switch (Index) {
    case 0:
      BltOperation = EfiGraphicsOutputBltOperationMax;
      break;

    case 1:
      BltOperation = EfiGraphicsOutputBltOperationMax + 1;
      break;

    case 2:
      BltOperation = EfiGraphicsOutputBltOperationMax + 10;
      break;

    case 3:
      BltOperation = EfiGraphicsOutputBltOperationMax + 100;
      break;

    case 4:
      BltOperation = EfiGraphicsOutputBltOperationMax + 1000;
      break;

    case 5:
      BltOperation = -1;
      break;

    default:
      BltOperation = EfiGraphicsOutputBltOperationMax - 1;
      break;
    }
    //
    // test data verification
    //
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
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

    if (Status != EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gGraphicsOutputBltConformanceTestAssertionGuid001,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt - Blt() with invalid BltOperation",
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

//
// TDS 4.2.2
//
EFI_STATUS
BBTestSetModeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
/*++

Routine Description:

  Entrypoint for EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode() Conformance Test

Arguments:

  This            - A pointer of EFI_BB_TEST_PROTOCOL
  ClientInterface - A pointer to the interface to be tested
  TestLevel       - Test "thoroughness" control
  SupportHandle   - A handle containing protocols required

Returns:

  EFI_SUCCESS - Finish the test successfully

--*/
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;

  EFI_TEST_ASSERTION                    AssertionType;

  UINT32                                Index;

  UINT32                                CurrentMode;
  UINT32                                MaxMode;
  UINTN                                 sizeofInfo;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  *info;

  GraphicsOutput  = (EFI_GRAPHICS_OUTPUT_PROTOCOL *) ClientInterface;

  CurrentMode     = GraphicsOutput->Mode->Mode;

  if ((Status = InitTestEnv (SupportHandle, &StandardLib, GraphicsOutput)) != EFI_SUCCESS) {
    return Status;

  }
  //
  // Assertion Point
  //
  //
  MaxMode = GraphicsOutput->Mode->MaxMode;
  for (Index = 0; Index < MaxMode; Index++) {

    Status = GraphicsOutput->SetMode (
                              GraphicsOutput,
                              Index
                              );

    if (Status == EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gGraphicsOutputSetModeConformanceTestAssertionGuid001,
                   L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() with valid mode",
                   L"%a:%d: mode:%d,Status = %r,Expected = not EFI_UNSUPPORTED ",
                   __FILE__,
                   (UINTN)__LINE__,
                   Index,
                   Status
                   );
    //
    // Check the content of info
    //
    if (Status == EFI_SUCCESS) {
      sizeofInfo = 0;
      info       = NULL;
      Status = GraphicsOutput->QueryMode (
                                 GraphicsOutput,
                                 Index,
                                 &sizeofInfo,
                                 &info
                                 );
      if (Status != EFI_SUCCESS) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }   else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }

      if (SctCompareMem ((VOID *) info,
          (void *) GraphicsOutput->Mode->Info,
          sizeof (EFI_GRAPHICS_OUTPUT_MODE_INFORMATION)
          ) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      if (info != NULL) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gGraphicsOutputSetModeConformanceTestAssertionGuid002,
                       L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() then QueryMode(), compare Info structure",
                       L"%a:%d: dump of query result:ver:%d, hRes:%d, VRes:%d, PixelFmt:%d, RMsk:%x,GMsk:%x,BMsk:%x,ReserveMask:%x,PixelPerScanline:%d\n dump of GOP->Info:ver:%d, hRes:%d, VRes:%d, PixelFmt:%d, RMsk:%x,GMsk:%x,BMsk:%x,ReserveMask:%x,PixelPerScanline:%d",
                       (UINTN) __FILE__,
                       (UINTN) (UINTN)__LINE__,
                       (UINTN) info->Version,
                       (UINTN) info->HorizontalResolution,
                       (UINTN) info->VerticalResolution,
                       (UINTN) info->PixelFormat,
                       (UINTN) info->PixelInformation.RedMask,
                       (UINTN) info->PixelInformation.GreenMask,
                       (UINTN) info->PixelInformation.BlueMask,
                       (UINTN) info->PixelInformation.ReservedMask,
                       (UINTN) info->PixelsPerScanLine,
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
        gtBS->FreePool (info);
      }
    }
  }

  Status = GraphicsOutput->SetMode (
                            GraphicsOutput,
                            MaxMode
                            );

  if (Status != EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gGraphicsOutputSetModeConformanceTestAssertionGuid003,
                 L"EFI_GRAPHICS_OUTPUT_PROTOCOL.SetMode - SetMode() with invalid (max)mode",
                 L"%a:%d: mode:%d,Status = %r,Expected =  EFI_UNSUPPORTED ",
                 __FILE__,
                 (UINTN)__LINE__,
                 MaxMode,
                 Status
                 );

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
