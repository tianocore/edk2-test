/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DevicePathUtilitiesBBTestMain.h

Abstract:

  BB test header file of Device Path Utilities protocol

--*/

#ifndef _DEVICE_PATH_UTILITIES_BBTEST_H_
#define _DEVICE_PATH_UTILITIES_BBTEST_H_

#include "Efi.h"
#ifndef EFIARM
#include <UEFI/Protocol/DevicePathUtilities.h>
#else
#include EFI_PROTOCOL_DEFINITION (DevicePath)
typedef EFI_DEVICE_PATH_PROTOCOL  EFI_DEVICE_PATH; 

#include EFI_PROTOCOL_DEFINITION (DevicePathFromText)
#include EFI_PROTOCOL_DEFINITION (DevicePathToText)
#include EFI_PROTOCOL_DEFINITION (DevicePathUtilities)
#endif

#include "Guid.h"
#include <Library/EfiTestLib.h>

#define DEVICE_PATH_PROTOCOL_TEST_REVISION  0x00010001

EFI_STATUS
EFIAPI
InitializeBBTestDevicePathUtilitiesProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestDevicePathUtilitiesProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Function Interface test declaration section
//
EFI_STATUS
EFIAPI
DevicePathUtilitiesCreateDeviceNodeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesAppendDeviceNodeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesGetDevicePathSizeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesDuplicateDevicePathFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesAppendDevicePathFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesAppendDevicePathInstanceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesGetNextDevicePathInstanceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesIsDevicePathMultiInstanceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesCreateDeviceNodeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesAppendDeviceNodeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesAppendDevicePathConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesAppendDevicePathInstanceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesGetNextDevicePathInstanceConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesGetDevicePathSizeConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
DevicePathUtilitiesDuplicateDevicePathConformanceTest (
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
#define DEVICE_PATH_UTILITIES_PROTOCOL_CREATEDEVICENODE_FUNCTION_GUID \
  { \
    0xfda477c2, 0x3678, 0x4c81, \
    { \
      0xb3, 0x8, 0x62, 0x83, 0xf2, 0x48, 0xf2, 0x14 \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICENODE_FUNCTION_GUID \
  { \
    0xe80d2ccd, 0xcf48, 0x437c, \
    { \
      0x95, 0x59, 0xfb, 0x98, 0xd0, 0x99, 0x33, 0xca \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_GETDEVICEPATHSIZE_FUNCTION_GUID \
  { \
    0xea0908e7, 0x4a59, 0x4660, \
    { \
      0x9f, 0xf6, 0xb5, 0x7, 0x64, 0x36, 0x55, 0x91 \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_DUPLICATEDEVICEPATH_FUNCTION_GUID \
  { \
    0x615c73a8, 0x6e80, 0x4c9b, \
    { \
      0x80, 0xc5, 0x24, 0x2b, 0x23, 0x9b, 0x7, 0x25 \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATH_FUNCTION_GUID \
  { \
    0x1bcec639, 0x96e1, 0x4daf, \
    { \
      0x88, 0x6b, 0x85, 0x35, 0x89, 0x10, 0x7f, 0x4 \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATHINSTANCE_FUNCTION_GUID \
  { \
    0x71299e5e, 0xa094, 0x40dd, \
    { \
      0xa0, 0x43, 0xe7, 0x65, 0xf3, 0x58, 0xa3, 0xa6 \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_GETNEXTDEVICEPATHINSTANCE_FUNCTION_GUID \
  { \
    0x2a2c4286, 0x9b68, 0x4c46, \
    { \
      0xb7, 0xdd, 0xb3, 0x2b, 0x4b, 0x85, 0x9a, 0xd4 \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_ISDEVICEPATHMULTIINSTANCE_FUNCTION_GUID \
  { \
    0x57c31faf, 0xa85f, 0x45cd, \
    { \
      0x93, 0x4f, 0x75, 0x7c, 0x91, 0xa, 0x0, 0xfb \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_CREATEDEVICENODE_CONFORMANCE_GUID \
  { \
    0x6ffc463d, 0x16ee, 0x46df, \
    { \
      0xb9, 0x42, 0xf, 0xad, 0x75, 0xc9, 0x83, 0xc8 \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICENODE_CONFORMANCE_GUID \
  { \
    0x88203701, 0xb540, 0x407c, \
    { \
      0x97, 0xf0, 0xca, 0x8b, 0x2f, 0x87, 0x21, 0x80 \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATH_CONFORMANCE_GUID \
  { \
    0x91e4223c, 0xf958, 0x44cb, \
    { \
      0xa6, 0x5c, 0xc4, 0xfd, 0x44, 0x5c, 0xd1, 0x58 \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_APPENDDEVICEPATHINSTANCE_CONFORMANCE_GUID \
  { \
    0x5f7832c, 0xf274, 0x4d65, \
    { \
      0xb8, 0x69, 0x7b, 0x36, 0x1f, 0x7, 0x9e, 0xaa \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_GETNEXTDEVICEPATHINSTANCE_CONFORMANCE_GUID \
  { \
    0x3ddc0d17, 0x610e, 0x48ee, \
    { \
      0xb2, 0xb7, 0x5c, 0x10, 0xfa, 0xd2, 0xc8, 0xf5 \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_GETDEVICEPATHSIZE_CONFORMANCE_GUID \
  { \
    0xa2fbc1f0, 0x35c3, 0x42b9, \
    { \
      0xb8, 0x1f, 0x5b, 0x30, 0xe1, 0x4f, 0xff, 0x2e \
    } \
  }

#define DEVICE_PATH_UTILITIES_PROTOCOL_DUPLICATEDEVICEPATH_CONFORMANCE_GUID \
  { \
    0x74c9cd0a, 0x348e, 0x4ae4, \
    { \
      0x91, 0xa2, 0x77, 0x99, 0xe5, 0x43, 0x2b, 0xbd \
    } \
  }

#endif
