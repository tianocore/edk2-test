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

  VlanConfigProtocol.h

Abstract:

  Vlan Config protocol from the UEFI 2.3 specification.

--*/

#ifndef _VLAN_CONFIG_PROTOCOL_H_
#define _VLAN_CONFIG_PROTOCOL_H_

//
// Global ID for the Vlan Config Protocol
//
#define EFI_VLAN_CONFIG_PROTOCOL_GUID \
{ 0x9e23d768, 0xd2f3, 0x4366, {0x9f, 0xc3, 0x3a, 0x7a, 0xba, 0x86, 0x43, 0x74 }}

//
// EFI_VLAN_FIND_DATA
//
typedef struct {
  UINT16    VlanId;
  UINT8     Priority;
} EFI_VLAN_FIND_DATA;


typedef struct _EFI_VLAN_CONFIG_PROTOCOL EFI_VLAN_CONFIG_PROTOCOL;;

typedef
EFI_STATUS
(EFIAPI *EFI_VLAN_CONFIG_SET) (
  IN  EFI_VLAN_CONFIG_PROTOCOL  *This,
  IN  UINT16                    VlanId,
  IN  UINT8                     Priority
);

typedef
EFI_STATUS
(EFIAPI *EFI_VLAN_CONFIG_FIND) (
  IN  EFI_VLAN_CONFIG_PROTOCOL  *This,
  IN  UINT16                    *VlanId,
  OUT UINT16                    *NumberOfVlan,
  OUT EFI_VLAN_FIND_DATA        **Entries
);

typedef
EFI_STATUS
(EFIAPI *EFI_VLAN_CONFIG_REMOVE) (
  IN EFI_VLAN_CONFIG_PROTOCOL  *This,
  IN UINT16                    VlanId
);

struct _EFI_VLAN_CONFIG_PROTOCOL {
  EFI_VLAN_CONFIG_SET        Set;
  EFI_VLAN_CONFIG_FIND       Find;
  EFI_VLAN_CONFIG_REMOVE     Remove;
};


extern EFI_GUID gBlackBoxEfiVlanConfigProtocolGuid;

#endif

