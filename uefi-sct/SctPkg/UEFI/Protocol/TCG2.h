/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2016, Intel Corporation. All rights reserved.<BR>
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

  TCG2.h

Abstract:

  EFI TCG Protocol

--*/


#ifndef __TCG2_PROTOCOL_H__
#define __TCG2_PROTOCOL_H__

//
// Global ID for the TCG2 Protocol
//
#define EFI_TCG2_PROTOCOL_GUID    \
   {0x607f766c, 0x7455, 0x42be, {0x93, 0x0b, 0xe4, 0xd7, 0x6d, 0xb2, 0x72, 0x0f}}

// Following defintions come from TCG2 Efi Protocol Spec
#define EFI_TCG2_BOOT_HASH_ALG_SHA1 0x00000001

#define EFI_TCG2_BOOT_HASH_ALG_SHA256 0x00000002

#define EFI_TCG2_BOOT_HASH_ALG_SHA384 0x00000004

#define EFI_TCG2_BOOT_HASH_ALG_SHA512 0x00000008

#define EFI_TCG2_BOOT_HASH_ALG_SM3_256 0x00000010

#define EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2 0x00000001

#define EFI_TCG2_EVENT_LOG_FORMAT_TCG_2 0x00000002

#define HASH_NUMBER 0x05
#define SHA1_DIGEST_SIZE    20
#define SHA256_DIGEST_SIZE  32
#define SHA384_DIGEST_SIZE  48
#define SHA512_DIGEST_SIZE  64
#define SM3_256_DIGEST_SIZE 32

typedef struct _EFI_TCG2_PROTOCOL EFI_TCG2_PROTOCOL;

typedef UINT32 EFI_TCG2_EVENT_LOG_BITMAP;

typedef UINT32 EFI_TCG2_EVENT_LOG_FORMAT;

typedef UINT32 EFI_TCG2_EVENT_ALGORITHM_BITMAP;

typedef UINT32 TCG_PCRINDEX;

typedef UINT32 TCG_EVENTTYPE;

// Following struct defintions come from TCG2 Efi Protocol Spec
typedef struct {
  UINT8 Major;
  UINT8 Minor;
} EFI_TCG2_VERSION;

typedef struct {
  UINT8 Size;
  EFI_TCG2_VERSION StructureVersion;
  EFI_TCG2_VERSION ProtocolVersion;
  EFI_TCG2_EVENT_ALGORITHM_BITMAP HashAlgorithmBitmap;
  EFI_TCG2_EVENT_LOG_BITMAP SupportedEventLogs;
  BOOLEAN TPMPresentFlag;
  UINT16 MaxCommandSize;
  UINT16 MaxResponseSize;
  UINT32 ManufacturerID;
  UINT32 NumberOfPcrBanks;
  EFI_TCG2_EVENT_ALGORITHM_BITMAP ActivePcrBanks;
} EFI_TCG2_BOOT_SERVICE_CAPABILITY;

typedef
EFI_STATUS
(EFIAPI *EFI_TCG2_GET_CAPABILITY) (
  IN EFI_TCG2_PROTOCOL *This,
  IN OUT EFI_TCG2_BOOT_SERVICE_CAPABILITY *ProtocolCapability
);

typedef
EFI_STATUS
(EFIAPI *EFI_TCG2_GET_EVENT_LOG) (
  IN EFI_TCG2_PROTOCOL *This,
  IN EFI_TCG2_EVENT_LOG_FORMAT EventLogFormat,
  OUT EFI_PHYSICAL_ADDRESS *EventLogLocation,
  OUT EFI_PHYSICAL_ADDRESS *EventLogLastEntry,
  OUT BOOLEAN *EventLogTruncated
);

// all structs except EFI_TCG2_BOOT_SERVICE_CAPABILITY are packed
#pragma pack(1)

typedef struct tdEFI_TCG2_EVENT_HEADER {
  UINT32 HeaderSize;
  UINT16 HeaderVersion;
  TCG_PCRINDEX PCRIndex;
  TCG_EVENTTYPE EventType;
} EFI_TCG2_EVENT_HEADER;

typedef struct tdEFI_TCG2_EVENT {
  UINT32 Size;
  EFI_TCG2_EVENT_HEADER Header;
  UINT8 Event[];
} EFI_TCG2_EVENT;

typedef union {
  UINT8 sha1[SHA1_DIGEST_SIZE];
  UINT8 sha256[SHA256_DIGEST_SIZE];
  UINT8 sm3_256[SM3_256_DIGEST_SIZE];
  UINT8 sha384[SHA384_DIGEST_SIZE];
  UINT8 sha512[SHA512_DIGEST_SIZE];
} TPMU_HA;

typedef struct {
  UINT16     hashAlg;
  TPMU_HA    digest;
} TPMT_HA;

typedef struct tdTPML_DIGEST_VALUES {
  UINT32 Count;                    // number of digests
  TPMT_HA Digests[HASH_NUMBER];    // Count digests
} TPML_DIGEST_VALUES;

// This Declaration is for parsing the eventlog header which is defined to be 20 bytes in TCG EFI Protocol Spec
typedef UINT8 TCG_DIGEST[20];

typedef struct tdTCG_PCR_EVENT2 {
  TCG_PCRINDEX PCRIndex;       // PCRIndex event extended to
  TCG_EVENTTYPE EventType;     // Type of event (see [2])
  TPML_DIGEST_VALUES Digests;  // List of digests extended to //PCRIndex
  UINT32 EventSize;            // Size of the event data
  UINT8 *Event;                // The event data
} TCG_PCR_EVENT2;

typedef struct tdTCG_PCR_EVENT {
  UINT32 PCRIndex; // PCRIndex event extended to
  UINT32 EventType; // Type of event (see EFI specs)
  TCG_DIGEST Digest; // Value extended into PCRIndex
  UINT32 EventSize; // Size of the event data
  UINT8 Event[0]; // The event data
} TCG_PCR_EVENT;
// Structure to be added to the Event Log

typedef struct tdTCG_EfiSpecIdEventAlgorithmSize {
  UINT16 algorithmId;
  UINT16 digestSize;
} TCG_EfiSpecIdEventAlgorithmSize;

typedef struct tdTCG_EfiSpecIdEventStruct {
   UINT8 signature[16];
   UINT32 platformClass;
   UINT8 specVersionMinor;
   UINT8 specVersionMajor;
   UINT8 specErrata;
   UINT8 uintnSize;
} TCG_EfiSpecIDEventStruct;

#pragma pack()

typedef
EFI_STATUS
(EFIAPI * EFI_TCG2_HASH_LOG_EXTEND_EVENT) (
  IN EFI_TCG2_PROTOCOL *This,
  IN UINT64 Flags,
  IN EFI_PHYSICAL_ADDRESS DataToHash,
  IN UINT64 DataToHashLen,
  IN EFI_TCG2_EVENT *EfiTcgEvent
);

typedef
EFI_STATUS
(EFIAPI *EFI_TCG2_SUBMIT_COMMAND) (
  IN EFI_TCG2_PROTOCOL *This,
  IN UINT32 InputParameterBlockSize,
  IN UINT8 *InputParameterBlock,
  IN UINT32 OutputParameterBlockSize,
  IN UINT8 *OutputParameterBlock
);

typedef
EFI_STATUS
(EFIAPI *EFI_TCG2_GET_ACTIVE_PCR_BANKS) (
  IN EFI_TCG2_PROTOCOL *This,
  OUT UINT32 *ActivePcrBanks
);

typedef
EFI_STATUS
(EFIAPI *EFI_TCG2_SET_ACTIVE_PCR_BANKS) (
  IN EFI_TCG2_PROTOCOL *This,
  IN UINT32 ActivePcrBanks
);

typedef
EFI_STATUS
(EFIAPI * EFI_TCG2_GET_RESULT_OF_SET_ACTIVE_PCR_BANKS) (
  IN EFI_TCG2_PROTOCOL *This,
  OUT UINT32 *OperationPresent,
  OUT UINT32 *Response
);

//
// Interface structure for the TCG2 Protocol
//
struct _EFI_TCG2_PROTOCOL {
  EFI_TCG2_GET_CAPABILITY GetCapability;
  EFI_TCG2_GET_EVENT_LOG GetEventLog;
  EFI_TCG2_HASH_LOG_EXTEND_EVENT HashLogExtendEvent;
  EFI_TCG2_SUBMIT_COMMAND SubmitCommand;
  EFI_TCG2_GET_ACTIVE_PCR_BANKS GetActivePcrBanks;
  EFI_TCG2_SET_ACTIVE_PCR_BANKS SetActivePcrBanks;
  EFI_TCG2_GET_RESULT_OF_SET_ACTIVE_PCR_BANKS GetResultOfSetActivePcrBanks;
};

extern EFI_GUID gEfiTcg2ProtocolGuid;

#endif
