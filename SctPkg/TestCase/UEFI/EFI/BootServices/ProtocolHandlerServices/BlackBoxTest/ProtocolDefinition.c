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

  ProtocolDefinition.c

Abstract:

  Protocols that will be used during the Protocol Handler
    Boot Services Test

--*/
#include "Efi.h"
#include "ProtocolDefinition.h"

//
// module globals
//


EFI_GUID mTestProtocol1Guid = TEST_PROTOCOL_1_GUID;
EFI_GUID mTestProtocol2Guid = TEST_PROTOCOL_2_GUID;

EFI_GUID mInterfaceFunctionTestProtocol1Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_1_GUID;
EFI_GUID mInterfaceFunctionTestProtocol2Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_2_GUID;
EFI_GUID mInterfaceFunctionTestProtocol3Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_3_GUID;
EFI_GUID mInterfaceFunctionTestProtocol4Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_4_GUID;
EFI_GUID mInterfaceFunctionTestProtocol5Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_5_GUID;
EFI_GUID mInterfaceFunctionTestProtocol6Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_6_GUID;
EFI_GUID mInterfaceFunctionTestProtocol7Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_7_GUID;
EFI_GUID mInterfaceFunctionTestProtocol8Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_8_GUID;
EFI_GUID mInterfaceFunctionTestProtocol9Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_9_GUID;
EFI_GUID mInterfaceFunctionTestProtocol10Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_10_GUID;
EFI_GUID mInterfaceFunctionTestProtocol11Guid = INTERFACE_FUNCTION_TEST_PROTOCOL_11_GUID;

EFI_GUID mExternalDriverProtocol1Guid = EXTERNAL_DRIVER_PROTOCOL_1_GUID;

EFI_GUID mTestNoInterfaceProtocol1Guid = TEST_NO_INTERFACE_PROTOCOL_1_GUID;
EFI_GUID mTestNoInterfaceProtocol2Guid = TEST_NO_INTERFACE_PROTOCOL_2_GUID;

EFI_GUID mBusDriver3Guid = BUS_DRIVER_3_GUID;
EFI_GUID mPlatformOverrideDriver1Guid = PLATFORM_OVERRIDE_DRIVER_1_GUID;

EFI_GUID mVendorDevicePath1Guid = VENDOR_DEVICE_PATH_1_GUID;
EFI_GUID mVendorDevicePath2Guid = VENDOR_DEVICE_PATH_2_GUID;
EFI_GUID mVendorDevicePath3Guid = VENDOR_DEVICE_PATH_3_GUID;
EFI_GUID mVendorDevicePath4Guid = VENDOR_DEVICE_PATH_4_GUID;
EFI_GUID mVendorDevicePath5Guid = VENDOR_DEVICE_PATH_5_GUID;
EFI_GUID mVendorDevicePath6Guid = VENDOR_DEVICE_PATH_6_GUID;
EFI_GUID mVendorDevicePath7Guid = VENDOR_DEVICE_PATH_7_GUID;
EFI_GUID mVendorDevicePath8Guid = VENDOR_DEVICE_PATH_8_GUID;
EFI_GUID mVendorDevicePath9Guid = VENDOR_DEVICE_PATH_9_GUID;
EFI_GUID mVendorDevicePath10Guid = VENDOR_DEVICE_PATH_10_GUID;

