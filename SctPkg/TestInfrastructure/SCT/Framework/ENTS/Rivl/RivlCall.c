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
