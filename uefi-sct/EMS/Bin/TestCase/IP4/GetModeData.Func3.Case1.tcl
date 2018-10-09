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
CaseGuid        15BC909E-CB7E-469f-91B8-3DFF7A6474B5
CaseName        GetModeData.Func3.Case1
CaseCategory    IP4
CaseDescription {Test the GetModeData Function of IP4 - Invoke GetModeData() to\
                 get all mode data and check the RouteTable data item.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# Begin scope
#
BeginScope _IP4_GETMODEDATA_FUNCTION3_CASE1_

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
EFI_IP4_MODE_DATA                R_Ip4ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE          R_SnpModeData
EFI_IP4_ROUTE_TABLE              R_RouteTable
EFI_IPv4_ADDRESS                 R_SubnetAddress
EFI_IPv4_ADDRESS                 R_SubnetMask
EFI_IPv4_ADDRESS                 R_GatewayAddress
UINTN                            R_CopyLen

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.GetModeData - Func - Create Child"                     \
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
                "Ip4.GetModeData - Func - Config Child"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# check point
#
Ip4->GetModeData {&@R_Ip4ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Get Mode Data"                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Ip4ModeData.RouteCount
if { ${R_Ip4ModeData.RouteCount} == 1 } {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Get RouteCount"                             \
                "Return - ${R_Ip4ModeData.RouteCount}, Expected - 1"

SetVar R_CopyLen [Sizeof R_RouteTable]
GetVar R_CopyLen
BS->CopyMem {&@R_RouteTable, @R_Ip4ModeData.RouteTable, @R_CopyLen, &@R_Status}
GetAck

set assert pass
set R_SubnetAddress [GetIpv4Address R_RouteTable.SubnetAddress]
if {[string compare -nocase $R_SubnetAddress 172.16.210.0] != 0} {
  set assert fail
  puts "R_SubnetAddress - $R_SubnetAddress"
}
set R_SubnetMask [GetIpv4Address R_RouteTable.SubnetMask]
if {[string compare -nocase $R_SubnetMask 255.255.255.0] != 0} {
  set assert fail
  puts "R_SubnetMask - $R_SubnetMask"
}
set R_GatewayAddress [GetIpv4Address R_RouteTable.GatewayAddress]
if {[string compare -nocase $R_GatewayAddress 0.0.0.0] != 0} {
  set assert fail
  puts "R_GatewayAddress - $R_GatewayAddress"
}
RecordAssertion $assert $Ip4GetModeDataFunc3AssertionGuid001                   \
                        "Ip4.GetModeData - check R_RouteTable field"

Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.GetModeData - Func - Destroy Child"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

VifDown 0

#
# End scope
#
EndScope _IP4_GETMODEDATA_FUNCTION3_CASE1_

#
# End Log
#
EndLog
