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
CaseGuid          CEA9D920-CE78-42b4-8EBB-80E4FB251A84
CaseName          CongestionCtrl.Func2.Case2
CaseCategory      TCP
CaseDescription   {This item is to test the [EUT] correctly generates          \
                   duplicated acknowledgements when it received disordering    \
                   segments.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  global RST
 
  UpdateTcpSendBuffer TCB -c $RST
  SendTcpPacket TCB
 
  DestroyTcb
  DestroyPacket
  DelEntryInArpCache

  Tcp4ServiceBinding->DestroyChild "@R_Tcp4Handle, &@R_Status"
  GetAck
 
}

proc CleanUpEutEnvironmentEnd {} {
  EndLogPacket
  EndScope _TCP4_RFC_COMPATIBILITY_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope on OS.
#
BeginScope _TCP4_RFC_COMPATIBILITY_

BeginLogPacket CongestionCtrl.Func2.Case2 "host $DEF_EUT_IP_ADDR and host      \
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

#
# Initialization of TCB related on OS side.
#
CreateTcb TCB $DEF_ENTS_IP_ADDR $DEF_ENTS_PRT $DEF_EUT_IP_ADDR $DEF_EUT_PRT
CreatePayload BoundaryPayload incr 536 0x00

LocalEther  $DEF_ENTS_MAC_ADDR
RemoteEther $DEF_EUT_MAC_ADDR
LocalIp     $DEF_ENTS_IP_ADDR
RemoteIp    $DEF_EUT_IP_ADDR

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
SetVar R_Configure_AccessPoint.StationPort            $DEF_EUT_PRT
SetIpv4Address R_Configure_AccessPoint.RemoteAddress  $DEF_ENTS_IP_ADDR
SetVar R_Configure_AccessPoint.RemotePort             $DEF_ENTS_PRT
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
SetVar R_Connect_ConnectionToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION

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

set L_TcpFlag [expr $SYN | $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag
SendTcpPacket TCB

ReceiveTcpPacket TCB 5

#
# Configure the OS to send consecutive data segments to the EUT, drop one
# segment in the middle and EUT should generate duplicated ACKs as the result
# of receiving every data segments.
#
for { set i 0} { $i < 6 } { incr i } {
  UpdateTcpSendBuffer TCB -c $ACK -p BoundaryPayload
  SendTcpPacket TCB
}

# This segment is to be dropped.
UpdateTcpSendBuffer TCB -c $ACK -p BoundaryPayload

#
# Flush the Receive buffer and record the last ack number.
#
while { 0 < 1} {
  ReceiveTcpPacket TCB 0
  if { ${TCB.received} == 1 } {
    continue
  } else {
    break
  }
}
set expecet_r_ack  [ expr {536 * 6 + 1} ]

#
# Send the data segments after the dropped one, and check the responded
# duplicated ACKs.
#
for { set i 0} { $i < 6 } { incr i } {
  UpdateTcpSendBuffer TCB -c $ACK -p BoundaryPayload
  SendTcpPacket TCB
}

#
# Track duplicated ACK sent from EUT side
#

#
# Track the first ACK for the disordered segment
#
set duplicatenum 0
for { set i 0} { $i < 12 } { incr i} {
  ReceiveTcpPacket TCB 2
  if { ${TCB.received} == 1 } {
    if { ${TCB.r_f_ack} == 1 && ${TCB.r_len} == 0 && ${TCB.r_ack} == $expecet_r_ack || ${TCB.r_seq} == 1} {
      incr duplicatenum
      break;
    }
  } else {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                            \
                        "EUT doesn't send out duplicated ACK segment correctly."
    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }	
}

if { $duplicatenum  == 0 } {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                            \
                      "EUT doesn't send out duplicated ACK segment correctly."
  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

# 
# Track for 2 more ACK for the disordered segment
#
for { set i 0} { $i < 2} {incr i } {
  ReceiveTcpPacket TCB 2
  if { ${TCB.received} == 1 } {
    if { ${TCB.r_f_ack} == 1 && ${TCB.r_len} == 0 && ${TCB.r_ack} == $expecet_r_ack || ${TCB.r_seq} == 1} {
      incr duplicatenum
    }
  } else {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                            \
                        "EUT doesn't send out duplicated ACK segment correctly."
    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }
}

if { $duplicatenum  == 3 } {
  set assert pass
  RecordAssertion $assert $GenericAssertionGuid                            \
                      "EUT send out duplicated ACK segments (at least 3) correctly."
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                            \
                      "EUT doesn't send out duplicated ACK segment correctly."
  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

#
# Retransmit the dropped segment, and EUT should respond with Full
# Acknowledgement as the result of the segment.
#
set temp_ack [ expr { $expecet_r_ack + ${TCB.l_isn} } ]
UpdateTcpSendBuffer TCB -c $ACK -p BoundaryPayload -s $temp_ack
SendTcpPacket TCB

set i 0
set timeoutnum 30
while { 1 } {
  if { $i > $timeoutnum} {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out Full ACK segment correctly before timeout."
    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }
  
  ReceiveTcpPacket TCB 2
  
  if { ${TCB.received} == 1 } {
    if { ${TCB.r_f_ack} != 1 || ${TCB.r_len} != 0} {
      set assert fail
      RecordAssertion $assert $GenericAssertionGuid                              \
                      "EUT doesn't send out Full ACK segment correctly."

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
    } else {
      if { ${TCB.r_ack} > $expecet_r_ack && ${TCB.r_seq} == 1 } {
        break
      }
    }
  }

  incr i
}
	  

set assert pass
RecordAssertion $assert $CongestionCtrlFunc2AssertionGuid002                 \
                  "The EUT send out the Full ACK correctly."


#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
