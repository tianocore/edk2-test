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

  ManagedNetwork.h

Abstract:

--*/

#ifndef _MANAGED_NETWORK_H_
#define _MANAGED_NETWORK_H_

#include "ServiceBinding.h"
#include "SimpleNetwork.h"

#define EFI_MANAGED_NETWORK_SERVICE_BINDING_PROTOCOL_GUID \
  { 0xf36ff770, 0xa7e1, 0x42cf, 0x9e, 0xd2, 0x56, 0xf0, 0xf2, 0x71,0xf4, 0x4c }

extern EFI_GUID gEfiManagedNetworkServiceBindingProtocolGuid;

#define EFI_MANAGED_NETWORK_PROTOCOL_GUID \
  { 0x7ab33a91, 0xace5, 0x4326, 0xb5, 0x72, 0xe7, 0xee, 0x33, 0xd3, 0x9f, 0x16 }

extern EFI_GUID gEfiManagedNetworkProtocolGuid;

EFI_FORWARD_DECLARATION (EFI_MANAGED_NETWORK_PROTOCOL);

typedef EFI_SIMPLE_NETWORK_MODE EFI_SIMPLE_NETWORK_MODE_DATA;
typedef EFI_SERVICE_BINDING_PROTOCOL EFI_MNP_SERVICE_BINDING_PROTOCOL;

//****************************************************
// EFI_MANAGED_NETWORK_CONFIG_DATA
//****************************************************
typedef struct {
  UINT32     ReceivedQueueTimeoutValue;
  UINT32     TransmitQueueTimeoutValue;
  UINT16     ProtocolTypeFilter;
  BOOLEAN    EnableUnicastReceive;
  BOOLEAN    EnableMulticastReceive;
  BOOLEAN    EnableBroadcastReceive;
  BOOLEAN    EnablePromiscuousReceive;
  BOOLEAN    EnableReceiveTimestamps;
  BOOLEAN    DisableBackgroundPolling;
} EFI_MANAGED_NETWORK_CONFIG_DATA;

//****************************************************
// EFI_MANAGED_NETWORK_RECEIVE_DATA 
//****************************************************
typedef struct {
  EFI_TIME      Timestamp;
  EFI_EVENT     RecycleEvent;
  UINT32        PacketLength;
  UINT32        HeaderLength;
  UINT32        AddressLength;
  UINT32        DataLength;
  BOOLEAN       BroadcastFlag;
  BOOLEAN       MulticastFlag;
  BOOLEAN       PromiscuousFlag;
  UINT16        ProtocolType;
  VOID          *DestinationAddress;
  VOID          *SourceAddress;
  VOID          *MediaHeader;
  VOID          *PacketData;
} EFI_MANAGED_NETWORK_RECEIVE_DATA;

//****************************************************
// EFI_MANAGED_NETWORK_FRAGMENT_DATA 
//****************************************************
typedef struct {
  UINT32        FragmentLength;
  VOID          *FragmentBuffer;
} EFI_MANAGED_NETWORK_FRAGMENT_DATA;

//****************************************************
// EFI_MANAGED_NETWORK_TRANSMIT_DATA 
//****************************************************
typedef struct {
  EFI_MAC_ADDRESS                   *DestinationAddress OPTIONAL;
  EFI_MAC_ADDRESS                   *SourceAddress      OPTIONAL;
  UINT16                            ProtocolType        OPTIONAL;
  UINT32                            DataLength;
  UINT16                            HeaderLength        OPTIONAL;
  UINT16                            FragmentCount;
  EFI_MANAGED_NETWORK_FRAGMENT_DATA FragmentTable[1];
} EFI_MANAGED_NETWORK_TRANSMIT_DATA;

//****************************************************
// EFI_MANAGED_NETWORK_COMPLETION_TOKEN 
//****************************************************
typedef struct {
  EFI_EVENT                             Event;
  EFI_STATUS                            Status;
  union {
    EFI_MANAGED_NETWORK_RECEIVE_DATA    *RxData;
    EFI_MANAGED_NETWORK_TRANSMIT_DATA   *TxData;
  }                                     Packet;
} EFI_MANAGED_NETWORK_COMPLETION_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_MANAGED_NETWORK_GET_MODE_DATA) (
  IN EFI_MANAGED_NETWORK_PROTOCOL      *This,
  OUT EFI_MANAGED_NETWORK_CONFIG_DATA  *MnpConfigData  OPTIONAL,
  OUT EFI_SIMPLE_NETWORK_MODE_DATA     *SnpModeData  OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MANAGED_NETWORK_CONFIGURE) (
  IN EFI_MANAGED_NETWORK_PROTOCOL     *This,
  IN EFI_MANAGED_NETWORK_CONFIG_DATA  *MnpConfigData  OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MANAGED_NETWORK_MCAST_IP_TO_MAC) (
  IN EFI_MANAGED_NETWORK_PROTOCOL  *This,
  IN BOOLEAN                       Ipv6Flag,
  IN EFI_IP_ADDRESS                *IpAddress,
  OUT EFI_MAC_ADDRESS              *MacAddress
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MANAGED_NETWORK_GROUPS) (
  IN EFI_MANAGED_NETWORK_PROTOCOL  *This,
  IN BOOLEAN                       JoinFlag,
  IN EFI_MAC_ADDRESS               *MacAddress  OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MANAGED_NETWORK_TRANSMIT) (
  IN EFI_MANAGED_NETWORK_PROTOCOL          *This,
  IN EFI_MANAGED_NETWORK_COMPLETION_TOKEN  *Token
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MANAGED_NETWORK_RECEIVE) (
  IN EFI_MANAGED_NETWORK_PROTOCOL          *This,
  IN EFI_MANAGED_NETWORK_COMPLETION_TOKEN  *Token
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MANAGED_NETWORK_CANCEL) (
  IN EFI_MANAGED_NETWORK_PROTOCOL          *This,
  IN EFI_MANAGED_NETWORK_COMPLETION_TOKEN  *Token OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MANAGED_NETWORK_POLL) (
  IN EFI_MANAGED_NETWORK_PROTOCOL    *This
  );

struct _EFI_MANAGED_NETWORK_PROTOCOL {
  EFI_MANAGED_NETWORK_GET_MODE_DATA       GetModeData;
  EFI_MANAGED_NETWORK_CONFIGURE           Configure;
  EFI_MANAGED_NETWORK_MCAST_IP_TO_MAC     McastIpToMac;
  EFI_MANAGED_NETWORK_GROUPS              Groups;
  EFI_MANAGED_NETWORK_TRANSMIT            Transmit;
  EFI_MANAGED_NETWORK_RECEIVE             Receive;
  EFI_MANAGED_NETWORK_CANCEL              Cancel;
  EFI_MANAGED_NETWORK_POLL                Poll;
};

#endif
