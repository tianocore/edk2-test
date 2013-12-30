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

  NetInterfaceConfig.h

Abstract:

--*/

#ifndef __PROTOCOL_NET_INTERFACE_CONFIG_H__
#define __PROTOCOL_NET_INTERFACE_CONFIG_H__

#include "Ip4.h"

#define EFI_NET_INTERFACE_CONFIG_PROTOCOL_GUID \
  { 0xdc5800a1, 0xba61, 0x470b, 0xb4, 0x0e, 0x6e, 0x24, 0x34, 0xd6, 0x71, 0x2b }


EFI_FORWARD_DECLARATION (EFI_NET_INTERFACE_CONFIG_PROTOCOL);

#define NET_MAX_PROTOCOL_ADDRESS_LENGTH sizeof(EFI_IP_ADDRESS)
#define NET_MAX_HARDWARE_ADDRESS_LENGTH sizeof(EFI_MAC_ADDRESS)

typedef struct _NET_PROTOCOL_ADDRESS
{
  UINT16        ProtocolAddressType;
  UINT8         ProtocolAddressLen;
  UINT8         ProtocolAddress[ NET_MAX_PROTOCOL_ADDRESS_LENGTH ];
} NET_PROTOCOL_ADDRESS;

typedef struct _NET_HARDWARE_ADDRESS
{
  UINT16        HardwareAddressType;
  UINT8         HardwareAddressLen;
  UINT8         HardwareAddress[ NET_MAX_HARDWARE_ADDRESS_LENGTH ];
} NET_HARDWARE_ADDRESS;

typedef enum _IP4_CONFIG_SOURCE
{
  IP4_CONFIG_SOURCE_DHCP,
  IP4_CONFIG_SOURCE_STATIC,
  IP4_CONFIG_SOURCE_MAX
} IP4_CONFIG_SOURCE;

//#pragma pack(1)

/*
typedef struct _IP4_CONFIG_INFO
{
  NET_HARDWARE_ADDRESS      HardwareAddress;
  IP4_CONFIG_SOURCE         Source;
  UINT32                    ConfigDataLength;
  UINT8                     ConfigData[ 1 ];
} IP4_CONFIG_INFO;
*/

typedef struct _IP4_CONFIG_INFO
{
  NET_HARDWARE_ADDRESS      HardwareAddress;
  IP4_CONFIG_SOURCE         Source;
  UINT32                    ConfigDataLength;
  EFI_IP4_IPCONFIG_DATA     ConfigData[ 1 ];
} IP4_CONFIG_INFO;




#define MAX_NETWORK_INTERFACE_NAME_LENGTH       64

#define EFI_NET_MAX_IP4_CONFIG_IN_VARIABLE    16

typedef struct _IP4_CONFIG_VARIABLE
{
  UINT32                    Count;            // No more than EFI_NET_MAX_IP4_CONFIG_IN_VARIABLE
  IP4_CONFIG_INFO           ConfigInfo[ 1 ];
} IP4_CONFIG_VARIABLE;

//#pragma pack()


typedef
EFI_STATUS
(EFIAPI *EFI_NET_INTERFACE_CONFIG_GET_INFO) (
  IN  EFI_NET_INTERFACE_CONFIG_PROTOCOL *This,
  IN OUT UINT32                         *ConfigInfoSize,
  OUT IP4_CONFIG_INFO                   *ConfigInfoBuffer    OPTIONAL );

typedef
EFI_STATUS
(EFIAPI *EFI_NET_INTERFACE_CONFIG_SET_INFO) (
  IN  EFI_NET_INTERFACE_CONFIG_PROTOCOL *This,
  IN  UINT32                            ConfigInfoSize,
  IN  IP4_CONFIG_INFO                   *ConfigInfoBuffer    OPTIONAL,
  IN  BOOLEAN                           NeedReConfig );

typedef
EFI_STATUS
(EFIAPI *EFI_NET_INTERFACE_CONFIG_GET_NAME) (
  IN  EFI_NET_INTERFACE_CONFIG_PROTOCOL *This,
  IN  UINT32                            *NameBufferLen,
  IN  UINT16                            *NameBuffer          OPTIONAL,
  IN  NET_HARDWARE_ADDRESS              *HardwareAddress     OPTIONAL );


struct _EFI_NET_INTERFACE_CONFIG_PROTOCOL {
  EFI_NET_INTERFACE_CONFIG_GET_INFO   GetInfo;
  EFI_NET_INTERFACE_CONFIG_SET_INFO   SetInfo;
  EFI_NET_INTERFACE_CONFIG_GET_NAME   GetName;
};


extern EFI_GUID gEfiNetInterfaceConfigProtocolGuid;

#endif
