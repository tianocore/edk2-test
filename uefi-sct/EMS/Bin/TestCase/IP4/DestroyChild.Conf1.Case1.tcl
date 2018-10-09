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
CaseGuid        9FEC35FD-784A-4cc4-A6D0-F8D35C08BCD2
CaseName        DestroyChild.Conf1.Case1
CaseCategory    IP4
CaseDescription {Test the DestroyChild Conformance of IP4 - Invoke DestroyChild()\
                 when the ChildHandle does not support the protocol that is    \
                 being removed.The return status should be EFI_UNSUPPORTED.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_DESTROYCHILD_CONFORMANCE1_CASE1_

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

VifUp 0 172.16.210.162 255.255.255.0

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck

Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.DestroyChild - Conf - DestroyChild the first time"     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_UNSUPPORTED]
RecordAssertion $assert $Ip4DestroyChildConf1AssertionGuid001                  \
                "Ip4SBP.DestroyChild - Conf - DestroyChild the second time"    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_UNSUPPORTED"
                
VifDown 0

#
# EndScope
#
EndScope _IP4_DESTROYCHILD_CONFORMANCE1_CASE1_

#
# End Log
#
EndLog
