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
CaseGuid        B82D2D26-23E8-49c5-9958-200354B587C5
CaseName        DestroyChild.Func1.Case1
CaseCategory    Udp4
CaseDescription {Test the CreateChild Function of UDP4 - Invoke DestroyChild() \
                 to destroy a child.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _UDP4_DESTROYCHILD_FUNCTION1_CASE1_

UINTN                            R_Status
UINTN                            R_Handle

#
# Create Child R_Handle
#
Udp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.DestroyChild - Func - Create Child"                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Destroy Child R_Handle
#
Udp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4DestroyChildFunc1AssertionGuid001                 \
                "Udp4SB.DestroyChild - Func - Destroy Child"                   \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"

#
# End scope
#
EndScope _UDP4_DESTROYCHILD_FUNCTION1_CASE1_

#
# End log ...
#
EndLog
