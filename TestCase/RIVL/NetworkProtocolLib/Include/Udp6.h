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

  Udp6.h

Abstract:

--*/

#ifndef __UDP6_H__
#define __UDP6_H__

#include "ServiceBinding.h"
#include "SimpleNetwork.h"
#include "ManagedNetwork.h"
#include "Ip6.h"

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_UDP6_SERVICE_BINDING_PROTOCOL;

//
//GUID definitions
//
#define EFI_UDP6_SERVICE_BINDING_PROTOCOL_GUID \
  { 0x66ed4721, 0x3c98, 0x4d3e, 0x81, 0xe3, 0xd0, 0x3d, 0xd3, 0x9a, 0x72, 0x54 }


#define EFI_UDP6_PROTOCOL_GUID \
  { 0x4f948815, 0xb4b9, 0x43cb, 0x8a, 0x33, 0x90, 0xe0, 0x60, 0xb3, 0x49, 0x55 }

//
//ICMP error definitions
//
#define EFI_NETWORK_UNREACHABLE      EFIERR(100)
#define EFI_HOST_UNREACHABLE         EFIERR(101) 
#define EFI_PROTOCOL_UNREACHABLE     EFIERR(102)
#define EFI_PORT_UNREACHABLE         EFIERR(103)

EFI_FORWARD_DECLARATION (EFI_UDP6_PROTOCOL);

//*************************************************
//      EFI_UDP6_FRAGMENT_DATA                    *
//*************************************************
typedef struct {
  UINT32        FragmentLength;
  VOID         *FragmentBuffer;
} EFI_UDP6_FRAGMENT_DATA;

//*************************************************
//      EFI_UDP6_SESSION_DATA                     *
//*************************************************
typedef struct {
  EFI_IPv6_ADDRESS   SourceAddress;
  UINT16             SourcePort;
  EFI_IPv6_ADDRESS   DestinationAddress;
  UINT16             DestinationPort;
} EFI_UDP6_SESSION_DATA;

#ifndef __STRUCT_EFI_UDP6_HEADER__
#define __STRUCT_EFI_UDP6_HEADER__
//************************************************
//           EFI_UDP6_HEADER                     *
//************************************************
#pragma pack(1)
typedef struct {
  UINT16     SourcePortNum;
  UINT16     DestinationPortNum;
  UINT16     UdpLength;
  UINT16     UdpCheckSum;
} EFI_UDP6_HEADER;
#pragma pack()
#endif //__STRUCT_EFI_UDP6_HEADER__

//************************************************
//      EFI_UDP6_CONFIG_DATA                     *
//************************************************
typedef struct {
  //Receiving Filters
  BOOLEAN        AcceptPromiscuous;
  BOOLEAN        AcceptAnyPort;
  BOOLEAN        AllowDuplicatePort;
  //I/O parameters
  UINT8          TrafficClass;
  UINT8          HopLimit;
  UINT32         ReceiveTimeout;
  UINT32         TransmitTimeout;
  //Access Point
  EFI_IPv6_ADDRESS  StationAddress;
  UINT16            StationPort;
  EFI_IPv6_ADDRESS  RemoteAddress;
  UINT16            RemotePort;
} EFI_UDP6_CONFIG_DATA;

//*******************************************************
//               EFI_UDP6_TRANSMIT_DATA                 *
//*******************************************************
typedef struct {
  EFI_UDP6_SESSION_DATA     *UdpSessionData;// Only the two fileds - DestionationAddr and DestiationPort
                                            // can be used.
  UINT32                    DataLength;
  UINT32                    FragmentCount; 
  EFI_UDP6_FRAGMENT_DATA    FragmentTable[1];
} EFI_UDP6_TRANSMIT_DATA;

//*******************************************************
//           EFI_UDP6_RECEIVE_DATA                      *
//*******************************************************
typedef struct {
  EFI_TIME                  TimeStamp;
  EFI_EVENT                 RecycleSignal;
  EFI_UDP6_SESSION_DATA     UdpSession;
  UINT32                    DataLength;
  UINT32                    FragmentCount;
  EFI_UDP6_FRAGMENT_DATA    FragmentTable[1];
} EFI_UDP6_RECEIVE_DATA;


//*******************************************************
//           EFI_UDP6_COMPLETION_TOKEN                  *
//*******************************************************
typedef struct {
  EFI_EVENT                             Event;
  EFI_STATUS                            Status;
  union {
    EFI_UDP6_RECEIVE_DATA               *RxData;
    EFI_UDP6_TRANSMIT_DATA              *TxData;
  } Packet;
} EFI_UDP6_COMPLETION_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_GET_MODE_DATA) (
  IN EFI_UDP6_PROTOCOL                 *This,
  OUT EFI_UDP6_CONFIG_DATA             *Udp6ConfigData OPTIONAL,
  OUT EFI_IP6_MODE_DATA                *Ip4ModeData    OPTIONAL,
  OUT EFI_MANAGED_NETWORK_CONFIG_DATA  *MnpConfigData  OPTIONAL,
  OUT EFI_SIMPLE_NETWORK_MODE          *SnpModeData    OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_CONFIGURE) (
  IN EFI_UDP6_PROTOCOL     *This,
  IN EFI_UDP6_CONFIG_DATA  *UdpConfigData OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_GROUPS) (
  IN EFI_UDP6_PROTOCOL  *This,
  IN BOOLEAN            JoinFlag,
  IN EFI_IPv6_ADDRESS   *MulticastAddress OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_TRANSMIT) (
  IN EFI_UDP6_PROTOCOL          *This,
  IN EFI_UDP6_COMPLETION_TOKEN  *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_RECEIVE) (
  IN EFI_UDP6_PROTOCOL          *This,
  IN EFI_UDP6_COMPLETION_TOKEN  *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_CANCEL)(
  IN EFI_UDP6_PROTOCOL          *This,
  IN EFI_UDP6_COMPLETION_TOKEN  *Token OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_UDP6_POLL) (
  IN EFI_UDP6_PROTOCOL  *This
);

struct _EFI_UDP6_PROTOCOL {
  EFI_UDP6_GET_MODE_DATA  GetModeData;
  EFI_UDP6_CONFIGURE      Configure;
  EFI_UDP6_GROUPS         Groups;
  EFI_UDP6_TRANSMIT       Transmit;
  EFI_UDP6_RECEIVE        Receive;
  EFI_UDP6_CANCEL         Cancel;
  EFI_UDP6_POLL           Poll;
};

extern EFI_GUID gEfiUdp6ServiceBindingProtocolGuid;
extern EFI_GUID gEfiUdp6ProtocolGuid;

#endif
