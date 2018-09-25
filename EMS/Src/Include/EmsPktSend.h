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
  
    EmsPktSend.h
    
Abstract:

    Incude header files for packet send

--*/

#ifndef __EMS_SEND_H__
#define __EMS_SEND_H__

#include "EmsTclInit.h"

VOID_P
SendTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet sending related TCL initialization routine.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

#endif
