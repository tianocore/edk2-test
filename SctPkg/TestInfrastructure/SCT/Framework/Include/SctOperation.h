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

  SctOperation.h

Abstract:

  This file provides the main operations of SCT.

--*/

#ifndef _EFI_SCT_OPERATION_H_
#define _EFI_SCT_OPERATION_H_

//
// External functions declarations
//

EFI_STATUS
AttachFirstStageTestData (
  VOID
  );

EFI_STATUS
AttachSecondStageTestData (
  VOID
  );

EFI_STATUS
DoFirstStageOperations (
  VOID
  );

EFI_STATUS
DoSecondStageOperations (
  VOID
  );

EFI_STATUS
DoThirdStageOperations (
  VOID
  );

EFI_STATUS
DoPreOperationAll (
  VOID
  );
#endif
