/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2014, ARM Ltd. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

#include "SctLibInternal.h"

//
// International Language
//
#define ISO_639_2_ENTRY_SIZE    3

#include EFI_PROTOCOL_DEFINITION (LoadedImage)

//
// LibInitialized - TRUE once SctInitializeLib () is called for the first time
//
STATIC BOOLEAN  LibInitialized = FALSE;

//
// ST - pointer to the EFI system table
//
EFI_SYSTEM_TABLE        *tST;

//
// BS - pointer to the boot services table
//
EFI_BOOT_SERVICES       *tBS;

//
// RT - pointer to the runtime table
//
EFI_RUNTIME_SERVICES    *tRT;

//
// Default pool allocation type
//
EFI_MEMORY_TYPE PoolAllocationType = EfiBootServicesData;

EFI_UNICODE_COLLATION_PROTOCOL   *UnicodeInterface = NULL;

/*++

Routine Description:

  Initializes Unicode support

Arguments:

  LangCode - Language Code specified

Returns:

  None

--*/
STATIC
VOID
InitializeUnicodeSupport (
  CHAR8 *LangCode
  )
{
  EFI_UNICODE_COLLATION_PROTOCOL *Ui;
  EFI_STATUS                      Status;
  CHAR8                           *Languages;
  UINTN                           Index, Position, Length;
  UINTN                           NoHandles;
  EFI_HANDLE                      *Handles;

  //
  // If we don't know it, lookup the current language code
  //

  SctLocateHandle (ByProtocol, &gEfiUnicodeCollationProtocolGuid, NULL, &NoHandles, &Handles);
  if (!LangCode || !NoHandles) {
    goto Done;
  }

  //
  // Check all driver's for a matching language code
  //

  for (Index=0; Index < NoHandles; Index++) {
    Status = tBS->HandleProtocol (Handles[Index], &gEfiUnicodeCollationProtocolGuid, (VOID**)&Ui);
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    // Check for a matching language code
    //

    Languages = Ui->SupportedLanguages;
    Length = SctAsciiStrLen (Languages);
    for (Position=0; Position < Length; Position += ISO_639_2_ENTRY_SIZE) {

      //
      // If this code matches, use this driver
      //

      if (SctCompareMem (Languages+Position, LangCode, ISO_639_2_ENTRY_SIZE) == 0) {
        UnicodeInterface = Ui;
        goto Done;
      }
    }
  }

Done:
  //
  // Cleanup
  //

  if (Handles) {
    SctFreePool (Handles);
  }
}

EFI_STATUS
SctInitializeLib (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
  EFI_STATUS                Status;
  CHAR8                     *LangCode;

  if (!LibInitialized) {
    LibInitialized = TRUE;

    //
    // Set up global pointer to the system table, boot services table,
    // and runtime services table
    //

    tST = SystemTable;
    tBS = SystemTable->BootServices;
    tRT = SystemTable->RuntimeServices;

    //
    // Initialize pool allocation type
    //

    if (ImageHandle) {
      Status = tBS->HandleProtocol (
                     ImageHandle,
                     &gEfiLoadedImageProtocolGuid,
                     (VOID*)&LoadedImage
                     );

      if (!EFI_ERROR(Status)) {
        PoolAllocationType = LoadedImage->ImageDataType;
      }

      EfiDebugAssertInit ();
      EfiDebugVariable ();
    }

    //
    // Initialize platform specific library
    //

    InitializeLibPlatform (ImageHandle,SystemTable);
  }

  if (ImageHandle) {
    LangCode = 0;
    //
    // BUGBUG: Hard code here because variable service is not available in sync3.
    //
    // LangCode = LibGetVariable (VarLanguage, &EfiGlobalVariable);
    // InitializeUnicodeSupport (LangCode);
    InitializeUnicodeSupport ("eng");
    if (LangCode) {
      SctFreePool (LangCode);
    }
    ASSERT (UnicodeInterface != NULL);
  }
  return EFI_SUCCESS;
}

EFI_STATUS
SctInitializeDriver (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
  /*++

Routine Description:

  Intialize Driver Lib if it has not yet been initialized.

Arguments:

  ImageHandle     - Standard EFI Image entry parameter

  SystemTable     - Standard EFI Image entry parameter

Returns:

  EFI_STATUS always returns EFI_SUCCESS

--*/
{
  tST = SystemTable;

  ASSERT (tST != NULL);

  tBS = tST->BootServices;
  tRT = tST->RuntimeServices;

  ASSERT (tBS != NULL);
  ASSERT (tRT != NULL);

  return EFI_SUCCESS;
}
