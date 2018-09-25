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

  IPsec2Protocol.h

Abstract:

  IPsec2 protocol from the UEFI 2.3 specification.

--*/

#ifndef _IPSEC2_PROTOCOL_H_
#define _IPSEC2_PROTOCOL_H_

#define  IP_VERSION_4          4
#define  IP_VERSION_6          6

#define IPSEC_ESP_PROTOCOL          50
#define IPSEC_AH_PROTOCOL           51

//
// Global ID for the IPSEC2 Protocol
//
#define EFI_IPSEC2_PROTOCOL_GUID \
{ 0xa3979e64, 0xace8, 0x4ddc, {0xbc, 0x7, 0x4d, 0x66, 0xb8, 0xfd, 0x9, 0x77 }}

extern EFI_GUID gBlackBoxEfiIPsec2ProtocolGuid;


typedef struct _EFI_IPSEC2_PROTOCOL EFI_IPSEC2_PROTOCOL;;


typedef struct _EFI_IPSEC_FRAGMENT_DATA {
  UINT32 FragmentLength;
  VOID   *FragmentBuffer;
} EFI_IPSEC_FRAGMENT_DATA;


typedef
EFI_STATUS
(EFIAPI *EFI_IPSEC_PROCESSEXT) (
  IN EFI_IPSEC2_PROTOCOL               *This,
  IN EFI_HANDLE                        NicHandle,
  IN UINT8                             IpVer,
  IN OUT VOID                          *IpHead,
  IN OUT UINT8                         *LastHead,
  IN OUT VOID                          **OptionsBuffer,
  IN OUT UINT32                        *OptionsLength,
  IN OUT EFI_IPSEC_FRAGMENT_DATA       **FragmentTable,
  IN OUT UINT32                        *FragmentCount,
  IN EFI_IPSEC_TRAFFIC_DIR             TrafficDirection,
  OUT EFI_EVENT                        *RecycleSignal
);

struct _EFI_IPSEC2_PROTOCOL {
  EFI_IPSEC_PROCESSEXT ProcessExt;
  EFI_EVENT            DisabledEvent;
  BOOLEAN              DisabledFlag;
};


#endif

