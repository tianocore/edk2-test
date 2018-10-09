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
CaseGuid          23B401D8-E2B2-4F23-D032-839A38D3E93F
CaseName          Others.Func1.Case3
CaseCategory      TCP
CaseDescription   {This item is to test [EUT] can correctly handle SYN flood.  \
                   --[EUT] should NOT send out <RST> segment to reset incomplete\
                   connection queue when ConnectionTimeout (SYN time) haven't  \
                   reached.                                                    \
                   --Discard following incoming <SYN> segment when             \
                   MaxSynBacklog is full.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  global RST SYN_TIMES

  for { set i 1 } { $i <= $SYN_TIMES } { incr i } {
    UpdateTcpSendBuffer TCB$i -c $RST
    SendTcpPacket TCB$i
  }

  UpdateTcpSendBuffer TCB -c $RST
  SendTcpPacket TCB

  DestroyTcb
  DelEntryInArpCache

  Tcp4ServiceBinding->DestroyChild "@R_Tcp4Handle, &@R_Status"
  GetAck

  Tcp4ServiceBinding->DestroyChild "@R_Accept_NewChildHandle, &@R_Status"
  GetAck

  BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
  GetAck

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

BeginLogPacket Others.Func1.Case3      "host $DEF_EUT_IP_ADDR and host         \
                                             $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
set      SYN_TIMES                               50
set      L_ControlOption_MaxSynBackLog           5
set      L_ControlOption_ConnectionTimeout       60

UINTN                            R_Status
UINTN                            R_Tcp4Handle
UINTN                            R_Context

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData

EFI_TCP4_COMPLETION_TOKEN        R_Accept_CompletionToken
EFI_TCP4_LISTEN_TOKEN            R_Accept_ListenToken
UINTN                            R_Accept_NewChildHandle

EFI_TCP4_OPTION                  R_Configure_ControlOption

#
# Initialization of TCB related on OS side.
#
CreateTcb TCB $DEF_ENTS_IP_ADDR $DEF_ENTS_PRT $DEF_EUT_IP_ADDR $DEF_EUT_PRT

for { set i 1 } { $i <= $SYN_TIMES } { incr i } {
  set temp_port [ expr 400 + $i ]
  CreateTcb TCB$i $DEF_ENTS_IP_ADDR $temp_port $DEF_EUT_IP_ADDR $DEF_EUT_PRT
}

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
                "Tcp4SBP.CreateChild - Create Child 1"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure TCP instance.
#
SetVar          R_Configure_AccessPoint.UseDefaultAddress  FALSE
SetIpv4Address  R_Configure_AccessPoint.StationAddress     $DEF_EUT_IP_ADDR
SetIpv4Address  R_Configure_AccessPoint.SubnetMask         $DEF_EUT_MASK
SetVar          R_Configure_AccessPoint.StationPort        $DEF_EUT_PRT
SetIpv4Address  R_Configure_AccessPoint.RemoteAddress      0
SetVar          R_Configure_AccessPoint.RemotePort         0
SetVar          R_Configure_AccessPoint.ActiveFlag         FALSE

SetVar    R_Configure_Tcp4ConfigData.TypeOfService    0
SetVar    R_Configure_Tcp4ConfigData.TimeToLive       128
SetVar    R_Configure_Tcp4ConfigData.AccessPoint      @R_Configure_AccessPoint
SetVar    R_Configure_ControlOption.ConnectionTimeout $L_ControlOption_ConnectionTimeout
SetVar    R_Configure_ControlOption.MaxSynBackLog     $L_ControlOption_MaxSynBackLog
SetVar    R_Configure_Tcp4ConfigData.ControlOption    &@R_Configure_ControlOption

Tcp4->Configure {&@R_Configure_Tcp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Configure - Configure Child 1."                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Tcp4.Accept for an passive TCP instance.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Accept_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Accept_ListenToken.CompletionToken @R_Accept_CompletionToken
SetVar R_Accept_ListenToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION

Tcp4->Accept {&@R_Accept_ListenToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Accept - Open an passive connection."                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# <SYN> flood
#
for { set i 1 } { $i <= $SYN_TIMES } { incr i } {
  UpdateTcpSendBuffer TCB$i -c $SYN
}
for { set i 1 } { $i <= $SYN_TIMES } { incr i } {
  SendTcpPacket TCB$i
}

#
# Send <SYN> segment to [EUT] when MaxSynBacklog is full.
#
UpdateTcpSendBuffer TCB -c $SYN
SendTcpPacket TCB

#
# OS gets <SYN, ACK> segment
#
ReceiveTcpPacket TCB $L_ControlOption_ConnectionTimeout

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_syn} == 1 && ${TCB.r_f_ack} == 1 } {
  set assert fail
  RecordAssertion $assert $Tcp4OthersFunc1AssertionGuid003                     \
                  "EUT should NOT send out <SYN, ACK> segment,                 \
                   because MaxSynBacklog is full."
  }
} else {
  set assert pass
  RecordAssertion $assert $Tcp4OthersFunc1AssertionGuid003                     \
                  "EUT does NOT send out <SYN, ACK> segment,                   \
                   because MaxSynBacklog is full."
}

SetVar R_Accept_NewChildHandle 0
#
# Get the NewChildHandle value.
#
GetVar R_Accept_ListenToken.NewChildHandle
SetVar R_Accept_NewChildHandle ${R_Accept_ListenToken.NewChildHandle}

Stall 2
#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment
