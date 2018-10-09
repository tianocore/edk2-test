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
CaseGuid        B165B66F-CBD7-438b-B4D7-A34C75AE9D1A
CaseName        Groups.Func1.Case1
CaseCategory    IP6
CaseDescription {Test the Groups Function of IP6 - Invoke Groups() \
                 to join and leave a multicast group.}
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin Log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope   _IP6_GROUPS_FUNCTION1_CASE1_

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

EFI_IP6_CONFIG_DATA                           R_Ip6ConfigData
SetVar R_Ip6ConfigData.DefaultProtocol        0x11;        #Next Header: UDP
SetVar R_Ip6ConfigData.AcceptAnyProtocol      FALSE
SetVar R_Ip6ConfigData.AcceptIcmpErrors       TRUE
SetVar R_Ip6ConfigData.AcceptPromiscuous      FALSE
SetIpv6Address R_Ip6ConfigData.DestinationAddress     "::"
SetIpv6Address R_Ip6ConfigData.StationAddress         "::"
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
# Check point: Call Groups with JoinFlag = TRUE and *GroupAddress = ff02::2
#              EFI_SUCCESS should be returned.
#
EFI_IPv6_ADDRESS                              R_GroupAddress
SetIpv6Address R_GroupAddress                 "ff02::2"
Ip6->Groups "TRUE, &@R_GroupAddress, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6GroupsFunc1AssertionGuid001         \
                "Ip6.Groups - Func - Join a multicast group"                \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Call GetModeData to check the added group entry.
#
EFI_IP6_MODE_DATA                             R_Ip6ModeData
Ip6->GetModeData "&@R_Ip6ModeData, NULL, NULL, &@R_Status"
GetAck

#
# Verify Ip6ModeData.GroupCount and *GroupTable
#
GetVar R_Ip6ModeData
set assert pass
if { ${R_Ip6ModeData.GroupCount} != 0x01 } {
    set assert fail
}

RecordAssertion $assert $Ip6GroupsFunc1AssertionGuid002       \
                "Ip6.Groups - Func - Check Ip6ModeData.GroupCount field"

EFI_IPv6_ADDRESS                              R_GroupTable
UINTN                                         R_CopyLen
SetVar R_CopyLen                              [Sizeof R_GroupTable]
BS->CopyMem "&@R_GroupTable, @R_Ip6ModeData.GroupTable, @R_CopyLen, &@R_Status"
GetAck

GetVar R_GroupTable
GetVar R_GroupAddress
set GroupTableString [GetIpv6Address R_GroupTable]
puts $GroupTableString
set GroupAddressString [GetIpv6Address R_GroupAddress]
puts $GroupAddressString

set assert pass
if {[string compare -nocase $GroupTableString $GroupAddressString] != 0} {
  set assert fail
}

RecordAssertion $assert $Ip6GroupsFunc1AssertionGuid003       \
                "Ip6.Groups - Func - Check Ip6ModeData.GroupTable field"

#
# Check point: Call Groups with JoinFlag = FALSE and *GroupAddress = ff02::2
#              EFI_SUCCESS should be returned.
#
SetIpv6Address R_GroupAddress                 "ff02::2"
Ip6->Groups "FALSE, &@R_GroupAddress, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6GroupsFunc1AssertionGuid004         \
                "Ip6.Groups - Func - Leave a multicast group"                \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Call GetModeData to check the deleted group entry.
#
Ip6->GetModeData "&@R_Ip6ModeData, NULL, NULL, &@R_Status"
GetAck

#
# Verify Ip6ModeData.GroupCount and *GroupTable
#
GetVar R_Ip6ModeData
set assert pass
if { ${R_Ip6ModeData.GroupCount} != 0x00 } {
    set assert fail
}

RecordAssertion $assert $Ip6GroupsFunc1AssertionGuid005       \
                "Ip6.Groups - Func - Check Ip6ModeData.GroupCount field"

#
# DestroyChild.
#
Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# End scope
#
EndScope _IP6_GROUPS_FUNCTION1_CASE1_
#
# End Log
#
EndLog
