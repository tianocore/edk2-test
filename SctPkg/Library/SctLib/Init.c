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

  Copyright (c) 2013-2014, ARM Ltd. All rights reserved.

--*/

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
