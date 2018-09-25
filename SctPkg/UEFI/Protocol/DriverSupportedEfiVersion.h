/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DriverSupportedEfiVersionProtocol.h

Abstract:

  Driver Support Efi Version Protocol(define according to the UEFI Spec 2.1 )

--*/

#ifndef _DRIVER_SUPPORTED_EFI_VERSION_FOR_TEST_H_
#define _DRIVER_SUPPORTED_EFI_VERSION_FOR_TEST_H_

//#include EFI_PROTOCOL_DEFINITION (DebugSupport)

#define  EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_GUID  \
  { 0x5c198761, 0x16a8, 0x4e69, {0x97, 0x2c, 0x89, 0xd6, 0x79, 0x54, 0xf8, 0x1d }}

typedef struct _EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL;;


struct _EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL {
 UINT32               Length; 
 UINT32               FirmwareVersion; 
};

extern EFI_GUID    gBlackBoxEfiDriverSupportedEfiVersionProtocolGuid;

#endif
