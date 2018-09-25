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

#
# test case Name, category, description, GUID...
#
CaseGuid          4CB23BD8-2997-414c-A033-644E81FDC0AA
CaseName          Receive.Conf1.Case1
CaseCategory      TCP6
CaseDescription   {This case is to test the conformance - EFI_NOT_STARTED.     \
                  -- Receive must not succeed when the instance has not been configured.}
################################################################################

Include Tcp6/include/Tcp6.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _TCP6_RECEIVE_CONF1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Context

EFI_TCP6_IO_TOKEN                R_Receive_IOToken
EFI_TCP6_COMPLETION_TOKEN        R_Receive_CompletionToken

set  L_FragmentLength            64
Packet                           R_Packet_Buffer
EFI_TCP6_RECEIVE_DATA            R_RxData
EFI_TCP6_FRAGMENT_DATA           R_FragmentTable
CHAR8                            R_FragmentBuffer($L_FragmentLength)

#
# Create Child for TCP6 protocol
#
Tcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp6SBP.CreateChild - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
               
#
# Check Point: Call Tcp6.Receive() to receive a packet,
#              with the instance not configured.
#
SetVar R_RxData.UrgentFlag                FALSE                   
SetVar R_RxData.DataLength                $L_FragmentLength
SetVar R_RxData.FragmentCount             1

SetVar R_FragmentTable.FragmentLength     $L_FragmentLength
SetVar R_FragmentTable.FragmentBuffer     &@R_FragmentBuffer
SetVar R_RxData.FragmentTable(0)          @R_FragmentTable

SetVar R_Packet_Buffer.RxData             &@R_RxData

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Receive_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Receive_IOToken.CompletionToken  @R_Receive_CompletionToken
SetVar R_Receive_IOToken.Packet_Buffer    @R_Packet_Buffer

Tcp6->Receive {&@R_Receive_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Tcp6ReceiveConf1AssertionGuid001                     \
                "Tcp6.Receive - Call Receive() with the instance not configured."     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

BS->CloseEvent {@R_Receive_CompletionToken.Event, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.DestroyEvent. "                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Destroy Child
#
Tcp6ServiceBinding->DestroyChild "@R_Handle,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp6SBP.DestroyChild - Destroy Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# EndScope
#
EndScope  _TCP6_RECEIVE_CONF1_CASE1_

#
# End log
#
EndLog
