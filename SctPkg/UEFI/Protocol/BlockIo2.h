/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2011 - 2012, Intel Corporation. All rights reserved.<BR>     
   
--*/
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
  { 0xa77b2472, 0xe282, 0x4e9f, 0xa2, 0x45, 0xc2, 0xc0, 0xe2, 0x7b, 0xbc, 0xc1 }

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
