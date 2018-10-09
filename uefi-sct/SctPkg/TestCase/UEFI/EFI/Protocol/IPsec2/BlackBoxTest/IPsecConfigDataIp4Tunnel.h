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

  IPsecConfigDataIp4Tunnel.h

Abstract:

  IPsec Config Data for Tunnel Mode from the UEFI 2.3 specification.

--*/

#ifndef _IPSEC_CONFIG_DATA_IP4_TUNNEL_H_
#define _IPSEC_CONFIG_DATA_IP4_TUNNEL_H_


extern EFI_IPSEC_PROCESS_POLICY ProcessingPolicyIp4Tunnel;

extern EFI_IP_ADDRESS_INFO LocalAddressIp4Tunnel;
extern EFI_IP_ADDRESS_INFO RemoteAddressIp4Tunnel;


extern EFI_IP_ADDRESS TunnelLocalAddressIp4;
extern EFI_IP_ADDRESS TunnelRemoteAddressIp4;

extern EFI_IPSEC_TUNNEL_OPTION  TunnelOptionIp4;


extern EFI_IPSEC_CONFIG_SELECTOR SpdSelectorIp4Tunnel;

extern EFI_IPSEC_CONFIG_SELECTOR SadSelectorIp4Tunnel;


extern CHAR8  EncKeyIp4Tunnel[128]; 
extern CHAR8  AuthKeyIp4Tunnel[128];

extern EFI_IPSEC_SA_DATA2 SadIp4Tunnel;

extern EFI_IPSEC_SPD_DATA SpdIp4Tunnel;

#endif

