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
CaseGuid        EB9C89DD-ECB4-4447-9FE8-827DFD16F9E4
CaseName        Groups.Conf4.Case1
CaseCategory    IP4
CaseDescription {Test the Groups Conformance of IP4 - Invoke Groups() when the \
                 instance has not been started. The return status should be    \
                 EFI_NOT_STARTED.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_GROUPS_CONFORMANCE4_CASE1_

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
EFI_IPv4_ADDRESS                 R_GroupAddress

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SB.Groups - Conf - Create Child"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_IpConfigData.DefaultProtocol            0
SetVar R_IpConfigData.AcceptAnyProtocol          TRUE
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

Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Groups - Conf - Config Child"                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4->Configure {NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Groups - Conf - reset Child"                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetIpv4Address R_GroupAddress "225.0.0.1"

Ip4->Groups {TRUE, &@R_GroupAddress, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Ip4GroupsConf4AssertionGuid001                        \
                "Ip4.Groups - Conf - not started"                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

Ip4->Groups {FALSE, &@R_GroupAddress, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Ip4GroupsConf4AssertionGuid001                        \
                "Ip4.Groups - Conf - not started"                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

Ip4->Groups {FALSE, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Ip4GroupsConf4AssertionGuid001                        \
                "Ip4.Groups - Conf - not started"                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SB.Groups - Conf - Destroy Child"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

VifDown 0

#
# End scope
#
EndScope _IP4_GROUPS_CONFORMANCE4_CASE1_

#
# End Log
#
EndLog
