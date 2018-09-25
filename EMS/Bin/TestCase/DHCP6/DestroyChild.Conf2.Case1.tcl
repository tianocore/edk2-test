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
CaseGuid        71B9A526-23AA-404f-8B28-A53CB80AD305
CaseName        DestroyChild.Conf2.Case1
CaseCategory    DHCP6
CaseDescription {Test the DestroyChild Conformance of DHCP6 - Invoke DestroyChild() \
                 with an unknown ChildHandle. EFI_UNSUPPORTED should be returned.}
################################################################################

Include DHCP6/include/Dhcp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope _DHCP6_DESTROYCHILD_CONF2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Create child.
#
Dhcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Dhcp6SB.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Check point: Destroy the Child just created. EFI_SUCCESS should be returned.
#
Dhcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Dhcp6SB.DestroyChild - Destroy ChildHandle 1."               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Destroy Child again. EFI_UNSUPPORTED should be returned.
#
Dhcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_UNSUPPORTED]
RecordAssertion $assert $Dhcp6DestroyChildConf2AssertionGuid001     \
                "Dhcp6SB.DestroyChild - Destroy ChildHandle 1 for the second time." \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_UNSUPPORTED"

#
# EndScope
#
EndScope    _DHCP6_DESTROYCHILD_CONF2
#
# End Log 
#
EndLog