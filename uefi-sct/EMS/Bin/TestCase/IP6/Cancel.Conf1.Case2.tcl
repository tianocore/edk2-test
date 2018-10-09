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
CaseGuid           4C21272C-02B3-48e8-A771-503A4B7301DB
CaseName           Cancel.Conf1.Case2
CaseCategory       IP6
CaseDescription    { Test the Cancel Function of IP6 - invoke Cancel()                            \
                     when the instance has not been configured.EFI_NOT_STARTED should be returned. \
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
BeginScope     IP6_CANCEL_CONF1_CASE2_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                                   R_Status
UINTN                                   R_Handle 

#
# Create a Child
#
Ip6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion  $assert $GenericAssertionGuid               \
                 "Ip6SB->CreateChild - Conf - Create Child "             \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]   @R_Handle
 
EFI_IP6_COMPLETION_TOKEN                            R_Token
UINTN            R_NotifyContext                     
SetVar           R_NotifyContext                    0

#
# Create an Event
#
BS->CreateEvent  "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_NotifyContext, &@R_Token.Event, &@R_Status"
GetAck
set assert       [VerifyReturnStatus  R_Status  $EFI_SUCCESS]
RecordAssertion  $assert      $GenericAssertionGuid            \
                 "BS->CreateEvent -Conf- Create an Event  "              \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

SetVar           R_Token.Status               "$EFI_SUCCESS"
EFI_IP6_TRANSMIT_DATA                         R_TxData
SetIpv6Address   R_TxData.DestinationAddress  "2002::2"
SetVar           R_TxData.OverrideData        0
SetVar           R_TxData.ExtHdrsLength       0
SetVar           R_TxData.ExtHdrs             0
SetVar           R_TxData.DataLength          60
SetVar           R_TxData.FragmentCount       1

EFI_IP6_FRAGMENT_DATA                         R_FragmentTable
SetVar  R_FragmentTable.FragmentLength        60
CHAR8   R_FragmentBuffer(1600)
SetVar  R_FragmentBuffer                      "Ip6TransmitTest !"
SetVar  R_FragmentTable.FragmentBuffer        &@R_FragmentBuffer
SetVar  R_TxData.FragmentTable                @R_FragmentTable
SetVar  R_Token.Packet                        &@R_TxData

#
# Check point: Call Cancel when the instance has not been configured
#              EFI_NOT_STARTED should be returned.
#
Ip6->Cancel       "&@R_Token, &@R_Status"
GetAck
set  assert       [VerifyReturnStatus R_Status  $EFI_NOT_STARTED]
RecordAssertion   $assert       $Ip6CancelConf1AssertionGuid002                                      \
                  "Ip6->Cancel -Conf- Call Cancel Function with the instance has not been configured and Token is Transmit type"  \
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
# Close an Event
#
BS->CloseEvent   "@R_Token.Event, &@R_Status"
GetAck
set assert      [VerifyReturnStatus  R_Status  $EFI_SUCCESS]
RecordAssertion  $assert       $GenericAssertionGuid         \
                 "BS->CloseEvent -Conf- Close the Event "              \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

#
# End scope
#
EndScope        IP6_CANCEL_CONF1_CASE2_
#
# End log
#
EndLog
