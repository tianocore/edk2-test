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

  Tcp6.h

Abstract:

  UEFI TCPv6 Protocol Definition

--*/

#ifndef _EFI_TCP6_H_
#define _EFI_TCP6_H_

#include <Protocol/ServiceBinding.h>
#include <UEFI/Protocol/SimpleNetwork.h>
#include <UEFI/Protocol/ManagedNetwork.h>
#include <UEFI/Protocol/Ip6.h>

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_TCP6_SERVICE_BINDING_PROTOCOL;

//
//GUID definitions
//
#define EFI_TCP6_SERVICE_BINDING_PROTOCOL_GUID \
  { \
    0xec20eb79, 0x6c1a, 0x4664, 0x9a, 0x0d, 0xd2, 0xe4, 0xcc, 0x16, 0xd6, 0x64 \
  }

#define EFI_TCP6_REGISTRY_DATA_GUID \
  { \
    0x80623540, 0x7B41, 0x4306, 0x99, 0x87, 0x1B, 0xF6, 0xE5, 0xAD, 0x15, 0x3E \
  }

#define EFI_TCP6_PROTOCOL_GUID \
  { \
    0x46e44855, 0xbd60, 0x4ab7, 0xab, 0x0d, 0xa6, 0x79, 0xb9, 0x44, 0x7d, 0x77 \
  }

extern EFI_GUID gBlackBoxEfiTcp6ProtocolGuid;
extern EFI_GUID gBlackBoxEfiTcp6ServiceBindingProtocolGuid;
extern EFI_GUID gBlackBoxEfiTcp6RegistryDataGuid;

typedef struct _EFI_TCP6_PROTOCOL EFI_TCP6_PROTOCOL;


//*******************************************
//EFI_TCP6_SERVICE_POINT
//*******************************************
typedef struct {
  EFI_HANDLE        InstanceHandle;
  EFI_IPv6_ADDRESS  LocalAddress;
  UINT16            LocalPort;
  EFI_IPv6_ADDRESS  RemoteAddress;
  UINT16            RemotePort;
} EFI_TCP6_SERVICE_POINT;

//*******************************************
//EFI_TCP6_DATA_REGISTRY_ENTRY
//*******************************************
typedef struct {
  EFI_GUID                ProtocolGuid;
  EFI_HANDLE              DriverHandle;
  UINT32                  ServiceCount;
  EFI_TCP6_SERVICE_POINT  Services[1];
} EFI_TCP6_DATA_REGISTRY_ENTRY;

//*******************************************
//EFI_TCP6_ACCESS_POINT
//*******************************************
typedef struct {
  EFI_IPv6_ADDRESS  StationAddress;
  UINT16            StationPort;
  EFI_IPv6_ADDRESS  RemoteAddress;
  UINT16            RemotePort;
  BOOLEAN           ActiveFlag;
} EFI_TCP6_ACCESS_POINT;

//*******************************************
//EFI_TCP6_OPTION
//*******************************************
typedef struct {
  UINT32   ReceiveBufferSize;
  UINT32   SendBufferSize;
  UINT32   MaxSynBackLog;
  UINT32   ConnectionTimeout;
  UINT32   DataRetries;
  UINT32   FinTimeout;
  UINT32   TimeWaitTimeout;
  UINT32   KeepAliveProbes;
  UINT32   KeepAliveTime;
  UINT32   KeepAliveInterval;
  BOOLEAN  EnableNagle;
  BOOLEAN  EnableTimeStamp;
  BOOLEAN  EnableWindowScaling;
  BOOLEAN  EnableSelectiveAck;
  BOOLEAN  EnablePathMtuDiscovery;
} EFI_TCP6_OPTION;

//*******************************************
//EFI_TCP6_CONFIG_DATA
//*******************************************
typedef struct {
  UINT8                 TrafficClass;
  UINT8                 HopLimit;
  EFI_TCP6_ACCESS_POINT AccessPoint;
  EFI_TCP6_OPTION       *ControlOption;
} EFI_TCP6_CONFIG_DATA;

//*******************************************
//EFI_TCP6_CONNECTION_STATE
//*******************************************
typedef enum {
  Tcp6StateClosed      = 0,
  Tcp6StateListen      = 1,
  Tcp6StateSynSent     = 2,
  Tcp6StateSynReceived = 3,
  Tcp6StateEstablished = 4,
  Tcp6StateFinWait1    = 5,
  Tcp6StateFinWait2    = 6,
  Tcp6StateClosing     = 7,
  Tcp6StateTimeWait    = 8,
  Tcp6StateCloseWait   = 9,
  Tcp6StateLastAck     = 10
} EFI_TCP6_CONNECTION_STATE;

//*******************************************
//EFI_TCP6_COMPLETION_TOKEN
//*******************************************
typedef struct {
  EFI_EVENT   Event;
  EFI_STATUS  Status;
} EFI_TCP6_COMPLETION_TOKEN;

//*******************************************
//EFI_TCP6_CONNECTION_TOKEN
//*******************************************
typedef struct {
  EFI_TCP6_COMPLETION_TOKEN CompletionToken;
} EFI_TCP6_CONNECTION_TOKEN;

//*******************************************
//EFI_TCP6_LISTEN_TOKEN
//*******************************************
typedef struct {
  EFI_TCP6_COMPLETION_TOKEN CompletionToken;
  EFI_HANDLE                NewChildHandle;
} EFI_TCP6_LISTEN_TOKEN;

//*******************************************
//EFI_TCP6_FRAGMENT_DATA
//*******************************************
typedef struct {
  UINT32 FragmentLength;
  VOID   *FragmentBuffer;
} EFI_TCP6_FRAGMENT_DATA;

//*******************************************
//EFI_TCP6_RECEIVE_DATA
//*******************************************
typedef struct {
  BOOLEAN                 UrgentFlag;
  UINT32                  DataLength;
  UINT32                  FragmentCount;
  EFI_TCP6_FRAGMENT_DATA  FragmentTable[1];
} EFI_TCP6_RECEIVE_DATA;

//*******************************************
//EFI_TCP6_TRANSMIT_DATA
//*******************************************
typedef struct {
  BOOLEAN                 Push;
  BOOLEAN                 Urgent;
  UINT32                  DataLength;
  UINT32                  FragmentCount;
  EFI_TCP6_FRAGMENT_DATA  FragmentTable[1];
} EFI_TCP6_TRANSMIT_DATA;

//*******************************************
//EFI_TCP6_IO_TOKEN
//*******************************************
typedef struct {
  EFI_TCP6_COMPLETION_TOKEN CompletionToken;
  union {
    EFI_TCP6_RECEIVE_DATA   *RxData;
    EFI_TCP6_TRANSMIT_DATA  *TxData;
  } Packet;
} EFI_TCP6_IO_TOKEN;

//*******************************************
//EFI_TCP6_CLOSE_TOKEN
//*******************************************
typedef struct {
  EFI_TCP6_COMPLETION_TOKEN CompletionToken;
  BOOLEAN                   AbortOnClose;
} EFI_TCP6_CLOSE_TOKEN;

//*******************************************
//EFI_TCP6_GET_MODE_DATA
//*******************************************
typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_GET_MODE_DATA) (
  IN  EFI_TCP6_PROTOCOL                  *This,
  OUT EFI_TCP6_CONNECTION_STATE          *Tcp6State OPTIONAL,
  OUT EFI_TCP6_CONFIG_DATA               *Tcp6ConfigData OPTIONAL,
  OUT EFI_IP6_MODE_DATA                  *Ip6ModeData OPTIONAL,
  OUT EFI_MANAGED_NETWORK_CONFIG_DATA    *MnpConfigData OPTIONAL,
  OUT EFI_SIMPLE_NETWORK_MODE            *SnpModeData OPTIONAL
  );

//*******************************************
//EFI_TCP6_CONFIGURE
//*******************************************
typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_CONFIGURE) (
  IN EFI_TCP6_PROTOCOL        *This,
  IN EFI_TCP6_CONFIG_DATA     *Tcp6ConfigData OPTIONAL
  );

//*******************************************
//EFI_TCP6_CONNECT
//*******************************************
typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_CONNECT) (
  IN EFI_TCP6_PROTOCOL           *This,
  IN EFI_TCP6_CONNECTION_TOKEN   *ConnectionToken
  );

//*******************************************
//EFI_TCP6_ACCEPT
//*******************************************
typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_ACCEPT) (
  IN EFI_TCP6_PROTOCOL             *This,
  IN EFI_TCP6_LISTEN_TOKEN         *ListenToken
  );

//*******************************************
//EFI_TCP6_TRANSMIT
//*******************************************
typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_TRANSMIT) (
  IN EFI_TCP6_PROTOCOL            *This,
  IN EFI_TCP6_IO_TOKEN            *Token
  );

//*******************************************
//EFI_TCP6_RECEIVE
//*******************************************
typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_RECEIVE) (
  IN EFI_TCP6_PROTOCOL           *This,
  IN EFI_TCP6_IO_TOKEN           *Token
  );

//*******************************************
//EFI_TCP6_CLOSE
//*******************************************
typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_CLOSE) (
  IN EFI_TCP6_PROTOCOL           *This,
  IN EFI_TCP6_CLOSE_TOKEN        *CloseToken
  );

//*******************************************
//EFI_TCP6_CANCEL
//*******************************************
typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_CANCEL) (
  IN EFI_TCP6_PROTOCOL           *This,
  IN EFI_TCP6_COMPLETION_TOKEN   *Token OPTIONAL
  );

//*******************************************
//EFI_TCP6_POLL
//*******************************************
typedef
EFI_STATUS
(EFIAPI *EFI_TCP6_POLL) (
  IN EFI_TCP6_PROTOCOL        *This
  );

//*******************************************
//EFI_TCP6_PROTOCOL
//*******************************************
struct _EFI_TCP6_PROTOCOL {
  EFI_TCP6_GET_MODE_DATA  GetModeData;
  EFI_TCP6_CONFIGURE      Configure;
  EFI_TCP6_CONNECT        Connect;
  EFI_TCP6_ACCEPT         Accept;
  EFI_TCP6_TRANSMIT       Transmit;
  EFI_TCP6_RECEIVE        Receive;
  EFI_TCP6_CLOSE          Close;
  EFI_TCP6_CANCEL         Cancel;
  EFI_TCP6_POLL           Poll;
};

#endif

