/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
