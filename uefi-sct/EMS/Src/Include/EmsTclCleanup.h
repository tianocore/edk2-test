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
  
    EmsTclCleanup.h
    
Abstract:

    Incude header files for EMS TCL cleanup functions

--*/

#ifndef	__EMSTCLCLEANUP__
#define	__EMSTCLCLEANUP__

#include <tcl.h>
#include <EmsTypes.h>

typedef struct EmsTclResMngStruct {
  struct EmsTclResMngStruct *Next;
  VOID * (*CleanupFunc) (VOID *);
  VOID * Res;
}EmsTclResMng;

VOID
EmsTclResStackPush (
  EmsTclResMng *Mng
  )
/*++

Routine Description:

  Push a EMS TCL resource into stack

Arguments:

  Mng - The structure for the EMS TCL resource management

Returns:

  None

--*/
;

VOID
EmsTclResStackPop (
  EmsTclResMng **Mng
  )
/*++

Routine Description:

  Pop a EMS TCL resource from stack

Arguments:

  Mng - The structure for the EMS TCL resource management

Returns:

  None

--*/
;

VOID_P
ResTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS cleanup related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

STATIC Tcl_CmdProc EmsTclResCleanup;

#endif
