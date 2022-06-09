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

  DevicePathFromTextBBTestMain.h

Abstract:

  BB test header file of Device Path From Text protocol

--*/

#ifndef _DEVICE_PATH_FROM_TEXT_BBTEST_H_
#define _DEVICE_PATH_FROM_TEXT_BBTEST_H_

#include <Base.h>
#include "SctLib.h"
#include <UEFI/Protocol/DevicePathFromText.h>
#include <UEFI/Protocol/DevicePathUtilities.h>
#include <UEFI/Protocol/DevicePathToText.h>
#include "Guid.h"
#include <Library/EfiTestLib.h>

#define DEVICE_PATH_PROTOCOL_TEST_REVISION  0x00010001

EFI_STATUS
EFIAPI
InitializeBBTestDevicePathFromTextProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestDevicePathFromTextProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//
EFI_STATUS
EFIAPI
DevicePathFromTextConvertTextToDeviceNodeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathFromTextConvertTextToDevicePathFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathFromTextConvertTextToDeviceNodeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathFromTextConvertTextToDevicePathConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathFromTextConvertTextToDeviceNodeCoverageTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathFromTextConvertTextToDevicePathCoverageTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Other function declaration section
//
//
// Entry GUIDs
//
#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICENODEFROMTEXT_FUNCTION_GUID \
  { \
    0x5cb6c4b1, 0x9a66, 0x49c4, \
    { \
      0xa9, 0xbf, 0x5e, 0xc1, 0x2, 0x1d, 0x3c, 0xbc \
    } \
  }

#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICEPATHFROMTEXT_FUNCTION_GUID \
  { \
    0x8e08526d, 0x57f9, 0x4b24, \
    { \
      0xb4, 0x92, 0x55, 0xdb, 0xbd, 0x8c, 0x98, 0x7a \
    } \
  }

#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICENODEFROMTEXT_CONFORMANCE_GUID \
  { \
    0xb09f3cab, 0x144d, 0x4111, \
    { \
      0xa3, 0x91, 0x62, 0x73, 0xaf, 0x5e, 0x3, 0x86 \
    } \
  }

#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICEPATHFROMTEXT_CONFORMANCE_GUID \
  { \
    0x26f7a7b7, 0xa851, 0x401b, \
    { \
      0x80, 0xc0, 0x1b, 0xde, 0xea, 0xd8, 0xe0, 0x5c \
    } \
  }

#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICENODEFROMTEXT_COVERAGE_GUID \
  { \
    0x5befac81, 0x4bf3, 0x4ff9, \
    { \
      0xb2, 0x24, 0xaa, 0xe3, 0x26, 0xc4, 0xb3, 0xb5 \
    } \
  }

#define DEVICE_PATH_FROM_TEXT_PROTOCOL_CONVERTDEVICEPATHFROMTEXT_COVERAGE_GUID \
  { \
    0xfa8223ce, 0x39d, 0x4886, \
    { \
      0x8a, 0x9f, 0x69, 0xd4, 0x87, 0xc3, 0x6a, 0x9d \
    } \
  }

#endif
