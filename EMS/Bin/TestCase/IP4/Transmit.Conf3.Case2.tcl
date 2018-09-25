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
CaseGuid        2420B14E-F178-4ed5-9F5B-A0F9B14351F4
CaseName        Transmit.Conf3.Case2
CaseCategory    IP4
CaseDescription {Test the Transmit Conformance of IP4 - Invoke Transmit() when \
                 the length of the IPv4 header + option length + total data    \
                 length is greater than MTU.The return status shoule be        \
                 EFI_BAD_BUFFER_SIZE.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_TRANSMIT_CONFORMANCE3_CASE2_

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
SetVar R_IpConfigData.DoNotFragment              FALSE
SetVar R_IpConfigData.RawData                    FALSE
SetVar R_IpConfigData.ReceiveTimeout             0
SetVar R_IpConfigData.TransmitTimeout            0

Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Conf - Config Child"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

SetIpv4Address R_TxData.DestinationAddress "172.16.210.162"
SetVar R_TxData.TotalDataLength            0x10000
SetVar R_TxData.FragmentCount              1

SetVar R_FragmentBuffer                    "IpConfigureTest"
SetVar R_FragmentTable.FragmentLength      0x10000
SetVar R_FragmentTable.FragmentBuffer      &@R_FragmentBuffer
SetVar R_TxData.FragmentTable              @R_FragmentTable
SetVar R_Token.Packet                      &@R_TxData

#
# check point
#
Ip4->Transmit {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_BAD_BUFFER_SIZE]
RecordAssertion $assert $Ip4TransmitConf3AssertionGuid002                      \
                "Ip4.Transmit - Conf - with TotalDataLength invalid"           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_BAD_BUFFER_SIZE"

Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

VifDown 0

#
# End scope
#
EndScope _IP4_TRANSMIT_CONFORMANCE3_CASE2_

#
# End log
#
EndLog
