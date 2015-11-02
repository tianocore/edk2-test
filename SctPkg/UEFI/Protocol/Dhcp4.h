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
  DHCP4.h

Abstract:
  EFI User Datagram Protocol Definition

--*/

#ifndef _EFI_DHCP4_PROTOCOL_H_
#define _EFI_DHCP4_PROTOCOL_H_

#include <Protocol/ServiceBinding.h>

//GUID definitions
#define EFI_DHCP4_PROTOCOL_GUID \
  { 0x8a219718, 0x4ef5, 0x4761,  0x91, 0xc8, 0xc0, 0xf0, 0x4b, 0xda, 0x9e, 0x56}

#define EFI_DHCP4_SERVICE_BINDING_PROTOCOL_GUID \
  {0x9d9a39d8, 0xbd42, 0x4a73, 0xa4, 0xd5, 0x8e, 0xe9, 0x4b, 0xe1, 0x13, 0x80}
  
extern EFI_GUID gBlackBoxEfiDhcp4ProtocolGuid;
extern EFI_GUID gBlackBoxEfiDhcp4ServiceBindingProtocolGuid;

typedef struct _EFI_DHCP4_PROTOCOL EFI_DHCP4_PROTOCOL;

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_DHCP4_SERVICE_BINDING_PROTOCOL;

//********************************************************
//DHCP4 Packet Option Data Structure
//********************************************************
#pragma pack(1)
typedef struct {
  UINT8       OpCode;
  UINT8       Length;
  UINT8       Data[1];
} EFI_DHCP4_PACKET_OPTION;
#pragma pack()

//********************************************************
//DHCP4 Header Data Structure
//********************************************************
#pragma pack(1)
typedef struct{
    UINT8   OpCode;
    UINT8   HwType;
    UINT8   HwAddrLen;
    UINT8   Hops;
    UINT32  Xid;
    UINT16  Seconds;
    UINT16  Reserved;
    EFI_IPv4_ADDRESS  ClientAddr;       //Client IP address from client
    EFI_IPv4_ADDRESS  YourAddr;         //Client IP address from server
    EFI_IPv4_ADDRESS  ServerAddr;       //IP address of next server in bootstrap 
    EFI_IPv4_ADDRESS  GwAddr;           //Relay agent IP address
    UINT8   ClientHwAddr[16];           //Client hardware address
    CHAR8   ServerName[64];   
    CHAR8   BootFileName[128];
}EFI_DHCP4_HEADER;
#pragma pack()

//*************************************************************
//DHCP4 Packet Data Structure
//*************************************************************
#pragma pack(1)
typedef struct {
  UINT32         Size;
  UINT32         Length;
  struct {
    EFI_DHCP4_HEADER    Header;
    UINT32              Magik;
    UINT8               Option[1];
  } Dhcp4;
} EFI_DHCP4_PACKET;
#pragma pack()

//**************************************************************
// EFI_DHCP4_STATE
//**************************************************************
typedef enum {
  Dhcp4Stopped          = 0x0,
  Dhcp4Init             = 0x1,
  Dhcp4Selecting        = 0x2,
  Dhcp4Requesting       = 0x3,
  Dhcp4Bound            = 0x4,
  Dhcp4Renewing         = 0x5,
  Dhcp4Rebinding        = 0x6,
  Dhcp4InitReboot       = 0x7,
  Dhcp4Rebooting        = 0x8
} EFI_DHCP4_STATE;

//***************************************************************
//EFI_DHCP4_EVENT
//***************************************************************
typedef enum{
  Dhcp4SendDiscover     = 0x01,
  Dhcp4RcvdOffer        = 0x02,
  Dhcp4SelectOffer      = 0x03,
  Dhcp4SendRequest      = 0x05,
  Dhcp4RcvdAck          = 0x06,
  Dhcp4RcvdNak          = 0x07,
  Dhcp4SendDecline      = 0x08,
  Dhcp4BoundCompleted   = 0x09,
  Dhcp4EnterRenewing    = 0x0a,
  Dhcp4EnterRebinding   = 0x0b,
  Dhcp4AddressLost      = 0x0c,
  Dhcp4Fail             = 0x0d
} EFI_DHCP4_EVENT;


//***************************************************************
//EFI_DHCP4_CALLBACK
//***************************************************************
typedef EFI_STATUS (*EFI_DHCP4_CALLBACK)(
  IN EFI_DHCP4_PROTOCOL      *This,
  IN VOID                    *Context,
  IN EFI_DHCP4_STATE         CurrentState,
  IN EFI_DHCP4_EVENT         Dhcp4Event,
  IN EFI_DHCP4_PACKET        *Packet     OPTIONAL, 
  OUT EFI_DHCP4_PACKET       **NewPacket OPTIONAL
);

//***************************************************************
//EFI_DHCP4_CONFIG_DATA
//***************************************************************
typedef struct {
  UINT32                  DiscoverTryCount        OPTIONAL;
  UINT32                  *DiscoverTimeout        OPTIONAL;
  UINT32                  RequestTryCount         OPTIONAL;
  UINT32                  *RequestTimeout         OPTIONAL;
  EFI_IPv4_ADDRESS        ClientAddress;
  EFI_DHCP4_CALLBACK      Dhcp4Callback           OPTIONAL;
  VOID                    *CallbackContext        OPTIONAL;
  UINT32                  OptionCount;
  EFI_DHCP4_PACKET_OPTION **OptionList            OPTIONAL;
}EFI_DHCP4_CONFIG_DATA;

//**************************************************************
// EFI_DHCP4_MODE_DATA
//**************************************************************
typedef struct {
  EFI_DHCP4_STATE         State;
  EFI_DHCP4_CONFIG_DATA   ConfigData;
  EFI_IPv4_ADDRESS        ClientAddress;
  EFI_MAC_ADDRESS         ClientMacAddress;
  EFI_IPv4_ADDRESS        ServerAddress;
  EFI_IPv4_ADDRESS        RouterAddress;
  EFI_IPv4_ADDRESS        SubnetMask;
  UINT32                  LeaseTime;
  EFI_DHCP4_PACKET        *ReplyPacket;
 } EFI_DHCP4_MODE_DATA;

//**************************************************************
//  EFI_DHCP4_LISTEN_POINT
//**************************************************************
typedef struct {
  EFI_IPv4_ADDRESS           ListenAddress;
  EFI_IPv4_ADDRESS           SubnetMask;
  UINT16                     ListenPort;
} EFI_DHCP4_LISTEN_POINT;

//**************************************************************
//  EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN
//**************************************************************
typedef struct {
  OUT EFI_STATUS            Status;
  IN EFI_EVENT              CompletionEvent         OPTIONAL;
  IN EFI_IPv4_ADDRESS       RemoteAddress;
  IN UINT16                 RemotePort;
  IN EFI_IPv4_ADDRESS       GatewayAddress          OPTIONAL;
  IN UINT32                 ListenPointCount;
  IN EFI_DHCP4_LISTEN_POINT *ListenPoints;
  IN UINT32                 TimeoutValue;
  IN EFI_DHCP4_PACKET       *Packet;
  OUT UINT32                ResponseCount;
  OUT EFI_DHCP4_PACKET      *ResponseList;   
}EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN;


typedef 
EFI_STATUS 
(EFIAPI *EFI_DHCP4_GET_MODE_DATA)(
  IN EFI_DHCP4_PROTOCOL       *This,
  OUT EFI_DHCP4_MODE_DATA     *Dhcp4ModeData
);

typedef 
EFI_STATUS
(EFIAPI *EFI_DHCP4_CONFIGURE) (
  IN EFI_DHCP4_PROTOCOL       *This,
  IN EFI_DHCP4_CONFIG_DATA    *Dhcp4CfgData  OPTIONAL
);


typedef EFI_STATUS
(EFIAPI *EFI_DHCP4_START) (
  IN EFI_DHCP4_PROTOCOL       *This,
  IN EFI_EVENT                CompletionEvent  OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_DHCP4_RENEW) (
  IN EFI_DHCP4_PROTOCOL       *This,
  IN BOOLEAN                  RebindRequest,
  IN EFI_EVENT                CompletionEvent  OPTIONAL
);

typedef 
EFI_STATUS
(EFIAPI *EFI_DHCP4_RELEASE) (
  IN EFI_DHCP4_PROTOCOL  *This
);

typedef EFI_STATUS
(EFIAPI *EFI_DHCP4_STOP) (
  IN EFI_DHCP4_PROTOCOL      *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_DHCP4_BUILD) (
  IN EFI_DHCP4_PROTOCOL       *This,
  IN EFI_DHCP4_PACKET         *SeedPacket,
  IN UINT32                   DeleteCount,
  IN UINT8                    *DeleteList         OPTIONAL,
  IN UINT32                   AppendCount,
  IN EFI_DHCP4_PACKET_OPTION  *AppendList[]       OPTIONAL,
  OUT EFI_DHCP4_PACKET        **NewPacket
);

typedef 
EFI_STATUS
(EFIAPI *EFI_DHCP4_TRANSMIT_RECEIVE) (
  IN EFI_DHCP4_PROTOCOL                *This,
  IN EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN  *Token
);


typedef
EFI_STATUS
(EFIAPI *EFI_DHCP4_PARSE) (
  IN EFI_DHCP4_PROTOCOL           *This,
  IN EFI_DHCP4_PACKET             *Packet,
  IN OUT UINT32                   *OptionCount,
  IN OUT EFI_DHCP4_PACKET_OPTION  *PacketOptionList[]  OPTIONAL
);

//*********************************************************
//DHCP4 protocol interface
//*********************************************************
struct _EFI_DHCP4_PROTOCOL {
  EFI_DHCP4_GET_MODE_DATA           GetModeData;
  EFI_DHCP4_CONFIGURE               Configure;
  EFI_DHCP4_START                   Start;
  EFI_DHCP4_RENEW                   RenewRebind;
  EFI_DHCP4_RELEASE                 Release;
  EFI_DHCP4_STOP                    Stop;
  EFI_DHCP4_BUILD                   Build;
  EFI_DHCP4_TRANSMIT_RECEIVE        TransmitReceive;
  EFI_DHCP4_PARSE                   Parse;
};


#endif /* _EFI_DHCP4_H */

