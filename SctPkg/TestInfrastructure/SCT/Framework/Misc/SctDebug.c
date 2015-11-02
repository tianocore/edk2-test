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
