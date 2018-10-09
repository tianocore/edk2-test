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
  
    EmsPktCreate.h
    
Abstract:

    Data definition for packet create function

--*/

#ifndef __EMS_CREATE_H__
#define __EMS_CREATE_H__

#include "EmsTypes.h"
#include "EmsProtocols.h"
#include "EmsTclInit.h"

extern
VOID_P
CreateTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None.

--*/
;

extern
EMS_STATUS
GetValueByName (
  FIELD_T    *Field,
  INT32      Argc,
  INT8       *Argv[]
  )
/*++

Routine Description:

  Get value through name string.

Arguments:

  Field       - Field context.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  EMS_STATUS status code to indicate success or failure operation.

--*/
;

#endif
