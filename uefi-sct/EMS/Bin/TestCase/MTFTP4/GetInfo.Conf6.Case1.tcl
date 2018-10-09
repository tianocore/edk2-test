# 
#  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
# 
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
# 
################################################################################
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid          B7E6DFBE-9BCB-484c-AD70-467D70B7E4C0
CaseName          GetInfo.Conf6.Case1
CaseCategory      MTFTP4
CaseDescription   {This case is to test the EFI_ICMP_ERROR conformance of      \
                   Mtftp4.GetInfo when an ICMP ERROR packet was received and in\
                   the buffer.}
################################################################################

proc CleanUpEutEnvironment {} {
  DelEntryInArpCache
  
  Mtftp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
  GetAck

  EndCapture
  EndScope _MTFTP4_GETINFO_CONFORMANCE6_CASE1_
  EndLog
}

#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl

BeginScope _MTFTP4_GETINFO_CONFORMANCE6_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_MTFTP4_CONFIG_DATA           R_MtftpConfigData
EFI_MTFTP4_OVERRIDE_DATA         R_OverrideData
UINT8                            R_Filename
UINT8                            R_OptionCount
EFI_MTFTP4_OPTION                R_OptionList(8)
UINT32                           R_PacketLength
POINTER                          R_Packet

#
# Initialization on ENTS side.
#
LocalEther  $DEF_OS_MAC_ADDR
RemoteEther $DEF_EUT_MAC_ADDR
LocalIp     $DEF_OS_IP_ADDR
RemoteIp    $DEF_EUT_IP_ADDR

#
# Add an entry in ARP cache.
#
AddEntryInArpCache

#
# Mtftp4
#
Mtftp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_MtftpConfigData.UseDefaultSetting   FALSE
SetIpv4Address R_MtftpConfigData.StationIp   "192.168.88.88"
SetIpv4Address R_MtftpConfigData.SubnetMask  "255.255.255.0"
SetVar R_MtftpConfigData.LocalPort           2048
SetIpv4Address R_MtftpConfigData.GatewayIp   "0.0.0.0"
SetIpv4Address R_MtftpConfigData.ServerIp    "192.168.88.1"
SetVar R_MtftpConfigData.InitialServerPort   69
SetVar R_MtftpConfigData.TryCount            10
SetVar R_MtftpConfigData.TimeoutValue        2

Mtftp4->Configure {&@R_MtftpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4.Configure - Normal operation."                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point
# - OverrideData is set to NULL
# - ModeStr is set to NULL
#
SetVar R_OptionCount                         0

set L_Filter "udp and src host 192.168.88.88"
StartCapture CCB $L_Filter

Mtftp4->GetInfo {NULL, &@R_Filename, NULL, @R_OptionCount, &@R_OptionList,     \
                 &@R_PacketLength, &@R_Packet, &@R_Status}

ReceiveCcbPacket CCB TempPacket1 20
if { ${CCB.received} == 0} {
#
# If have not captured the packet. Fail
#
  GetAck
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp4.GetInfo - GetInfo() invocation with valid parameters \
                   should send a packet to MTFTP4 server, but not."

  CleanUpEutEnvironment
  return
}

#
# If have captured the packet. Sends out an ICMP error packet.
#
# Destination Unreachable - Fragmentation needed
ParsePacket TempPacket1 -t eth -eth_payload eth_payload
SplitPayload ip_head eth_payload 0 19
ParsePacket TempPacket1 -t ip -ipv4_payload ip_payload
SplitPayload udp_head ip_payload 0 7
ConcatPayload icmp_payload ip_head udp_head
CreatePacket icmp_error -t icmp -icmp_type 3 -icmp_code 4 -icmp_orig_len 66    \
             -icmp_orig_tos 0 -icmp_orig_id 0x017b -icmp_orig_frag 0           \
             -icmp_orig_ttl 255 -icmp_orig_prot 0x11 -icmp_orig_check 0x0      \
             -icmp_orig_src 192.168.88.88 -icmp_orig_dst 192.168.88.1          \
             -icmp_payload icmp_payload
SendPacket icmp_error
GetAck

set assert [VerifyReturnStatus R_Status $EFI_ICMP_ERROR]
RecordAssertion $assert $Mtftp4GetInfoConfAssertionGuid011                     \
                "Mtftp4.GetInfo - Server responses with ICMP error packet,     \
                 client should terminate the session."                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ICMP_ERROR"

CleanUpEutEnvironment