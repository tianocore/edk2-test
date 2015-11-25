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
CaseGuid          B8A18D68-C938-4564-B28E-301B105E93A8
CaseName          KeepAliveTimer.Func1.Case1
CaseCategory      TCP
CaseDescription   {This item is to test the [EUT] correctly respond to the     \
keep-alive segment which without garbage data.}
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
BeginLogPacket KeepAlive.Timer.Func4.case1 "host $DEF_EUT_IP_ADDR and host  \
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
                      "The sequence number or acknowledge number in ${TCB.r_seq}\
                       ${TCB.r_ack} EUT's SYN/ACK segment is not correct."
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
# Successfully Get the TCP child Handle
#
set assert pass
puts "EUT Successfully Create the TCP Child Handle."
RecordAssertion $assert $GenericAssertionGuid                                  \
                "EUT Successfully Create the TCP Child Handle."

#
#  check point1: Dose [EUT] correctly respond to the keep-alive segment which without
#  one garbage data
#
set L_Seq ${TCB.l_next_seq}
set l_isn ${TCB.l_isn}
set L_TCPFlage [expr $ACK]
UpdateTcpSendBuffer TCB -C $L_TCPFlage -s [expr $L_Seq + $l_isn - 1]
SendTcpPacket TCB

set count 0
while { $count < 5 } {
  Stall 10
  UpdateTcpSendBuffer TCB -C $L_TCPFlage -s [expr $L_Seq + $l_isn - 1]
  SendTcpPacket TCB
  ReceiveTcpPacket TCB 5
  if {${TCB.received} == 1} {
    if {${TCB.r_ack} == 1} {
      incr count
    } else {
      set assert fail
       puts "EUT don't correctly response Keep-alive porbe"
       RecordAssertion $assert $Tcp4KeepAliveTimerFunc1AssertionGuid001        \
                       "EUT don't don't correctly responed no garbage data     \
                        Keep-alive porbe"
       CleanUpEutEnvironment
       return
    }
  } else {
      set assert fail
      puts "EUT don't send out response for no garbage data Keep-alive porbe"
      RecordAssertion $assert $Tcp4KeepAliveTimerFunc1AssertionGuid001         \
                      "EUT don't send out response for no garbage data         \
                       Keep-alive porbe"
      CleanUpEutEnvironment
      return
  }
}

 set assert pass
 puts "EUT correctly send out response for no garbage data Keep-alive porbe"
 RecordAssertion $assert $Tcp4KeepAliveTimerFunc1AssertionGuid001              \
                 "EUT correctly send out response for no garbage data          \
                  Keep-alive porbe"
 
#
# CleanUpEutEnvironment
#
CleanUpEutEnvironment