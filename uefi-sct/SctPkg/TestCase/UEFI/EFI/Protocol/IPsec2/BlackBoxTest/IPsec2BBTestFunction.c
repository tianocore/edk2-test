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
    IPsec2BBTestFunction.c

Abstract:
    for EFI Driver IPsec2 Protocol's function Test

--*/
#include "SctLib.h"
#include "IPsec2BBTestMain.h"

static IP_PACKET IP6PacketBuffer[] = {
     {L"IP6_TCP", Ip6PacketTcp, &Ip6PacketTcpSize},            /* IP6 TCP  */
     {L"IP6_UDP", Ip6PacketUdp, &Ip6PacketUdpSize},            /* IP6 UDP  */     
     {NULL,       NULL,         0}                            /* END */   
  };

EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  );

EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  );

EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint3(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  );

EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint4(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  );

EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  );

EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  );

EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint7 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  );

EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint8 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  );


//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_IPSEC2_PROTOCOL                   *IPsec2 = NULL;
  EFI_IPSEC_CONFIG_PROTOCOL             *IpSecConf = NULL;
  EFI_IP4_HEADER                        *Ip4Head = NULL;
  EFI_IP6_HEADER                        *Ip6Head = NULL;

  //
  // init
  //
  IPsec2 = (EFI_IPSEC2_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  //
  // Open IPSEC_CONFIG_PROTOCOL
  //
  SctLocateProtocol(
    &gBlackBoxEfiIPsecConfigProtocolGuid,
    (VOID**) &IpSecConf
    );

  if (IpSecConf != NULL) {
    
    //
    // =====================IP4 Transport Mode Test ==========================
    //
    
    //
    // Config SPD/SAD through IPSEC_CONFIG_PROTOCOL 
    //
    //
    // Initialize IP Sec Configuration Data for Ip4 TransportMode
    //
    Ip4Head = (EFI_IP4_HEADER *)Ip4Packet;

    //
    // 1. Transport mode with NULL OptionBuffer & zero OptionLen , Use algorithm {SHA1HMAC, 3DESCBC}
    //
    Ip4InitIPsecConfigDataTransport (Ip4Head);

    SctPrint(L"Create InBound & OutBound SPD/SAD {SHA1HMAC, 3DESCBC} for Ip4 Transport Mode.\n"); 
    //
    // InBound SPD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &InBoundSpdSelectorIp4Transport,
                          &InBoundSpdIp4Transport,
                          NULL
                          );

    //
    // OutBound SPD
    //    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &OutBoundSpdSelectorIp4Transport,
                          &OutBoundSpdIp4Transport,
                          NULL
                          );
    //
    // InBound SAD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &InBoundSadSelectorIp4Transport,
                          &InBoundSadIp4Transport,
                          NULL
                          );
    //
    // OutBound SAD
    // 
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &OutBoundSadSelectorIp4Transport,
                          &OutBoundSadIp4Transport,
                          NULL
                          );
    BBTestProcessExtFunctionTestCheckpoint1( StandardLib, IPsec2);
  
 
    
    SctPrint(L"Remove created InBound & OutBound SPD/SAD {SHA1HMAC, 3DESCBC} for Ip4 Transport Mode.\n\n\n"); 
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &InBoundSpdSelectorIp4Transport,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &OutBoundSpdSelectorIp4Transport,
                          NULL,
                          NULL
                          );

    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &InBoundSadSelectorIp4Transport,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &OutBoundSadSelectorIp4Transport,
                          NULL,
                          NULL
                          );

    //
    // 2. Transport mode with OptionBuffer & OptionLen , Use algorithm {SHA1HMAC, AESCBC}
    //
   
    InBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_AESCBC;
    InBoundProcessingPolicyIp4Transport.EncAlgoId = IKE_EALG_AESCBC;

    OutBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_AESCBC;
    OutBoundProcessingPolicyIp4Transport.EncAlgoId = IKE_EALG_AESCBC;

    //
    // Reset InBound & OutBound Encrypt Key for AESCBC
    // they shoud be the same
    //
    SctZeroMem (InBoundEncKeyIp4Transport, 128);
    SctCopyMem (InBoundEncKeyIp4Transport, "ipv4readylogo3aescbcout1", 24);
    SctZeroMem (OutBoundEncKeyIp4Transport, 128);
    SctCopyMem (OutBoundEncKeyIp4Transport, "ipv4readylogo3aescbcout1", 24);

    SctPrint(L"Create InBound & OutBound SPD/SAD {SHA1HMAC, AESCBC} for Ip4 Transport Mode.\n"); 

    //
    // InBound SPD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &InBoundSpdSelectorIp4Transport,
                          &InBoundSpdIp4Transport,
                          NULL
                          );

    //
    // OutBound SPD
    //    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &OutBoundSpdSelectorIp4Transport,
                          &OutBoundSpdIp4Transport,
                          NULL
                          );
    //
    // InBound SAD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &InBoundSadSelectorIp4Transport,
                          &InBoundSadIp4Transport,
                          NULL
                          );
    //
    // OutBound SAD
    // 
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &OutBoundSadSelectorIp4Transport,
                          &OutBoundSadIp4Transport,
                          NULL
                          );
    
    BBTestProcessExtFunctionTestCheckpoint2( StandardLib, IPsec2);
    
        
    SctPrint(L"Remove created InBound & OutBound SPD/SAD {SHA1HMAC, AESCBC} for Ip4 Transport Mode.\n\n\n"); 
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &InBoundSpdSelectorIp4Transport,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &OutBoundSpdSelectorIp4Transport,
                          NULL,
                          NULL
                          );

    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &InBoundSadSelectorIp4Transport,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &OutBoundSadSelectorIp4Transport,
                          NULL,
                          NULL
                          );

    //
    // =======================IP4 Tunnel Mode Test ===========================
    //
    //
    // 3. Tunnel mode with NULL OptionBuffer & zero OptionLen , Use algorithm {SHA1HMAC, 3DESCBC}
    //
    SctPrint(L"Create SPD/SAD {SHA1HMAC, 3DESCBC} for Ip4 Tunnel Mode.\n"); 

    Ip4InitIPsecConfigDataTunnel(Ip4Head);

    //
    // SPD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &SpdSelectorIp4Tunnel,
                          &SpdIp4Tunnel,
                          NULL
                          );
    //
    // SAD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &SadSelectorIp4Tunnel,
                          &SadIp4Tunnel,
                          NULL
                          );

    BBTestProcessExtFunctionTestCheckpoint3( StandardLib, IPsec2);
    

    //
    // Remove SPD/SAD Tunnel Mode configuration through IPSEC_CONFIG_PROTOCOL
    //
    SctPrint(L"Remove created SPD/SAD {SHA1HMAC, 3DESCBC} for Ip4 Tunnel Mode.\n\n\n"); 

    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &SpdSelectorIp4Tunnel,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &SadSelectorIp4Tunnel,
                          NULL,
                          NULL
                          );
    
    
    //
    // 4. Tunnel mode with Null OptionBuffer & zero OptionLen , Use algorithm {SHA1HMAC, AESCBC}
    //
    SadIp4Tunnel.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_AESCBC;
    ProcessingPolicyIp4Tunnel.EncAlgoId = IKE_EALG_AESCBC;

    //
    // Reset InBound & OutBound Encrypt Key for AESCBC
    //
    SctZeroMem (EncKeyIp4Tunnel, 128);
    SctCopyMem (EncKeyIp4Tunnel, "ipv4readylogo3aescbcout1", 24);

    
    SctPrint(L"Create SPD/SAD {SHA1HMAC, AESCBC} for Ip4 Tunnel Mode.\n"); 

    //
    // SPD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &SpdSelectorIp4Tunnel,
                          &SpdIp4Tunnel,
                          NULL
                          );
    //
    // SAD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &SadSelectorIp4Tunnel,
                          &SadIp4Tunnel,
                          NULL
                          );

    BBTestProcessExtFunctionTestCheckpoint4( StandardLib, IPsec2);

    //
    // Remove SPD/SAD Tunnel Mode configuration through IPSEC_CONFIG_PROTOCOL
    //
    SctPrint(L"Remove created SPD/SAD {SHA1HMAC, AESCBC} for Ip4 Tunnel Mode.\n"); 

    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &SpdSelectorIp4Tunnel,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &SadSelectorIp4Tunnel,
                          NULL,
                          NULL
                          );



    //
    // =====================IP6 Transport Mode Test ==========================
    //
    

    //
    // Config SPD/SAD through IPSEC_CONFIG_PROTOCOL 
    //
    //
    // Initialize IP Sec Configuration Data for Ip6 TransportMode
    //
    Ip6Head = (EFI_IP6_HEADER *)IP6PacketBuffer[0].Packet;
    
    //
    // 5. Transport mode with NULL OptionBuffer & zero OptionLen , Use algorithm {SHA1HMAC, 3DESCBC}
    //
    Ip6InitIPsecConfigDataTransport (Ip6Head);
    
    SctPrint(L"Create InBound & OutBound SPD/SAD {SHA1HMAC, 3DESCBC} for IP6 Transport Mode.\n");

    //
    // InBound SPD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &InBoundSpdSelectorIp6Transport,
                          &InBoundSpdIp6Transport,
                          NULL
                          );

    //
    // OutBound SPD
    //    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &OutBoundSpdSelectorIp6Transport,
                          &OutBoundSpdIp6Transport,
                          NULL
                          );
    //
    // InBound SAD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &InBoundSadSelectorIp6Transport,
                          &InBoundSadIp6Transport,
                          NULL
                          );
    //
    // OutBound SAD
    // 
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &OutBoundSadSelectorIp6Transport,
                          &OutBoundSadIp6Transport,
                          NULL
                          );
    
    BBTestProcessExtFunctionTestCheckpoint5 (StandardLib, IPsec2);

    
    
    SctPrint(L"Remove created InBound & OutBound SPD/SAD {SHA1HMAC, 3DESCBC} for IP6 Transport Mode.\n\n\n"); 
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &InBoundSpdSelectorIp6Transport,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &OutBoundSpdSelectorIp6Transport,
                          NULL,
                          NULL
                          );

    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &InBoundSadSelectorIp6Transport,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &OutBoundSadSelectorIp6Transport,
                          NULL,
                          NULL
                          );
  
    //
    // 6. Transport mode with OptionBuffer & OptionLen , Use algorithm {SHA1HMAC, AESCBC}
    //
   
    InBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_AESCBC;
    InBoundProcessingPolicyIp6Transport.EncAlgoId = IKE_EALG_AESCBC;

    OutBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_AESCBC;
    OutBoundProcessingPolicyIp6Transport.EncAlgoId = IKE_EALG_AESCBC;

    //
    // Reset InBound & OutBound Encrypt Key for AESCBC
    // they shoud be the same
    //
    SctZeroMem (InBoundEncKeyIp6Transport, 128);
    SctCopyMem (InBoundEncKeyIp6Transport, "ipv6readylogo3aescbcout1", 24);
    SctZeroMem (OutBoundEncKeyIp6Transport, 128);
    SctCopyMem (OutBoundEncKeyIp6Transport, "ipv6readylogo3aescbcout1", 24);

    SctPrint(L"Create InBound & OutBound SPD/SAD {SHA1HMAC, AESCBC} for Ip6 Transport Mode.\n"); 

    //
    // InBound SPD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &InBoundSpdSelectorIp6Transport,
                          &InBoundSpdIp6Transport,
                          NULL
                          );

    //
    // OutBound SPD
    //    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &OutBoundSpdSelectorIp6Transport,
                          &OutBoundSpdIp6Transport,
                          NULL
                          );
    //
    // InBound SAD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &InBoundSadSelectorIp6Transport,
                          &InBoundSadIp6Transport,
                          NULL
                          );
    //
    // OutBound SAD
    // 
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &OutBoundSadSelectorIp6Transport,
                          &OutBoundSadIp6Transport,
                          NULL
                          );
    
    BBTestProcessExtFunctionTestCheckpoint6( StandardLib, IPsec2);
    
        
    SctPrint(L"Remove created InBound & OutBound SPD/SAD {SHA1HMAC, AESCBC} for Ip6 Transport Mode.\n\n\n"); 
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &InBoundSpdSelectorIp6Transport,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &OutBoundSpdSelectorIp6Transport,
                          NULL,
                          NULL
                          );

    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &InBoundSadSelectorIp6Transport,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &OutBoundSadSelectorIp6Transport,
                          NULL,
                          NULL
                          ); 

    //
    // =======================IP6 Tunnel Mode Test ===========================
    //
    //
    // 7. Tunnel mode with NULL OptionBuffer & zero OptionLen , Use algorithm {SHA1HMAC, 3DESCBC}
    //
    SctPrint(L"Create SPD/SAD {SHA1HMAC, 3DESCBC} for Ip6 Tunnel Mode.\n"); 

    Ip6InitIPsecConfigDataTunnel(Ip6Head);

    //
    // SPD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &SpdSelectorIp6Tunnel,
                          &SpdIp6Tunnel,
                          NULL
                          );
    //
    // SAD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &SadSelectorIp6Tunnel,
                          &SadIp6Tunnel,
                          NULL
                          );

    BBTestProcessExtFunctionTestCheckpoint7( StandardLib, IPsec2);
    

    //
    // Remove SPD/SAD Tunnel Mode configuration through IPSEC_CONFIG_PROTOCOL
    //
    SctPrint(L"Remove created SPD/SAD {SHA1HMAC, 3DESCBC} for Ip6 Tunnel Mode.\n\n\n"); 

    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &SpdSelectorIp6Tunnel,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &SadSelectorIp6Tunnel,
                          NULL,
                          NULL
                          );
    
    
    //
    // 8 Tunnel mode with Null OptionBuffer & zero OptionLen , Use algorithm {SHA1HMAC, AESCBC}
    //
    SadIp6Tunnel.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_AESCBC;
    ProcessingPolicyIp6Tunnel.EncAlgoId = IKE_EALG_AESCBC;

    //
    // Reset InBound & OutBound Encrypt Key for AESCBC
    //
    SctZeroMem (EncKeyIp6Tunnel, 128);
    SctCopyMem (EncKeyIp6Tunnel, "ipv6readylogo3aescbcout1", 24);

    
    SctPrint(L"Create SPD/SAD {SHA1HMAC, AESCBC} for Ip6 Tunnel Mode.\n"); 

    //
    // SPD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &SpdSelectorIp6Tunnel,
                          &SpdIp6Tunnel,
                          NULL
                          );
    //
    // SAD
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &SadSelectorIp6Tunnel,
                          &SadIp6Tunnel,
                          NULL
                          );

    BBTestProcessExtFunctionTestCheckpoint8( StandardLib, IPsec2);

    //
    // Remove SPD/SAD Tunnel Mode configuration through IPSEC_CONFIG_PROTOCOL
    //
    SctPrint(L"Remove created SPD/SAD {SHA1HMAC, AESCBC} for Ip4 Tunnel Mode.\n"); 

    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &SpdSelectorIp6Tunnel,
                          NULL,
                          NULL
                          );
    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &SadSelectorIp6Tunnel,
                          NULL,
                          NULL
                          );


    

  }
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EVENT                            RecycleEvent1 = NULL;
  EFI_EVENT                            RecycleEvent2 = NULL;
  EFI_IP4_HEADER                       *Ip4Head = NULL;
  EFI_IP4_HEADER                       *Ip4HeadSrc = NULL;
  UINT8                                *OptionsBuffer = NULL;
  UINT32                               OptionLen;
  EFI_IPSEC_FRAGMENT_DATA              *FragmentTable = NULL;
  UINT32                               FragmentCount;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable1 = NULL;
  UINT32                               TestFragmentCount1;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable2 = NULL;
  UINT32                               TestFragmentCount2;
  EFI_HANDLE                           *NicHandleBuffer = NULL;
  UINTN                                NoHandles;
  UINT32                               i;
  UINT8                                *FragmentData1 = NULL;
  UINT8                                *FragmentData2 = NULL;
  UINT32                               FragmentLen1, FragmentLen2;
  UINT8                                *Ip4PacketTemp = NULL;
  
  //
  // Allocate a NIC handle  which has Udp4 service binding protocol installed
  // IPSEC2.ProcessExt may need Upd4/Udp6 in ike negotiation process
  // 
  gtBS->LocateHandleBuffer(
          ByProtocol, 
          &gBlackBoxEfiUdp4ServiceBindingProtocolGuid, 
          NULL, 
          &NoHandles,
          &NicHandleBuffer
          );
  //
  // Create a temp Ip4 packet buffer for test 
  // to make sure orignal test patten unchanged 
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Ip4PacketSize, 
                   (VOID **)&Ip4PacketTemp
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool - Allocate IP4 Packet space for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto FUNC_EXIT;
  }
  SctCopyMem (Ip4PacketTemp, Ip4Packet, Ip4PacketSize);

  
  //
  // Create One IP4 Packet comprise of {IP4Head, OptionsBuffer, FragmentTable}
  //
  Status = IP4ProcessPacket(
             StandardLib, 
             Ip4PacketTemp, 
             Ip4PacketSize,
             &Ip4Head, 
             (VOID **) &OptionsBuffer,
             &OptionLen,
             &FragmentTable, 
             &FragmentCount
             );

  Ip4HeadSrc = (EFI_IP4_HEADER *)Ip4Packet;

  if (Status != EFI_SUCCESS) {
    goto FUNC_EXIT;
  }
  
  for (i = 0; i < NoHandles; i++) {
    //
    // Save Fragment Table address, Since ProcessExt will change its value 
    // 
    TestFragmentTable1 = FragmentTable;
    TestFragmentCount1 = FragmentCount;

    //
    // OutBound Packet to encrypt Ip4 packet
    //
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) &OptionsBuffer,
                       &OptionLen,
                       &TestFragmentTable1,
                       &TestFragmentCount1,
                       EfiIPsecOutBound,
                       &RecycleEvent1
                       );
  
    
    if (EFI_ERROR(Status)) {
      //
      // Record test failure status & return 
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - OutBound ProcessExt call to encrypt IP4 packet fails",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto FUNC_EXIT;
    }
    
    //
    // Check first ProcessExt Call return parameter status
    //
    if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent1 != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    // Check IPSec Packet Header 
    // Transport mode should only change  Ip4Header.TotalLength & Ip4Header.Checksum
    //
    if ( Ip4HeadSrc->HeaderLength != Ip4Head->HeaderLength
      || Ip4HeadSrc->Version != Ip4Head->Version
      || Ip4HeadSrc->TypeOfService != Ip4Head->TypeOfService
      || Ip4HeadSrc->Identification != Ip4Head->Identification
      || Ip4HeadSrc->Fragmentation != Ip4Head->Fragmentation
      || Ip4HeadSrc->TimeToLive != Ip4Head->TimeToLive
      || Ip4Head->Protocol != IPSEC_ESP_PROTOCOL
      || SctCompareMem (&(Ip4HeadSrc->DestinationAddress), &(Ip4Head->DestinationAddress), sizeof(EFI_IPv4_ADDRESS)) != 0
      || SctCompareMem (&(Ip4HeadSrc->SourceAddress), &(Ip4Head->SourceAddress), sizeof(EFI_IPv4_ADDRESS)) != 0
      ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid001,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Transport Mode OutBound Call to do IP4 IPSEC Encrypt Algorithm {SHA1HMAC, 3DESCBC}",
                   L"%a:%d:Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    //
    // Switch IP SEC packet Src / Dest Address for inbound Decryption
    //
    SctCopyMem (&(Ip4Head->SourceAddress), &(Ip4HeadSrc->DestinationAddress), sizeof(EFI_IPv4_ADDRESS));
    SctCopyMem (&(Ip4Head->DestinationAddress), &(Ip4HeadSrc->SourceAddress), sizeof(EFI_IPv4_ADDRESS));
    
    //
    // Save Fragment Table address, Since ProcessExt will change its value 
    // 
    TestFragmentTable2 = TestFragmentTable1;
    TestFragmentCount2 = TestFragmentCount1;
    
    //
    // Decrypt IpSec packet
    //
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) &OptionsBuffer,
                       &OptionLen,
                       &TestFragmentTable2,
                       &TestFragmentCount2,
                       EfiIPsecInBound,
                       &RecycleEvent2
                       );

    
   if (EFI_ERROR(Status)) {
      //
      // Record test failure status & return 
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - Transport Mode OutBound ProcessExt call to encrypt IP4 packet fails",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto FUNC_EXIT;
    }

    
    //
    // Check if the IP4 packet is unchanged
    //
    if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent2 != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Ip4Header should be unchanged 
    //
    if ( Ip4HeadSrc->HeaderLength != Ip4Head->HeaderLength
      || Ip4HeadSrc->Version != Ip4Head->Version
      || Ip4HeadSrc->TypeOfService != Ip4Head->TypeOfService
      || Ip4HeadSrc->TotalLength != Ip4Head->TotalLength
      || Ip4HeadSrc->Identification != Ip4Head->Identification
      || Ip4HeadSrc->Fragmentation != Ip4Head->Fragmentation
      || Ip4HeadSrc->TimeToLive != Ip4Head->TimeToLive
      || Ip4HeadSrc->Protocol != Ip4Head->Protocol
      || Ip4HeadSrc->Checksum != Ip4Head->Checksum
      || SctCompareMem (&(Ip4HeadSrc->DestinationAddress), &(Ip4Head->SourceAddress), sizeof(EFI_IPv4_ADDRESS)) != 0
      || SctCompareMem (&(Ip4HeadSrc->SourceAddress), &(Ip4Head->DestinationAddress), sizeof(EFI_IPv4_ADDRESS)) != 0
      ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid002,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt -  Transport Mode IPSEC InBound to Decrypt IP4 packet Algorithm {SHA1HMAC, 3DESCBC} and check if Packet Header content is intact",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // check if the Ip4Packet data content is the same as 
    // the content after encrypt & decrypt call
    //
    for (FragmentLen1 = 0, i = 0; i < FragmentCount; i++) {
      FragmentLen1 += FragmentTable[i].FragmentLength;
    }

    for (FragmentLen2 = 0, i = 0; i < TestFragmentCount2; i++) {
      FragmentLen2 += TestFragmentTable2[i].FragmentLength;
    }

    
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (FragmentLen1 == FragmentLen2) {
      for (i = 0; i < FragmentLen1 ; i++) {
        FragmentData1 = FragmentTableGetByte(FragmentTable, FragmentCount, i);
        FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
        if (*FragmentData1 != *FragmentData2) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

        
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid003,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Transport Mode IPSEC InBound to Decrypt IP4 packet Algorithm {SHA1HMAC, 3DESCBC}. Check if Packet Payload Content is intact",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // Signal RecycleEvent to free all resouces allocated inside ProcessExt
    //
    if (RecycleEvent1 != NULL) {
      gtBS->SignalEvent(RecycleEvent1);
      RecycleEvent1 = NULL;
    }
    
    if (RecycleEvent2 != NULL) {
      gtBS->SignalEvent(RecycleEvent2);
      RecycleEvent2 = NULL;
    }
 
  }


FUNC_EXIT:
  //
  // Free all allocated resources 
  //
  if (Ip4Head != NULL) {
    gtBS->FreePool (Ip4Head);
  }

  if (OptionsBuffer != NULL) {
    gtBS->FreePool (OptionsBuffer);
  }

  if (FragmentTable != NULL) {
    gtBS->FreePool (FragmentTable);
  }

  if (Ip4PacketTemp != NULL) {
    gtBS->FreePool (Ip4PacketTemp);
  }
   
  if (NicHandleBuffer != NULL) {
    gtBS->FreePool (NicHandleBuffer);
  }

  if (RecycleEvent1 != NULL) {
    gtBS->SignalEvent(RecycleEvent1);
  }  

  if (RecycleEvent2 != NULL) {
    gtBS->SignalEvent(RecycleEvent2);
  }
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EVENT                            RecycleEvent1 = NULL;
  EFI_EVENT                            RecycleEvent2 = NULL;
  EFI_IP4_HEADER                       *Ip4Head = NULL;
  EFI_IP4_HEADER                       *Ip4HeadSrc = NULL;
  UINT8                                *OptionsBuffer = NULL;
  UINT32                               OptionLen;
  EFI_IPSEC_FRAGMENT_DATA              *FragmentTable = NULL;
  UINT32                               FragmentCount;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable1 = NULL;
  UINT32                               TestFragmentCount1;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable2 = NULL;
  UINT32                               TestFragmentCount2;
  EFI_HANDLE                           *NicHandleBuffer = NULL;
  UINTN                                NoHandles;
  UINT32                               i;
  UINT8                                *FragmentData1 = NULL;
  UINT8                                *FragmentData2 = NULL;
  UINT32                               FragmentLen1, FragmentLen2;
  UINT8                                *Ip4PacketTemp = NULL;
  
  //
  // Allocate a NIC handle  which has Udp4 service binding protocol installed
  // IPSEC2.ProcessExt may need Upd4/Udp6 in ike negotiation process
  // 
  gtBS->LocateHandleBuffer(
          ByProtocol, 
          &gBlackBoxEfiUdp4ServiceBindingProtocolGuid, 
          NULL, 
          &NoHandles,
          &NicHandleBuffer
          );
  //
  // Create a temp Ip4 packet buffer for test 
  // to make sure orignal test patten unchanged 
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Ip4PacketSize, 
                   (VOID **)&Ip4PacketTemp
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool - Allocate IP4 Packet space for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto FUNC_EXIT;
  }
  SctCopyMem (Ip4PacketTemp, Ip4Packet, Ip4PacketSize);

  
  //
  // Create One IP4 Packet comprise of {IP4Head, OptionsBuffer, FragmentTable}
  //
  Status = IP4ProcessPacket(
             StandardLib, 
             Ip4PacketTemp, 
             Ip4PacketSize,
             &Ip4Head, 
             (VOID **) &OptionsBuffer,
             &OptionLen,
             &FragmentTable, 
             &FragmentCount
             );

  Ip4HeadSrc = (EFI_IP4_HEADER *)Ip4Packet;

  if (Status != EFI_SUCCESS) {
    goto FUNC_EXIT;
  }
  
  for (i = 0; i < NoHandles; i++) {
    //
    // Save Fragment Table address, Since ProcessExt will change its value 
    // 
    TestFragmentTable1 = FragmentTable;
    TestFragmentCount1 = FragmentCount;

    //
    // OutBound Packet to encrypt Ip4 packet
    //
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) &OptionsBuffer,
                       &OptionLen,
                       &TestFragmentTable1,
                       &TestFragmentCount1,
                       EfiIPsecOutBound,
                       &RecycleEvent1
                       );
  
    
    if (EFI_ERROR(Status)) {
      //
      // Record test failure status & return 
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - OutBound ProcessExt call to encrypt IP4 packet fails",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto FUNC_EXIT;
    }
    
    //
    // Check first ProcessExt Call return parameter status
    //
    if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent1 != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    // Check IPSec Packet Header 
    // Transport mode should only change  Ip4Header.TotalLength & Ip4Header.Checksum
    //
    if ( Ip4HeadSrc->HeaderLength != Ip4Head->HeaderLength
      || Ip4HeadSrc->Version != Ip4Head->Version
      || Ip4HeadSrc->TypeOfService != Ip4Head->TypeOfService
      || Ip4HeadSrc->Identification != Ip4Head->Identification
      || Ip4HeadSrc->Fragmentation != Ip4Head->Fragmentation
      || Ip4HeadSrc->TimeToLive != Ip4Head->TimeToLive
      || Ip4Head->Protocol != IPSEC_ESP_PROTOCOL
      || SctCompareMem (&(Ip4HeadSrc->DestinationAddress), &(Ip4Head->DestinationAddress), sizeof(EFI_IPv4_ADDRESS)) != 0
      || SctCompareMem (&(Ip4HeadSrc->SourceAddress), &(Ip4Head->SourceAddress), sizeof(EFI_IPv4_ADDRESS)) != 0
      ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid004,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Transport Mode OutBound Call to do IP4 IPSEC Encrypt Algorithm {SHA1HMAC, AESCBC}",
                   L"%a:%d:Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    
    //
    // Switch IP SEC packet Src / Dest Address for inbound Decryption
    //
    SctCopyMem (&(Ip4Head->SourceAddress), &(Ip4HeadSrc->DestinationAddress), sizeof(EFI_IPv4_ADDRESS));
    SctCopyMem (&(Ip4Head->DestinationAddress), &(Ip4HeadSrc->SourceAddress), sizeof(EFI_IPv4_ADDRESS));

    
    //
    // Save Fragment Table address, Since ProcessExt will change its value 
    // 
    TestFragmentTable2 = TestFragmentTable1;
    TestFragmentCount2 = TestFragmentCount1;
    
    //
    // Decrypt IpSec packet
    //
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) &OptionsBuffer,
                       &OptionLen,
                       &TestFragmentTable2,
                       &TestFragmentCount2,
                       EfiIPsecInBound,
                       &RecycleEvent2
                       );

    
   if (EFI_ERROR(Status)) {
      //
      // Record test failure status & return 
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - OutBound ProcessExt call to encrypt IP4 packet fails",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto FUNC_EXIT;
    }

    
    //
    // Check if the IP4 packet is unchanged
    //
    if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent2 != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Ip4Header should be unchanged 
    //
    if ( Ip4HeadSrc->HeaderLength != Ip4Head->HeaderLength
      || Ip4HeadSrc->Version != Ip4Head->Version
      || Ip4HeadSrc->TypeOfService != Ip4Head->TypeOfService
      || Ip4HeadSrc->TotalLength != Ip4Head->TotalLength
      || Ip4HeadSrc->Identification != Ip4Head->Identification
      || Ip4HeadSrc->Fragmentation != Ip4Head->Fragmentation
      || Ip4HeadSrc->TimeToLive != Ip4Head->TimeToLive
      || Ip4HeadSrc->Protocol != Ip4Head->Protocol
      || Ip4HeadSrc->Checksum != Ip4Head->Checksum
      || SctCompareMem (&(Ip4HeadSrc->DestinationAddress), &(Ip4Head->SourceAddress), sizeof(EFI_IPv4_ADDRESS)) != 0
      || SctCompareMem (&(Ip4HeadSrc->SourceAddress), &(Ip4Head->DestinationAddress), sizeof(EFI_IPv4_ADDRESS)) != 0
      ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid005,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Transport Mode IPSEC InBound to Decrypt IP4 packet Algorithm {SHA1HMAC, AESCBC}. Check if Packet Header content is intact",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // check if the Ip4Packet data content is the same as 
    // the content after encrypt & decrypt call
    //
    for (FragmentLen1 = 0, i = 0; i < FragmentCount; i++) {
      FragmentLen1 += FragmentTable[i].FragmentLength;
    }

    for (FragmentLen2 = 0, i = 0; i < TestFragmentCount2; i++) {
      FragmentLen2 += TestFragmentTable2[i].FragmentLength;
    }

    
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (FragmentLen1 == FragmentLen2) {
      for (i = 0; i < FragmentLen1 ; i++) {
        FragmentData1 = FragmentTableGetByte(FragmentTable, FragmentCount, i);
        FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
        if (*FragmentData1 != *FragmentData2) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

        
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid006,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Transport Mode IPSEC InBound  to Decrypt IP4 packet Algorithm {SHA1HMAC, AESCBC}. Check if Packet Payload Content is intact",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // Signal RecycleEvent to free all resouces allocated inside ProcessExt
    //
    if (RecycleEvent1 != NULL) {
      gtBS->SignalEvent(RecycleEvent1);
      RecycleEvent1 = NULL;
    }
    
    if (RecycleEvent2 != NULL) {
      gtBS->SignalEvent(RecycleEvent2);
      RecycleEvent2 = NULL;
    }
 
  }


FUNC_EXIT:
  //
  // Free all allocated resources 
  //
  if (Ip4Head != NULL) {
    gtBS->FreePool (Ip4Head);
  }

  if (OptionsBuffer != NULL) {
    gtBS->FreePool (OptionsBuffer);
  }

  if (FragmentTable != NULL) {
    gtBS->FreePool (FragmentTable);
  }

  if (Ip4PacketTemp != NULL) {
    gtBS->FreePool (Ip4PacketTemp);
  }
   
  if (NicHandleBuffer != NULL) {
    gtBS->FreePool (NicHandleBuffer);
  }

  if (RecycleEvent1 != NULL) {
    gtBS->SignalEvent(RecycleEvent1);
  }  

  if (RecycleEvent2 != NULL) {
    gtBS->SignalEvent(RecycleEvent2);
  }
  
  return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint3(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EVENT                            RecycleEvent1 = NULL;
  EFI_EVENT                            RecycleEvent2 = NULL;
  EFI_IP4_HEADER                       *Ip4Head = NULL;    
  EFI_IP4_HEADER                       *Ip4HeadInnerCpy = NULL;
  EFI_IP4_HEADER                       *Ip4HeadSrc = NULL;
  UINT8                                *OptionsBuffer = NULL;
  UINT32                               OptionLen;
  EFI_IPSEC_FRAGMENT_DATA              *FragmentTable = NULL;
  UINT32                               FragmentCount;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable1 = NULL;
  UINT32                               TestFragmentCount1;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable2 = NULL;
  UINT32                               TestFragmentCount2;
  EFI_HANDLE                           *NicHandleBuffer = NULL;
  UINTN                                NoHandles;
  UINT32                               i;
  UINT8                                *FragmentData2 = NULL;
  UINT32                               FragmentLen2;
  EFI_IP4_HEADER                       ZeroIp4Head;
  UINT8                                *Ip4PacketTemp = NULL;
   
  //
  // Allocate a NIC handle  which has Udp4 service binding protocol installed
  // IPSEC2.ProcessExt may need Upd4/Udp6 in ike negotiation process
  // 
  gtBS->LocateHandleBuffer(
          ByProtocol, 
          &gBlackBoxEfiUdp4ServiceBindingProtocolGuid, 
          NULL, 
          &NoHandles,
          &NicHandleBuffer
          );

  //
  // Create a temp Ip4 packet buffer for test 
  // to make sure orignal test patten unchanged 
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Ip4PacketSize, 
                   (VOID **)&Ip4PacketTemp
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool - Allocate IP4 Packet space for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto FUNC_EXIT;
  }
  SctCopyMem (Ip4PacketTemp, Ip4Packet, Ip4PacketSize);

  
  //
  // Create One IP4 Packet comprise of {IP4Head, OptionsBuffer, FragmentTable}
  //
  Status = IP4ProcessPacket(
             StandardLib, 
             Ip4Packet, 
             Ip4PacketSize,
             &Ip4Head, 
             (VOID **) &OptionsBuffer,
             &OptionLen,
             &FragmentTable, 
             &FragmentCount
             );

  Ip4HeadSrc = (EFI_IP4_HEADER *)Ip4Packet;

  if (Status != EFI_SUCCESS) {
    goto FUNC_EXIT;
  }
  
  for (i = 0; i < NoHandles; i++) {
    //
    // Save Fragment Table address, Since ProcessExt will change its value 
    // 
    TestFragmentTable1 = FragmentTable;
    TestFragmentCount1 = FragmentCount;

    //
    // OutBound Packet to encrypt Ip4 packet
    //
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) &OptionsBuffer,
                       &OptionLen,
                       &TestFragmentTable1,
                       &TestFragmentCount1,
                       EfiIPsecOutBound,
                       &RecycleEvent1
                       );
  
    
    if (EFI_ERROR(Status)) {
      //
      // Record test failure status & return 
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - OutBound ProcessExt call to encrypt IP4 packet fails",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto FUNC_EXIT;
    }
    
    //
    // Check first ProcessExt Call return parameter status
    //
    if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent1 != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    //
    // Check IPSec Packet Header shoud be set to Tunnel IP header  
    //
    if ( Ip4HeadSrc->Version != Ip4Head->Version
      || Ip4HeadSrc->TypeOfService != Ip4Head->TypeOfService
      || Ip4HeadSrc->Identification != Ip4Head->Identification
      || Ip4HeadSrc->Fragmentation != Ip4Head->Fragmentation
      || Ip4HeadSrc->TimeToLive != Ip4Head->TimeToLive
      || Ip4Head->Protocol != IPSEC_ESP_PROTOCOL
      || SctCompareMem (&(Ip4Head->DestinationAddress), &TunnelRemoteAddressIp4, sizeof(EFI_IPv4_ADDRESS)) != 0
      || SctCompareMem (&(Ip4Head->SourceAddress), &TunnelLocalAddressIp4, sizeof(EFI_IPv4_ADDRESS)) != 0
      ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid007,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode OutBound Call to do IP4 IPSEC Encrypt Algorithm {SHA1HMAC, 3DESCBC}",
                   L"%a:%d:Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    
    //
    // Save Fragment Table address, Since ProcessExt will change its value 
    // 
    TestFragmentTable2 = TestFragmentTable1;
    TestFragmentCount2 = TestFragmentCount1;
    
    //
    // Decrypt IpSec packet
    //
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) &OptionsBuffer,
                       &OptionLen,
                       &TestFragmentTable2,
                       &TestFragmentCount2,
                       EfiIPsecInBound,
                       &RecycleEvent2
                       );

    
   if (EFI_ERROR(Status)) {
      //
      // Record test failure status & return 
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - OutBound ProcessExt call to encrypt IP4 packet fails",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto FUNC_EXIT;
    }

    
    //
    // Check if the IP4 packet is unchanged
    //
    if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent2 != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    
    //
    // Ip4Header should be set to reset to Zero
    //
   
    SctZeroMem (&ZeroIp4Head, sizeof (EFI_IP4_HEADER));
    if ( SctCompareMem (Ip4Head, &ZeroIp4Head, sizeof(EFI_IP4_HEADER)) != 0 ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid008,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode IPSEC InBound to Decrypt IP4 packet Algorithm {SHA1HMAC, 3DESCBC}. Check Returned Packet Header is set ZERO",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // Get a Inner IP4 Header copy 
    //
    Status =  gtBS->AllocatePool (
                      EfiBootServicesData,
                      sizeof(EFI_IP4_HEADER), 
                      (VOID **)&Ip4HeadInnerCpy
                      );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - Allocate IP4 Temper Header for testing",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto FUNC_EXIT;
    }

    for (i = 0; i < sizeof(EFI_IP4_HEADER); i++) {
      FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
      ((UINT8 *)Ip4HeadInnerCpy)[i] = *FragmentData2;
    }

    //
    // Check Inner IP4 Header after decryption
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if ( Ip4HeadSrc->Version != Ip4HeadInnerCpy->Version
      || Ip4HeadSrc->TypeOfService != Ip4HeadInnerCpy->TypeOfService
      || Ip4HeadSrc->Identification != Ip4HeadInnerCpy->Identification
      || Ip4HeadSrc->Fragmentation != Ip4HeadInnerCpy->Fragmentation
      || Ip4HeadSrc->TimeToLive != Ip4HeadInnerCpy->TimeToLive
      || Ip4HeadSrc->Protocol != Ip4HeadInnerCpy->Protocol 
      || SctCompareMem (&(Ip4HeadInnerCpy->DestinationAddress), &TunnelRemoteAddressIp4, sizeof(EFI_IPv4_ADDRESS)) != 0
      || SctCompareMem (&(Ip4HeadInnerCpy->SourceAddress), &(Ip4HeadSrc->SourceAddress), sizeof(EFI_IPv4_ADDRESS)) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } 
      
      
    StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid009,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode IPSEC InBound to Decrypt IP4 packet Algorithm {SHA1HMAC, 3DESCBC}. Check IP4 Packet "     \
                     L"InnerHeader is correct",
                     L"%a:%d:",
                     __FILE__,
                     (UINTN)__LINE__
                     );
    //
    // check if the Ip4Packet data content is the same as 
    // the content after encrypt & decrypt call
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for (FragmentLen2 = 0, i = 0; i < TestFragmentCount2; i++) {
      FragmentLen2 += TestFragmentTable2[i].FragmentLength;
    }

    
    if (NTOHS(Ip4HeadSrc->TotalLength) == FragmentLen2) {   
      //
      // Need not to check TCP/UDP pesudo checksum
      //
      if (Ip4HeadInnerCpy->Protocol == EFI_IP_PROTO_UDP) {    
        //
        // Skip UDP header checksum field check
        //
        for (i = sizeof(EFI_IP4_HEADER); i < sizeof(EFI_IP4_HEADER) + sizeof(EFI_UDP_HEAD) - 2 ; i++) {
        
          FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);

          if (Ip4Packet[i] != *FragmentData2) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
          }
        }
        i = sizeof(EFI_IP4_HEADER) + sizeof(EFI_UDP_HEAD);
      } else if (Ip4HeadInnerCpy->Protocol == EFI_IP_PROTO_TCP) {
        //
        // Skip TCP header checksum field check
        //
        for (i = sizeof(EFI_IP4_HEADER); i < sizeof(EFI_IP4_HEADER) + sizeof(EFI_TCP_HEAD) - 4 ; i++) {

          FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);

          if (Ip4Packet[i] != *FragmentData2) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
          }
        }
        i = sizeof(EFI_IP4_HEADER) + sizeof(EFI_TCP_HEAD);
      } else {
        i = sizeof(EFI_IP4_HEADER);
      }

      //
      // Check Payload
      //
      
      for (; i < FragmentLen2 ; i++) {
        FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
        if (Ip4Packet[i] != *FragmentData2) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }

    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

        
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid010,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode IPSEC InBound to Decrypt IP4 packet Algorithm {SHA1HMAC, 3DESCBC}. Check IP4 Packet "     \
                   L"PayLoad is intact",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // Signal RecycleEvent to free all resouces allocated inside ProcessExt
    //
    if (RecycleEvent1 != NULL) {
      gtBS->SignalEvent(RecycleEvent1);
      RecycleEvent1 = NULL;
    }
    
    if (RecycleEvent2 != NULL) {
      gtBS->SignalEvent(RecycleEvent2);
      RecycleEvent2 = NULL;
    }
 
  }


FUNC_EXIT:
  //
  // Free all allocated resources 
  //
  if (Ip4Head != NULL) {
    gtBS->FreePool (Ip4Head);
  }

  if (OptionsBuffer != NULL) {
    gtBS->FreePool (OptionsBuffer);
  }

  if (FragmentTable != NULL) {
    gtBS->FreePool (FragmentTable);
  }
     
  if (Ip4PacketTemp != NULL) {
    gtBS->FreePool (Ip4PacketTemp);
  }

  if (NicHandleBuffer != NULL) {
    gtBS->FreePool (NicHandleBuffer);
  }

  if (Ip4HeadInnerCpy != NULL) {
    gtBS->FreePool (Ip4HeadInnerCpy);
  }

  if (RecycleEvent1 != NULL) {
    gtBS->SignalEvent(RecycleEvent1);
  }  

  if (RecycleEvent2 != NULL) {
    gtBS->SignalEvent(RecycleEvent2);
  }

  return EFI_SUCCESS;
}




EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint4(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EVENT                            RecycleEvent1 = NULL;
  EFI_EVENT                            RecycleEvent2 = NULL;
  EFI_IP4_HEADER                       *Ip4Head = NULL;
  EFI_IP4_HEADER                       *Ip4HeadInnerCpy = NULL;
  EFI_IP4_HEADER                       *Ip4HeadSrc = NULL;
  UINT8                                *OptionsBuffer = NULL;
  UINT32                               OptionLen;
  EFI_IPSEC_FRAGMENT_DATA              *FragmentTable = NULL;
  UINT32                               FragmentCount;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable1 = NULL;
  UINT32                               TestFragmentCount1;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable2 = NULL;
  UINT32                               TestFragmentCount2;
  EFI_HANDLE                           *NicHandleBuffer = NULL;
  UINTN                                NoHandles;
  UINT32                               i;
  UINT8                                *FragmentData2 = NULL;
  UINT32                               FragmentLen2;
  EFI_IP4_HEADER                       ZeroIp4Head;
  UINT8                                *Ip4PacketTemp = NULL;

  //
  // Allocate a NIC handle  which has Udp4 service binding protocol installed
  // IPSEC2.ProcessExt may need Upd4/Udp6 in ike negotiation process
  // 
  gtBS->LocateHandleBuffer(
          ByProtocol, 
          &gBlackBoxEfiUdp4ServiceBindingProtocolGuid, 
          NULL, 
          &NoHandles,
          &NicHandleBuffer
          );

  //
  // Create a temp Ip4 packet buffer for test 
  // to make sure orignal test patten unchanged 
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Ip4PacketSize, 
                   (VOID **)&Ip4PacketTemp
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool - Allocate IP4 Packet space for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto FUNC_EXIT;
  }
  SctCopyMem (Ip4PacketTemp, Ip4Packet, Ip4PacketSize);

  
  //
  // Create One IP4 Packet comprise of {IP4Head, OptionsBuffer, FragmentTable}
  //
  Status = IP4ProcessPacket(
             StandardLib, 
             Ip4Packet, 
             Ip4PacketSize,
             &Ip4Head, 
             (VOID **) &OptionsBuffer,
             &OptionLen,
             &FragmentTable, 
             &FragmentCount
             );

  Ip4HeadSrc = (EFI_IP4_HEADER *)Ip4Packet;

  if (Status != EFI_SUCCESS) {
    goto FUNC_EXIT;
  }
  
  for (i = 0; i < NoHandles; i++) {
    //
    // Save Fragment Table address, Since ProcessExt will change its value 
    // 
    TestFragmentTable1 = FragmentTable;
    TestFragmentCount1 = FragmentCount;

    //
    // OutBound Packet to encrypt Ip4 packet
    //
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) &OptionsBuffer,
                       &OptionLen,
                       &TestFragmentTable1,
                       &TestFragmentCount1,
                       EfiIPsecOutBound,
                       &RecycleEvent1
                       );
  
    
    if (EFI_ERROR(Status)) {
      //
      // Record test failure status & return 
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - OutBound ProcessExt call to encrypt IP4 packet fails",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto FUNC_EXIT;
    }
    
    //
    // Check first ProcessExt Call return parameter status
    //
    if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent1 != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    //
    // Check IPSec Packet Header shoud be set to Tunnel IP header  
    //
    if ( Ip4HeadSrc->Version != Ip4Head->Version
      || Ip4HeadSrc->TypeOfService != Ip4Head->TypeOfService
      || Ip4HeadSrc->Identification != Ip4Head->Identification
      || Ip4HeadSrc->Fragmentation != Ip4Head->Fragmentation
      || Ip4HeadSrc->TimeToLive != Ip4Head->TimeToLive
      || Ip4Head->Protocol != IPSEC_ESP_PROTOCOL
      || SctCompareMem (&(Ip4Head->DestinationAddress), &TunnelRemoteAddressIp4, sizeof(EFI_IPv4_ADDRESS)) != 0
      || SctCompareMem (&(Ip4Head->SourceAddress), &TunnelLocalAddressIp4, sizeof(EFI_IPv4_ADDRESS)) != 0
      ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid011,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode OutBound Call to do IP4 IPSEC Encrypt Algorithm {SHA1HMAC, AESCBC}",
                   L"%a:%d:Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    
    //
    // Save Fragment Table address, Since ProcessExt will change its value 
    // 
    TestFragmentTable2 = TestFragmentTable1;
    TestFragmentCount2 = TestFragmentCount1;
    
    //
    // Decrypt IpSec packet
    //
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) &OptionsBuffer,
                       &OptionLen,
                       &TestFragmentTable2,
                       &TestFragmentCount2,
                       EfiIPsecInBound,
                       &RecycleEvent2
                       );

    
   if (EFI_ERROR(Status)) {
      //
      // Record test failure status & return 
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - OutBound ProcessExt call to encrypt IP4 packet fails",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto FUNC_EXIT;
    }

    
    //
    // Check if the IP4 packet is unchanged
    //
    if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent2 != NULL) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    
    //
    // Ip4Header should be set to reset to Zero
    //
   
    SctZeroMem (&ZeroIp4Head, sizeof (EFI_IP4_HEADER));
    if ( SctCompareMem (Ip4Head, &ZeroIp4Head, sizeof(EFI_IP4_HEADER)) != 0 ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid012,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode IPSEC InBound to Decrypt IP4 packet Algorithm {SHA1HMAC, AESCBC}. Check Returned Packet Header is set ZERO",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // Get a Inner IP4 Header copy 
    //
    Status =  gtBS->AllocatePool (
                      EfiBootServicesData,
                      sizeof(EFI_IP4_HEADER), 
                      (VOID **)&Ip4HeadInnerCpy
                      );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - Allocate IP4 Temper Header for testing",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto FUNC_EXIT;
    }
    
    for (i = 0; i < sizeof(EFI_IP4_HEADER); i++) {
      FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
      ((UINT8 *)Ip4HeadInnerCpy)[i] = *FragmentData2;
    }
    
    //
    // Check Inner IP4 Header after decryption
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if ( Ip4HeadSrc->Version != Ip4HeadInnerCpy->Version
      || Ip4HeadSrc->TypeOfService != Ip4HeadInnerCpy->TypeOfService
      || Ip4HeadSrc->Identification != Ip4HeadInnerCpy->Identification
      || Ip4HeadSrc->Fragmentation != Ip4HeadInnerCpy->Fragmentation
      || Ip4HeadSrc->TimeToLive != Ip4HeadInnerCpy->TimeToLive
      || Ip4HeadSrc->Protocol != Ip4HeadInnerCpy->Protocol 
      || SctCompareMem (&(Ip4HeadInnerCpy->DestinationAddress), &TunnelRemoteAddressIp4, sizeof(EFI_IPv4_ADDRESS)) != 0
      || SctCompareMem (&(Ip4HeadInnerCpy->SourceAddress), &(Ip4HeadSrc->SourceAddress), sizeof(EFI_IPv4_ADDRESS)) != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } 
         
    StandardLib->RecordAssertion (
                        StandardLib,
                        AssertionType,
                        gIpSec2BBTestFunctionAssertionGuid013,
                        L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode IPSEC InBound to Decrypt IP4 packet Algorithm {SHA1HMAC, AESCBC}. Check IP4 Packet "     \
                        L"InnerHeader is correct",
                        L"%a:%d:",
                        __FILE__,
                        (UINTN)__LINE__
                        );

    //
    // check if the Ip4Packet data content is the same as 
    // the content after encrypt & decrypt call
    //
    for (FragmentLen2 = 0, i = 0; i < TestFragmentCount2; i++) {
      FragmentLen2 += TestFragmentTable2[i].FragmentLength;
    }

    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (NTOHS(Ip4HeadSrc->TotalLength) == FragmentLen2) {
      //
      // Need not to check TCP/UDP pesudo checksum
      //
      if (Ip4HeadInnerCpy->Protocol == EFI_IP_PROTO_UDP) {
        //
        // Skip UDP header checksum field check
        //
        for (i = sizeof(EFI_IP4_HEADER); i < sizeof(EFI_IP4_HEADER) + sizeof(EFI_UDP_HEAD) - 2 ; i++) {

          FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);

          if (Ip4Packet[i] != *FragmentData2) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
          }
        }
        i = sizeof(EFI_IP4_HEADER) + sizeof(EFI_UDP_HEAD);
      } else if (Ip4HeadInnerCpy->Protocol == EFI_IP_PROTO_TCP) {
        //
        // Skip TCP header checksum field check
        //
        for (i = sizeof(EFI_IP4_HEADER); i < sizeof(EFI_IP4_HEADER) + sizeof(EFI_TCP_HEAD) - 4 ; i++) {
          
          FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);

          if (Ip4Packet[i] != *FragmentData2) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
          }
        }
        i = sizeof(EFI_IP4_HEADER) + sizeof(EFI_TCP_HEAD);
      } else {
        i = sizeof(EFI_IP4_HEADER);
      }

      //
      // Check Payload
      //
      
      for (; i < FragmentLen2 ; i++) {
        FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
        if (Ip4Packet[i] != *FragmentData2) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          break;
        }
      }
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

        
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestFunctionAssertionGuid014,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt -  IPSEC Encrypt & Decrypt IP4 packet Algorithm {SHA1HMAC, AESCBC} and Check IP4 Packet "     \
                   L"PayLoad is intact",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    //
    // Signal RecycleEvent to free all resouces allocated inside ProcessExt
    //
    if (RecycleEvent1 != NULL) {
      gtBS->SignalEvent(RecycleEvent1);
      RecycleEvent1 = NULL;
    }
    
    if (RecycleEvent2 != NULL) {
      gtBS->SignalEvent(RecycleEvent2);
      RecycleEvent2 = NULL;
    }
 
  }


FUNC_EXIT:
  //
  // Free all allocated resources 
  //
  if (Ip4Head != NULL) {
    gtBS->FreePool (Ip4Head);
  }

  if (OptionsBuffer != NULL) {
    gtBS->FreePool (OptionsBuffer);
  }

  if (FragmentTable != NULL) {
    gtBS->FreePool (FragmentTable);
  }
     
  if (Ip4PacketTemp != NULL) {
    gtBS->FreePool (Ip4PacketTemp);
  }

  if (NicHandleBuffer != NULL) {
    gtBS->FreePool (NicHandleBuffer);
  }
  
  if (Ip4HeadInnerCpy != NULL) {
    gtBS->FreePool (Ip4HeadInnerCpy);
  }

  if (RecycleEvent1 != NULL) {
    gtBS->SignalEvent(RecycleEvent1);
  }  

  if (RecycleEvent2 != NULL) {
    gtBS->SignalEvent(RecycleEvent2);
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EVENT                            RecycleEvent1 = NULL;
  EFI_EVENT                            RecycleEvent2 = NULL;
  EFI_IP6_HEADER                       *Ip6Head = NULL;
  EFI_IP6_HEADER                       *Ip6HeadSrc = NULL;
  UINT8                                *OptionsBuffer = NULL;
  UINT32                               OptionLen;
  EFI_IPSEC_FRAGMENT_DATA              *FragmentTable = NULL;
  UINT32                               FragmentCount;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable1 = NULL;
  UINT32                               TestFragmentCount1;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable2 = NULL;
  UINT32                               TestFragmentCount2;
  EFI_HANDLE                           *NicHandleBuffer = NULL;
  UINTN                                NoHandles;
  UINT32                               i;
  UINT8                                *FragmentData1 = NULL;
  UINT8                                *FragmentData2 = NULL;
  UINT32                               FragmentLen1, FragmentLen2;
  UINT8                                *Ip6PacketTemp = NULL;
  UINT32                               PacketIndex;

  
  //
  // Allocate a NIC handle  which has Udp6 service binding protocol installed
  // IPSEC2.ProcessExt may need Upd4/Udp6 in ike negotiation process
  // 
  gtBS->LocateHandleBuffer(
          ByProtocol, 
          &gBlackBoxEfiUdp6ServiceBindingProtocolGuid, 
          NULL, 
          &NoHandles,
          &NicHandleBuffer
          );

  for (PacketIndex = 0; IP6PacketBuffer[PacketIndex].PacketName != NULL; PacketIndex++) {
  
    //
    // Create a temp Ip6 packet buffer for test 
    // to make sure orignal test patten unchanged 
    //
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     *(IP6PacketBuffer[PacketIndex].PacketSize), 
                     (VOID **)&Ip6PacketTemp
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - Allocate IP6 Packet space for testing",
                     L"%a:%d:Status - %r. Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
      goto FUNC_EXIT;
    }
    SctCopyMem (
      Ip6PacketTemp, 
      IP6PacketBuffer[PacketIndex].Packet, 
      *(IP6PacketBuffer[PacketIndex].PacketSize)
      );
  
    
    //
    // Create One IP6 Packet comprise of {IP6Head, OptionsBuffer, FragmentTable}
    //
    Status = IP6ProcessPacket(
               StandardLib, 
               Ip6PacketTemp, 
               *(IP6PacketBuffer[PacketIndex].PacketSize),
               &Ip6Head, 
               (VOID **) &OptionsBuffer,
               &OptionLen,
               &FragmentTable, 
               &FragmentCount
               );
  
    Ip6HeadSrc = (EFI_IP6_HEADER *)IP6PacketBuffer[PacketIndex].Packet;
  
    if (Status != EFI_SUCCESS) {
      goto FUNC_EXIT;
    }
    
    for (i = 0; i < NoHandles; i++) {
      //
      // Save Fragment Table address, Since ProcessExt will change its value 
      // 
      TestFragmentTable1 = FragmentTable;
      TestFragmentCount1 = FragmentCount;
  
      //
      // OutBound Packet to encrypt Ip6 packet
      //
      Status = IPsec2->ProcessExt (
                         IPsec2,
                         NicHandleBuffer[i],
                         IP_VERSION_6,
                         Ip6Head,
                         &(Ip6Head->NextHeader),
                         (VOID **) &OptionsBuffer,
                         &OptionLen,
                         &TestFragmentTable1,
                         &TestFragmentCount1,
                         EfiIPsecOutBound,
                         &RecycleEvent1
                         );
    
      
      if (EFI_ERROR(Status)) {
        //
        // Record test failure status & return 
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"AllocatePool - OutBound ProcessExt call to encrypt IP6 packet fails",
                       L"%a:%d:Status - %r. Packet Type : %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       IP6PacketBuffer[PacketIndex].PacketName
                       );
        goto FUNC_EXIT;
      }
      
      //
      // Check first ProcessExt Call return parameter status
      //
      if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent1 != NULL) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // Check IP6 IPSec Packet Header 
      // Transport mode should only change  Ip6Header.PyaloadLength
      //
      if ( Ip6HeadSrc->TrafficClassH != Ip6Head->TrafficClassH
        || Ip6HeadSrc->Version != Ip6Head->Version
        || Ip6HeadSrc->FlowLabelH != Ip6Head->FlowLabelH
        || Ip6HeadSrc->TrafficClassL != Ip6Head->TrafficClassL
        || Ip6HeadSrc->FlowLabelL != Ip6Head->FlowLabelL
        || Ip6Head->NextHeader != IPSEC_ESP_PROTOCOL
        || Ip6HeadSrc->HopLimit != Ip6Head->HopLimit
        || SctCompareMem (&(Ip6HeadSrc->DestinationAddress), &(Ip6Head->DestinationAddress), sizeof(EFI_IPv6_ADDRESS)) != 0
        || SctCompareMem (&(Ip6HeadSrc->SourceAddress), &(Ip6Head->SourceAddress), sizeof(EFI_IPv6_ADDRESS)) != 0
        ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid015,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Transport Mode OutBound Call to do IPSEC IP6 Packet Encrypt Algorithm {SHA1HMAC, 3DESCBC}",
                     L"%a:%d:Status=%r. Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__, 
                     Status,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
  
      //
      // Switch IP SEC packet Src / Dest Address for inbound Decryption
      //
      SctCopyMem (&(Ip6Head->SourceAddress), &(Ip6HeadSrc->DestinationAddress), sizeof(EFI_IPv6_ADDRESS));
      SctCopyMem (&(Ip6Head->DestinationAddress), &(Ip6HeadSrc->SourceAddress), sizeof(EFI_IPv6_ADDRESS));
      
      //
      // Save Fragment Table address, Since ProcessExt will change its value 
      // 
      TestFragmentTable2 = TestFragmentTable1;
      TestFragmentCount2 = TestFragmentCount1;
      
      //
      // Decrypt IpSec packet
      //
      Status = IPsec2->ProcessExt (
                         IPsec2,
                         NicHandleBuffer[i],
                         IP_VERSION_6,
                         Ip6Head,
                         &(Ip6Head->NextHeader),
                         (VOID **) &OptionsBuffer,
                         &OptionLen,
                         &TestFragmentTable2,
                         &TestFragmentCount2,
                         EfiIPsecInBound,
                         &RecycleEvent2
                         );
  
      
     if (EFI_ERROR(Status)) {
        //
        // Record test failure status & return 
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"AllocatePool - OutBound ProcessExt call to encrypt IP6 packet fails",
                       L"%a:%d:Status - %r. Packet Type : %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       IP6PacketBuffer[PacketIndex].PacketName
                       );
        goto FUNC_EXIT;
      }
  
      
      //
      // Check if the IP6 packet is unchanged
      //
      if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent2 != NULL) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
  
      //
      // Ip6Header should be unchanged 
      //
      if ( Ip6HeadSrc->TrafficClassH != Ip6Head->TrafficClassH
        || Ip6HeadSrc->Version != Ip6Head->Version
        || Ip6HeadSrc->FlowLabelH != Ip6Head->FlowLabelH
        || Ip6HeadSrc->TrafficClassL != Ip6Head->TrafficClassL
        || Ip6HeadSrc->FlowLabelL != Ip6Head->FlowLabelL
        || Ip6HeadSrc->PayloadLength != Ip6Head->PayloadLength
        || Ip6HeadSrc->NextHeader != Ip6Head->NextHeader
        || Ip6HeadSrc->HopLimit != Ip6Head->HopLimit
        || SctCompareMem (&(Ip6HeadSrc->DestinationAddress), &(Ip6Head->SourceAddress), sizeof(EFI_IPv6_ADDRESS)) != 0
        || SctCompareMem (&(Ip6HeadSrc->SourceAddress), &(Ip6Head->DestinationAddress), sizeof(EFI_IPv6_ADDRESS)) != 0
        ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
  
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid016,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Transport Mode IPSEC IP6 InBound to Decrypt Algorithm {SHA1HMAC, 3DESCBC}. Check if Packet Header content is intact",
                     L"%a:%d:  Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
  
      //
      // check if the Ip6Packet data content is the same as 
      // the content after encrypt & decrypt call
      //
      for (FragmentLen1 = 0, i = 0; i < FragmentCount; i++) {
        FragmentLen1 += FragmentTable[i].FragmentLength;
      }
  
      for (FragmentLen2 = 0, i = 0; i < TestFragmentCount2; i++) {
        FragmentLen2 += TestFragmentTable2[i].FragmentLength;
      }
  
      
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (FragmentLen1 == FragmentLen2) {
        for (i = 0; i < FragmentLen1 ; i++) {
          FragmentData1 = FragmentTableGetByte(FragmentTable, FragmentCount, i);
          FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
          if (*FragmentData1 != *FragmentData2) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
          }
        }
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
  
          
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid017,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Transport Mode IPSEC InBound to Decrypt IP6 packet Algorithm {SHA1HMAC, 3DESCBC}. Check if Packet Payload Content is intact",
                     L"%a:%d:  Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                    IP6PacketBuffer[PacketIndex].PacketName
                     );
  
      //
      // Signal RecycleEvent to free all resouces allocated inside ProcessExt
      //
      if (RecycleEvent1 != NULL) {
        gtBS->SignalEvent(RecycleEvent1);
        RecycleEvent1 = NULL;
      }
      
      if (RecycleEvent2 != NULL) {
        gtBS->SignalEvent(RecycleEvent2);
        RecycleEvent2 = NULL;
      }
   
    }

    if (Ip6Head != NULL) {
      gtBS->FreePool (Ip6Head);
      Ip6Head = NULL;
    }
    
    if (OptionsBuffer != NULL) {
      gtBS->FreePool (OptionsBuffer);
      OptionsBuffer = NULL;
    }
    
    if (FragmentTable != NULL) {
      gtBS->FreePool (FragmentTable);
      FragmentTable = NULL;
    }
    
    if (Ip6PacketTemp != NULL) {
      gtBS->FreePool (Ip6PacketTemp);
      Ip6PacketTemp = NULL;
    }

  }

FUNC_EXIT:
  //
  // Free all allocated resources 
  //
  if (Ip6Head != NULL) {
    gtBS->FreePool (Ip6Head);
  }

  if (OptionsBuffer != NULL) {
    gtBS->FreePool (OptionsBuffer);
  }

  if (FragmentTable != NULL) {
    gtBS->FreePool (FragmentTable);
  }

  if (Ip6PacketTemp != NULL) {
    gtBS->FreePool (Ip6PacketTemp);
  }
   
  if (NicHandleBuffer != NULL) {
    gtBS->FreePool (NicHandleBuffer);
  }
  
  if (RecycleEvent1 != NULL) {
    gtBS->SignalEvent(RecycleEvent1);
  }  

  if (RecycleEvent2 != NULL) {
    gtBS->SignalEvent(RecycleEvent2);
  }
  
  return EFI_SUCCESS;
}



EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EVENT                            RecycleEvent1 = NULL;
  EFI_EVENT                            RecycleEvent2 = NULL;
  EFI_IP6_HEADER                       *Ip6Head = NULL;
  EFI_IP6_HEADER                       *Ip6HeadSrc = NULL;
  UINT8                                *OptionsBuffer = NULL;
  UINT32                               OptionLen;
  EFI_IPSEC_FRAGMENT_DATA              *FragmentTable = NULL;
  UINT32                               FragmentCount;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable1 = NULL;
  UINT32                               TestFragmentCount1;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable2 = NULL;
  UINT32                               TestFragmentCount2;
  EFI_HANDLE                           *NicHandleBuffer = NULL;
  UINTN                                NoHandles;
  UINT32                               i;
  UINT8                                *FragmentData1 = NULL;
  UINT8                                *FragmentData2 = NULL;
  UINT32                               FragmentLen1, FragmentLen2;
  UINT8                                *Ip6PacketTemp = NULL;
  UINT32                               PacketIndex;

  //
  // Allocate a NIC handle  which has Udp6 service binding protocol installed
  // IPSEC2.ProcessExt may need Upd4/Udp6 in ike negotiation process
  // 
  gtBS->LocateHandleBuffer(
          ByProtocol, 
          &gBlackBoxEfiUdp6ServiceBindingProtocolGuid, 
          NULL, 
          &NoHandles,
          &NicHandleBuffer
          );
  
  for (PacketIndex = 0; IP6PacketBuffer[PacketIndex].PacketName != NULL; PacketIndex++) {

    //
    // Create a temp Ip6 packet buffer for test 
    // to make sure orignal test patten unchanged 
    //
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     *(IP6PacketBuffer[PacketIndex].PacketSize), 
                     (VOID **)&Ip6PacketTemp
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - Allocate IP6 packet space for testing",
                     L"%a:%d:Status - %r. Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,                     
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
      goto FUNC_EXIT;
    }
    SctCopyMem (
      Ip6PacketTemp, 
      IP6PacketBuffer[PacketIndex].Packet, 
      *(IP6PacketBuffer[PacketIndex].PacketSize)
      );
  
    
    //
    // Create One IP6 Packet comprise of {IP6Head, OptionsBuffer, FragmentTable}
    //
    Status = IP6ProcessPacket(
               StandardLib, 
               Ip6PacketTemp, 
               *(IP6PacketBuffer[PacketIndex].PacketSize),
               &Ip6Head, 
               (VOID **) &OptionsBuffer,
               &OptionLen,
               &FragmentTable, 
               &FragmentCount
               );
  
    Ip6HeadSrc = (EFI_IP6_HEADER *)IP6PacketBuffer[PacketIndex].Packet;
  
    if (Status != EFI_SUCCESS) {
      goto FUNC_EXIT;
    }
    
    for (i = 0; i < NoHandles; i++) {
      //
      // Save Fragment Table address, Since ProcessExt will change its value 
      // 
      TestFragmentTable1 = FragmentTable;
      TestFragmentCount1 = FragmentCount;
  
      //
      // OutBound Packet to encrypt Ip6 packet
      //
      Status = IPsec2->ProcessExt (
                         IPsec2,
                         NicHandleBuffer[i],
                         IP_VERSION_6,
                         Ip6Head,
                         &(Ip6Head->NextHeader),
                         (VOID **) &OptionsBuffer,
                         &OptionLen,
                         &TestFragmentTable1,
                         &TestFragmentCount1,
                         EfiIPsecOutBound,
                         &RecycleEvent1
                         );
    
      
      if (EFI_ERROR(Status)) {
        //
        // Record test failure status & return 
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"AllocatePool - OutBound ProcessExt call to encrypt IP6 packet fails",
                       L"%a:%d:Status - %r. Packet Type : %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       IP6PacketBuffer[PacketIndex].PacketName
                       );
        goto FUNC_EXIT;
      }
      
      //
      // Check first ProcessExt Call return parameter status
      //
      if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent1 != NULL) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // Check IP6 IPSec Packet Header 
      // Transport mode should only change  Ip6Header.PayLoad 
      //
      if ( Ip6HeadSrc->TrafficClassH != Ip6Head->TrafficClassH
        || Ip6HeadSrc->Version != Ip6Head->Version
        || Ip6HeadSrc->FlowLabelH != Ip6Head->FlowLabelH
        || Ip6HeadSrc->TrafficClassL != Ip6Head->TrafficClassL
        || Ip6HeadSrc->FlowLabelL != Ip6Head->FlowLabelL
        || Ip6Head->NextHeader != IPSEC_ESP_PROTOCOL
        || Ip6HeadSrc->HopLimit != Ip6Head->HopLimit
        || SctCompareMem (&(Ip6HeadSrc->DestinationAddress), &(Ip6Head->DestinationAddress), sizeof(EFI_IPv6_ADDRESS)) != 0
        || SctCompareMem (&(Ip6HeadSrc->SourceAddress), &(Ip6Head->SourceAddress), sizeof(EFI_IPv6_ADDRESS)) != 0
        ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid018,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Transport Mode OutBound Call to do IPSEC IP6 packet Encrypt Algorithm {SHA1HMAC, AESCBC}",
                     L"%a:%d:Status=%r. Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
      
      //
      // Switch IP6 SEC packet Src / Dest Address for inbound Decryption
      //
      SctCopyMem (&(Ip6Head->SourceAddress), &(Ip6HeadSrc->DestinationAddress), sizeof(EFI_IPv6_ADDRESS));
      SctCopyMem (&(Ip6Head->DestinationAddress), &(Ip6HeadSrc->SourceAddress), sizeof(EFI_IPv6_ADDRESS));
  
      
      //
      // Save Fragment Table address, Since ProcessExt will change its value 
      // 
      TestFragmentTable2 = TestFragmentTable1;
      TestFragmentCount2 = TestFragmentCount1;
      
      //
      // Decrypt IpSec packet
      //
      Status = IPsec2->ProcessExt (
                         IPsec2,
                         NicHandleBuffer[i],
                         IP_VERSION_6,
                         Ip6Head,
                         &(Ip6Head->NextHeader),
                         (VOID **) &OptionsBuffer,
                         &OptionLen,
                         &TestFragmentTable2,
                         &TestFragmentCount2,
                         EfiIPsecInBound,
                         &RecycleEvent2
                         );
  
      
     if (EFI_ERROR(Status)) {
        //
        // Record test failure status & return 
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"AllocatePool - OutBound ProcessExt call to encrypt IP6 packet fails",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        goto FUNC_EXIT;
      }
  
      
      //
      // Check if the IP6 packet is unchanged
      //
      if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent2 != NULL) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
  
      //
      // Ip6Header should be unchanged 
      //
      if ( Ip6HeadSrc->TrafficClassH != Ip6Head->TrafficClassH
        || Ip6HeadSrc->Version != Ip6Head->Version
        || Ip6HeadSrc->FlowLabelH != Ip6Head->FlowLabelH
        || Ip6HeadSrc->TrafficClassL != Ip6Head->TrafficClassL
        || Ip6HeadSrc->FlowLabelL != Ip6Head->FlowLabelL
        || Ip6HeadSrc->PayloadLength != Ip6Head->PayloadLength
        || Ip6HeadSrc->NextHeader != Ip6Head->NextHeader
        || Ip6HeadSrc->HopLimit != Ip6Head->HopLimit
        || SctCompareMem (&(Ip6HeadSrc->DestinationAddress), &(Ip6Head->SourceAddress), sizeof(EFI_IPv6_ADDRESS)) != 0
        || SctCompareMem (&(Ip6HeadSrc->SourceAddress), &(Ip6Head->DestinationAddress), sizeof(EFI_IPv6_ADDRESS)) != 0
        ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
  
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid019,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Transport Mode IPSEC InBound to Decrypt IP6 packet Algorithm {SHA1HMAC, AESCBC}. Check if Packet Header content is intact",
                     L"%a:%d:  Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
  
      //
      // check if the Ip6Packet data content is the same as 
      // the content after encrypt & decrypt call
      //
      for (FragmentLen1 = 0, i = 0; i < FragmentCount; i++) {
        FragmentLen1 += FragmentTable[i].FragmentLength;
      }
  
      for (FragmentLen2 = 0, i = 0; i < TestFragmentCount2; i++) {
        FragmentLen2 += TestFragmentTable2[i].FragmentLength;
      }
  
      
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (FragmentLen1 == FragmentLen2) {
        for (i = 0; i < FragmentLen1 ; i++) {
          FragmentData1 = FragmentTableGetByte(FragmentTable, FragmentCount, i);
          FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
          if (*FragmentData1 != *FragmentData2) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
          }
        }
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
  
          
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid020,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Transport Mode IPSEC InBound to Decrypt IP6 packet Algorithm {SHA1HMAC, AESCBC}. Check if Packet Payload Content is intact",
                     L"%a:%d:  Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
  
      //
      // Signal RecycleEvent to free all resouces allocated inside ProcessExt
      //
      if (RecycleEvent1 != NULL) {
        gtBS->SignalEvent(RecycleEvent1);
        RecycleEvent1 = NULL;
      }
      
      if (RecycleEvent2 != NULL) {
        gtBS->SignalEvent(RecycleEvent2);
        RecycleEvent2 = NULL;
      }
   
    }

    if (Ip6Head != NULL) {
      gtBS->FreePool (Ip6Head);
      Ip6Head = NULL;
    }
  
    if (OptionsBuffer != NULL) {
      gtBS->FreePool (OptionsBuffer);
      OptionsBuffer = NULL;
    }
  
    if (FragmentTable != NULL) {
      gtBS->FreePool (FragmentTable);
      FragmentTable = NULL;
    }
  
    if (Ip6PacketTemp != NULL) {
      gtBS->FreePool (Ip6PacketTemp);
      Ip6PacketTemp = NULL;
    }
   
  }

FUNC_EXIT:
  //
  // Free all allocated resources 
  //
  if (Ip6Head != NULL) {
    gtBS->FreePool (Ip6Head);
  }

  if (OptionsBuffer != NULL) {
    gtBS->FreePool (OptionsBuffer);
  }

  if (FragmentTable != NULL) {
    gtBS->FreePool (FragmentTable);
  }

  if (Ip6PacketTemp != NULL) {
    gtBS->FreePool (Ip6PacketTemp);
  }
   
  if (NicHandleBuffer != NULL) {
    gtBS->FreePool (NicHandleBuffer);
  }
  
  if (RecycleEvent1 != NULL) {
    gtBS->SignalEvent(RecycleEvent1);
  }  

  if (RecycleEvent2 != NULL) {
    gtBS->SignalEvent(RecycleEvent2);
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint7(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EVENT                            RecycleEvent1 = NULL;
  EFI_EVENT                            RecycleEvent2 = NULL;
  EFI_IP6_HEADER                       *Ip6Head = NULL;    
  EFI_IP6_HEADER                       *Ip6HeadInnerCpy = NULL;
  EFI_IP6_HEADER                       *Ip6HeadSrc = NULL;
  UINT8                                *OptionsBuffer = NULL;
  UINT32                               OptionLen;
  EFI_IPSEC_FRAGMENT_DATA              *FragmentTable = NULL;
  UINT32                               FragmentCount;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable1 = NULL;
  UINT32                               TestFragmentCount1;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable2 = NULL;
  UINT32                               TestFragmentCount2;
  EFI_HANDLE                           *NicHandleBuffer = NULL;
  UINTN                                NoHandles;
  UINT32                               i;
  UINT8                                *FragmentData2 = NULL;
  UINT32                               FragmentLen2;
  EFI_IP6_HEADER                       ZeroIp6Head;
  UINT8                                *Ip6PacketTemp = NULL;
  UINT32                               PacketIndex;

  //
  // Allocate a NIC handle  which has Udp6 service binding protocol installed
  // IPSEC2.ProcessExt may need Upd4/Udp6 in ike negotiation process
  // 
  gtBS->LocateHandleBuffer(
          ByProtocol, 
          &gBlackBoxEfiUdp6ServiceBindingProtocolGuid, 
          NULL, 
          &NoHandles,
          &NicHandleBuffer
          );

  for (PacketIndex = 0; IP6PacketBuffer[PacketIndex].PacketName != NULL; PacketIndex++) {
  
    //
    // Create a temp Ip6 packet buffer for test 
    // to make sure orignal test patten unchanged 
    //
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     *(IP6PacketBuffer[PacketIndex].PacketSize), 
                     (VOID **)&Ip6PacketTemp
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - Allocate IP6 packet space for testing",
                     L"%a:%d:Status - %r. Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
      goto FUNC_EXIT;
    }
    SctCopyMem (
      Ip6PacketTemp, 
      IP6PacketBuffer[PacketIndex].Packet, 
      *(IP6PacketBuffer[PacketIndex].PacketSize)
      );
  
    
    //
    // Create One IP6Packet comprise of {IP6Head, OptionsBuffer, FragmentTable}
    //
    Status = IP6ProcessPacket(
               StandardLib, 
               IP6PacketBuffer[PacketIndex].Packet, 
               *(IP6PacketBuffer[PacketIndex].PacketSize),
               &Ip6Head, 
               (VOID **) &OptionsBuffer,
               &OptionLen,
               &FragmentTable, 
               &FragmentCount
               );
  
    Ip6HeadSrc = (EFI_IP6_HEADER *)IP6PacketBuffer[PacketIndex].Packet;
  
    if (Status != EFI_SUCCESS) {
      goto FUNC_EXIT;
    }
    
    for (i = 0; i < NoHandles; i++) {
      //
      // Save Fragment Table address, Since ProcessExt will change its value 
      // 
      TestFragmentTable1 = FragmentTable;
      TestFragmentCount1 = FragmentCount;
  
      //
      // OutBound Packet to encrypt Ip6 packet
      //
      Status = IPsec2->ProcessExt (
                         IPsec2,
                         NicHandleBuffer[i],
                         IP_VERSION_6,
                         Ip6Head,
                         &(Ip6Head->NextHeader),
                         (VOID **) &OptionsBuffer,
                         &OptionLen,
                         &TestFragmentTable1,
                         &TestFragmentCount1,
                         EfiIPsecOutBound,
                         &RecycleEvent1
                         );
    
      
      if (EFI_ERROR(Status)) {
        //
        // Record test failure status & return 
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"AllocatePool - OutBound ProcessExt call to encrypt IP6 packet fails",
                       L"%a:%d:Status - %r. Packet Type : %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       IP6PacketBuffer[PacketIndex].PacketName
                       );
        goto FUNC_EXIT;
      }
      
      //
      // Check first ProcessExt Call return parameter status
      //
      if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent1 != NULL) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
  
      //
      // Check IPSec Packet Header shoud be set to Tunnel IP header  
      //
      if ( Ip6HeadSrc->TrafficClassH != Ip6Head->TrafficClassH
        || Ip6HeadSrc->Version != Ip6Head->Version
        || Ip6HeadSrc->FlowLabelH != Ip6Head->FlowLabelH
        || Ip6HeadSrc->TrafficClassL != Ip6Head->TrafficClassL
        || Ip6HeadSrc->FlowLabelL != Ip6Head->FlowLabelL
        || Ip6Head->NextHeader != IPSEC_ESP_PROTOCOL
        || Ip6HeadSrc->HopLimit != Ip6Head->HopLimit
        || SctCompareMem (&(Ip6Head->DestinationAddress), &TunnelRemoteAddressIp6, sizeof(EFI_IPv6_ADDRESS)) != 0
        || SctCompareMem (&(Ip6Head->SourceAddress), &TunnelLocalAddressIp6, sizeof(EFI_IPv6_ADDRESS)) != 0
        ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid021,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode OutBound Call to do IP6 IPSEC Tunnel Mode Encrypt Algorithm {SHA1HMAC, 3DESCBC}",
                     L"%a:%d:Status=%r. Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
  
      
      //
      // Save Fragment Table address, Since ProcessExt will change its value 
      // 
      TestFragmentTable2 = TestFragmentTable1;
      TestFragmentCount2 = TestFragmentCount1;
      
      //
      // Decrypt IpSec packet
      //
      Status = IPsec2->ProcessExt (
                         IPsec2,
                         NicHandleBuffer[i],
                         IP_VERSION_6,
                         Ip6Head,
                         &(Ip6Head->NextHeader),
                         (VOID **) &OptionsBuffer,
                         &OptionLen,
                         &TestFragmentTable2,
                         &TestFragmentCount2,
                         EfiIPsecInBound,
                         &RecycleEvent2
                         );
  
      
     if (EFI_ERROR(Status)) {
        //
        // Record test failure status & return 
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"AllocatePool - OutBound ProcessExt call to encrypt Ip6 packet fails",
                       L"%a:%d:Status - %r. Packet Type : %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       IP6PacketBuffer[PacketIndex].PacketName
                       );
        goto FUNC_EXIT;
      }
  
      
      //
      // Check if the IP6 packet is unchanged
      //
      if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent2 != NULL) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      //
      // Ip6Header should be set to reset to Zero
      //
     
      SctZeroMem (&ZeroIp6Head, sizeof (EFI_IP6_HEADER));
      if ( SctCompareMem (Ip6Head, &ZeroIp6Head, sizeof(EFI_IP6_HEADER)) != 0 ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid021,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode IPSEC Tunnel Mode InBound to Decrypt IP6 packet Algorithm {SHA1HMAC, 3DESCBC}. Check Returned Packet Header is set ZERO",
                     L"%a:%d:  Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
  
      //
      // Get a Inner IP6 Header copy 
      //
      Status =  gtBS->AllocatePool (
                        EfiBootServicesData,
                        sizeof(EFI_IP6_HEADER), 
                        (VOID **)&Ip6HeadInnerCpy
                        );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"AllocatePool - Allocate Temper IP6 Tunnel Mode Inner Header for testing",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        goto FUNC_EXIT;
      }
  
      for (i = 0; i < sizeof(EFI_IP6_HEADER); i++) {
        FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
        ((UINT8 *)Ip6HeadInnerCpy)[i] = *FragmentData2;
      }
  
      //
      // Check Inner IP6 Header after decryption
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if ( Ip6HeadSrc->TrafficClassH != Ip6HeadInnerCpy->TrafficClassH
        || Ip6HeadSrc->Version != Ip6HeadInnerCpy->Version
        || Ip6HeadSrc->FlowLabelH != Ip6HeadInnerCpy->FlowLabelH
        || Ip6HeadSrc->TrafficClassL != Ip6HeadInnerCpy->TrafficClassL
        || Ip6HeadSrc->FlowLabelL != Ip6HeadInnerCpy->FlowLabelL
        || Ip6HeadSrc->NextHeader != Ip6HeadInnerCpy->NextHeader
        || Ip6HeadSrc->HopLimit != Ip6HeadInnerCpy->HopLimit
        || SctCompareMem (&(Ip6HeadInnerCpy->DestinationAddress), &TunnelRemoteAddressIp6, sizeof(EFI_IPv6_ADDRESS)) != 0
        || SctCompareMem (&(Ip6HeadInnerCpy->SourceAddress), &(Ip6HeadSrc->SourceAddress), sizeof(EFI_IPv6_ADDRESS)) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } 
        
        
      StandardLib->RecordAssertion (
                       StandardLib,
                       AssertionType,
                       gIpSec2BBTestFunctionAssertionGuid022,
                       L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode IPSEC Tunnel Mode InBound to Decrypt IP6 packet Algorithm {SHA1HMAC, 3DESCBC}. Check IP6 Packet "     \
                       L"InnerHeader is correct",
                       L"%a:%d:  Packet Type : %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       IP6PacketBuffer[PacketIndex].PacketName
                       );
      //
      // check if the Ip6Packet data content is the same as 
      // the content after encrypt & decrypt call
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      for (FragmentLen2 = 0, i = 0; i < TestFragmentCount2; i++) {
        FragmentLen2 += TestFragmentTable2[i].FragmentLength;
      }
  
      
      if (NTOHS(Ip6HeadSrc->PayloadLength) == FragmentLen2 - sizeof(EFI_IP6_HEADER)) {   
        //
        // Need not to check TCP/UDP pesudo checksum
        //
        if (Ip6HeadInnerCpy->NextHeader == EFI_IP_PROTO_UDP) {    
          //
          // Skip UDP header checksum field check
          //
          for (i = sizeof(EFI_IP6_HEADER); i < sizeof(EFI_IP6_HEADER) + sizeof(EFI_UDP_HEAD) - 2 ; i++) {
          
            FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
  
            if (IP6PacketBuffer[PacketIndex].Packet[i] != *FragmentData2) {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
              break;
            }
          }
          i = sizeof(EFI_IP6_HEADER) + sizeof(EFI_UDP_HEAD);
        } else if (Ip6HeadInnerCpy->NextHeader == EFI_IP_PROTO_TCP) {
          //
          // Skip TCP header checksum field check
          //
          for (i = sizeof(EFI_IP6_HEADER); i < sizeof(EFI_IP6_HEADER) + sizeof(EFI_TCP_HEAD) - 4 ; i++) {
  
            FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
  
            if (IP6PacketBuffer[PacketIndex].Packet[i] != *FragmentData2) {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
              break;
            }
          }
          i = sizeof(EFI_IP6_HEADER) + sizeof(EFI_TCP_HEAD);
        } else {
          i = sizeof(EFI_IP6_HEADER);
        }
  
        //
        // Check Payload
        //
        
        for (; i < FragmentLen2 ; i++) {
          FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
          if (IP6PacketBuffer[PacketIndex].Packet[i] != *FragmentData2) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
          }
        }
  
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
  
          
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid023,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt -  IPSEC Tunnel Mode InBound to Decrypt IP6 packet Algorithm {SHA1HMAC, 3DESCBC}. Check IP6 Packet "     \
                     L"PayLoad is intact",
                     L"%a:%d:   Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
  
      //
      // Signal RecycleEvent to free all resouces allocated inside ProcessExt
      //
      if (RecycleEvent1 != NULL) {
        gtBS->SignalEvent(RecycleEvent1);
        RecycleEvent1 = NULL;
      }
      
      if (RecycleEvent2 != NULL) {
        gtBS->SignalEvent(RecycleEvent2);
        RecycleEvent2 = NULL;
      }
   
    }

    if (Ip6Head != NULL) {
      gtBS->FreePool (Ip6Head);
      Ip6Head = NULL;
    }
  
    if (OptionsBuffer != NULL) {
      gtBS->FreePool (OptionsBuffer);
      OptionsBuffer = NULL;
    }
  
    if (FragmentTable != NULL) {
      gtBS->FreePool (FragmentTable);
      FragmentTable = NULL;
    }
       
    if (Ip6PacketTemp != NULL) {
      gtBS->FreePool (Ip6PacketTemp);
      Ip6PacketTemp = NULL;
    }
  
    if (Ip6HeadInnerCpy != NULL) {
      gtBS->FreePool (Ip6HeadInnerCpy);
      Ip6HeadInnerCpy = NULL;      
    }

  }

FUNC_EXIT:
  //
  // Free all allocated resources 
  //
  if (Ip6Head != NULL) {
    gtBS->FreePool (Ip6Head);
  }

  if (OptionsBuffer != NULL) {
    gtBS->FreePool (OptionsBuffer);
  }

  if (FragmentTable != NULL) {
    gtBS->FreePool (FragmentTable);
  }
     
  if (Ip6PacketTemp != NULL) {
    gtBS->FreePool (Ip6PacketTemp);
  }

  if (Ip6HeadInnerCpy != NULL) {
    gtBS->FreePool (Ip6HeadInnerCpy);
  }
  
  if (NicHandleBuffer != NULL) {
     gtBS->FreePool (NicHandleBuffer);
   }

  if (RecycleEvent1 != NULL) {
    gtBS->SignalEvent(RecycleEvent1);
  }  

  if (RecycleEvent2 != NULL) {
    gtBS->SignalEvent(RecycleEvent2);
  }

  return EFI_SUCCESS;
}




EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTestCheckpoint8(
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  )
{
  EFI_STATUS                           Status;
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EVENT                            RecycleEvent1 = NULL;
  EFI_EVENT                            RecycleEvent2 = NULL;
  EFI_IP6_HEADER                       *Ip6Head = NULL;
  EFI_IP6_HEADER                       *Ip6HeadInnerCpy = NULL;
  EFI_IP6_HEADER                       *Ip6HeadSrc = NULL;
  UINT8                                *OptionsBuffer = NULL;
  UINT32                               OptionLen;
  EFI_IPSEC_FRAGMENT_DATA              *FragmentTable = NULL;
  UINT32                               FragmentCount;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable1 = NULL;
  UINT32                               TestFragmentCount1;
  EFI_IPSEC_FRAGMENT_DATA              *TestFragmentTable2 = NULL;
  UINT32                               TestFragmentCount2;
  EFI_HANDLE                           *NicHandleBuffer = NULL;
  UINTN                                NoHandles;
  UINT32                               i;
  UINT8                                *FragmentData2 = NULL;
  UINT32                               FragmentLen2;
  EFI_IP6_HEADER                       ZeroIp6Head;
  UINT8                                *Ip6PacketTemp = NULL;
  UINT32                               PacketIndex;

  //
  // Allocate a NIC handle  which has Udp6 service binding protocol installed
  // IPSEC2.ProcessExt may need Upd4/Udp6 in ike negotiation process
  // 
  gtBS->LocateHandleBuffer(
          ByProtocol, 
          &gBlackBoxEfiUdp6ServiceBindingProtocolGuid, 
          NULL, 
          &NoHandles,
          &NicHandleBuffer
          );

  for (PacketIndex = 0; IP6PacketBuffer[PacketIndex].PacketName != NULL; PacketIndex++) {
  
    //
    // Create a temp Ip6 packet buffer for test 
    // to make sure orignal test patten unchanged 
    //
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     *(IP6PacketBuffer[PacketIndex].PacketSize), 
                     (VOID **)&Ip6PacketTemp
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - Allocate Temp IP6 packet space for testing",
                     L"%a:%d:Status - %r. Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
      goto FUNC_EXIT;
    }
    SctCopyMem (
      Ip6PacketTemp, 
      IP6PacketBuffer[PacketIndex].Packet, 
      *(IP6PacketBuffer[PacketIndex].PacketSize)
      );
  
    
    //
    // Create One IP6 Packet comprise of {IP6Head, OptionsBuffer, FragmentTable}
    //
    Status = IP6ProcessPacket(
               StandardLib, 
               IP6PacketBuffer[PacketIndex].Packet, 
               *(IP6PacketBuffer[PacketIndex].PacketSize),
               &Ip6Head, 
               (VOID **) &OptionsBuffer,
               &OptionLen,
               &FragmentTable, 
               &FragmentCount
               );
  
    Ip6HeadSrc = (EFI_IP6_HEADER *)IP6PacketBuffer[PacketIndex].Packet;
  
    if (Status != EFI_SUCCESS) {
      goto FUNC_EXIT;
    }
    
    for (i = 0; i < NoHandles; i++) {
      //
      // Save Fragment Table address, Since ProcessExt will change its value 
      // 
      TestFragmentTable1 = FragmentTable;
      TestFragmentCount1 = FragmentCount;
  
      //
      // OutBound Packet to encrypt Ip6 packet
      //
      Status = IPsec2->ProcessExt (
                         IPsec2,
                         NicHandleBuffer[i],
                         IP_VERSION_6,
                         Ip6Head,
                         &(Ip6Head->NextHeader),
                         (VOID **) &OptionsBuffer,
                         &OptionLen,
                         &TestFragmentTable1,
                         &TestFragmentCount1,
                         EfiIPsecOutBound,
                         &RecycleEvent1
                         );
    
      
      if (EFI_ERROR(Status)) {
        //
        // Record test failure status & return 
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"AllocatePool - OutBound ProcessExt Tunnel Mode call to encrypt IP6 packet fails",
                       L"%a:%d:Status - %r. Packet Type : %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       IP6PacketBuffer[PacketIndex].PacketName
                       );
        goto FUNC_EXIT;
      }
      
      //
      // Check first ProcessExt Call return parameter status
      //
      if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent1 != NULL) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      //
      // Check IPSec Packet Header shoud be set to Tunnel IP header  
      //
      if ( Ip6HeadSrc->TrafficClassH != Ip6Head->TrafficClassH
        || Ip6HeadSrc->Version != Ip6Head->Version
        || Ip6HeadSrc->FlowLabelH != Ip6Head->FlowLabelH
        || Ip6HeadSrc->TrafficClassL != Ip6Head->TrafficClassL
        || Ip6HeadSrc->FlowLabelL != Ip6Head->FlowLabelL
        || Ip6Head->NextHeader != IPSEC_ESP_PROTOCOL
        || Ip6HeadSrc->HopLimit != Ip6Head->HopLimit
        || SctCompareMem (&(Ip6Head->DestinationAddress), &TunnelRemoteAddressIp6, sizeof(EFI_IPv6_ADDRESS)) != 0
        || SctCompareMem (&(Ip6Head->SourceAddress), &TunnelLocalAddressIp6, sizeof(EFI_IPv6_ADDRESS)) != 0
        ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid024,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode OutBound Call to do IP6 IPSEC Encrypt Algorithm {SHA1HMAC, AESCBC}",
                     L"%a:%d:Status=%r. Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
  
      
      //
      // Save Fragment Table address, Since ProcessExt will change its value 
      // 
      TestFragmentTable2 = TestFragmentTable1;
      TestFragmentCount2 = TestFragmentCount1;
      
      //
      // Decrypt IpSec packet
      //
      Status = IPsec2->ProcessExt (
                         IPsec2,
                         NicHandleBuffer[i],
                         IP_VERSION_6,
                         Ip6Head,
                         &(Ip6Head->NextHeader),
                         (VOID **) &OptionsBuffer,
                         &OptionLen,
                         &TestFragmentTable2,
                         &TestFragmentCount2,
                         EfiIPsecInBound,
                         &RecycleEvent2
                         );
  
      
     if (EFI_ERROR(Status)) {
        //
        // Record test failure status & return 
        //
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"AllocatePool - OutBound ProcessExt call to encrypt IP6 packet fails",
                       L"%a:%d:Status - %r. Packet Type : %s",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status,
                       IP6PacketBuffer[PacketIndex].PacketName
                       );
        goto FUNC_EXIT;
      }
  
      
      //
      // Check if the IP6 packet is unchanged
      //
      if (OptionsBuffer == NULL && OptionLen == 0 && RecycleEvent2 != NULL) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      //
      // Ip6Header should be set to reset to Zero
      //
     
      SctZeroMem (&ZeroIp6Head, sizeof (EFI_IP6_HEADER));
      if (SctCompareMem (Ip6Head, &ZeroIp6Head, sizeof(EFI_IP6_HEADER)) != 0 ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
      
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid025,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode IPSEC InBound to Decrypt IP6 packet Algorithm {SHA1HMAC, AESCBC}. Check Returned Packet Header is set ZERO",
                     L"%a:%d:   Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
  
      //
      // Get a Inner IP6 Header copy 
      //
      Status =  gtBS->AllocatePool (
                        EfiBootServicesData,
                        sizeof(EFI_IP6_HEADER), 
                        (VOID **)&Ip6HeadInnerCpy
                        );
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"AllocatePool - Allocate IP6 Temper Header for testing",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        goto FUNC_EXIT;
      }
      
      for (i = 0; i < sizeof(EFI_IP6_HEADER); i++) {
        FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
        ((UINT8 *)Ip6HeadInnerCpy)[i] = *FragmentData2;
      }
      
      //
      // Check Inner IP6 Header after decryption
      //
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if ( Ip6HeadSrc->TrafficClassH != Ip6HeadInnerCpy->TrafficClassH
        || Ip6HeadSrc->Version != Ip6HeadInnerCpy->Version
        || Ip6HeadSrc->FlowLabelH != Ip6HeadInnerCpy->FlowLabelH
        || Ip6HeadSrc->TrafficClassL != Ip6HeadInnerCpy->TrafficClassL
        || Ip6HeadSrc->FlowLabelL != Ip6HeadInnerCpy->FlowLabelL
        || Ip6HeadSrc->NextHeader != Ip6HeadInnerCpy->NextHeader
        || Ip6HeadSrc->HopLimit != Ip6HeadInnerCpy->HopLimit
        || SctCompareMem (&(Ip6HeadInnerCpy->DestinationAddress), &TunnelRemoteAddressIp6, sizeof(EFI_IPv6_ADDRESS)) != 0
        || SctCompareMem (&(Ip6HeadInnerCpy->SourceAddress), &(Ip6HeadSrc->SourceAddress), sizeof(EFI_IPv6_ADDRESS)) != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      } 
           
      StandardLib->RecordAssertion (
                          StandardLib,
                          AssertionType,
                          gIpSec2BBTestFunctionAssertionGuid026,
                          L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode IPSEC InBound to Decrypt IP6 packet Algorithm {SHA1HMAC, AESCBC}. Check IP6 Packet "     \
                          L"InnerHeader is correct",
                          L"%a:%d:   Packet Type : %s",
                          __FILE__,
                          (UINTN)__LINE__,
                          IP6PacketBuffer[PacketIndex].PacketName
                          );
  
      //
      // check if the Ip6Packet data content is the same as 
      // the content after encrypt & decrypt call
      //
      for (FragmentLen2 = 0, i = 0; i < TestFragmentCount2; i++) {
        FragmentLen2 += TestFragmentTable2[i].FragmentLength;
      }
  
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (NTOHS(Ip6HeadSrc->PayloadLength) == FragmentLen2 - sizeof(EFI_IP6_HEADER)) {
        //
        // Need not to check TCP/UDP pesudo checksum
        //
        if (Ip6HeadInnerCpy->NextHeader == EFI_IP_PROTO_UDP) {
          //
          // Skip UDP header checksum field check
          //
          for (i = sizeof(EFI_IP6_HEADER); i < sizeof(EFI_IP6_HEADER) + sizeof(EFI_UDP_HEAD) - 2 ; i++) {
  
            FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
  
            if (IP6PacketBuffer[PacketIndex].Packet[i] != *FragmentData2) {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
              break;
            }
          }
          i = sizeof(EFI_IP6_HEADER) + sizeof(EFI_UDP_HEAD);
        } else if (Ip6HeadInnerCpy->NextHeader == EFI_IP_PROTO_TCP) {
          //
          // Skip TCP header checksum field check
          //
          for (i = sizeof(EFI_IP6_HEADER); i < sizeof(EFI_IP6_HEADER) + sizeof(EFI_TCP_HEAD) - 4 ; i++) {
            
            FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
  
            if (IP6PacketBuffer[PacketIndex].Packet[i] != *FragmentData2) {
              AssertionType = EFI_TEST_ASSERTION_FAILED;
              break;
            }
          }
          i = sizeof(EFI_IP6_HEADER) + sizeof(EFI_TCP_HEAD);
        } else {
          i = sizeof(EFI_IP6_HEADER);
        }
  
        //
        // Check Payload
        //
        
        for (; i < FragmentLen2 ; i++) {
          FragmentData2 = FragmentTableGetByte(TestFragmentTable2, TestFragmentCount2, i);
          if (IP6PacketBuffer[PacketIndex].Packet[i] != *FragmentData2) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            break;
          }
        }
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }
  
          
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIpSec2BBTestFunctionAssertionGuid027,
                     L"EFI_IPSEC2_PROTOCOL.ProcessExt - Tunnel Mode IPSEC InBound to Decrypt IP6 packet Algorithm {SHA1HMAC, AESCBC}. Check IP6 Packet "     \
                     L"PayLoad is intact",
                     L"%a:%d:   Packet Type : %s",
                     __FILE__,
                     (UINTN)__LINE__,
                     IP6PacketBuffer[PacketIndex].PacketName
                     );
  
      //
      // Signal RecycleEvent to free all resouces allocated inside ProcessExt
      //
      if (RecycleEvent1 != NULL) {
        gtBS->SignalEvent(RecycleEvent1);
        RecycleEvent1 = NULL;
      }
      
      if (RecycleEvent2 != NULL) {
        gtBS->SignalEvent(RecycleEvent2);
        RecycleEvent2 = NULL;
      }
   
    }

    if (Ip6Head != NULL) {
      gtBS->FreePool (Ip6Head);
      Ip6Head = NULL;
    }
  
    if (OptionsBuffer != NULL) {
      gtBS->FreePool (OptionsBuffer);
      OptionsBuffer = NULL;
    }
  
    if (FragmentTable != NULL) {
      gtBS->FreePool (FragmentTable);
      FragmentTable = NULL;
    }
       
    if (Ip6PacketTemp != NULL) {
      gtBS->FreePool (Ip6PacketTemp);
      Ip6PacketTemp = NULL;
    }
  
    if (Ip6HeadInnerCpy != NULL) {
      gtBS->FreePool (Ip6HeadInnerCpy);
      Ip6HeadInnerCpy = NULL;      
    }
  }

FUNC_EXIT:
  //
  // Free all allocated resources 
  //
  if (Ip6Head != NULL) {
    gtBS->FreePool (Ip6Head);
  }

  if (OptionsBuffer != NULL) {
    gtBS->FreePool (OptionsBuffer);
  }

  if (FragmentTable != NULL) {
    gtBS->FreePool (FragmentTable);
  }
     
  if (Ip6PacketTemp != NULL) {
    gtBS->FreePool (Ip6PacketTemp);
  }

  if (Ip6HeadInnerCpy != NULL) {
    gtBS->FreePool (Ip6HeadInnerCpy);
  }
  
  if (NicHandleBuffer != NULL) {
    gtBS->FreePool (NicHandleBuffer);
  }

  if (RecycleEvent1 != NULL) {
    gtBS->SignalEvent(RecycleEvent1);
  }  

  if (RecycleEvent2 != NULL) {
    gtBS->SignalEvent(RecycleEvent2);
  }

  return EFI_SUCCESS;
}

