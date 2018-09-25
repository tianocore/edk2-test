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
CaseGuid        AAEA2C83-D15F-48ca-8A34-F69E5756AEC7
CaseName        Cancel.Conf1.Case1
CaseCategory    MNP
CaseDescription {Test the Cancel Conformance of MNP - Aborts an asynchronous   \
	               transmit or receive request - Call Cancel() when the child    \
	               has not been configured. The return status should be          \
	               EFI_NOT_STARTED.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
#Begin log ...
#
BeginLog
BeginScope      _MNP_CANCEL_CONFORMANCE1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS	Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfData

#
# Create Child
#
MnpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Cancel - Conf - Create Child"                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Cancel be child start - EFI_NOT_STARTED
#
Mnp->Cancel "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $MnpCancelConf1AssertionGuid001                        \
                "Mnp.Cancel - Conf - Call Cancel when child not start"         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

#
# Destroy Child
#
MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MnpSB.Cancel - Conf - Destroy Child1"                         \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"

EndScope  _MNP_CANCEL_CONFORMANCE1_CASE1_

#
# EndLog
#
EndLog
