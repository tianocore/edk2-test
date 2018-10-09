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
CaseGuid        3A377E18-7D09-4180-8017-51EB49668F9E
CaseName        DestroyChild.Conf2.Case1
CaseCategory    Udp4
CaseDescription {Test the EFI_UNSUPPORTED Conformance of UDP4.DestroyChild -   \
                 Invoke DestroyChild() to destroy an existed child twice.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _UDP4_DESTROYCHILD_CONFORMANCE2_CASE1_

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
# Destroy Child R_Handle for the first time.
#
Udp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.DestroyChild - Func - Destroy Child"                   \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"

#
# Destroy Child R_Handle for the second time.
#
Udp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_UNSUPPORTED]
RecordAssertion $assert $Udp4DestroyChildConf2AssertionGuid001                 \
                "Udp4SB.DestroyChild - Func - Destroy Child"                   \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_UNSUPPORTED"
                
#
# End scope
#
EndScope _UDP4_DESTROYCHILD_CONFORMANCE2_CASE1_

#
# End log ...
#
EndLog
