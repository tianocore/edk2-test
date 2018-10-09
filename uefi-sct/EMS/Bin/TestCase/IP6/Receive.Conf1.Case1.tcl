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
CaseGuid           44B1A976-727B-4452-8EB1-82191EF1DFF5
CaseName           Receive.Conf1.Case1
CaseCategory       IP6
CaseDescription    { Test the Receive Function of IP6 - invoke Receive()  \
                     when the instance has not been configured              \
                     EFI_NOT_STARTED should be returned.
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
BeginScope          IP6_RECEIVE_CONF1_CASE1_

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
SetVar  [subst $ENTS_CUR_CHILD]    @R_Handle

EFI_IP6_COMPLETION_TOKEN                            R_Token
UINTN                                               R_NotifyContext
SetVar           R_NotifyContext                    0

#
# Create an Event
#
BS->CreateEvent   "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_NotifyContext, &@R_Token.Event, &@R_Status"
GetAck
set assert        [VerifyReturnStatus  R_Status   $EFI_SUCCESS]
RecordAssertion   $assert           $GenericAssertionGuid       \
                  "SB->CreateEvent -Conf- Create an Event "               \
                  "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

#
# Check point:Call Receive Function when the instance has not been configured.\
#              EFI_NOT_STARTED should be returned.
#    
Ip6->Receive       "&@R_Token, &@R_Status"
GetAck
set  assert        [VerifyReturnStatus R_Status  $EFI_NOT_STARTED]
RecordAssertion    $assert       $Ip6ReceiveConf1AssertionGuid001            \
                   "Ip6->Receive -Conf- Call Receive Function with the instance not configured "  \
                   "ReturnStatus -$R_Status, ExpectedStatus -$EFI_NOT_STARTED"

#
# Destroy Child
#
Ip6ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert        [VerifyReturnStatus  R_Status $EFI_SUCCESS]
RecordAssertion   $assert  $GenericAssertionGuid                 \
                  "Ip6SB->DestroyChild - Conf - Destroy Child"              \
                  "RetrunStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Close Event
#
BS->CloseEvent    "@R_Token.Event, &@R_Status"
GetAck
set assert        [VerifyReturnStatus  R_Status $EFI_SUCCESS]
RecordAssertion   $assert       $GenericAssertionGuid         \
                  "BS->CloseEvent -Conf- Close the Event "              \
                  "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

#
#End scope
#
EndScope          IP6_RECEIVE_CONF1_CASE1_
#
#End log
#
EndLog
