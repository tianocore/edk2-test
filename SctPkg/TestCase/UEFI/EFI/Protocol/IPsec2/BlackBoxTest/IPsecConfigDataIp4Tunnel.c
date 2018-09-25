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

  IPsecConfigDataIp4Tunnel.c

Abstract:

  IPsec Config Tunnel Mode Setting Data from the UEFI 2.3 specification.

--*/

#include "Efi.h"
#include <UEFI/Protocol/IPsecConfig.h>



EFI_IP_ADDRESS_INFO LocalAddressIp4Tunnel;
EFI_IP_ADDRESS_INFO RemoteAddressIp4Tunnel;

EFI_IP_ADDRESS TunnelLocalAddressIp4;
EFI_IP_ADDRESS TunnelRemoteAddressIp4;


CHAR8  EncKeyIp4Tunnel[128]   = "ipv4readylogo3descbcout1"; 
CHAR8  AuthKeyIp4Tunnel[128]  = "ipv4readylogsha1out1";

EFI_IPSEC_TUNNEL_OPTION  TunnelOptionIp4;


EFI_IPSEC_PROCESS_POLICY ProcessingPolicyIp4Tunnel = 
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
  &TunnelOptionIp4,       // TunnelOption
  EfiIPsecESP,            // Proto
  IKE_AALG_SHA1HMAC,      // AuthAlgoId
  IKE_EALG_3DESCBC        // EncAlgoId
};



//
// Tunnel Mode SPD selector 
//
EFI_IPSEC_CONFIG_SELECTOR SpdSelectorIp4Tunnel =
{ 
   1,                             // LocalAddressCount
   &LocalAddressIp4Tunnel,        // LocalAddress
   1,                             // RemoteAddressCount;
   &RemoteAddressIp4Tunnel,       // RemoteAddress
   0xFFFF,                        // NextLayerProtocol
   0,                             // LocalPort
   65534,                         // LocalPortRange
   0,                             // RemotePort
   65534                          // RemotePortRange
};


EFI_IPSEC_CONFIG_SELECTOR SadSelectorIp4Tunnel;

//
// SAD
//
EFI_IPSEC_SA_DATA2 SadIp4Tunnel = 
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
  &(SpdSelectorIp4Tunnel.SpdSelector),          // SpdSelector
  TRUE,                                         // ManualSet
                                                // TunnelSourceAddress
                                                // TunnelDestinationAddress 
};


//
// Bi-direction SPD Tunnel Mode
//
EFI_IPSEC_SPD_DATA SpdIp4Tunnel =
{
  "TestIp4TunnelMode",                     // Name
  0x0,                                     // PackageFlag
  0,                                       // TrafficDirection
  EfiIPsecActionProtect,                   // Action
  &ProcessingPolicyIp4Tunnel,      // ProcessingPolicy
  1,                                       // SaIdCount
  {                  
    {                                      // SaId[0]
      0,                            // SPI
      EfiIPsecESP                   // Proto
                                    // DestAddres
    },
  },
};

