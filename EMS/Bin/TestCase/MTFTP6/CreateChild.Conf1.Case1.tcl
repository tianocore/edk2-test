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
CaseGuid        611CE2D1-DCBF-40c4-A680-4B3EF3ADA233
CaseName        CreateChild.Conf1.Case1
CaseCategory    MTFTP6
CaseDescription {This case is to test the CreateChild Conformance of       \
                 Mtftp6-Invoke CreateChild function with ChildHandle NULL   \
                 EFI_INVALID_PARAMETER should be returned.}
################################################################################

Include MTFTP6/include/Mtftp6.inc.tcl

#
# Begin log ...
#
BeginLog

BeginScope _MTFTP6_CREATECHILD_CONFORMANCE1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status

#
# Check Point: Call Mtftp6 ServiceBinding when ChildHandle is NULL,\
#              EFI_INVALID_PARAMETER should be returned.
#
Mtftp6ServiceBinding->CreateChild "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Mtftp6CreateChildConf1AssertionGuid001      \
                "Mtftp6SB.CreateChild - Conf - Create a Child"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# End log
#
EndLog

EndScope _MTFTP6_CREATECHILD_CONFORMANCE1_CASE1_

#
# End Log
#
EndLog
