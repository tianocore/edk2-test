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

  DevicePathUtilitiesProtocol.h

Abstract:

--*/

#ifndef _DEVICE_PATH_UTILITIES_PROTOCOL_H_
#define _DEVICE_PATH_UTILITIES_PROTOCOL_H_

#define EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID \
  { \
    0x379be4e, 0xd706, 0x437d, {0xb0, 0x37, 0xed, 0xb8, 0x2f, 0xb7, 0x72, 0xa4 } \
  }

typedef EFI_DEVICE_PATH_PROTOCOL  EFI_DEVICE_PATH;

typedef
UINTN
(EFIAPI *EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE) (
  IN CONST EFI_DEVICE_PATH* DevicePath
  );

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH) (IN CONST EFI_DEVICE_PATH *DevicePath);

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_PATH)
  (
    IN CONST EFI_DEVICE_PATH *Src1,
    IN CONST EFI_DEVICE_PATH *Src2
  );

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_NODE)
  (
    IN CONST EFI_DEVICE_PATH *DevicePath,
    IN CONST EFI_DEVICE_PATH *DeviceNode
  );

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE)
  (
    IN CONST EFI_DEVICE_PATH *DevicePath,
    IN CONST EFI_DEVICE_PATH *DevicePathInstance
  );

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE)
  (
    IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePathInstance,
    OUT UINTN *DevicePathInstanceSize
  );

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_CREATE_NODE)
  (
    IN UINT8 NodeType,
    IN UINT8 NodeSubType,
    IN UINT16 NodeLength
  );

typedef
BOOLEAN
(EFIAPI *EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE) (
  IN CONST EFI_DEVICE_PATH* DevicePath
  );

typedef struct _EFI_DEVICE_PATH_UTILITIES_PROTOCOL {
  EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE  GetDevicePathSize;
  EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH       DuplicateDevicePath;
  EFI_DEVICE_PATH_UTILS_APPEND_PATH           AppendDevicePath;
  EFI_DEVICE_PATH_UTILS_APPEND_NODE           AppendDeviceNode;
  EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE       AppendDevicePathInstance;
  EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE     GetNextDevicePathInstance;
  EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE     IsDevicePathMultiInstance;
  EFI_DEVICE_PATH_UTILS_CREATE_NODE           CreateDeviceNode;
} EFI_DEVICE_PATH_UTILITIES_PROTOCOL;

#endif
