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
CaseGuid        5784AC31-7CA8-4dff-BFEA-DFDAAB4A79E6
CaseName        DestroyChild.Conf1.Case1
CaseCategory    Udp4
CaseDescription {Test the DestroyChild Conformance of UDP4 - Invoke DestroyChild()\
                 with the parameter ChildHandle being invalid.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _UDP4_DESTROYCHILD_CONFORMANCE1_CASE1_


#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status

#
# Destroy un-existed child
#
Udp4ServiceBinding->DestroyChild "0, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Udp4DestroyChildConf1AssertionGuid001                 \
                "Udp4SB.DestroyChild - Conf - Destroy NULL Child "             \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# EndScope
#
EndScope _UDP4_DESTROYCHILD_CONFORMANCE1_CASE1_

#
# End log ...
#
EndLog
