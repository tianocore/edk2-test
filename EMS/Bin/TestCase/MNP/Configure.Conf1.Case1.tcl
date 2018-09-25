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
CaseGuid        A55A10C4-48F1-40b6-B925-1BCFB668DE6C
CaseName        Configure.Conf1.Case1
CaseCategory    MNP
CaseDescription {Test the Configure conformance of MNP - Call MNP.Configure()  \
	               with MnpConfigData.ProtocolTypeFilter being invalid. The      \
	               return status should be EFI_INVALID_PARAMETER.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#	
BeginLog
BeginScope _MNP_CONFIGURE_CONFORMANCE1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfData

MnpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Configure - Conf - Create Child"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Configure with invalid parameter
#
SetMnpConfigData R_MnpConfData 0 0 1000 TRUE FALSE TRUE TRUE FALSE FALSE TRUE

Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $MnpConfigureConf1AssertionGuid001                     \
                "MnpSB.Configure - Call Configure() with invalid parameter -   \
                R_MnpConfData.ProtocolTypeFilter is not valid."                \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Destroy this child
#
MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MnpSB.Configure - Conf - Destroy Child1"                      \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"


EndScope _MNP_CONFIGURE_CONFORMANCE1_CASE1_

#
# EndLog
#
EndLog                   
