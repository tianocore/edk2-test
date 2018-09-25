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

  DevicePathToTextProtocol.h

Abstract:

--*/

#ifndef _DEVICE_PATH_TO_TEXT_PROTOCOL_H_
#define _DEVICE_PATH_TO_TEXT_PROTOCOL_H_

typedef EFI_DEVICE_PATH_PROTOCOL  EFI_DEVICE_PATH;

#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID \
  { \
    0x8b843e20, 0x8132, 0x4852, 0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c \
  }

typedef CHAR16 * (EFIAPI *EFI_DEVICE_PATH_TO_TEXT_NODE)
  (
    IN CONST EFI_DEVICE_PATH *DeviceNode,
    IN BOOLEAN DisplayOnly,
    IN BOOLEAN AllowShortcuts
  );

typedef CHAR16 * (EFIAPI *EFI_DEVICE_PATH_TO_TEXT_PATH)
  (
    IN CONST EFI_DEVICE_PATH *DevicePath,
    IN BOOLEAN DisplayOnly,
    IN BOOLEAN AllowShortcuts
  );

typedef struct _EFI_DEVICE_PATH_TO_TEXT_PROTOCOL {
  EFI_DEVICE_PATH_TO_TEXT_NODE  ConvertDeviceNodeToText;
  EFI_DEVICE_PATH_TO_TEXT_PATH  ConvertDevicePathToText;
} EFI_DEVICE_PATH_TO_TEXT_PROTOCOL;

extern EFI_GUID gBlackBoxEfiDevicePathToTextProtocolGuid;

#endif /* _DEVICE_PATH_TO_TEXT_PROTOCOL_H_ */
