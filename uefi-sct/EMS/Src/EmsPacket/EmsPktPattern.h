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
  
    EmsPktPattern.h
    
Abstract:

    Incude header files for packet validate pattern

--*/

#ifndef __PATTERN_H__
#define __PATTERN_H__

#include "EmsTypes.h"
#include "EmsProtocols.h"

BOOLEAN
Validate (
  INT8    *Pattern,
  FIELD_T *Unpack
  )
/*++

Routine Description:

  The main process of validate

Arguments:

  Pattern - The pattern validation
  Unpack  - The Data

Returns:

  Calculated result.

--*/
;

#endif
