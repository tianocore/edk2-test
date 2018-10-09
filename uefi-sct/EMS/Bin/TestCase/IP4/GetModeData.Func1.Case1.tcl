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
CaseGuid        D2435814-2E95-489c-AC9F-11C17222F18C
CaseName        GetModeData.Func1.Case1
CaseCategory    IP4
CaseDescription {Test the GetModeData Function of IP4 - Invoke GetModeData() to\
                 get IP4/snp/mnp mode data or all mode data when the Ip4 child \
                 has not been configured or configured.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# Begin scope ...
#
BeginScope   _IP4_GETMODEDATA_FUNCTION1_CASE1_

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
                "Ip4SBP.GetModeData - Func - Create Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_IpConfigData.DefaultProtocol           0
SetVar R_IpConfigData.AcceptAnyProtocol         TRUE
SetVar R_IpConfigData.AcceptIcmpErrors          TRUE
SetVar R_IpConfigData.AcceptBroadcast           TRUE
SetVar R_IpConfigData.AcceptPromiscuous         TRUE
SetVar R_IpConfigData.UseDefaultAddress         FALSE
SetIpv4Address R_IpConfigData.StationAddress    "172.16.210.102"
SetIpv4Address R_IpConfigData.SubnetMask        "255.255.255.0"
SetVar R_IpConfigData.TypeOfService             0
SetVar R_IpConfigData.TimeToLive                16
SetVar R_IpConfigData.DoNotFragment             TRUE
SetVar R_IpConfigData.RawData                   FALSE
SetVar R_IpConfigData.ReceiveTimeout            0
SetVar R_IpConfigData.TransmitTimeout           0

#
# check point
#
Ip4->GetModeData {&@R_Ip4ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip4GetModeDataFunc1AssertionGuid001                   \
                "Ip4.GetModeData - Func - Get all Mode Data before Configured" \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4->GetModeData {&@R_Ip4ModeData, NULL, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip4GetModeDataFunc1AssertionGuid002                   \
                "Ip4.GetModeData - Func - Get Ip4 Data before Configured"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4->GetModeData {NULL, &@R_MnpConfigData, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip4GetModeDataFunc1AssertionGuid003                   \
                "Ip4.GetModeData - Func - Get Mnp Data before Configured"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4->GetModeData {NULL, NULL, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip4GetModeDataFunc1AssertionGuid004                   \
                "Ip4.GetModeData - Func - Get Snp Data before Configured"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


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
RecordAssertion $assert $Ip4GetModeDataFunc1AssertionGuid005                   \
                "Ip4.GetModeData - Func - Get Mode Data after Configured"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4->GetModeData {&@R_Ip4ModeData, NULL, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip4GetModeDataFunc1AssertionGuid006                   \
                "Ip4.GetModeData - Func - Get Ip4 Data after Configured"       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4->GetModeData {NULL, &@R_MnpConfigData, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip4GetModeDataFunc1AssertionGuid007                   \
                "Ip4.GetModeData - Func - Get Mnp Data after Configured"       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4->GetModeData {NULL, NULL, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip4GetModeDataFunc1AssertionGuid008                   \
                "Ip4.GetModeData - Func - Get Snp Data after Configured"       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

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
EndScope _IP4_GETMODEDATA_FUNCTION1_CASE1_

#
# End Log
#
EndLog
