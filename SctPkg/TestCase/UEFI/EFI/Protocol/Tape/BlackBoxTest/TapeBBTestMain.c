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
                                                                
  Copyright (c) 2010 - 2012, Phoenix Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  TapeBBTestMain.c

Abstract:

  Test Driver of TapeIo Protocol

--*/

#include "SctLib.h"
#include "TapeBBTestMain.h"

EFI_BB_TEST_PROTOCOL *gTapeTestProtocol = NULL;
EFI_TAPE_IO_PROTOCOL *gTapeIoProtocol = NULL;

EFI_EVENT              TimerEvent;
EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib = NULL;
EFI_TEST_LOGGING_LIBRARY_PROTOCOL	*LoggingLib = NULL;
  
EFI_BB_TEST_PROTOCOL_FIELD gEfiTapeTestProtField = {
  TAPE_TEST_REVISION,
  TAPE_FUNCTION_TEST_GUID,
  L"Tape Protocol Testing",
  L"Tape Protocol"
};

EFI_GUID gStandardLibSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gTapeTestEntryField[] = {
  {
    EFI_TEST_TAPE_BBTESTMAIN_ASSERTION_001_GUID,
    L"TapeTest_I",
    L"Read Tape Testing",
    EFI_TEST_LEVEL_DEFAULT,
    gStandardLibSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestTapeFunctionRead
  },
  {
    EFI_TEST_TAPE_BBTESTMAIN_ASSERTION_002_GUID,
    L"TapeTest_II",
    L"Write Tape Testing",
    EFI_TEST_LEVEL_DEFAULT,
    gStandardLibSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestTapeFunctionWrite
  },
  {
    EFI_TEST_TAPE_BBTESTMAIN_ASSERTION_003_GUID,
    L"TapeTest_III",
    L"Rewind Tape Testing",
    EFI_TEST_LEVEL_DEFAULT,
    gStandardLibSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestTapeFunctionRewind
  },
  {
    EFI_TEST_TAPE_BBTESTMAIN_ASSERTION_004_GUID,
    L"TapeTest_IV",
    L"Space Tape Testing",
    EFI_TEST_LEVEL_DEFAULT,
    gStandardLibSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestTapeFunctionSpace
  },
  {
    EFI_TEST_TAPE_BBTESTMAIN_ASSERTION_005_GUID,
    L"TapeTest_V",
    L"WriteFM Tape Testing",
    EFI_TEST_LEVEL_DEFAULT,
    gStandardLibSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestTapeFunctionWriteFM
  },
  {
    EFI_TEST_TAPE_BBTESTMAIN_ASSERTION_006_GUID,
    L"TapeTest_VI",
    L"Reset Tape Testing",
    EFI_TEST_LEVEL_DEFAULT,
    gStandardLibSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestTapeFunctionReset
  },    
  0
};


/*********************************************************************************
 *  Creates/installs the BlackBox Interface and eminating Entry Point node list.
 *  @param  ImageHandle The test driver image handle
 *  @param  SystemTable Pointer to System Table
 *  @return EFI_SUCCESS Indicates the interface was installed
 *  @return EFI_OUT_OF_RESOURCES Indicates space for the new handle could not be allocated
 *  @return EFI_INVALID_PARAMETER: One of the parameters has an invalid value.
 ********************************************************************************/
EFI_STATUS
InitializeTapeTest (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS Status;
  
  
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);
  SctInitializeDriver (ImageHandle, SystemTable);
  
  //
  // Make sure the Protocol is not already installed in the system
  //
  //ASSERT_PROTOCOL_ALREADY_INSTALLED (NULL, &gBlackBoxEfiTapeIoProtocolGuid);  
  
  Status = gtBS->CreateEvent (EVT_TIMER, 0, NULL, NULL, &TimerEvent);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gEfiTapeTestProtField,
           gTapeTestEntryField,
           UnloadTapeTest,
           &gTapeTestProtocol
           );  
  return Status;  
         
}

EFI_STATUS
UnloadTapeTest (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = gtBS->CloseEvent (TimerEvent);
  if (EFI_ERROR(Status)) {

  }
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gTapeTestProtocol
           );
}

/********************************************************************************
 *  Wait for any input from user
 ********************************************************************************/
void TapeTestWaitForAnyInput (void)
{
  UINTN                   NoWait = 1, WaitIndex;
  EFI_EVENT               WaitList[1];
  EFI_STATUS              Status;
  EFI_INPUT_KEY           Key;

  SctPrint (L"\r\nPress any key to continue...");

  //
  // Set 1 second periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);

  //
  // Set up a wait list for a key and the timer
  //
  NoWait = 0;
  WaitList[NoWait++] = gtST->ConIn->WaitForKey;

  //
  // Wait for either
  //
  while (NoWait) {
    Status = gtBS->WaitForEvent (NoWait, WaitList, &WaitIndex);

    switch (WaitIndex) {
      case 0:
        //
        // Read the key
        //
        Status = gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
        if (EFI_SUCCESS == Status)
          NoWait = 0;
        break;

      default:
        break;
    }
  }
  SctPrint (L"\r\n");

  //
  // Done, cancel periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
}

EFI_STATUS
getStandardLibInterface( EFI_HANDLE SupportHandle )
{
	EFI_STATUS Status;

  //
  // Get support library (Standard Lib, Profile Lib, Logging Lib)
  //
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );
  if (EFI_ERROR(Status))
  {
  	SctPrint (L"\r\nHandleProtocol(StandardLib) Fail(%Xh) !", Status);
    return Status;
  }

  // Get the Logging Library Interface
  //
  Status = gtBS->LocateProtocol (
                   &gEfiTestLoggingLibraryGuid,
                   NULL,
                   &LoggingLib
                   );
  if (EFI_ERROR(Status))
  {
  	SctPrint (L"\r\nHandleProtocol(LoggingLib) Fail(%Xh) !", Status);
    return Status;
  }
  
  //SctPrint (L"\r\ngetStandardLibInterface successful.");
  return Status;

}
