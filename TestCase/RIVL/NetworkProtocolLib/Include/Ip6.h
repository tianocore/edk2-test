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

  Ip6.h

Abstract:

  EFI_IP6_PROTOCOL

--*/

#ifndef __EFI_IP6_PROTOCOL_H__
#define __EFI_IP6_PROTOCOL_H__

#include "ServiceBinding.h"
#include "SimpleNetwork.h"
#include "ManagedNetwork.h"


//
//GUID definitions
//
#define EFI_IP6_SERVICE_BINDING_PROTOCOL_GUID \
  { \
    0xec835dd3,0xfe0f,0x617b,0xa6,0x21,0xb3,0x50,0xc3,0xe1,0x33,0x88 \
  }
extern EFI_GUID gEfiIp6ServiceBindingProtocolGuid;

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_IP6_SERVICE_BINDING_PROTOCOL;

#define EFI_IP6_REGISTRY_DATA_GUID    \
  { 0x6a257608, 0x7549, 0x4ffd, 0x83, 0x5b, 0x90, 0x62, 0x4c, 0x76, 0xd1, 0xab }
  
extern EFI_GUID gEfiIp6RegistryDataGuid;

#define EFI_IP6_PROTOCOL_GUID \
  { \
    0x2c8759d5,0x5c2d,0x66ef,0x92,0x5f,0xb6,0x6c,0x10,0x19,0x57,0xe2 \
  }
extern EFI_GUID gEfiIp6ProtocolGuid;
#define EFI_IP6_CONFIG_PROTOCOL_GUID \
  { 0x937fe521, 0x95ae, 0x4d1a, 0x89, 0x29, 0x48, 0xbc, 0xd9, 0x0a, 0xd3, 0x1a}

extern EFI_GUID gEfiIp4ConfigProtocolGuid;
EFI_FORWARD_DECLARATION (EFI_IP6_PROTOCOL);
EFI_FORWARD_DECLARATION (EFI_IP6_CONFIG_PROTOCOL);



//***********************************************************
// ICMPv6 type definitions for error messages
//***********************************************************
#define ICMP_V6_DEST_UNREACHABLE                 0x1
#define ICMP_V6_PACKET_TOO_BIG                   0x2
#define ICMP_V6_TIME_EXCEEDED                    0x3
#define ICMP_V6_PARAMETER_PROBLEM                0x4
     
//***********************************************************
// ICMPv6 type definition for informational messages
//***********************************************************
#define ICMP_V6_ECHO_REQUEST                     0x80
#define ICMP_V6_ECHO_REPLY                       0x81
#define ICMP_V6_LISTENER_QUERY                   0x82
#define ICMP_V6_LISTENER_REPORT                  0x83
#define ICMP_V6_LISTENER_DONE                    0x84
#define ICMP_V6_ROUTER_SOLICIT                   0x85
#define ICMP_V6_ROUTER_ADVERTISE                 0x86
#define ICMP_V6_NEIGHBOR_SOLICIT                 0x87
#define ICMP_V6_NEIGHBOR_ADVERTISE               0x88
#define ICMP_V6_REDIRECT                         0x89
#define ICMP_V6_LISTENER_REPORT_2                0x8F
//***********************************************************
// ICMPv6 code definitions for ICMP_V6_DEST_UNREACHABLE
//***********************************************************
#define ICMP_V6_NO_ROUTE_TO_DEST                 0x0
#define ICMP_V6_COMM_PROHIBITED                  0x1
#define ICMP_V6_BEYOND_SCOPE                     0x2
#define ICMP_V6_ADDR_UNREACHABLE                 0x3 
#define ICMP_V6_PORT_UNREACHABLE                 0x4
#define ICMP_V6_SOURCE_ADDR_FAILED               0x5
#define ICMP_V6_ROUTE_REJECTED                   0x6
       
//***********************************************************
// ICMPv6 code definitions for ICMP_V6_TIME_EXCEEDED
//***********************************************************
#define ICMP_V6_TIMEOUT_HOP_LIMIT                0x0
#define ICMP_V6_TIMEOUT_REASSEMBLE               0x1
       
//***********************************************************
// ICMPv6 code definitions for ICMP_V6_PARAMETER_PROBLEM
//***********************************************************
#define ICMP_V6_ERRONEOUS_HEADER                 0x0
#define ICMP_V6_UNRECOGNIZE_NEXT_HDR             0x1
#define ICMP_V6_UNRECOGNIZE_OPTION               0x2

typedef struct {
  UINT8                   DefaultProtocol;
  BOOLEAN                 AcceptAnyProtocol;
  BOOLEAN                 AcceptIcmpErrors;
  BOOLEAN                 AcceptPromiscuous;
  EFI_IPv6_ADDRESS        DestinationAddress;
  EFI_IPv6_ADDRESS        StationAddress; 
  UINT8                   TrafficClass;
  UINT8                   HopLimit;
  UINT32                  FlowLabel;
  UINT32                  ReceiveTimeout;
  UINT32                  TransmitTimeout;
} EFI_IP6_CONFIG_DATA;

typedef struct {
  EFI_IPv6_ADDRESS        Address;
  UINT8                   PrefixLength;
} EFI_IP6_ADDRESS_INFO;

typedef struct {
  EFI_IPv6_ADDRESS        Gateway;
  EFI_IPv6_ADDRESS        Destination;  
  UINT8                   PrefixLength;
} EFI_IP6_ROUTE_TABLE;

typedef enum {
  EfiNeighborInComplete, 
  EfiNeighborReachable,
  EfiNeighborStale,
  EfiNeighborDelay,
  EfiNeighborProbe
} EFI_IP6_NEIGHBOR_STATE;

typedef struct {
  EFI_IPv6_ADDRESS        Neighbor;
  EFI_MAC_ADDRESS         LinkAddress;
  EFI_IP6_NEIGHBOR_STATE  State;
} EFI_IP6_NEIGHBOR_CACHE;

typedef struct {
  UINT8                   Type;
  UINT8                   Code;
} EFI_IP6_ICMP_TYPE;

typedef struct {
  BOOLEAN                 IsStarted;
  UINT32                  MaxPacketSize;
  EFI_IP6_CONFIG_DATA     ConfigData;
  BOOLEAN                 IsConfigured;
  UINT32                  AddressCount;
  EFI_IP6_ADDRESS_INFO    *AddressList;
  UINT32                  GroupCount;
  EFI_IPv6_ADDRESS        *GroupTable;
  UINT32                  RouteCount;
  EFI_IP6_ROUTE_TABLE     *RouteTable;
  UINT32                  NeighborCount;
  EFI_IP6_NEIGHBOR_CACHE  *NeighborCache;  
  UINT32                  PrefixCount;
  EFI_IP6_ADDRESS_INFO    *PrefixTable;
  UINT32                  IcmpTypeCount;
  EFI_IP6_ICMP_TYPE       *IcmpTypeList;
} EFI_IP6_MODE_DATA;

#ifndef __STRUCT_EFI_IP6_HEADER__
#define __STRUCT_EFI_IP6_HEADER__
typedef struct _EFI_IP6_HEADER {
  UINT8                   TrafficClassH:4;
  UINT8                   Version:4;
  UINT8                   FlowLabelH:4;
  UINT8                   TrafficClassL:4;  
  UINT16                  FlowLabelL;
  UINT16                  PayloadLength;
  UINT8                   NextHeader;
  UINT8                   HopLimit;
  EFI_IPv6_ADDRESS        SourceAddress;
  EFI_IPv6_ADDRESS        DestinationAddress;
} EFI_IP6_HEADER;
#endif //__STRUCT_EFI_IP6_HEADER__

typedef struct _EFI_IP6_FRAGMENT_DATA {
  UINT32                  FragmentLength;
  VOID                    *FragmentBuffer;
} EFI_IP6_FRAGMENT_DATA;

typedef struct _EFI_IP6_RECEIVE_DATA {
  EFI_TIME                TimeStamp;
  EFI_EVENT               RecycleSignal;
  UINT32                  HeaderLength;
  EFI_IP6_HEADER          *Header;
  UINT32                  DataLength;
  UINT32                  FragmentCount;
  EFI_IP6_FRAGMENT_DATA   FragmentTable[1];
} EFI_IP6_RECEIVE_DATA;

typedef struct _EFI_IP6_OVERRIDE_DATA {
  UINT8                   Protocol;
  UINT8                   HopLimit;
  UINT32                  FlowLabel;
} EFI_IP6_OVERRIDE_DATA;

typedef struct _EFI_IP6_TRANSMIT_DATA {
  EFI_IPv6_ADDRESS        DestinationAddress;

  EFI_IP6_OVERRIDE_DATA   *OverrideData;
  UINT32                  ExtHdrsLength;
  VOID                    *ExtHdrs;

  UINT32                  DataLength;
  UINT32                  FragmentCount;
  EFI_IP6_FRAGMENT_DATA   FragmentTable[1];
} EFI_IP6_TRANSMIT_DATA;

typedef struct {
  EFI_EVENT               Event;
  EFI_STATUS              Status;
  union {
    EFI_IP6_RECEIVE_DATA  *RxData;
    EFI_IP6_TRANSMIT_DATA *TxData;
  } Packet;
} EFI_IP6_COMPLETION_TOKEN;

typedef 
EFI_STATUS
(EFIAPI *EFI_IP6_GET_MODE_DATA) (
  IN EFI_IP6_PROTOCOL                 *This,
  OUT EFI_IP6_MODE_DATA               *Ip6ModeData     OPTIONAL,
  OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData   OPTIONAL,
  OUT EFI_SIMPLE_NETWORK_MODE         *SnpModeData     OPTIONAL
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP6_CONFIGURE) (
  IN EFI_IP6_PROTOCOL          *This,
  IN EFI_IP6_CONFIG_DATA       *Ip6ConfigData OPTIONAL
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP6_GROUPS) (
  IN EFI_IP6_PROTOCOL  *This,
  IN BOOLEAN           JoinFlag,
  IN EFI_IPv6_ADDRESS  *GroupAddress  OPTIONAL
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP6_ROUTES) (
  IN EFI_IP6_PROTOCOL    *This,
  IN BOOLEAN             DeleteRoute,
  IN EFI_IPv6_ADDRESS    *Destination, OPTIONAL
  IN UINT8               PrefixLength,
  IN EFI_IPv6_ADDRESS    *GatewayAddress OPTIONAL 
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP6_NEIGHBORS) (
  IN EFI_IP6_PROTOCOL          *This,
  IN BOOLEAN                   DeleteFlag,
  IN EFI_IPv6_ADDRESS          *TargetIp6Address,
  IN EFI_MAC_ADDRESS           *TargetLinkAddress,
  IN UINT32                    Timeout,
  IN BOOLEAN                   Override
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP6_TRANSMIT) (
  IN EFI_IP6_PROTOCOL          *This,
  IN EFI_IP6_COMPLETION_TOKEN  *Token
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP6_RECEIVE) (
  IN EFI_IP6_PROTOCOL          *This,
  IN EFI_IP6_COMPLETION_TOKEN  *Token
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_CANCEL)(
  IN EFI_IP6_PROTOCOL          *This,
  IN EFI_IP6_COMPLETION_TOKEN  *Token    OPTIONAL
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP6_POLL) (
  IN EFI_IP6_PROTOCOL          *This
  );

struct _EFI_IP6_PROTOCOL {
  EFI_IP6_GET_MODE_DATA   GetModeData;
  EFI_IP6_CONFIGURE       Configure;
  EFI_IP6_GROUPS          Groups;
  EFI_IP6_ROUTES          Routes;
  EFI_IP6_NEIGHBORS       Neighbors;
  EFI_IP6_TRANSMIT        Transmit;
  EFI_IP6_RECEIVE         Receive;
  EFI_IP6_CANCEL          Cancel;
  EFI_IP6_POLL            Poll;
};


//******************************************************************************
// EFI_IP6_CONFIG_DATA_TYPE
//******************************************************************************
typedef enum {
  Ip6ConfigDataTypeInterfaceInfo,
  Ip6ConfigDataTypeAltInterfaceId,
  Ip6ConfigDataTypePolicy,
  Ip6ConfigDataTypeDupAddrDetectTransmits,
  Ip6ConfigDataTypeManualAddress,
  Ip6ConfigDataTypeGateway,
  Ip6ConfigDataTypeDnsServer,
  Ip6ConfigDataTypeMaximum
} EFI_IP6_CONFIG_DATA_TYPE;

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_CONFIG_SET_DATA) (
  IN EFI_IP6_CONFIG_PROTOCOL    *This,
  IN EFI_IP6_CONFIG_DATA_TYPE   DataType,
  IN UINTN                      DataSize,
  IN VOID                       *Data
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_CONFIG_GET_DATA) (
  IN EFI_IP6_CONFIG_PROTOCOL    *This,
  IN EFI_IP6_CONFIG_DATA_TYPE   DataType,
  IN OUT UINTN                  *DataSize,
  IN VOID                       *Data   OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_CONFIG_REGISTER_NOTIFY) (
  IN EFI_IP6_CONFIG_PROTOCOL    *This,
  IN EFI_IP6_CONFIG_DATA_TYPE   DataType,
  IN EFI_EVENT                  Event
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IP6_CONFIG_UNREGISTER_NOTIFY) (
  IN EFI_IP6_CONFIG_PROTOCOL    *This,
  IN EFI_IP6_CONFIG_DATA_TYPE   DataType,
  IN EFI_EVENT                  Event
  );

struct _EFI_IP6_CONFIG_PROTOCOL {
  EFI_IP6_CONFIG_SET_DATA           SetData;
  EFI_IP6_CONFIG_GET_DATA           GetData;
  EFI_IP6_CONFIG_REGISTER_NOTIFY    RegisterDataNotify;
  EFI_IP6_CONFIG_UNREGISTER_NOTIFY  UnregisterDataNotify;
};
  
extern EFI_GUID gEfiIp6ServiceBindingProtocolGuid;
extern EFI_GUID gEfiIp6ProtocolGuid;

#endif
