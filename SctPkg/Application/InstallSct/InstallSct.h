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
InstallSct (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  );

#endif
