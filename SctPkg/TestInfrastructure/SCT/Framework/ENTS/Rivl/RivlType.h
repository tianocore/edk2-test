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

  RivlType.h

Abstract:

  Remote Interface Validation Language Type implementation

--*/

#ifndef __RIVL_TYPE_H__
#define __RIVL_TYPE_H__

EFI_STATUS
AddRivlType (
  IN CHAR16                    *Type,
  IN UINT32                    Size,
  IN UINT32                    MemberNumber,
  IN RIVL_MEMBER               *RivlMember
  )
/*++

Routine Description:

  This func is to add RivlType to gRivlTypeList.

Arguments:

  Type          - Type of RivlType.
  Size          - Size of RivlType.
  MemberNumber  - MemberNumber of RivlType.
  RivlMember    - Pointer to the RivlMember of RivlType.

Returns:

  EFI_ALREADY_STARTED   - Rivil type already existed.
  EFI_OUT_OF_RESOURCES  - Memory allocation failed.
  EFI_SUCCESS           - Operation succeeded.

--*/
;

EFI_STATUS
DelRivlType (
  IN CHAR16                    *Type
  )
/*++

Routine Description:

  This func is to delete RivlType from gRivlTypeList.

Arguments:

  Type  - Type of RivlType.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_NOT_FOUND         - The specified type cannot be found.
  EFI_SUCCESS           - Operation succeeded.

--*/
;

EFI_STATUS
DelRivlAllType (
  VOID
  )
/*++

Routine Description:

  This func is to delete all RivlType from gRivlTypeList

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

#endif // __RIVL_TYPE_H__
