/** @file

  Copyright 2006 - 2015 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2015, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  AdapterInfoProtocol.h

Abstract:

  Adapter Information protocol from the UEFI 2.4 specification.

--*/

#ifndef _ADAPTER_INFORMATION_PROTOCOL_H_
#define _ADAPTER_INFORMATION_PROTOCOL_H_

//
// Global ID for the Adapter Information Protocol
//
#define EFI_ADAPTER_INFORMATION_PROTOCOL_GUID \
{ 0xE5DD1403, 0xD622, 0xC24E, 0x84, 0x88, 0xC7, 0x1B, 0x17, 0xF5, 0xE8, 0x02 } 



typedef struct _EFI_ADAPTER_INFORMATION_PROTOCOL EFI_ADAPTER_INFORMATION_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_ADAPTER_INFO_GET_INFO) (
IN EFI_ADAPTER_INFORMATION_PROTOCOL     *This,
IN EFI_GUID                             *InformationType,
OUT VOID                                **InformationBlock,
OUT UINTN                               *InformationBlockSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_ADAPTER_INFO_SET_INFO) (
IN EFI_ADAPTER_INFORMATION_PROTOCOL     *This,
IN EFI_GUID                             *InformationType,
IN VOID                                 *InformationBlock,
IN UINTN                                InformationBlockSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES) (
IN EFI_ADAPTER_INFORMATION_PROTOCOL     *This,
OUT EFI_GUID                            **InfoTypesBuffer,
OUT UINTN                               *InfoTypesBufferCount
) ;



typedef struct _EFI_ADAPTER_INFORMATION_PROTOCOL {
EFI_ADAPTER_INFO_GET_INFO               GetInformation;
EFI_ADAPTER_INFO_SET_INFO               SetInformation;
EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES    GetSupportedTypes;
} EFI_ADAPTER_INFORMATION_PROTOCOL;


//Information Blocks  Struct

typedef struct {
  EFI_STATUS MediaState;
} EFI_ADAPTER_INFO_MEDIA_STATE;


typedef struct {
  BOOLEAN iSsciIpv4BootCapablity;
  BOOLEAN iScsiIpv6BootCapablity;
  BOOLEAN FCoeBootCapablity;
  BOOLEAN OffloadCapability;
  BOOLEAN iScsiMpioCapability;
  BOOLEAN iScsiIpv4Boot;
  BOOLEAN iScsiIpv6Boot;
  BOOLEAN FCoeBoot;
} EFI_ADAPTER_INFO_NETWORK_BOOT;


typedef struct {
  EFI_MAC_ADDRESS SanMacAddress;
} EFI_ADAPTER_INFO_SAN_MAC_ADDRESS;

typedef struct {
BOOLEAN Ipv6Support;
} EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT;

extern EFI_GUID gEfiAdapterInformationProtocolGuid;

#endif

