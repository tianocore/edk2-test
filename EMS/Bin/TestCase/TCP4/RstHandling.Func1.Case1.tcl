#
# The material contained herein is not a license, either      
# expressly or impliedly, to any intellectual property owned  
# or controlled by any of the authors or developers of this   
# material or to any contribution thereto. The material       
# contained herein is provided on an "AS IS" basis and, to the
# maximum extent permitted by applicable law, this information
# is provided AS IS AND WITH ALL FAULTS, and the authors and  
# developers of this material hereby disclaim all other       
# warranties and conditions, either express, implied or       
# statutory, including, but not limited to, any (if any)      
# implied warranties, duties or conditions of merchantability,
# of fitness for a particular purpose, of accuracy or         
# completeness of responses, of results, of workmanlike       
# effort, of lack of viruses and of lack of negligence, all   
# with regard to this material and any contribution thereto.  
# Designers must not rely on the absence or characteristics of
# any features or instructions marked "reserved" or           
# "undefined." The Unified EFI Forum, Inc. reserves any       
# features or instructions so marked for future definition and
# shall have no responsibility whatsoever for conflicts or    
# incompatibilities arising from future changes to them. ALSO,
# THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
# QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
# NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
# CONTRIBUTION THERETO.                                       
#                                                             
# IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
# ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
# THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
# PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
# CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
# UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
# WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
# DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
# THE POSSIBILITY OF SUCH DAMAGES.                            
#                                                             
# Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
#
#
################################################################################
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT

#
# test case Name, category, description, GUID...
#
CaseGuid          0CFACCBD-9273-43b1-915C-970B8F071FD3
CaseName          RstHandling.Func1.Case1
CaseCategory      TCP
CaseDescription   {This item is to test the <EUT> correctly send out the reset \
                   segment while in CLOSED state.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  DestroyTcb
  DestroyPacket
  DelEntryInArpCache

  Tcp4ServiceBinding->DestroyChild "@R_Tcp4Handle, &@R_Status"
  GetAck
 
}

proc CleanUpEutEnvironmentEnd {} {
  EndLogPacket
  EndScope _TCP4_RSTHANDLING_FUNC1_CASE1_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope on OS.
#
BeginScope _TCP4_RSTHANDLING_FUNC1_CASE1_

BeginLogPacket RstHandling.Func1.Case1 "host $DEF_EUT_IP_ADDR and host         \
                                             $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Tcp4Handle
UINTN                            R_Context

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData

EFI_TCP4_COMPLETION_TOKEN        R_Connect_CompletionToken
EFI_TCP4_CONNECTION_TOKEN        R_Connect_ConnectionToken

EFI_TCP4_COMPLETION_TOKEN        R_Close_CompletionToken
EFI_TCP4_CLOSE_TOKEN             R_Close_CloseToken
#
# In EFI1.1 2-8, Element of standard ANSI C enum type declaration. Type INTN
#
INTN                             R_Connection_State

LocalEther  $DEF_ENTS_MAC_ADDR
RemoteEther $DEF_EUT_MAC_ADDR
LocalIp     $DEF_ENTS_IP_ADDR
RemoteIp    $DEF_EUT_IP_ADDR

#
# Initialization of TCB related on OS side.
#
set L_Port $DEF_ENTS_PRT
set R_Port $DEF_EUT_PRT

CreateTcb TCB $DEF_ENTS_IP_ADDR $L_Port $DEF_EUT_IP_ADDR $R_Port
CreatePayload HelloWorld STRING 11 HelloWorld

#
# Add an entry in ARP cache.
#
AddEntryInArpCache

#
# Create Tcp4 Child.
#
Tcp4ServiceBinding->CreateChild "&@R_Tcp4Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Tcp4Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4SBP.CreateChild - Create Child 1."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure TCP instance.
#
SetVar R_Configure_AccessPoint.UseDefaultAddress      FALSE
SetIpv4Address R_Configure_AccessPoint.StationAddress $DEF_EUT_IP_ADDR
SetIpv4Address R_Configure_AccessPoint.SubnetMask     $DEF_EUT_MASK
SetVar R_Configure_AccessPoint.StationPort            $R_Port
SetIpv4Address R_Configure_AccessPoint.RemoteAddress  $DEF_ENTS_IP_ADDR
SetVar R_Configure_AccessPoint.RemotePort             $L_Port
SetVar R_Configure_AccessPoint.ActiveFlag             TRUE

SetVar R_Configure_Tcp4ConfigData.TypeOfService       0
SetVar R_Configure_Tcp4ConfigData.TimeToLive          128
SetVar R_Configure_Tcp4ConfigData.AccessPoint         @R_Configure_AccessPoint
SetVar R_Configure_Tcp4ConfigData.ControlOption       0

Tcp4->Configure {&@R_Configure_Tcp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Configure - Configure Child 1."                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Tcp4.Connect for an active TCP instance.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Connect_ConnectionToken.CompletionToken @R_Connect_CompletionToken

Tcp4->Connect {&@R_Connect_ConnectionToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Connect - Open an active connection."                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Handles the three-way handshake.
#
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_syn} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ConnSetup: Expect: EUT O <SYN>, Result: No packet out."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

set L_TcpFlag [expr $SYN | $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag
SendTcpPacket TCB

ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_ack} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out ACK segment correctly."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}
RecordMessage DEFAULT "After 3-way handshake, Conn Setup"

#
# Call Close interface to do a graceful close working flow.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Close_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Close_CloseToken.CompletionToken @R_Close_CompletionToken
SetVar R_Close_CloseToken.AbortOnClose    FALSE

Tcp4->Close {&@R_Close_CloseToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp4RstHandlingFunc1AssertionGuid001                  \
                "Tcp4.Close - Close a connection."                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Hanlde the simultaneous close.
#

#
# Build FIN packet and send out
#
set L_TcpFlag [expr $FIN | $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag
SendTcpPacket TCB

#
# Receive SYN
#
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_fin} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "<SimuClose> Expect: EUT O <FIN>, Result: No FIN out."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "<SimuClose> Expect: EUT O <FIN>, Result: No packet out."

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

#
# Receive ACK
#
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_ack} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "<SimuClose> Expect: EUT O <ACK>, Result: No ACK out."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "<SimuClose> Expect: EUT O <ACK>, Result: No packet out."

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

#
# Send ACK for EUT
#
set L_TcpFlag [expr $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag
SendTcpPacket TCB
RecordMessage DEFAULT  "Simultaneously closed the connection"

# Wait enough time to let TIME_WAIT expired, 2 MSL, In RFC793, MSL is 2 minutes
RecordMessage DEFAULT  "Wait enough time to let TIME_WAIT expired, (4 minutes)"
after 240000

#Modify the l_isn & r_isn, let it be 0
#set TCB.l_isn  0
set TCB.r_isn  0

#
# Validate RST generation in <CLOSED> state
#
Tcp4->GetModeData {&@R_Connection_State, NULL, NULL, NULL, NULL, &@R_Status}
GetAck
GetVar R_Connection_State
if { $R_Status!=$EFI_SUCCESS || $R_Connection_State!=$Tcp4StateClosed } {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Active Connection, Enter LAST_WAIT"                         \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"    \
                  "CurState-$R_Connection_State,ExpectedState-Tcp4StateClosed"

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}
RecordMessage DEFAULT "Enter CLOSED state"
#
# 1. In <CLOSED> state, OS Send SYN, EUT Respond with RST
#
set L_TcpFlag $SYN
UpdateTcpSendBuffer TCB -c $L_TcpFlag
SendTcpPacket TCB
set L_ExpectedAck ${TCB.l_next_seq}
set L_ExpectedSeq ${TCB.l_isn}

#
# Receive RST from <EUT>
#
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_rst} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                            "<CLOSED>: Expect: <EUT> 0 RST when rcvd SYN,"     \
                            "Result: No RST out"

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                          "<CLOSED>: Expect: <EUT> 0 RST when rcvd SYN,"       \
                          "Result: No packet out"

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

#
# Verify RST.seqid == 0, RST.ackid == next send sequence
#
RecordMessage DEFAULT "TCB.r_seq=${TCB.r_seq}, TCB.r_ack=${TCB.r_ack}"         \
                      "TCB.l_isn=${TCB.l_isn}, TCB.r_isn=${TCB.r_isn}"
 
if { ${TCB.r_seq} != 0 || ${TCB.r_ack}!=$L_ExpectedAck } {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "<CLOSED>: Expect: <EUT> 0 RST when rcvd SYN, "              \
                  "RST.seq=[expr 0-$L_ExpectedSeq], RST.ack=${L_ExpectedAck} " \
                  "Result: RST.seq=${TCB.r_seq}, RST.ack=${TCB.r_ack}"

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

set assert pass
RecordAssertion $assert $GenericAssertionGuid                                  \
                        "<CLOSED>: Expect: <EUT> 0 RST when rcvd SYN, "        \
                        "RST.seq=0, RST.ack=${TCB.r_next_seq} "                \
                        "Result: RST.seq=${TCB.r_seq}, RST.ack=${TCB.r_ack}"

#
# 2. In <CLOSED> state, OS Send FIN, EUT Respond with RST
#    BugBug - In Fake driver, the rcvd RST.ack equals to RST.seq
#             instead of FIN.seq+datalen
#
set L_TcpFlag [expr $FIN | $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag
SendTcpPacket TCB
set L_ExpectedAck ${TCB.l_next_seq}
set L_ExpectedSeq ${TCB.l_acked_seq}

#
# Verify <EUT> send out RST
#
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_rst} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                            "<CLOSED>: Expect: <EUT> 0 RST when rcvd FIN,"     \
                            "Result: No RST out"

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                          "<CLOSED>: Expect: <EUT> 0 RST when rcvd FIN,"       \
                          "Result: No packet out"

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

#
# Verify RST.seqid == ACK# in FIN|ACK, RST.ackid == next send sequence
#
#if { ${TCB.r_seq} != 0 || ${TCB.r_ack}!=$L_ExpectedAck } {
if { ${TCB.r_seq} != 0 } {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                          "<CLOSED>: Expect: <EUT> 0 RST when rcvd FIN, "      \
                          "RST.seq=$L_ExpectedSeq, RST.ack=$L_ExpectedAck "    \
                          "Result: RST.seq=${TCB.r_seq}, RST.ack=${TCB.r_ack}"

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

set assert pass
RecordAssertion $assert $GenericAssertionGuid                                  \
                        "<CLOSED>: Expect: <EUT> 0 RST when rcvd FIN, "        \
                        "RST.seq==$L_ExpectedSeq, RST.ack==$L_ExpectedAck "    \
                        "Result: RST.seq=${TCB.r_seq}, RST.ack=${TCB.r_ack}"

#
# 3. In <CLOSED> state, OS Send URG|ACK, EUT Respond with RST
#    BugBug - In Fake driver, the rcvd RST.ack equals to RST.seq
#             instead of Data.seq+datalen
#
set L_TcpFlag [expr $URG | $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag -p HelloWorld
SendTcpPacket TCB
set L_ExpectedAck ${TCB.l_next_seq}
set L_ExpectedSeq ${TCB.l_acked_seq}

#
# Verify <EUT> send out RST
#
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_rst} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                            "<CLOSED>: Expect: <EUT> 0 RST when rcvd URG|ACK," \
                            "Result: No RST out"

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                          "<CLOSED>: Expect: <EUT> 0 RST when rcvd URG|ACK,"   \
                          "Result: No packet out"

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

#
# Verify RST.seqid == 0, RST.ackid == next send sequence
#
#if { ${TCB.r_seq} != 0 || ${TCB.r_ack}!=$L_ExpectedAck } {
if { ${TCB.r_seq} != 0 } {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                          "<CLOSED>: Expect: <EUT> 0 RST when rcvd URG|ACK, "  \
                          "RST.seq==$L_ExpectedSeq, RST.ack==$L_ExpectedAck "  \
                          "Result: RST.seq=${TCB.r_seq}, RST.ack=${TCB.r_ack}"

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

set assert pass
RecordAssertion $assert $GenericAssertionGuid                                  \
                        "<CLOSED>: Expect: <EUT> 0 RST when rcvd URG|ACK, "    \
                        "RST.seq==$L_ExpectedSeq, RST.ack==$L_ExpectedAck "    \
                        "Result: RST.seq=${TCB.r_seq}, RST.ack=${TCB.r_ack}"

#
# 4. In <CLOSED> state, OS Send RST|ACK, EUT Respond with Nothing
#
set L_TcpFlag [expr $RST | $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag
SendTcpPacket TCB

#
# Receive RST from <EUT>
#
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "<CLOSED>: Expect: <EUT> discard silent when rcvd RST"     \
                    "Result: EUT send out packet"

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
}

set assert pass
RecordAssertion $assert $GenericAssertionGuid                                  \
                "<CLOSED>: Expect: <EUT> discard silent when rcvd RST"

#
# Clean up the environment on EUT side.
#

CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
