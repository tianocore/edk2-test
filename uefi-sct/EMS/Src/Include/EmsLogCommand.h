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
  
    EmsLogCommand.h
    
Abstract:

    Incude header files for log command

--*/

#ifndef __EMS_LOG_COMMAND_H__
#define __EMS_LOG_COMMAND_H__

#include <tcl.h>
#include <EmsTypes.h>

VOID_P
LogTclInit (
  IN Tcl_Interp   *Interp
  )
/*++

Routine Description:

  Log related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None.

--*/
;

VOID_P
LogCurrentCommand (
  IN INT32        Argc,
  IN CONST84 INT8 *Argv[]
  )
/*++

Routine Description:

  Log the argumems into runtime information.

Arguments:

  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  None.

--*/
;

#endif
