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
CaseGuid        E9C9345D-7721-4c8b-AE74-A812F2DFBDD1
CaseName        CreateChild.Conf1.Case2
CaseCategory    MNP
CaseDescription {Test the CreateChild function of MNPSB - Call                 \
	               MnpServiceBinding.CreateChild() with the parameter ChildHandle\
	               pointing to another existed ChildPointer.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope  _MNP_CREATECHILD_CONFORMANCE1_CASE2_

UINTN                            R_Status
UINTN                            R_Handle1
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfData

SetMnpConfigData R_MnpConfData 0 0 0 TRUE FALSE TRUE TRUE FALSE FALSE TRUE

MnpServiceBinding->CreateChild "&@R_Handle1, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MnpSB.CreateChild - Create Child 1"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# The pointer points to existed another ChildPointer
#
MnpServiceBinding->CreateChild "&@R_Handle1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $MnpCreateChildConf1AssertionGuid003                   \
                "MnpSB.CreateChild - Create Child 1 - Install I/0"             \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_INVALID_PARAMETER"

Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MnpSB.CreateChild - Config Child 1"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

MnpServiceBinding->DestroyChild {@R_Handle1, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MnpSB.DestroyChild - Destroy Child 1"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"  

EndScope _MNP_CREATECHILD_CONFORMANCE1_CASE2_

#
# EndLog
#
EndLog
