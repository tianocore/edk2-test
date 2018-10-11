/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++           

Module Name:

  PartitionInfo.h

Abstract:

  Partition Info protocol from the UEFI specification.

--*/

#ifndef _PARTITION_INFO_PROTOCOL_H_
#define _PARTITION_INFO_PROTOCOL_H_

#include <IndustryStandard/Mbr.h>
#include <Uefi/UefiGpt.h>

#define EFI_PARTITION_INFO_PROTOCOL_GUID \
  { \
    0x8cf2f62c, 0xbc9b, 0x4821, {0x80, 0x8d, 0xec, 0x9e, 0xc4, 0x21, 0xa1, 0xa0} \
  }

#define EFI_UNUSED_ENTRY_GUID \
{ 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }
extern EFI_GUID gPartitionInfoEFIUnusedEntryGuid;
  
#define EFI_SYSTEM_PARTITION_GUID \
{ 0xc12a7328, 0xf81f, 0x11d2, { 0xba, 0x4b, 0x00, 0xa0, 0xc9, 0x3e, 0xc9, 0x3b } }
extern EFI_GUID gPartitionInfoEFISystemPartitionGuid;

#define EFI_PARTITION_CONTAINING_LEGACY_MBR_GUID \
{ 0x024dee41, 0x33e7, 0x11d3, { 0x9d, 0x69, 0x00, 0x08, 0xc7, 0x81, 0xf3, 0x9f } }
extern EFI_GUID gPartitionInfoEFIPartitionContainingLegacyMBRGuid;


#define EFI_PARTITION_INFO_PROTOCOL_REVISION     0x0001000
#define PARTITION_TYPE_OTHER                     0x00
#define PARTITION_TYPE_MBR                       0x01
#define PARTITION_TYPE_GPT                       0x02



#pragma pack(1)

///
/// Partition Information Protocol structure.
///
typedef struct {
  //
  // Set to EFI_PARTITION_INFO_PROTOCOL_REVISION.
  //
  UINT32                     Revision;
  //
  // Partition info type (PARTITION_TYPE_MBR, PARTITION_TYPE_GPT, or PARTITION_TYPE_OTHER).
  //
  UINT32                     Type;
  //
  // If 1, partition describes an EFI System Partition.
  //
  UINT8                      System;
  UINT8                      Reserved[7];
  union {
    ///
    /// MBR data
    ///
    MBR_PARTITION_RECORD     Mbr;
    ///
    /// GPT data
    ///
    EFI_PARTITION_ENTRY      Gpt;
  } Info;
} EFI_PARTITION_INFO_PROTOCOL;

#pragma pack()


extern EFI_GUID gBlackBoxEfiPartitionInfoProtocolGuid;

#endif