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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsRivlTclVar.h
    
Abstract:

    Incude header files for RIVL tcl variable related functions

--*/

#ifndef __EMS_RIVL_TCL_VAR_H__
#define __EMS_RIVL_TCL_VAR_H__
#include "EmsRivlMain.h"

RIVL_TCL_VARIABLES  *
RivlTclVarsFindByName (
  INT8                    *Name
  )
/*++

Routine Description:

  Find one group of Rivl TCL variables accroding to name

Arguments:

  Name  - The name of the group

Returns:

  return the pointer to the group of Rivl variables found

--*/
;

BOOLEAN
TclVarsExist (
  INT8                    *Name
  )
/*++

Routine Description:

  Check whether the group of TCL variable exists

Arguments:

  Name  - The name of the group

Returns:

  TRUE or FALSE

--*/
;

RIVL_TCL_VARIABLE   *
RivlTclVarFindByName (
  RIVL_TCL_VARIABLES    *Vars,
  INT8                  *Name
  )
/*++

Routine Description:

  Find a Rivl TCL variable accroding to name

Arguments:

  Name  - The name of the variable

Returns:

  return the pointer to the Rivl variable found

--*/
;

BOOLEAN
TclVarExist (
  RIVL_TCL_VARIABLES     *Vars,
  INT8                   *Name
  )
/*++

Routine Description:

  Check whether the TCL variable exists

Arguments:

  Name  - The name of the variable

Returns:

  TRUE or FALSE

--*/
;

BOOLEAN
RivlAddTclVarsByName (
  INT8  *Name
  )
/*++

Routine Description:

  Add TCL variable by RIVL variable name

Arguments:

  Name  - The RIVL variable name

Returns:

  TRUE or FALSE

--*/
;

BOOLEAN
RivlAddTclVarByName (
  INT8  *VarName,
  INT8  *TclVarName
  )
/*++

Routine Description:

  Add TCL variable by RIVL variable name and TCL variable name

Arguments:

  VarName      - The RIVL variable name
  TclVarName   - The TCL variable name

Returns:

  TRUE or FALSE

--*/
;

VOID_P
RivlRemoveTclVarsAll (
  Tcl_Interp        *Interp
  )
/*++

Routine Description:

  Remove all the TCL variables

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

VOID_P
RivlRemoveTclVarsByName (
  Tcl_Interp        *Interp,
  INT8              *Name
  )
/*++

Routine Description:

  Remove a TCL variable accroding to name

Arguments:

  Interp      - TCL intepreter.
  Name    - The variable name

Returns:

  None

--*/
;

BOOLEAN
RivlRemoveTclVars (
  Tcl_Interp          *Interp,
  RIVL_TCL_VARIABLES  *Vars
  )
/*++

Routine Description:

  Remove all the TCL variables

Arguments:

  Interp      - TCL intepreter.
  Vars    - The RIVL variables

Returns:

  TRUE

--*/
;

#endif
