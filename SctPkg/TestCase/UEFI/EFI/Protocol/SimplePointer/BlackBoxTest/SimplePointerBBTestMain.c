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

  SimplePointerBBTestMain.c

Abstract:

  Test Driver of Simple Pointer Protocol

--*/


#include "SctLib.h"
#include "SimplePointerBBTestMain.h"

EFI_EVENT              TimerEvent;
//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  SIMPLE_POINTER_PROTOCOL_TEST_REVISION,
  EFI_SIMPLE_POINTER_PROTOCOL_GUID,
  L"Simple Pointer Protocol Test",
  L"UEFI Simple Pointer Protocol Test"
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
    SIMPLE_POINTER_PROTOCOL_RESET_FUNCTION_AUTO_GUID,
    L"Reset_Func",
    L"Perform auto function checkes on the Reset interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetFunctionAutoTest
  },
  {
    SIMPLE_POINTER_PROTOCOL_GETSTATE_FUNCTION_AUTO_GUID,
    L"GetState_Func",
    L"Perform auto function checkes on the GetState interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetStateFunctionAutoTest
  },

  //
  // Extensive Test
  //
#ifdef EFI_TEST_EXHAUSTIVE
  {
    SIMPLE_POINTER_PROTOCOL_RESET_FUNCTION_MANUAL_GUID,
    L"Reset_Func_Manual",
    L"Perform Manual function checkes on the Reset interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestResetFunctionManualTest
  },
  {
    SIMPLE_POINTER_PROTOCOL_GETSTATE_FUNCTION_MANUAL_GUID,
    L"GetState_Func_Manual",
    L"Perform Manual function checkes on the GetState interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestGetStateFunctionManualTest
  },
  {
    SIMPLE_POINTER_PROTOCOL_WAITFORINPUT_FUNCTION_MANUAL_GUID,
    L"WaitForInput_Func_Manual",
    L"Perform Manual function checkes on the WaitForInput event",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestWaitForInputFunctionManualTest
  },
  {
    SIMPLE_POINTER_PROTOCOL_RESET_CLEARANCE_MANUAL_GUID,
    L"Reset_Clearance_Manual",
    L"Perform Manual Clearance checkes on the Reset",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestResetClearanceManualTest
  },
  {
    SIMPLE_POINTER_PROTOCOL_GETSTATE_EXTENSIVE_MANUAL_GUID,
    L"GetState_Stress_Manual",
    L"Perform Extensively Manual checkes on the GetState",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestGetStateExtensiveManualTest
  },
#endif

  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
BBTestSimplePointerProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Simple Pointer Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestSimplePointer (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  gtBS->CreateEvent (EVT_TIMER, 0, NULL, NULL, &TimerEvent);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestSimplePointerProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestSimplePointerProtocolUnload (
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
 *  assistant function to locate DevicePath Protocol from Simple Pointer Protocol
 *  @param
 *  @param
 *  @return Status
*/
EFI_STATUS
LocateDevicePathFromSimplePointer (
  IN EFI_SIMPLE_POINTER_PROTOCOL          *SimpleIn,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                   NoHandles, Index;
  EFI_HANDLE                              *HandleBuffer;
  EFI_SIMPLE_POINTER_PROTOCOL             *OtherSimpleIn;

  //
  // Locate the Handle that the SimplePointer interface is bound to
  //
  HandleBuffer = NULL;
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiSimplePointerProtocolGuid,
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
  // Find the exact handle that SimplePointer bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[Index],
                       &gBlackBoxEfiSimplePointerProtocolGuid,
                       &OtherSimpleIn
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
                   &gEfiDevicePathProtocolGuid,
                   DevicePath
                   );

  gtBS->FreePool (HandleBuffer);
  return Status;
}

/**
 *  assistant function to wait a key press or timeout?
 *  @param  Seconds time inteval
*/
BOOLEAN
WaitTimeOrPointer (
  IN  UINTN                         Seconds,
  IN  EFI_SIMPLE_POINTER_PROTOCOL   *SimplePointer
  )
{
  EFI_STATUS              Status;
  EFI_EVENT               WaitList[2];
  UINTN                   NoWait, WaitIndex;
  BOOLEAN                 PointerInput = FALSE;

  //
  // Set 1 second periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);

  //
  // Set up a wait list for a key and the timer
  //

  NoWait = 0;
  WaitList[NoWait++] = TimerEvent;
  WaitList[NoWait++] = SimplePointer->WaitForInput;

  //
  // Wait for either
  //

  while (NoWait)   {
    SctPrint (L"\rRemains %d seconds ", Seconds);
    Status = gtBS->WaitForEvent (NoWait, WaitList, &WaitIndex);

    switch (WaitIndex) {
      case 0:
        Seconds -= 1;
        if (Seconds <= 0) {
          NoWait = 0;     // stop loop
        }
        break;
      case 1:
        PointerInput = TRUE;
        NoWait = 0;
        break;
      default:            // bad WaitIndex response
        break;
   }
  }


  //
  // Done, cancle periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
  return PointerInput;
}

/**
 *  assistant function to auto judge the user's choice, correct or uncorrect?
 *  @param  Seconds time inteval
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
VOID
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
      SctPrint (L"\rYes/No?(Auto judge as Yes in %d seconds) ", Seconds);
    } else {
      SctPrint (L"\rYes/No?(Auto judge as No in %d seconds) ", Seconds);
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
 *  assistant function to auto judge whether pointer keep silent?
 *  @param  Mode  Pointer device capability
 *  @param  State Pointer device state
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
PointerKeepSilent (
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  )
{
  if (Mode->ResolutionX!=0 && State->RelativeMovementX!=0) {
    return FALSE;
  }

  if (Mode->ResolutionY!=0 && State->RelativeMovementY!=0) {
    return FALSE;
  }

  if (Mode->ResolutionZ!=0 && State->RelativeMovementZ!=0) {
    return FALSE;
  }

  return TRUE;
}

/**
 *  assistant function to auto judge whether pointer's right button is pressed?
 *  @param  Mode  Pointer device capability
 *  @param  State Pointer device state
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
PointerRButtonPressed (
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  )
{
  if (Mode->RightButton==TRUE && State->RightButton==FALSE) {
    return FALSE;
  }

  return TRUE;
}

/**
 *  assistant function to auto judge whether pointer's right button is pressed?
 *  and no other pointer action exists
 *  @param  Mode  Pointer device capability
 *  @param  State Pointer device state
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
PointerRButtonPressedExt (
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  )
{
  if (Mode->ResolutionX!=0 && State->RelativeMovementX!=0) {
    return FALSE;
  }

  if (Mode->ResolutionY!=0 && State->RelativeMovementY!=0) {
    return FALSE;
  }

  if (Mode->ResolutionZ!=0 && State->RelativeMovementZ!=0) {
    return FALSE;
  }

  if (Mode->LeftButton==TRUE && State->LeftButton==TRUE) {
    return FALSE;
  }

  if (Mode->RightButton==TRUE && State->RightButton==FALSE) {
    return FALSE;
  }

  return TRUE;
}

/**
 *  assistant function to auto judge whether pointer's left button is pressed?
 *  @param  Mode  Pointer device capability
 *  @param  State Pointer device state
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
PointerLButtonPressed (
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  )
{
  if (Mode->LeftButton==TRUE && State->LeftButton==FALSE) {
    return FALSE;
  }

  return TRUE;
}


/**
 *  assistant function to auto judge whether pointer's Left button is pressed?
 *  and no other pointer action exists
 *  @param  Mode  Pointer device capability
 *  @param  State Pointer device state
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
PointerLButtonPressedExt (
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  )
{
  if (Mode->ResolutionX!=0 && State->RelativeMovementX!=0) {
    return FALSE;
  }

  if (Mode->ResolutionY!=0 && State->RelativeMovementY!=0) {
    return FALSE;
  }

  if (Mode->ResolutionZ!=0 && State->RelativeMovementZ!=0) {
    return FALSE;
  }

  if (Mode->RightButton==TRUE && State->RightButton==TRUE) {
    return FALSE;
  }

  if (Mode->LeftButton==TRUE && State->LeftButton==FALSE) {
    return FALSE;
  }

  return TRUE;
}


/**
 *  assistant function to auto judge whether pointer's Only moved?
 *  and no other pointer action exists
 *  @param  Mode  Pointer device capability
 *  @param  State Pointer device state
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
PointerMovedExt (
  IN  EFI_SIMPLE_POINTER_MODE   *Mode,
  IN  EFI_SIMPLE_POINTER_STATE  *State
  )
{
  if (PointerKeepSilent (Mode, State) == TRUE) {
    return FALSE;
  }

  if (Mode->LeftButton==TRUE && State->LeftButton==TRUE) {
    return FALSE;
  }

  if (Mode->LeftButton==TRUE && State->LeftButton==TRUE) {
    return FALSE;
  }

  return TRUE;
}

