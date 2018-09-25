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
CaseGuid        8EE06845-5F66-4ce4-9CC8-ADEA2F6E080F
CaseName        CreateChild.Conf1.Case1
CaseCategory    DHCP6
CaseDescription {Test the CreateChild Conformance of DHCP6 - Invoke CreateChild() \
                 with ChildHandle being NULL. EFI_INVALID_PARAMETER should be returned.}
################################################################################

Include DHCP6/include/Dhcp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope  _DHCP6_CREATECHILD_CONF1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN    R_Status

#
# Check Point: The pointer is NULL. EFI_INVALID_PARAMETER should be returned
#
Dhcp6ServiceBinding->CreateChild "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp6CreateChildConf1AssertionGuid001     \
                "Dhcp6SB.CreateChild - Conf - ChildHandle=NULL."             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# EndScope
#
EndScope    _DHCP6_CREATECHILD_CONF1
#
# End Log 
#
EndLog