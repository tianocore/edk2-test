/** @file

  Copyright (c) 2022, Ventana Micro Systems Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

  RiscVBoot.h

Abstract:

  This UEFI protocol for RISC-V systems provides early information to the bootloaders or Operating
  Systems. Firmwares like EDK2/u-boot need to implement this protocol on RISC-V UEFI systems.
--*/

#ifndef _RISCV_BOOT_H_
#define _RISCV_BOOT_H_


//
// Global ID for the RISC-V Boot Protocol
//
#define RISCV_EFI_BOOT_PROTOCOL_GUID \
	{ 0xccd15fec, 0x6f73, 0x4eec, { 0x83, 0x95, 0x3e, 0x69, 0xe4, 0xb9, 0x40, 0xbf } }

typedef struct _RISCV_EFI_BOOT_PROTOCOL RISCV_EFI_BOOT_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_GET_BOOT_HARTID) (
  IN RISCV_EFI_BOOT_PROTOCOL    *This,
  OUT UINTN 			*BootHartId
  )
/*++

  Routine Description:
    This interface provides the hartid of the boot cpu.

  Arguments:
    This          - Protocol instance pointer.
    BootHartId    - Pointer to the variable receiving the hartid of the boot cpu.

  Returns:
    EFI_SUCCESS 	  - The boot hart id could be returned.
    EFI_INVALID_PARAMETER - This parameter is NULL or does not point to a valid
			    RISCV_EFI_BOOT_PROTOCOL implementation.
    EFI_INVALID_PARAMETER - BootHartId parameter is NULL.

--*/
;

//
// Interface structure for the RISC-V Boot Protocol
//
struct _RISCV_EFI_BOOT_PROTOCOL {
  UINTN    		Revision;
  EFI_GET_BOOT_HARTID  	GetBootHartId;
};

extern EFI_GUID gBlackBoxEfiRiscVBootProtocolGuid;

#endif
