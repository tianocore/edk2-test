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
CaseGuid        3969E3B3-C834-4a52-813A-FED3B913248B
CaseName        DestroyChild.Conf1.Case1
CaseCategory    MNP
CaseDescription {Test the DestroyChild conformance of MNPSB - Call             \
	               MnpServiceBinding.DestroyChild() when the parameter           \
	               ChildHandle being NULL. The return status should be           \
	               EFI_INVALID_PARAMETER.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope _MNP_DESTROYCHILD_CONFORMANCE1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status

#
# Destroy un-existed child
#
MnpServiceBinding->DestroyChild "0, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $MnpDestroyChildConf1AssertionGuid001                  \
                "MnpSB.CreateChild - Destroy NULL Child "                      \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_INVALID_PARAMETER"
                
                
EndScope _MNP_DESTROYCHILD_CONFORMANCE1_CASE1_

#
# End log ...
#
EndLog
