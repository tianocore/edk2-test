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
CaseGuid        2870CBE4-9ECD-438e-89B3-7CA3A7F4948F
CaseName        CreateChild.Conf1.Case1
CaseCategory    TCP6
CaseDescription {Test the CreateChild Conformance of TCP6 - Invoke CreateChild()\
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
BeginScope  _TCP6SB_CREATECHILD_CONF1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status

#
#The pointer is NULL, return EFI_INVALID_PARAMETER
#
Tcp6ServiceBinding->CreateChild "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]

RecordAssertion $assert $Tcp6CreateChildConf1AssertionGuid001                  \
                "Tcp6SBP.CreateChild - Create NULL ChildHandle, returns        \
                 EFI_INVALID_PARAMETER."                                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"
 
#
# EndScope
#
EndScope   _TCP6SB_CREATECHILD_CONF1_CASE1_

#
# End log
#
EndLog
