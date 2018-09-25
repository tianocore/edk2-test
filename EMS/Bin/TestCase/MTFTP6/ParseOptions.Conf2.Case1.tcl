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
CaseGuid        B952630F-D484-4fd5-AA12-CF67F9B3EBA8
CaseName        ParseOptions.Conf2.Case1
CaseCategory    MTFTP6
CaseDescription {Test ParseOptions Conformance of MTFTP6 - Invoke ParseOptions()  \
                 when packet is NULL.EFI_INVALID_PARAMETER should be returned.}
################################################################################

Include MTFTP6/include/Mtftp6.inc.tcl
#
# Begin log ...
#
BeginLog

BeginScope _MTFTP6_PARSEOPTIONS_CONFORMANCE2_CASE1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
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
                "Mtftp6SB.CreateChild - Create Child 1"                   \
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
# check point:Call ParseOptions when the packet is NULL.\
#             EFI_INVALID_PARAMETER should be returned.
#
UINT32                      R_PacketLen
SetVar R_PacketLen          64
UINT32                      R_OptionCount
POINTER                     R_OptionList

Mtftp6->ParseOptions "@R_PacketLen, NULL, &@R_OptionCount,&@R_OptionList, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Mtftp6ParseOptionsConf2AssertionGuid001     \
               "Mtftp6.ParseOptions() -Conf- Call ParseOption when Packet is NULL." \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Destroy child
#
Mtftp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp6SB.DestroyChild - Destroy Child 1"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EUTClose
				
EndScope _MTFTP6_PARSEOPTIONS_CONFORMANCE2_CASE1_

#
# End Log
#
EndLog