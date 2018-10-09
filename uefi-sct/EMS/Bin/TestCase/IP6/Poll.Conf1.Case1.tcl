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
# Test Case Name, Category, Description, GUID ...
#
CaseGuid           2B3B2533-9265-447d-A7D5-6CAF586E046A
CaseName           Poll.Conf1.Case1
CaseCategory       IP6
CaseDescription    { Test the Poll Function of IP6 - invoke Poll()                               \
                     when the instance has not been configured.EFI_NOT_STARTED should be returned.\			 
                   }
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin  log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope         IP6_POLL_CONF1_CASE1_

# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                       R_Status
UINTN                       R_Handle 

#
# Create Child
#
Ip6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert       [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion  $assert $GenericAssertionGuid               \
                 "Ip6SB->CreateChild - Conf - Create Child "             \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]    @R_Handle

#
# Check point:Call poll Function when the instance has not been configured.
#             EFI_NOT_STARTED should be returned.
#    
Ip6->Poll    "&@R_Status"
GetAck
set  assert        [VerifyReturnStatus R_Status  $EFI_NOT_STARTED]
RecordAssertion    $assert       $Ip6PollConf1AssertionGuid001                \
                   "Ip6->Poll -Conf- Call Poll  Function with the instance has not been configured "  \
                   "ReturnStatus -$R_Status, ExpectedStatus -$EFI_NOT_STARTED"
#
# Destroy Child
#
Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert        [VerifyReturnStatus  R_Status $EFI_SUCCESS]
RecordAssertion   $assert  $GenericAssertionGuid                 \
                  "Ip6SB->DestroyChild - Conf - Destroy Child"              \
                  "RetrunStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# End scope
#
EndScope          IP6_POLL_CONF1_CASE1_
#
# End log
#
EndLog
