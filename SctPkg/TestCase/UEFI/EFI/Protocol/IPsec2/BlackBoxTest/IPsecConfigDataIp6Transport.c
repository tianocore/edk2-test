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

  IPsecConfigDataIp6Transport.c

Abstract:

  IPsec Config Transport Mode Setting Data from the UEFI 2.3 specification.

--*/

#include "Efi.h"
#include <UEFI/Protocol/IPsecConfig.h>

EFI_IP_ADDRESS_INFO LocalAddressIp6Transport;
EFI_IP_ADDRESS_INFO RemoteAddressIp6Transport;


//
// Currently Inbound & OutBound use the same EncKey to keep encryption & decryption keys equal 
//
CHAR8  InBoundEncKeyIp6Transport[128]   = "ipv6readylogo3descbcout1"; 
CHAR8  InBoundAuthKeyIp6Transport[128]  = "ipv6readylogsha1out1";
CHAR8  OutBoundEncKeyIp6Transport[128]  = "ipv6readylogo3descbcout1";
CHAR8  OutBoundAuthKeyIp6Transport[128] = "ipv6readylogsha1out1";



//
// In Bound & OutBound transport mode SPD selector 
//
EFI_IPSEC_CONFIG_SELECTOR InBoundSpdSelectorIp6Transport =
{ 
   1,                                 // LocalAddressCount
   &RemoteAddressIp6Transport,        // LocalAddress
   1,                                 // RemoteAddressCount;
   &LocalAddressIp6Transport,         // RemoteAddress
   0xFFFF,                            // NextLayerProtocol
   0,                                 // LocalPort
   65535,                             // LocalPortRange
   0,                                 // RemotePort
   65535                              // RemotePortRange
};

EFI_IPSEC_CONFIG_SELECTOR OutBoundSpdSelectorIp6Transport = 
{ 
   1,                                 // LocalAddressCount
   &LocalAddressIp6Transport,         // LocalAddress
   1,                                 // RemoteAddressCount;
   &RemoteAddressIp6Transport,        // RemoteAddress
   0xFFFF,                            // NextLayerProtocol
   0,                                 // LocalPort
   65535,                             // LocalPortRange
   0,                                 // RemotePort
   65535                              // RemotePortRange
};

EFI_IPSEC_CONFIG_SELECTOR InBoundSadSelectorIp6Transport;
EFI_IPSEC_CONFIG_SELECTOR OutBoundSadSelectorIp6Transport;


EFI_IPSEC_PROCESS_POLICY InBoundProcessingPolicyIp6Transport = 
{
  FALSE,                  // ExtSeqNum 
  FALSE,                  // SeqOverflow
  FALSE,                  // FragCheck
               
  {                       // SaLifetime 
    0xFFFFFFFF,      // ByteCount;
    0xFFFFFFFF,      // SoftLifetime;
    0xFFFFFFFF,      // HardLifetime
  },            

  EfiIPsecTransport,      // Mode
  NULL,                   // TunnelOption
  EfiIPsecESP,            // Proto
  IKE_AALG_SHA1HMAC,      // AuthAlgoId
  IKE_EALG_3DESCBC        // EncAlgoId
};

EFI_IPSEC_PROCESS_POLICY OutBoundProcessingPolicyIp6Transport = 
{
  FALSE,                  // ExtSeqNum 
  FALSE,                  // SeqOverflow
  FALSE,                  // FragCheck
               
  {                       // SaLifetime 
    0xFFFFFFFF,      //ByteCount;
    0xFFFFFFFF,      // SoftLifetime;
    0xFFFFFFFF,      // HardLifetime
  },            

  EfiIPsecTransport,      // Mode
  NULL,                   // TunnelOption
  EfiIPsecESP,            // Proto
  IKE_AALG_SHA1HMAC,      // AuthAlgoId
  IKE_EALG_3DESCBC        // EncAlgoId
};


//
// InBound & OutBound SAD
//
EFI_IPSEC_SA_DATA2 InBoundSadIp6Transport = 
{
  EfiIPsecTransport,                                  // Mode
  0,                                                  // SNCount
  10,                                                 // AntiReplayWindows
  {                                                   // AlgoInfo
                   // AhAlgoInfo
    0,             // AuthAlgoId
    0,             // KeyLength
    NULL           // Key            
  }, 
  {                                                   // SaLifetime 
    0xFFFFFFFF,    // ByteCount
    0xFFFFFFFF,    // SoftLifetime
    0xFFFFFFFF,    // HardLifetime
  }, 
  1000,                                               // PathMTU
  &(InBoundSpdSelectorIp6Transport.SpdSelector),      // SpdSelector
  TRUE,                                               // ManualSet
                                                      // TunnelSourceAddress
                                                      // TunnelDestinationAddress 
};


EFI_IPSEC_SA_DATA2 OutBoundSadIp6Transport = 
{
  EfiIPsecTransport,                                 // Mode
  0,                                                 // SNCount
  10,                                                // AntiReplayWindows
  {                                                  // AlgoInfo
                   // AhAlgoInfo
    0,             // AuthAlgoId
    0,             // KeyLength
    NULL           // Key            
  }, 
  {                                                  //SaLifetime 
    0xFFFFFFFF,    // ByteCount
    0xFFFFFFFF,    // SoftLifetime
    0xFFFFFFFF,    // HardLifetime
  },
  1000,                  // PathMTU
  &(OutBoundSpdSelectorIp6Transport.SpdSelector),    // SpdSelector
  TRUE,                                              // ManualSet
                                                     // TunnelSourceAddress
                                                     // TunnelDestinationAddress
};


//
// InBound & OutBound SPD Transport Mode
//
EFI_IPSEC_SPD_DATA OutBoundSpdIp6Transport =
{
  "OutboundTestIp6TransportMode",                    // Name
  0x0,                                               // PackageFlag
  EfiIPsecOutBound,                                  // TrafficDirection
  EfiIPsecActionProtect,                             // Action
  &OutBoundProcessingPolicyIp6Transport,             // ProcessingPolicy
  1,                                                 // SaIdCount
  {                  
    {                                      // SaId[0]
      0,                            // SPI
      EfiIPsecESP                   // Proto
                                    // DestAddres
    },
  },
};


EFI_IPSEC_SPD_DATA InBoundSpdIp6Transport = 
{
  "InboundTestIp6TransportMode",                       // Name
  0x0,                                                 // PackageFlag
  EfiIPsecInBound,                                     // TrafficDirection
  EfiIPsecActionProtect,                               // Action
  &InBoundProcessingPolicyIp6Transport,                // ProcessingPolicy
  1,                                                   // SaIdCount
  {                  
    {                                     // SaId[0]
      0,                            // SPI
      EfiIPsecESP                   // Proto
                                    // DestAddres
    },
  },
};



