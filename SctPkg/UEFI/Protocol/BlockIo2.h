/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2011 - 2016, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  BlockIo2Protocol.h

Abstract:

  Block I/O 2 Protocol (define according to the EFI Spec 2.3.1 )

--*/

#ifndef _EFI_BLOCK_IO2_FOR_TEST_H_
#define _EFI_BLOCK_IO2_FOR_TEST_H_

#include <UEFI/Protocol/BlockIo.h>

#define EFI_BLOCK_IO2_PROTOCOL_GUID \
  { 0xa77b2472, 0xe282, 0x4e9f, {0xa2, 0x45, 0xc2, 0xc0, 0xe2, 0x7b, 0xbc, 0xc1 }}

typedef struct _EFI_BLOCK_IO2_PROTOCOL EFI_BLOCK_IO2_PROTOCOL;;

typedef struct { 
  EFI_EVENT             Event;
  EFI_STATUS            TransactionStatus;
} EFI_BLOCK_IO2_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_RESET_EX) (
  IN EFI_BLOCK_IO2_PROTOCOL   *This,
  IN BOOLEAN                  ExtendedVerification
  );

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_READ_EX) (
  IN EFI_BLOCK_IO2_PROTOCOL     *This,
  IN UINT32                     MediaId,
  IN EFI_LBA                    LBA,
  IN OUT EFI_BLOCK_IO2_TOKEN    *Token,
  IN UINTN                      BufferSize,
  OUT VOID                      *Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_WRITE_EX) (
  IN EFI_BLOCK_IO2_PROTOCOL     *This,
  IN UINT32                     MediaId,
  IN EFI_LBA                    LBA,
  IN OUT EFI_BLOCK_IO2_TOKEN	*Token,
  IN UINTN                      BufferSize,
  IN VOID                       *Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_FLUSH_EX) (
  IN EFI_BLOCK_IO2_PROTOCOL      *This,
  IN OUT EFI_BLOCK_IO2_TOKEN	 *Token
  );

struct _EFI_BLOCK_IO2_PROTOCOL {
  EFI_BLOCK_IO_MEDIA        *Media;
  EFI_BLOCK_RESET_EX        Reset;
  EFI_BLOCK_READ_EX         ReadBlocksEx;
  EFI_BLOCK_WRITE_EX        WriteBlocksEx;
  EFI_BLOCK_FLUSH_EX        FlushBlocksEx;
};


extern EFI_GUID                           gBlackBoxEfiBlockIo2ProtocolGuid;

#endif
