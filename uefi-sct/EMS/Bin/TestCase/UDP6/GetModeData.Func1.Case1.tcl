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
CaseGuid        D3135A6E-66FF-472f-8437-628CAA90CA2E
CaseName        GetModeData.Func1.Case1
CaseCategory    UDP6

CaseDescription {Test the GetModeData Function of UdP6 - Invoke GetModeData()     \
                 with valid parameters and check whether Udp6ModeData->ConfigData \
                 is the same as previous set.EFI_SUCCESS should be returned.
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
BeginScope  _UDP6_GETMODEDATA_FUNC1_

EUTSetup

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
# Check Point: Call GetModeData function with Udp6ConfigData,Ip6ModeData,MnpConfigData,\
#              SnpModeData not NULL.EFI_SUCCESS should be returned,and\
#              Udp6ModeData->ConfigData should be the same as previous set.
#
EFI_UDP6_CONFIG_DATA                            R_Udp6ConfigData1
EFI_IP6_MODE_DATA                               R_Ip6ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA                 R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE                         R_SnpModeData

Udp6->GetModeData "&@R_Udp6ConfigData1, &@R_Ip6ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6GetModeDataFunc1AssertionGuid001      \
                "Udp6.GetModeData-Func-Call GetModeData with valid parameters" \
                "ReturnStatus-$R_Status, ExpectedStatus-$EFI_SUCCESS"

GetVar R_Ip6ModeData.IsConfigured
set assert fail
if { ${R_Ip6ModeData.IsConfigured} == true} {
    set assert pass
}
RecordAssertion $assert $Udp6GetModeDataFunc1AssertionGuid002          \
                "Udp6.GetModeData - Func - Udp6ModeData.IsConfigured should be TRUE"

GetVar R_Udp6ConfigData1
set assert pass
if { ${R_Udp6ConfigData1.AcceptPromiscuous} != false} {
    set assert fail  
}
RecordAssertion $assert $Udp6GetModeDataFunc1AssertionGuid003                        \
                "ConfigData.AcceptPromiscuous should be FALSE as previous set."

set assert pass
if { ${R_Udp6ConfigData1.AcceptAnyPort} != false} {
    set assert fail  
}
RecordAssertion $assert $Udp6GetModeDataFunc1AssertionGuid003                        \
                "ConfigData.AcceptAnyPort should be FALSE as previous set."

set assert pass
if { ${R_Udp6ConfigData1.AllowDuplicatePort} != false} {
    set assert fail  
}
RecordAssertion $assert $Udp6GetModeDataFunc1AssertionGuid003                        \
                "ConfigData.AllowDuplicatePort should be FALSE as previous set."

set assert pass
if {${R_Udp6ConfigData1.TrafficClass} != 0} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.TrafficClass should be 0 as previous set."

set assert pass
if {${R_Udp6ConfigData1.HopLimit} != 64} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.HopLimit should be 64 as previous set."

set assert pass
if {${R_Udp6ConfigData1.ReceiveTimeout} != 50000} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.ReceiveTimeout should be 50000 as previous set."

set assert pass
if {${R_Udp6ConfigData1.TransmitTimeout} != 50000} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.TransmitTimeout should be 50000 as previous set."

SetIpv6Address  R_Udp6ConfigData.StationAddress  "2002::4321"
set assert pass
set S1 [GetIpv6Address R_Udp6ConfigData1.StationAddress]
set S2 [GetIpv6Address R_Udp6ConfigData.StationAddress]

set temp [string compare $S1 $S2]
if {$temp != 0} {
   set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.StationAddress should be the same as previous set."

set assert pass
if {${R_Udp6ConfigData1.StationPort} != 1780} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.StationPort should be 1780 as previous set."

set assert pass
set S1 [GetIpv6Address R_Udp6ConfigData1.RemoteAddress]
set S2 [GetIpv6Address R_Udp6ConfigData.RemoteAddress]
set temp [string compare $S1 $S2]
if {$temp != 0} {
   set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.RemoteAddress should be 2002::2 as previous set."

set assert pass
if {${R_Udp6ConfigData1.RemotePort} != 1781} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.RemotePort should be 1781 as previous set."

#
# Check point: Destroy child.
#
Udp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                         \
                "Udp6SB.DestroyChild - Destroy Child."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EUTClose
				
#
# EndScope
#
EndScope    _UDP6_GETMODEDATA_FUNC1_
#
# End Log 
#
EndLog