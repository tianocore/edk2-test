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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  SimpleTextInputExBBTestMain.c

Abstract:

  Test Driver of Simple Text Input Ex Protocol

--*/

#include "SctLib.h"
#include "SimpleTextInputExBBTestMain.h"


//
// Global variables
//
EFI_EVENT              TimerEvent;

EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  IHV_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_REVISION,
  IHV_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID,
  L"Simple Text Input Ex Protocol Test",
  L"UEFI Simple Text Input Ex Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0101,
    L"ResetFunctionAuto",
    L"Function auto test for Simple Text Input Ex Protocol Reset().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestResetFunctionAutoTest
  },
#ifdef EFI_TEST_EXHAUSTIVE
  {
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0102,
    L"ResetFunctionManual",
    L"Function manual test for Simple Text Input Ex Protocol Reset().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestResetFunctionManualTest
  },
  {
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0103,
    L"ReadKeyStrokeExFunctionManual",
    L"Function manual test for Simple Text Input Ex Protocol ReadKeyStrokeEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestReadKeyStrokeExFunctionManualTest
  },
  {
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0104,
    L"SetStateFunctionManual",
    L"Function Manual test for Simple Text Input Ex Protocol SetState().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetStateFunctionManualTest
  },
  {
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0105,
    L"RegisterKeyNotifyFunctionManual",
    L"Function manual test for Simple Text Input Ex Protocol RegisterKeyNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterKeyNotifyFunctionManualTest
  },
  {
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0106,
    L"UnregisterkeyNotifyFunctionManual",
    L"Function Manual test for Simple Text Input Ex Protocol UnregisterKeyNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterKeyNotifyFunctionManualTest
  },
#endif
  {
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0201,
    L"ReadKeyStrokeExConformance",
    L"Conformance test for Simple Text Input Ex Protocol ReadKeyStrokeEx().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestReadKeyStrokeExConformanceTest
  },
  {
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0202,
    L"SetStateConformance",
    L"Conformance test for Simple Text Input Ex Protocol SetState().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestSetStateConformanceTest
  },
  {
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0203,
    L"RegisterKeyNotifyConformance",
    L"Conformance test for Simple Text Input Ex Protocol RegisterKeyNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRegisterKeyNotifyConformanceTest
  },
  {
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_TEST_ENTRY_GUID0204,
    L"UnregisterKeyNotifyConformance",
    L"Conformance test for Simple Text Input Ex Protocol UnregisterKeyNotify().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnregisterKeyNotifyConformanceTest
  },
  0
};

BOOLEAN     BeenExecuted;

//
//
//

EFI_STATUS
InitializeSimpleTextInputExBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //

  SctInitializeLib (ImageHandle, SystemTable);
  gtBS->CreateEvent (EVT_TIMER, 0, NULL, NULL, &TimerEvent);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallIHVBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           UnloadSimpleTextInputExBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
UnloadSimpleTextInputExBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeIHVBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

//
// Guid for messaging path, used in Serial port setting.
//
EFI_GUID            Guid[4] = {
  DEVICE_PATH_MESSAGING_PC_ANSI,
  DEVICE_PATH_MESSAGING_VT_100,
  DEVICE_PATH_MESSAGING_VT_100_PLUS,
  DEVICE_PATH_MESSAGING_VT_UTF8
};


BOOLEAN
WaitTimeOrKey (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *SimpleTextInputEx,
  IN  UINTN                              Seconds
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
  WaitList[NoWait++] = SimpleTextInputEx->WaitForKeyEx;

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


BOOLEAN
AutoJudge (
  IN  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL  *SimpleTextInputEx,
  IN  UINTN                              Seconds,
  IN  BOOLEAN                            Default,
  IN  CHAR16                             *Message
  )
{
  EFI_STATUS              Status;
  EFI_EVENT               WaitList[2];
  UINTN                   NoWait, WaitIndex;
  EFI_KEY_DATA            Key;
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
  WaitList[NoWait++] = SimpleTextInputEx->WaitForKeyEx;


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
        Status = SimpleTextInputEx->ReadKeyStrokeEx (SimpleTextInputEx, &Key);
        SctAPrint ((char*)(&Key.Key.UnicodeChar));
        switch (Key.Key.UnicodeChar) {
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


CHAR16*
ScanCodeDesc (
  IN  UINT16    ScanCode
  )
{
  switch (ScanCode) {
    case TEST_SCAN_F1:
      return L"F1";
    case TEST_SCAN_F2:
      return L"F2";
    case TEST_SCAN_F3:
      return L"F3";
    case TEST_SCAN_F4:
      return L"F4";
    case TEST_SCAN_F5:
      return L"F5";
    case TEST_SCAN_F6:
      return L"F6";
    case TEST_SCAN_F7:
      return L"F7";
    case TEST_SCAN_F8:
      return L"F8";
    case TEST_SCAN_F9:
      return L"F9";
    case TEST_SCAN_F10:
      return L"F10";
    case TEST_SCAN_F11:
      return L"F11";
    case TEST_SCAN_F12:
      return L"F12";
    case TEST_SCAN_F13:
      return L"F13";
    case TEST_SCAN_F14:
      return L"F14";
    case TEST_SCAN_F15:
      return L"F15";
    case TEST_SCAN_F16:
      return L"F16";
    case TEST_SCAN_F17:
      return L"F17";
    case TEST_SCAN_F18:
      return L"F18";
    case TEST_SCAN_F19:
      return L"F19";
    case TEST_SCAN_F20:
      return L"F20";
    case TEST_SCAN_F21:
      return L"F21";
    case TEST_SCAN_F22:
      return L"F22";
    case TEST_SCAN_F23:
      return L"F23";
    case TEST_SCAN_F24:
      return L"F24";
    case TEST_SCAN_INSERT:
      return L"INSERT";
    case TEST_SCAN_HOME:
      return L"HOME";
    case TEST_SCAN_PAGE_UP:
      return L"PAGE_UP";
    case TEST_SCAN_DELETE:
      return L"DELETE";
    case TEST_SCAN_END:
      return L"END";
    case TEST_SCAN_PAGE_DOWN:
      return L"PAGE_DOWN";
    case TEST_SCAN_RIGHT:
      return L"RIGHT";
    case TEST_SCAN_LEFT:
      return L"LEFT";
    case TEST_SCAN_DOWN:
      return L"DOWN";
    case TEST_SCAN_UP:
      return L"UP";
    case TEST_SCAN_ESC:
      return L"ESC";
    case TEST_SCAN_MUTE:
      return L"MUTE";
    case TEST_SCAN_VOLUME_UP:
      return L"VOLUME_UP";
    case TEST_SCAN_VOLUME_DOWN:
      return L"VOLUME_DOWN";
    case TEST_SCAN_BRIGHTNESS_UP:
      return L"BRIGHTNESS_UP";
    case TEST_SCAN_BRIGHTNESS_DOWN:
      return L"BRIGHTNESS_DOWN";
    case TEST_SCAN_SUSPEND:
      return L"SUSPEND";
    case TEST_SCAN_HIBERNATE:
      return L"HIBERNATE";
    case TEST_SCAN_TOGGLE_DISPLAY:
      return L"TOGGLE_DISPLAY";
    case TEST_SCAN_RECOVERY:
      return L"RECOVERY";
    case TEST_SCAN_EJECT:
      return L"EJECT";
    default:
      return L"UNKNOWN KEY";
  }
}

EFI_STATUS
KeyStatePrint (
  IN EFI_KEY_STATE KeyState
)
{
  SctPrint( L"\r\nKeyShiftState is: %x", KeyState.KeyShiftState );
  SctPrint( L"\r\nKeyToggleState is: %x\r\n", KeyState.KeyToggleState );
  
  if ( KeyState.KeyShiftState & EFI_RIGHT_SHIFT_PRESSED )
    SctPrint( L"RIGHT_SHIFT_PRESSED  " );
  if ( KeyState.KeyShiftState & EFI_LEFT_SHIFT_PRESSED )
    SctPrint( L"LEFT_SHIFT_PRESSED  " );
  if ( KeyState.KeyShiftState & EFI_RIGHT_CONTROL_PRESSED )
    SctPrint( L"RIGHT_CONTROL_PRESSED  " );
  if ( KeyState.KeyShiftState & EFI_LEFT_CONTROL_PRESSED )
    SctPrint( L"LEFT_CONTROL_PRESSED  " );
  if ( KeyState.KeyShiftState & EFI_RIGHT_ALT_PRESSED )
    SctPrint( L"RIGHT_ALT_PRESSED  " );
  if ( KeyState.KeyShiftState & EFI_LEFT_ALT_PRESSED )
    SctPrint( L"LEFT_ALT_PRESSED  " );
  if ( KeyState.KeyShiftState & EFI_RIGHT_LOGO_PRESSED )
    SctPrint( L"RIGHT_LOGO_PRESSED  " );
  if ( KeyState.KeyShiftState & EFI_LEFT_LOGO_PRESSED )
    SctPrint( L"LEFT_LOGO_PRESSED  " );
  if ( KeyState.KeyShiftState & EFI_MENU_KEY_PRESSED )
    SctPrint( L"MENU_KEY_PRESSED  " );
  if ( KeyState.KeyShiftState & EFI_SYS_REQ_PRESSED )
    SctPrint( L"EFI_SYS_REQ_PRESSED  " );

  if ( KeyState.KeyToggleState & EFI_SCROLL_LOCK_ACTIVE )
    SctPrint( L"SCROLL_LOCK_ACTIVE  " );
  if ( KeyState.KeyToggleState & EFI_NUM_LOCK_ACTIVE )
    SctPrint( L"NUM_LOCK_ACTIVE  " );
  if ( KeyState.KeyToggleState & EFI_CAPS_LOCK_ACTIVE )
    SctPrint( L"CAPS_LOCK_ACTIVE  " );

  return EFI_SUCCESS;
}



EFI_STATUS
TestRegisterNotifyFunction (
  IN EFI_KEY_DATA *KeyData
)
{
    return EFI_SUCCESS;
}


EFI_STATUS
FunctionTestNotifyFunction (
  IN EFI_KEY_DATA *KeyData
)
{
    BeenExecuted = TRUE;
    return EFI_SUCCESS;
}


EFI_STATUS
LocateDevicePathFromSimpleTextInputEx (
  IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *SimpleTextInputEx,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                   NoHandles, Index;
  EFI_HANDLE                              *HandleBuffer;
  EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL       *OtherSimpleTextInputEx;

  //
  // Locate the Handle that the SimpleTextOutIn interface is bound to
  //
  Status = gtBS->LocateHandleBuffer (
                        ByProtocol,
                        &gBlackBoxEfiSimpleTextInputExProtocolGuid,
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
                        &gBlackBoxEfiSimpleTextInputExProtocolGuid,
                        &OtherSimpleTextInputEx
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

    if (OtherSimpleTextInputEx == SimpleTextInputEx) {
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
                      &gEfiDevicePathProtocolGuid,
                      DevicePath
                      );

  gtBS->FreePool (HandleBuffer);
  return Status;
}

BOOLEAN
IsATerminalDevice (
  IN CHAR16 *DevicePathStr
  )
{
    const UINTN      TerminalPathStrLength = 5;
    CHAR16           TerminalPathStr[] = L"0501";
    UINTN            i, j, DevicePathStrLength;
    
    for( i=0; DevicePathStr[i]; i++ ) {
    }
    DevicePathStrLength = ++i;

    for ( i=0; i<=DevicePathStrLength-TerminalPathStrLength; i++ ) {
      for ( j=0; TerminalPathStr[j]; j++ ) {
        if ( DevicePathStr[i+j] != TerminalPathStr[j] )
          break;
      }
      if ( j == TerminalPathStrLength - 1 )
        return TRUE;
    }

    return FALSE;
}

BOOLEAN
IsTerminalDevicePath (
  IN  EFI_DEVICE_PATH_PROTOCOL *DevicePath,
  OUT TYPE_OF_TERMINAL         *Termi,
  OUT UINTN                    *Com
  )
/*++

Routine Description:
  Test whether DevicePath is a valid Terminal

Arguments:
  DevicePath  -   DevicePath to be checked
  Termi       -   If is terminal, give its type
  Com         -   If is Com Port, give its type

Returns:
  TRUE        -   If DevicePath point to a Terminal
  FALSE

--*/
{
  UINT8                 *Ptr;
  BOOLEAN               IsTerminal;
  VENDOR_DEVICE_PATH    *Vendor;
//  ACPI_HID_DEVICE_PATH  *Acpi;
//  UINT32                Match;
  EFI_GUID              TempGuid;

  IsTerminal = FALSE;

  //
  // Parse the Device Path, should be change later!!!
  //
  Ptr = (UINT8 *) DevicePath;
  while (*Ptr != END_DEVICE_PATH_TYPE) {
    Ptr++;
  }

  Ptr     = Ptr - sizeof (VENDOR_DEVICE_PATH);
  Vendor  = (VENDOR_DEVICE_PATH *) Ptr;

  //
  // There are four kinds of Terminal types
  // check to see whether this devicepath
  // is one of that type
  //
  gtBS->CopyMem (&TempGuid, &Vendor->Guid, sizeof (EFI_GUID));

  if (SctCompareGuid (&TempGuid, &Guid[0]) == 0) {
    *Termi      = PC_ANSI;
    IsTerminal  = TRUE;
  } else {
    if (SctCompareGuid (&TempGuid, &Guid[1]) == 0) {
      *Termi      = VT_100;
      IsTerminal  = TRUE;
    } else {
      if (SctCompareGuid (&TempGuid, &Guid[2]) == 0) {
        *Termi      = VT_100_PLUS;
        IsTerminal  = TRUE;
      } else {
        if (SctCompareGuid (&TempGuid, &Guid[3]) == 0) {
          *Termi      = VT_UTF8;
          IsTerminal  = TRUE;
        } else {
          IsTerminal = FALSE;
        }
      }
    }
  }

  if (!IsTerminal) {
    return FALSE;
  }
/*
  Ptr   = Ptr - sizeof (UART_DEVICE_PATH) - sizeof (ACPI_HID_DEVICE_PATH);
  Acpi  = (ACPI_HID_DEVICE_PATH *) Ptr;
  Match = EISA_PNP_ID (0x0501);
  if (SctCompareMem (&Acpi->HID, &Match, sizeof (UINT32)) == 0) {
    gtBS->CopyMem (Com, &Acpi->UID, sizeof (UINT32));
  } else {
    return FALSE;
  }
*/
  return TRUE;
}
