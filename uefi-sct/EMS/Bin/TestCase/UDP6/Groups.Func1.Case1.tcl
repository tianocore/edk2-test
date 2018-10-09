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
CaseGuid        EA111B08-B337-4d02-89B0-5E30CB1FA596
CaseName        Groups.Func1.Case1
CaseCategory    UDP6

CaseDescription {Test the Groups Function of UdP6 - Invoke Groups()     \
                 with valid parameters and EFI_SUCCESS should be returned.
                }
################################################################################

Include UdP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope  _UDP6_GROUPS_FUNC1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Check point: Create child.
#
Udp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid  \
                "Udp6SB.CreateChild - Create Child "                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Check Point:Call Configure with valid parameters.EFI_SUCCESS should be returned.
#
EFI_UDP6_CONFIG_DATA                            R_Udp6ConfigData
SetVar  R_Udp6ConfigData.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData.TrafficClass           0
SetVar  R_Udp6ConfigData.HopLimit               64
SetVar  R_Udp6ConfigData.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData.StationAddress "::"
SetVar  R_Udp6ConfigData.StationPort            1780
SetIpv6Address  R_Udp6ConfigData.RemoteAddress  "2002::2"
SetVar  R_Udp6ConfigData.RemotePort             1781
  
Udp6->Configure "&@R_Udp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid  \
                "Udp6.Configure - Configure Child with valid parameters"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Groups when JoinFlag is TRUE and MultiCastAddress is "ff02::2".   \
#              EFI_SUCCESS should be returned and Call GetModeData to check the added \
#              Group entry.
#
BOOLEAN                             R_JoinFlag
EFI_IPv6_ADDRESS                    R_MulticastAddress
SetVar           R_JoinFlag         TRUE
SetIpv6Address   R_MulticastAddress "ff02::2"
  
Udp6->Groups     "@R_JoinFlag, &@R_MulticastAddress, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6GroupsFunc1AssertionGuid001        \
                "Udp6.Groups -conf- Join a Group"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EFI_UDP6_CONFIG_DATA                            R_Udp6ConfigData1
EFI_IP6_MODE_DATA                               R_Ip6ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA                 R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE                         R_SnpModeData

Udp6->GetModeData "&@R_Udp6ConfigData1, &@R_Ip6ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6GroupsFunc1AssertionGuid002                  \
                "Udp6.GetModeData-Func-Call GetModeData to check the added group entry." \
                "ReturnStatus-$R_Status, ExpectedStatus-$EFI_SUCCESS"

GetVar   R_Ip6ModeData
set assert pass
if { ${R_Ip6ModeData.GroupCount} != 0x01 } {
    set assert fail
}
RecordAssertion $assert $Udp6GroupsFunc1AssertionGuid002       \
                "Udp6.Groups - Func - Check Ip6ModeData.GroupCount field"

EFI_IPv6_ADDRESS                              R_GroupTable
UINTN                                         R_CopyLen
SetVar R_CopyLen                              [Sizeof R_GroupTable]
BS->CopyMem "&@R_GroupTable, @R_Ip6ModeData.GroupTable, @R_CopyLen, &@R_Status"
GetAck

GetVar  R_GroupTable
GetVar  R_MulticastAddress
set GroupTableAddress [GetIpv6Address R_GroupTable]
set MulticastAddress  [GetIpv6Address R_MulticastAddress]

set assert pass
if {[string compare -nocase $GroupTableAddress $MulticastAddress] != 0} {
  set assert fail
}
RecordAssertion $assert $Ip6GroupsFunc1AssertionGuid002       \
                "Udp6.Groups - Func - Check Ip6ModeData.GroupTable field"

#
# Check Point: Call Groups to leave the Group "ff02::2" that we joined before.     \
#              EFI_SUCCESS should be returned and call GetModeData to check whether\
#              the GroupTable entry has been deleted.
#
Udp6->Groups     "FALSE, &@R_MulticastAddress, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6GroupsFunc1AssertionGuid003        \
                "Udp6.Groups -conf- Leave a Group"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EFI_UDP6_CONFIG_DATA                            R_Udp6ConfigData2
EFI_IP6_MODE_DATA                               R_Ip6ModeData2
EFI_MANAGED_NETWORK_CONFIG_DATA                 R_MnpConfigData2
EFI_SIMPLE_NETWORK_MODE                         R_SnpModeData2

Udp6->GetModeData "&@R_Udp6ConfigData2, &@R_Ip6ModeData2, &@R_MnpConfigData2, &@R_SnpModeData2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6GroupsFunc1AssertionGuid004                          \
                "Udp6.GetModeData-Func-Call GetModeData to check the group entry has been deleted." \
                "ReturnStatus-$R_Status, ExpectedStatus-$EFI_SUCCESS"

GetVar   R_Ip6ModeData2
set assert pass
if { ${R_Ip6ModeData2.GroupCount} != 0x00 } {
    set assert fail
}
RecordAssertion $assert $Udp6GroupsFunc1AssertionGuid004       \
                "Udp6.Groups - Func - Check Ip6ModeData.GroupCount field"

#
# Check point: Destroy child.
#
Udp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                         \
                "Udp6SB.DestroyChild - Destroy Child."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# EndScope
#
EndScope    _UDP6_GROUPS_FUNC1_
#
# End Log 
#
EndLog