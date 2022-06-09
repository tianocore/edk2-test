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

  UgaDrawBBTestMain.c

Abstract:

  Test Driver of UGA Draw Protocol

--*/


#include "SctLib.h"
#include "UgaDrawBBTestMain.h"

#define  NEED_MORE_STRESS_TEST

#ifdef NEED_MORE_STRESS_TEST

DEMO_RESOLUTION_TYPE     DemoResolution[]  = {{800, 600}, {800, 640}, {640, 480}, {1024, 768}, {1280, 1024}, {1600, 1200}};
DEMO_REFRESH_RATE_TYPE   DemoRefreshRate[] = {60, 72, 75, 80, 85, 90, 100, 110, 120, 160};

#else

DEMO_RESOLUTION_TYPE     DemoResolution[]  = {{800, 600}, {800, 640}, {640, 480}, {1024, 768}};
DEMO_REFRESH_RATE_TYPE   DemoRefreshRate[] = {60};

#endif

DEMO_COLOR_DEPTH_TYPE    DemoColorDepth[]  = {32, 24};

EFI_EVENT                TimerEvent;

//
// Build Data structure here
//
EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  UGA_DRAW_PROTOCOL_TEST_REVISION,
  EFI_UGA_DRAW_PROTOCOL_GUID,
  L"UGA Draw Protocol Test",
  L"UEFI UGA Draw Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    UGA_DRAW_PROTOCOL_GETMODE_FUNCTION_AUTO_GUID,
    L"GetMode/SetMode_Func",
    L"Perform auto function checkes on the GetMode/SetMode interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetModeFunctionAutoTest
  },
  {
    UGA_DRAW_PROTOCOL_EFIUGAVIDEOFILL_FUNCTION_AUTO_GUID,
    L"Blt-EfiUgaVideoFill_Func",
    L"Perform auto function checkes on the Blt()-EfiUgaVideoFill",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestEfiUgaVideoFillFunctionAutoTest
  },

  {
    UGA_DRAW_PROTOCOL_EFIUGAVIDEOBLTBUFFER_FUNCTION_AUTO_GUID,
    L"Blt-EfiUgaVideoToBltBuffer&BltBufferToVideo_Func",
    L"Perform auto function checkes on the Blt()-EfiUgaVideoToBltBuffer&BltBufferToVideo",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestEfiUgaVideoBltBufferFunctionAutoTest
  },
  {
    UGA_DRAW_PROTOCOL_EFIUGAVIDEOTOVIDEO_FUNCTION_AUTO_GUID,
    L"Blt-EfiUgaVideoToVideo_Func",
    L"Perform auto function checkes on the Blt()-EfiUgaVideoToVideo",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestEfiUgaVideoToVideoFunctionAutoTest
  },

  //
  // Conformance Function
  //
  {
    UGA_DRAW_PROTOCOL_GETMODE_CONFORMANCE_AUTO_GUID,
    L"GetMode_Conf",
    L"Perform auto conformance checkes on the GetMode",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetModeConformanceAutoTest
  },
  {
    UGA_DRAW_PROTOCOL_BLT_CONFORMANCE_AUTO_GUID,
    L"Blt_Conf",
    L"Perform auto conformance checkes on the Blt",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestBltConformanceAutoTest
  },

  //
  // Extensive Function
  //
#ifdef EFI_TEST_EXHAUSTIVE
  {
    UGA_DRAW_PROTOCOL_VIDEOFILL_BUFFERTOVIDEO_EXTENSIVE_MANUAL_GUID,
    L"Blt-VideoFill/BufferToVideo_Extensive_Manual",
    L"Perform manual extensive checkes on the Blt VideoFill/BufferToVideo",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestVideoFillBufferToVideoManualTest
  },

  {
    UGA_DRAW_PROTOCOL_VIDEOFILL_VIDEOTOVIDEO_EXTENSIVE_MANUAL_GUID,
    L"Blt-VideoFill/VideoToVideo_Extensive_Manual",
    L"Perform manual extensive checkes on the Blt VideoFill/VideoToVideo",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestVideoFillVideoToVideoManualTest
  },
 {
    UGA_DRAW_PROTOCOL_VIDEOTOBLTBUFFER_EXTENSIVE_AUTO_GUID,
    L"Blt-VideoToBltBuffer_Extensive",
    L"Perform auto extensive checkes on the Blt VideoToBltBuffer",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestVideoToBltBufferAutoTest
  },
  {
    UGA_DRAW_PROTOCOL_EFIUGAVIDEOFILL_STRESS_AUTO_GUID,
    L"Blt-EfiUgaVideoFill_Stress",
    L"Perform auto function checkes on the Blt()-EfiUgaVideoFill",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestEfiUgaVideoFillStressAutoTest
  },

  {
    UGA_DRAW_PROTOCOL_EFIUGAVIDEOBLTBUFFER_STRESS_AUTO_GUID,
    L"Blt-EfiUgaVideoToBltBuffer&BltBufferToVideo_Stress",
    L"Perform auto function checkes on the Blt()-EfiUgaVideoToBltBuffer&BltBufferToVideo",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestEfiUgaVideoBltBufferStressAutoTest
  },
  {
    UGA_DRAW_PROTOCOL_EFIUGAVIDEOTOVIDEO_STRESS_AUTO_GUID,
    L"Blt-EfiUgaVideoToVideo_Stress",
    L"Perform auto function checkes on the Blt()-EfiUgaVideoToVideo",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestEfiUgaVideoToVideoStressAutoTest
  },
#endif

  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestUgaDrawProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  UGA Draw Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestUgaDraw (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);
  SctInitializeDriver (ImageHandle, SystemTable);

  //
  // Initialize Demo Data
  //
  DemoResolutionMax  = sizeof (DemoResolution) / sizeof (DEMO_RESOLUTION_TYPE);
  DemoRefreshRateMax = sizeof (DemoRefreshRate) / sizeof (DEMO_REFRESH_RATE_TYPE);
  DemoColorDepthMax  = sizeof (DemoColorDepth) / sizeof (DEMO_COLOR_DEPTH_TYPE);

  gtBS->CreateEvent (EVT_TIMER, 0, (EFI_EVENT_NOTIFY) NULL, NULL, &TimerEvent);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestUgaDrawProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
EFIAPI
BBTestUgaDrawProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  gtBS->CloseEvent (TimerEvent);

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}


static EFI_UGA_PIXEL mEfiColors[16] = {
  0x00, 0x00, 0x00, 0x00,
  0x98, 0x00, 0x00, 0x00,
  0x00, 0x98, 0x00, 0x00,
  0x98, 0x98, 0x00, 0x00,
  0x00, 0x00, 0x98, 0x00,
  0x98, 0x00, 0x98, 0x00,
  0x00, 0x98, 0x98, 0x00,
  0x98, 0x98, 0x98, 0x00,
  0x10, 0x10, 0x10, 0x00,
  0xff, 0x10, 0x10, 0x00,
  0x10, 0xff, 0x10, 0x00,
  0xff, 0xff, 0x10, 0x00,
  0x10, 0x10, 0xff, 0x00,
  0xf0, 0x10, 0xff, 0x00,
  0x10, 0xff, 0xff, 0x00,
  0xff, 0xff, 0xff, 0x00,
};

/**
 *  Assistant function for print some text in Uga mode
 *  @param UgaDraw protocol interface
 *  @param Sto TextOut Protocol interface
 *  @param X/Y coordinate of destine location
 *  @param Foreground/Background fore/back ground color
 *  @param fmt text to be printted
 *  @return status
 */
UINTN
_IPrint (
  IN EFI_UGA_DRAW_PROTOCOL            *UgaDraw,
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL     *Sto,
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_UGA_PIXEL                    *Foreground,
  IN EFI_UGA_PIXEL                    *Background,
  IN CHAR16                           *fmt
  )
{
  VOID                                *Buffer;
  EFI_STATUS                          Status;
  UINT16                              GlyphWidth;
  UINT32                              GlyphStatus;
  UINT16                              StringIndex;
  UINTN                               Index;
  CHAR16                              *UnicodeWeight;
  EFI_NARROW_GLYPH                    *Glyph;
  UINTN                               Size;
  EFI_HII_PROTOCOL                    *Hii;
  EFI_HANDLE                          Handle;
  EFI_UGA_PIXEL                       *LineBuffer;
  UINT32                              HorizontalResolution;
  UINT32                              VerticalResolution;
  UINT32                              ColorDepth;
  UINT32                              RefreshRate;


  GlyphStatus = 0;

  //
  // For now, allocate an arbitrarily long buffer
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   0x10000,
                   (VOID **) &Buffer
                   );

  //SctZeroMem (Buffer, 0x10000);

  CopyUnicodeString ((CHAR16 *) Buffer, fmt);
  UgaDraw->GetMode (UgaDraw, &HorizontalResolution, &VerticalResolution, &ColorDepth, &RefreshRate);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof (EFI_UGA_PIXEL) * HorizontalResolution * GLYPH_HEIGHT,
                   (VOID **)&LineBuffer
                   );

  if (EFI_ERROR (Status)) {
    gtBS->FreePool (Buffer);
    return Status;
  }

  Size = sizeof (EFI_HANDLE);

  Status = gtBS->LocateHandle (
                   ByProtocol,
                   &gBlackBoxEfiHiiProtocolGuid,
                   NULL,
                   &Size,
                   &Handle
                   );

  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = gtBS->HandleProtocol (
                   Handle,
                   &gBlackBoxEfiHiiProtocolGuid,
                   (VOID **) &Hii
                   );

  if (EFI_ERROR (Status)) {
    goto Error;
  }

  UnicodeWeight = (CHAR16 *)Buffer;

  for (Index = 0; UnicodeWeight[Index] != 0; Index++) {
    if (UnicodeWeight[Index] == CHAR_BACKSPACE ||
        UnicodeWeight[Index] == CHAR_LINEFEED ||
        UnicodeWeight[Index] == CHAR_CARRIAGE_RETURN) {
      UnicodeWeight[Index] = 0;
    }
  }

  for (Index = 0; Index < SctStrLen (Buffer); Index++) {
    StringIndex = (UINT16)Index;
    Status = Hii->GetGlyph (Hii, UnicodeWeight, &StringIndex, (UINT8 **)&Glyph, &GlyphWidth, &GlyphStatus);
    if (EFI_ERROR (Status)) {
      goto Error;
    }

    if (Foreground == NULL || Background == NULL) {
      Status = Hii->GlyphToBlt (Hii, (UINT8 *)Glyph, mEfiColors[Sto->Mode->Attribute & 0x0f], mEfiColors[Sto->Mode->Attribute >> 4], SctStrLen (Buffer), GlyphWidth, GLYPH_HEIGHT, &LineBuffer[Index * GLYPH_WIDTH]);
    } else {
      Status = Hii->GlyphToBlt (Hii, (UINT8 *)Glyph, *Foreground, *Background, SctStrLen (Buffer), GlyphWidth, GLYPH_HEIGHT, &LineBuffer[Index * GLYPH_WIDTH]);
    }
  }

  //
  // Blt a character to the screen
  //
  Status = UgaDraw->Blt (
                      UgaDraw,
                      LineBuffer,
                      EfiUgaBltBufferToVideo,
                      0,
                      0,
                      X,
                      Y,
                      GLYPH_WIDTH * SctStrLen (Buffer),
                      GLYPH_HEIGHT,
                      GLYPH_WIDTH * SctStrLen (Buffer) * sizeof (EFI_UGA_PIXEL)
                      );

Error:
  gtBS->FreePool (LineBuffer);
  gtBS->FreePool (Buffer);
  return Status;
}

/**
 *  Assistant function for print some text in Uga mode
 *  @param UgaDraw protocol interface
 *  @param X/Y coordinate of destine location
 *  @param Foreground/Background fore/back ground color
 *  @param fmt text to be printted
 *  @return status
 */
UINTN
UgaPrintXY (
  IN EFI_UGA_DRAW_PROTOCOL            *UgaDraw,
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_UGA_PIXEL                    *ForeGround,  OPTIONAL
  IN EFI_UGA_PIXEL                    *BackGround,  OPTIONAL
  IN CHAR16                           *Fmt
  )
{
  EFI_HANDLE                          Handle;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL        *Sto;
  EFI_STATUS                          Status;



  Handle = gtST->ConsoleOutHandle;

  Status = gtBS->HandleProtocol (
                   Handle,
                   &gBlackBoxEfiSimpleTextOutProtocolGuid,
                   (VOID **) &Sto
                   );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  return _IPrint (UgaDraw, Sto, X, Y, ForeGround, BackGround, Fmt);
}

/**
 *  Assistant function to copy a Unicode string to destination
 *  @param  Destination buffer of destine Unicode string
 *  @param  Source buffer of original Unicode string
 */
VOID
CopyUnicodeString (
  IN CHAR16                     *Destination,
  IN CHAR16                     *Source
  )
{
  UINTN                Index = 0;
  while (Source != NULL && (*Source) != 0 && Index < 255) {
    *Destination=*Source;
    Destination++;
    Source++;
  }
  *Destination = 0;
}

/**
 *  Assistant function for print some text in Uga mode
 *  @param X/Y coordinate of destine location
 *  @param Foreground/Background fore/back ground color
 *  @param fmt text to be printted
 *  @return status
 */
UINTN
PrintXY (
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_UGA_PIXEL                    *ForeGround,  OPTIONAL
  IN EFI_UGA_PIXEL                    *BackGround,  OPTIONAL
  IN CHAR16                           *Fmt
  )
{
  EFI_HANDLE                          Handle;
  EFI_UGA_DRAW_PROTOCOL               *UgaDraw;
  EFI_SIMPLE_TEXT_OUT_PROTOCOL        *Sto;
  EFI_STATUS                          Status;



  Handle = gtST->ConsoleOutHandle;


  Status = gtBS->HandleProtocol (
                   Handle,
                   &gBlackBoxEfiUgaDrawProtocolGuid,
                   (VOID **) &UgaDraw
                   );

  if (EFI_ERROR (Status)) {
    return Status;
  }


  Status = gtBS->HandleProtocol (
                   Handle,
                   &gBlackBoxEfiSimpleTextOutProtocolGuid,
                   (VOID **) &Sto
                   );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  return _IPrint (UgaDraw, Sto, X, Y, ForeGround, BackGround, Fmt);
}


/**
 *  assistant function to auto judge the user's choice, correct or uncorrect?
 *  @param  Seconds time inteval
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
AutoJudge (
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  )
{
  EFI_STATUS              Status;
  EFI_EVENT               WaitList[2];
  UINTN                   NoWait, WaitIndex;
  EFI_INPUT_KEY           Key;
  BOOLEAN                 PressYes;


  //
  // Set 1 second periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);


  //
  // Set up a wait list for a key and the timer
  //
  NoWait = 0;
  WaitList[NoWait++] = TimerEvent;
  WaitList[NoWait++] = gtST->ConIn->WaitForKey;


  PressYes = Default;
  //
  // Wait for either
  //
  SctPrint (Message);
  while (NoWait) {
    if (Default == TRUE) {
      SctPrint (L"\rYes/No?(Auto judge as Yes in %d seconds", Seconds);
    } else {
      SctPrint (L"\rYes/No?(Auto judge as No in %d seconds", Seconds);
    }

    Status = gtBS->WaitForEvent (NoWait, WaitList, &WaitIndex);

    switch (WaitIndex) {
      case 0:
        Seconds -= 1;
        if (Seconds <= 0) {
          //
          // To stop loop
          //
          NoWait = 0;
        }
        break;

      case 1:
        //
        // Read the key
        //
        Status = gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
        SctAPrint ((char *)(&Key.UnicodeChar));
        switch (Key.UnicodeChar) {
          case 'Y':
          case 'y':
            NoWait = 0;
            PressYes = TRUE;
            break;
          case 'N':
          case 'n':
            NoWait = 0;
            PressYes = FALSE;
            break;
          default :
            SctPrint (L"\n");
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
  SctPrint (L"\r\n");

  //
  // Done, cancle periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);

  return PressYes;
}

/**
 *  assistant function to auto judge the user's choice, correct or uncorrect?(in Uga mode)
 *  @param  Seconds time inteval
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
AutoJudgeUga (
  IN  UINTN         X,
  IN  UINTN         Y,
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  )
{
  EFI_STATUS              Status;
  EFI_EVENT               WaitList[2];
  UINTN                   NoWait, WaitIndex;
  EFI_INPUT_KEY           Key;
  BOOLEAN                 PressYes;
  CHAR16                  *Msg;


  //
  // Set 1 second periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);


  //
  // Set up a wait list for a key and the timer
  //
  NoWait = 0;
  WaitList[NoWait++] = TimerEvent;
  WaitList[NoWait++] = gtST->ConIn->WaitForKey;


  PressYes = Default;
  //
  // Wait for either
  //
  PrintXY (X, Y, NULL, NULL, Message);
  while (NoWait) {
    if (Default == TRUE) {
      Msg = SctPoolPrint (L"Yes/No?(Auto judge as Yes in %d seconds  ", Seconds);
    } else {
      Msg = SctPoolPrint (L"Yes/No?(Auto judge as No in %d seconds   ", Seconds);
    }

    if (Msg == NULL) {
      return FALSE;
    } else {
      PrintXY(X, Y + 20, NULL, NULL, Msg);
      SctFreePool (Msg);
    }

    Status = gtBS->WaitForEvent (NoWait, WaitList, &WaitIndex);

    switch (WaitIndex) {
      case 0:
        Seconds -= 1;
        if (Seconds <= 0) {
          //
          // To stop loop
          //
          NoWait = 0;
        }
        break;

      case 1:
        //
        // Read the key
        //
        Status = gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
        SctAPrint ((char *)(&Key.UnicodeChar));
        switch (Key.UnicodeChar) {
          case 'Y':
          case 'y':
            NoWait = 0;
            PressYes = TRUE;
            break;
          case 'N':
          case 'n':
            NoWait = 0;
            PressYes = FALSE;
            break;
          default :
            //PrintXY(X, YL"\n");
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
  //SctPrint (L"\r\n");

  //
  // Done, cancle periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);

  return PressYes;
}

/**
 *  Assistant function for load a bmp file
 *  @param BltBuffer buffer for bmp file
 *  @param Width/Height of the bmp file
 */
EFI_STATUS
LoadBmp (
  IN EFI_UGA_PIXEL  **BltBuffer,
  IN UINTN           *Width,
  IN UINTN           *Height
  )
{

  EFI_UGA_PIXEL             *Blt;
  EFI_STATUS                 Status;
  UINTN                     IndexX;
  UINTN                     IndexY;
  UINTN                     m;
  UINTN                     Wx, Hy;

//  LoadBmp(&BltBuffer, &Width, &Height);

  Wx = 150;
  Hy = 150;

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Wx * Hy * sizeof (EFI_UGA_PIXEL),
                   (VOID **)&Blt
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  SctZeroMem (Blt, Wx * Hy * sizeof (EFI_UGA_PIXEL));

  for (IndexY =0 ; IndexY < Hy / 3; IndexY++) {
    for (IndexX = 0; IndexX < Wx; IndexX++) {
      m = IndexY * Wx + IndexX;

      Blt[m].Blue  = 0xFF;
      Blt[m].Green = 0x00;
      Blt[m].Red = 0x00;
      Blt[m].Reserved = 0x00;
    }
  }
  for (IndexY = Hy / 3; IndexY < (Hy / 3) * 2; IndexY++) {
    for (IndexX = 0; IndexX < Wx; IndexX++) {
      m = IndexY * Wx + IndexX;

      Blt[m].Blue  = 0x00;
      Blt[m].Green = 0xFF;
      Blt[m].Red = 0x00;
      Blt[m].Reserved = 0x00;
    }
  }
  for (IndexY = (Hy / 3) * 2; IndexY < Hy; IndexY++) {
    for (IndexX = 0; IndexX < Wx; IndexX++) {
      m = IndexY * Wx + IndexX;

      Blt[m].Blue  = 0x00;
      Blt[m].Green = 0x00;
      Blt[m].Red = 0xFF;
      Blt[m].Reserved = 0x00;
    }
  }
  *BltBuffer = Blt;
  *Width = Wx;
  *Height = Hy;
  return EFI_SUCCESS;
}

/**
 *  Return the graphics image file named FileNameGuid into Image and return it's
 *  size in ImageSize. All Firmware Volumes (FV) in the system are searched for the file name.
 *  @param  FileNameGuid  - File Name of graphics file in the FV(s).
 *  @param  Image         - Pointer to pointer to return graphics image.  If NULL, a buffer will be allocated.
 *  @param  ImageSize     - Size of the graphics Image in bytes. Zero if no image found.
 *  @return EFI_SUCCESS          - Image and ImageSize are valid.
 *  @return EFI_BUFFER_TOO_SMALL - Image not big enough. ImageSize has required size
 *  @return EFI_NOT_FOUND        - FileNameGuid not found
*/
EFI_STATUS
GetGraphicsBitMapFromFV (
  IN  EFI_GUID      *FileNameGuid,
  OUT VOID          **Image,
  OUT UINTN         *ImageSize
  )
{
  EFI_STATUS                    Status, ReturnStatus;
  UINTN                         FvProtocolCount;
  EFI_HANDLE                    *FvHandles;
  EFI_FIRMWARE_VOLUME_PROTOCOL  *Fv;
  UINTN                         Index;
  UINT32                        AuthenticationStatus;


  ReturnStatus = EFI_NOT_FOUND;

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiFirmwareVolumeProtocolGuid,
                   NULL,
                   &FvProtocolCount,
                   &FvHandles
                   );
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index < FvProtocolCount; Index++) {
    Status = gtBS->HandleProtocol (
                     FvHandles[Index],
                     &gBlackBoxEfiFirmwareVolumeProtocolGuid,
                     (VOID **)&Fv
                     );

    //
    // Assuming Image and ImageSize are correct on input.
    //
    Status = Fv->ReadSection (
                   Fv,
                   &gBlackBoxEfiDefaultBmpLogoGuid,
                   EFI_SECTION_RAW,
                   0,
                   Image,
                   ImageSize,
                   &AuthenticationStatus
                   );

    if (!EFI_ERROR (Status)) {
      ReturnStatus = EFI_SUCCESS;
      goto FreeHandle;
    } else if (Status == EFI_BUFFER_TOO_SMALL) {
      //
      // ImageSize updated to needed size so return
      //
      ReturnStatus = Status;
      goto FreeHandle;
    }
  }

FreeHandle:
  if (FvHandles != NULL) {
    gtBS->FreePool (FvHandles);
  }

  return ReturnStatus;
}

/**
 *  Convert a *.BMP graphics image to a UGA blt buffer. If a NULL UgaBlt buffer
 *  is passed in a UgaBlt buffer will be allocated by this routine. If a UgaBlt
 *  buffer is passed in it will be used if it is big enough.
 *  @param BmpImage      - Pointer to BMP file
 *  @param BmpImageSize  - Number of bytes in BmpImage
 *  @param UgaBlt        - Buffer containing UGA version of BmpImage.
 *  @param UgaBltSize    - Size of UgaBlt in bytes.
 *  @param PixelHeight   - Height of UgaBlt/BmpImage in pixels
 *  @param PixelWidth    - Width of UgaBlt/BmpImage in pixels
 *  @return EFI_SUCCESS           - UgaBlt and UgaBltSize are returned.
 *  @return EFI_UNSUPPORTED       - BmpImage is not a valid *.BMP image
 *  @return EFI_BUFFER_TOO_SMALL  - The passed in UgaBlt buffer is not big enough.UgaBltSize will contain the required size.
*/
EFI_STATUS
ConvertBmpToUgaBlt (
  IN  VOID      *BmpImage,
  IN  UINTN     BmpImageSize,
  IN OUT VOID   **UgaBlt,
  IN OUT UINTN  *UgaBltSize,
  OUT UINTN     *PixelHeight,
  OUT UINTN     *PixelWidth
  )
{
  EFI_STATUS              Status;
  UINT8                   *Image;
  BMP_IMAGE_HEADER        *BmpHeader;
  BMP_COLOR_MAP           *BmpColorMap;
  EFI_UGA_PIXEL           *BltBuffer, *Blt;
  UINTN                   BltBufferSize, Index;
  UINTN                   Height, Width;
  UINTN                   ImageIndex;


  BmpHeader = (BMP_IMAGE_HEADER *)BmpImage;
  if (BmpHeader->CharB != 'B' || BmpHeader->CharM != 'M') {
    return EFI_UNSUPPORTED;
  }

  if (BmpHeader->CompressionType != 0) {
    return EFI_UNSUPPORTED;
  }

  //
  // Calculate Color Map offset in the image.
  //
  Image = BmpImage;
  BmpColorMap = (BMP_COLOR_MAP *)(Image + sizeof (BMP_IMAGE_HEADER));

  //
  // Calculate graphics image data address in the image
  //
  Image = ((UINT8 *)BmpImage) + BmpHeader->ImageOffset;

  BltBufferSize = BmpHeader->PixelWidth * BmpHeader->PixelHeight * sizeof (EFI_UGA_PIXEL);
  if (*UgaBlt == NULL) {
    *UgaBltSize = BltBufferSize;
    Status = gtBS->AllocatePool (EfiBootServicesData, *UgaBltSize, (VOID **)UgaBlt);
    if (EFI_ERROR (Status)) {
      return EFI_OUT_OF_RESOURCES;
    }
  } else {
    if (*UgaBltSize < BltBufferSize) {
      *UgaBltSize = BltBufferSize;
      return EFI_BUFFER_TOO_SMALL;
    }
  }

  *PixelWidth = BmpHeader->PixelWidth;
  *PixelHeight = BmpHeader->PixelHeight;


  //
  // Convert image from BMP to Blt buffer format
  //
  BltBuffer = *UgaBlt;
  for (Height = 0; Height < BmpHeader->PixelHeight; Height++) {
    Blt = &BltBuffer[(BmpHeader->PixelHeight - Height - 1) * BmpHeader->PixelWidth];
    for (Width = 0; Width < BmpHeader->PixelWidth; Width++, Image++, Blt++) {
      switch (BmpHeader->BitPerPixel) {
      case 4:
        //
        // Convert BMP Palette to 24-bit color
        //
        Index = (* Image) >> 4;
        Blt->Red   = BmpColorMap[Index].Red;
        Blt->Green = BmpColorMap[Index].Green;
        Blt->Blue  = BmpColorMap[Index].Blue;
        if (Width < (BmpHeader->PixelWidth - 1)) {
          Blt++;
          Width++;
          Index = (* Image) & 0x0f;
          Blt->Red   = BmpColorMap[Index].Red;
          Blt->Green = BmpColorMap[Index].Green;
          Blt->Blue  = BmpColorMap[Index].Blue;
        }
        break;
      case 8:
        //
        // Convert BMP Palette to 24-bit color
        //
        Blt->Red   = BmpColorMap[*Image].Red;
        Blt->Green = BmpColorMap[*Image].Green;
        Blt->Blue  = BmpColorMap[*Image].Blue;
      break;
      case 24:
        Blt->Blue = *Image++;
        Blt->Green = *Image++;
        Blt->Red = *Image;
        break;
      default:
        return EFI_UNSUPPORTED;
        break;
      };

    }

    ImageIndex = (UINTN)(Image - BmpHeader->ImageOffset);
    if ((ImageIndex % 4) != 0) {
      //
      // Bmp Image starts each row on a 32-bit boundary!
      //
      Image = Image + (4 - (ImageIndex % 4));
    }
  }

  return EFI_SUCCESS;
}

/**
 *  Clear the whole screen
 *  @param UgaDraw      - UgaDraw protocol interface
 *  @param HorizontalResolution/VerticalResolution  - Resolution of the screen
 *  @return Status
*/
EFI_STATUS
UgaDrawClearScreen (
  IN  EFI_UGA_DRAW_PROTOCOL      *UgaDraw,
  IN  UINT32                     HorizontalResolution,
  IN  UINT32                     VerticalResolution
  )
{
  EFI_UGA_PIXEL  blt;
  blt.Blue  = 0;
  blt.Red   = 0;
  blt.Green = 0;
  return UgaDraw->Blt (
                    UgaDraw,
                    &blt,
                    EfiUgaVideoFill,
                    0,
                    0,
                    0,
                    0,
                    HorizontalResolution,
                    VerticalResolution,
                    0
                    );
}

/**
 *  Assistant fucntion for prepare test data
 *  @param Index      - Index of the current test count
 *  @param ..         - test data to be returned
*/
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
  IN  UINT32       HorizontalResolution,
  IN  UINT32       VerticalResolution
  )
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
      *SourceX = 0;
      *SourceY = 0;
      break;
    case 1:
      *SourceX = 100;
      *SourceY = 100;
      break;
    case 2:
      *SourceX = HorizontalResolution / 2;
      *SourceY = VerticalResolution / 2;
      break;
    default:
      *SourceX = HorizontalResolution + 1;
      *SourceY = VerticalResolution + 1;
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
    case 0:
      *Delta = 0;
      break;
    case 1:
      *Delta = 100 * sizeof (EFI_UGA_PIXEL);
      break;
    case 2:
      *Delta = (*Width / 2) * sizeof (EFI_UGA_PIXEL);
      break;
    case 3:
      *Delta = *Width * sizeof (EFI_UGA_PIXEL);
      break;
    default:
      *Delta = (*Width + 1) * sizeof (EFI_UGA_PIXEL);
  }
}

/**
 *  Output some picture in some position
 *  @param UgaDraw      - UgaDraw protocol interface
 *  @param SourceX/SourceY  - position of the destination screen
 *  @param DestinationX/DestinationY - No use here
 *  @return Status
*/
EFI_STATUS
OutputScreen (
  IN EFI_UGA_DRAW_PROTOCOL   *UgaDraw,
  IN UINTN                   SourceX,
  IN UINTN                   SourceY,
  IN UINTN                   DestinationX,
  IN UINTN                   DestinationY
  )
{

#ifdef  LOAD_INTEL_LOG
  UINTN                      Width, Height;
  EFI_UGA_PIXEL              *BltBuffer;
  EFI_STATUS                 Status;

  Status = LoadBmp (&BltBuffer, &Width, &Height);
  if EFI_ERROR (Status) {
    return Status;
  }
  Status = UgaDraw->Blt (
                      UgaDraw,
                      BltBuffer,
                      EfiUgaBltBufferToVideo,
                      0,
                      0,
                      SourceX,
                      SourceY,
                      Width,
                      Height,
                      Width * sizeof (EFI_UGA_PIXEL)
                      );
    if (BltBuffer != NULL) {
      gtBS->FreePool (BltBuffer);
    }
    return Status;

#else

  UINTN                      Index;

  for (Index = 0; Index < 5; Index++); {
    UgaPrintXY (UgaDraw, SourceX + Index * 5, SourceY + Index * 5, NULL, NULL, L"This is for test!");
  }
  return EFI_SUCCESS;
#endif
}

/**
 *  assistant function to locate DevicePath Protocol from UgaDraw Protocol
 *  @param  UgaDraw protocol interface
 *  @param  DevicePath protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateDevicePathFromUgaDraw (
  IN EFI_UGA_DRAW_PROTOCOL                *UgaDraw,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                   NoHandles, Index;
  EFI_HANDLE                              *HandleBuffer;
  EFI_UGA_DRAW_PROTOCOL                   *OtherUgaDraw;

  //
  // Locate the Handle that the UgaDraw interface is bound to
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiUgaDrawProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
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

  if (NoHandles <= 0 ||HandleBuffer == NULL) {
    StandardLib->RecordAssertion (
                   StandardLib,
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
  // Find the exact handle that UgaDraw bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[Index],
                       &gBlackBoxEfiUgaDrawProtocolGuid,
                       (VOID **) &OtherUgaDraw
                       );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
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
    if (OtherUgaDraw == UgaDraw) {
      break;
    }
  }

  //
  // Locate the DevicePath Protocol bound to UgaDraw Protocol
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
                   (VOID **) DevicePath
                   );

   gtBS->FreePool (HandleBuffer);

   return Status;
}
