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
CaseGuid        E3B9F006-ECDD-4753-AC89-EFBDA1B67AA7
CaseName        DestroyChild.Conf1.Case1
CaseCategory    Udp6
CaseDescription {Test the DestroyChild Conformance of UDP6 - Invoke DestroyChild() with\
                 the ChildHandle being NULL.EFI_INVALID_PARAMETER should be returned.}
################################################################################

Include UDP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog

#
# Begin Scope
#
BeginScope  _UDP6_DESTROYCHILD_CONFORMANCE1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status

#
# Check Point: The pointer is NULL, return EFI_INVALID_PARAMETER
#
Udp6ServiceBinding->DestroyChild "0, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Udp6DestroyChildConf1AssertionGuid001          \
                "Udp6SB.DestroyChild - Conf - Destroy a created Child"                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"
                
#
# EndScope
#
EndScope  _UDP6_DESTROYCHILD_CONFORMANCE1_CASE1_

#
# End log
#
EndLog
