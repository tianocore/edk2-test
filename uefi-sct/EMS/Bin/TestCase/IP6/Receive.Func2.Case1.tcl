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
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        3165381D-57EC-4372-9EFD-5827C4EFD02A
CaseName        Receive.Func2.Case1
CaseCategory    IP6
CaseDescription {Test the Receive Function of IP6 - Invoke Receive() \
                 to receive data in fragment.}
################################################################################

Include IP6/include/Ip6.inc.tcl

proc CleanUpEutEnvironment {} {
  Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  BS->CloseEvent "@R_Token.Event, &@R_Status"
  GetAck

  DestroyPacket
  EndCapture
  
  EndScope _IP6_RECEIVE_FUNCTION2_CASE1_
  
  EndLog
}

#
# Begin Log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope   _IP6_RECEIVE_FUNCTION2_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Create child.
#
Ip6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Ip6SB.CreateChild - Create Child 1"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar [subst $ENTS_CUR_CHILD]          @R_Handle

#
# Address Configuration
#
UINTN                                       R_Ip6ConfigDataSize
UINT32                                      R_Ip6ConfigDataType
UINT32                                      R_Ip6ConfigPolicy
EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS    R_Ip6ConfigDadTransmits
EFI_IP6_CONFIG_MANUAL_ADDRESS               R_Ip6ConfigManualAddress

SetVar R_Ip6ConfigDataType   2
SetVar R_Ip6ConfigDataSize   4
SetVar R_Ip6ConfigPolicy     $IP6CP(Manual)
  
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigPolicy,&@R_Status"
GetAck

SetVar R_Ip6ConfigDataType   3
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS]
SetVar R_Ip6ConfigDadTransmits.DupAddrDetectTransmits 0
  
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigDadTransmits,&@R_Status"
GetAck
  
SetVar R_Ip6ConfigDataType   4
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_MANUAL_ADDRESS]
SetVar R_Ip6ConfigManualAddress.IsAnycast    FALSE
SetVar R_Ip6ConfigManualAddress.PrefixLength 64
SetIpv6Address R_Ip6ConfigManualAddress.Address $DEF_EUT_IP_ADDR
puts $DEF_EUT_IP_ADDR
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigManualAddress,&@R_Status"
GetAck

EFI_IP6_CONFIG_DATA                           R_Ip6ConfigData
SetVar R_Ip6ConfigData.DefaultProtocol        0x11;        #Next Header: UDP
SetVar R_Ip6ConfigData.AcceptAnyProtocol      FALSE
SetVar R_Ip6ConfigData.AcceptIcmpErrors       TRUE
SetVar R_Ip6ConfigData.AcceptPromiscuous      FALSE
SetIpv6Address R_Ip6ConfigData.DestinationAddress     "::"
SetIpv6Address R_Ip6ConfigData.StationAddress         $DEF_EUT_IP_ADDR
SetVar R_Ip6ConfigData.TrafficClass           0
SetVar R_Ip6ConfigData.HopLimit               64
SetVar R_Ip6ConfigData.FlowLabel              0
SetVar R_Ip6ConfigData.ReceiveTimeout         50000
SetVar R_Ip6ConfigData.TransmitTimeout        50000

#
# Configure this child with valid parameter.
#
Ip6->Configure "&@R_Ip6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Ip6.Configure - Func - Configure child with valid parameter"     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Add a Neighbor cache
# Call Neighbors with 
#                         DeleteFlag = FALSE
#                         TargetIp6Address = 
#                         TargetLinkAddress = 
#                         Timeout = 0
#                         Override = TRUE
#              EFI_SUCCESS should be returned.
#
EFI_IPv6_ADDRESS                              R_TargetIp6Address
SetIpv6Address R_TargetIp6Address             $DEF_ENTS_IP_ADDR
EFI_MAC_ADDRESS                               R_TargetLinkAddress             
SetEthMacAddress R_TargetLinkAddress          $DEF_ENTS_MAC_ADDR
UINT32                                        R_Timeout
SetVar R_Timeout                              0

Ip6->Neighbors "FALSE, &@R_TargetIp6Address, &@R_TargetLinkAddress, @R_Timeout, TRUE, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Ip6.Neighbors - Func - Add a neighbor entry"               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point
#
EFI_IP6_COMPLETION_TOKEN                       R_Token
UINTN                                          R_Context
SetVar R_Context                               0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

EFI_IP6_RECEIVE_DATA                           R_RxData
EFI_IP6_RECEIVE_DATA                           R_RxData1
SetVar R_Token.Packet                          &@R_RxData1

#
# Create a IPv6 packet
#
#set hostmac    [GetHostMac]
#set targetmac  [GetTargetMac]
#RemoteEther    $targetmac
#LocalEther     $hostmac
#set LocalIP    "2002::2"
#LocalIPv6      $LocalIP
#RemoteIPv6     $RemoteIP
RemoteEther    $DEF_EUT_MAC_ADDR
LocalEther     $DEF_ENTS_MAC_ADDR
LocalIPv6      $DEF_ENTS_IP_ADDR
RemoteIPv6     $DEF_EUT_IP_ADDR


#8 bytes fragment header, 1448bytes data
set PayloadDataLength 1456
#set FragmentHeader "0x11 0x00 0x00 0x01 0x1e 0xce 0xfd 0xc5"

CreatePayload IPv6Payload Data $PayloadDataLength 0x11 0x00 0x00 0x01 0x1e 0xce 0xfd 0xc5 0XAA

CreatePacket Ipv6Packet -t IPv6 -IPv6_ver 0x06 -IPv6_tc 0x00 -IPv6_fl 0x00 \
                                     -IPv6_pl $PayloadDataLength -IPv6_nh 0x2c -IPv6_hl 128 \
                                     -IPv6_payload IPv6Payload
#8 byts fragment header, 552
set PayloadDataLength2 560
CreatePayload IPv6Payload2 Data $PayloadDataLength2 0x11 0x00 0x05 0xa8 0x1e 0xce 0xfd 0xc5 0XBB
CreatePacket Ipv6Packet2 -t IPv6 -IPv6_ver 0x06 -IPv6_tc 0x00 -IPv6_fl 0x00 \
                                     -IPv6_pl $PayloadDataLength2 -IPv6_nh 0x2c -IPv6_hl 128 \
                                     -IPv6_payload IPv6Payload2

#
# Check point: Call Receive() to receive a packet by fragment
#
Ip6->Receive "&@R_Token, &@R_Status"
SendPacket Ipv6Packet
SendPacket Ipv6Packet2
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6ReceiveFunc2AssertionGuid001        \
                "Ip6.Receive - Func - Call Receive "                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Token->Event should be signaled
#
GetVar R_Context
set assert fail
if { ${R_Context} ==1} {
  set assert pass
}
RecordAssertion $assert $Ip6ReceiveFunc2AssertionGuid002        \
                "Ip6.Receive - Func - Verify Token->Event whether signaled"
#
# Check point: Token->Status should be EFI_SUCCESS
#
GetVar R_Token
set assert fail
if { ${R_Token.Status} == $EFI_SUCCESS} {
  set assert pass
}
RecordAssertion $assert $Ip6ReceiveFunc2AssertionGuid003        \
                "Ip6.Receive - Func - Verify R_Token.Status "               \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Verify the packet received
#
UINTN            R_CopyLen
SetVar R_CopyLen [Sizeof R_RxData]
GetVar R_CopyLen
BS->CopyMem "&@R_RxData, @R_Token.Packet, @R_CopyLen, &@R_Status"
GetAck
GetVar R_RxData
puts "Header length: ${R_RxData.HeaderLength}"
# Check point: Ipv6 header length should be 40
if {${R_RxData.HeaderLength}==40} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Ip6ReceiveFunc2AssertionGuid004   \
                "Ip6.Receive - Validate RxData: HeaderLength."

# Check point: Check Data length
if {${R_RxData.DataLength}==2000} {
  set assert pass
} else {
  set assert fail
  puts "Rx Data length: ${R_RxData.DataLength}"
}
RecordAssertion $assert $Ip6ReceiveFunc2AssertionGuid005   \
                "Ip6.Receive - Validate RxData: DataLength."

# Check point: Check FragmentCount
if {${R_RxData.FragmentCount}==2} {
  set assert pass
} else {
  set assert fail
}
puts ${R_RxData.FragmentCount}
RecordAssertion $assert $Ip6ReceiveFunc2AssertionGuid006   \
                "Ip6.Receive - Validate RxData: FragmentCount."

EFI_IP6_HEADER R_Header
SetVar R_CopyLen [Sizeof R_Header]
GetVar R_CopyLen
BS->CopyMem "&@R_Header, @R_RxData.Header, @R_CopyLen, &@R_Status"
GetAck
GetVar R_Header

#
# Check point: Validate the header of the packet
#
set assert pass
if {${R_Header.Version_TrafficClass_FlowLabel} != 0x60} {
  set assert fail
}
if {[Ntohs ${R_Header.PayloadLength}] != $PayloadDataLength} {
  set assert fail
}
if {${R_Header.NextHeader} != 0x11} {
  set assert fail
}
if {${R_Header.HopLimit} != 128} {
  set assert fail
}
set SourceAddressString [GetIpv6Address R_Header.SourceAddress]
set SourceAddressString2 $DEF_ENTS_IP_ADDR
if {[string compare -nocase $SourceAddressString $SourceAddressString2] != 0} {
  set assert fail
}

set DestinationAddressString [GetIpv6Address R_Header.DestinationAddress]
set DestinationAddressString2 $DEF_EUT_IP_ADDR
if {[string compare -nocase $SourceAddressString $SourceAddressString2] != 0} {
  set assert fail
}

RecordAssertion $assert $Ip6ReceiveFunc2AssertionGuid007   \
                "Ip6.Receive - Validate RxData: IPv6 Header."

CleanUpEutEnvironment