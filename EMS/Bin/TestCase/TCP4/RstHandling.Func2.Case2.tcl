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
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT

#
# test case Name, category, description, GUID...
#
CaseGuid          28261FEA-4AB6-4ae7-897A-BAB63F56DBA3
CaseName          RstHandling.Func2.Case2
CaseCategory      TCP
CaseDescription   {This item is to test the <EUT> correctly handles the        \
                   reception of a RST segment in SYN_RCVD state                \
                   Previous state is LISTEN - It return to LISTEN state}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironment {} {
global RST

  UpdateTcpSendBuffer TCB -c $RST
  SendTcpPacket TCB

  DestroyTcb
  DestroyPacket
  DelEntryInArpCache

  Tcp4ServiceBinding->DestroyChild "@R_Tcp4Handle, &@R_Status"
  GetAck
 
  EndLogPacket
  EndScope _TCP4_RSTHANDLING_FUNC2_CASE2_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope on OS.
#
BeginScope _TCP4_RSTHANDLING_FUNC2_CASE2_

BeginLogPacket RstHandling.Func2.Case2 "host $DEF_EUT_IP_ADDR and host         \
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
SetVar R_Configure_AccessPoint.ActiveFlag             FALSE

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
# Instruct <OS> send a SYN segment, Expect Receive SYN|ACK
#
set L_TcpFlag $SYN
UpdateTcpSendBuffer TCB -c $L_TcpFlag
SendTcpPacket TCB

ReceiveTcpPacket TCB 5
if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_ack} != 1 || ${TCB.r_f_syn} != 1} {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out SYN|ACK segment correctly."
    CleanUpEutEnvironment
    return
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."
  CleanUpEutEnvironment
  return
}

RecordMessage DEFAULT "Enter SYN_RCVD state From LISTEN"

#
# Instruct <OS> send a valid RST segment
# It's sequence number is one-byte less than window boundary
#
set L_OrigSeq ${TCB.l_next_seq}
set L_TcpFlag $RST
UpdateTcpSendBuffer TCB -c $L_TcpFlag -s [expr $L_OrigSeq+${TCB.r_win}-1]
SendTcpPacket TCB

# Recover the next sequence number
set TCB.l_next_seq $L_OrigSeq

#
# Expect: On receiving a valid RST, the connection returned to LISTEN state
#
#BUGBUG - Call GetModeData will result in crash
Tcp4->GetModeData {&@R_Connection_State, NULL, NULL, NULL, NULL, &@R_Status}
GetAck
GetVar R_Connection_State
if { $R_Connection_State != $Tcp4StateListen || $R_Status != $EFI_SUCCESS} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "<SYN_RCVD>: On recv RST, Expect: Return LISTEN."            \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"    \
                  "CurState - $R_Connection_State, ExpectedState - LISTEN"
  CleanUpEnvironment
  return
}
RecordAssertion pass $GenericAssertionGuid                                     \
                "Passive Connection, On recving RST (1-B less than "           \
                "window boundary), Return LISTEN state"

#
# Re-initiate connection, let it enter SYN_RCVD state
#
#
# Instruct <OS> send a SYN segment, Expect Receive SYN|ACK
#
set L_TcpFlag $SYN
UpdateTcpSendBuffer TCB -c $L_TcpFlag
SendTcpPacket TCB

ReceiveTcpPacket TCB 5
if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_ack} != 1 || ${TCB.r_f_syn} != 1} {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out SYN|ACK segment correctly."
    CleanUpEutEnvironment
    return
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."
  CleanUpEutEnvironment
  return
}

RecordAssertion pass $GenericAssertionGuid                                     \
                "Passive Connection: after return to LISTEN,still respond"     \
                "to connection request normally"

#
# Instruct <OS> send a valid RST segment
# It's sequence number is EQUAL TO window boundary
#
set L_OrigSeq ${TCB.l_next_seq}
set L_TcpFlag $RST
UpdateTcpSendBuffer TCB -c $L_TcpFlag -s [expr $L_OrigSeq+${TCB.r_win}]
SendTcpPacket TCB

# Recover the next sequence number
set TCB.l_next_seq $L_OrigSeq

#
# Expect: On receiving a valid RST, the connection returned to LISTEN state
#
#BUGBUG - Call GetModeData will result in crash
Tcp4->GetModeData {&@R_Connection_State, NULL, NULL, NULL, NULL, &@R_Status}
GetAck
GetVar R_Connection_State
if { $R_Connection_State != $Tcp4StateListen || $R_Status != $EFI_SUCCESS} {
  set assert fail
  RecordAssertion $assert $Tcp4RstHandlingFunc2AssertionGuid002                \
                  "Passive Connection <SYN_RCVD> - 2: "                        \
                  "On recv RST, Expect Return to LISTEN state."                \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"    \
                  "CurState - $R_Connection_State, ExpectedState - LISTEN"
}
RecordAssertion pass $GenericAssertionGuid                                     \
                "Passive Connection, On recving RST (EQUAL window "            \
                "boundary), Return LISTEN state"

# Clean up the environment on EUT side.
#
CleanUpEutEnvironment



