/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  TCP4.h

Abstract:

--*/

#ifndef _TCP4_H_
#define _TCP4_H_

#include <UEFI/Protocol/Ip4.h>
#include <Protocol/ServiceBinding.h>

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_TCP4_SERVICE_BINDING_PROTOCOL;

#define EFI_TCP4_SERVICE_BINDING_PROTOCOL_GUID \
     { 0x00720665, 0x67EB, 0x4a99, {0xBA, 0xF7, 0xD3, 0xC3, 0x3A, 0x1C, 0x7C, 0xC9 }}
 
#define EFI_TCP4_REGISTRY_DATA_GUID   \
     { 0x755B4303, 0xCAA5, 0x4481, {0xB1, 0x3D, 0x07, 0xBE, 0x14, 0xD5, 0x4D, 0x3F }}
 
#define EFI_TCP4_PROTOCOL_GUID   \
     { 0x65530BC7, 0xA359, 0x410f, {0xB0, 0x10, 0x5A, 0xAD, 0xC7, 0xEC, 0x2B, 0x62 }}
 
extern EFI_GUID gBlackBoxEfiTcp4ProtocolGuid;
extern EFI_GUID gBlackBoxEfiTcp4ServiceBindingProtocolGuid;
extern EFI_GUID gBlackBoxEfiTcp4RegistryDataGuid;

typedef struct _EFI_TCP4_PROTOCOL EFI_TCP4_PROTOCOL;


//**********************************************
// EFI_TCP4_SERVICE_POINT 
//**********************************************
typedef struct{
  EFI_HANDLE                  InstanceHandle;
  EFI_IPv4_ADDRESS            LocalAddress;
  UINT16                      LocalPort;
  EFI_IPv4_ADDRESS            RemoteAddress;
  UINT16                      RemotePort;
} EFI_TCP4_SERVICE_POINT; 
 
 
 
//**********************************************
// EFI_TCP4_DATA_REGISTRY_ENTRY
//**********************************************
typedef struct {
  EFI_GUID                    ProtocolGuid;
  EFI_HANDLE                  DriverHandle;
  UINTN                       ServiceCount;
  EFI_TCP4_SERVICE_POINT  Services[1];
} EFI_TCP4_DATA_REGISTRY_ENTRY;
 
//**********************************************
// EFI_TCP4_ACCESS_POINT
//**********************************************
typedef struct {
  BOOLEAN                     UseDefaultAddress;
  EFI_IPv4_ADDRESS            StationAddress;
  EFI_IPv4_ADDRESS            SubnetMask;
  UINT16                      StationPort;
  EFI_IPv4_ADDRESS            RemoteAddress;
  UINT16                      RemotePort;
  BOOLEAN                     ActiveFlag;
}EFI_TCP4_ACCESS_POINT;
 
//**********************************************
// EFI_TCP4_OPTION
//**********************************************
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
  BOOLEAN                     EnableNagle;
  BOOLEAN                     EnableTimeStamp;
  BOOLEAN                     EnableWindowScaling;
  BOOLEAN                     EnableSelectiveAck;
  BOOLEAN                     EnablePathMtuDiscovery;
}EFI_TCP4_OPTION;
 
//***************************************************************
// EFI_TCP4_CONFIG_DATA
//***************************************************************
typedef struct {
   //
  // I/O parameters
  //
  UINT8                       TypeOfService;
  UINT8                       TimeToLive;
  
  //
  // Access Point
  //
  EFI_TCP4_ACCESS_POINT       AccessPoint; 
 
  //
  // TCP Control Options
  //
  EFI_TCP4_OPTION             *ControlOption;
} EFI_TCP4_CONFIG_DATA;
 
//***************************************************************
// EFI_TCP4_CONNECTION_STATE
//***************************************************************
 
typedef enum {
  Tcp4StateClosed             = 0,
  Tcp4StateListen             = 1,
  Tcp4StateSynSent            = 2,
  Tcp4StateSynReceived        = 3,
  Tcp4StateEstablished        = 4,
  Tcp4StateFinWait1           = 5,
  Tcp4StateFinWait2           = 6,
  Tcp4StateClosing    = 7,
  Tcp4StateTimeWait   = 8,
  Tcp4StateCloseWait  = 9,
  Tcp4StateLastAck    = 10
} EFI_TCP4_CONNECTION_STATE;
 
 
//***************************************************************
// EFI_TCP4_COMPLETION_TOKEN
//***************************************************************
typedef struct {
  EFI_EVENT                   Event;
  EFI_STATUS                  Status;
} EFI_TCP4_COMPLETION_TOKEN;
 
//***************************************************************
// EFI_TCP4_CONNECTION_TOKEN
//***************************************************************
typedef struct {
  EFI_TCP4_COMPLETION_TOKEN   CompletionToken;
} EFI_TCP4_CONNECTION_TOKEN;
 
//***************************************************************
// EFI_TCP4_LISTEN_TOKEN
//***************************************************************
typedef struct {
  EFI_TCP4_COMPLETION_TOKEN   CompletionToken;
  EFI_HANDLE                  NewChildHandle;
} EFI_TCP4_LISTEN_TOKEN;
 
//***************************************************************
// EFI_TCP4_FRAGMENT_DATA
//***************************************************************
typedef struct {
  UINT32 FragmentLength;
  VOID         *FragmentBuffer;
} EFI_TCP4_FRAGMENT_DATA;
 
 
//***************************************************************
// EFI_TCP4_RECEIVE_DATA
//***************************************************************
typedef struct {
  BOOLEAN                     UrgentFlag;
  UINT32                  DataLength;
  UINT32                  FragmentCount;
  EFI_TCP4_FRAGMENT_DATA      FragmentTable[1];
} EFI_TCP4_RECEIVE_DATA;
 
//**************************************************************
// EFI_TCP4_TRANSMIT_DATA
//**************************************************************
typedef struct {
  BOOLEAN                     Push;
  BOOLEAN                     Urgent;
  UINT32                  DataLength;
  UINT32                  FragmentCount;
  EFI_TCP4_FRAGMENT_DATA      FragmentTable[1];
} EFI_TCP4_TRANSMIT_DATA;
 
//***************************************************************
// EFI_TCP4_IO_TOKEN
//***************************************************************
typedef struct {
  EFI_TCP4_COMPLETION_TOKEN    CompletionToken;
  union {
    EFI_TCP4_RECEIVE_DATA      *RxData;
    EFI_TCP4_TRANSMIT_DATA     *TxData;
  }Packet; 
} EFI_TCP4_IO_TOKEN; 
  
//***************************************************************
// EFI_TCP4_CLOSE_TOKEN 
//***************************************************************
typedef struct { 
  EFI_TCP4_COMPLETION_TOKEN    CompletionToken;
  BOOLEAN                      AbortOnClose;
} EFI_TCP4_CLOSE_TOKEN;        
                               
//***************************************************************
//                 Interface definition for TCP4 protocol
//***************************************************************
                               
//                             
// Get the mode data of a TCP instance
//
typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_GET_MODE_DATA) (
  IN    EFI_TCP4_PROTOCOL             *This,
  OUT EFI_TCP4_CONNECTION_STATE       *Tcp4State       OPTIONAL,
  OUT EFI_TCP4_CONFIG_DATA            *Tcp4ConfigData  OPTIONAL,
  OUT EFI_IP4_MODE_DATA              *Ip4ModeData     OPTIONAL,
  OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData   OPTIONAL,
  OUT EFI_SIMPLE_NETWORK_MODE         *SnpModeData     OPTIONAL
  );
 
//
// Initialize or reset a TCP instance
//
typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_CONFIGURE) (
  IN EFI_TCP4_PROTOCOL        *This,
  IN EFI_TCP4_CONFIG_DATA     *TcpConfigData OPTIONAL
  );
 
//
// Add a route entry to the route table 
//
typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_ROUTES) (
  IN EFI_TCP4_PROTOCOL   *This,
  IN BOOLEAN              DeleteRoute,
  IN EFI_IPv4_ADDRESS    *SubnetAddress,
  IN EFI_IPv4_ADDRESS    *SubnetMask,
  IN EFI_IPv4_ADDRESS    *GatewayAddress
  );
 
 
//
// Issue an asynchronous connection establishment request to the peer
//
typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_CONNECT) (
  IN EFI_TCP4_PROTOCOL           *This,
  IN EFI_TCP4_CONNECTION_TOKEN   *ConnectionToken
  );
 
//
// Issue an asynchronous listent token to accept an incoming connection reques
//
typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_ACCEPT) (
  IN EFI_TCP4_PROTOCOL             *This,
  IN EFI_TCP4_LISTEN_TOKEN       *ListenToken
  );
 
//
// Issue an asynchronous IO token to transmit some data through this TCP instance
//
typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_TRANSMIT) (
  IN EFI_TCP4_PROTOCOL           *This,
  IN EFI_TCP4_IO_TOKEN            *Token
  );
 
//
// Issue an asynchronous IO token to receive some data through this TCP instance
//
typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_RECEIVE) (
  IN EFI_TCP4_PROTOCOL          *This,
  IN EFI_TCP4_IO_TOKEN           *Token
  );
 
//
// Issue an asynchronous CloseToken to close a TCP connection represented by instance
//
typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_CLOSE)(
  IN EFI_TCP4_PROTOCOL           *This,
  IN EFI_TCP4_CLOSE_TOKEN        *CloseToken
  );
 
//
// cancle an connect, listent or IO token
//
typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_CANCEL)(
  IN EFI_TCP4_PROTOCOL           *This,
  IN EFI_TCP4_COMPLETION_TOKEN   *Token    OPTIONAL
  );
 
//
// poll data from NIC for receive
//
typedef
EFI_STATUS
(EFIAPI *EFI_TCP4_POLL) (
  IN EFI_TCP4_PROTOCOL        *This
  );

//**********************************************
// EFI_TCP4_PROTOCOL
//**********************************************
struct _EFI_TCP4_PROTOCOL {
  EFI_TCP4_GET_MODE_DATA      GetModeData;
  EFI_TCP4_CONFIGURE          Configure;
  EFI_TCP4_ROUTES             Routes;
  EFI_TCP4_CONNECT            Connect;
  EFI_TCP4_ACCEPT             Accept;
  EFI_TCP4_TRANSMIT           Transmit;
  EFI_TCP4_RECEIVE            Receive;
  EFI_TCP4_CLOSE              Close;
  EFI_TCP4_CANCEL             Cancel;
  EFI_TCP4_POLL               Poll;
};

#endif
