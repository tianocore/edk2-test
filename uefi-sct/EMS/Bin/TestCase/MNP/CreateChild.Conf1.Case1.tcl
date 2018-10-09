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
CaseGuid        9775E91C-A85D-42e4-8959-976455A506F0
CaseName        CreateChild.Conf1.Case1
CaseCategory    MNP
CaseDescription {Test the CreateChild conformance of MNPSB - Call              \
	               MnpServiceBinding.CreateChild() with the parameter ChildHandle\
	               being NULL. The return status should be EFI_INVALID_PARAMETER.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope _MNP_CREATECHILD_CONFORMANCE1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

SetVar  R_Handle   0

#
# The pointer is NULL, return EFI_INVALID_PARAMETER
#
MnpServiceBinding->CreateChild "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $MnpCreateChildConf1AssertionGuid001                   \
                "MnpSB.CreateChild - Create Child 1"                           \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_INVALID_PARAMETER"


#
# The pointer is not NULL, return EFI_SUCCESS
#
MnpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $MnpCreateChildConf1AssertionGuid002                   \
                "MnpSB.CreateChild - Create Child 1 - Install I/0"             \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"                             

MnpServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MnpSB.CreateChild - Destroy Child 1"                          \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"
                            

EndScope      _MNP_CREATECHILD_CONFORMANCE1_CASE1_

#
# End log
#
EndLog
