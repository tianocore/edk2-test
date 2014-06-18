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

  ReportConfig.c

Abstract:

  Reports the system under test configuration.

--*/

#include "Sct.h"
#include "ReportSupport.h"

//
// External function implatmentation
//

EFI_STATUS
SctReportConfig (
  OUT UINTN               *BufferSize,
  OUT VOID                **Buffer
  )
/*++

Routine Description:

  Report the system configuration via shell commands.

--*/
{
  EFI_STATUS  Status;
  UINTN       Index;
  CHAR16      *CmdLine;
  CHAR16      *FileName;
  CHAR16      *CmdList[] = {
                L"map -v",
                L"memmap",
                L"pci",
                L"ver",
                L"dh -v",
                L""
              };

  //
  // Record an empty line to a file via shell command
  //

  CmdLine = SctPoolPrint (
              L"ECHO \" \" >a %s",
              EFI_SCT_FILE_CFG
              );
  if (CmdLine == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = SctShellExecute (
             &gFT->ImageHandle,
             CmdLine,
             FALSE,
             NULL, NULL
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctShellExecute: %s - %r", CmdLine, Status));
    tBS->FreePool (CmdLine);
    return Status;
  }

  tBS->FreePool (CmdLine);

  //
  // For each shell command
  //

  for (Index = 0; CmdList[Index][0] != L'\0'; Index++) {

    //
    // Record the command to a file via shell command
    //

    CmdLine = SctPoolPrint (
                L"ECHO \"%s\" >>a %s",
                CmdList[Index],
                EFI_SCT_FILE_CFG
                );
    if (CmdLine == NULL) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
      return EFI_OUT_OF_RESOURCES;
    }

    Status = SctShellExecute (
               &gFT->ImageHandle,
               CmdLine,
               FALSE,
               NULL, NULL
               );
    if (EFI_ERROR (Status)) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctShellExecute: %s - %r", CmdLine, Status));
      tBS->FreePool (CmdLine);
      return Status;
    }

    tBS->FreePool (CmdLine);

    //
    // Get the system configuration to a file via shell command
    //

    CmdLine = SctPoolPrint (
                L"%s >>a %s",
                CmdList[Index],
                EFI_SCT_FILE_CFG
                );
    if (CmdLine == NULL) {
      EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
      return EFI_OUT_OF_RESOURCES;
    }

    Status = SctShellExecute (
               &gFT->ImageHandle,
               CmdLine,
               FALSE,
               NULL, NULL
               );
    if (EFI_ERROR (Status)) {
      //
      // Just record as a debug info. It is acceptable for this command return
      //  an error status
      //
      EFI_SCT_DEBUG ((EFI_SCT_D_DEBUG, L"SctShellExecute: %s - %r", CmdLine, Status));
    }

    tBS->FreePool (CmdLine);
  }

  //
  // Get the system configuration from the file
  //

  FileName = SctPoolPrint (
               L"%s\\%s",
               gFT->FilePath,
               EFI_SCT_FILE_CFG
               );
  if (FileName == NULL) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"SctPoolPrint: Out of resources"));
    return EFI_OUT_OF_RESOURCES;
  }

  Status = ReadFileToBuffer (
             gFT->DevicePath,
             FileName,
             BufferSize,
             (VOID **)Buffer
             );
  if (EFI_ERROR (Status)) {
    EFI_SCT_DEBUG ((EFI_SCT_D_ERROR, L"ReadFileToBuffer: %s - %r", FileName, Status));
    tBS->FreePool (FileName);
    return Status;
  }

  tBS->FreePool (FileName);

  //
  // Done
  //
  return EFI_SUCCESS;
}
