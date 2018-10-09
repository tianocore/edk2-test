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
CaseLevel          CONFORMANCE
CaseAttribute      AUTO
CaseVerboseLevel   DEFAULT
set reportfile     report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid           3A98DED7-536C-4ec8-82D7-5A529B2B5F86
CaseName           Groups.Conf1.Case1
CaseCategory       IP6
CaseDescription    {Test the Groups Function of IP6 - invoke Groups() \
                    when the instance has not been configured         \
                    EFI_NOT_STARTED should be returned.
                   }
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# Begin Scope ...
#

BeginScope           IP6_GROUPS_CONF1_CASE1_

# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                 R_Status
UINTN                 R_Handle

#
# Create child
#
Ip6ServiceBinding->CreateChild "&@R_Handle,  &@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                    \
                "Ip6SB->CreatChild - Creat Child 1"                        \
                "ReturnStatus -$R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar  [subst $ENTS_CUR_CHILD]      @R_Handle

EFI_IPv6_ADDRESS      R_GroupAddress
SetIpv6Address        R_GroupAddress      "ff00::8"

#
# Check point:Call Groups Function when the instance has not been configured.EFI_NOT_STARTED should be returned.
#
Ip6->Groups     "TRUE, &@R_GroupAddress, &@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Ip6GroupsConf1AssertionGuid001            \
                "Ip6->Group - Conf - Not Started"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

#
# Destroy Child
#
Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Ip6->DestroyChild -Conf - Destroy Child 1 "                     \
                "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

#
# End Scope
#
EndScope        IP6_GROUPS_CONF1_CASE1_
#
#End log
#
EndLog
