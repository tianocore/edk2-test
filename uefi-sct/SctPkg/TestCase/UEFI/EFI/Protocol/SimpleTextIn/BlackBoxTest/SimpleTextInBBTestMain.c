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

  SimpleTextInBBTestMain.c

Abstract:

  Test Driver of Simple Input Protocol

--*/

#include "SimpleTextInBBTestMain.h"

EFI_EVENT              TimerEvent;
//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SIMPLE_TEXT_IN_PROTOCOL_TEST_REVISION,
  EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID,
  L"Simple Input Protocol Test",
  L"UEFI Simple Input Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  //
  // Interface test
  //
  {
    SIMPLE_TEXT_IN_PROTOCOL_RESET_FUNCTION_AUTO_GUID,
    L"Reset_Func",
    L"Perform auto function checkes on the Reset interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetFunctionAutoTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    SIMPLE_TEXT_IN_PROTOCOL_READKEYSTROKE_CONFORMANCE_MANUAL_GUID,
    L"ReadKeyStroke_Conf_Manaul",
    L"Perform Manual conformance checkes on the ReadKeyStroke interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestReadKeyStrokeConformanceManualTest
  },

  {
    SIMPLE_TEXT_IN_PROTOCOL_WAITFORKEY_CONFORMANCE_MANUAL_GUID,
    L"WaitForKey_Conf_Manaul",
    L"Perform Manual conformance checkes on the ReadKeyStroke interface",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestWaitForKeyConformanceManualTest
  },

  {
    SIMPLE_TEXT_IN_PROTOCOL_RESET_FUNCTION_MANUAL_GUID,
    L"Reset_Func_Manual",
    L"Perform manual function checkes on the Reset interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestResetFunctionManualTest
  },

  {
    SIMPLE_TEXT_IN_PROTOCOL_READKEYSTROKE_FUNCTION_MANUAL_GUID,
    L"ReadKeyStroke_Func_Manual",
    L"Perform Manual function checkes on the ReadKeyStroke interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestReadKeyStrokeFunctionManualTest
  },

  {
    SIMPLE_TEXT_IN_PROTOCOL_WAITFORKEY_FUNCTION_MANUAL_GUID,
    L"WaitForKey_Func_Manual",
    L"Perform Manual function checkes on the WaitForKey interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestWaitForKeyFunctionManualTest
  },

  //
  // Extensive Test
  //
  {
    SIMPLE_TEXT_IN_PROTOCOL_READWAIT_EXTENSIVE_MANUAL_GUID,
    L"ReadKeyStroke&WaitForKey_Stress_Manual",
    L"Perform manual function checkes on the ReadKeyStroke&WaitForKey interface",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestReadKeyStrokeManualTest
  },
#endif

  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestSimpleTextInProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Simple Input Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestSimpleTextIn (
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
              BBTestSimpleTextInProtocolUnload,
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
BBTestSimpleTextInProtocolUnload (
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
 *  assistant function to locate DevicePath Protocol from SimpleTextIn Protocol
 *  @param  SimpleTextIn protocol interface
 *  @param  DevicePath protocol interface
 *  @param  StandardLib protocol interface for record assertion point
 *  @return Status
*/
EFI_STATUS
LocateDevicePathFromSimpleTextIn (
  IN EFI_SIMPLE_TEXT_IN_PROTOCOL          *SimpleIn,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                   NoHandles, Index;
  EFI_HANDLE                              *HandleBuffer;
  EFI_SIMPLE_TEXT_IN_PROTOCOL             *OtherSimpleIn;

  //
  // Locate the Handle that the SimpleTextOutIn interface is bound to
  //
  Status = gtBS->LocateHandleBuffer (
                        ByProtocol,
                        &gBlackBoxEfiSimpleTextInProtocolGuid,
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

  if (NoHandles<=0) {
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
  // Find the exact handle that SimpleTextIn bound to
  //
  for (Index=0;Index<NoHandles;Index++) {
      Status = gtBS->HandleProtocol (
                        HandleBuffer[Index],
                        &gBlackBoxEfiSimpleTextInProtocolGuid,
                        (VOID **) &OtherSimpleIn
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

    if (OtherSimpleIn == SimpleIn) {
      break;
    }
  }

  //
  // Locate the DevicePath Protocol bound to SimpleIn Protocol
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

/**
 *  assistant function to wait a key press or timeout?
 *  @param  Seconds time inteval
*/
BOOLEAN
WaitTimeOrKeySimpleIn (
  IN  EFI_SIMPLE_TEXT_IN_PROTOCOL  *ConIn,
  IN  UINTN                        Seconds
  )
{
  EFI_STATUS              Status;
  EFI_EVENT               WaitList[2];
  UINTN                   NoWait, WaitIndex;
  BOOLEAN                 KeyPressed = FALSE;


  //
  // Set 1 second periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);

  //
  // Set up a wait list for a key and the timer
  //

  NoWait = 0;
  WaitList[NoWait++] = TimerEvent;
  WaitList[NoWait++] = ConIn->WaitForKey;

  //
  // Wait for either
  //

  while (NoWait)   {
    Status = gtBS->WaitForEvent (NoWait, WaitList, &WaitIndex);

    switch (WaitIndex) {
      case 0:
        Seconds -= 1;
        if (Seconds <= 0) {
          NoWait = 0;     // stop loop
        }
        KeyPressed = FALSE;
        break;
      case 1:
        NoWait=0;
        KeyPressed = TRUE;
        break;
      default:            // bad WaitIndex response
        break;
   }
  }


  //
  // Done, cancle periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);

  return KeyPressed;
}

CHAR16*
ScanCodeDesc (
  IN  UINT16    ScanCode
  )
{
  switch (ScanCode) {
    case SCAN_F1:
      return L"F1";
    case SCAN_F2:
      return L"F2";
    case SCAN_F3:
      return L"F3";
    case SCAN_F4:
      return L"F4";
    case SCAN_F5:
      return L"F5";
    case SCAN_F6:
      return L"F6";
    case SCAN_F7:
      return L"F7";
    case SCAN_F8:
      return L"F8";
    case SCAN_F9:
      return L"F9";
    case SCAN_F10:
      return L"F10";
    case SCAN_INSERT:
      return L"INSERT";
    case SCAN_HOME:
      return L"HOME";
    case SCAN_PAGE_UP:
      return L"PAGE_UP";
    case SCAN_DELETE:
      return L"DELETE";
    case SCAN_END:
      return L"END";
    case SCAN_PAGE_DOWN:
      return L"PAGE_DOWN";
    case SCAN_RIGHT:
      return L"RIGHT";
    case SCAN_LEFT:
      return L"LEFT";
    case SCAN_DOWN:
      return L"DOWN";
    case SCAN_UP:
      return L"UP";
    case SCAN_ESC:
      return L"ESC";
    default:
      return L"UNKNOWN KEY";
  }
}
