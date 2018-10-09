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
CaseGuid        BC4B304C-AC9E-4f6f-8645-D6FE0F2C35A4
CaseName        DestroyChild.Func1.Case1
CaseCategory    IP4
CaseDescription {Test the function of IP4SB.DestroyChild() - Create multi      \
	               children and destroy them.}
################################################################################
 
Include IP4/include/Ip4.inc.tcl

# 
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_DESTROYCHILD_FUNCTION1_CASE1_

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

VifUp 0 172.16.210.162 255.255.255.0

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle1
UINTN                            R_Handle2
UINTN                            R_Handle3


Ip4ServiceBinding->CreateChild "&@R_Handle1, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Routes - Conf - Create Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4ServiceBinding->CreateChild "&@R_Handle2, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Routes - Conf - Create Child 2"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4ServiceBinding->CreateChild "&@R_Handle3, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle3
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Routes - Conf - Create Child 3"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"                

Ip4ServiceBinding->DestroyChild {@R_Handle1, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Routes - Conf - Destroy Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


Ip4ServiceBinding->DestroyChild {@R_Handle2, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Routes - Conf - Destroy Child 2"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


Ip4ServiceBinding->DestroyChild {@R_Handle3, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip4DestroyChildFunc1AssertionGuid001                  \
                "Ip4SBP.Routes - Conf - Destroy Child 3"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                                
VifDown 0

#
# End scope
#
EndScope _IP4_DESTROYCHILD_FUNCTION1_CASE1_

#
# End Log
#
EndLog