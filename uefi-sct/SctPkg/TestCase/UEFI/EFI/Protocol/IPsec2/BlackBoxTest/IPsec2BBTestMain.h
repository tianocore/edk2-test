/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  IPsec2BBTestMain.h

Abstract:

  Test Driver of IPsec 2 Protocol header file

--*/

#ifndef _IPSEC2_BB_TEST_MAIN
#define _IPSEC2_BB_TEST_MAIN

#include "Efi.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/IPsecConfig.h>
#include <UEFI/Protocol/IPsec2.h>
#include "Guid.h"
#include <UEFI/Protocol/Ip4.h>
#include <UEFI/Protocol/Ip6.h>
#include "Ip4Packet.h"
#include "Ip6Packet.h"
#include <UEFI/Protocol/Udp4.h>
#include <UEFI/Protocol/Udp6.h>
#include "IPsecConfigDataIp4Transport.h"
#include "IPsecConfigDataIp4Tunnel.h"
#include "IPsecConfigDataIp6Transport.h"
#include "IPsecConfigDataIp6Tunnel.h"


#define EFI_IPSEC2_PROTOCOL_TEST_REVISION    0x00010000


//
// Entry GUIDs for Func Test
//
#define EFI_IPSEC2_PROTOCOL_TEST_ENTRY_GUID0101 \
{ 0x9e6c498c, 0x330a, 0x46de, { 0x88, 0x5, 0x17, 0x3f, 0xf8, 0xf0, 0xfd, 0x33 } }

//
// Entry GUIDs for Conformance Test
//
#define EFI_IPSEC2_PROTOCOL_TEST_ENTRY_GUID0201 \
{ 0x32d729e3, 0xb51, 0x4744, { 0xba, 0x48, 0x65, 0x68, 0xed, 0x11, 0xa4, 0x5b } }

//
//
//
EFI_STATUS
EFIAPI
InitializeIPsec2BBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  );
  
EFI_STATUS
EFIAPI
UnloadIPsec2BBTest (
  IN EFI_HANDLE                   ImageHandle
  );
  
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestProcessExtConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );
  
EFI_STATUS
EFIAPI
BBTestProcessExtFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

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
  );


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
  );


UINT8  *
FragmentTableGetByte (
  IN  EFI_IPSEC_FRAGMENT_DATA    *FragmentTable,
  IN  UINT32                     FragmentCount,
  IN  UINT32                     Offset
  );


EFI_STATUS
Ip4InitIPsecConfigDataTransport(
  IN EFI_IP4_HEADER   *Ip4Head
  );


EFI_STATUS
Ip4InitIPsecConfigDataTunnel(
  IN EFI_IP4_HEADER   *Ip4Head
  ) ;


EFI_STATUS
Ip6InitIPsecConfigDataTransport(
  IN EFI_IP6_HEADER   *Ip6Head
  ) ;

EFI_STATUS
Ip6InitIPsecConfigDataTunnel(
  IN EFI_IP6_HEADER   *Ip6Head
  ) ;


//
//  UINT16 NTOHS(UINT16 x);
//
#define NTOHS(x)           \
  (UINT16) ((((UINT16)(x) & 0xff  )<<8) | (((UINT16)(x) & 0xff00)>>8) )


typedef UINT32          TCP_SEQNO;
typedef UINT16          TCP_PORTNO;


typedef struct {
  UINT16                SrcPort;
  UINT16                DstPort;
  UINT16                Length;
  UINT16                Checksum;
} EFI_UDP_HEAD;



//
// TCP header definition
//
typedef struct {
  TCP_PORTNO            SrcPort;
  TCP_PORTNO            DstPort;
  TCP_SEQNO             Seq;
  TCP_SEQNO             Ack;
  UINT8                 Res     : 4;
  UINT8                 HeadLen : 4;
  UINT8                 Flag;
  UINT16                Wnd;
  UINT16                Checksum;
  UINT16                Urg;
} EFI_TCP_HEAD;

typedef struct{
  CHAR16               *PacketName;     /* IP Packet type namse */ 
  UINT8                *Packet;         /*Whole IP packet Content */
  UINT32               *PacketSize;       
}IP_PACKET;
#endif
