/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SctDebug.c

Abstract:

  This file provides the debug macro services for SCT.

--*/

#include "Sct.h"

//
// Module variables
//

EFI_FILE *mLogFile = NULL;

//
// External functions implementation
//

EFI_STATUS
InitializeDebugServices (
  VOID
  )
/*++

Routine Description:

  Initialize the debug services.

Returns:

  EFI_SUCCESS   - Successful.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;
  CHAR16      *FileName;

  //
  // Check the pre-conditions
  //
  if ((gFT == NULL) || (gFT->TolProtocol == NULL)) {
    return EFI_NOT_READY;
  }

  //
  // Open the system log file
  //
  FileName = SctPoolPrint (L"%s\\%s", gFT->FilePath, EFI_SCT_FILE_LOG);
  if (FileName == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = gFT->TolProtocol->Open (
                               gFT->TolProtocol,
                               gFT->DevicePath,
                               FileName,
                               TRUE,                  // Overwrite
                               &mLogFile
                               );
  if (EFI_ERROR(Status)) {
    tBS->FreePool (FileName);
    return Status;
  }

  tBS->FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}


EFI_STATUS
FreeDebugServices (
  VOID
  )
/*++

Routine Description:

  Free the debug services.

Returns:

  EFI_SUCCESS   - Successful.
  Other value   - Something failed.

--*/
{
  EFI_STATUS  Status;

  //
  // Check the pre-conditions
  //
  if (mLogFile == NULL) {
    return EFI_SUCCESS;
  }

  //
  // Close the system log file
  //
  Status = gFT->TolProtocol->Close (
                               gFT->TolProtocol,
                               mLogFile
                               );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  mLogFile = NULL;

  //
  // Done
  //
  return EFI_SUCCESS;
}


VOID
EfiSctDebug (
  IN UINTN              Level,
  IN CHAR16             *Format,
  ...
  )
/*++

Routine Description:

  Worker function for EFI_SCT_DEBUG marco.

--*/
{
  EFI_STATUS  Status;
  VA_LIST     Marker;
  CHAR16      Buffer[EFI_SCT_MAX_BUFFER_SIZE];
  CHAR16      *String;

  //
  // Check the debug masks
  //
  if ((Level & EFI_SCT_D_MASK) == 0) {
    return;
  }

  VA_START (Marker, Format);
  SctVSPrint (Buffer, EFI_SCT_MAX_BUFFER_SIZE, Format, Marker);
  VA_END (Marker);

  //
  // Deal with different error level
  //
  switch (Level) {
  case EFI_SCT_D_ERROR:
    String = SctPoolPrint (L"ERROR: %s\n", Buffer);
    break;

  case EFI_SCT_D_DEBUG:
    String = SctPoolPrint (L"DEBUG: %s\n", Buffer);
    break;

  case EFI_SCT_D_TRACE:
    String = SctPoolPrint (L"TRACE: %s\n", Buffer);
    break;

  default:
    return;
  }

  if (mLogFile != NULL) {
    //
    // Record into the system log file
    //
    Status = gFT->TolProtocol->Write (
                                 gFT->TolProtocol,
                                 mLogFile,
                                 String
                                 );
    if (EFI_ERROR(Status)) {
      tBS->FreePool (String);
      return;
    }
  } else {
    //
    // Print the message into screen before calling InitializeDebugServices
    //
    SctPrint (String);
  }

  tBS->FreePool (String);
}
