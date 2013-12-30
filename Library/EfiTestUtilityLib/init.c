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

  init.c

Abstract:

  Initialization function

--*/

#include "lib.h"


VOID
EFIDebugVariable (
  VOID
  );


VOID
InitializeLib (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
/*++

Routine Description:

  Initializes EFI library for use

Arguments:

  Firmware's EFI system table

Returns:

  None

--*/
{
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
  EFI_STATUS                Status;
  CHAR8                     *LangCode;

  if (!LibInitialized) {
    LibInitialized = TRUE;
    LibFwInstance = FALSE;

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
      EFIDebugVariable ();
    }

    //
    // Initialize platform specific library
    //

    InitializeLibPlatform (ImageHandle,SystemTable);
  }

  if (ImageHandle && UnicodeInterface == &LibStubUnicodeInterface) {
    LangCode = 0;
    //
    // BUGBUG: Hard code here because variable service is not available in sync3.
    //
    // LangCode = LibGetVariable (VarLanguage, &EfiGlobalVariable);
    // InitializeUnicodeSupport (LangCode);
    InitializeUnicodeSupport ("eng");
    if (LangCode) {
      FreePool (LangCode);
    }
  }
}


VOID
InitializeUnicodeSupport (
  CHAR8 *LangCode
  )
/*++

Routine Description:

  Initializes Unicode support

Arguments:

  LangCode - Language Code specified

Returns:

  None

--*/
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

  LibLocateHandle (ByProtocol, &gEfiUnicodeCollationProtocolGuid, NULL, &NoHandles, &Handles);
  if (!LangCode || !NoHandles) {
    goto Done;
  }

  //
  // Check all driver's for a matching language code
  //

  for (Index=0; Index < NoHandles; Index++) {
    Status = tBS->HandleProtocol (Handles[Index], &gEfiUnicodeCollationProtocolGuid, (VOID*)&Ui);
    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    // Check for a matching language code
    //

    Languages = Ui->SupportedLanguages;
    Length = strlena(Languages);
    for (Position=0; Position < Length; Position += ISO_639_2_ENTRY_SIZE) {

      //
      // If this code matches, use this driver
      //

      if (CompareMem (Languages+Position, LangCode, ISO_639_2_ENTRY_SIZE) == 0) {
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
    FreePool (Handles);
  }
}

VOID
EFIDebugVariable (
  VOID
  )
/*++

Routine Description:
  Initializes the EFIDebug variable for our build

Arguments:

  None

Returns:

  None

--*/
{
  EFI_STATUS      Status;
  UINT32          Attributes;
  UINTN           DataSize;
  UINTN           NewEFIDebug;

  DataSize = sizeof(EFIDebug);
  Status = tRT->GetVariable(L"EFIDebug", &tEfiGlobalVariable, &Attributes, &DataSize, &NewEFIDebug);
  if (!EFI_ERROR(Status)) {
    EFIDebug = NewEFIDebug;
  }
}
