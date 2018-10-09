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
CaseGuid        7EDBE5B2-BECA-4ea6-9A37-A01AF0A66A37
CaseName        CreateChild.Conf1.Case1
CaseCategory    TCP
CaseDescription {Test the CreateChild Conformance of TCP4 - Invoke CreateChild()\
                 with the ChildHandle being NULL.}
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

BeginLogPacket CreateChild.Conf1.Case1 "host $DEF_EUT_IP_ADDR and host            \
                                             $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status

#
#The pointer is NULL, return EFI_INVALID_PARAMETER
#
Tcp4ServiceBinding->CreateChild "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Tcp4CreateChildConf1AssertionGuid001                  \
                "Tcp4SBP.CreateChild - Create NULL ChildHandle, returns        \
                 EFI_INVALID_PARAMETER."                                       \
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
