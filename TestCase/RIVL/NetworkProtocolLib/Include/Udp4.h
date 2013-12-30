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

  UdpIo.h

Abstract:

--*/

#ifndef __UDP4_H__
#define __UDP4_H__

#include "Ip4.h"

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_UDP4_SERVICE_BINDING_PROTOCOL;
//
//GUID definitions
//
#define EFI_UDP4_SERVICE_BINDING_PROTOCOL_GUID \
  { 0x83f01464, 0x99bd, 0x45e5, 0xb3, 0x83, 0xaf, 0x63, 0x5, 0xd8, 0xe9, 0xe6 }

#define EFI_UDP4_PROTOCOL_GUID \
  { 0x3ad9df29, 0x4501, 0x478d, 0xb1, 0xf8, 0x7f, 0x7f, 0xe7, 0xe, 0x50, 0xf3 }

//
//ICMP error definitions
//
#define EFI_NETWORK_UNREACHABLE      EFIERR(100)
#define EFI_HOST_UNREACHABLE         EFIERR(101) 
#define EFI_PROTOCOL_UNREACHABLE     EFIERR(102)
#define EFI_PORT_UNREACHABLE         EFIERR(103)

EFI_FORWARD_DECLARATION (EFI_UDP4_PROTOCOL);

//*************************************************
//      EFI_UDP4_FRAGMENT_DATA                    *
//*************************************************
typedef struct {
  UINT32       FragmentLength;
  VOID         *FragmentBuffer;
} EFI_UDP4_FRAGMENT_DATA;

//*************************************************
//      EFI_UDP4_SESSION_DATA                     *
//*************************************************
typedef struct {
  EFI_IPv4_ADDRESS   SourceAddress;
  UINT16             SourcePort;
  EFI_IPv4_ADDRESS   DestinationAddress;
  UINT16             DestinationPort;
} EFI_UDP4_SESSION_DATA;

#ifndef __STRUCT_EFI_UDP4_HEADER__
#define __STRUCT_EFI_UDP4_HEADER__
//************************************************
//           EFI_UDP4_HEADER                     *
//************************************************
#pragma pack(1)
typedef struct {
  UINT16     SourcePortNum;
  UINT16     DestinationPortNum;
  UINT16     UdpLength;
  UINT16     UdpCheckSum;
} EFI_UDP4_HEADER;
#pragma pack()
#endif //__STRUCT_EFI_UDP4_HEADER__

//************************************************
//      EFI_UDP4_CONFIG_DATA                     *
//************************************************
typedef struct {
  //Receiving Filters
  BOOLEAN               AcceptBroadcast;
  BOOLEAN               AcceptPromiscuous;
  BOOLEAN               AcceptAnyPort;
  BOOLEAN               AllowDuplicatePort;
  //I/O parameters
  UINT8                 TypeOfService;
  UINT8                 TimeToLive;
  BOOLEAN               DoNotFragment;
  UINT32                ReceiveTimeout;
  UINT32                TransmitTimeout;
  //Access Point
  BOOLEAN               UseDefaultAddress;
  EFI_IPv4_ADDRESS      StationAddress;
  EFI_IPv4_ADDRESS      SubnetMask;
  UINT16                StationPort;
  EFI_IPv4_ADDRESS      RemoteAddress;
  UINT16                RemotePort;
} EFI_UDP4_CONFIG_DATA;

//*******************************************************
//               EFI_UDP4_TRANSMIT_DATA                 *
//*******************************************************
typedef struct {
  EFI_UDP4_SESSION_DATA     *UdpSessionData       OPTIONAL;
  EFI_IPv4_ADDRESS          *GatewayAddress       OPTIONAL;
  UINT32                    DataLength;
  UINT32                    FragmentCount; 
  EFI_UDP4_FRAGMENT_DATA    FragmentTable[1];
} EFI_UDP4_TRANSMIT_DATA;

//*******************************************************
//           EFI_UDP4_RECEIVE_DATA                      *
//*******************************************************
typedef struct {
  EFI_TIME                  TimeStamp;
  EFI_EVENT                 RecycleSignal;
  EFI_UDP4_SESSION_DATA     UdpSession;
  UINT32                    DataLength;
  UINT32                    FragmentCount;
  EFI_UDP4_FRAGMENT_DATA    FragmentTable[1];
} EFI_UDP4_RECEIVE_DATA;

//*******************************************************
//           EFI_UDP4_COMPLETION_TOKEN                  *
//*******************************************************
typedef struct {
  EFI_EVENT                             Event;
  EFI_STATUS                            Status;
  union {
    EFI_UDP4_RECEIVE_DATA               *RxData;
    EFI_UDP4_TRANSMIT_DATA              *TxData;
  }                                     Packet;
} EFI_UDP4_COMPLETION_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_GET_MODE_DATA) (
  IN EFI_UDP4_PROTOCOL                *This,
  OUT EFI_UDP4_CONFIG_DATA            *Udp4ConfigData OPTIONAL,
  OUT EFI_IP4_MODE_DATA               *Ip4ModeData    OPTIONAL,
  OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData  OPTIONAL,
  OUT EFI_SIMPLE_NETWORK_MODE         *SnpModeData    OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_CONFIGURE) (
  IN EFI_UDP4_PROTOCOL      *This,
  IN EFI_UDP4_CONFIG_DATA   *UdpConfigData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_GROUPS) (
  IN EFI_UDP4_PROTOCOL  *This,
  IN BOOLEAN            JoinFlag,
  IN EFI_IPv4_ADDRESS   *MulticastAddress    OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_ROUTES) (
  IN EFI_UDP4_PROTOCOL   *This,
  IN BOOLEAN             DeleteRoute,
  IN EFI_IPv4_ADDRESS    *SubnetAddress,
  IN EFI_IPv4_ADDRESS    *SubnetMask,
  IN EFI_IPv4_ADDRESS    *GatewayAddress
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_POLL) (
  IN EFI_UDP4_PROTOCOL        *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_RECEIVE) (
  IN EFI_UDP4_PROTOCOL          *This,
  IN EFI_UDP4_COMPLETION_TOKEN  *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_TRANSMIT) (
  IN EFI_UDP4_PROTOCOL           *This,
  IN EFI_UDP4_COMPLETION_TOKEN   *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP4_CANCEL)(
  IN EFI_UDP4_PROTOCOL          *This,
  IN EFI_UDP4_COMPLETION_TOKEN  *Token
);


struct _EFI_UDP4_PROTOCOL {
  EFI_UDP4_GET_MODE_DATA   GetModeData;
  EFI_UDP4_CONFIGURE       Configure;
  EFI_UDP4_GROUPS          Groups;
  EFI_UDP4_ROUTES          Routes;
  EFI_UDP4_TRANSMIT        Transmit;
  EFI_UDP4_RECEIVE         Receive;
  EFI_UDP4_CANCEL          Cancel;
  EFI_UDP4_POLL            Poll;
};

extern EFI_GUID gEfiUdp4ServiceBindingProtocolGuid;
extern EFI_GUID gEfiUdp4ProtocolGuid;

#endif
