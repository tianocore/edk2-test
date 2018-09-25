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
CaseGuid        E840B007-A8F9-46d2-9197-25EA90ABC923
CaseName        DestroyChild.Conf2.Case1
CaseCategory    MTFTP4
CaseDescription {This case is to test the EFI_UNSUPPORTED Conformance of       \
	              Mtftp4SB.DestroyChild - destroy the same child for twice.}
################################################################################

#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl
BeginScope _MTFTP4_DESTROYCHILD_CONFORMANCE1_CASE2_

UINTN                            R_Status
UINTN                            R_Handle

#
# check point
#
Mtftp4ServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.CreateChild - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Mtftp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.DestroyChild - Destroy Child"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Mtftp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_UNSUPPORTED]
RecordAssertion $assert $Mtftp4DestroyChildConfAssertionGuid003                \
                "Mtftp4SBP.DestroyChild - returns EFI_UNSUPPORTED for          \
                 Destroying Child twice"                                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_UNSUPPORTED"

EndScope _MTFTP4_DESTROYCHILD_CONFORMANCE1_CASE2_

#
# End log ...
#
EndLog
