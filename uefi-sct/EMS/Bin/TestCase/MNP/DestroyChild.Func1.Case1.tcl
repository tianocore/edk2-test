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
CaseGuid        CF2C62DB-7BBF-4921-B7BC-6E944B76495D
CaseName        DestroyChild.Func1.Case1
CaseCategory    MNP
CaseDescription {Test the DestroyChild function of MNPSB - Call                \
	               MnpServiceBinding.DestroyChild() to destroy the child handle  \
	               created before.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope _MNP_DESTROYCHILD_FUNCTION1_CASE1_

UINTN                            R_Status
UINTN                            R_Handle

#
# Create Child R_Handle
#
MnpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "ManagedNetwork.GetModeData - Create Child"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Destroy Child R_Handle
#
MnpServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $MnpDestroyChildFunc1AssertionGuid001                  \
                "MnpSB.DestroyChild - Destroy Child"                           \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"

EndScope _MNP_DESTROYCHILD_FUNCTION1_CASE1_

#
# End log ...
#
EndLog
