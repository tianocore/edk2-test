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
CaseGuid        350BFB10-0D56-4f39-82BA-BC91D79BE0CA
CaseName        CreateDestroyChild.Func1.Case1
CaseCategory    TCP6
CaseDescription {Test the Function of CreateDestroyChild of TCP6 - CreateDestroyChild\
                 must succeed with valid parameters.}
################################################################################

Include TCP6/include/Tcp6.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _TCP6SB_CREATEDESTROYCHILD_FUNC1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Handle1
UINTN                            R_Handle2
UINTN                            R_Status1
UINTN                            R_Status2

#
#Check Point: Create Child with valid parameters
#
Tcp6ServiceBinding->CreateChild "&@R_Handle1, &@R_Status1"
GetAck
set assert [VerifyReturnStatus R_Status1 $EFI_SUCCESS]
RecordAssertion $assert $Tcp6CreateDestroyChildFunc1AssertionGuid001                  \
                "Tcp6SBP.CreateChild - Create ChildHandle, returns EFI_SUCCESS."                   \
                "ReturnStatus - $R_Status1, ExpectedStatus - $EFI_SUCCESS"

Tcp6ServiceBinding->CreateChild "&@R_Handle2, &@R_Status2"
GetAck
set assert [VerifyReturnStatus R_Status2 $EFI_SUCCESS]
RecordAssertion $assert $Tcp6CreateDestroyChildFunc1AssertionGuid002                  \
                "Tcp6SBP.CreateChild - Create ChildHandle, returns EFI_SUCCESS."                   \
                "ReturnStatus - $R_Status2, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Destroy Child with valid parameters
#
Tcp6ServiceBinding->DestroyChild "@R_Handle1, &@R_Status1"
GetAck
set assert [VerifyReturnStatus R_Status1 $EFI_SUCCESS]
RecordAssertion $assert $Tcp6CreateDestroyChildFunc1AssertionGuid003                  \
                "Tcp6SBP.DestroyChild - Destroy ChildHandle, returns EFI_SUCCESS."                   \
                "ReturnStatus - $R_Status1, ExpectedStatus - $EFI_SUCCESS"

Tcp6ServiceBinding->DestroyChild "@R_Handle2, &@R_Status2"
GetAck
set assert [VerifyReturnStatus R_Status2 $EFI_SUCCESS]
RecordAssertion $assert $Tcp6CreateDestroyChildFunc1AssertionGuid004                  \
                "Tcp6SBP.DestroyChild - Destroy ChildHandle, returns EFI_SUCCESS."                   \
                "ReturnStatus - $R_Status2, ExpectedStatus - $EFI_SUCCESS"
 
#
# EndScope
#
EndScope   _TCP6SB_CREATEDESTROYCHILD_FUNC1_CASE1_

#
# End log
#
EndLog
