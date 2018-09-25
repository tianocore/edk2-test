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

  IPsecConfigDataIp4Transport.h

Abstract:

  IPsec Config Data for Transport Mode from the UEFI 2.3 specification.

--*/

#ifndef _IPSEC_CONFIG_DATA_IP4_TRANSPORT_H_
#define _IPSEC_CONFIG_DATA_IP4_TRANSPORT_H_


extern EFI_IPSEC_PROCESS_POLICY InBoundProcessingPolicyIp4Transport;
extern EFI_IPSEC_PROCESS_POLICY OutBoundProcessingPolicyIp4Transport;


extern EFI_IP_ADDRESS_INFO LocalAddressIp4Transport;
extern EFI_IP_ADDRESS_INFO RemoteAddressIp4Transport;

extern EFI_IPSEC_CONFIG_SELECTOR InBoundSpdSelectorIp4Transport;
extern EFI_IPSEC_CONFIG_SELECTOR OutBoundSpdSelectorIp4Transport;

extern EFI_IPSEC_CONFIG_SELECTOR InBoundSadSelectorIp4Transport;
extern EFI_IPSEC_CONFIG_SELECTOR OutBoundSadSelectorIp4Transport;


extern CHAR8  InBoundEncKeyIp4Transport[128]; 
extern CHAR8  InBoundAuthKeyIp4Transport[128];
extern CHAR8  OutBoundEncKeyIp4Transport[128]; 
extern CHAR8  OutBoundAuthKeyIp4Transport[128];

extern EFI_IPSEC_SA_DATA2 InBoundSadIp4Transport;
extern EFI_IPSEC_SA_DATA2 OutBoundSadIp4Transport;

extern EFI_IPSEC_SPD_DATA OutBoundSpdIp4Transport;
extern EFI_IPSEC_SPD_DATA InBoundSpdIp4Transport;

#endif

