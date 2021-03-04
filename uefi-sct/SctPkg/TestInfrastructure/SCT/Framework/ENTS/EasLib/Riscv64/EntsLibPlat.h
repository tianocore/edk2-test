/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, ARM Ltd. All rights reserved.<BR>
  Copyright (c) 2021 Hewlett Packard Enterprise Development LP. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EntsLibPlat.h

Abstract:

  RISCV64 specific defines

--*/

#ifndef _EFI_LIB_PLAT_H_
#define _EFI_LIB_PLAT_H_

#define MIN_ALIGNMENT_SIZE  8

VOID
EntsInitializeLibPlatform (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
/*++

Routine Description:

  Initialize platform.

Arguments:

  ImageHandle           - The image handle.
  SystemTable           - The system table.

Returns:

  None.

--*/
;

#endif
