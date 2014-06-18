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
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

    iScsiInitiatorNameProtocol.h

Abstract:

    IscsiInitiatorName Protocol (define according to the UEFI Spec 2.0 )

Revision History

--*/

#ifndef __ISCSIINITIATORNAMEPROTOCOL_H__
#define __ISCSIINITIATORNAMEPROTOCOL_H__

#define EFI_ISCSI_INITIATOR_NAME_PROTOCOL_GUID \
  { 0x59324945, 0xec44, 0x4c0d, {0xb1, 0xcd, 0x9d, 0xb1, 0x39, 0xdf, 0x7, 0xc } }

typedef struct _EFI_ISCSI_INITIATOR_NAME_PROTOCOL EFI_ISCSI_INITIATOR_NAME_PROTOCOL;

typedef 
EFI_STATUS
(EFIAPI *EFI_ISCSI_INITIATOR_NAME_GET) (
  IN EFI_ISCSI_INITIATOR_NAME_PROTOCOL *This,
  IN OUT UINTN                         *BufferSize,
  OUT VOID                             *Buffer
  )
/*++

  Routine Description:
    Retrieves the current set value of iSCSI Initiator Name.
  
  Arguments:
    This         - Pointer to the EFI_ISCSI_INITIATOR_NAME_PROTOCOL instance.
    BufferSize   - Size of the buffer in bytes pointed to by Buffer / Actual size of the
                   variable data buffer.
    Buffer       - Pointer to the buffer for data to be read.

  Returns:
    EFI_SUCCESS           - Data was successfully retrieved into the provided buffer and the
                            BufferSize was sufficient to handle the iSCSI initiator name
    EFI_BUFFER_TOO_SMALL  - BufferSize is too small for the result.
    EFI_INVALID_PARAMETER - BufferSize or Buffer is NULL.
    EFI_DEVICE_ERROR      - The iSCSI initiator name could not be retrieved due to a hardware error.
    
--*/
;

  

typedef EFI_STATUS
(EFIAPI *EFI_ISCSI_INITIATOR_NAME_SET) (
  IN EFI_ISCSI_INITIATOR_NAME_PROTOCOL *This,
  IN OUT UINTN                         *BufferSize,
  IN VOID                              *Buffer
  )
/*++

  Routine Description:
    Sets the iSCSI Initiator Name.

  Arguments:
    This       - Pointer to the EFI_ISCSI_INITIATOR_NAME_PROTOCOL instance.
    BufferSize - Size of the buffer in bytes pointed to by Buffer.
    Buffer     - Pointer to the buffer for data to be written.

  Returns:
    EFI_SUCCESS           - Data was successfully stored by the protocol.
    EFI_UNSUPPORTED       - Platform policies do not allow for data to be written.
    EFI_INVALID_PARAMETER - BufferSize or Buffer is NULL, or BufferSize exceeds the maximum allowed limit.
    EFI_DEVICE_ERROR      - The data could not be stored due to a hardware error.
    EFI_OUT_OF_RESOURCES  - Not enough storage is available to hold the data.
    EFI_PROTOCOL_ERROR    - Input iSCSI initiator name does not adhere to RFC 3720
                            (and other related protocols)
    
--*/
;  

struct _EFI_ISCSI_INITIATOR_NAME_PROTOCOL {
  EFI_ISCSI_INITIATOR_NAME_GET         Get;
  EFI_ISCSI_INITIATOR_NAME_SET         Set;
};

extern EFI_GUID gBlackBoxEfiIScsiInitiatorNameProtocolGuid;

#endif
