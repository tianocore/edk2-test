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
CaseGuid          B8A18D68-C938-4564-B28E-301B105E93A8
CaseName          KeepAliveTimer.Func1.Case2
CaseCategory      TCP
CaseDescription   {This item is to test the [EUT] correctly respond to the     \
keep-alive segment which with garbage data.}
################################################################################
Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironment {} {
#
# send RST segment to [EUT]
#
  global RST
  UpdateTcpSendBuffer TCB -c $RST
  SendTcpPacket  TCB
 
  DestroyTcb
  DestroyPacket
  DelEntryInArpCache
 
  Tcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck
 
  Tcp4ServiceBinding->DestroyChild "@R_Accept_NewChildHandle, &@R_Status"
  GetAck

  BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
  GetAck

  EndLogPacket
  EndScope _TCP4_RFC_Timer_KeepAlive
  EndLog
}
#
# Begin log...
#
BeginLog

#
# Begin Scope
#
BeginScope _TCP4_RFC_Timer_KeepAlive
BeginLogPacket KeepAlive.Timer.Func4.case2 "host $DEF_EUT_IP_ADDR and host  \
                                               $DEF_ENTS_IP_ADDR"
#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Context
 
EFI_TCP4_CONFIG_DATA             R_Tcp4ConfigData
 
EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_OPTION                  R_Configure_ControlOption
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData
 
EFI_TCP4_LISTEN_TOKEN            R_Accept_ListenToken
EFI_TCP4_COMPLETION_TOKEN        R_Accept_CompletionToken
UINTN			                       R_Accept_NewChildHandle

set    L_FragmentLength          16

Packet                           R_Packet_Buffer
EFI_TCP4_TRANSMIT_DATA           R_TxData
EFI_TCP4_FRAGMENT_DATA           R_FragmentTable
CHAR8                            R_FragmentBuffer($L_FragmentLength)
#
# Initialization of TCB related on OS side.
#
CreateTcb TCB $DEF_ENTS_IP_ADDR $DEF_ENTS_PRT $DEF_EUT_IP_ADDR $DEF_EUT_PRT
CreatePayload Hello STRING 1 H

LocalEther  $DEF_ENTS_MAC_ADDR
RemoteEther $DEF_EUT_MAC_ADDR
LocalIp     $DEF_ENTS_IP_ADDR
RemoteIp    $DEF_EUT_IP_ADDR
#
# Add an entry in ARP cache.
#
AddEntryInArpCache

#
# Create TCP CHILD
#
Tcp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4SBP.CreateChild - Create Child 1"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# Configure TCP instance
#
SetVar          R_Configure_AccessPoint.UseDefaultAddress  FALSE
SetIpv4Address  R_Configure_AccessPoint.StationAddress     $DEF_EUT_IP_ADDR
SetIpv4Address  R_Configure_AccessPoint.SubnetMask         $DEF_EUT_MASK
SetVar          R_Configure_AccessPoint.StationPort        $DEF_EUT_PRT
SetIpv4Address  R_Configure_AccessPoint.RemoteAddress      $DEF_ENTS_IP_ADDR
SetVar          R_Configure_AccessPoint.RemotePort         $DEF_ENTS_PRT
SetVar          R_Configure_AccessPoint.ActiveFlag         FALSE

SetVar R_Configure_ControlOption.ReceiveBufferSize      4096
SetVar R_Configure_ControlOption.SendBufferSize         4096
SetVar R_Configure_ControlOption.MaxSynBackLog          0
SetVar R_Configure_ControlOption.ConnectionTimeout      0
SetVar R_Configure_ControlOption.DataRetries            0
SetVar R_Configure_ControlOption.FinTimeout             0
SetVar R_Configure_ControlOption.KeepAliveProbes        7200
SetVar R_Configure_ControlOption.KeepAliveTime          5
SetVar R_Configure_ControlOption.KeepAliveInterval      30
SetVar R_Configure_ControlOption.EnableNagle            TRUE
SetVar R_Configure_ControlOption.EnableTimeStamp        FALSE
SetVar R_Configure_ControlOption.EnableWindowScaling    FALSE
SetVar R_Configure_ControlOption.EnableSelectiveAck     FALSE
SetVar R_Configure_ControlOption.EnablePathMtuDiscovery FALSE

SetVar R_Configure_Tcp4ConfigData.TypeOfService      0
SetVar R_Configure_Tcp4ConfigData.TimeToLive         128
SetVar R_Configure_Tcp4ConfigData.AccessPoint        @R_Configure_AccessPoint
SetVar R_Configure_Tcp4ConfigData.ControlOption      &@R_Configure_ControlOption

Tcp4->Configure {&@R_Configure_Tcp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Configure - Configure Child 1."                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call TCP.Accept()
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Accept_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Accept_NewChildHandle  0
SetVar R_Accept_ListenToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION
SetVar R_Accept_ListenToken.CompletionToken @R_Accept_CompletionToken


Tcp4->Accept {&@R_Accept_ListenToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Accept - Accept a connection."                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
#  Handle the 3-way handshake
#

set L_TCPFlage [expr $SYN]
UpdateTcpSendBuffer TCB  -C $L_TCPFlage
SendTcpPacket TCB
ReceiveTcpPacket  TCB 3

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_ack} !=1  || ${TCB.r_f_syn} != 1 }  {
   set assert fail
   puts "EUT doesn't send out SYN|ACK segment correctly."
   RecordAssertion $assert $GenericAssertionGuid                               \
                   "EUT doesn't send out ACK segment correctly."
   CleanUpEutEnvironment
   return
 } else {
 
    if { ${TCB.r_seq} != 0 || ${TCB.r_ack} != 1 } {
       set assert fail
       puts "The sequence number or acknowledge number in EUT's SYN/ACK segment\
           is not correct."
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "The sequence number or acknowledge number in            \
                      ${TCB.r_seq} ${TCB.r_ack} EUT's SYN/ACK segment is not correct."
       CleanUpEutEnvironment
      return
     }
   }
} else {
   set assert fail
   puts "EUT doesn't send out any segment."
   RecordAssertion $assert $GenericAssertionGuid                               \
                   "EUT doesn't send out any segment."
   CleanUpEutEnvironment
   return
}

set L_TCPFlage [expr $ACK]
UpdateTcpSendBuffer TCB -C $L_TCPFlage
SendTcpPacket TCB

#
#  Get TcpChild Handle
#
while {1 > 0} {
  Stall 1
  GetVar R_Accept_ListenToken.CompletionToken.Status
 
  if { ${R_Accept_ListenToken.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
    if { ${R_Accept_ListenToken.CompletionToken.Status} != $EFI_SUCCESS} {
      set assert fail
      puts "Three-way handshake for passive connection failed."
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "Three-way handshake for passive connection failed."     \
                      "ReturnStatus - ${R_Accept_ListenToken.CompletionToken.Status},\
                       ExpectedStatus - $EFI_SUCCESS"
      CleanUpEutEnvironment
      return
    } else {
      break
    }
  }
}

GetVar R_Accept_ListenToken.NewChildHandle
SetVar R_Accept_NewChildHandle ${R_Accept_ListenToken.NewChildHandle}
SetVar [subst $ENTS_CUR_CHILD] @R_Accept_NewChildHandle

#
#check point1: Dose [EUT] keep connection when not all keep-alive probe was acknowledged
#
set L_Seq ${TCB.l_next_seq}
set l_isn ${TCB.l_isn}
set L_TCPFlage [expr $ACK]

set count 0
while { $count < 5 } {
  Stall 10
  UpdateTcpSendBuffer TCB -C $L_TCPFlage -s [expr $L_Seq + $l_isn - 1] -p Hello
  SendTcpPacket TCB
  ReceiveTcpPacket TCB 5
  if {${TCB.received} == 1} {
    if {${TCB.r_ack} == 1} {
      incr count
    } else {
      set assert fail
       puts "EUT don't correctly response Keep-alive porbe"
       RecordAssertion $assert $Tcp4KeepAliveTimerFunc1AssertionGuid002        \
                       "EUT don't don't correctly responed no garbage data     \
                       Keep-alive porbe"
       CleanUpEutEnvironment
       return
    }
  } else {
      set assert fail
      puts "EUT don't send out response for no garbage data Keep-alive porbe"
      RecordAssertion $assert $Tcp4KeepAliveTimerFunc1AssertionGuid002         \
                      "EUT don't send out response for no garbage data         \
                       Keep-alive porbe"
      CleanUpEutEnvironment
      return
  }
}

#
# CleanUpEutEnvironment
#
CleanUpEutEnvironment
