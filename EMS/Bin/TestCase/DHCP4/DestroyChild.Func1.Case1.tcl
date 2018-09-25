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
CaseGuid        4F8B7586-B43F-4339-849D-5315D95167FC
CaseName        DestroyChild.Func1.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Function of Dhcp4ServiceBinding.DestroyChild.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_DESTROYCHILD_FUNC1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle1
UINTN                            R_Handle2
UINTN                            R_Handle3

#
# Call [DHCP4SBP] -> CreateChild to create child.
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle1, &@R_Status}
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Dhcp4ServiceBinding->CreateChild {&@R_Handle2, &@R_Status}
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 2"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Dhcp4ServiceBinding->CreateChild {&@R_Handle3, &@R_Status}
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle3
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 3"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                
#
# Call Dhcp4ServiceBinding->DestroyChild to Destroy Child.
#
Dhcp4ServiceBinding->DestroyChild "@R_Handle1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.DestroyChild - Destroy Child 1."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Dhcp4ServiceBinding->DestroyChild "@R_Handle2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.DestroyChild - Destroy Child 2."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Dhcp4ServiceBinding->DestroyChild "@R_Handle3, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4DestroyChildFunc1AssertionGuid001                \
                "Dhcp4.DestroyChild - Destroy Child 3."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                
EndScope    _DHCP4_DESTROYCHILD_FUNC1
#
# End Log 
#
EndLog