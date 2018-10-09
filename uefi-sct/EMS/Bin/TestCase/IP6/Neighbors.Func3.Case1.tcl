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
CaseGuid        76B5D476-9C2A-4ace-B84C-0730965BA61F
CaseName        Neighbors.Func3.Case1
CaseCategory    IP6
CaseDescription {Test the Neighbors Function of IP6 - Invoke Neighbors() \
                 to add a neighbor entry and timeout later.}
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin Log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope   _IP6_NEIGHBORS_FUNCTION3_CASE1_

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
# Check point: Call Neighbors with 
#                         DeleteFlag = FALSE
#                         TargetIp6Address = 2002::1
#                         TargetLinkAddress = 00-97-3B-34-CD-9A
#                         Timeout = 2*10^7
#                         Override = FALSE
#              EFI_SUCCESS should be returned.
#
EFI_IPv6_ADDRESS                              R_TargetIp6Address
SetIpv6Address R_TargetIp6Address             "2002::1"
EFI_MAC_ADDRESS                               R_TargetLinkAddress             
SetEthMacAddress R_TargetLinkAddress          "00:97:3B:34:CD:9A"
UINT32                                        R_Timeout
SetVar R_Timeout                              20000000

Ip6->Neighbors "FALSE, &@R_TargetIp6Address, &@R_TargetLinkAddress, @R_Timeout, FALSE, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6NeighborsFunc3AssertionGuid001         \
                "Ip6.Neighbors - Func - Add a neighbor entry"                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Call GetModeData to check the added neighbor entry.
#
EFI_IP6_MODE_DATA                             R_Ip6ModeData
Ip6->GetModeData "&@R_Ip6ModeData, NULL, NULL, &@R_Status"
GetAck

#
# Verify Ip6ModeData.NeighborCount
#
GetVar R_Ip6ModeData
set assert fail

if { ${R_Ip6ModeData.NeighborCount} == 1 } {
    set assert pass
}

RecordAssertion $assert $Ip6NeighborsFunc3AssertionGuid002       \
                "Ip6.Neighbors - Func - Check Ip6ModeData.NeighborsCount field"

#
# Verify Ip6ModeData.NeighborCache
#
EFI_IP6_NEIGHBOR_CACHE                        R_NeighborCache
UINTN                                         R_CopyLen
#
# Copy Ip6ModeData.NeighborCache
#
SetVar R_CopyLen [Sizeof EFI_IP6_NEIGHBOR_CACHE]
BS->CopyMem "&@R_NeighborCache, @R_Ip6ModeData.NeighborCache, @R_CopyLen, &@R_Status"
GetAck
GetVar R_NeighborCache
#
# Verify Neighbor
#
set TargetIp6AddressString [GetIpv6Address R_TargetIp6Address]
puts $TargetIp6AddressString
set NeighborCacheNeighborString [GetIpv6Address R_NeighborCache.Neighbor]
puts $NeighborCacheNeighborString

set assert fail
if {[string compare -nocase $TargetIp6AddressString $NeighborCacheNeighborString] == 0} {
  set assert pass
}

RecordAssertion $assert $Ip6NeighborsFunc3AssertionGuid003       \
                "Ip6.Neighbors - Func - Check Ip6ModeData.NeighborsCache.Neighbor field"

#
# Verify LinkAddress
#
set TargetLinkAddressString [GetEthMacAddress R_TargetLinkAddress]
puts $TargetLinkAddressString
set NeighborCacheLinkAddressString [GetEthMacAddress R_NeighborCache.LinkAddress]
puts $NeighborCacheLinkAddressString

set assert fail
if {[string compare -nocase $TargetLinkAddressString $NeighborCacheLinkAddressString] == 0} {
  set assert pass
}

RecordAssertion $assert $Ip6NeighborsFunc3AssertionGuid004       \
                "Ip6.Neighbors - Func - Check Ip6ModeData.NeighborsCache.LinkAddress field"

#
# Stall 2 seconds
#
Stall 2

#
# Check point: Call GetModeData to check the over timed neighbor entry.
#
Ip6->GetModeData "&@R_Ip6ModeData, NULL, NULL, &@R_Status"
GetAck

#
# Verify Ip6ModeData.NeighborCount
#
GetVar R_Ip6ModeData
set assert fail

if { ${R_Ip6ModeData.NeighborCount} == 0 } {
    set assert pass
}

RecordAssertion $assert $Ip6NeighborsFunc3AssertionGuid005       \
                "Ip6.Neighbors - Func - Check Ip6ModeData.NeighborsCount field after time out"

#
# Delete this neighbor entry, in case that Timeout fails
#
Ip6->Neighbors "TRUE, &@R_TargetIp6Address, &@R_TargetLinkAddress, @R_Timeout, TRUE, &@R_Status"
GetAck

#
# DestroyChild.
#
Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# End scope
#
EndScope _IP6_NEIGHBORS_FUNCTION3_CASE1_
#
# End Log
#
EndLog