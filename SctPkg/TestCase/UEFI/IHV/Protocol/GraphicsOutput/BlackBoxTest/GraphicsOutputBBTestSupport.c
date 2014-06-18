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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  GraphicsOutputBBTestSupport.c

Abstract:

  The Support Functions Provided for Test Cases of Graphics Output Protocol

References:
  UEFI 2.0 Specification
  Graphics Output Protocol Test Design Specification
  UEFI/Tiano DXE Test Case Writer's Guide

Revision History

--*/


#include "SctLib.h"
#include "GraphicsOutputBBTest.h"

EFI_EVENT TimerEvent;

EFI_STATUS
InitTestEnv (
  IN EFI_HANDLE                         SupportHandle,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL **StandardLib,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL       *GraphicsOutput

  )
/*++

Routine Description:

  find the Standard Test Libray Interface from SupportHandle,
  locate the DevicePath Protocol bound to GraphicsOutput Protocol,
  output the device path string


Arguments:

  SupportHandle     - The handle to find the S.T.L. Interface
  GraphicsOutput    - The protocol to find its corresponse device path
  StandardLib       - The S.T.L. interface instance found with S.T.L. GUID

Returns:

  EFI_SUCCESS      - No error occurs
  EFI_DEVICE_ERROR - Something wrong.

--*/
{
  EFI_STATUS                    Status;

  UINTN                         NoHandles;
  UINTN                         Index;
  EFI_HANDLE                    *HandleBuffer;
  EFI_GRAPHICS_OUTPUT_PROTOCOL  *OtherGraphicsOutput;

  EFI_DEVICE_PATH_PROTOCOL      *DevicePath;
  CHAR16                        *DevicePathStr;

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   StandardLib
                   );

  if (EFI_ERROR (Status)) {
    (*StandardLib)->RecordAssertion (
                      (*StandardLib),
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
  //
  // Locate the Handle that the GraphicsOutput interface is bound to
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiGraphicsOutputProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    (*StandardLib)->RecordAssertion (
                      (*StandardLib),
                      EFI_TEST_ASSERTION_FAILED,
                      gTestGenericFailureGuid,
                      L"BS.LocateHandle - LocateHandle",
                      L"%a:%d:Status - %r",
                      __FILE__,
                      (UINTN)__LINE__,
                      Status
                      );
    return Status;
  }

  if (NoHandles <= 0 || HandleBuffer == NULL) {
    (*StandardLib)->RecordAssertion (
                      (*StandardLib),
                      EFI_TEST_ASSERTION_FAILED,
                      gTestGenericFailureGuid,
                      L"BS.LocateHandle - LocateHandle",
                      L"%a:%d:Device Error",
                      __FILE__,
                      (UINTN)__LINE__
                      );
    return EFI_DEVICE_ERROR;
  }
  //
  // Find the exact handle that GraphicsOutput bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiGraphicsOutputProtocolGuid,
                     &OtherGraphicsOutput
                     );
    if (EFI_ERROR (Status)) {
      (*StandardLib)->RecordAssertion (
                        (*StandardLib),
                        EFI_TEST_ASSERTION_FAILED,
                        gTestGenericFailureGuid,
                        L"BS.HandleProtocol - HandleProtocol",
                        L"%a:%d:Status - %r",
                        __FILE__,
                        (UINTN)__LINE__,
                        Status
                        );

      gtBS->FreePool (HandleBuffer);
      return Status;
    }

    if (OtherGraphicsOutput == GraphicsOutput) {
      break;
    }
  }
  //
  // Locate the DevicePath Protocol bound to GraphicsOutput Protocol
  //
  if (Index >= NoHandles) {
    //
    // No Handle Found!!
    //
    gtBS->FreePool (HandleBuffer);

    return EFI_DEVICE_ERROR;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gEfiDevicePathProtocolGuid,
                   &DevicePath
                   );

  gtBS->FreePool (HandleBuffer);

  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      (*StandardLib)->RecordMessage (
                        (*StandardLib),
                        EFI_VERBOSE_LEVEL_DEFAULT,
                        L"\r\nCurrent Device: %s",
                        DevicePathStr
                        );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR (Status)) {
        (*StandardLib)->RecordAssertion (
                          (*StandardLib),
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
    // Console Splitter/GraphicsOutput, must add to continue run the rest of the test case
    //
    (*StandardLib)->RecordMessage (
                      (*StandardLib),
                      EFI_VERBOSE_LEVEL_DEFAULT,
                      L"\r\nCurrent Device: ConsoleSplitter/GraphicsOutput"
                      );

    return EFI_SUCCESS;
  }

  return Status;
}

EFI_STATUS
GraphicsOutputClearScreen (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL      *GraphicsOutput,
  IN  UINTN                             HorizontalResolution,
  IN  UINTN                             VerticalResolution
  )
/*++

Routine Description:

  Clear the whole screen

Arguments:

  GraphicsOutput        - GraphicsOutPut protocol interface
  HorizontalResolution  - Horizontal resolution of the screen
  VerticalResolution    - Vertical resolution of the screen

Returns:

  EFI_SUCCESS - No error occurs
  
--*/
{
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL blt;
  
  blt.Blue = 0;
  blt.Red = 0;
  blt.Green = 0;

  return GraphicsOutput->Blt (
                           GraphicsOutput,
                           &blt,
                           EfiBltVideoFill,
                           0,
                           0,
                           0,
                           0,
                           HorizontalResolution,
                           VerticalResolution,
                           0
                           );
}


VOID
GetTestData (
  IN  UINTN        Index,
  IN  UINTN        *Width,
  IN  UINTN        *Height,
  IN  UINTN        *SourceX,
  IN  UINTN        *SourceY,
  IN  UINTN        *DestinationX,
  IN  UINTN        *DestinationY,
  IN  UINTN        *Delta,
  IN  UINTN        HorizontalResolution,
  IN  UINTN        VerticalResolution
  )
/*++

Routine Description:

  Assistant function for preparing test data

Arguments:

  Index                 - Index of the current test count
  Width                 - Test data for Width to be returned
  Height                - Test data for Height to be returned
  SourceX               - Test data for SourceX to be returned
  SourceY               - Test data for SourceY to be returned
  DestinationX          - Test data for DestinationX to be returned
  DestinationY          - Test data for DestinationY to be returned
  Delta                 - Test data for Delta to be returned
  HorizontalResolution  - Test data for HorizontalResolution to be returned
  VerticalResolution    - Test data for VerticalResolution to be returned

Returns:

  No return status.

--*/
{
  switch (Index / (DEMO_SOURCE_POSITION_ENUM * DEMO_DESTINATION_POSITION_ENUM * DEMO_DELTA_ENUM)) {
  //
  // Width & Height evaluation
  //
  case 0:
    *Width  = 100;
    *Height = 100;
    break;

  case 1:
    *Width  = HorizontalResolution / 2;
    *Height = VerticalResolution / 2;
    break;

  default:
    *Width  = 0;
    *Height = 0;
    break;
  }

  Index = Index % (DEMO_SOURCE_POSITION_ENUM * DEMO_DESTINATION_POSITION_ENUM * DEMO_DELTA_ENUM);

  switch (Index / (DEMO_DESTINATION_POSITION_ENUM * DEMO_DELTA_ENUM)) {
  //
  // Source evaluation
  //
  case 0:
    *SourceX  = 0;
    *SourceY  = 0;
    break;

  case 1:
    *SourceX  = 100;
    *SourceY  = 100;
    break;

  case 2:
    *SourceX  = HorizontalResolution / 2;
    *SourceY  = VerticalResolution / 2;
    break;

  default:
    *SourceX  = HorizontalResolution + 1;
    *SourceY  = VerticalResolution + 1;
    break;
  }

  Index = Index % (DEMO_DESTINATION_POSITION_ENUM * DEMO_DELTA_ENUM);

  switch (Index / DEMO_DELTA_ENUM) {
  //
  // Destination evaluation
  //
  case 0:
    *DestinationX = 0;
    *DestinationY = 0;
    break;

  case 1:
    *DestinationX = 100;
    *DestinationY = 100;
    break;

  case 2:
    *DestinationX = HorizontalResolution / 2;
    *DestinationY = VerticalResolution / 2;
    break;

  default:
    *DestinationX = HorizontalResolution + 1;
    *DestinationY = VerticalResolution + 1;
    break;
  }

  Index = Index % DEMO_DELTA_ENUM;
  switch (Index) {
  //
  // Delta evaluation
  //
  case 0:
    *Delta = 0;
    break;

  case 1:
    *Delta = 100 * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    break;

  case 2:
    *Delta = (*Width / 2) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    break;

  case 3:
    *Delta = (*Width) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    break;

  default:
    *Delta = (*Width + 1) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
  }
}


EFI_STATUS
LoadBmp (
  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL  **BltBuffer,
  IN UINTN                          *Width,
  IN UINTN                          *Height
  )
/*++

Routine Description:

  Assistant function for loading a bmp file

Arguments:

  BltBuffer - Buffer for loading a bmp file
  Width     - Width of the bmp file
  Height    - Height of the bmp file

Returns:

  EFI_SUCCESS - No error returns

--*/
{

  EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Blt;
  EFI_STATUS                    Status;
  UINTN                         IndexX;
  UINTN                         IndexY;
  UINTN                         m;
  UINTN                         Wx;
  UINTN                         Hy;

  Wx  = 150;
  Hy  = 150;

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Wx * Hy * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL),
                   (VOID **) &Blt
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SctZeroMem (Blt, Wx * Hy * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

  for (IndexY = 0; IndexY < Hy / 3; IndexY++) {
    for (IndexX = 0; IndexX < Wx; IndexX++) {
      m               = IndexY * Wx + IndexX;

      Blt[m].Blue     = 0xFF;
      Blt[m].Green    = 0x00;
      Blt[m].Red      = 0x00;
      Blt[m].Reserved = 0x00;
    }
  }

  for (IndexY = Hy / 3; IndexY < (Hy / 3) * 2; IndexY++) {
    for (IndexX = 0; IndexX < Wx; IndexX++) {
      m               = IndexY * Wx + IndexX;

      Blt[m].Blue     = 0x00;
      Blt[m].Green    = 0xFF;
      Blt[m].Red      = 0x00;
      Blt[m].Reserved = 0x00;
    }
  }

  for (IndexY = (Hy / 3) * 2; IndexY < Hy; IndexY++) {
    for (IndexX = 0; IndexX < Wx; IndexX++) {
      m               = IndexY * Wx + IndexX;

      Blt[m].Blue     = 0x00;
      Blt[m].Green    = 0x00;
      Blt[m].Red      = 0xFF;
      Blt[m].Reserved = 0x00;
    }
  }

  *BltBuffer  = Blt;
  *Width      = Wx;
  *Height     = Hy;
  return EFI_SUCCESS;
}

BOOLEAN
AutoJudgeGop (
  IN  UINTN         X,
  IN  UINTN         Y,
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  )
/*++

Routine Description:

  Assistant function to auto judge the user's choice, correct or uncorrect?

Arguments:

  X       - The coordination of X
  Y       - The coordination of Y
  Seconds - The time to wait the user for judging
  Default - Default value(True/False) for auto judge(Yes/No) 
  Message - The message printed to the serial port to remind the user

Returns:

  TRUE/FALSE standing for correct/uncorrect choice respectively

--*/
{
  EFI_STATUS    Status;
  EFI_EVENT     WaitList[2];
  UINTN         NoWait;
  UINTN         WaitIndex;
  EFI_INPUT_KEY Key;
  BOOLEAN       PressYes;
  CHAR16        *Msg;
  UINTN         AutoJudge;

  Msg       = NULL;
  AutoJudge = 1;

  Status = gtBS->CreateEvent (
                   EVT_TIMER,
                   0,
                   NULL,
                   NULL,
                   &TimerEvent
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Create event. %a:%d:%r\n", __FILE__, (UINTN)__LINE__, Status));
    return FALSE;
  }
  //
  // Set 1 second periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);

  //
  // Set up a wait list for a key and the timer
  //
  NoWait              = 0;
  WaitList[NoWait++]  = TimerEvent;
  WaitList[NoWait++]  = gtST->ConIn->WaitForKey;

  PressYes            = Default;
  //
  // Wait for either
  //
  SctPrintAt (Y, X, Message);
  while (AutoJudge && (Seconds > 0)) {
    if (Default == TRUE) {
      Msg = SctPoolPrint (L"Yes/No?(Auto judge as Yes in %d seconds  ", Seconds);
    } else {
      Msg = SctPoolPrint (L"Yes/No?(Auto judge as No in %d seconds   ", Seconds);
    }

    if (Msg == NULL) {
      return FALSE;
    } else {
      SctPrintAt (Y + 40, X, Msg);
      SctFreePool (Msg);
    }

    Status = gtBS->WaitForEvent (NoWait, WaitList, &WaitIndex);

    switch (WaitIndex) {
    case 0:
      Seconds--;
      if (Seconds <= 0) {
        //
        // To stop loop
        //
        AutoJudge = 0;
      }
      break;

    case 1:
      //
      // Read the key
      //
      Status = gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
      SctAPrint ((char *) (&Key.UnicodeChar));
      switch (Key.UnicodeChar) {
      case 'Y':
      case 'y':
        AutoJudge = 0;
        PressYes  = TRUE;
        break;

      case 'N':
      case 'n':
        AutoJudge = 0;
        PressYes  = FALSE;
        break;

      default:
        break;
      }
      break;

    default:
      break;
      //
      // bad WaitIndex response
      //
    }
  }
  //
  // SctPrint (L"\r\n");
  //
  // Done, cancle periodic timer event
  //
  gtBS->CloseEvent (TimerEvent);
  
  return PressYes;
}
