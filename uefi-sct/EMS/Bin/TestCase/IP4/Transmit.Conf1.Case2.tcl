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
CaseGuid        A495E6CA-90A5-48c5-8589-87C4E39140D3
CaseName        Transmit.Conf1.Case2
CaseCategory    IP4
CaseDescription {Test the conformance - EFI_INVALID_PARAMEER of IP4.Transmit}
################################################################################

Include IP4/include/Ip4.inc.tcl

proc CleanUpEutEnvironment {} {
  Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
  GetAck

  BS->CloseEvent "@R_Token.Event, &@R_Status"
  GetAck

  EndCapture
  
  VifDown 0
  
  EndScope _IP4_TRANSMIT_CONFORMANCE1_CASE2_
  
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_TRANSMIT_CONFORMANCE1_CASE2_

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
EFI_IP4_TRANSMIT_DATA            R_TxData
EFI_IP4_FRAGMENT_DATA            R_FragmentTable
CHAR8                            R_FragmentBuffer(1600)
EFI_IP4_OVERRIDE_DATA            R_OverrideData

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Transmit - Conf - Create Child"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_IpConfigData.DefaultProtocol            0
SetVar R_IpConfigData.AcceptAnyProtocol          TRUE
SetVar R_IpConfigData.AcceptIcmpErrors           TRUE
SetVar R_IpConfigData.AcceptBroadcast            TRUE
SetVar R_IpConfigData.AcceptPromiscuous          TRUE
SetVar R_IpConfigData.UseDefaultAddress          FALSE
SetIpv4Address R_IpConfigData.StationAddress     "172.16.210.102"
SetIpv4Address R_IpConfigData.SubnetMask         "255.255.255.0"
SetVar R_IpConfigData.TypeOfService              0
SetVar R_IpConfigData.TimeToLive                 16
SetVar R_IpConfigData.DoNotFragment              TRUE
SetVar R_IpConfigData.RawData                    FALSE
SetVar R_IpConfigData.ReceiveTimeout             0
SetVar R_IpConfigData.TransmitTimeout            0

Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Conf - Config Child"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetFilter "ip and host 172.16.210.102"

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context, \
                 &@R_Token.Event, &@R_Status"
GetAck

SetIpv4Address R_TxData.DestinationAddress   "172.16.210.162"
SetVar R_TxData.TotalDataLength              20
SetVar R_TxData.FragmentCount                1

SetIpv4Address R_OverrideData.SourceAddress  "172.16.210.101"
SetIpv4Address R_OverrideData.GatewayAddress "172.16.210.255"
SetVar R_OverrideData.Protocol               1
SetVar R_OverrideData.TypeOfService          1
SetVar R_OverrideData.TimeToLive             8
SetVar R_OverrideData.DoNotFragment          FALSE
SetVar R_TxData.OverrideData                 &@R_OverrideData

SetVar R_FragmentBuffer                      "IpConfigureTest"
SetVar R_FragmentTable.FragmentLength        20
SetVar R_FragmentTable.FragmentBuffer        &@R_FragmentBuffer
SetVar R_TxData.FragmentTable                @R_FragmentTable
SetVar R_Token.Packet                        &@R_TxData

#
# check point
#
Ip4->Transmit {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4TransmitConf1AssertionGuid010                      \
                "Ip4.Transmit - Conf - with GatewayAddress invalid"            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

SetIpv4Address R_OverrideData.SourceAddress  "172.16.210.101"
SetIpv4Address R_OverrideData.GatewayAddress "171.16.210.254"

#
# check point
#
Ip4->Transmit {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4TransmitConf1AssertionGuid011                      \
                "Ip4.Transmit - Conf - with GatewayAddress invalid"            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

SetIpv4Address R_OverrideData.SourceAddress  "172.16.210.101"
SetIpv4Address R_OverrideData.GatewayAddress "240.0.0.2"

#
# check point
#
Ip4->Transmit {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4TransmitConf1AssertionGuid012                      \
                "Ip4.Transmit - Conf - with GatewayAddress invalid"            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

SetIpv4Address R_OverrideData.SourceAddress  "172.16.210.101"
SetIpv4Address R_OverrideData.GatewayAddress "255.255.255.255"

#
# check point
#
Ip4->Transmit {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4TransmitConf1AssertionGuid013                      \
                "Ip4.Transmit - Conf - with GatewayAddress invalid"            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

CleanUpEutEnvironment
