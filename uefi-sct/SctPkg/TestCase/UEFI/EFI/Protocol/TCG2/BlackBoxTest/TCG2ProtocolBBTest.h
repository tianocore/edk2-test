/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2013, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2021 - 2023, Arm Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:
    TCG2ProtocolBBTest.h

Abstract:
    head file of test driver of EFI TCG2 Protocol Test

--*/

#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/TCG2.h>
#include "Guid.h"

#define EFI_TCG2_TEST_REVISION 0x00010000

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Function Test
//
#define EFI_TCG2_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0x39ff9c71, 0x4b41, 0x4e5b, {0xae, 0xd7, 0x87, 0xc7, 0x94, 0x18, 0x7d, 0x67} }

#define EFI_TCG2_PROTOCOL_TEST_ENTRY_GUID0102 \
 {0x847f1ae0, 0xb429, 0x49f1, {0x9e, 0x0c, 0x8f, 0x43, 0xfb, 0x55, 0x34, 0x54} }

#define EFI_TCG2_PROTOCOL_TEST_ENTRY_GUID0103 \
 {0x907a7878, 0xb294, 0xf147, {0xe9, 0x0a, 0x65, 0x43, 0xab, 0x55, 0x76, 0x46} }

#define EFI_TCG2_PROTOCOL_TEST_ENTRY_GUID0104 \
 {0x9087ad78, 0x9ad2, 0x4172, {0x9a, 0xbc, 0x98, 0x23, 0x08, 0xf5, 0x6d, 0x26} }

#define EV_POST_CODE 0x01

#define EV_NO_ACTION 0x03

#define EFI_TCG2_EXTEND_ONLY 0x0000000000000001

#define PE_COFF_IMAGE 0x0000000000000010

// ST_NO_SESSION as defined in Table 19 of TPM Library Part 2: Structures
#define ST_NO_SESSIONS (UINT16) 0x8001

// TPM_RC_SUCCESS as defined in Table 16 of TPM Library Spec Part 2: Structures
#define TPM_RC_SUCCESS (UINT32) 0x0000000

// TPM_CC_Hash as defined in Table 12 of TPM Library Spec Part 2: Structures
#define TPM_CC_Hash    (UINT32)(0x0000017D)

#define TPM_RH_NULL    (UINT32) 0x40000007

#define TPM_ALG_SHA256 (UINT16) 0x000B

#define SHA256_LENGTH (UINT16) 0x0020

#pragma pack(1)
// TPM2B_MAX_BUFFER as defined in Table 86 of TPM Library Spec Part 2: Structures
// Size of buffer in spec is variable length, but hash test will always use a fixed length string
// of length 43
#define TEST_STRING_LEN 43
typedef struct {
  UINT16 size;
  UINT8  buffer[TEST_STRING_LEN];
} TPM2B_MAX_BUFFER;

// TPM2B_DIGEST as defined in Table 73 of TPM Library Spec Part 2: Structures
typedef struct {
  UINT16 size;
  UINT8  digest[32];  // Size of buffer in spec is defined to be variable length but for this test will always be 32
} TPM2B_DIGEST;

typedef struct {
  UINT16           tag;
  UINT32           hierarchy;
  UINT16           digest;  // Size of buffer in spec is defined to be variable length but for this test will always be UINT16
} TPMT_TK_HASHCHECK;

// TPM2_Hash command Structure as defined in Section 15.4 of TPM Spec Part 3: Commands
typedef struct {
  UINT16 Tag;
  UINT32 CommandSize;
  UINT32 CommandCode;
  TPM2B_MAX_BUFFER data;
  UINT16 hashAlg;
  UINT32 hierarchy;
} TPM2_HASH_COMMAND;

// TPM2_Hash Response Structure as defined in Section 15.4 of TPM Spec Part 3: Commands
typedef struct {
  UINT16 Tag;
  UINT32 ResponseSize;
  UINT32 ResponseCode;
  TPM2B_DIGEST data;
  TPMT_TK_HASHCHECK validation;
} TPM2_HASH_RESPONSE;
#pragma pack()

EFI_STATUS
EFIAPI
BBTestTCG2ProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetActivePcrBanksConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetActivePcrBanksConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestHashLogExtendEventConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestHashLogExtendEventConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetEventLogConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetEventLogConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestSubmitCommandConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  );

EFI_STATUS
BBTestGetCapabilityConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestGetActivePcrBanksConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestHashLogExtendEventConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestSubmitCommandConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
