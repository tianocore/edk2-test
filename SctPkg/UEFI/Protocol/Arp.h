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

  Arp.h

Abstract:

--*/

#ifndef _ARP_H_
#define _ARP_H_

#include <Protocol/ServiceBinding.h>

#define EFI_ARP_SERVICE_BINDING_PROTOCOL_GUID   \
  { 0xf44c00ee, 0x1f2c, 0x4a00, 0xaa, 0x09, 0x1c, 0x9f, 0x3e, 0x08, 0x00, 0xa3 }

extern EFI_GUID gBlackBoxEfiArpServiceBindingProtocolGuid;

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_ARP_SERVICE_BINDING_PROTOCOL;

#define EFI_ARP_PROTOCOL_GUID   \
  { 0xf4b427bb, 0xba21, 0x4f16, 0xbc, 0x4e, 0x43, 0xe4, 0x16, 0xab, 0x61, 0x9c }

extern EFI_GUID gBlackBoxEfiArpProtocolGuid;

typedef struct _EFI_ARP_PROTOCOL EFI_ARP_PROTOCOL;

//*************************************************
// EFI_ARP_CONFIG_DATA
//*************************************************
typedef struct {
  UINT16                    SwAddressType;
  UINT8                     SwAddressLength;
  VOID                      *StationAddress;
  UINT32                    EntryTimeOut;
  UINT32                    RetryCount;
  UINT32                    RetryTimeOut;
}EFI_ARP_CONFIG_DATA;

//*************************************************
// EFI_ARP_FIND_DATA
//*************************************************
typedef struct {
  UINT32               Size;
  BOOLEAN              DenyFlag;
  BOOLEAN              StaticFlag;
  UINT16               HwAddressType;
  UINT16               SwAddressType;
  UINT8                HwAddressLength;
  UINT8                SwAddressLength;
} EFI_ARP_FIND_DATA;

typedef 
EFI_STATUS
(EFIAPI *EFI_ARP_CONFIGURE) (
  IN EFI_ARP_PROTOCOL          *This,
  IN EFI_ARP_CONFIG_DATA       *ConfigData OPTIONAL
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_ARP_ADD) (
  IN EFI_ARP_PROTOCOL  *This,
  IN BOOLEAN           DenyFlag,
  IN VOID              *TargetSwAddress  OPTIONAL,
  IN VOID              *TargetHwAddress  OPTIONAL,
  IN UINT32            TimeoutValue,
  IN BOOLEAN           Overwrite
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_ARP_FIND) (
  IN EFI_ARP_PROTOCOL     *This,
  IN BOOLEAN              BySwAddress,
  IN VOID                 *AddressBuffer    OPTIONAL,
  OUT UINT32              *EntryLength      OPTIONAL,
  OUT UINT32              *EntryCount       OPTIONAL,
  OUT EFI_ARP_FIND_DATA   **Entries,
  IN BOOLEAN              Refresh
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_ARP_DELETE) (
  IN EFI_ARP_PROTOCOL      *This,
  IN BOOLEAN               BySwAddress,
  IN VOID                  *AddressBuffer OPTIONAL
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_ARP_FLUSH) (
  IN EFI_ARP_PROTOCOL  *This
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_ARP_REQUEST) (
  IN EFI_ARP_PROTOCOL  *This, 
  IN VOID              *TargetSwAddress  OPTIONAL,
  IN EFI_EVENT         ResolvedEvent     OPTIONAL,
  OUT VOID             *TargetHwAddress  
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_ARP_CANCEL) (
  IN EFI_ARP_PROTOCOL  *This, 
  IN VOID              *TargetSwAddress  OPTIONAL,
  IN EFI_EVENT         ResolvedEvent     OPTIONAL
  );

struct _EFI_ARP_PROTOCOL {
  EFI_ARP_CONFIGURE         Configure;
  EFI_ARP_ADD               Add;
  EFI_ARP_FIND              Find;
  EFI_ARP_DELETE            Delete;
  EFI_ARP_FLUSH             Flush;
  EFI_ARP_REQUEST           Request;
  EFI_ARP_CANCEL            Cancel;
};

#endif
