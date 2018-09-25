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

  IPsecConfigDataIp6Transport.h

Abstract:

  IPsec Config Data for Transport Mode from the UEFI 2.3 specification.

--*/

#ifndef _IPSEC_CONFIG_DATA_IP6_TRANSPORT_H_
#define _IPSEC_CONFIG_DATA_IP6_TRANSPORT_H_


extern EFI_IPSEC_PROCESS_POLICY InBoundProcessingPolicyIp6Transport;
extern EFI_IPSEC_PROCESS_POLICY OutBoundProcessingPolicyIp6Transport;


extern EFI_IP_ADDRESS_INFO LocalAddressIp6Transport;
extern EFI_IP_ADDRESS_INFO RemoteAddressIp6Transport;

extern EFI_IPSEC_CONFIG_SELECTOR InBoundSpdSelectorIp6Transport;
extern EFI_IPSEC_CONFIG_SELECTOR OutBoundSpdSelectorIp6Transport;

extern EFI_IPSEC_CONFIG_SELECTOR InBoundSadSelectorIp6Transport;
extern EFI_IPSEC_CONFIG_SELECTOR OutBoundSadSelectorIp6Transport;


extern CHAR8  InBoundEncKeyIp6Transport[128]; 
extern CHAR8  InBoundAuthKeyIp6Transport[128];
extern CHAR8  OutBoundEncKeyIp6Transport[128]; 
extern CHAR8  OutBoundAuthKeyIp6Transport[128];

extern EFI_IPSEC_SA_DATA2 InBoundSadIp6Transport;
extern EFI_IPSEC_SA_DATA2 OutBoundSadIp6Transport;

extern EFI_IPSEC_SPD_DATA OutBoundSpdIp6Transport;
extern EFI_IPSEC_SPD_DATA InBoundSpdIp6Transport;

#endif

