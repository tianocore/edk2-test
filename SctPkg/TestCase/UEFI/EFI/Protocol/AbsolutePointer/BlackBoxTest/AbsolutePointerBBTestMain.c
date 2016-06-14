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
                                                                
  Copyright (c) 2010 - 2011, Byosoft Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  AbsolutePointerBBTestMain.c

Abstract:

  Test Driver of Absolute Pointer Protocol

--*/

#include "SctLib.h"
#include "AbsolutePointerBBTestMain.h"

EFI_EVENT              TimerEvent;

//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  ABSOLUTE_POINTER_PROTOCOL_TEST_REVISION,
  EFI_ABSOLUTE_POINTER_PROTOCOL_GUID,
  L"Absolute Pointer Protocol Test",
  L"UEFI Absolute Pointer Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    ABSOLUTE_POINTER_PROTOCOL_RESET_FUNCTION_AUTO_GUID,
    L"Reset_Func",
    L"Invoke Reset() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestResetFunctionAutoTest
  },

  {
    ABSOLUTE_POINTER_PROTOCOL_GETSTATE_FUNCTION_AUTO_GUID,
    L"GetState_Func",
    L"Invoke GetState() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetStateFunctionAutoTest
  },

  {
    ABSOLUTE_POINTER_PROTOCOL_GETSTATE_CONFORMANCE_AUTO_GUID,
    L"GetState_Conf",
    L"Test whether GetState() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetStateConformanceAutoTest
  },

  //
  // Extensive Test
  //
#ifdef EFI_TEST_EXHAUSTIVE
  {
    ABSOLUTE_POINTER_PROTOCOL_RESET_FUNCTION_MANUAL_GUID,
    L"Reset_Func_Manual",
    L"Perform Manual function checkes on the Reset interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestResetFunctionManualTest
  },
  {
    ABSOLUTE_POINTER_PROTOCOL_GETSTATE_FUNCTION_MANUAL_GUID,
    L"GetState_Func_Manual",
    L"Perform Manual function checkes on the GetState interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestGetStateFunctionManualTest
  },
  {
    ABSOLUTE_POINTER_PROTOCOL_WAITFORINPUT_FUNCTION_MANUAL_GUID,
    L"WaitForInput_Func_Manual",
    L"Perform Manual function checkes on the WaitForInput event",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestWaitForInputFunctionManualTest
  },
  {
    ABSOLUTE_POINTER_PROTOCOL_RESET_CLEARANCE_MANUAL_GUID,
    L"Reset_Clearance_Manual",
    L"Perform Manual Clearance checkes on the Reset",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestResetClearanceManualTest
  },
  {
    ABSOLUTE_POINTER_PROTOCOL_GETSTATE_EXTENSIVE_MANUAL_GUID,
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
BBTestAbsolutePointerProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

/**
 *  Absolute Pointer Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestAbsolutePointer (
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
           BBTestAbsolutePointerProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestAbsolutePointerProtocolUnload (
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
 *  assistant function to locate DevicePath Protocol from Absolute Pointer Protocol
 *  @param   AbsoluteIn a pointer of EFI_ABSOLUTE_POINTER_PROTOCOL
 *  @param   DevicePath a pointer pointing to a pointer of EFI_DEVICE_PATH_PROTOCOL
 *  @param   StandardLib a pointer of EFI_STANDARD_TEST_LIBRARY_PROTOCOL
 *  @return Status EFI_SUCCESS if successful.
*/
EFI_STATUS
LocateDevicePathFromAbsolutePointer (
  IN EFI_ABSOLUTE_POINTER_PROTOCOL          *AbsoluteIn,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  )
{
  EFI_STATUS                              Status;

  UINTN                                   NoHandles, Index;
  EFI_HANDLE                              *HandleBuffer;
  EFI_ABSOLUTE_POINTER_PROTOCOL             *OtherAbsoluteIn;

  //
  // Locate the Handle that the AbsolutePointer interface is bound to
  //
  HandleBuffer = NULL;
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiAbsolutePointerProtocolGuid,
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
  // Find the exact handle that AbsolutePointer bound to
  //
  for (Index = 0; Index < NoHandles; Index++) {
      Status = gtBS->HandleProtocol (
                       HandleBuffer[Index],
                       &gBlackBoxEfiAbsolutePointerProtocolGuid,
                       &OtherAbsoluteIn
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
    if (OtherAbsoluteIn == AbsoluteIn) {
      break;
    }
  }

  //
  // Locate the DevicePath Protocol bound to AbsoluteIn Protocol
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
 *  @param  AbsolutePointer This a pointer of  EFI_ABSOLUTE_POINTER_PROTOCOL
*/
BOOLEAN
WaitTimeOrPointer (
  IN  UINTN                         Seconds,
  IN  EFI_ABSOLUTE_POINTER_PROTOCOL   *AbsolutePointer
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
  WaitList[NoWait++] = AbsolutePointer->WaitForInput;

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
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  )
{
  if (Mode->AbsoluteMaxX!=0&& Mode->AbsoluteMinX!=0&& State->CurrentX!=0) {
    return FALSE;
  }

  if (Mode->AbsoluteMaxY!=0 && Mode->AbsoluteMinY!=0&& State->CurrentY!=0) {
    return FALSE;
  }

  if (Mode->AbsoluteMaxZ!=0 && Mode->AbsoluteMinZ!=0&& State->CurrentZ!=0) {
    return FALSE;
  }

  return TRUE;
}

/**
 *  assistant function to auto judge whether pointer's alternate button input is valided?
 *  @param  Mode  Pointer device capability
 *  @param  State Pointer device state
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
SupportAltActive (
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  )
{
  if (Mode->Attributes==FALSE || State->ActiveButtons==FALSE) {
    return FALSE;
  }
  
  return TRUE;
}

/**
 *  assistant function to auto judge whether pointer's alternate button input is pressed?
 *  and no other pointer action exists
 *  @param  Mode  Pointer device capability
 *  @param  State Pointer device state
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
SupportAltActiveExt (
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  )
{
  if (Mode->AbsoluteMaxX!=0 && Mode->AbsoluteMinX!=0 && State->CurrentX!=0) {
    return FALSE;
  }

  if (Mode->AbsoluteMaxY!=0 && Mode->AbsoluteMinY!=0 && State->CurrentY!=0) {
    return FALSE;
  }

  if (Mode->AbsoluteMaxZ!=0 && Mode->AbsoluteMinZ!=0 && State->CurrentZ!=0) {
    return FALSE;
  }

  if (Mode->Attributes==EFI_ABSP_SupportsAltActive && State->ActiveButtons==FALSE) {
    return FALSE;
  }

  if (Mode->Attributes==EFI_ABSP_SupportsPressureAsZ && State->ActiveButtons==FALSE) {
    return FALSE;
  }
  
  if (Mode->Attributes==EFI_ABSP_SupportsPressureAsZ && State->ActiveButtons==TRUE) {
    return FALSE;
  }
  return TRUE;
}

/**
 *  assistant function to auto judge whether pointer's PressureAsZ is actived?
 *  @param  Mode  Pointer device capability
 *  @param  State Pointer device state
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/

BOOLEAN
SupportPressureAsZ(
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  )
{
  if (Mode->Attributes==EFI_ABSP_SupportsPressureAsZ && State->ActiveButtons!=FALSE) {
    return TRUE;
  }

  return FALSE;
}


/**
 *  assistant function to auto judge whether pointer's PressureAsZ is actived?
 *  and no other pointer action exists
 *  @param  Mode  Pointer device capability
 *  @param  State Pointer device state
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
SupportPressureAsZExt (
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  )
{
  if (Mode->AbsoluteMaxX!=0 && Mode->AbsoluteMinX!=0 && State->CurrentX!=0) {
    return FALSE;
  }

  if (Mode->AbsoluteMaxY!=0 && Mode->AbsoluteMinY!=0 && State->CurrentY!=0) {
    return FALSE;
  }

  if (Mode->AbsoluteMaxZ!=0 && Mode->AbsoluteMinZ!=0 && State->CurrentZ!=0) {
    return FALSE;
  }

  if (Mode->Attributes==EFI_ABSP_SupportsPressureAsZ && State->ActiveButtons==FALSE) {
    return FALSE;
  }

  if (Mode->Attributes==EFI_ABSP_SupportsAltActive && State->ActiveButtons==FALSE) {
    return FALSE;
  }
  
  if (Mode->Attributes==EFI_ABSP_SupportsAltActive && State->ActiveButtons==TRUE) {
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
  IN  EFI_ABSOLUTE_POINTER_MODE   *Mode,
  IN  EFI_ABSOLUTE_POINTER_STATE  *State
  )
{
  if (PointerKeepSilent (Mode, State) == TRUE) {
    return FALSE;
  }

  if (Mode->Attributes==TRUE && State->ActiveButtons==TRUE) {
    return FALSE;
  }
  
  return TRUE;
}
