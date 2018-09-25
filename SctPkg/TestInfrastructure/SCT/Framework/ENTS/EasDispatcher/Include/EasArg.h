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

  EasArg.h

Abstract:

--*/

#ifndef _EAS_ARG_H_
#define _EAS_ARG_H_

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
;

#endif
