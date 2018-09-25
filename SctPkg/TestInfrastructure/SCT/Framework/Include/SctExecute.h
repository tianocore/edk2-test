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

  SctExecute.h

Abstract:

  This file provides the test execution services.

--*/

#ifndef _EFI_SCT_EXECUTE_H_
#define _EFI_SCT_EXECUTE_H_

//
// External functions declaration
//

//
// Execution services
//

EFI_STATUS
SctExecutePrepare (
  VOID
  );

EFI_STATUS
SctExecuteStart (
  VOID
  );

EFI_STATUS
SctExecute (
  VOID
  );

EFI_STATUS
SctContinueExecute (
  VOID
  );

//
// Reset services
//

EFI_STATUS
RemoveRecoveryFile (
  VOID
  );

EFI_STATUS
ResetAllTestResults (
  VOID
  );

EFI_STATUS
RemoveFile (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FileName
  );


#endif
