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
CaseGuid        ABED967C-7BBB-43a2-A1B3-DB30B794895D
CaseName        Receive.Func1.Case1
CaseCategory    IP4
CaseDescription {Test the Receive Function of IP4 - Invoke Receive() to receive\
                 a ip packet.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_RECEIVE_FUNCTION1_CASE1_

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

VifUp 0 172.16.210.162 255.255.255.0

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#  
UINTN                            R_Status
UINTN                            R_Handle
EFI_IP4_CONFIG_DATA              R_IpConfigData
UINTN                            R_Context
EFI_IP4_COMPLETION_TOKEN         R_Token
EFI_IP4_RECEIVE_DATA             R_RxData
EFI_IP4_HEADER                   R_IpHeader
UINTN                            R_CopyLen

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Receive - Func - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_IpConfigData.DefaultProtocol            252
SetVar R_IpConfigData.AcceptAnyProtocol          FALSE
SetVar R_IpConfigData.AcceptIcmpErrors           TRUE
SetVar R_IpConfigData.AcceptBroadcast            FALSE
SetVar R_IpConfigData.AcceptPromiscuous          FALSE
SetVar R_IpConfigData.UseDefaultAddress          FALSE
SetIpv4Address R_IpConfigData.StationAddress     "172.16.210.102"
SetIpv4Address R_IpConfigData.SubnetMask         "255.255.255.0"
SetVar R_IpConfigData.TypeOfService              0
SetVar R_IpConfigData.TimeToLive                 16
SetVar R_IpConfigData.DoNotFragment              TRUE
SetVar R_IpConfigData.RawData                    FALSE
SetVar R_IpConfigData.ReceiveTimeout             0 
SetVar R_IpConfigData.TransmitTimeout            0

#
# check point
#
Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Receive - Func - Config Child"                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1,                     \
                 &@R_Context, &@R_Token.Event, &@R_Status"
GetAck

LocalEther  0:2:3:4:5:6
RemoteEther $targetmac
LocalIp     172.16.210.161
RemoteIp    172.16.210.102

CreatePayload aaa const 18 0x0
CreatePacket 2 -t ip -ipv4_prot 252 -ipv4_tos 1 -ipv4_ttl 8 -ipv4_payload aaa

Ip4->Receive {&@R_Token, &@R_Status}

for {set i 0} {$i < 3} {incr i} {
  SendPacket 2
  Stall 1
}

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Receive - Func - Receive a packet"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Token.Status
if {${R_Token.Status} == $EFI_SUCCESS} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Receive - Func - check R_Token"                           \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Context
if {$R_Context == 1} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Receive - Func - check Event"                             \
                "Return R_Context - $R_Context, Expected R_Context - 1"

SetVar R_CopyLen [Sizeof R_RxData]
GetVar R_CopyLen

GetVar R_Token.Packet
puts ${R_Token.Packet}

BS->CopyMem {&@R_RxData, @R_Token.Packet, @R_CopyLen, &@R_Status}
GetAck

GetVar R_RxData.HeaderLength
puts   ${R_RxData.HeaderLength}

SetVar R_CopyLen [Sizeof R_IpHeader]
GetVar R_CopyLen
BS->CopyMem {&@R_IpHeader, @R_RxData.Header, @R_CopyLen, &@R_Status}
GetAck

set assert pass
GetVar R_IpHeader.Version_HeaderLength
if {${R_IpHeader.Version_HeaderLength} != 0x45} {
  set assert fail
}

GetVar R_IpHeader.TypeOfService
if {${R_IpHeader.TypeOfService} != 1} {
  set assert fail
}

GetVar R_IpHeader.TimeToLive
if {${R_IpHeader.TimeToLive} != 8} {
  set assert fail
}

GetVar R_IpHeader.Protocol
if {${R_IpHeader.Protocol} != 252} {
  set assert fail
}

set SourceAddress [GetIpv4Address R_IpHeader.SourceAddress]
if {[string compare -nocase $SourceAddress 172.16.210.161] != 0} {
  set assert fail
}

set DestinationAddress [GetIpv4Address R_IpHeader.DestinationAddress]
if {[string compare -nocase $DestinationAddress 172.16.210.102] != 0} {
  set assert fail
}
RecordAssertion $assert $Ip4ConfigureFunc1AssertionGuid002                     \
                        "Ip4.Configure - Func - Check packet field"

Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Receive - Func - Destroy Child"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

VifDown 0

DestroyPacket

#
# End scope 
#
EndScope _IP4_RECEIVE_FUNCTION1_CASE1_

#
# End Log
#
EndLog
