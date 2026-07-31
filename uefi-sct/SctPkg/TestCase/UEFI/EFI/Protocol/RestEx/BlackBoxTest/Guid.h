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

   GUIDs auto-generated for EFI REST EX Protocol test assertion.

--*/

//
// Conformance Assertion GUIDs
//

// GetService() with NULL RestExServiceInfo
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_001_GUID \
{ 0x3a1b2c4d, 0x5e6f, 0x4a7b, { 0x8c, 0x9d, 0x0e, 0x1f, 0x2a, 0x3b, 0x4c, 0x5d } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid001;

// GetModeData() with NULL RestExConfigData
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_002_GUID \
{ 0x4b2c3d5e, 0x6f70, 0x4b8c, { 0x9d, 0xae, 0x1f, 0x20, 0x3b, 0x4c, 0x5d, 0x6e } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid002;

// GetModeData() before Configure() returns EFI_NOT_READY
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_003_GUID \
{ 0x5c3d4e6f, 0x7081, 0x4c9d, { 0xae, 0xbf, 0x20, 0x31, 0x4c, 0x5d, 0x6e, 0x7f } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid003;

// Configure() with NULL RestExConfigData resets to unconfigured
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_004_GUID \
{ 0x6d4e5f70, 0x8192, 0x4dae, { 0xbf, 0xc0, 0x31, 0x42, 0x5d, 0x6e, 0x7f, 0x80 } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid004;

// SendReceive() with NULL RequestMessage
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_005_GUID \
{ 0x7e5f6081, 0x92a3, 0x4ebf, { 0xc0, 0xd1, 0x42, 0x53, 0x6e, 0x7f, 0x80, 0x91 } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid005;

// SendReceive() with NULL ResponseMessage
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_006_GUID \
{ 0x8f607192, 0xa3b4, 0x4fc0, { 0xd1, 0xe2, 0x53, 0x64, 0x7f, 0x80, 0x91, 0xa2 } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid006;

// AyncSendReceive() with NULL RestExToken
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_007_GUID \
{ 0x907182a3, 0xb4c5, 0x40d1, { 0xe2, 0xf3, 0x64, 0x75, 0x80, 0x91, 0xa2, 0xb3 } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid007;

// AyncSendReceive() before Configure() returns EFI_NOT_READY
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_008_GUID \
{ 0xa18293b4, 0xc5d6, 0x40e2, { 0xf3, 0x04, 0x75, 0x86, 0x91, 0xa2, 0xb3, 0xc4 } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid008;

// GetServiceTime() with NULL Time
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_009_GUID \
{ 0xb293a4c5, 0xd6e7, 0x41f3, { 0x04, 0x15, 0x86, 0x97, 0xa2, 0xb3, 0xc4, 0xd5 } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid009;

// GetServiceTime() before Configure() returns EFI_NOT_READY
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_010_GUID \
{ 0xc3a4b5d6, 0xe7f8, 0x4204, { 0x15, 0x26, 0x97, 0xa8, 0xb3, 0xc4, 0xd5, 0xe7 } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid010;

// EventService() with NULL RestExToken
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_011_GUID \
{ 0xd4b5c6e7, 0xf809, 0x4315, { 0x26, 0x37, 0xa8, 0xb9, 0xc4, 0xd5, 0xe6, 0xf8 } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid011;

// EventService() before Configure() returns EFI_NOT_READY
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_012_GUID \
{ 0xe5c6d7f8, 0x091a, 0x4426, { 0x37, 0x48, 0xb9, 0xca, 0xd5, 0xe6, 0xf7, 0x09 } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid012;

// SendReceive() before Configure() returns EFI_NOT_READY
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_013_GUID \
{ 0xf6d7e809, 0x1a2b, 0x4537, { 0x48, 0x59, 0xca, 0xdb, 0xe6, 0xf7, 0x08, 0x1a } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid013;

// AyncSendReceive() cancellation via NULL RequestMessage returns EFI_ABORTED (Mantis 1924)
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_014_GUID \
{ 0x07e8f91a, 0x2b3c, 0x4648, { 0x59, 0x6a, 0xdb, 0xec, 0xf7, 0x08, 0x19, 0x2b } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid014;

// AyncSendReceive() with zero timeout returns EFI_TIMEOUT (Mantis 1924)
#define EFI_TEST_REST_EX_BBTESTCONFORMANCE_ASSERTION_015_GUID \
{ 0x18f90a2b, 0x3c4d, 0x4759, { 0x6a, 0x7b, 0xec, 0xfd, 0x08, 0x19, 0x2a, 0x3c } }

extern EFI_GUID gRestExBBTestConformanceAssertionGuid015;

//
// Function Assertion GUIDs
//

// GetService() returns valid EFI_REST_EX_SERVICE_INFO
#define EFI_TEST_REST_EX_BBTESTFUNCTION_ASSERTION_001_GUID \
{ 0xb293a4c5, 0xd6e7, 0x40f3, { 0x04, 0x15, 0x86, 0x97, 0xa2, 0xb3, 0xc4, 0xd5 } }

extern EFI_GUID gRestExBBTestFunctionAssertionGuid001;

// GetService() returns valid service type
#define EFI_TEST_REST_EX_BBTESTFUNCTION_ASSERTION_002_GUID \
{ 0xc3a4b5d6, 0xe7f8, 0x4104, { 0x15, 0x26, 0x97, 0xa8, 0xb3, 0xc4, 0xd5, 0xe6 } }

extern EFI_GUID gRestExBBTestFunctionAssertionGuid002;

// Configure() with valid config data succeeds
#define EFI_TEST_REST_EX_BBTESTFUNCTION_ASSERTION_003_GUID \
{ 0xd4b5c6e7, 0xf809, 0x4215, { 0x26, 0x37, 0xa8, 0xb9, 0xc4, 0xd5, 0xe6, 0xf7 } }

extern EFI_GUID gRestExBBTestFunctionAssertionGuid003;

// Configure() with NULL resets to unconfigured
#define EFI_TEST_REST_EX_BBTESTFUNCTION_ASSERTION_004_GUID \
{ 0xe5c6d7f8, 0x091a, 0x4326, { 0x37, 0x48, 0xb9, 0xca, 0xd5, 0xe6, 0xf7, 0x08 } }

extern EFI_GUID gRestExBBTestFunctionAssertionGuid004;

// GetModeData() after Configure() returns valid data
#define EFI_TEST_REST_EX_BBTESTFUNCTION_ASSERTION_005_GUID \
{ 0xf6d7e809, 0x1a2b, 0x4437, { 0x48, 0x59, 0xca, 0xdb, 0xe6, 0xf7, 0x08, 0x19 } }

extern EFI_GUID gRestExBBTestFunctionAssertionGuid005;

// SendReceive() basic GET request
#define EFI_TEST_REST_EX_BBTESTFUNCTION_ASSERTION_006_GUID \
{ 0x07e8f91a, 0x2b3c, 0x4548, { 0x59, 0x6a, 0xdb, 0xec, 0xf7, 0x08, 0x19, 0x2a } }

extern EFI_GUID gRestExBBTestFunctionAssertionGuid006;

// GetServiceTime() returns valid time or EFI_UNSUPPORTED
#define EFI_TEST_REST_EX_BBTESTFUNCTION_ASSERTION_007_GUID \
{ 0x18f90a2b, 0x3c4d, 0x4659, { 0x6a, 0x7b, 0xec, 0xfd, 0x08, 0x19, 0x2a, 0x3b } }

extern EFI_GUID gRestExBBTestFunctionAssertionGuid007;

// AyncSendReceive() establishes async request
#define EFI_TEST_REST_EX_BBTESTFUNCTION_ASSERTION_008_GUID \
{ 0x290a1b3c, 0x4d5e, 0x476a, { 0x7b, 0x8c, 0xfd, 0x0e, 0x19, 0x2a, 0x3b, 0x4c } }

extern EFI_GUID gRestExBBTestFunctionAssertionGuid008;

// EventService() establishes event subscription
#define EFI_TEST_REST_EX_BBTESTFUNCTION_ASSERTION_009_GUID \
{ 0x3a1b2c4d, 0x5e6f, 0x487b, { 0x8c, 0x9d, 0x0e, 0x1f, 0x2a, 0x3b, 0x4c, 0x5e } }

extern EFI_GUID gRestExBBTestFunctionAssertionGuid009;

// AyncSendReceive() with timeout parameter (Mantis 1924)
#define EFI_TEST_REST_EX_BBTESTFUNCTION_ASSERTION_010_GUID \
{ 0x4b2c3d5e, 0x6f70, 0x498c, { 0x9d, 0xae, 0x1f, 0x20, 0x3b, 0x4c, 0x5d, 0x6f } }

extern EFI_GUID gRestExBBTestFunctionAssertionGuid010;

// AyncSendReceive() cancellation via NULL RequestMessage returns EFI_ABORTED (Mantis 1924)
#define EFI_TEST_REST_EX_BBTESTFUNCTION_ASSERTION_011_GUID \
{ 0x5c3d4e6f, 0x7081, 0x4a9d, { 0xae, 0xbf, 0x20, 0x31, 0x4c, 0x5d, 0x6e, 0x80 } }

extern EFI_GUID gRestExBBTestFunctionAssertionGuid011;
