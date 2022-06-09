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

  SimpleTextOutBBTestMain_uefi.c

Abstract:

  Test Driver of Simple Text Output Protocol

--*/


#include "SimpleTextOutBBTestMain_uefi.h"

EFI_EVENT              TimerEvent;

CHAR16                 *mAttribStr[] = { L"BLACK", L"BLUE", L"GREEN", L"CYAN", L"RED", L"MAGENTA", L"BROWN", L"LIGHT GRAY", L"DARK GRAY",
                                         L"LIGHT BLUE", L"LIGHT GREEN", L"LIGHT GYAN", L"LIGHT RED", L"LIGHT MAGENTA", L"YELLOW", L"WHITE"};

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SIMPLE_TEXT_OUTPUT_PROTOCOL_TEST_REVISION,
  EFI_SIMPLE_TEXT_OUT_PROTOCOL_GUID,
  L"Simple Text Output Protocol Test",
  L"UEFI2.0 Simple Text Output Protocol Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_RESET_FUNCTION_AUTO_GUID,
    L"Reset_Func",
    L"Automatically Test the functionality of Reset",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestResetFunctionAutoTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_OUTPUTSTRING_FUNCTION_AUTO_GUID,
    L"OutputString_Func",
    L"Auto Test the functionality of OutputString",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestOutputStringFunctionAutoTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_TESTSTRING_FUNCTION_AUTO_GUID,
    L"TestString_Func",
    L"Automatically Test the functionality of TestString",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestTestStringFunctionAutoTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_QUERYMODE_FUNCTION_AUTO_GUID,
    L"QueryMode_Func",
    L"Automatically Test the functionality of QueryMode",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestQueryModeFunctionAutoTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_SETMODE_FUNCTION_AUTO_GUID,
    L"SetMode_Func",
    L"Auto Test the functionality of SetMode",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetModeFunctionAutoTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_SETATTRIBUTE_FUNCTION_AUTO_GUID,
    L"SetAttribute_Func",
    L"Auto Test the functionality of SetAttribute",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetAttributeFunctionAutoTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_CLEARSCREEN_FUNCTION_AUTO_GUID,
    L"ClearScreen_Func",
    L"Auto Test the functionality of ClearScreen",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestClearScreenFunctionAutoTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_ENABLECURSOR_FUNCTION_AUTO_GUID,
    L"EnableCursor_Func",
    L"Auto Test the functionality of EnableCursor",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestEnableCursorFunctionAutoTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_SETCURSORPOSITION_FUNCTION_AUTO_GUID,
    L"SetCursorPosition_Func",
    L"Auto Test the functionality of SetCursorPosition",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetCursorPositionFunctionAutoTest
  },

  //
  // Conformance test function data structure
  //
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_QUERYMODE_CONFORMANCE_AUTO_GUID,
    L"QueryMode_Conf",
    L"Auto Conformance Test of QueryMode",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestQueryModeConformanceAutoTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_SETMODE_CONFORMANCE_AUTO_GUID,
    L"SetMode_Conf",
    L"Auto Conformance Test of SetMode",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetModeConformanceAutoTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_SETCURSORPOSITION_CONFORMANCE_AUTO_GUID,
    L"SetCursorPosition_Conf",
    L"Auto Conformance Test of SetCursorPosition",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetCursorPositionConformanceAutoTest
  },
/*  
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_SETATTRIBUTE_CONFORMANCE_AUTO_GUID,
    L"SetAttribute_Conf",
    L"Auto Conformance Test of SetAttribute",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetAttributeConformanceAutoTest
  },
*/
#ifdef EFI_TEST_EXHAUSTIVE
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_RESET_FUNCTION_MANUAL_GUID,
    L"Reset_Func_Manual",
    L"Manually Test the functionality of Reset",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    BBTestResetFunctionManualTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_OUTPUTSTRING_FUNCTION_MANUAL_GUID,
    L"OutputString_Func_Manual",
    L"Manually Test the functionality of OutputString",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    BBTestOutputStringFunctionManualTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_SETMODE_FUNCTION_MANUAL_GUID,
    L"SetMode_Func_Manual",
    L"Manually Test the functionality of SetMode",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    BBTestSetModeFunctionManualTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_SETATTRIBUTE_FUNCTION_MANUAL_GUID,
    L"SetAttribute_Func_Manual",
    L"Manually Test the functionality of SetAttribute",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    BBTestSetAttributeFunctionManualTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_CLEARSCREEN_FUNCTION_MANUAL_GUID,
    L"ClearScreen_Func_Manual",
    L"Manually Test the functionality of ClearScreen",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    BBTestClearScreenFunctionManualTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_SETCURSORPOSITION_FUNCTION_MANUAL_GUID,
    L"SetCursorPosition_Func_Manual",
    L"Manually Test the functionality of SetCursorPosition",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    BBTestSetCursorPositionFunctionManualTest
  },
  {
    SIMPLE_TEXT_OUTPUT_PROTOCOL_ENABLECURSOR_FUNCTION_MANUAL_GUID,
    L"EnableCursor_Func_Manual",
    L"Manually Test the functionality of EnableCursor",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_MANUAL,
    BBTestEnableCursorFunctionManualTest
  },
#endif

  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestSimpleTextOutputProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Simple Text Output Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestSimpleTextOutput (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  gtBS->CreateEvent (EVT_TIMER, 0, (EFI_EVENT_NOTIFY) NULL, NULL, &TimerEvent);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestSimpleTextOutputProtocolUnload,
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
BBTestSimpleTextOutputProtocolUnload (
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
  while (Source!=NULL && (*Source)!=0 && Index<256) {
    *Destination=*Source;
    Destination++;
    Source++;
  }
  *Destination=0;
}

#if (EFI_SPECIFICATION_VERSION < 0x0002000A)
UINTN
_IPrint (
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL            *GraphicsOutput,
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *Sto,
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL                    *Foreground,
  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL                    *Background,
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
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL                        *LineBuffer;
  UINTN                             HorizontalResolution;
  UINTN                              VerticalResolution;

  GlyphStatus = 0;

  //
  // For now, allocate an arbitrarily long buffer
  //
  Status = gtBS->AllocatePool (EfiBootServicesData,
                              0x10000,
                              (VOID **) &Buffer);

  CopyUnicodeString ((CHAR16*) Buffer, fmt);

  HorizontalResolution  = GraphicsOutput->Mode->Info->HorizontalResolution;
  VerticalResolution    = GraphicsOutput->Mode->Info->VerticalResolution;

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL) * HorizontalResolution * GLYPH_HEIGHT,
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
 Status = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  LineBuffer,
                                  EfiBltBufferToVideo,
                                  0,
                                  0,
                                  X,
                                  Y,
                                  GLYPH_WIDTH * SctStrLen (Buffer),
                                  GLYPH_HEIGHT,
                                  GLYPH_WIDTH * SctStrLen (Buffer) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                  );

Error:
  gtBS->FreePool (LineBuffer);
  gtBS->FreePool (Buffer);
  return Status;
}


UINTN
PrintXY (
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL                    *ForeGround,  OPTIONAL
  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL                    *BackGround,  OPTIONAL
  IN CHAR16                           *Fmt
  )
{
  EFI_HANDLE                          Handle;
  EFI_GRAPHICS_OUTPUT_PROTOCOL        *GraphicsOutput;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL     *Sto;
  EFI_STATUS                          Status;



  Handle = gtST->ConsoleOutHandle;

  Status = gtBS->HandleProtocol (
                   Handle,
                   &gBlackBoxEfiGraphicsOutputProtocolGuid,
                   (VOID **) &GraphicsOutput
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

  return _IPrint (GraphicsOutput, Sto, X, Y, ForeGround, BackGround, Fmt);
}
#endif

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
    if (Default==TRUE) {
      SctPrint (L"\rYes/No?(Auto judge as Yes in %d seconds)", Seconds);
    } else {
      SctPrint (L"\rYes/No?(Auto judge as No in %d seconds)", Seconds);
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
        SctAPrint ((char*)(&Key.UnicodeChar));
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

#if (EFI_SPECIFICATION_VERSION < 0x0002000A)
/**
 *  assistant function to auto judge the user's choice, correct or uncorrect?
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
    if (Default==TRUE) {
      Msg = SctPoolPrint (L"Yes/No?(Auto judge as Yes in %d seconds  ", Seconds);
    } else {
      Msg = SctPoolPrint (L"Yes/No?(Auto judge as No in %d seconds   ", Seconds);
    }

    if (Msg == NULL) {
      return FALSE;
    } else {
      PrintXY(X, Y+20, NULL, NULL, Msg);
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
        SctAPrint ((char*)(&Key.UnicodeChar));
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
            //PrintXY(X,YL"\n");
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
#endif

/**
 *  assistant function to restore the mode of SimpleTextOutput Protocol
 *  @param  SimpleOut destine SimpleTextOutput Protocol
 *  @param  SavedMode EFI_SIMPLE_TEXT_OUTPUT_MODE type
 *  @param  StandardLib EFI Standard Test Library Protocol Interface
 *  @return  EFI Status of the procedure
 */
EFI_STATUS
RestoreMode (
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL      *SimpleOut,
  IN EFI_SIMPLE_TEXT_OUTPUT_MODE          *SavedMode,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS  Status;

  //
  //restore old mode of SimpleOut
  //
  if (SavedMode->Mode != SimpleOut->Mode->Mode) {
    Status = SimpleOut->SetMode (SimpleOut, SavedMode->Mode);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetMode - SetMode to restore.",
                  L"%a:%d, Status = %r,Mode = %d",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status,
                  SavedMode->Mode);
      return Status;
    }
  }

  //
  //restore old attriubte of SimpleOut
  //
  if (SavedMode->Attribute != SimpleOut->Mode->Attribute) {
    Status = SimpleOut->SetAttribute (SimpleOut, SavedMode->Attribute);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetAttribute - SetAttribute to restore.",
                  L"%a:%d, Status = %r,Attribute = %d",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status,
                  SavedMode->Attribute);
      return Status;
    }
  }

  //
  //restore old cursor attriubte of SimpleOut
  //
  if (SavedMode->CursorVisible != SimpleOut->Mode->CursorVisible) {
    Status = SimpleOut->EnableCursor (SimpleOut, SavedMode->CursorVisible);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                  StandardLib,
                  EFI_TEST_ASSERTION_FAILED,
                  gTestGenericFailureGuid,
                  L"EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.EnableCursor - EnableCursor to restore cursor.",
                  L"%a:%d, Status = %r,CursorVisible = %d",
                  __FILE__,
                  (UINTN)__LINE__,
                  Status,
                  SavedMode->CursorVisible);
      return Status;
    }
  }

  //
  //restore mode successfully
  //
  return EFI_SUCCESS;
}

/**
 *  assistant function to backup the mode of SimpleTextOutput Protocol
 *  @param  SimpleOut destine SimpleTextOutput Protocol
 *  @param  SavedMode EFI_SIMPLE_TEXT_OUTPUT_MODE type
 *  @param  StandardLib EFI Standard Test Library Protocol Interface
 *  @return  EFI Status of the procedure
 */
VOID
BackupMode (
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL      *SimpleOut,
  IN EFI_SIMPLE_TEXT_OUTPUT_MODE          *SavedMode
  )
{
  //
  //backup old mode of SimpleOut
  //
  SavedMode->MaxMode            = SimpleOut->Mode->MaxMode;
  SavedMode->Mode               = SimpleOut->Mode->Mode;
  SavedMode->Attribute          = SimpleOut->Mode->Attribute;
  SavedMode->CursorColumn       = SimpleOut->Mode->CursorColumn;
  SavedMode->CursorRow          = SimpleOut->Mode->CursorRow;
  SavedMode->CursorVisible      = SimpleOut->Mode->CursorVisible;
}

/**
 *  assistant function to locate DevicePath Protocol from SimpleTextOut Protocol
 *  @param  SimpleTextOut protocol interface
 *  @param  DevicePath protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateDevicePathFromSimpleTextOut (
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL      *SimpleOut,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                   NoHandles, Index;
  EFI_HANDLE                              *HandleBuffer;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL         *OtherSimpleOut;

  //
  // Locate the Handle that the SimpleTextOutput interface is bound to
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiSimpleTextOutProtocolGuid,
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

  if (NoHandles <= 0 || HandleBuffer == NULL) {
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
  // Find the exact handle that SimpleTextOutput bound to
  //
  for (Index=0; Index<NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiSimpleTextOutProtocolGuid,
                     (VOID **) &OtherSimpleOut
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

    if (OtherSimpleOut == SimpleOut) {
      break;
    }
  }

  //
  // Locate the DevicePath Protocol bound to SimpleOut Protocol
  //
  if (Index>=NoHandles) {
    //
    // No Handle Found!!
    //
    gtBS->FreePool (HandleBuffer);
    return EFI_DEVICE_ERROR;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[Index],
                   &gBlackBoxEfiDevicePathProtocolGuid,
                   (VOID **) DevicePath
                   );


  gtBS->FreePool (HandleBuffer);

  return Status;
}

/**
 *  assistant function to locate GraphicsOutput Protocol from SimpleTextOut Protocol
 *  @param  SimpleTextOut protocol interface
 *  @param  Graphics Output protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateGopFromSimpleTextOut (
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL      *SimpleOut,
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL           **GraphicsOutput,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                   NoHandles, Index;
  EFI_HANDLE                              *HandleBuffer;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL         *OtherSimpleOut;

  //
  // Locate the Handle that the SimpleTextOutput interface is bound to
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiSimpleTextOutProtocolGuid,
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

  if (NoHandles <= 0 || HandleBuffer == NULL) {
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
  // Find the exact handle that SimpleTextOutput bound to
  //
  for (Index=0; Index<NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiSimpleTextOutProtocolGuid,
                     (VOID **) &OtherSimpleOut
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
    if (OtherSimpleOut == SimpleOut) {
      break;
    }
  }

  //
  // Locate the Graphics Output Protocol bound to SimpleOut Protocol
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
                   &gBlackBoxEfiGraphicsOutputProtocolGuid,
                   (VOID **) GraphicsOutput
                   );

  gtBS->FreePool (HandleBuffer);
  return Status;
}

BOOLEAN
CheckModeIntegrity (
  IN EFI_SIMPLE_TEXT_OUTPUT_MODE          *ModeExpected,
  IN EFI_SIMPLE_TEXT_OUTPUT_MODE          *Mode
  )
{
  if (Mode->Mode!=ModeExpected->Mode) {
    return FALSE;
  }

  if (Mode->MaxMode!=ModeExpected->MaxMode) {
    return FALSE;
  }

  if (Mode->Attribute!=ModeExpected->Attribute) {
    return FALSE;
  }

  if (Mode->CursorColumn!=ModeExpected->CursorColumn) {
    return FALSE;
  }

  if (Mode->CursorRow!=ModeExpected->CursorRow) {
    return FALSE;
  }

  if (Mode->CursorVisible!=ModeExpected->CursorVisible) {
    return FALSE;
  }

  return TRUE;
}

/**
 *  assistant function to wait a key press or timeout?
 *  @param  Seconds time inteval
*/
void
WaitTimeOrKey (
  IN  UINTN       Seconds
  )
{
  EFI_STATUS              Status;
  EFI_EVENT               WaitList[2];
  UINTN                   NoWait, WaitIndex;
  EFI_INPUT_KEY           Key;

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

  //
  // Wait for either
  //

  while (NoWait)   {
    SctPrint (L"\rAuto begin in %d seconds or Press Enter to start ", Seconds);
    Status = gtBS->WaitForEvent (NoWait, WaitList, &WaitIndex);

    switch (WaitIndex) {
      case 0:
        Seconds -= 1;
        if (Seconds <= 0) {
          NoWait = 0;     // stop loop
        }
        break;
      case 1:             // Read the key
        Status = gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
        if (Key.UnicodeChar == 0xD) {
          NoWait = 0;     // stop loop
        }
        break;
      default:            // bad WaitIndex response
        break;
   }
  }


  //
  // Done, cancle periodic timer
  //

  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
}
