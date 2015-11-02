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
  UsbHcTestMain.c

Abstract:
  The main source file for Usb Hc tesing.

--*/

//
// Includes
//

#include "SctLib.h"
#include "UsbHcTest.h"

//
// Declarations
//

EFI_EVENT              TimerEvent;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  USB_HC_TEST_REVISION,
  EFI_USB_HC_PROTOCOL_GUID,
  L"Usb Host Controller Protocol Interface Tests",
  L"UEFI Usb Host Controller Protocol Interface Test"
};

EFI_GUID gSupportProtocolGuid1[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_GUID gSupportProtocolGuid2[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_TEST_RECOVERY_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    USB_HC_RESET_CONFORMANCE_AUTO_GUID,
    L"Reset_Conf",
    L"Perform conformance checks on the UsbHc->Reset",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcResetConformanceAutoTest
  },
  {
    USB_HC_GETSTATE_CONFORMANCE_AUTO_GUID,
    L"GetState_Conf",
    L"Perform conformance checks on the UsbHc->GetState",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcGetStateConformanceAutoTest
  },
  {
    USB_HC_SETSTATE_CONFORMANCE_AUTO_GUID,
    L"SetState_Conf",
    L"Perform conformance checks on the UsbHc->SetState",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcSetStateConformanceAutoTest
  },
  {
    USB_HC_CONTROLTRANSFER_CONFORMANCE_AUTO_GUID,
    L"ControlTransfer_Conf",
    L"Perform conformance checks on the UsbHc->ControlTransfer",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcControlTransferConformanceAutoTest
  },
  {
    USB_HC_BULKTRANSFER_CONFORMANCE_AUTO_GUID,
    L"BulkTransfer_Conf",
    L"Perform conformance checks on the UsbHc->BulkTransfer",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcBulkTransferConformanceAutoTest
  },
  {
    USB_HC_ASYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID,
    L"AsyncInterruptTransfer_Conf",
    L"Perform conformance checks on the UsbHc->AsyncInterruptTransfer",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcAsyncInterruptTransferConformanceAutoTest
  },
  {
    USB_HC_SYNCINTERRUPTTRANSFER_CONFORMANCE_AUTO_GUID,
    L"SyncInterruptTransfer_Conf",
    L"Perform conformance checks on the UsbHc->SyncInterruptTransfer",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcSyncInterruptTransferConformanceAutoTest
  },
  {
    USB_HC_ASYNCISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID,
    L"AsyncIsochronousTransfer_Conf",
    L"Perform conformance checks on the UsbHc->AsyncIsochronousTransfer",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcAsyncIsochronousTransferConformanceAutoTest
  },
  {
    USB_HC_ISOCHRONOUSTRANSFER_CONFORMANCE_AUTO_GUID,
    L"IsochronousTransfer_Conf",
    L"Perform conformance checks on the UsbHc->IsochronousTransfer",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcIsochronousTransferConformanceAutoTest
  },
  {
    USB_HC_GETROOTHUBPORTNUMBER_CONFORMANCE_AUTO_GUID,
    L"GetRootHubPortNumber_Conf",
    L"Perform conformance checks on the UsbHc->GetRootHubPortNumber",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcGetRootHubPortNumberConformanceAutoTest
  },
  {
    USB_HC_GETROOTHUBPORTSTATUS_CONFORMANCE_AUTO_GUID,
    L"GetRootHubPortStatus_Conf",
    L"Perform conformance checks on the UsbHc->GetRootHubPortStatus",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcGetRootHubPortStatusConformanceAutoTest
  },
  {
    USB_HC_SETROOTHUBPORTFEATURE_CONFORMANCE_AUTO_GUID,
    L"SetRootHubPortFeature_Conf",
    L"Perform conformance checks on the UsbHc->SetRootHubPortFeature",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcSetRootHubPortFeatureConformanceAutoTest
  },
  {
    USB_HC_CLEARROOTHUBPORTFEATURE_CONFORMANCE_AUTO_GUID,
    L"ClearRootHubPortFeature_Conf",
    L"Perform conformance checks on the UsbHc->ClearRootHubPortFeature",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    UsbHcClearRootHubPortFeatureConformanceAutoTest
  },
  0
};

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

//
// Functions
//


/**
 *  Creates/installs the BlackBox Interface and the Entry Point list.
 *  @param ImageHandle    The image handle.
 *  @param SystemTable    The system table.
 *  @return EFI_SUCCESS   The interface was installed successfully.
 *  @return EFI_OUT_OF_RESOURCES    Failed due to the lack of resources.
 *  @return EFI_INVALID_PARAMETER   One of parameters is invalid.
 */
EFI_STATUS
InitializeBBTestUsbHc (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);

  gtBS->CreateEvent(EVT_TIMER, 0, NULL, NULL, &TimerEvent);

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestUsbHcUnload,
           &gBBTestProtocolInterface
           );
}


/**
 *  Unloads the BlackBox Interface and the Entry Point list.
 *  @param ImageHandle    The image handle.
 *  @return EFI_SUCCESS   The interface was uninstalled successfully.
 */
EFI_STATUS
BBTestUsbHcUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  gtBS->CloseEvent(TimerEvent);
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


VOID StallForChangeDevice(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN UINTN                                Time
  )
{
  UINTN i;
  for (i = 0; i < Time; i++) {
    StandardLib->RecordMessage (StandardLib, EFI_VERBOSE_LEVEL_DEFAULT, L"%d s left", Time - i);
    gtBS->Stall (1000000);
  }
}

/**
 *  assistant function to auto judge the user's choice, correct or uncorrect?
 *  @param  Seconds time inteval
 *  @return TRUE/FALSE standing for correct/uncorrect choice respectively
*/
BOOLEAN
AutoJudge(
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
  Status = gtBS->SetTimer(TimerEvent, TimerPeriodic, 10000000);

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
      SctPrint(L"\rYes/No?(Auto judge as Yes in %d seconds)",Seconds);
    } else {
      SctPrint(L"\rYes/No?(Auto judge as No in %d seconds)",Seconds);
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
        switch( Key.UnicodeChar ) {
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
            SctPrint(L"\n");
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
