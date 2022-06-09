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

  PxeBaseCodeBBTestMain.h

Abstract:

  BB test header file of PXE Base Code Protocol

--*/

#ifndef __PXE_BASE_CODE_BB_TEST_H__
#define __PXE_BASE_CODE_BB_TEST_H__

#include "SctLib.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/SimpleNetwork.h>
#include <UEFI/Protocol/PxeBaseCode.h>
#include <UEFI/Protocol/PxeBaseCodeCallBack.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#define PXE_BASE_CODE_TEST_REVISION 0x00010001

#define MAX_UDP_SIZE 65535

#define NP_Print SctPrint

extern UINTN                gCallBackInvoked;


EFI_STATUS
EFIAPI
BBTestNewStartFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestNewStopFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestNewSetIpFilterFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestNewStartConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
EFIAPI
BBTestNewStopConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Prototypes of Function Test
//

//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestStartFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
EFIAPI
BBTestStopFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.3
//
EFI_STATUS
EFIAPI
BBTestDhcpFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.4
//
EFI_STATUS
EFIAPI
BBTestDiscoverFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.5
//
EFI_STATUS
EFIAPI
BBTestMtftpFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.6
//
EFI_STATUS
EFIAPI
BBTestUdpWriteFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.7
//
EFI_STATUS
EFIAPI
BBTestUdpReadFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.8
//
EFI_STATUS
EFIAPI
BBTestSetIpFilterFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.9
//
EFI_STATUS
EFIAPI
BBTestArpFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.10
//
EFI_STATUS
EFIAPI
BBTestSetParametersFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.11
//
EFI_STATUS
EFIAPI
BBTestSetStationIpFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.12
//
EFI_STATUS
EFIAPI
BBTestSetPacketsFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes of Conformance Test
//

//
// TDS 5.1
//
EFI_STATUS
EFIAPI
BBTestStartConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2
//
EFI_STATUS
EFIAPI
BBTestStopConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3
//
EFI_STATUS
EFIAPI
BBTestDhcpConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.4
//
EFI_STATUS
EFIAPI
BBTestDiscoverConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.5
//
EFI_STATUS
EFIAPI
BBTestMtftpConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.6
//
EFI_STATUS
EFIAPI
BBTestUdpWriteConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.7
//
EFI_STATUS
EFIAPI
BBTestUdpReadConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.8
//
EFI_STATUS
EFIAPI
BBTestSetIpFilterConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
//
//
EFI_STATUS
EFIAPI
BBTestArpConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.9
//
EFI_STATUS
EFIAPI
BBTestArpConformanceManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.10
//
EFI_STATUS
EFIAPI
BBTestSetParametersConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.11
//
EFI_STATUS
EFIAPI
BBTestSetStationIpConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.12
//
EFI_STATUS
EFIAPI
BBTestSetPacketsConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes of Internal Functions
//
#define MAX_FILE_SIZE     0x2fffff//4M
#define MAX_DIRECTORY_SIZE      0x1000 //4//4K


#define LOG_CHAR16_ASCII_DFLT1(StandardLib, Buffer) \
  StandardLib->RecordMessage( \
                StandardLib,   \
                EFI_VERBOSE_LEVEL_DEFAULT, \
                Buffer \
                );

#define LOG_CHAR16_ASCII_DFLT(LoggingLib, Buffer, Len) \
  LoggingLib->DumpBuf(LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, Buffer, (UINT32)Len, EFI_DUMP_ASCII)

#define LOG_CHAR8_ASCII_DFLT(LoggingLib, Buffer, Len)\
  LogChar8String(LoggingLib, Buffer, Len)

#define LOG_BUF_HEX_DFLT(LoggingLib, Buffer, Len)  \
  LoggingLib->DumpBuf(LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, Buffer, (UINT32)Len, EFI_DUMP_HEX)

#define LOG_UINT16_HEX_DFLT(LoggingLib, Val)  \
  LoggingLib->DumpBuf(LoggingLib,EFI_VERBOSE_LEVEL_DEFAULT, (CHAR16*)&(Val),1, EFI_DUMP_HEX)

#define LOG_UINT32_HEX_DFLT(LoggingLib, Val)  \
  LoggingLib->DumpBuf(LoggingLib,EFI_VERBOSE_LEVEL_DEFAULT, (CHAR16*)&(Val),2, EFI_DUMP_HEX)

#define LOG_IP_HEX_DFLT(LoggingLib, Data) \
{\
  UINT32 TempIp; \
  TempIp = ((Data[0])<<24) + ((Data[1])<<16) + ((Data[2])<<8) + Data[3]; \
  LOG_UINT32_HEX_DFLT(LoggingLib, TempIp);\
}

#define COPY_IP_FILTER(Dest, Src)\
  SctCopyMem (Dest, Src, sizeof(EFI_PXE_BASE_CODE_IP_FILTER))


EFI_STATUS
ChangePxeState (
  EFI_PXE_BASE_CODE_PROTOCOL    *PxeInterface,
  BOOLEAN                        UsingIpv6,
  BOOLEAN                        Cur,
  BOOLEAN                        Nxt
  );

EFI_STATUS
ReInitPxeBaseCode (
  EFI_PXE_BASE_CODE_PROTOCOL    *BcInterface
);

typedef enum {
  EFI_PXE_PACKET_TYPE_MIN = 0,
  EFI_PXE_PACKET_TYPE_DHCP_DISCOVER,
  EFI_PXE_PACKET_TYPE_DHCP_ACK,
  EFI_PXE_PACKET_TYPE_PROXY_OFFER,
  EFI_PXE_PACKET_TYPE_PXE_DISCOVER,
  EFI_PXE_PACKET_TYPE_PXE_OFFER,
  EFI_PXE_PACKET_TYPE_MAX
} EFI_PXE_PACKET_TYPE;

BOOLEAN
WaitForAnyInput ();

BOOLEAN
WaitForUserCheck ();

BOOLEAN
IsBufZeroed (
  CHAR8               *Buf,
  UINTN                Len
  );

BOOLEAN
IsPxePacketValid(
  EFI_PXE_PACKET_TYPE       PacketType,
  EFI_PXE_BASE_CODE_PACKET *Packet
  );

#define IS_ICMP_ERROR_ZEROED(data)   IsBufZeroed((CHAR8 *)data, sizeof(*(data)))
#define IS_TFTP_ERROR_ZEROED(data)   IsBufZeroed((CHAR8 *)data, sizeof(*(data)))
#define IS_IP_FILTER_ZEROED(data)    IsBufZeroed((CHAR8 *)data, sizeof(*(data)))
#define IS_PXE_PACKET_ZEROED(data)   IsBufZeroed((CHAR8 *)data, sizeof(*(data)))
#define IS_IP_ADDRESS_ZEROED(data)   IsBufZeroed((CHAR8 *)data, sizeof(*(data)))

EFI_STATUS
SetIpAndMask(
  EFI_IP_ADDRESS *EfiIp,
  EFI_IP_ADDRESS *EfiMask,
  UINT32          NumIpv4,
  UINT32          NumMask
  );

EFI_STATUS
SetIpAddress (
  EFI_IP_ADDRESS *EfiIp,
  UINT32          NumIpv4
  );

BOOLEAN
IsIpMaskEqual (
  IN EFI_IP_ADDRESS *NewStationIp,
  IN EFI_IP_ADDRESS *NewSubnetMask,
  IN EFI_IP_ADDRESS *OldStationIp,
  IN EFI_IP_ADDRESS *OldSubnetMask
  );

EFI_PXE_BASE_CODE_CALLBACK_STATUS
EFIAPI
NewCallBack (
  IN EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL  *This,
  IN EFI_PXE_BASE_CODE_FUNCTION           Function,
  IN BOOLEAN                              Received,
  IN UINT32                               PacketLen,
  IN EFI_PXE_BASE_CODE_PACKET             *Packet OPTIONAL
  );

EFI_STATUS
HookReturnAbortCallBack (
  EFI_PXE_BASE_CODE_FUNCTION FuncNum,
  EFI_PXE_BASE_CODE_PROTOCOL *BcInterface
  );

EFI_STATUS
UnHookReturnAbortCallBack (
  EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface
  );

EFI_STATUS
PrintPxePacket (
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL *LoggingLib,
  CHAR16*                            Title,
  EFI_PXE_BASE_CODE_PACKET          *Packet
  );
EFI_STATUS
PrintArpTable(
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL *LoggingLib,
  IN EFI_PXE_BASE_CODE_MODE            *Mode
  );

EFI_STATUS
CopyPxePacket (
  IN EFI_PXE_BASE_CODE_PACKET *DestPacket,
  IN EFI_PXE_BASE_CODE_PACKET *SrcPacket
  );

BOOLEAN
IsPxePacketEqual(
  IN EFI_PXE_BASE_CODE_PACKET *DestPacket,
  IN EFI_PXE_BASE_CODE_PACKET *SrcPacket
  );

EFI_STATUS
LogUdpPacket (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL *LoggingLib,
  IN EFI_IP_ADDRESS                    *DestIp,
  IN EFI_PXE_BASE_CODE_UDP_PORT        *DestPort,
  IN EFI_IP_ADDRESS                    *SrcIp,
  IN EFI_PXE_BASE_CODE_UDP_PORT        *SrcPort,
  IN UINTN                              BufferSize,
  IN VOID                              *BufferPtr
  );

BOOLEAN
IsIpFilterEqual (
  EFI_PXE_BASE_CODE_IP_FILTER          *SrcIpFilter,
  EFI_PXE_BASE_CODE_IP_FILTER          *DstIpFilter
  );

EFI_STATUS
LogChar8String(
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL *LoggingLib,
  IN CHAR8*                             Buffer,
  IN UINTN                              Len
  );

//
// Entry GUIDs
//

#define PXE_START_FUNCTION_TEST_GUID \
  {0x13466760, 0xa9fe, 0x4a36, {0xad, 0x40, 0x34, 0xe6, 0xb4, 0x6c, 0xd3, 0x2d }}

#define PXE_STOP_FUNCTION_TEST_GUID \
  {0xf9c785c6, 0xa0be, 0x4828, {0x89, 0x16, 0x85, 0x2, 0xac, 0xfa, 0x39, 0xf0 }}

#define PXE_DHCP_FUNCTION_TEST_GUID \
  { 0x6ff9f282, 0x8137, 0x4fc0, {0xa5, 0x47, 0xe7, 0x4d, 0x2c, 0xe9, 0x5f, 0x34 }}

#define PXE_DISCOVER_FUNCTION_TEST_GUID \
  { 0x7a9bd3c2, 0xdd01, 0x45c2, {0x87, 0x34, 0x70, 0xbb, 0xad, 0x4e, 0x7c, 0xcb }}

#define PXE_MTFTP_FUNCTION_TEST_GUID \
  { 0x7b8b9b1, 0xe8f2, 0x48ba, {0x98, 0x35, 0xb2, 0xe, 0x81, 0x74, 0x97, 0xca }}

#define PXE_UDPWRITE_FUNCTION_TEST_GUID \
  { 0xe1d2094a, 0xdd08, 0x4aff, {0xa6, 0x9b, 0x93, 0x82, 0xc9, 0x3f, 0x80, 0x64 }}

#define PXE_UDPREAD_FUNCTION_TEST_GUID \
  { 0x6f2a51d6, 0xe3a6, 0x4e60, {0xb5, 0x84, 0xea, 0x12, 0x65, 0x6f, 0x74, 0x38 }}

#define PXE_SETIPFILTER_FUNCTION_TEST_GUID \
  { 0xe15b5072, 0xf015, 0x4b34, {0xa7, 0xde, 0x21, 0x7b, 0x59, 0xc9, 0x6e, 0xea }}

#define PXE_ARP_FUNCTION_TEST_GUID \
  { 0xd74cb602, 0x3a32, 0x4ef0, {0x85, 0x5b, 0xfd, 0x36, 0x2c, 0x2d, 0xc3, 0x79 }}

#define PXE_SETPARAMETERS_FUNCTION_TEST_GUID \
  { 0xe95e236f, 0xc361, 0x49b9, {0xa1, 0xfd, 0x66, 0xa1, 0x2e, 0x3c, 0xd0, 0x3c }}

#define PXE_SETSTATIONIP_FUNCTION_TEST_GUID \
  { 0x51cbcbb6, 0xa6ba, 0x4499, {0xb8, 0x7b, 0xfb, 0xf4, 0x42, 0x52, 0xe0, 0xbc }}

#define PXE_SETPACKETS_FUNCTION_TEST_GUID \
  { 0x12c0407, 0x5089, 0x4d04, {0xa6, 0xe9, 0xa2, 0xba, 0xcc, 0xf1, 0x6, 0x63 }}

#define PXE_START_CONFORMANCE_TEST_GUID \
  { 0x71ca8f2f, 0x19fa, 0x405f, {0x9e, 0xf0, 0x40, 0x9b, 0xdc, 0x2e, 0x63, 0x45 }}

#define PXE_STOP_CONFORMANCE_TEST_GUID \
  { 0xb3e86b7e, 0x3fa4, 0x40da, {0x95, 0xae, 0x14, 0x44, 0x39, 0x8a, 0xe0, 0xcd }}

#define PXE_DHCP_CONFORMANCE_TEST_GUID \
  { 0xee5efbe6, 0x8132, 0x4b19, {0xa6, 0x57, 0xa4, 0x51, 0x9, 0x60, 0x9b, 0x1d }}

#define PXE_DISCOVER_CONFORMANCE_TEST_GUID \
  { 0x23f1ad8f, 0x3ad2, 0x40a7, {0x8d, 0xa0, 0xa2, 0x75, 0x65, 0x16, 0xcb, 0xa9 }}

#define PXE_Mtftp_CONFORMANCE_TEST_GUID \
  { 0xce340198, 0x6c87, 0x41f5, {0xb3, 0x9d, 0x35, 0xf7, 0xdc, 0xa8, 0xe3, 0x82 }}

#define PXE_UDPWRITE_CONFORMANCE_TEST_GUID \
  { 0xd32eb6fb, 0x8e96, 0x49d5, {0x86, 0x99, 0x70, 0x7e, 0xd7, 0x4a, 0xa2, 0xb }}

#define PXE_UDPREAD_CONFORMANCE_TEST_GUID \
  { 0x7a184f40, 0x6c85, 0x4f1d, {0xaa, 0xd8, 0x51, 0x1d, 0x81, 0x12, 0x3a, 0xad }}

#define PXE_SETIPFILTER_CONFORMANCE_TEST_GUID \
  { 0xd48064c0, 0x771d, 0x4949, {0xb2, 0x48, 0x47, 0x40, 0xfb, 0xa5, 0xf2, 0x8d }}

#define PXE_ARP_CONFORMANCE_AUTO_TEST_GUID \
  { 0x4c89bac6, 0x21ea, 0x4f04, {0xa2, 0xb6, 0xef, 0x67, 0xd3, 0x4f, 0x64, 0x98 }}

#define PXE_ARP_CONFORMANCE_MANUAL_TEST_GUID \
  { 0x5f1571e0, 0xdde1, 0x4eed, {0x8a, 0x65, 0x60, 0xf0, 0x1, 0xc2, 0xb2, 0x63 }}

#define PXE_SETPARAMETERS_CONFORMANCE_TEST_GUID \
  { 0x84b3cf04, 0x2a1, 0x42f5, {0xb2, 0xc5, 0xeb, 0x17, 0x40, 0x12, 0x20, 0xe7 }}

#define PXE_SETSTATIONIP_CONFORMANCE_TEST_GUID \
  { 0x890c3df2, 0xe88d, 0x4577, {0xaa, 0x4e, 0xd6, 0x63, 0x4a, 0x5b, 0xc5, 0xb1 }}

#define PXE_SETPACKETS_CONFORMANCE_TEST_GUID \
  { 0x3e5209a9, 0xc5b0, 0x472f, {0xb3, 0x48, 0xb2, 0x99, 0x45, 0x54, 0xfe, 0x24 }}

#endif
