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
CaseGuid        E51406C9-3D8C-4c68-8E72-75198EA3CB27
CaseName        Receive.Conf1.Case1
CaseCategory    MNP
CaseDescription {Test Receive conformance of MNP - Call MNP.Receive() with the \
	               parameter Token being NULL. The return status should be       \
	               EFI_INVALID_PARAMETER.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope  _MNP_RECEIVE_CONFORMANCE1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfData
EFI_MANAGED_NETWORK_COMPLETION_TOKEN  R_Token
UINTN                                 R_Context
#
# Create child R_Handle
#
MnpServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Receive - Conformance - Create"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar          [subst $ENTS_CUR_CHILD]  @R_Handle

#
# configure this child
#
SetMnpConfigData R_MnpConfData 0 0 10000 FALSE FALSE FALSE FALSE FALSE FALSE FALSE
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Receive - Conformance"                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# Call Receive function with invalid parameter
# R_Token=NULL
#
Mnp->Receive "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $MnpReceiveConf1AssertionGuid001                       \
                "Mnp.Receive - Conformance - Call Receive function with        \
                invalid parameterToken=NULL"                                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Destroy child R_Handle
#
MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Transmit - Basic Func - Dst specified"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EndScope  _MNP_RECEIVE_CONFORMANCE1_CASE1_

#
# End log
#
EndLog
