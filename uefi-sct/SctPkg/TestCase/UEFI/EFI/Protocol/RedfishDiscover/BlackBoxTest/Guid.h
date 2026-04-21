/** @file

  Copyright 2006 - 2026 Unified EFI, Inc.<BR>
  Copyright (c) 2026, AMD Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

 Module Name:

   Guid.h

 Abstract:

   GUIDs for EFI Redfish Discover Protocol test assertion.

--*/

//
// Conformance Assertion GUIDs
//

// GetNetworkInterfaceList() with NULL NumberOfNetworkInterfaces
#define EFI_TEST_REDFISH_DISCOVER_BBTESTCONFORMANCE_ASSERTION_001_GUID \
{ 0xa1b2c3d4, 0xe5f6, 0x4a01, { 0xb2, 0xc3, 0xd4, 0xe5, 0xf6, 0x07, 0x18, 0x29 } }

extern EFI_GUID gRedfishDiscoverBBTestConformanceAssertionGuid001;

// GetNetworkInterfaceList() with NULL NetworkInterfaces
#define EFI_TEST_REDFISH_DISCOVER_BBTESTCONFORMANCE_ASSERTION_002_GUID \
{ 0xb2c3d4e5, 0xf607, 0x4b12, { 0xc3, 0xd4, 0xe5, 0xf6, 0x07, 0x18, 0x29, 0x3a } }

extern EFI_GUID gRedfishDiscoverBBTestConformanceAssertionGuid002;

// AcquireRedfishService() with NULL Token
#define EFI_TEST_REDFISH_DISCOVER_BBTESTCONFORMANCE_ASSERTION_003_GUID \
{ 0xc3d4e5f6, 0x0718, 0x4c23, { 0xd4, 0xe5, 0xf6, 0x07, 0x18, 0x29, 0x3a, 0x4b } }

extern EFI_GUID gRedfishDiscoverBBTestConformanceAssertionGuid003;

// AcquireRedfishService() with Flags == 0
#define EFI_TEST_REDFISH_DISCOVER_BBTESTCONFORMANCE_ASSERTION_004_GUID \
{ 0xd4e5f607, 0x1829, 0x4d34, { 0xe5, 0xf6, 0x07, 0x18, 0x29, 0x3a, 0x4b, 0x5c } }

extern EFI_GUID gRedfishDiscoverBBTestConformanceAssertionGuid004;

// ReleaseRedfishService() with NULL List
#define EFI_TEST_REDFISH_DISCOVER_BBTESTCONFORMANCE_ASSERTION_005_GUID \
{ 0xe5f60718, 0x293a, 0x4e45, { 0xf6, 0x07, 0x18, 0x29, 0x3a, 0x4b, 0x5c, 0x6d } }

extern EFI_GUID gRedfishDiscoverBBTestConformanceAssertionGuid005;

// AcquireRedfishService() with Flags == EFI_REDFISH_DISCOVER_VALIDATION only (Mantis 2172)
#define EFI_TEST_REDFISH_DISCOVER_BBTESTCONFORMANCE_ASSERTION_006_GUID \
{ 0x4b5c6d7e, 0x8f90, 0x4a56, { 0x07, 0x18, 0x29, 0x3a, 0x4b, 0x5c, 0x6d, 0x7e } }

extern EFI_GUID gRedfishDiscoverBBTestConformanceAssertionGuid006;

// GetNetworkInterfaceList() with NULL ImageHandle (Mantis 2172)
#define EFI_TEST_REDFISH_DISCOVER_BBTESTCONFORMANCE_ASSERTION_007_GUID \
{ 0x5c6d7e8f, 0x90a1, 0x4b67, { 0x18, 0x29, 0x3a, 0x4b, 0x5c, 0x6d, 0x7e, 0x8f } }

extern EFI_GUID gRedfishDiscoverBBTestConformanceAssertionGuid007;

// AcquireRedfishService() with NULL ImageHandle (Mantis 2172)
#define EFI_TEST_REDFISH_DISCOVER_BBTESTCONFORMANCE_ASSERTION_008_GUID \
{ 0x6d7e8f90, 0xa1b2, 0x4c78, { 0x29, 0x3a, 0x4b, 0x5c, 0x6d, 0x7e, 0x8f, 0xa0 } }

extern EFI_GUID gRedfishDiscoverBBTestConformanceAssertionGuid008;

//
// Function Assertion GUIDs
//

// GetNetworkInterfaceList() returns valid interface list
#define EFI_TEST_REDFISH_DISCOVER_BBTESTFUNCTION_ASSERTION_001_GUID \
{ 0xf6071829, 0x3a4b, 0x4f56, { 0x07, 0x18, 0x29, 0x3a, 0x4b, 0x5c, 0x6d, 0x7e } }

extern EFI_GUID gRedfishDiscoverBBTestFunctionAssertionGuid001;

// GetNetworkInterfaceList() NumberOfNetworkInterfaces is consistent
#define EFI_TEST_REDFISH_DISCOVER_BBTESTFUNCTION_ASSERTION_002_GUID \
{ 0x0718293a, 0x4b5c, 0x4067, { 0x18, 0x29, 0x3a, 0x4b, 0x5c, 0x6d, 0x7e, 0x8f } }

extern EFI_GUID gRedfishDiscoverBBTestFunctionAssertionGuid002;

// AcquireRedfishService() with valid parameters
#define EFI_TEST_REDFISH_DISCOVER_BBTESTFUNCTION_ASSERTION_003_GUID \
{ 0x18293a4b, 0x5c6d, 0x4178, { 0x29, 0x3a, 0x4b, 0x5c, 0x6d, 0x7e, 0x8f, 0x90 } }

extern EFI_GUID gRedfishDiscoverBBTestFunctionAssertionGuid003;

// AbortAcquireRedfishService() basic call
#define EFI_TEST_REDFISH_DISCOVER_BBTESTFUNCTION_ASSERTION_004_GUID \
{ 0x293a4b5c, 0x6d7e, 0x4289, { 0x3a, 0x4b, 0x5c, 0x6d, 0x7e, 0x8f, 0x90, 0xa1 } }

extern EFI_GUID gRedfishDiscoverBBTestFunctionAssertionGuid004;

// ReleaseRedfishService() basic call
#define EFI_TEST_REDFISH_DISCOVER_BBTESTFUNCTION_ASSERTION_005_GUID \
{ 0x3a4b5c6d, 0x7e8f, 0x439a, { 0x4b, 0x5c, 0x6d, 0x7e, 0x8f, 0x90, 0xa1, 0xb2 } }

extern EFI_GUID gRedfishDiscoverBBTestFunctionAssertionGuid005;
