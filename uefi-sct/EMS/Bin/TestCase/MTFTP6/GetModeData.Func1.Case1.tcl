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
CaseGuid        E28129E1-3587-4440-B10C-86D00ADB9A96
CaseName        GetModeData.Func1.Case1
CaseCategory    MTFTP6
CaseDescription {Test the GetModeData Function of MtftP6 -Invoke GetModeData()  \
                 with valid parameters.EFI_SUCCESS should be returned.
                }
################################################################################

Include MTFTP6/include/Mtftp6.inc.tcl
#
# Begin log ...
#
BeginLog

BeginScope _MTFTP6_GETMODEDATA_FUNC1_CASE1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Create child
#
Mtftp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                    \
                "Mtftp6SB.CreateChild - Create Child "                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Check Point: Call Configure function with valid parameters. 
#              EFI_SUCCESS should be returned.
#
EFI_MTFTP6_CONFIG_DATA      R_Mtftp6ConfigData
SetIpv6Address    R_Mtftp6ConfigData.StationIp         "2002::4321" 
SetVar            R_Mtftp6ConfigData.LocalPort         1780
SetIpv6Address    R_Mtftp6ConfigData.ServerIp          "2002::2"
SetVar            R_Mtftp6ConfigData.InitialServerPort 0
SetVar            R_Mtftp6ConfigData.TryCount          3
SetVar            R_Mtftp6ConfigData.TimeoutValue      3

Mtftp6->Configure "&@R_Mtftp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Mtftp6.Configure -conf- Call Configure with valid parameters"  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call GetModeData function with valid parameters.
#              EFI_SUCCESS should be returned. 
#
EFI_MTFTP6_MODE_DATA         R_Mtftp6ModeData

Mtftp6->GetModeData "&@R_Mtftp6ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Mtftp6GetModeDataFunc1AssertionGuid001         \
                "Mtftp6.GetModeData -Func- Call GetModeData with valid parameters."    \
                "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

GetVar R_Mtftp6ModeData
#
# Check Point:Mtftp6ModeData.ConfigData should be the same as previous set.
#
EFI_MTFTP6_CONFIG_DATA       R_ConfigData
UINTN                        R_CopyLen
SetVar R_CopyLen [Sizeof R_ConfigData]
GetVar R_CopyLen
BS->CopyMem "&@R_ConfigData, &@R_Mtftp6ModeData.ConfigData, @R_CopyLen, &@R_Status"
GetAck

EFI_MTFTP6_CONFIG_DATA       R_ConfigData1
SetIpv6Address               R_ConfigData1.StationIp  "2002::4321"
set assert pass
set S1 [GetIpv6Address R_ConfigData1.StationIp]
set S2 [GetIpv6Address R_ConfigData.StationIp]

set temp [string compare $S1 $S2]
if {$temp != 0} {
   set assert fail
}
RecordAssertion  $assert $GenericAssertionGuid                          \
                 "Mtftp6ModeData.ConfigData.StationIp should be the same as previous set."

GetVar R_ConfigData.LocalPort
set assert pass
if { ${R_ConfigData.LocalPort} != 1780} {
   set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                            \
                "ConfigData.LocalPort should be the same as previous set."

SetIpv6Address  R_ConfigData1.ServerIp  "2002::2"
set assert pass
set S1 [GetIpv6Address R_ConfigData1.ServerIp]
set S2 [GetIpv6Address R_ConfigData.ServerIp]

set temp [string compare $S1 $S2]
if {$temp != 0} {
   set assert fail
}
RecordAssertion  $assert $GenericAssertionGuid                          \
                 "Mtftp6ModeData.ConfigData.ServerIp should be the same as previous set."

GetVar R_ConfigData.InitialServerPort
set assert pass 
if { ${R_ConfigData.InitialServerPort} != 0 } {
   set assert fail
}
RecordAssertion  $assert $GenericAssertionGuid                                \
                 "Mtftp6ModeData.ConfigData.InitialServerPort should be the same as previous set."

GetVar R_ConfigData.TryCount
set assert pass
if { ${R_ConfigData.TryCount} != 3} {
   set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                             \
                "TryCount should be the same as previous set equals 3"

GetVar R_ConfigData.TimeoutValue
set assert pass
if { ${R_ConfigData.TimeoutValue} != 3} {
   set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                             \
                "TimeoutValue should be the same as previous set equals 3"

#
# Destroy child
#
Mtftp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Mtftp6SB.DestroyChild - Destroy Child "                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EUTClose
				
EndScope _MTFTP6_GETMODEDATA_FUNC1_CASE1_

#
# End Log
#
EndLog