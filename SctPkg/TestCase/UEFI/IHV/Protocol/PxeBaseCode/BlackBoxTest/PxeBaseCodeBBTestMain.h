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

  PxeBaseCodeBBTestMain.h

Abstract:

  BB test header file of PXE Base Code Protocol

--*/

#ifndef __PXE_BASE_CODE_BB_TEST_H__
#define __PXE_BASE_CODE_BB_TEST_H__

#include "Efi.h"
#include "guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/SimpleNetwork.h>
#include <UEFI/Protocol/PxeBaseCode.h>
#include <UEFI/Protocol/PxeBaseCodeCallBack.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#define PXE_BASE_CODE_TEST_REVISION 0x00010001

#define IHV_PXE_BASE_CODE_PROTOCOL_GUID \
  { 0xf4a968b4, 0x7828, 0x4934, { 0xac, 0x58, 0x66, 0x53, 0xa8, 0x6e, 0xf9, 0x5a } }

#define MAX_UDP_SIZE 65535

#define NP_Print SctPrint

extern UINTN                gCallBackInvoked;


EFI_STATUS
BBTestNewStartFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestNewStopFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestNewSetIpFilterFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestNewStartConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
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
  { 0xe66a8373, 0x3a02, 0x4491, { 0xbc, 0xba, 0xe3, 0x5d, 0xaa, 0xf0, 0x4b, 0x90 } }

#define PXE_STOP_FUNCTION_TEST_GUID \
  { 0xe166e032, 0x74cc, 0x4717, { 0x84, 0x6c, 0xc0, 0x6d, 0x63, 0xaa, 0xe, 0xa2 } }

#define PXE_DHCP_FUNCTION_TEST_GUID \
  { 0xbd06e305, 0x85b9, 0x4b08, { 0xaa, 0x1f, 0x20, 0x1, 0xc, 0x78, 0x39, 0x51 } }

#define PXE_DISCOVER_FUNCTION_TEST_GUID \
  { 0xb7bf6762, 0xb004, 0x4d8b, { 0x81, 0xe6, 0x51, 0xcb, 0xd8, 0xa0, 0xc5, 0xff } }

#define PXE_MTFTP_FUNCTION_TEST_GUID \
  { 0x2aea040d, 0x8d04, 0x4cb3, { 0xa1, 0x8d, 0xa9, 0xd8, 0xf3, 0x52, 0x90, 0xce } }

#define PXE_UDPWRITE_FUNCTION_TEST_GUID \
  { 0xbc6eeb18, 0x924d, 0x4f6c, { 0x82, 0xad, 0x96, 0x47, 0x8b, 0x48, 0x61, 0x6e } }

#define PXE_UDPREAD_FUNCTION_TEST_GUID \
  { 0x29635db4, 0xf0a9, 0x428f, { 0x84, 0xd8, 0x47, 0x7c, 0x53, 0x7e, 0xf, 0x35 } }

#define PXE_SETIPFILTER_FUNCTION_TEST_GUID \
  { 0xec901421, 0x9c50, 0x4bce, { 0x9e, 0x2, 0xe0, 0xfc, 0x50, 0x9d, 0x88, 0xa5 } }

#define PXE_ARP_FUNCTION_TEST_GUID \
  { 0x832d3dcd, 0x6022, 0x4db2, { 0xaa, 0x1b, 0x99, 0xda, 0x4a, 0xbb, 0x39, 0x68 } }

#define PXE_SETPARAMETERS_FUNCTION_TEST_GUID \
  { 0xbf6fc874, 0x31c, 0x4f47, { 0xb0, 0xa8, 0x3f, 0xd6, 0xf1, 0x32, 0x8f, 0xc1 } }

#define PXE_SETSTATIONIP_FUNCTION_TEST_GUID \
  { 0x4d369c1, 0xc65f, 0x4a77, { 0xb1, 0xa7, 0xf3, 0x8f, 0x89, 0x1f, 0xdc, 0xa6 } }

#define PXE_SETPACKETS_FUNCTION_TEST_GUID \
  { 0x2edb5697, 0x7c35, 0x428e, { 0x91, 0x26, 0x2d, 0x78, 0x82, 0xe9, 0x95, 0xf2 } }

#define PXE_START_CONFORMANCE_TEST_GUID \
  { 0x7fd12a3c, 0xb617, 0x44ed, { 0xad, 0x12, 0xf3, 0xc2, 0xb9, 0xca, 0xac, 0x97 } }

#define PXE_STOP_CONFORMANCE_TEST_GUID \
  { 0x4113eb21, 0x49c1, 0x414f, { 0xb1, 0x3e, 0xe0, 0xed, 0x90, 0xfb, 0x30, 0xbd } }

#define PXE_DHCP_CONFORMANCE_TEST_GUID \
  { 0xe9829c77, 0xefa4, 0x4b53, { 0x8a, 0x28, 0x3f, 0x25, 0x80, 0xca, 0x39, 0x57 } }

#define PXE_DISCOVER_CONFORMANCE_TEST_GUID \
  { 0x27fee6e8, 0x9628, 0x4561, { 0x8a, 0x8b, 0x12, 0x59, 0x80, 0x4f, 0x6e, 0x21 } }

#define PXE_Mtftp_CONFORMANCE_TEST_GUID \
  { 0x92ab2ae5, 0xc610, 0x41d1, { 0x9d, 0xb0, 0x44, 0x91, 0xa3, 0x61, 0x1f, 0x47 } }

#define PXE_UDPWRITE_CONFORMANCE_TEST_GUID \
  { 0xd6d4696c, 0xdb4f, 0x4326, { 0x80, 0x36, 0x35, 0x5a, 0x95, 0x38, 0x4e, 0x5c } }

#define PXE_UDPREAD_CONFORMANCE_TEST_GUID \
  { 0x58193198, 0x2085, 0x4127, { 0x8a, 0xf4, 0x80, 0x43, 0xd5, 0x43, 0xdb, 0xa9 } }

#define PXE_SETIPFILTER_CONFORMANCE_TEST_GUID \
  { 0xf04c65f2, 0x92bf, 0x4975, { 0x8d, 0x48, 0xf6, 0x11, 0xc0, 0xda, 0xc6, 0xbd } }

#define PXE_ARP_CONFORMANCE_AUTO_TEST_GUID \
  { 0xf98c8452, 0x7b9e, 0x4db0, { 0xad, 0xc6, 0x91, 0xfb, 0xe4, 0x5f, 0x3b, 0x20 } }

#define PXE_ARP_CONFORMANCE_MANUAL_TEST_GUID \
  { 0x24be1c0, 0x5083, 0x4b96, { 0xa4, 0xa8, 0x53, 0xaf, 0xa5, 0xe, 0xea, 0x61 } }

#define PXE_SETPARAMETERS_CONFORMANCE_TEST_GUID \
  { 0x54f792d5, 0x16a3, 0x4ca2, { 0xb2, 0x54, 0x6e, 0x9a, 0x40, 0xbf, 0x8d, 0x74 } }

#define PXE_SETSTATIONIP_CONFORMANCE_TEST_GUID \
  { 0x6a42940c, 0xbd17, 0x4ba7, { 0x81, 0x43, 0xa3, 0x57, 0xe1, 0xdb, 0x9a, 0x3a } }

#define PXE_SETPACKETS_CONFORMANCE_TEST_GUID \
  { 0x1102c3a0, 0x1feb, 0x4024, { 0x90, 0xa9, 0xd0, 0xd8, 0x2, 0xea, 0xa9, 0x8b } }

#endif
