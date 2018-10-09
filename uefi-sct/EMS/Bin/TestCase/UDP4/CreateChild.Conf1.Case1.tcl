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
CaseGuid        C06078BC-57BA-455c-8B81-D76CCD07DEB2
CaseName        CreateChild.Conf1.Case1
CaseCategory    Udp4
CaseDescription {Test the CreateChild Conformance of UDP4 - Invoke CreateChild()\
                 with the ChildHandle being NULL.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _UDP4_CREATECHILD_CONFORMANCE1_CASE1_


#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status

#
#The pointer is NULL, return EFI_INVALID_PARAMETER
#
Udp4ServiceBinding->CreateChild "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Udp4CreateChildConf1AssertionGuid001                  \
                "Udp4SB.CreateChild - Conf - Create Child"                     \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_INVALID_PARAMETER"
                

#
# EndScope
#
EndScope  _UDP4_CREATECHILD_CONFORMANCE1_CASE1_

#
# End log
#
EndLog
