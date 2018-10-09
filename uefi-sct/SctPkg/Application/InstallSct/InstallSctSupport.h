/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  InstallSctSupport.h

Abstract:

  This file provides the support services for the EFI SCT installation.

--*/

#ifndef _EFI_INSTALL_SCT_SUPPORT_H_
#define _EFI_INSTALL_SCT_SUPPORT_H_

#define SCT_FOLDER    (1 << 0)
#define SCT_STARTUP   (1 << 1)

typedef struct {
  CHAR16 Name[10];
  UINT64 FreeSpace;
  UINTN  IsSctPresent;
} SCT_FILE_VOLUME;

//
// External functions
//

EFI_STATUS
GetFreeSpace (
  IN OUT SCT_FILE_VOLUME *FileVolume
  );

EFI_STATUS
CopyFile (
  IN CHAR16             *SrcName,
  IN CHAR16             *DstName
  );

EFI_STATUS
CopyDir(
  IN CHAR16             *SrcName,
  IN CHAR16             *DstName
  );

EFI_STATUS
ProcessExistingSctFile (
  IN  CHAR16*         Name,
  IN  CHAR16*         FileName
  );

EFI_STATUS
CheckForInstalledSct (
  IN OUT SCT_FILE_VOLUME *FileVolume
  );

#endif
