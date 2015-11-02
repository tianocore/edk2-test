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

  RivlCall.c

Abstract:

  Remote Interface Validation Language Call implementation

--*/

#include "SctLib.h"
#include "Rivl.h"
#include "RivlCall.h"

//
// Internal Function
//
EFI_STATUS
RivlAssignFromVar (
  IN UINTN           *Arg,
  IN CHAR16          *Name,
  IN OUT UINTN       *ArgOffset
  );

EFI_STATUS
RivlAssignFromArg (
  IN UINTN           *Arg,
  IN CHAR16          *Name,
  IN OUT UINTN       *ArgOffset
  );

//
// Function implementation
//
EFI_STATUS
RivlCallRivlFunc (
  IN CHAR16                    *FuncBuf,
  IN OUT EFI_STATUS            *FuncStatus
  )
/*++

Routine Description:

  This func is attend to add RivlType to gRivlTypeList
  The format of the type buffer is :
    <FuncName> <Arg1> <Arg2> ...

Arguments:

  FuncBuf     - The buffer string of Func
  FuncStatus  - The return value of Func

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS           - Operation succeeded.

--*/
{
  RIVL_VARIABLE   *RivlVariable;
  UINT32          Offset;
  UINT32          Length;
  UINT32          ArrayNumber;
  VOID            *Type;
  UINT32          Feature;
  EFI_STATUS      Status;
  UINT8           **VarBaseAddress;
  CHAR16          *FuncName;
  CHAR16          *ArgBuffer;
  UINTN           ArgOffset;
  RIVL_CALL_FRAME RivlCallFrame;
  UINTN           Index;

  //
  // Conformance check
  //
  if (FuncBuf == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  SctSetMem (&RivlCallFrame, sizeof (RIVL_CALL_FRAME), 0);

  //
  // Seperate the FuncBuf
  //
  FuncName = strtok_line (FuncBuf, RIVL_SEP_SIG);
  Status = AdvancedSearchRivlVariable (
            FuncName,
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
    VarBaseAddress = (UINT8 **) &RivlVariable->Address;
  } else {
    VarBaseAddress = RivlVariable->Address;
  }

  if ((Feature & RIVL_VAR_FEATURE_ADDRESS) == RIVL_VAR_FEATURE_ADDRESS) {
    //
    // It it refrence
    //
    return EFI_INVALID_PARAMETER;
  } else {
    //
    // It it value
    //
    RivlCallFrame.FuncAddr = *VarBaseAddress + Offset;
  }

  Index = 0;
  while (TRUE) {
    ArgBuffer = strtok_line (NULL, RIVL_SEP_SIG);
    if (ArgBuffer == NULL) {
      break;
    }

    if ((ArgBuffer[0] == RIVL_ADD_SIG) || (ArgBuffer[0] == RIVL_PTR_SIG) || (ArgBuffer[0] == RIVL_VAL_SIG)) {
      Status = RivlAssignFromVar (&RivlCallFrame.Stack[Index], ArgBuffer, &ArgOffset);
    } else {
      Status = RivlAssignFromArg (&RivlCallFrame.Stack[Index], ArgBuffer, &ArgOffset);
    }

    if (EFI_ERROR (Status)) {
      RIVL_DEBUG ((L"Parse Arg - %s, Status - %r\n", ArgBuffer, Status));
      break;
    }

    Index += ArgOffset;
  }

  RivlCallFrame.CallingType = 0;
  RivlCallFrame.Number      = Index;
  RivlCallFrame.StackTop    = &RivlCallFrame.Stack[0];
  RivlCallFrame.StackBottom = &RivlCallFrame.Stack[RivlCallFrame.Number - 1];
  //
  //  CallRivlFunc (&RivlCallFrame);
  //
  if (FuncStatus != NULL) {
    *FuncStatus = RivlCallFrame.Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
RivlAssignFromVar (
  IN UINTN           *Arg,
  IN CHAR16          *Name,
  IN OUT UINTN       *ArgOffset
  )
/*++

Routine Description:

  This func is attend to assign Function-Call Argument from Variable.

Arguments:

  Arg       - The Argument buffer.
  Name      - The Argument Name.
  ArgOffset - Assign Function-Call Argument successfully.

Returns:

  EFI_INVALID_PARAMETER - Invalide parameter.
  EFI_SUCCESS           - Operation succeeded.

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
    VarBaseAddress = (UINT8 **) &RivlVariable->Address;
  } else {
    VarBaseAddress = RivlVariable->Address;
  }

  *ArgOffset = 1;
  if ((Feature & RIVL_VAR_FEATURE_ADDRESS) == RIVL_VAR_FEATURE_ADDRESS) {
    //
    // It it refrence
    //
    *(VOID **) (Arg) = (VOID *) (*VarBaseAddress + Offset);
  } else {
    //
    // It it value
    //
    SctCopyMem (
      Arg,
      *VarBaseAddress + Offset,
      Length
      );

    //
    // Handle if Arg Length > sizeof(UINTN)
    //
    *ArgOffset += Length / sizeof (UINTN);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
RivlAssignFromArg (
  IN UINTN           *Arg,
  IN CHAR16          *Name,
  IN OUT UINTN       *ArgOffset
  )
/*++

Routine Description:

  This func is attend to assign Function-Call Argument from Argument.

Arguments:

  Arg       - The Argument buffer
  Name      - The Argument Name
  ArgOffset - The argument offset.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  CHAR16  *TmpName;

  StringToMem (Name, Arg, sizeof (UINTN));
  *ArgOffset  = 1;
  TmpName     = Name;

  //
  // Handle if Arg Length > sizeof(UINTN)
  //
  while (SctStrLen (TmpName) > sizeof (UINTN)) {
    StringToMem (TmpName + sizeof (UINTN), Arg + 1, sizeof (UINTN));
    *ArgOffset += 1;
    TmpName += sizeof (UINTN);
  }

  return EFI_SUCCESS;
}
