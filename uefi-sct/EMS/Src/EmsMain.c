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
  
    EmsMain.c
    
Abstract:

    Implementation for main entry point of EMS

--*/

#include <stdlib.h>
#include "EmsTclInit.h"

#ifdef WITH_GUI
STATIC Tk_ArgvInfo ArgTable[] = {
   {"", TK_ARGV_END, },
};
#endif

INT32
main (
  INT32 Argc,
  INT8  *Argv[]
  )
/*++

Routine Description:

  EMS main entry point

Arguments:

  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  exit(0) or exit(1).

--*/
{
  Tcl_Interp  *Interp;

  Tcl_FindExecutable (Argv[0]);

  Interp = Tcl_CreateInterp ();
  if (Tcl_Init (Interp) == TCL_ERROR) {
    return TCL_ERROR;
  }

  EmsTestInterpInit(Interp);

#ifdef WITH_GUI
  Tk_Main (Argc, Argv, EmsGuiInterpInit);
#else
  Tcl_Main (Argc, Argv, EmsGuiInterpInit);
#endif

  exit (0);
}
