/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  IPsec2BBTestMain.c

Abstract:

  Test Driver of IPsec2 Protocol

--*/

#include "SctLib.h"
#include "IPsec2BBTestMain.h"


//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_IPSEC2_PROTOCOL_TEST_REVISION,
  EFI_IPSEC2_PROTOCOL_GUID,
  L"IPsec2 Protocol Test",
  L"UEFI IPsec2 Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    EFI_IPSEC2_PROTOCOL_TEST_ENTRY_GUID0101,
    L"ProcessExtFunction",
    L"Function auto test for IPsec2 Protocol ProcessExt().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestProcessExtFunctionTest
  },
  {
    EFI_IPSEC2_PROTOCOL_TEST_ENTRY_GUID0201,
    L"ProcessExtConformance",
    L"Conformance auto test for IPsec2 Protocol ProcessExt().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestProcessExtConformanceTest
  },
  
  0
};



//
// IPSEC2 test case entry point
//

EFI_STATUS
InitializeIPsec2BBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           UnloadIPsec2BBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
UnloadIPsec2BBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

/**
  Process one IPv4 packet to create Ip4header, Optionbuffer and Fragment Table

    IP4ProcessPacket process a IP4 packet to create {IP4Header, Optionbuffer, FragmentTable} out of input Buffer. 
    Caller is responsible to free {Ip4Header /OptionsBuffer / Fragment table} created inside this function. 

  @param[in]   StandardLib         Pointer to the EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  @param[in]   Ip4Packet            Pointer to a IPv4 Packet.
  @param[in]   PacketLen            IP4 Packet Total length
  @param[out] Ip4Head              Pointer to the IPv4 Header.
  @param[out] OptionsBuffer       returns IPv4 packet options buffer
  @param[out] OptionsLength      returns IPv4 packet options buffer length
  @param[out] FragmentTable     Points to Ip4 packet Fragment Data Table .
  @param[out] FragmentCount    Points to Ip4 packet Fragment count.
 
  @retval EFI_SUCCESS              IP4 packet is successfully built.
  
**/

EFI_STATUS 
IP4ProcessPacket(
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN  VOID                                 *Ip4Packet,
  IN  UINT32                               PacketLen,
  OUT EFI_IP4_HEADER                       **Ip4Head,
  OUT VOID                                 **OptionsBuffer,
  OUT UINT32                               *OptionsLength,
  OUT EFI_IPSEC_FRAGMENT_DATA              **FragmentTable,
  OUT UINT32                               *FragmentCount
  )
{
  EFI_STATUS                      Status;
  EFI_IP4_HEADER                  *HeaderSrc = NULL;
  EFI_IP4_HEADER                  *HeaderDst = NULL;
  UINT32                          OptionLen;
  UINT8                           *OptionSrc = NULL;
  UINT8                           *OptionDst = NULL;
  EFI_IPSEC_FRAGMENT_DATA         *FragTable = NULL;
  

  ASSERT(Ip4Packet!=NULL && Ip4Head != NULL && OptionsBuffer != NULL && FragmentTable != NULL);

  HeaderSrc = (EFI_IP4_HEADER *)Ip4Packet;
   
  //
  // Create a IP4 Packet Header
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData, 
                   sizeof(EFI_IP4_HEADER), 
                   (VOID **)&HeaderDst
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool - Allocate IP4 Packet Ip4Header for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto ERROR_EXIT;
  }
  //
  // Copy Ip4 Packet header to a new buffer
  //
  SctCopyMem (HeaderDst, HeaderSrc, sizeof(EFI_IP4_HEADER));

  //
  // Create OptionsBuffer, if necessary
  //
  OptionLen = (HeaderSrc->HeaderLength << 2) - IP4_MIN_HEADLEN;
  
  if (OptionLen > 0) {
    OptionSrc = (UINT8 *) (HeaderSrc + 1);

    Status = gtBS->AllocatePool (
                   EfiBootServicesData, 
                   OptionLen, 
                   (VOID **)&OptionDst
                   );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"AllocatePool - Allocate IP4 Packet Option Buffer for testing",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto ERROR_EXIT; 
    }
    
    //
    // Copy Ip4 Packet Option buffer to a new buffer
    //
    SctCopyMem (OptionDst, OptionSrc, OptionLen);
  }

  
  //
  // Create FragmentTable from IP4 Packet Payload
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData, 
                   sizeof(EFI_IPSEC_FRAGMENT_DATA) * 1, 
                   (VOID **)&FragTable
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool - Allocate IPSEC FRAGEMENT Table buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto ERROR_EXIT;
  }

  if (OptionLen > 0) {
    FragTable->FragmentBuffer = OptionSrc + OptionLen;
    FragTable->FragmentLength = PacketLen - IP4_MIN_HEADLEN - OptionLen;
  } else {
    FragTable->FragmentBuffer = (UINT8 *) (HeaderSrc + 1);
    FragTable->FragmentLength = PacketLen - IP4_MIN_HEADLEN;
  }

  //
  // Return All Informantion 
  //
  *Ip4Head = HeaderDst;

  *OptionsBuffer = OptionDst;
  *OptionsLength = OptionLen;

  *FragmentTable = FragTable;
  *FragmentCount = 1;
  
  return EFI_SUCCESS;


ERROR_EXIT:

  if (HeaderDst != NULL) {
    gtBS->FreePool (HeaderDst);
  }

  if (OptionDst != NULL) {
    gtBS->FreePool (OptionDst);
  }
  
  if (FragTable != NULL) {
    gtBS->FreePool (FragTable);
  }
  
  return Status;
}


/**
  Process one IPv6 packet to create Ip6header,  Extend Header(Optionbuffer) and Fragment Table (Payload)

    IP6ProcessPacket process a IP6 packet to create {IP6Header, Extend Header(Optionbuffer), FragmentTable} out of input Buffer. 
    Caller is responsible to free {Ip6Header /OptionsBuffer / Fragment table} created inside this function. 

  @param[in]   StandardLib         Pointer to the EFI_STANDARD_TEST_LIBRARY_PROTOCOL instance.
  @param[in]   Ip6Packet            Pointer to a IPv6 Packet.
  @param[in]   PacketLen            IP4 Packet Total length
  @param[out] Ip6Head              Pointer to the IPv4 Header.
  @param[out] ExtHdrs              returns IPv6 packet extend header (caller-supplied options).
  @param[out] ExtHdrsLen         returns IPv6 packet extend header Len (length of the option).
  @param[out] FragmentTable     Points to Ip4 packet Fragment Data Table .
  @param[out] FragmentCount    Points to Ip4 packet Fragment count.
 
  @retval EFI_SUCCESS              IP4 packet is successfully built.
  
**/

EFI_STATUS 
IP6ProcessPacket(
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib,
  IN  VOID                                 *Ip6Packet,
  IN  UINT32                               PacketLen,
  OUT EFI_IP6_HEADER                       **Ip6Head,
  OUT VOID                                 **ExtHdrs,
  OUT UINT32                               *ExtHdrsLen,
  OUT EFI_IPSEC_FRAGMENT_DATA              **FragmentTable,
  OUT UINT32                               *FragmentCount
  )
{
  EFI_STATUS                      Status;
  EFI_IP6_HEADER                  *HeaderSrc = NULL;
  EFI_IP6_HEADER                  *HeaderDst = NULL;
  EFI_IPSEC_FRAGMENT_DATA         *FragTable = NULL;
  

  ASSERT(Ip6Packet!=NULL && Ip6Head != NULL && ExtHdrs != NULL && FragmentTable != NULL);

  HeaderSrc = (EFI_IP6_HEADER *)Ip6Packet;
   
  //
  // Create a IP4 Packet Header
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData, 
                   sizeof(EFI_IP6_HEADER), 
                   (VOID **)&HeaderDst
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool - Allocate IP6 Packet Ip6Header for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto ERROR_EXIT;
  }
  //
  // Copy Ip4 Packet header to a new buffer
  //
  SctCopyMem (HeaderDst, HeaderSrc, sizeof(EFI_IP6_HEADER));

  //
  // Create ExtHdrs(OptionsBuffer), if necessary
  // Now function do not support IPv6 extension Header
  //
  switch (HeaderDst->NextHeader) {
    case IP6_HOP_BY_HOP:         /* pass through */
    case IP6_DESTINATION:        /* pass through */
    case IP6_ROUTING:            /* pass through */
    case IP6_FRAGMENT:           /* pass through */
    case IP6_AH:                 /* pass through */
    case IP6_ESP:                /* pass through */
    case IP6_NO_NEXT_HEADER:     
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"Pass IP6 Extend header error - Now do not support passing Ip6 extend header type %d",
                     L"%a:%d:",
                     HeaderDst->NextHeader,
                     __FILE__,
                     (UINTN)__LINE__
                     );
      goto ERROR_EXIT;

    default :
      //
      // No extended headers
      //
      *ExtHdrs = NULL;
      *ExtHdrsLen = 0;
      break;
      
  }

  
  //
  // Create FragmentTable from IP6 Packet Payload
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData, 
                   sizeof(EFI_IPSEC_FRAGMENT_DATA) * 1, 
                   (VOID **)&FragTable
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool - Allocate IPSEC FRAGEMENT Table buffer for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto ERROR_EXIT;
  }

  FragTable->FragmentBuffer = (UINT8 *) (HeaderSrc + 1);
  FragTable->FragmentLength = PacketLen - IP6_MIN_HEADLEN;


  //
  // Return All Informantion 
  //
  *Ip6Head = HeaderDst;

  *FragmentTable = FragTable;
  *FragmentCount = 1;
  
  return EFI_SUCCESS;


ERROR_EXIT:

  if (HeaderDst != NULL) {
    gtBS->FreePool (HeaderDst);
  }

  if (FragTable != NULL) {
    gtBS->FreePool (FragTable);
  }
  
  return Status;
}



/**
  Get the data in the Fragment Table buffer list

  @param[in]   FragmentTable      Pointer to the fragment table.
  @param[in]   FragmentCount     Pointer to the fragment count.
  @param[in]   Offset                  The offset of the byte.

  @return       Pointer to the Offset'th byte of data in the fragment table, or NULL
                if there is no such data in the fragment table.

**/

UINT8  *
FragmentTableGetByte (
  IN  EFI_IPSEC_FRAGMENT_DATA    *FragmentTable,
  IN  UINT32                     FragmentCount,
  IN  UINT32                     Offset
  )
{
  UINT32  i;
  
  for (i = 0; i < FragmentCount; i++) {
    if (Offset > FragmentTable[i].FragmentLength) {
      Offset -= FragmentTable[i].FragmentLength;
    } else {
      return (UINT8 *)FragmentTable[i].FragmentBuffer + Offset;
    }
  }

  return NULL;
}

/**
  Initialize IPSEC_CONFIG_DATA SPD/SAD.... on Iput IP Packet Header for transport mode
  
  @param[in]   IP4 Packet Header

  @return    initialization succeed

**/

EFI_STATUS
Ip4InitIPsecConfigDataTransport(
  IN EFI_IP4_HEADER   *Ip4Head
  ) 
{

  //
  // Address Configuration
  //
  LocalAddressIp4Transport.Address.v4.Addr[0] = Ip4Head->SourceAddress.Addr[0];
  LocalAddressIp4Transport.Address.v4.Addr[1] = Ip4Head->SourceAddress.Addr[1];
  LocalAddressIp4Transport.Address.v4.Addr[2] = Ip4Head->SourceAddress.Addr[2];
  LocalAddressIp4Transport.Address.v4.Addr[3] = Ip4Head->SourceAddress.Addr[3];
  LocalAddressIp4Transport.PrefixLength = 0x20;

  RemoteAddressIp4Transport.Address.v4.Addr[0] = Ip4Head->DestinationAddress.Addr[0];
  RemoteAddressIp4Transport.Address.v4.Addr[1] = Ip4Head->DestinationAddress.Addr[1];
  RemoteAddressIp4Transport.Address.v4.Addr[2] = Ip4Head->DestinationAddress.Addr[2];
  RemoteAddressIp4Transport.Address.v4.Addr[3] = Ip4Head->DestinationAddress.Addr[3];
  RemoteAddressIp4Transport.PrefixLength = 0x20;

  //
  // InBound & OutBound SPD
  //
  OutBoundSpdIp4Transport.SaId[0].DestAddress.v4.Addr[0] = Ip4Head->DestinationAddress.Addr[0];
  OutBoundSpdIp4Transport.SaId[0].DestAddress.v4.Addr[1] = Ip4Head->DestinationAddress.Addr[1];
  OutBoundSpdIp4Transport.SaId[0].DestAddress.v4.Addr[2] = Ip4Head->DestinationAddress.Addr[2];
  OutBoundSpdIp4Transport.SaId[0].DestAddress.v4.Addr[3] = Ip4Head->DestinationAddress.Addr[3];
  
  InBoundSpdIp4Transport.SaId[0].DestAddress.v4.Addr[0] = Ip4Head->SourceAddress.Addr[0];
  InBoundSpdIp4Transport.SaId[0].DestAddress.v4.Addr[1] = Ip4Head->SourceAddress.Addr[1];
  InBoundSpdIp4Transport.SaId[0].DestAddress.v4.Addr[2] = Ip4Head->SourceAddress.Addr[2];
  InBoundSpdIp4Transport.SaId[0].DestAddress.v4.Addr[3] = Ip4Head->SourceAddress.Addr[3];

  //
  // InBound & OutBound SAD
  //
  InBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_3DESCBC;
  InBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.EncKeyLength = 24;
  InBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.EncKey = InBoundEncKeyIp4Transport;
  InBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.AuthAlgoId = IKE_AALG_SHA1HMAC;
  InBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.AuthKeyLength = 20;
  InBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.AuthKey = InBoundAuthKeyIp4Transport;

  OutBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_3DESCBC;
  OutBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.EncKeyLength = 24;
  OutBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.EncKey = OutBoundEncKeyIp4Transport;
  OutBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.AuthAlgoId = IKE_AALG_SHA1HMAC;
  OutBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.AuthKeyLength = 20;
  OutBoundSadIp4Transport.AlgoInfo.EspAlgoInfo.AuthKey = OutBoundAuthKeyIp4Transport;

  //
  // InBound & OutBound SAD selector
  //
  InBoundSadSelectorIp4Transport.SaId.DestAddress.v4.Addr[0] = Ip4Head->SourceAddress.Addr[0];
  InBoundSadSelectorIp4Transport.SaId.DestAddress.v4.Addr[1] = Ip4Head->SourceAddress.Addr[1];
  InBoundSadSelectorIp4Transport.SaId.DestAddress.v4.Addr[2] = Ip4Head->SourceAddress.Addr[2];
  InBoundSadSelectorIp4Transport.SaId.DestAddress.v4.Addr[3] = Ip4Head->SourceAddress.Addr[3];
  InBoundSadSelectorIp4Transport.SaId.Proto = EfiIPsecESP;
  InBoundSadSelectorIp4Transport.SaId.Spi = 0;
  
  OutBoundSadSelectorIp4Transport.SaId.DestAddress.v4.Addr[0] = Ip4Head->DestinationAddress.Addr[0];
  OutBoundSadSelectorIp4Transport.SaId.DestAddress.v4.Addr[1] = Ip4Head->DestinationAddress.Addr[1];
  OutBoundSadSelectorIp4Transport.SaId.DestAddress.v4.Addr[2] = Ip4Head->DestinationAddress.Addr[2];
  OutBoundSadSelectorIp4Transport.SaId.DestAddress.v4.Addr[3] = Ip4Head->DestinationAddress.Addr[3];
  OutBoundSadSelectorIp4Transport.SaId.Proto = EfiIPsecESP;
  OutBoundSadSelectorIp4Transport.SaId.Spi = 0;
  
  return EFI_SUCCESS;
}

/**
  Initialize IPSEC_CONFIG_DATA SPD/SAD.... on Iput IP Packet Header for Tunnel mode
  
  @param[in]   IP4 Packet Header

  @return    initialization succeed

**/

EFI_STATUS
Ip4InitIPsecConfigDataTunnel(
  IN EFI_IP4_HEADER   *Ip4Head
  ) 
{
  //
  // Tunnel Address configuration
  // 
  TunnelLocalAddressIp4.v4.Addr[0] = 123;
  TunnelLocalAddressIp4.v4.Addr[1] = 1;
  TunnelLocalAddressIp4.v4.Addr[2] = 2;
  TunnelLocalAddressIp4.v4.Addr[3] = 3;
  
  TunnelRemoteAddressIp4.v4.Addr[0] = 123;
  TunnelRemoteAddressIp4.v4.Addr[1] = 2;
  TunnelRemoteAddressIp4.v4.Addr[2] = 3;
  TunnelRemoteAddressIp4.v4.Addr[3] = 4;

  //
  // Address Configuration
  //
  LocalAddressIp4Tunnel.Address.v4.Addr[0] = Ip4Head->SourceAddress.Addr[0];
  LocalAddressIp4Tunnel.Address.v4.Addr[1] = Ip4Head->SourceAddress.Addr[1];
  LocalAddressIp4Tunnel.Address.v4.Addr[2] = Ip4Head->SourceAddress.Addr[2];
  LocalAddressIp4Tunnel.Address.v4.Addr[3] = Ip4Head->SourceAddress.Addr[3];
  LocalAddressIp4Tunnel.PrefixLength = 0x20;

  RemoteAddressIp4Tunnel.Address.v4.Addr[0] = Ip4Head->DestinationAddress.Addr[0];
  RemoteAddressIp4Tunnel.Address.v4.Addr[1] = Ip4Head->DestinationAddress.Addr[1];
  RemoteAddressIp4Tunnel.Address.v4.Addr[2] = Ip4Head->DestinationAddress.Addr[2];
  RemoteAddressIp4Tunnel.Address.v4.Addr[3] = Ip4Head->DestinationAddress.Addr[3];
  RemoteAddressIp4Tunnel.PrefixLength = 0x20;

  //
  //  SPD
  //
  SpdIp4Tunnel.SaId[0].DestAddress.v4.Addr[0] = Ip4Head->DestinationAddress.Addr[0];
  SpdIp4Tunnel.SaId[0].DestAddress.v4.Addr[1] = Ip4Head->DestinationAddress.Addr[1];
  SpdIp4Tunnel.SaId[0].DestAddress.v4.Addr[2] = Ip4Head->DestinationAddress.Addr[2];
  SpdIp4Tunnel.SaId[0].DestAddress.v4.Addr[3] = Ip4Head->DestinationAddress.Addr[3];
  

  //
  // SAD
  //
  SadIp4Tunnel.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_3DESCBC;
  SadIp4Tunnel.AlgoInfo.EspAlgoInfo.EncKeyLength = 24;
  SadIp4Tunnel.AlgoInfo.EspAlgoInfo.EncKey = EncKeyIp4Tunnel;
  SadIp4Tunnel.AlgoInfo.EspAlgoInfo.AuthAlgoId = IKE_AALG_SHA1HMAC;
  SadIp4Tunnel.AlgoInfo.EspAlgoInfo.AuthKeyLength = 20;
  SadIp4Tunnel.AlgoInfo.EspAlgoInfo.AuthKey = AuthKeyIp4Tunnel;

  SctCopyMem (
    &SadIp4Tunnel.TunnelSourceAddress, 
    &TunnelLocalAddressIp4,
    sizeof(EFI_IP_ADDRESS)
    );
  
  SctCopyMem (
    &SadIp4Tunnel.TunnelDestinationAddress, 
    &TunnelRemoteAddressIp4 ,
    sizeof(EFI_IP_ADDRESS)
    );



  TunnelOptionIp4.DF = EfiIPsecTunnelCopyDf;
  SctCopyMem (
    &TunnelOptionIp4.LocalTunnelAddress, 
    &TunnelLocalAddressIp4,
    sizeof(EFI_IP_ADDRESS)
    );

  SctCopyMem (
    &TunnelOptionIp4.RemoteTunnelAddress, 
    &TunnelRemoteAddressIp4,
    sizeof(EFI_IP_ADDRESS)
    );
  

  //
  // SAD selector
  //
  SadSelectorIp4Tunnel.SaId.DestAddress.v4.Addr[0] = Ip4Head->DestinationAddress.Addr[0];
  SadSelectorIp4Tunnel.SaId.DestAddress.v4.Addr[1] = Ip4Head->DestinationAddress.Addr[1];
  SadSelectorIp4Tunnel.SaId.DestAddress.v4.Addr[2] = Ip4Head->DestinationAddress.Addr[2];
  SadSelectorIp4Tunnel.SaId.DestAddress.v4.Addr[3] = Ip4Head->DestinationAddress.Addr[3];
  SadSelectorIp4Tunnel.SaId.Proto = EfiIPsecESP;
  SadSelectorIp4Tunnel.SaId.Spi = 0;
  
  return EFI_SUCCESS;
}


EFI_STATUS
Ip6InitIPsecConfigDataTransport(
  IN EFI_IP6_HEADER   *Ip6Head
  ) 
{

  //
  // Address Configuration
  //
  SctCopyMem (&(LocalAddressIp6Transport.Address.v6), &(Ip6Head->SourceAddress), sizeof(EFI_IPv6_ADDRESS));
  LocalAddressIp6Transport.PrefixLength = 0x80;

  SctCopyMem (&(RemoteAddressIp6Transport.Address.v6), &(Ip6Head->DestinationAddress), sizeof(EFI_IPv6_ADDRESS));
  RemoteAddressIp6Transport.PrefixLength = 0x80;

  //
  // InBound & OutBound SPD
  //
  SctCopyMem (&(OutBoundSpdIp6Transport.SaId[0].DestAddress.v6), &(Ip6Head->DestinationAddress), sizeof(EFI_IPv6_ADDRESS));
  SctCopyMem (&(InBoundSpdIp6Transport.SaId[0].DestAddress.v6), &(Ip6Head->SourceAddress), sizeof(EFI_IPv6_ADDRESS));

  
  //
  // InBound & OutBound SAD
  //
  InBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_3DESCBC;
  InBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.EncKeyLength = 24;
  InBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.EncKey = InBoundEncKeyIp6Transport;
  InBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.AuthAlgoId = IKE_AALG_SHA1HMAC;
  InBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.AuthKeyLength = 20;
  InBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.AuthKey = InBoundAuthKeyIp6Transport;

  OutBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_3DESCBC;
  OutBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.EncKeyLength = 24;
  OutBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.EncKey = OutBoundEncKeyIp6Transport;
  OutBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.AuthAlgoId = IKE_AALG_SHA1HMAC;
  OutBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.AuthKeyLength = 20;
  OutBoundSadIp6Transport.AlgoInfo.EspAlgoInfo.AuthKey = OutBoundAuthKeyIp6Transport;

  //
  // InBound & OutBound SAD selector
  //
  SctCopyMem (&(InBoundSadSelectorIp6Transport.SaId.DestAddress.v6), &(Ip6Head->SourceAddress), sizeof(EFI_IPv6_ADDRESS));
  InBoundSadSelectorIp6Transport.SaId.Proto = EfiIPsecESP;
  InBoundSadSelectorIp6Transport.SaId.Spi = 0;

  
  SctCopyMem (&(OutBoundSadSelectorIp6Transport.SaId.DestAddress.v6), &(Ip6Head->DestinationAddress), sizeof(EFI_IPv6_ADDRESS));
  OutBoundSadSelectorIp6Transport.SaId.Proto = EfiIPsecESP;
  OutBoundSadSelectorIp6Transport.SaId.Spi = 0;
  
  return EFI_SUCCESS;
}

/**
  Initialize IPSEC_CONFIG_DATA SPD/SAD.... on Iput IP Packet Header for Tunnel mode
  
  @param[in]   IP6 Packet Header

  @return    initialization succeed

**/

EFI_STATUS
Ip6InitIPsecConfigDataTunnel(
  IN EFI_IP6_HEADER   *Ip6Head
  ) 
{
  //
  // Tunnel Address configuration
  // 
  TunnelLocalAddressIp6.v6.Addr[0]  = 123;
  TunnelLocalAddressIp6.v6.Addr[9]  = 1;
  TunnelLocalAddressIp6.v6.Addr[10] = 2;
  TunnelLocalAddressIp6.v6.Addr[11] = 3;
  TunnelLocalAddressIp6.v6.Addr[12] = 4;
  TunnelLocalAddressIp6.v6.Addr[13] = 5;
  TunnelLocalAddressIp6.v6.Addr[14] = 6;
  TunnelLocalAddressIp6.v6.Addr[15] = 7;

  TunnelLocalAddressIp6.v6.Addr[0]  = 123;
  TunnelLocalAddressIp6.v6.Addr[9]  = 2;
  TunnelLocalAddressIp6.v6.Addr[10] = 3;
  TunnelLocalAddressIp6.v6.Addr[11] = 4;
  TunnelLocalAddressIp6.v6.Addr[12] = 5;
  TunnelLocalAddressIp6.v6.Addr[13] = 6;
  TunnelLocalAddressIp6.v6.Addr[14] = 7;
  TunnelLocalAddressIp6.v6.Addr[15] = 8;


  //
  // Address Configuration
  //
  SctCopyMem (&(LocalAddressIp6Tunnel.Address.v6), &(Ip6Head->SourceAddress), sizeof(EFI_IPv6_ADDRESS));
  LocalAddressIp6Tunnel.PrefixLength = 0x80;

  SctCopyMem (&(RemoteAddressIp6Tunnel.Address.v6),&(Ip6Head->DestinationAddress), sizeof(EFI_IPv6_ADDRESS));
  RemoteAddressIp6Tunnel.PrefixLength = 0x80;

  //
  //  SPD
  //
  SctCopyMem (&(SpdIp6Tunnel.SaId[0].DestAddress.v6), &(Ip6Head->DestinationAddress), sizeof(EFI_IPv6_ADDRESS));
  

  //
  // SAD
  //
  SadIp6Tunnel.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_3DESCBC;
  SadIp6Tunnel.AlgoInfo.EspAlgoInfo.EncKeyLength = 24;
  SadIp6Tunnel.AlgoInfo.EspAlgoInfo.EncKey = EncKeyIp6Tunnel;
  SadIp6Tunnel.AlgoInfo.EspAlgoInfo.AuthAlgoId = IKE_AALG_SHA1HMAC;
  SadIp6Tunnel.AlgoInfo.EspAlgoInfo.AuthKeyLength = 20;
  SadIp6Tunnel.AlgoInfo.EspAlgoInfo.AuthKey = AuthKeyIp6Tunnel;

  SctCopyMem (
    &SadIp6Tunnel.TunnelSourceAddress, 
    &TunnelLocalAddressIp6,
    sizeof(EFI_IP_ADDRESS)
    );
  
  SctCopyMem (
    &SadIp6Tunnel.TunnelDestinationAddress, 
    &TunnelRemoteAddressIp6 ,
    sizeof(EFI_IP_ADDRESS)
    );



  TunnelOptionIp6.DF = EfiIPsecTunnelCopyDf;
  SctCopyMem (
    &TunnelOptionIp6.LocalTunnelAddress, 
    &TunnelLocalAddressIp6,
    sizeof(EFI_IP_ADDRESS)
    );

  SctCopyMem (
    &TunnelOptionIp6.RemoteTunnelAddress, 
    &TunnelRemoteAddressIp6,
    sizeof(EFI_IP_ADDRESS)
    );
  

  //
  // SAD selector
  //
  SctCopyMem (&(SadSelectorIp6Tunnel.SaId.DestAddress.v6), &(Ip6Head->DestinationAddress), sizeof(EFI_IPv6_ADDRESS));
  SadSelectorIp6Tunnel.SaId.Proto = EfiIPsecESP;
  SadSelectorIp6Tunnel.SaId.Spi = 0;
  
  return EFI_SUCCESS;
}

