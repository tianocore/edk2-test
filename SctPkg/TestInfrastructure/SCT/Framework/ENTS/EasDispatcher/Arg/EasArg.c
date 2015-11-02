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

  EasArg.c

Abstract:

--*/

#include "SctLib.h"
#include "Eas.h"
#include "EfiTest.h"
#include EFI_TEST_PROTOCOL_DEFINITION (EntsMonitorProtocol)

EFI_STATUS
AssignFromVar (
  IN ENTS_ARG_FIELD  *ArgField,
  IN CHAR16          *Name
  );

EFI_STATUS
AssignFromArg (
  IN ENTS_ARG_FIELD  *ArgField,
  IN CHAR16          *Name
  );

EFI_STATUS
ParseArg (
  IN ENTS_ARG_FIELD  *ArgField
  )
/*++

Routine Description:

  Parse the argument list of remote calling.

Arguments:

  ArgField  - Argument list.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Operation failed.

--*/
{
  ENTS_ARG_FIELD  *Field;
  CHAR16          *ArgBuffer;
  EFI_STATUS      Status;

  Status    = EFI_SUCCESS;
  Field     = ArgField;
  ArgBuffer = strtok_line ((gEasFT->Cmd)->ComdArg, RIVL_SEP_SIG);
  for (; Field->Type != 0; Field++) {

    if (ArgBuffer == NULL) {
      break;
    }

    if ((ArgBuffer[0] == RIVL_ADD_SIG) || (ArgBuffer[0] == RIVL_PTR_SIG) || (ArgBuffer[0] == RIVL_VAL_SIG)) {
      Status = AssignFromVar (Field, ArgBuffer);
    } else {
      Status = AssignFromArg (Field, ArgBuffer);
    }

    if (EFI_ERROR (Status)) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"ParseArg(%s) Status-%r", ArgBuffer, Status));
      break;
    }

    ArgBuffer = strtok_line (NULL, RIVL_SEP_SIG);
  }

  return Status;
}

EFI_STATUS
AssignFromVar (
  IN ENTS_ARG_FIELD  *ArgField,
  IN CHAR16          *Name
  )
/*++

Routine Description:

  Assignment from specific variable.

Arguments:

  ArgField  - ArgField pointer.
  Name      - Variable name.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Some failure happened.
  
--*/
{
  RIVL_VARIABLE *RivlVariable;
  UINT32        Offset;
  UINT32        Length;
  UINT32        ArrayNumber;
  VOID          *Type;
  UINT32        Feature;
  EFI_STATUS    Status;
  UINT8         **VarBaseAddress;

  Status = AdvancedSearchRivlVariable (
            Name,
            &RivlVariable,
            &Offset,
            &Length,
            &ArrayNumber,
            &Type,
            &Feature
            );
  if (EFI_ERROR (Status)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((Feature & RIVL_VAR_FEATURE_POINTER) != RIVL_VAR_FEATURE_POINTER) {
    VarBaseAddress = (UINT8 **)&RivlVariable->Address;
  } else {
    VarBaseAddress = RivlVariable->Address;
  }
  //
  // It it refrence
  //
  if ((Feature & RIVL_VAR_FEATURE_ADDRESS) == RIVL_VAR_FEATURE_ADDRESS) {
    if (ArgField->Type != POINTER) {
      return EFI_INVALID_PARAMETER;
    }

    * (VOID **) (ArgField->Data) = (VOID *) (*VarBaseAddress + Offset);
    goto Done;
  }
  //
  // It it value
  //
  SctCopyMem (
    ArgField->Data,
    *VarBaseAddress + Offset,
    Length
    );

Done:
  return EFI_SUCCESS;
}

EFI_STATUS
AssignFromArg (
  IN ENTS_ARG_FIELD  *ArgField,
  IN CHAR16          *Name
  )
/*++

Routine Description:

  Assignment from specific pre-defined argument.

Arguments:

  ArgField  - ArgField pointer.
  Name      - Argument name.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_INVALID_PARAMETER - Some failure happened.

--*/
{
  switch (ArgField->Type) {
  case OCTET1:
    StringToMem (Name, ArgField->Data, sizeof (UINT8));
    break;

  case OCTET2:
    StringToMem (Name, ArgField->Data, sizeof (UINT16));
    break;

  case OCTET4:
    StringToMem (Name, ArgField->Data, sizeof (UINT32));
    break;

  case OCTET8:
    StringToMem (Name, ArgField->Data, sizeof (UINT64));
    break;

  case OCTETN:
    StringToMem (Name, ArgField->Data, sizeof (UINTN));
    break;

  case
BOOL:
    StringToMem (Name, ArgField->Data, sizeof (UINT8));
    break;

  case POINTER:
    if (SctStrCmp (Name, L"NULL") == 0) {
      *(VOID **) (ArgField->Data) = 0;
    } else {
      StringToMem (Name, ArgField->Data, sizeof (UINTN));
    }
    break;

  default:
    break;
  }

  return EFI_SUCCESS;
}
