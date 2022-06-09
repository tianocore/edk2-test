/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Phoenix Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

# Module Name:

  AUTHBBTestMain.c

Abstract:

  Test Driver of AUTH Protocol

--*/

#include "SctLib.h"
#include "AuthenticationBBTestMain.h"
#include "AuthTest.h"

EFI_EVENT              TimerEvent;
EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
EFI_TEST_LOGGING_LIBRARY_PROTOCOL		*LoggingLib;
  
EFI_BB_TEST_PROTOCOL_FIELD gEfiAuthenticationTestProtField = {
  AUTH_TEST_REVISION,
  AUTH_FUNCTION_TEST_GUID,
  L"AUTH Protocol Test",
  L"AUTH Protocol"
};

EFI_GUID gStandardLibSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gAuthenticationTestEntryField[] = {

//#ifdef EFI_TEST_EXHAUSTIVE
  {
    EFI_TEST_AUTH_BBTESTMAIN_ASSERTION_001_GUID,
    L"Authentication_Setting",
    L"Authentication Test of Setting Information",
    EFI_TEST_LEVEL_DEFAULT,
    gStandardLibSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestAuthenticationFunctionTestA
  },
//#endif
  {
    EFI_TEST_AUTH_BBTESTMAIN_ASSERTION_002_GUID,
    L"Authentication_Getting",
    L"Authentication Test of Getting Information",
    EFI_TEST_LEVEL_DEFAULT,
    gStandardLibSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestAuthenticationFunctionTestB
  },
  0
};


EFI_BB_TEST_PROTOCOL *gAuthenticationTestProt;


/*********************************************************************************
 *  Creates/installs the BlackBox Interface and eminating Entry Point node list.
 *  @param  ImageHandle The test driver image handle
 *  @param  SystemTable Pointer to System Table
 *  @return EFI_SUCCESS Indicates the interface was installed
 *  @return EFI_OUT_OF_RESOURCES Indicates space for the new handle could not be allocated
 *  @return EFI_INVALID_PARAMETER: One of the parameters has an invalid value.
 ********************************************************************************/
EFI_STATUS
EFIAPI
InitializeAuthenticationTest (
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
  //ASSERT_PROTOCOL_ALREADY_INSTALLED (NULL, &);  
  
  Status = gtBS->CreateEvent (EVT_TIMER, 0, (EFI_EVENT_NOTIFY) NULL, NULL, &TimerEvent);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gEfiAuthenticationTestProtField,
           gAuthenticationTestEntryField,
           UnloadAuthenticationTest,
           &gAuthenticationTestProt
           );
}

EFI_STATUS
EFIAPI
UnloadAuthenticationTest (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;
  
  Status = gtBS->CloseEvent (TimerEvent);
  if (EFI_ERROR(Status)) {

  }
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gAuthenticationTestProt
           );
}

/*********************************************************************************
 *  Entrypoint for EFI_LOAD_FILE.AUTH() Function and Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 ********************************************************************************/
EFI_STATUS
EFIAPI
BBTestAuthenticationFunctionTestA (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  )
{

  EFI_STATUS                            Status;
  EFI_AUTHENTICATION_INFO_PROTOCOL *AuthenticationProtocol = NULL;
  EFI_HANDLE testAuthHandle = NULL;

  //
  // Get support library (Standard Lib, Profile Lib, Logging Lib)
  //
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status))
  {
    return Status;
  }

  // Get the Logging Library Interface
  //
  Status = gtBS->LocateProtocol (
                   &gEfiTestLoggingLibraryGuid,
                   NULL,
                   (VOID **) &LoggingLib
                   );
  if (EFI_ERROR(Status))
  {
    return Status;
  }
  
   //
  // Get the Standard Library Interface
  //
  AuthenticationProtocol = (EFI_AUTHENTICATION_INFO_PROTOCOL *)ClientInterface;
  if(AuthenticationProtocol == NULL)
  	return EFI_UNSUPPORTED;
  	
  my_printf((L"\n  SetAuthInfoTest ..."));  
  SetAuthInfoTest(AuthenticationProtocol, &testAuthHandle); 
  
  my_printf((L"\n\n  DumpAll ..."));    
  AuthenticationProtocol->DumpAll(AuthenticationProtocol); 
  
  my_printf((L"\n\n  CleanAll ..."));     
  AuthenticationProtocol->CleanAll(AuthenticationProtocol);  
//==============================================================================================


  
  return Status;
}

/*********************************************************************************
 *  Entrypoint for EFI_LOAD_FILE.AUTH() Function and Conformance Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 ********************************************************************************/
EFI_STATUS
EFIAPI
BBTestAuthenticationFunctionTestB (
  IN EFI_BB_TEST_PROTOCOL             *This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  )
{

  EFI_STATUS                            Status;
  EFI_AUTHENTICATION_INFO_PROTOCOL *AuthenticationProtocol = NULL;
  EFI_HANDLE testAuthHandle = NULL;
  GenericAuthenticationNodeStruct info;
  //
  // Get support library (Standard Lib, Profile Lib, Logging Lib)
  //
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status))
  {
    return Status;
  }

  // Get the Logging Library Interface
  //
  Status = gtBS->LocateProtocol (
                   &gEfiTestLoggingLibraryGuid,
                   NULL,
                   (VOID **) &LoggingLib
                   );
  if (EFI_ERROR(Status))
  {
    return Status;
  }
  
   //
  // Get the Standard Library Interface
  //
  AuthenticationProtocol = (EFI_AUTHENTICATION_INFO_PROTOCOL *)ClientInterface;
  if(AuthenticationProtocol == NULL)
  	return EFI_UNSUPPORTED;

	info.length = 0x30;
  Status = AuthenticationProtocol->Set(AuthenticationProtocol, &testAuthHandle, &info);	
  
  my_printf((L"\n\n  DumpAll ..."));    
  AuthenticationProtocol->DumpAll(AuthenticationProtocol); 
    
  my_printf((L"\n\n  GetAuthInfoTest ..."));    
  GetAuthInfoTest(AuthenticationProtocol, &testAuthHandle);
  
  my_printf((L"\n\n  DumpAll ..."));    
  AuthenticationProtocol->DumpAll(AuthenticationProtocol); 
  
  my_printf((L"\n\n  CleanAll ..."));     
  AuthenticationProtocol->CleanAll(AuthenticationProtocol);  
  
  return Status;
}

/********************************************************************************
 *  Wait for any input from user
 ********************************************************************************/
VOID
AuthenticationTestWaitForAnyInput ()
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
  // Done, cancle periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);
}

