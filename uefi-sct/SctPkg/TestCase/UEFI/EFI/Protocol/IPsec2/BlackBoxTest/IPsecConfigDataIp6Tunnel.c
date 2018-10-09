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

  IPsecConfigDataIp6Tunnel.c

Abstract:

  IPsec Config Tunnel Mode Setting Data from the UEFI 2.3 specification.

--*/

#include "Efi.h"
#include <UEFI/Protocol/IPsecConfig.h>



EFI_IP_ADDRESS_INFO LocalAddressIp6Tunnel;
EFI_IP_ADDRESS_INFO RemoteAddressIp6Tunnel;

EFI_IP_ADDRESS TunnelLocalAddressIp6;
EFI_IP_ADDRESS TunnelRemoteAddressIp6;


CHAR8  EncKeyIp6Tunnel[128]   = "ipv6readylogo3descbcout1"; 
CHAR8  AuthKeyIp6Tunnel[128]  = "ipv6readylogsha1out1";

EFI_IPSEC_TUNNEL_OPTION  TunnelOptionIp6;


EFI_IPSEC_PROCESS_POLICY ProcessingPolicyIp6Tunnel = 
{
  FALSE,                  // ExtSeqNum 
  FALSE,                  // SeqOverflow
  FALSE,                  // FragCheck
               
  {                       // SaLifetime 
    0xFFFFFFFF,      //ByteCount;
    0xFFFFFFFF,      // SoftLifetime;
    0xFFFFFFFF,      // HardLifetime
  },            

  EfiIPsecTunnel,         // Mode
  &TunnelOptionIp6,       // TunnelOption
  EfiIPsecESP,            // Proto
  IKE_AALG_SHA1HMAC,      // AuthAlgoId
  IKE_EALG_3DESCBC        // EncAlgoId
};



//
// Tunnel Mode SPD selector 
//
EFI_IPSEC_CONFIG_SELECTOR SpdSelectorIp6Tunnel =
{ 
   1,                             // LocalAddressCount
   &LocalAddressIp6Tunnel,        // LocalAddress
   1,                             // RemoteAddressCount;
   &RemoteAddressIp6Tunnel,       // RemoteAddress
   0xFFFF,                        // NextLayerProtocol
   0,                             // LocalPort
   65534,                         // LocalPortRange
   0,                             // RemotePort
   65534                          // RemotePortRange
};


EFI_IPSEC_CONFIG_SELECTOR SadSelectorIp6Tunnel;

//
// SAD
//
EFI_IPSEC_SA_DATA2 SadIp6Tunnel = 
{
  EfiIPsecTunnel,                               //Mode
  0,                                            // SNCount
  10, // AntiReplayWindows
  {                                             // AlgoInfo
                   // AhAlgoInfo
    0,             // AuthAlgoId
    0,             // KeyLength
    NULL           // Key            
  }, 
  {                                             //SaLifetime 
    0xFFFFFFFF,    // ByteCount
    0xFFFFFFFF,    // SoftLifetime
    0xFFFFFFFF,    // HardLifetime
  }, 
  1000,                                         // PathMTU
  &(SpdSelectorIp6Tunnel.SpdSelector),          // SpdSelector
  TRUE,                                         // ManualSet
                                                // TunnelSourceAddress
                                                // TunnelDestinationAddress 
};


//
// Bi-direction SPD Tunnel Mode
//
EFI_IPSEC_SPD_DATA SpdIp6Tunnel =
{
  "TestIp6TunnelMode",                     // Name
  0x0,                                     // PackageFlag
  0,                                       // TrafficDirection
  EfiIPsecActionProtect,                   // Action
  &ProcessingPolicyIp6Tunnel,      // ProcessingPolicy
  1,                                       // SaIdCount
  {                  
    {                                      // SaId[0]
      0,                            // SPI
      EfiIPsecESP                   // Proto
                                    // DestAddres
    },
  },
};

