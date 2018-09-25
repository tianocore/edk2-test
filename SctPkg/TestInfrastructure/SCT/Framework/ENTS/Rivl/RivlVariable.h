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

  RivlVariable.h

Abstract:

  Remote Interface Validation Language Variable definitions

--*/

#ifndef __RIVL_VARIABLE_H__
#define __RIVL_VARIABLE_H__

EFI_STATUS
AddRivlVariable (
  IN CHAR16                    *Name,
  IN CHAR16                    *Type,
  IN UINT32                    TotalSize,
  IN UINT32                    ArrayNumber,
  IN UINT32                    Attribute
  )
/*++

Routine Description:

  This func is to add RivlVariable to gRivlVariableList.

Arguments:

  Name        - Type of RivlVariable.
  Type        - Type of RivlVariable.
  TotalSize   - TotalSize of RivlVariable.
  ArrayNumber - ArrayNumber of RivlVariable.
  Attribute   - Attribute of RivlVariable.

Returns:

  EFI_ALREADY_STARTED   - Rivil type already existed.
  EFI_OUT_OF_RESOURCES  - Memory allocation failed.
  EFI_INVALID_PARAMETER - Invalide parameter.
  EFI_SUCCESS           - Operation succeeded.
  
--*/
;

EFI_STATUS
DelRivlVariable (
  IN CHAR16                    *Name
  )
/*++

Routine Description:

  This func is to delete RivlVariable from gRivlVariableList.

Arguments:

  Name  - Type of RivlVariable.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_NOT_FOUND         - The specified type cannot be found.
  EFI_SUCCESS           - Operation succeeded.

--*/
;

EFI_STATUS
DelRivlAllVariable (
  VOID
  )
/*++

Routine Description:

  This func is to delete all RivlVariable from gRivlVariableList.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

#endif // __RIVL_VARIABLE_H__
