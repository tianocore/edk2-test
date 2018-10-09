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
  
    EmsRivlNameScope.h
    
Abstract:

    Incude header files for RIVL namescope related functions

--*/

#ifndef _EMS_RIVL_NAMESCOPE_H_
#define _EMS_RIVL_NAMESCOPE_H_

#include "EmsMain.h"
#include "EmsTypes.h"
#include "EmsTclInit.h"
#include "EmsUtilityString.h"
#include "EmsLogCommand.h"

#define SCOPE_STACK_DEPTH 512
#define MAX_SCOPENAME_LEN 128

typedef struct _RIVL_SCOPE {
  INT8  Name[MAX_SCOPENAME_LEN];  // name
} RIVL_SCOPE;

extern RIVL_SCOPE *RivlScopes[SCOPE_STACK_DEPTH];
extern UINT32     ScopeDepth;

VOID
EmsClearLocalScope(
  VOID
  )
/*++

Routine Description:

  Clear all local scope

Arguments:

  None

Returns:

  None

--*/
;

#endif
