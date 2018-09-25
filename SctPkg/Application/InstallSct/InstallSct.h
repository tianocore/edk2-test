/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  InstallSct.h

Abstract:

  The EFI SCT installation.

--*/

#ifndef _EFI_INSTALL_SCT_H_
#define _EFI_INSTALL_SCT_H_

//
// Includes
//

#include "Efi.h"
#include "SctLib.h"
#include "InstallSctDef.h"
#include "InstallSctSupport.h"
#include <Library/UefiBootServicesTableLib.h>

//
// Global definitions
//

#define INSTALL_SCT_1M                  (1024 * 1024)
#define INSTALL_SCT_FREE_SPACE          (1024 * 1024 * 100)
#define INSTALL_SCT_FREE_SPACE_MB       (INSTALL_SCT_FREE_SPACE / INSTALL_SCT_1M)

#define SCAN_SCT_MAX_FILE_SYSTEM        0xF
#define INSTALL_SCT_MAX_FILE_SYSTEM     (SCAN_SCT_MAX_FILE_SYSTEM * 2)
#define INSTALL_SCT_MAX_BACKUP          0xF

#define INSTALL_SCT_STARTUP_FILE        L"SctStartup.nsh"

typedef enum {
  BACKUP_POLICY_UNDEFINED = 0,
  BACKUP_POLICY_NONE,
  BACKUP_POLICY_BACKUP,
  BACKUP_POLICY_BACKUP_ALL,
  BACKUP_POLICY_REMOVE,
  BACKUP_POLICY_REMOVE_ALL,
} BACKUP_POLICY;

//
// Global variables
//

extern BACKUP_POLICY mBackupPolicy;

//
// External functions
//

EFI_STATUS
EFIAPI
InstallSct (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

#endif
