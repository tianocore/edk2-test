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
                                                                
  Copyright 2017 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++           

Module Name:

  EraseBlock.h

Abstract:

  Erase Block protocol from the UEFI specification.

--*/

#ifndef _ERASE_BLOCK_PROTOCOL_H_
#define _ERASE_BLOCK_PROTOCOL_H_

#define EFI_ERASE_BLOCK_PROTOCOL_GUID \
  { \
    0x95a9a93e, 0xa86e, 0x4926, { 0xaa, 0xef, 0x99, 0x18, 0xe7, 0x72, 0xd9, 0x87 } \
  }

typedef struct _EFI_ERASE_BLOCK_PROTOCOL EFI_ERASE_BLOCK_PROTOCOL;

#define EFI_ERASE_BLOCK_PROTOCOL_REVISION ((2<<16) | (60))

///
/// EFI_ERASE_BLOCK_TOKEN
///
typedef struct {
  //
  // If Event is NULL, then blocking I/O is performed. If Event is not NULL and
  // non-blocking I/O is supported, then non-blocking I/O is performed, and
  // Event will be signaled when the erase request is completed.
  //
  EFI_EVENT             Event;
  //
  // Defines whether the signaled event encountered an error.
  //
  EFI_STATUS            TransactionStatus;
} EFI_ERASE_BLOCK_TOKEN;

/**
  Erase a specified number of device blocks.

  @param[in]       This           Indicates a pointer to the calling context.
  @param[in]       MediaId        The media ID that the erase request is for.
  @param[in]       LBA            The starting logical block address to be
                                  erased. The caller is responsible for erasing
                                  only legitimate locations.
  @param[in, out]  Token          A pointer to the token associated with the
                                  transaction.
  @param[in]       Size           The size in bytes to be erased. This must be
                                  a multiple of the physical block size of the
                                  device.

  @retval EFI_SUCCESS             The erase request was queued if Event is not
                                  NULL. The data was erased correctly to the
                                  device if the Event is NULL.to the device.
  @retval EFI_WRITE_PROTECTED     The device cannot be erased due to write
                                  protection.
  @retval EFI_DEVICE_ERROR        The device reported an error while attempting
                                  to perform the erase operation.
  @retval EFI_INVALID_PARAMETER   The erase request contains LBAs that are not
                                  valid.
  @retval EFI_NO_MEDIA            There is no media in the device.
  @retval EFI_MEDIA_CHANGED       The MediaId is not for the current media.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_ERASE) (
  IN     EFI_ERASE_BLOCK_PROTOCOL      *This,
  IN     UINT32                        MediaId,
  IN     EFI_LBA                       LBA,
  IN OUT EFI_ERASE_BLOCK_TOKEN         *Token,
  IN     UINTN                         Size
  );

///
/// The EFI Erase Block Protocol provides the ability for a device to expose
/// erase functionality. This optional protocol is installed on the same handle
/// as the EFI_BLOCK_IO_PROTOCOL or EFI_BLOCK_IO2_PROTOCOL.
///
struct _EFI_ERASE_BLOCK_PROTOCOL {
  //
  // The revision to which the EFI_ERASE_BLOCK_PROTOCOL adheres. All future
  // revisions must be backwards compatible. If a future version is not
  // backwards compatible, it is not the same GUID.
  //
  UINT64                     Revision;
  //
  // Returns the erase length granularity as a number of logical blocks. A
  // value of 1 means the erase granularity is one logical block.
  //
  UINT32                     EraseLengthGranularity;
  EFI_BLOCK_ERASE            EraseBlocks;
};

extern EFI_GUID gBlackBoxEfiEraseBlockProtocolGuid;

#endif