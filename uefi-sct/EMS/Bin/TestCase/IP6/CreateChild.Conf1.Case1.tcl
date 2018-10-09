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
CaseGuid          FCF73A15-63A8-42c9-9A52-03F3A0D0C6E9
CaseName          CreateChild.Conf1.Case1
CaseCategory      IP6
CaseDescription   {Test the CreateChild Conformance of IP6 - Invoke CreateChild()      \
	               with ChildHandle being NULL. EFI_INVALID_PARAMETER should be returned.}
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin log...
#
BeginLog
#
# BeginScope
#
BeginScope        _IP6_CREATECHILD_CONFORMANCE1_CASE1_

#
# Parameter definition
# R_ represents "Remote EFI Side Parameter"
# L- represents "Local OS Side Parameter"
#
UINTN                        R_Status
#
# Check point:Call CreateChild Function when the child handle is NULL,EFI_INVALID_PARAMETER should be returned.
#
Ip6ServiceBinding->CreateChild "NULL, &@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip6CreateChildConf1AssertionGuid001                   \
                "Ip6SBP.CreateChild-Conf-With NULL child handle"                \
				"ReturnStatus-$R_Status, ExpectedStatus-$EFI_INVALID_PARAMETER"
				
#
# EndScope
#
EndScope        _IP6_CREATECHILD_CONFORMANCE1_CASE1_
#
# End Log
#
EndLog

