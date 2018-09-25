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
CaseGuid        57042FD8-1F15-4cfa-9B4F-D7BF62C0734D
CaseName        DestroyChild.Conf1.Case1
CaseCategory    TCP
CaseDescription {Test the EFI_INVALID_PARAMETER Conformance of TCP4BSP.DestroyChild.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _TCP4_SPEC_CONFORMANCE_

BeginLogPacket DestroyChild.Conf1.Case1 "host $DEF_EUT_IP_ADDR and host         \
                                             $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle1
 
Tcp4ServiceBinding->DestroyChild "@R_Handle1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Tcp4DestroyChildConf1AssertionGuid001                 \
                "Tcp4SBP.DestroyChild - DestroyChild Child 1."                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"
 
EndLogPacket
#
# EndScope
#
EndScope  _TCP4_SPEC_CONFORMANCE_

#
# End log
#
EndLog
