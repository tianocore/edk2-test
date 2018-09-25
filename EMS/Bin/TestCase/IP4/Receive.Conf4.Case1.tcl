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
CaseGuid        BECCBBFD-F31F-4350-AB5F-5DF7B69D2110
CaseName        Receive.Conf4.Case1
CaseCategory    IP4
CaseDescription {Test the Receive Conformance of IP4 - Invoke Receive() when an\
                 ICMP error packet was received.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_RECEIVE_CONFORMANCE4_CASE1_

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

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Receive - Conf - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_IpConfigData.DefaultProtocol            1
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
                "Ip4.Receive - Conf - Config Child"                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

LocalEther  0:2:3:4:5:6
RemoteEther $targetmac
LocalIp     172.16.210.162
RemoteIp    172.16.210.102

#
# Source Quench
#
CreatePayload icmppayload data 46 0x45 0x00 0x00 0x26 0x00 0x00 0x00 0x00 0x10 \
                                  0x01 0x00 0x00 0xac 0x10 0xd2 0x66 0xac 0x10 \
                                  0xd2 0xa2 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
                                  0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
                                  0x00 0x00

CreatePacket 2 -t icmp -icmp_type 3 -icmp_code 3 -icmp_orig_len 66             \
               -icmp_orig_tos 0 -icmp_orig_id 0x017b -icmp_orig_frag 0         \
               -icmp_orig_ttl 255 -icmp_orig_prot 0x11 -icmp_orig_check 0x8885 \
               -icmp_orig_src 172.16.210.162 -icmp_orig_dst 172.16.210.102     \
               -icmp_payload icmppayload
                                  
Ip4->Receive {&@R_Token, &@R_Status}

for {set i 0} {$i < 2} {incr i} {
  SendPacket 2
  Stall 1
}

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Receive - Conf - Receive a packet"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Token.Status
if {${R_Token.Status} == $EFI_ICMP_ERROR} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Ip4ReceiveConf4AssertionGuid002                       \
                "Ip4.Receive - Conf - Check R_Token"                           \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_ICMP_ERROR"

GetVar R_Context
if {$R_Context == 1} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Receive - Conf - Check Event"                             \
                "Return R_Context - $R_Context, Expected R_Context - 1"

Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Receive - Conf - Destroy Child"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

VifDown 0

DestroyPacket

#
# EndScope
#
EndScope _IP4_RECEIVE_CONFORMANCE4_CASE1_

#
# End Log
#
EndLog
