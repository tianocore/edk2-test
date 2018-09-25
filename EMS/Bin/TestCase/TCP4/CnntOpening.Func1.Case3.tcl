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
CaseGuid          3404D45E-B327-4552-9D7A-09CEDCAB70D4
CaseName          CnntOpening.Func1.Case3
CaseCategory      TCP
CaseDescription   {This item is to test the [EUT] correctly establishes the    \
                   TCP connection through active open. This connection should  \
                   not affect any previously established connection.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  global RST
 
  UpdateTcpSendBuffer TCB_CNNT1 -c $RST
  SendTcpPacket TCB_CNNT1
 
  UpdateTcpSendBuffer TCB_CNNT2 -c $RST
  SendTcpPacket TCB_CNNT2
 
  DestroyTcb
  DelEntryInArpCache

  Tcp4ServiceBinding->DestroyChild "@R_Tcp4Handle_Cnnt1, &@R_Status"
  GetAck
 
  Tcp4ServiceBinding->DestroyChild "@R_Tcp4Handle_Cnnt2, &@R_Status"
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
# BeginScope on ENTS.
#
BeginScope _TCP4_RFC_COMPATIBILITY_

BeginLogPacket CnntOpening.Func1.Case3 "host $DEF_EUT_IP_ADDR and host         \
                                             $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Tcp4Handle_Cnnt1
UINTN                            R_Tcp4Handle_Cnnt2
UINTN                            R_Context_Cnnt1
UINTN                            R_Context_Cnnt2

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint_Cnnt1
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData_Cnnt1
EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint_Cnnt2
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData_Cnnt2

EFI_TCP4_COMPLETION_TOKEN        R_Connect_CompletionToken_Cnnt1
EFI_TCP4_CONNECTION_TOKEN        R_Connect_ConnectionToken_Cnnt1
EFI_TCP4_COMPLETION_TOKEN        R_Connect_CompletionToken_Cnnt2
EFI_TCP4_CONNECTION_TOKEN        R_Connect_ConnectionToken_Cnnt2

#
# Initialization of TCB related on OS side.
#
CreateTcb TCB_CNNT1 $DEF_ENTS_IP_ADDR $DEF_ENTS_PRT $DEF_EUT_IP_ADDR $DEF_EUT_PRT

set R_CNNT2_PRT [expr $DEF_EUT_PRT+1]
CreateTcb TCB_CNNT2 $DEF_ENTS_IP_ADDR $DEF_ENTS_PRT $DEF_EUT_IP_ADDR $R_CNNT2_PRT

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
Tcp4ServiceBinding->CreateChild "&@R_Tcp4Handle_Cnnt1, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Tcp4Handle_Cnnt1
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4SBP.CreateChild - Create Child 1."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure TCP instance.
#
SetVar R_Configure_AccessPoint_Cnnt1.UseDefaultAddress      FALSE
SetIpv4Address R_Configure_AccessPoint_Cnnt1.StationAddress $DEF_EUT_IP_ADDR
SetIpv4Address R_Configure_AccessPoint_Cnnt1.SubnetMask     $DEF_EUT_MASK
SetVar R_Configure_AccessPoint_Cnnt1.StationPort            $DEF_EUT_PRT
SetIpv4Address R_Configure_AccessPoint_Cnnt1.RemoteAddress  $DEF_ENTS_IP_ADDR
SetVar R_Configure_AccessPoint_Cnnt1.RemotePort             $DEF_ENTS_PRT
SetVar R_Configure_AccessPoint_Cnnt1.ActiveFlag             TRUE

SetVar R_Configure_Tcp4ConfigData_Cnnt1.TypeOfService       0
SetVar R_Configure_Tcp4ConfigData_Cnnt1.TimeToLive          128
SetVar R_Configure_Tcp4ConfigData_Cnnt1.AccessPoint         @R_Configure_AccessPoint_Cnnt1
SetVar R_Configure_Tcp4ConfigData_Cnnt1.ControlOption       0

Tcp4->Configure {&@R_Configure_Tcp4ConfigData_Cnnt1, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Configure - Configure Child 1."                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Tcp4.Connect for an active TCP instance.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context_Cnnt1,  \
                 &@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Connect_ConnectionToken_Cnnt1.CompletionToken @R_Connect_CompletionToken_Cnnt1
SetVar R_Connect_ConnectionToken_Cnnt1.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION

Tcp4->Connect {&@R_Connect_ConnectionToken_Cnnt1, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Connect - Open an active connection."                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Handles the three-way handshake.
#
ReceiveTcpPacket TCB_CNNT1 5

if { ${TCB_CNNT1.received} == 1 } {
  if { ${TCB_CNNT1.r_f_syn} != 1 } {
    set assert fail
    puts "EUT doesn't send out SYN segment correctly."
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out SYN segment correctly."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  } else {
    if { ${TCB_CNNT1.r_seq} != 0 } {
      set assert fail
      puts "The sequence number in EUT's SYN segment is not correct."
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "The sequence number in EUT's SYN segment is not correct."

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
    }
  }
} else {
  set assert fail
  puts "EUT doesn't send out any segment."
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

set L_TcpFlag [expr $SYN | $ACK]
UpdateTcpSendBuffer TCB_CNNT1 -c $L_TcpFlag
SendTcpPacket TCB_CNNT1

ReceiveTcpPacket TCB_CNNT1 5

if { ${TCB_CNNT1.received} == 1 } {
  if { ${TCB_CNNT1.r_f_ack} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out ACK segment correctly."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  } else {
    if { ${TCB_CNNT1.r_ack} != 1 } {
      set assert fail
      puts "The Acknowledgment Number in EUT's ACK segment is not correct."
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "The Acknowledgment Number in EUT's ACK segment is not correct."

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
    }
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                          "EUT doesn't send out any segment."

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

#
# Check the Token.Status to verify the connection has been established.
#
while {1 > 0} {
  Stall 1
  GetVar R_Connect_ConnectionToken_Cnnt1.CompletionToken.Status
 
  if { ${R_Connect_ConnectionToken_Cnnt1.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
    if { ${R_Connect_ConnectionToken_Cnnt1.CompletionToken.Status} != $EFI_SUCCESS} {
      set assert fail
      puts "Three-way handshake for active connection failed."
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "Three-way handshake for active connection failed."      \
                      "ReturnStatus - ${R_Connect_ConnectionToken_Cnnt1.CompletionToken.Status},\
                       ExpectedStatus - $EFI_SUCCESS"

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
    } else {
      break
    }
  }
}


#
# After Connection1 established, begin the second connection
#
Tcp4ServiceBinding->CreateChild "&@R_Tcp4Handle_Cnnt2, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Tcp4Handle_Cnnt2
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4SBP.CreateChild - Create Child 2."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure TCP instance.
#
SetVar R_Configure_AccessPoint_Cnnt2.UseDefaultAddress      FALSE
SetIpv4Address R_Configure_AccessPoint_Cnnt2.StationAddress $DEF_EUT_IP_ADDR
SetIpv4Address R_Configure_AccessPoint_Cnnt2.SubnetMask     $DEF_EUT_MASK
SetVar R_Configure_AccessPoint_Cnnt2.StationPort            $R_CNNT2_PRT
SetIpv4Address R_Configure_AccessPoint_Cnnt2.RemoteAddress  $DEF_ENTS_IP_ADDR
SetVar R_Configure_AccessPoint_Cnnt2.RemotePort             $DEF_ENTS_PRT
SetVar R_Configure_AccessPoint_Cnnt2.ActiveFlag             TRUE

SetVar R_Configure_Tcp4ConfigData_Cnnt2.TypeOfService       0
SetVar R_Configure_Tcp4ConfigData_Cnnt2.TimeToLive          128
SetVar R_Configure_Tcp4ConfigData_Cnnt2.AccessPoint         @R_Configure_AccessPoint_Cnnt2
SetVar R_Configure_Tcp4ConfigData_Cnnt2.ControlOption       0

Tcp4->Configure {&@R_Configure_Tcp4ConfigData_Cnnt2, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Configure - Configure Child 2."                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Tcp4.Connect for an active TCP instance.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context_Cnnt2,  \
                 &@R_Connect_CompletionToken_Cnnt2.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid   "BS.CreateEvent."              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Connect_ConnectionToken_Cnnt2.CompletionToken @R_Connect_CompletionToken_Cnnt2
SetVar R_Connect_ConnectionToken_Cnnt2.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION

Tcp4->Connect {&@R_Connect_ConnectionToken_Cnnt2, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp4CnntOpeningFunc1AssertionGuid003                  \
                "Tcp4.Connect - Open an active connection."                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Handles the three-way handshake.
#
ReceiveTcpPacket TCB_CNNT2 5

if { ${TCB_CNNT2.received} == 1 } {
  if { ${TCB_CNNT2.r_f_syn} != 1 } {
    set assert fail
    puts "EUT doesn't send out SYN segment correctly."
    RecordAssertion $assert $GenericAssertionGuid                              \
                            "EUT doesn't send out SYN segment correctly."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
    GetAck
    BS->CloseEvent "@R_Connect_CompletionToken_Cnnt2.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  } else {
    if { ${TCB_CNNT2.r_seq} != 0 } {
      set assert fail
      puts "The sequence number in EUT's SYN segment is not correct."
      RecordAssertion $assert $GenericAssertionGuid                            \
                              "The sequence number in EUT's SYN segment is not \
                              correct."

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
      GetAck
      BS->CloseEvent "@R_Connect_CompletionToken_Cnnt2.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
    }
  }
} else {
  set assert fail
  puts "EUT doesn't send out any segment."
  RecordAssertion $assert $GenericAssertionGuid                                \
                          "EUT doesn't send out any segment."

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Connect_CompletionToken_Cnnt2.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

set L_TcpFlag [expr $SYN | $ACK]
UpdateTcpSendBuffer TCB_CNNT2 -c $L_TcpFlag
SendTcpPacket TCB_CNNT2

ReceiveTcpPacket TCB_CNNT2 5

if { ${TCB_CNNT2.received} == 1 } {
  if { ${TCB_CNNT2.r_f_ack} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                            "EUT doesn't send out ACK segment correctly."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
    GetAck
    BS->CloseEvent "@R_Connect_CompletionToken_Cnnt2.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  } else {
    if { ${TCB_CNNT2.r_ack} != 1 } {
      set assert fail
      puts "The Acknowledgment Number in EUT's ACK segment is not correct."
      RecordAssertion $assert $GenericAssertionGuid                            \
                              "The Acknowledgment Number in EUT's ACK segment  \
                              is not correct."

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
      GetAck
      BS->CloseEvent "@R_Connect_CompletionToken_Cnnt2.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
    }
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                          "EUT doesn't send out any segment."

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Connect_CompletionToken_Cnnt2.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

#
# Check the Token.Status to verify the connection has been established.
#
while {1 > 0} {
  Stall 1
  GetVar R_Connect_ConnectionToken_Cnnt2.CompletionToken.Status
 
  if { ${R_Connect_ConnectionToken_Cnnt2.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
    if { ${R_Connect_ConnectionToken_Cnnt2.CompletionToken.Status} != $EFI_SUCCESS} {
      set assert fail
      puts "Three-way handshake for active connection failed."
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "Three-way handshake for active connection failed."      \
      "ReturnStatus - ${R_Connect_ConnectionToken_Cnnt2.CompletionToken.Status}, ExpectedStatus - $EFI_SUCCESS"

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
      GetAck
      BS->CloseEvent "@R_Connect_CompletionToken_Cnnt2.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
    } else {
      break
    }
  }
}

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Connect_CompletionToken_Cnnt1.Event, &@R_Status"
GetAck
BS->CloseEvent "@R_Connect_CompletionToken_Cnnt2.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
