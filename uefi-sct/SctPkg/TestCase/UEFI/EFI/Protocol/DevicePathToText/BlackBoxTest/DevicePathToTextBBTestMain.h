/** @file

  Copyright 2006 - 2015 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DevicePathToTextBBTestMain.h

Abstract:

  BB test header file of Device Path To Text protocol

--*/

#ifndef _DEVICE_PATH_TO_TEXT_BBTEST_H_
#define _DEVICE_PATH_TO_TEXT_BBTEST_H_

#include <Base.h>
#include "SctLib.h"
#include <UEFI/Protocol/DevicePath.h>
#include <UEFI/Protocol/DevicePathUtilities.h>
#include <UEFI/Protocol/DevicePathFromText.h>
#include <UEFI/Protocol/DevicePathToText.h>
#include <UEFI/Protocol/DebugPort.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#include EFI_PROTOCOL_DEFINITION (DebugPort)
#include EFI_GUID_DEFINITION (PcAnsi)

#define DEVICE_PATH_PROTOCOL_TEST_REVISION  0x00010001

#define USB_CLASS_AUDIO            1
#define USB_CLASS_CDCCONTROL       2
#define USB_CLASS_HID              3
#define USB_CLASS_IMAGE            6
#define USB_CLASS_PRINTER          7
#define USB_CLASS_MASS_STORAGE     8
#define USB_CLASS_HUB              9
#define USB_CLASS_CDCDATA          10
#define USB_CLASS_SMART_CARD       11
#define USB_CLASS_VIDEO            14
#define USB_CLASS_DIAGNOSTIC       220
#define USB_CLASS_WIRELESS         224

#define USB_CLASS_RESERVE          254
#define USB_SUBCLASS_FW_UPDATE     1
#define USB_SUBCLASS_IRDA_BRIDGE   2
#define USB_SUBCLASS_TEST          3

typedef struct {
  CHAR16                    *DevicePathNodeText;
  EFI_DEVICE_PATH_PROTOCOL  * (*Function) (CHAR16 *);
} DEVICE_PATH_FROM_TEXT_TABLE;


EFI_STATUS
EFIAPI
InitializeBBTestDevicePathToTextProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestDevicePathToTextProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//
EFI_STATUS
EFIAPI
DevicePathToTextConvertDeviceNodeToTextFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathToTextConvertDevicePathToTextFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathToTextConvertDeviceNodeToTextConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathToTextConvertDevicePathToTextConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathToTextConvertDeviceNodeToTextCoverageTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathToTextConvertDevicePathToTextCoverageTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_DEVICE_PATH_PROTOCOL *
SctConvertTextToDeviceNode (
  IN CHAR16                *TextDevicePath
  );

EFI_DEVICE_PATH_PROTOCOL *
SctConvertTextToDevicePath (
  IN CHAR16 *TextDevicePath
  );

//
// Other function declaration section
//
//
// Entry GUIDs
//
#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICENODETOTEXT_FUNCTION_GUID \
  { \
    0xa9092653, 0xd44e, 0x407f, \
    { \
      0xa5, 0x1e, 0x94, 0xb, 0xe4, 0x77, 0xa, 0x26 \
    } \
  }

#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICEPATHTOTEXT_FUNCTION_GUID \
  { \
    0x1ab644ba, 0x1cb5, 0x4533, \
    { \
      0xb5, 0xcd, 0x30, 0x1e, 0xeb, 0x5c, 0x9, 0xd4 \
    } \
  }

#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICENODETOTEXT_CONFORMANCE_GUID \
  { \
    0x60e1b540, 0x3351, 0x455b, \
    { \
      0xb9, 0xf9, 0x86, 0x62, 0x5b, 0x7a, 0x15, 0x4e \
    } \
  }

#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICEPATHTOTEXT_CONFORMANCE_GUID \
  { \
    0xf8489292, 0x27f2, 0x4aa6, \
    { \
      0xa4, 0x33, 0x6d, 0x57, 0xa8, 0xb, 0x4a, 0x91 \
    } \
  }

#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICENODETOTEXT_COVERAGE_GUID \
  { \
    0xc843762a, 0x8d11, 0x46b8, \
    { \
      0x84, 0x17, 0x97, 0xa8, 0x92, 0x80, 0x9a, 0xb0 \
    } \
  }

#define DEVICE_PATH_TO_TEXT_PROTOCOL_CONVERTDEVICEPATHTOTEXT_COVERAGE_GUID \
  { \
    0xab54423, 0x22c5, 0x4391, \
    { \
      0xaf, 0x3a, 0x4, 0x8a, 0x4d, 0x4a, 0xfd, 0xe1 \
    } \
  }

extern EFI_GUID gDevicePathToTextBBTestVirtualDiskGuid;
extern EFI_GUID gDevicePathToTextBBTestVirtualCDGuid;
extern EFI_GUID gDevicePathToTextBBTestPresistentVirtualDiskGuid;
extern EFI_GUID gDevicePathToTextBBTestPresistentVirtualCDGuid;

#endif
