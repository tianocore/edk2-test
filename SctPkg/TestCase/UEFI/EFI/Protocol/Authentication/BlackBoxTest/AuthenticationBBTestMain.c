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
  
  Status = gtBS->CreateEvent (EVT_TIMER, 0, NULL, NULL, &TimerEvent);
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
                   &StandardLib
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
                   &LoggingLib
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
                   &StandardLib
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
                   &LoggingLib
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

