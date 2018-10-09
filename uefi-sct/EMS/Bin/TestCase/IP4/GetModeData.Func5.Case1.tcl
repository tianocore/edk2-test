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
CaseGuid        40C62405-70A7-49ec-A20B-31A7B515E3D7
CaseName        GetModeData.Func5.Case1
CaseCategory    IP4
CaseDescription {Test the GetModeData Function of IP4 - Invoke GetModeData() to\
                 check the instance status when Configure() has been called    \
                 with the parameter Ip4ModeData being NULL.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# Begin scope
#
BeginScope _IP4_GETMODEDATA_FUNCTION5_CASE1_

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

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.GetModeData - Func - Create Child"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_IpConfigData.DefaultProtocol          0
SetVar R_IpConfigData.AcceptAnyProtocol        TRUE
SetVar R_IpConfigData.AcceptIcmpErrors         TRUE
SetVar R_IpConfigData.AcceptBroadcast          TRUE
SetVar R_IpConfigData.AcceptPromiscuous        TRUE
SetVar R_IpConfigData.UseDefaultAddress        FALSE
SetIpv4Address R_IpConfigData.StationAddress   "172.16.210.102"
SetIpv4Address R_IpConfigData.SubnetMask       "255.255.255.0"
SetVar R_IpConfigData.TypeOfService            0
SetVar R_IpConfigData.TimeToLive               16
SetVar R_IpConfigData.DoNotFragment            TRUE
SetVar R_IpConfigData.RawData                  FALSE
SetVar R_IpConfigData.ReceiveTimeout           0
SetVar R_IpConfigData.TransmitTimeout          0

#
# check point
#
Ip4->GetModeData {&@R_Ip4ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Func - Get Mode Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set assert pass
GetVar R_Ip4ModeData.IsStarted
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "false"] != 0} {
  set assert fail
}
GetVar R_Ip4ModeData.IsConfigured
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "false"] != 0} {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                        "Ip4.GetModeData - Func - check status"

Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Func - Config Child 1"                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# check point
#
Ip4->GetModeData {&@R_Ip4ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Func - Get Mode Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set assert pass
GetVar R_Ip4ModeData.IsStarted
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "true"] != 0} {
  set assert fail
}
GetVar R_Ip4ModeData.IsConfigured
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "true"] != 0} {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                        "Ip4.GetModeData - Func - check status"

Ip4->Configure {NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Func - Reset Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4->GetModeData {&@R_Ip4ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Func - Get Mode Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set assert pass
GetVar R_Ip4ModeData.IsStarted
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "false"] != 0} {
  set assert fail
}
GetVar R_Ip4ModeData.IsConfigured
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "false"] != 0} {
  set assert fail
}
RecordAssertion $assert $Ip4GetModeDataFunc5AssertionGuid001                   \
                        "Ip4.GetModeData - Func - check status"

Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SB.GetModeData - Func - Destroy Child"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

VifDown 0

#
# End scope
#
EndScope _IP4_GETMODEDATA_FUNCTION5_CASE1_

#
# End Log
#
EndLog
