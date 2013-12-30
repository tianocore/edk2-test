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

#ifndef _IP4_H_
#define _IP4_H_

//#include "ServiceBinding.h"
//#include "SimpleNetwork.h"
#include "ManagedNetwork.h"

#define EFI_IP4_SERVICE_BINDING_PROTOCOL_GUID   \
  { 0xc51711e7, 0xb4bf, 0x404a, 0xbf, 0xb8, 0x0a, 0x04, 0x8e, 0xf1, 0xff, 0xe4 }

extern EFI_GUID gEfiIp4ServiceBindingProtocolGuid;

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_IP4_SERVICE_BINDING_PROTOCOL;

#define EFI_IP4_REGISTRY_DATA_GUID    \
  { 0x6a257608, 0x7549, 0x4ffd, 0x83, 0x5b, 0x90, 0x62, 0x4c, 0x76, 0xd1, 0xab }

extern EFI_GUID gEfiIp4RegistryDataGuid;

#define EFI_IP4_PROTOCOL_GUID   \
  { 0x41d94cd2, 0x35b6, 0x455a, 0x82, 0x58, 0xd4, 0xe5, 0x13, 0x34, 0xaa, 0xdd }

extern EFI_GUID gEfiIp4ProtocolGuid;

#define EFI_IP4_CONFIG_PROTOCOL_GUID   \
  { 0x3b95aa31, 0x3793, 0x434b, 0x86, 0x67, 0xc8, 0x07, 0x08, 0x92, 0xe0, 0x5e }

extern EFI_GUID gEfiIp4ConfigProtocolGuid;

EFI_FORWARD_DECLARATION (EFI_IP4_PROTOCOL);
EFI_FORWARD_DECLARATION (EFI_IP4_CONFIG_PROTOCOL);

//**********************************************
// EFI_IP4_CONFIG_DATA 
//**********************************************
typedef struct {
  UINT8              DefaultProtocol;
  BOOLEAN            AcceptAnyProtocol;
  BOOLEAN            AcceptIcmpErrors;
  BOOLEAN            AcceptBroadcast;
  BOOLEAN            AcceptPromiscuous;
  BOOLEAN            UseDefaultAddress;
  EFI_IPv4_ADDRESS   StationAddress;
  EFI_IPv4_ADDRESS   SubnetMask;
  UINT8              TypeOfService;
  UINT8              TimeToLive;
  BOOLEAN            DoNotFragment;
  BOOLEAN            RawData;
  UINT32             ReceiveTimeout;
  UINT32             TransmitTimeout;
} EFI_IP4_CONFIG_DATA;

//**********************************************
// EFI_IP4_ROUTE_TABLE 
//**********************************************
typedef struct {
  EFI_IPv4_ADDRESS        SubnetAddress;
  EFI_IPv4_ADDRESS        SubnetMask;
  EFI_IPv4_ADDRESS        GatewayAddress;
} EFI_IP4_ROUTE_TABLE;

//**********************************************
// EFI_IP4_ICMP_TYPE 
//**********************************************
typedef struct {
  UINT8                Type;
  UINT8                Code;
} EFI_IP4_ICMP_TYPE;

//**********************************************
// EFI_IP4_MODE_DATA 
//**********************************************
typedef struct {
  BOOLEAN               IsStarted;
  UINT32                MaxPacketSize;
  EFI_IP4_CONFIG_DATA   ConfigData;
  BOOLEAN               IsConfigured;
  UINT32                GroupCount;
  EFI_IPv4_ADDRESS      *GroupTable;
  UINT32                RouteCount;
  EFI_IP4_ROUTE_TABLE   *RouteTable;
  UINT32                IcmpTypeCount;
  EFI_IP4_ICMP_TYPE     *IcmpTypeList;
} EFI_IP4_MODE_DATA;

#ifndef __STRUCT_EFI_IP4_HEADER__
#define __STRUCT_EFI_IP4_HEADER__
//**********************************************
// EFI_IP4_HEADER 
//**********************************************
#pragma pack(1)
typedef struct _EFI_IP4_HEADER {
  UINT8               HeaderLength:4;
  UINT8               Version:4;
//UINT8               VerHdrLen; //On little-endian platform, VersionHeader >> 4 is the version number.
  UINT8               TypeOfService;
  UINT16              TotalLength;
  UINT16              Identification;
  UINT16              Fragmentation;
  UINT8               TimeToLive;
  UINT8               Protocol;
  UINT16              Checksum;
  EFI_IPv4_ADDRESS    SourceAddress;
  EFI_IPv4_ADDRESS    DestinationAddress;
} EFI_IP4_HEADER;
#pragma pack()
#endif //__STRUCT_EFI_IP4_HEADER__

//**********************************************
// EFI_IP4_FRAGMENT_DATA 
//**********************************************
typedef struct {
  UINT32        FragmentLength;
  VOID          *FragmentBuffer;
} EFI_IP4_FRAGMENT_DATA;

//**********************************************
// EFI_IP4_RECEIVE_DATA 
//**********************************************
typedef struct {
  EFI_TIME               TimeStamp;
  EFI_EVENT              RecycleSignal;
  UINT32                 HeaderLength;
  EFI_IP4_HEADER         *Header;
  UINT32                 OptionsLength;
  VOID                   *Options;
  UINT32                 DataLength;
  UINT32                 FragmentCount;
  EFI_IP4_FRAGMENT_DATA  FragmentTable[1];
} EFI_IP4_RECEIVE_DATA;

//**********************************************
// EFI_IP4_OVERRIDE_DATA 
//**********************************************
typedef struct {
  EFI_IPv4_ADDRESS       SourceAddress;
  EFI_IPv4_ADDRESS       GatewayAddress;
  UINT8                  Protocol;
  UINT8                  TypeOfService;
  UINT8                  TimeToLive;
  BOOLEAN                DoNotFragment;
  BOOLEAN                RawData;
} EFI_IP4_OVERRIDE_DATA;

//**********************************************
// EFI_IP4_TRANSMIT_DATA 
//**********************************************
typedef struct {
  EFI_IPv4_ADDRESS       DestinationAddress;
  EFI_IP4_OVERRIDE_DATA  *OverrideData      OPTIONAL;
  UINT32                 OptionsLength      OPTIONAL;
  VOID                   *OptionsBuffer     OPTIONAL;
  UINT32                 TotalDataLength;
  UINT32                 FragmentCount;
  EFI_IP4_FRAGMENT_DATA  FragmentTable[1];
} EFI_IP4_TRANSMIT_DATA;

//**********************************************
// EFI_IP4_COMPLETION_TOKEN 
//**********************************************
typedef struct {
  EFI_EVENT                             Event;
  EFI_STATUS                            Status;
  union {
    EFI_IP4_RECEIVE_DATA                *RxData;
    EFI_IP4_TRANSMIT_DATA               *TxData;
  }                                     Packet;
} EFI_IP4_COMPLETION_TOKEN;

//**********************************************
// EFI_IP4_IPCONFIG_DATA 
//**********************************************
typedef struct {
  EFI_IPv4_ADDRESS     StationAddress;
  EFI_IPv4_ADDRESS     SubnetMask;
  UINT32               RouteTableSize;
  EFI_IP4_ROUTE_TABLE  *RouteTable    OPTIONAL;
} EFI_IP4_IPCONFIG_DATA;

typedef 
EFI_STATUS
(EFIAPI *EFI_IP4_GET_MODE_DATA) (
  IN EFI_IP4_PROTOCOL                 *This,
  OUT EFI_IP4_MODE_DATA               *Ip4ModeData     OPTIONAL,
  OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData   OPTIONAL,
  OUT EFI_SIMPLE_NETWORK_MODE         *SnpModeData     OPTIONAL
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP4_CONFIGURE) (
  IN EFI_IP4_PROTOCOL          *This,
  IN EFI_IP4_CONFIG_DATA       *IpConfigData     OPTIONAL
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP4_GROUPS) (
  IN EFI_IP4_PROTOCOL  *This,
  IN BOOLEAN           JoinFlag,
  IN EFI_IPv4_ADDRESS  *GroupAddress  OPTIONAL
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP4_ROUTES) (
  IN EFI_IP4_PROTOCOL    *This,
  IN BOOLEAN             DeleteRoute,
  IN EFI_IPv4_ADDRESS    *SubnetAddress,
  IN EFI_IPv4_ADDRESS    *SubnetMask,
  IN EFI_IPv4_ADDRESS    *GatewayAddress  
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP4_RECEIVE) (
  IN EFI_IP4_PROTOCOL          *This,
  IN EFI_IP4_COMPLETION_TOKEN  *Token
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP4_TRANSMIT) (
  IN EFI_IP4_PROTOCOL          *This,
  IN EFI_IP4_COMPLETION_TOKEN  *Token
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_CANCEL) (
  IN EFI_IP4_PROTOCOL          *This,
  IN EFI_IP4_COMPLETION_TOKEN  *Token  OPTIONAL
  );

typedef 
EFI_STATUS
(EFIAPI *EFI_IP4_POLL) (
  IN EFI_IP4_PROTOCOL      *This
  );

struct _EFI_IP4_PROTOCOL {
  EFI_IP4_GET_MODE_DATA   GetModeData;
  EFI_IP4_CONFIGURE       Configure;
  EFI_IP4_GROUPS          Groups;
  EFI_IP4_ROUTES          Routes;
  EFI_IP4_TRANSMIT        Transmit;
  EFI_IP4_RECEIVE         Receive;
  EFI_IP4_CANCEL          Cancel;
  EFI_IP4_POLL            Poll;
};

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_CONFIG_START) (
  IN EFI_IP4_CONFIG_PROTOCOL   *This,
  IN EFI_EVENT                 DoneEvent,
  IN EFI_EVENT                 ReconfigEvent
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_CONFIG_STOP) (
  IN EFI_IP4_CONFIG_PROTOCOL  *This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_IP4_CONFIG_GET_DATA) (
  IN EFI_IP4_CONFIG_PROTOCOL *This,
  IN OUT UINTN               *ConfigDataSize,
  OUT EFI_IP4_IPCONFIG_DATA  *ConfigData    OPTIONAL
  );

struct _EFI_IP4_CONFIG_PROTOCOL {
  EFI_IP4_CONFIG_START     Start;
  EFI_IP4_CONFIG_STOP      Stop;
  EFI_IP4_CONFIG_GET_DATA  GetData;
};

#endif
