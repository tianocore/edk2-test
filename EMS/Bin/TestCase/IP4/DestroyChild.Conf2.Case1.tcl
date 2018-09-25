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
CaseGuid        984BB5DE-B6CC-426c-AA54-A5FC2538871A
CaseName        DestroyChild.Conf2.Case1
CaseCategory    IP4
CaseDescription {Test the DestroyChild EFI_INVALID_PARAMETER Conformance of    \
                 IP4.SB - Destroy a NULL/un-existed child.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_DESTROYCHILD_CONFORMANCE2_CASE1_

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

Ip4ServiceBinding->DestroyChild {0, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4DestroyChildConf2AssertionGuid001                  \
                "Ip4SBP.DestroyChild - Conf - Destroy a NULL ChildHandle."     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"
                
                
Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4DestroyChildConf2AssertionGuid002                  \
                "Ip4SBP.DestroyChild - Conf - Destroy a un-existed ChildHandle."\
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"
                
VifDown 0

#
# EndScope
#
EndScope _IP4_DESTROYCHILD_CONFORMANCE2_CASE1_

#
# End Log
#
EndLog