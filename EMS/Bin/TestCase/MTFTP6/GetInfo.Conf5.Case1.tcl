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
CaseGuid          1A157212-CE32-4237-93BB-70F2FE20B983
CaseName          GetInfo.Conf5.Case1
CaseCategory      MTFTP6
CaseDescription   {Test GetInfo Conformance of MTFTP6 - Invoke  \
                   GetInfo() function when PacketLength is NULL. 
                   EFI_INVALID_PARAMETER should be returned.}
################################################################################

Include MTFTP6/include/Mtftp6.inc.tcl

#
# Begin log ...
#
BeginLog

BeginScope _MTFTP6_GETINFO_CONFORMANCE5_CASE1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

Mtftp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Mtftp6SB.CreateChild - Create Child "                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Check Point: Call Configure function with valid parameters.\
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
# check point: Call GetInfo function when PacketLength is NULL.  \
#              EFI_INVALID_PARAMETER should be returned.
#
EFI_MTFTP6_OVERRIDE_DATA         R_OverrideData

SetIpv6Address    R_OverrideData.ServerIp       "2002::2"
SetVar            R_OverrideData.ServerPort     1780
SetVar            R_OverrideData.TryCount       3
SetVar            R_OverrideData.TimeoutValue   3

CHAR8                            R_Filename(20)
SetVar R_Filename                "Shell.efi"

UINT8                            R_OptionCount
SetVar R_OptionCount             1

EFI_MTFTP6_OPTION                R_OptionList(8)

CHAR8                            R_OptionStr0(10)
CHAR8                            R_ValueStr0(10)
SetVar R_OptionStr0                          "tsize"
SetVar R_ValueStr0                           "0"
SetVar R_OptionList(0).OptionStr             &@R_OptionStr0
SetVar R_OptionList(0).ValueStr              &@R_ValueStr0


Mtftp6->GetInfo "&@R_OverrideData, &@R_Filename, NULL, @R_OptionCount, \
                                     &@R_OptionList, NULL, NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Mtftp6GetInfoConf5AssertionGuid001                         \
                "Mtftp6.GetInfo -conf- Call GetInfo when PacketLength is NULL."  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Destroy Child 
#
Mtftp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                  \
                "Mtftp6SB.DestroyChild - Destroy Child "                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EUTClose
				
EndScope _MTFTP6_GETINFO_CONFORMANCE5_CASE1_

#
# End Log
#
EndLog