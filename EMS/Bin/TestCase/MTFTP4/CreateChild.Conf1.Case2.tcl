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
CaseGuid        0040C121-4104-48cf-99B6-B61C9207B00A
CaseName        CreateChild.Conf1.Case2
CaseCategory    MTFTP4
CaseDescription {This case is to test the EFI_INVALID_PARAMETER Conformance of \
	               Mtftp4SB.CreateChild with ChildHandle being NULL.}
################################################################################

#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl

BeginScope _MTFTP4_CREATECHILD_CONFORMANCE1_CASE2_

UINTN                            R_Status

#
# check point
#
Mtftp4ServiceBinding->CreateChild {NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Mtftp4CreateChildConfAssertionGuid002                 \
                "Mtftp4SBP.CreateChild - returns EFI_INVALID_PARAMETER with    \
                 NULL ChildHandle."                                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

EndScope _MTFTP4_CREATECHILD_CONFORMANCE1_CASE2_

#
# End Log
#
EndLog