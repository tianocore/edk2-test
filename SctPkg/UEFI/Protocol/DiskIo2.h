/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2016, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  DiskIo2Protocol.h

Abstract:

  Disk I/O2 Protocol (define according to the EFI Spec 2.4 )

--*/

#ifndef _EFI_DISK_IO2_FOR_TEST_H_
#define _EFI_DISK_IO2_FOR_TEST_H_

#include <UEFI/Protocol/DiskIo.h>

#define EFI_DISK_IO2_PROTOCOL_GUID \
  { 0x151c8eae, 0x7f2c, 0x472c, {0x9e, 0x54, 0x98, 0x28, 0x19, 0x4f, 0x6a, 0x88 }}

typedef struct _EFI_DISK_IO2_PROTOCOL EFI_DISK_IO2_PROTOCOL;;

typedef struct {
  EFI_EVENT 					Event;
  EFI_STATUS 					TransactionStatus;
} EFI_DISK_IO2_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_CANCEL_EX) (
  IN EFI_DISK_IO2_PROTOCOL 			*This
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_READ_EX) (
  IN EFI_DISK_IO2_PROTOCOL 			*This,
  IN UINT32 						MediaId,
  IN UINT64 						Offset,
  IN OUT EFI_DISK_IO2_TOKEN 		*Token,
  IN UINTN 							BufferSize,
  OUT VOID 							*Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_WRITE_EX) (
  IN EFI_DISK_IO2_PROTOCOL 			*This,
  IN UINT32 						MediaId,
  IN UINT64 						Offset,
  IN OUT EFI_DISK_IO2_TOKEN 		*Token,
  IN UINTN 							BufferSize,
  IN VOID 							*Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_FLUSH_EX) (
  IN EFI_DISK_IO2_PROTOCOL 			*This,
  IN UINT32 						MediaId,
  IN UINT64 						Offset,
  IN OUT EFI_DISK_IO2_TOKEN 		*Token
);

typedef struct _EFI_DISK_IO2_PROTOCOL {
  UINT64 Revision;
  EFI_DISK_CANCEL_EX 				Cancel;
  EFI_DISK_READ_EX 					ReadDiskEx;
  EFI_DISK_WRITE_EX 				WriteDiskEx;
  EFI_DISK_FLUSH_EX 				FlushDiskEx;
} EFI_DISK_IO2_PROTOCOL;

extern EFI_GUID                           gBlackBoxEfiDiskIo2ProtocolGuid;

#endif
