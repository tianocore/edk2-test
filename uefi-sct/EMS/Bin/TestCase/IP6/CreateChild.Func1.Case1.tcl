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
CaseGuid        1E74CD15-C273-4b77-9096-58A7570B0EAD
CaseName        CreateChild.Func1.Case1
CaseCategory    IP6
CaseDescription {Test the CreateChild and Destroy Function of IP6 - Invoke CreateChild() \
                 to create two children and invoke DestroyChild() to destroy them.}
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin Log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope _IP6_CREATECHILD_FUNCTION1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle1
UINTN                            R_Handle2

#
# Check point: Call CreateChild to create child1.
#              EFI_SUCCESS should be returned.
#
Ip6ServiceBinding->CreateChild "&@R_Handle1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6CreateChildFunc1AssertionGuid001        \
                "Ip6SB.CreateChild - Func - Create Child 1"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar [subst $ENTS_CUR_CHILD]          @R_Handle1

#
# Check point: Call CreateChild to create child2.
#              EFI_SUCCESS should be returned.
#
Ip6ServiceBinding->CreateChild "&@R_Handle2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6CreateChildFunc1AssertionGuid002        \
                "Ip6SB.CreateChild - Func - Create Child 1"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar [subst $ENTS_CUR_CHILD]          @R_Handle2

#
# Check point: Call DestroyChild to destroy child2.
#              EFI_SUCCESS should be returned.
#
Ip6ServiceBinding->DestroyChild "@R_Handle2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6DestroyChildFunc1AssertionGuid001        \
                "Ip6SB.DestroyChild - Func - DestroyChild 1"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Call DestroyChild to create child1.
#              EFI_SUCCESS should be returned.
#
Ip6ServiceBinding->DestroyChild "@R_Handle1 &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6DestroyChildFunc1AssertionGuid002        \
                "Ip6SB.DestroyChild - Func - Detroy Child 1"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# End Scope
#
EndScope _IP6_CREATECHILD_FUNCTION1_CASE1_
#
#End Log
#
EndLog

