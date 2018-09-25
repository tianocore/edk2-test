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
CaseGuid        98E6C54B-6EEE-4c36-80D6-C87B920AF4A8
CaseName        CreateDestroyChild.Func1.Case1
CaseCategory    UDP6

CaseDescription {Test the Create and Destroy Function of UdP6 - Invoke CreateChild() \
                 to create two Children then invoke DestroyChild to destroy them. \
                 EFI_SUCCESS should be returned.
                }
################################################################################

Include UdP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope  _UDP6_CREATEDESTROYCHILD_FUNC1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle1
UINTN                            R_Handle2

#
# Check point: Create child1.
#
Udp6ServiceBinding->CreateChild "&@R_Handle1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6CreateDestroyChildFunc1AssertionGuid001  \
                "Udp6SB.CreateChild - Create Child 1"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1

#
# Check point: Create child2.
#
Udp6ServiceBinding->CreateChild "&@R_Handle2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6CreateDestroyChildFunc1AssertionGuid001  \
                "Udp6SB.CreateChild - Create Child 2"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2

#
# Check point: Destroy child2.
#
Udp6ServiceBinding->DestroyChild "@R_Handle2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6CreateDestroyChildFunc1AssertionGuid002  \
                "Udp6SB.DestroyChild - Destroy Child 2"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Destroy child1.
#
Udp6ServiceBinding->DestroyChild "@R_Handle1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6CreateDestroyChildFunc1AssertionGuid002  \
                "Udp6SB.DestroyChild - Destroy Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# EndScope
#
EndScope    _UDP6_CREATEDESTROYCHILD_FUNC1_
#
# End Log 
#
EndLog