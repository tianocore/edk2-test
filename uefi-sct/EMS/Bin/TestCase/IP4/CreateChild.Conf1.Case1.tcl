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
CaseGuid        3B3DAB94-FCC2-45ac-A9E0-7A6D8CD8B68A
CaseName        CreateChild.Conf1.Case1
CaseCategory    IP4
CaseDescription {Test the CreateChild Conformance of IP4 - Invoke CreateChild()\
                 with the parameter ChildHandle being NULL,the return status   \
                 should be EFI_INVALID_PARAMETER.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_CREATECHILD_CONFORMANCE1_CASE1_

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

Ip4ServiceBinding->CreateChild "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4CreateChildConf1AssertionGuid001                   \
                "Ip4SBP.CreateChild - Conf - With NULL child handle"           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"


Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

VifDown 0

#
# EndScope
#
EndScope _IP4_CREATECHILD_CONFORMANCE1_CASE1_

#
# End Log
#
EndLog
