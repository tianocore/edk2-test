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
CaseGuid          221AE17F-AC90-47a7-8582-EA5BC4E6CB4A
CaseName          Receive.Func2.Case2
CaseCategory      TCP
CaseDescription   {This case is to test the Functionality.                     \
                   --Use Tcp4->Receive() to receive more fragments.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  global L_FragmentLength
  array unset L_FragmentLength

  global RST
  UpdateTcpSendBuffer TCB -c $RST
  SendTcpPacket TCB

  DestroyTcb
  DestroyPacket
  DelEntryInArpCache

  Tcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

}

proc CleanUpEutEnvironmentEnd {} {
  EndLogPacket
  EndScope _TCP4_SPEC_FUNCTIONALITY_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _TCP4_SPEC_FUNCTIONALITY_

BeginLogPacket Receive.Func2.Case2 "host $DEF_EUT_IP_ADDR and host             \
                                             $DEF_ENTS_IP_ADDR"
#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
if { [ info exists L_FragmentLength ] } {
  unset L_FragmentLength
}
array set L_FragmentLength {
  0    1
  1    2
  2    4
  3    8
  4    16
  5    32
  6    64
  7    128
  8    256
  9    512
}

set    L_FragmentNumber          10

UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Context

UINTN                            TempStatus

EFI_TCP4_CONFIG_DATA             R_Tcp4ConfigData
EFI_IP4_MODE_DATA                R_Ip4ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE          R_SnpModeData

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData

EFI_TCP4_COMPLETION_TOKEN        R_Connect_CompletionToken
EFI_TCP4_CONNECTION_TOKEN        R_Connect_ConnectionToken

EFI_TCP4_IO_TOKEN                R_Receive_IOToken
EFI_TCP4_COMPLETION_TOKEN        R_Receive_CompletionToken

Packet                           R_Packet_Buffer
EFI_TCP4_RECEIVE_DATA            R_RxData
EFI_TCP4_FRAGMENT_DATA           R_FragmentTable(10)

CHAR8                            R_FragmentBuffer0($L_FragmentLength(0))
CHAR8                            R_FragmentBuffer1($L_FragmentLength(1))
CHAR8                            R_FragmentBuffer2($L_FragmentLength(2))
CHAR8                            R_FragmentBuffer3($L_FragmentLength(3))
CHAR8                            R_FragmentBuffer4($L_FragmentLength(4))
CHAR8                            R_FragmentBuffer5($L_FragmentLength(5))
CHAR8                            R_FragmentBuffer6($L_FragmentLength(6))
CHAR8                            R_FragmentBuffer7($L_FragmentLength(7))
CHAR8                            R_FragmentBuffer8($L_FragmentLength(8))
CHAR8                            R_FragmentBuffer9($L_FragmentLength(9))

BuildTcpOptions MssOption -m 100

for { set i 0 } { $i < $L_FragmentNumber } { incr i } {
  CreatePayload payload$i const $L_FragmentLength($i)  $i
}

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
# Create Tcp4 Child.
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
SetVar          R_Configure_AccessPoint.ActiveFlag         TRUE

SetVar R_Configure_Tcp4ConfigData.TypeOfService       1
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
    puts "EUT doesn't send out SYN segment correctly."
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out SYN segment correctly."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }
} else {
  set assert fail
  puts "EUT doesn't send out any segment."
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

set L_TcpFlag [ expr $SYN | $ACK ]
UpdateTcpSendBuffer TCB -c $L_TcpFlag -o MssOption
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

Stall 1
#
# OS send DATA & ACK segment, more fragments
#
for { set i 0 } { $i < $L_FragmentNumber } { incr i } {

  ReceiveTcpPacket TCB 1

  if { $i < $L_FragmentNumber - 1 } {
    set L_TcpFlag $ACK
  } else {
    set L_TcpFlag [ expr $PSH | $ACK ]
  }
  UpdateTcpSendBuffer TCB -c $L_TcpFlag -p payload$i
  SendTcpPacket TCB

}

#
# Call Tcp4.Receive to receive a packet.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Receive_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_RxData.UrgentFlag                FALSE
set    L_FragmentLength_SUM               0
for { set i 0 } { $i < $L_FragmentNumber } { incr i } {
  set  L_FragmentLength_SUM  [ expr $L_FragmentLength_SUM + $L_FragmentLength($i) ]
}
SetVar R_RxData.DataLength                $L_FragmentLength_SUM
SetVar R_RxData.FragmentCount             $L_FragmentNumber

for { set i 0 } { $i < $L_FragmentNumber } { incr i } {
  SetVar R_FragmentTable($i).FragmentLength    $L_FragmentLength($i)
  SetVar R_FragmentTable($i).FragmentBuffer    &@R_FragmentBuffer$i
  SetVar R_RxData.FragmentTable($i)            @R_FragmentTable($i)
}

SetVar R_Packet_Buffer.RxData  &@R_RxData

SetVar R_Receive_IOToken.CompletionToken  @R_Receive_CompletionToken
SetVar R_Receive_IOToken.Packet_Buffer    @R_Packet_Buffer
SetVar R_Receive_IOToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION

Tcp4->Receive {&@R_Receive_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Receive - Receive a packet."                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set TempStatus $R_Status

#
# OS get the ACK segment.
#
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_ack} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                            "EUT doesn't send out ACK segment correctly."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    BS->CloseEvent "@R_Receive_CompletionToken.Event, &@R_Status"
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
  BS->CloseEvent "@R_Receive_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

#
# Check the Token.Status to verify the data has been transmitted successfully.
#
while {1} {
  Stall 1
  GetVar R_Receive_IOToken.CompletionToken.Status

  if { $TempStatus != $EFI_SUCCESS }   {
      set assert fail
      RecordAssertion $assert $Tcp4ReceiveFunc2AssertionGuid002                \
                      "Tcp4.Receive - Call Receive() to receive more fragments."\
                      "ReturnStatus - $TempStatus, ExpectedStatus - $EFI_SUCCESS"

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
      GetAck
      BS->CloseEvent "@R_Receive_CompletionToken.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
  } else {
 
  if { ${R_Receive_IOToken.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
    if { ${R_Receive_IOToken.CompletionToken.Status} != $EFI_SUCCESS} {
      set assert fail
      RecordAssertion $assert $Tcp4ReceiveFunc2AssertionGuid002                \
                              "Transmission failed.                            \
                              ReturnStatus - ${R_Receive_IOToken.CompletionToken.Status},\
                              ExpectedStatus - $EFI_SUCCESS"

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
      GetAck
      BS->CloseEvent "@R_Receive_CompletionToken.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
    } else {
    	set assert pass
      RecordAssertion $assert $Tcp4ReceiveFunc2AssertionGuid002                \
                      "Tcp4.Receive - Call Receive() to receive more fragments."\
      "ReturnStatus - ${R_Receive_IOToken.CompletionToken.Status}, ExpectedStatus - $EFI_SUCCESS"
      break
    }
  }
 }
}

Stall 3
#
# Clean up the environment on EUT side.
#

CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
BS->CloseEvent "@R_Receive_CompletionToken.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
