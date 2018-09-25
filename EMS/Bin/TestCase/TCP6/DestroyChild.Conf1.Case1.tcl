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
CaseGuid        3AF82D61-8E16-4cc0-BF90-4F63CBB38FEE
CaseName       DestroyChild.Conf1.Case1
CaseCategory    TCP6
CaseDescription {Test the DestroyChild Conformance of TCP6 - Invoke DestroyChild()\
                 with the ChildHandle being NULL.}
################################################################################

Include TCP6/include/Tcp6.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _TCP6SB_DESTROYCHILD_CONF1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents  "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle1

SetVar R_Handle1 0
Tcp6ServiceBinding->DestroyChild "@R_Handle1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Tcp6DestroyChildConf1AssertionGuid001                 \
                "Tcp6SBP.DestroyChild - DestroyChild with NULL handle, returns EFI_INVALID_PARAMETER."                \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# EndScope
#
EndScope  _TCP6SB_DESTROYCHILD_CONF1_CASE1_

#
# End log
#
EndLog
