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
CaseGuid        39F6D44D-66E7-4a24-B972-19B9BD9CF112
CaseName        DestroyChild.Conf2.Case1
CaseCategory    MNP
CaseDescription {Test the EFI_UNSUPPORTED conformance of MNPSB.DestroyChild() -\
                 Call MnpServiceBinding.DestroyChild() twice to destroy one    \
                 child handle created before.}
################################################################################

#
# Begin log ...
#
BeginLog

Include MNP/include/Mnp.inc.tcl

BeginScope _MNP_DESTROYCHILD_CONFORMANCE2_CASE1_

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
# Destroy Child R_Handle for the first time
#
MnpServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MnpSB.DestroyChild - Destroy Child for the first time."       \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"
                
#
# Destroy Child R_Handle for the second time
#
MnpServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_UNSUPPORTED]
RecordAssertion $assert $MnpDestroyChildConf2AssertionGuid001                  \
                "MnpSB.DestroyChild - Destroy Child for the second time."      \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_UNSUPPORTED"

EndScope _MNP_DESTROYCHILD_CONFORMANCE2_CASE1_

#
# End log ...
#
EndLog