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
CaseGuid        0FDF6378-A025-4a84-AD29-674080F483A6
CaseName        GetModeData.Func1.Case1
CaseCategory    MNP
CaseDescription {Test the Function of MNP.GetModeData - Call MNP.GetModeData() \
	               to get the data configured previously, and verify the data.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope _MNP_GETMODEDATA_FUNCTION1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                             R_Status
UINTN                             R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA   R_MnpConfData
EFI_MANAGED_NETWORK_CONFIG_DATA   R_SampleMnpConfData
EFI_SIMPLE_NETWORK_MODE           R_SnpModeData

UINTN                             TempStatus

MnpServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MNP.GetModeData - Create Child"                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetMnpConfigData R_MnpConfData 0 0 0 TRUE FALSE TRUE TRUE FALSE FALSE TRUE
SetVar  R_SampleMnpConfData @R_MnpConfData
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MNP.GetModeData - Configure"                                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# Get Config data we configured
#
Mnp->GetModeData {&@R_MnpConfData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $MnpGetModeDataFunc1AssertionGuid001                   \
                "MNP.GetModeData - Basic Func - Call GetModeData() to get the  \
                configured data"                                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                
set TempStatus $R_Status

#
# Check Configure Data
#
GetVar      R_MnpConfData
GetVar      R_SampleMnpConfData
set assert [VerifyMnpConfData R_MnpConfData R_SampleMnpConfData]

if {$assert == "pass"  && $TempStatus == $EFI_SUCCESS} {
  set assert pass
} else {
  set assert fail
}

RecordAssertion $assert $MnpGetModeDataFunc1AssertionGuid002                   \
                "MNP.GetModeData - Check the configured data we got after      \
                calling GetModeData()"                                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MNP.GetModeData - Destroy Child"                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"  

EndScope _MNP_GETMODEDATA_FUNCTION1_CASE1_

#
# End log
#
EndLog
                            