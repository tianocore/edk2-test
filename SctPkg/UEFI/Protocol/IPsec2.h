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

  IPsec2Protocol.h

Abstract:

  IPsec2 protocol from the UEFI 2.3 specification.

--*/

#ifndef _IPSEC2_PROTOCOL_H_
#define _IPSEC2_PROTOCOL_H_

#define  IP_VERSION_4          4
#define  IP_VERSION_6          6

#define IPSEC_ESP_PROTOCOL          50
#define IPSEC_AH_PROTOCOL           51

//
// Global ID for the IPSEC2 Protocol
//
#define EFI_IPSEC2_PROTOCOL_GUID \
{0xa3979e64, 0xace8, 0x4ddc, 0xbc, 0x7, 0x4d, 0x66, 0xb8, 0xfd, 0x9, 0x77}

extern EFI_GUID gBlackBoxEfiIPsec2ProtocolGuid;


typedef struct _EFI_IPSEC2_PROTOCOL EFI_IPSEC2_PROTOCOL;;


typedef struct _EFI_IPSEC_FRAGMENT_DATA {
  UINT32 FragmentLength;
  VOID   *FragmentBuffer;
} EFI_IPSEC_FRAGMENT_DATA;


typedef
EFI_STATUS
(EFIAPI *EFI_IPSEC_PROCESSEXT) (
  IN EFI_IPSEC2_PROTOCOL               *This,
  IN EFI_HANDLE                        NicHandle,
  IN UINT8                             IpVer,
  IN OUT VOID                          *IpHead,
  IN OUT UINT8                         *LastHead,
  IN OUT VOID                          **OptionsBuffer,
  IN OUT UINT32                        *OptionsLength,
  IN OUT EFI_IPSEC_FRAGMENT_DATA       **FragmentTable,
  IN OUT UINT32                        *FragmentCount,
  IN EFI_IPSEC_TRAFFIC_DIR             TrafficDirection,
  OUT EFI_EVENT                        *RecycleSignal
);

struct _EFI_IPSEC2_PROTOCOL {
  EFI_IPSEC_PROCESSEXT ProcessExt;
  EFI_EVENT            DisabledEvent;
  BOOLEAN              DisabledFlag;
};


#endif

