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
CaseGuid        7E590474-4189-47b0-AF0C-40754176D4E3
CaseName        GetModeData.Func1.Case1
CaseCategory    IP6
CaseDescription {Test the GetModeData Function of IP6 - Invoke GetModeData() \
                 to get Ip6/Mnp/Snp mode data when the Ip6 child has not been configured.}
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin Log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope   _IP6_GETMODEDATA_FUNCTION1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                                   R_Status
UINTN                                   R_Handle

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

EFI_IP6_MODE_DATA                       R_Ip6ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA         R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE                 R_SnpModeData

#
# Check point: Call GetModeData() to get Ip6ModeData, MnpConfigData and SnpModeData
#
Ip6->GetModeData "&@R_Ip6ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6GetModeDataFunc1AssertionGuid001       \
                "Ip6.GetModeData - Func - Get all Mode Data before Configured"   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Ip6ModeData.IsConfigured
set assert fail
if { ${R_Ip6ModeData.IsConfigured} == false} {
    set assert pass
}

RecordAssertion $assert $Ip6GetModeDataFunc1AssertionGuid002       \
                "Ip6.GetModeData - Func - Ip6ModeData.IsConfigured should be FALSE"

#
# DestroyChild.
#
Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# End scope
#
EndScope _IP6_GETMODEDATA_FUNCTION1_CASE1_
#
# End Log
#
EndLog
