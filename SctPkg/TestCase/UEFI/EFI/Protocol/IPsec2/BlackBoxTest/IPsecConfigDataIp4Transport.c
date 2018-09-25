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

  IPsecConfigDataIp4Transport.c

Abstract:

  IPsec Config Transport Mode Setting Data from the UEFI 2.3 specification.

--*/

#include "Efi.h"
#include <UEFI/Protocol/IPsecConfig.h>

EFI_IP_ADDRESS_INFO LocalAddressIp4Transport;
EFI_IP_ADDRESS_INFO RemoteAddressIp4Transport;


//
// Currently Inbound & OutBound use the same EncKey to keep encryption & decryption keys equal 
//
CHAR8  InBoundEncKeyIp4Transport[128]   = "ipv4readylogo3descbcout1"; 
CHAR8  InBoundAuthKeyIp4Transport[128]  = "ipv4readylogsha1out1";
CHAR8  OutBoundEncKeyIp4Transport[128]  = "ipv4readylogo3descbcout1";
CHAR8  OutBoundAuthKeyIp4Transport[128] = "ipv4readylogsha1out1";



//
// In Bound & OutBound transport mode SPD selector 
//
EFI_IPSEC_CONFIG_SELECTOR InBoundSpdSelectorIp4Transport =
{ 
   1,                                 // LocalAddressCount
   &RemoteAddressIp4Transport,        // LocalAddress
   1,                                 // RemoteAddressCount;
   &LocalAddressIp4Transport,         // RemoteAddress
   0xFFFF,                            // NextLayerProtocol
   0,                                 // LocalPort
   65535,                             // LocalPortRange
   0,                                 // RemotePort
   65535                              // RemotePortRange
};

EFI_IPSEC_CONFIG_SELECTOR OutBoundSpdSelectorIp4Transport = 
{ 
   1,                                 // LocalAddressCount
   &LocalAddressIp4Transport,         // LocalAddress
   1,                                 // RemoteAddressCount;
   &RemoteAddressIp4Transport,        // RemoteAddress
   0xFFFF,                            // NextLayerProtocol
   0,                                 // LocalPort
   65535,                             // LocalPortRange
   0,                                 // RemotePort
   65535                              // RemotePortRange
};

EFI_IPSEC_CONFIG_SELECTOR InBoundSadSelectorIp4Transport;
EFI_IPSEC_CONFIG_SELECTOR OutBoundSadSelectorIp4Transport;


EFI_IPSEC_PROCESS_POLICY InBoundProcessingPolicyIp4Transport = 
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

EFI_IPSEC_PROCESS_POLICY OutBoundProcessingPolicyIp4Transport = 
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
EFI_IPSEC_SA_DATA2 InBoundSadIp4Transport = 
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
  &(InBoundSpdSelectorIp4Transport.SpdSelector),      // SpdSelector
  TRUE,                                               // ManualSet
                                                      // TunnelSourceAddress
                                                      // TunnelDestinationAddress 
};


EFI_IPSEC_SA_DATA2 OutBoundSadIp4Transport = 
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
  &(OutBoundSpdSelectorIp4Transport.SpdSelector),    // SpdSelector
  TRUE,                                              // ManualSet
                                                     // TunnelSourceAddress
                                                     // TunnelDestinationAddress
};


//
// InBound & OutBound SPD Transport Mode
//
EFI_IPSEC_SPD_DATA OutBoundSpdIp4Transport =
{
  "OutboundTestIp4TransportMode",                    // Name
  0x0,                                               // PackageFlag
  EfiIPsecOutBound,                                  // TrafficDirection
  EfiIPsecActionProtect,                             // Action
  &OutBoundProcessingPolicyIp4Transport,             // ProcessingPolicy
  1,                                                 // SaIdCount
  {                  
    {                                      // SaId[0]
      0,                            // SPI
      EfiIPsecESP                   // Proto
                                    // DestAddres
    },
  },
};


EFI_IPSEC_SPD_DATA InBoundSpdIp4Transport = 
{
  "InboundTestIp4TransportMode",                       // Name
  0x0,                                                 // PackageFlag
  EfiIPsecInBound,                                     // TrafficDirection
  EfiIPsecActionProtect,                               // Action
  &InBoundProcessingPolicyIp4Transport,                // ProcessingPolicy
  1,                                                   // SaIdCount
  {                  
    {                                     // SaId[0]
      0,                            // SPI
      EfiIPsecESP                   // Proto
                                    // DestAddres
    },
  },
};



