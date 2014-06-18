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
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  SctInit.c

Abstract:

  Provides SCT initialization services.

--*/

#include "Sct.h"

//
// External functions implementation
//

EFI_STATUS
InitializeFrameworkTable (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
/*++

Routine Description:

  Initialize the framework table.

Arguments:

  ImageHandle    - The image handle.
  SystemTable    - The system table.

Returns:

  EFI_SUCCESS   - Successfully.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  CHAR16      **Argv;
  CHAR16      *TempFilePathPtr;

  //
  // Allocate memory for the framework table
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 sizeof(EFI_SCT_FRAMEWORK_TABLE),
                 (VOID **)&gFT
                 );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  SctZeroMem (gFT, sizeof(EFI_SCT_FRAMEWORK_TABLE));

  //
  // Initialize the items of framework table
  //
  gFT->Signature = EFI_SCT_FRAMEWORK_TABLE_SIGNATURE;
  gFT->Revision  = EFI_SCT_FRAMEWORK_TABLE_REVISION;

  SctInitializeListHead (&gFT->CategoryList);
  SctInitializeListHead (&gFT->TestFileList);
  SctInitializeListHead (&gFT->SupportFileList);
  SctInitializeListHead (&gFT->ProxyFileList);
  SctInitializeListHead (&gFT->TestCaseList);
  SctInitializeListHead (&gFT->TestNodeList);
  SctInitializeListHead (&gFT->SkippedCaseList);

  //
  // Initialize the image data
  //
  gFT->ImageHandle = ImageHandle;
  gFT->SystemTable = SystemTable;

  SctShellGetArguments (NULL, &Argv);
  Status = SctGetFilesystemDevicePath (
             Argv[0],
             &gFT->DevicePath,
             &TempFilePathPtr
             );
  gFT->FilePath = SctStrDuplicate (TempFilePathPtr);
  if (gFT->FilePath == NULL) {
    FreeFrameworkTable ();
    return EFI_OUT_OF_RESOURCES;
  }
  Status = StripLastPathComponent (gFT->FilePath);
  if (EFI_ERROR (Status)) {
    FreeFrameworkTable ();
    return Status;
  }

  //
  // Initialize the test data
  //
  gFT->Operations    = EFI_SCT_OPERATIONS_NONE;
  gFT->SeqFileName   = NULL;
  gFT->RepFileName   = NULL;

  gFT->TestCaseFileName = SctPoolPrint (
                 L"%s\\%s",
                 gFT->FilePath,
                 EFI_SCT_FILE_TEST_CASE
                 );
  if (gFT->TestCaseFileName == NULL) {
    FreeFrameworkTable ();
    return Status;
  }
  gFT->TestCaseIniFile = NULL;

  gFT->IsFirstTimeExecute = TRUE;

  //
  // The configuration data will be initialized later
  //

  //
  // Initialize the test support protocols
  //
  gFT->TolProtocol = gOutputProtocol;

  //
  // Initialize the debug services
  //
  Status = InitializeDebugServices ();
  if (EFI_ERROR (Status)) {
    FreeFrameworkTable ();
    return Status;
  }

  //
  // Get the maximum watchdog timer
  //
  Status = GetMaxWatchdogTimer (&gTestCaseMaxRunTimeMax);
  if (EFI_ERROR (Status)) {
    FreeFrameworkTable ();
    return Status;
  }

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FreeFrameworkTable (
  VOID
  )
/*++

Routine Description:

  Free the framework table.

--*/
{
  //
  // Close/Free the INI file
  //
  tBS->FreePool (gFT->TestCaseFileName);
  if (gFT->TestCaseIniFile != NULL) {
    gFT->TplProtocol->EfiIniClose (gFT->TplProtocol, gFT->TestCaseIniFile);
  }

  //
  // Close the standard test support files
  //
  CloseStandardSupportFiles ();

  //
  // Free the items of framework table
  //
  if (gFT->ConfigData != NULL) {
    FreeConfigData (gFT->ConfigData);
    tBS->FreePool (gFT->ConfigData);
    gFT->ConfigData = NULL;
  }

  FreeSkippedCases (&gFT->SkippedCaseList);

  FreeCategoryData (&gFT->CategoryList);

  FreeTestCases (&gFT->TestCaseList);
  FreeTestNodes (&gFT->TestNodeList);

  UnloadTestFiles (&gFT->TestFileList);
  UnloadSupportFiles (&gFT->SupportFileList);
  UnloadProxyFiles (&gFT->ProxyFileList);

    gFT->DevicePath = NULL;

  if (gFT->FilePath != NULL) {
    tBS->FreePool (gFT->FilePath);
    gFT->FilePath = NULL;
  }

  if (gFT->SeqFileName != NULL) {
    tBS->FreePool (gFT->SeqFileName);
    gFT->SeqFileName = NULL;
  }

  if (gFT->RepFileName != NULL) {
    tBS->FreePool (gFT->RepFileName);
    gFT->RepFileName = NULL;
  }

  //
  // Free the debug services
  //
  FreeDebugServices ();

  //
  // Free the framework table itself
  //
  tBS->FreePool (gFT);

  //
  // Done
  //
  return EFI_SUCCESS;
}
