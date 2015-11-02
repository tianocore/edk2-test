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

  EntsResult.c
  
Abstract:
  
  Implementation of recording result services 
  
--*/
#include "Efi.h"
#include <Library/EntsLib.h>

EFI_STATUS
RecordMessage (
  IN  OUT CHAR16**ResultBuffer,
  IN  OUT UINTN *ResultBufferSize,
  IN     CHAR16 *Format,
  ...
  )
/*++

Routine Description:

  Record runtime information to a buffer.

Arguments:

  ResultBuffer      - Buffer space.
  ResultBufferSize  - Result buffer size in octets.
  Format            - Format string.
  ...               - Variables.

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.

--*/
{
  UINTN   Size;
  VA_LIST Marker;
  CHAR16  *Buffer;

  Buffer = EntsAllocatePool (ENTS_MAX_BUFFER_SIZE * 4 * 8);
  if (Buffer == NULL) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in RecordMessage Status - EFI_OUT_OF_RESOURCES"));
    return EFI_OUT_OF_RESOURCES;
  }

  VA_START (Marker, Format);
  EntsVSPrint (Buffer, ENTS_MAX_BUFFER_SIZE * 4 * 8, Format, Marker);
  VA_END (Marker);

  if (*ResultBuffer == NULL) {
    Size          = EntsStrLen (Buffer) * 2 + 4 + ENTS_MAX_BUFFER_SIZE * 4;
    *ResultBuffer = EntsAllocatePool (Size);
    if (*ResultBuffer == NULL) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in RecordMessage Status - EFI_OUT_OF_RESOURCES"));
      goto RecordMessageFail1;
    }
    (*ResultBuffer)[0]  = L'\0';
    *ResultBufferSize   = Size;
  }

  Size = EntsStrLen (*ResultBuffer) * 2 + EntsStrLen (Buffer) * 2 + 4;
  if ((*ResultBufferSize) < Size) {
    *ResultBuffer = EntsReallocatePool (*ResultBuffer, *ResultBufferSize, Size + ENTS_MAX_BUFFER_SIZE * 4);
    if (*ResultBuffer == NULL) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Error in RecordMessage Status - EFI_OUT_OF_RESOURCES"));
      goto RecordMessageFail2;
    }

    *ResultBufferSize = Size + ENTS_MAX_BUFFER_SIZE * 4;
  }

  EntsStrCat (*ResultBuffer, Buffer);
  EntsStrCat (*ResultBuffer, L"\n");

  EntsFreePool (Buffer);
  return EFI_SUCCESS;

RecordMessageFail2:
  if(*ResultBuffer != NULL) {
    EntsFreePool (*ResultBuffer);
  }
RecordMessageFail1:
  if (Buffer != NULL) {
    EntsFreePool (Buffer);
  }

  return EFI_OUT_OF_RESOURCES;
}
