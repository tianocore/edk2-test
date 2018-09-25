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

  DevicePathFromTextProtocol.h

Abstract:

--*/

#ifndef _DEVICE_PATH_FROM_TEXT_PROTOCOL_H_
#define _DEVICE_PATH_FROM_TEXT_PROTOCOL_H_

typedef EFI_DEVICE_PATH_PROTOCOL  EFI_DEVICE_PATH;

#define EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID \
  { \
    0x5c99a21, 0xc70f, 0x4ad2, 0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e \
  }

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_FROM_TEXT_NODE) (IN CONST CHAR16 *TextDeviceNode);

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_FROM_TEXT_PATH) (IN CONST CHAR16 *TextDevicePath);

typedef struct _EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL {
  EFI_DEVICE_PATH_FROM_TEXT_NODE  ConvertTextToDeviceNode;
  EFI_DEVICE_PATH_FROM_TEXT_PATH  ConvertTextToDevicePath;
} EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL;

extern EFI_GUID gBlackBoxEfiDevicePathFromTextProtocolGuid;

#endif
