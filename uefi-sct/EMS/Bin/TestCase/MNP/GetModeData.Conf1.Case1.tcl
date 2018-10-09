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
CaseGuid        2E767D7E-8306-4bfa-81A9-AB18DC7811A2
CaseName        GetModeData.Conf1.Case1
CaseCategory    MNP
CaseDescription {Test the conformance of MNP.GetModeData - Call GetModeData()  \
	               with the parameter MnpConfigData not NULL when the MNP child  \
	               has not been configured. The return status should be          \
	               EFI_NOT_STARTED}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope  _MNP_GETMODEDATA_CONFORMANCE1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                             R_Status
UINTN                             R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA   R_MnpConfData
EFI_SIMPLE_NETWORK_MODE           R_SnpModeData

MnpServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MNP.GetModeData - Create Child"                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Get Default MNP Config data
#
Mnp->GetModeData {&@R_MnpConfData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $MnpGetModeDataConf1AssertionGuid001                   \
                "MNP.GetModeData - Call GetModeData() when the MNP child       \
                driver instance has not been configured."                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MNP.GetModeData - Destroy Child"                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS" 

EndScope _MNP_GETMODEDATA_CONFORMANCE1_CASE1_

#
# End log
#
EndLog
