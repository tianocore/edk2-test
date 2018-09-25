/** @file

  Copyright 2006 - 2011 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  IPsecConfigDataIp6Tunnel.h

Abstract:

  IPsec Config Data for Tunnel Mode from the UEFI 2.3 specification.

--*/

#ifndef _IPSEC_CONFIG_DATA_IP6_TUNNEL_H_
#define _IPSEC_CONFIG_DATA_IP6_TUNNEL_H_


extern EFI_IPSEC_PROCESS_POLICY ProcessingPolicyIp6Tunnel;

extern EFI_IP_ADDRESS_INFO LocalAddressIp6Tunnel;
extern EFI_IP_ADDRESS_INFO RemoteAddressIp6Tunnel;


extern EFI_IP_ADDRESS TunnelLocalAddressIp6;
extern EFI_IP_ADDRESS TunnelRemoteAddressIp6;

extern EFI_IPSEC_TUNNEL_OPTION  TunnelOptionIp6;


extern EFI_IPSEC_CONFIG_SELECTOR SpdSelectorIp6Tunnel;

extern EFI_IPSEC_CONFIG_SELECTOR SadSelectorIp6Tunnel;


extern CHAR8  EncKeyIp6Tunnel[128]; 
extern CHAR8  AuthKeyIp6Tunnel[128];

extern EFI_IPSEC_SA_DATA2 SadIp6Tunnel;

extern EFI_IPSEC_SPD_DATA SpdIp6Tunnel;

#endif

