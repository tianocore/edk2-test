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
CaseGuid          84911C3C-692E-491d-A149-5A526B5388CF
CaseName          Options.Func4.Case4
CaseCategory      TCP
CaseDescription   {This case is to test the Functionality. It is designed to   \
test that when [EUT] recevied <SYN> segment without MSS,    \
[EUT] could take [ENTS]'s MSS as RFC default value 536.     \
                   -- And [EUT] will set its own MSS = 536 too, when receive   \
                   segment data length larger than its MSS, it should handle it\
                   -- With unaligned window scale option.  -- format 2:        \
                     0            7           15           23           31     \
                     +------------+------------+------------+------------+     \
                     |   No-Oper  |   No-Oper  |  00000011  |  00000011  |     \
                     +------------+------------+------------+------------+     \
                     |  shift.cnt |   No-Oper  |   No-Oper  |   No-Oper  |     \
                     +------------+------------+------------+------------+.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  global RST
  UpdateTcpSendBuffer TCB -c $RST
  SendTcpPacket TCB

  DestroyTcb
  DestroyPacket
  DelEntryInArpCache

  Tcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  Tcp4ServiceBinding->DestroyChild "@R_Accept_NewChildHandle, &@R_Status"
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
# BeginScope
#
BeginScope _TCP4_RFC_COMPATIBILITY_

BeginLogPacket Options.Func6.Case4 "host $DEF_EUT_IP_ADDR and host $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
set    L_FragmentLength          1460    ;# data to transmit by [EUT]
set    RFC_TCP_DEF_MSS           536     ;# RFC default MSS, EFI conform with it.
set    L_WindowField             256     ;# [OS] TCP header - Window Field
set    L_WindowScale             2       ;# [OS] TCP option - Window Scale
#
# Calculate [OS] MAX acceptable window
#
set    L_RCV_WND                 [ expr $L_WindowField << $L_WindowScale ]

UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Context

EFI_TCP4_CONFIG_DATA             R_Tcp4ConfigData
EFI_IP4_MODE_DATA                R_Ip4ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE          R_SnpModeData

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData
EFI_TCP4_OPTION                  R_Configure_ControlOption

EFI_TCP4_LISTEN_TOKEN            R_Accept_ListenToken
UINTN                            R_Accept_NewChildHandle
EFI_TCP4_COMPLETION_TOKEN        R_Accept_CompletionToken

EFI_TCP4_IO_TOKEN                R_Transmit_IOToken
EFI_TCP4_COMPLETION_TOKEN        R_Transmit_CompletionToken

Packet                           R_Packet_Buffer
EFI_TCP4_TRANSMIT_DATA           R_TxData
EFI_TCP4_FRAGMENT_DATA           R_FragmentTable
UINT8                            R_FragmentBuffer($L_FragmentLength)

#
# Create TCP option.
# Windows Scale: shift.cnt = 2
#
CreatePayload Option_WS Data 8 0x01 0x01 0x03 0x03 $L_WindowScale 0x01 0x01 0x01


##
## Create data segment to transmit.
## else, will transmit all zero as NULL value. This will quicken case run speed.
##
#CreatePayload PayloadData incr $L_FragmentLength 0x00
#PayloadToArray PayloadData L_FragmentBuffer
#
#for {set i 0} {$i < $L_FragmentLength} {incr i} {
#    SetVar R_FragmentBuffer($i) $L_FragmentBuffer($i)
#}

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
# Configure TCP instance.
#
SetVar          R_Configure_AccessPoint.UseDefaultAddress  FALSE
SetIpv4Address  R_Configure_AccessPoint.StationAddress     $DEF_EUT_IP_ADDR
SetIpv4Address  R_Configure_AccessPoint.SubnetMask         $DEF_EUT_MASK
SetVar          R_Configure_AccessPoint.StationPort        $DEF_EUT_PRT
SetIpv4Address  R_Configure_AccessPoint.RemoteAddress      $DEF_ENTS_IP_ADDR
SetVar          R_Configure_AccessPoint.RemotePort         $DEF_ENTS_PRT
SetVar          R_Configure_AccessPoint.ActiveFlag         FALSE

SetVar R_Configure_Tcp4ConfigData.TypeOfService       1
SetVar R_Configure_Tcp4ConfigData.TimeToLive          128
SetVar R_Configure_Tcp4ConfigData.AccessPoint         @R_Configure_AccessPoint

SetVar R_Configure_ControlOption.EnableWindowScaling  TRUE

Tcp4->Configure {&@R_Configure_Tcp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Configure - Configure Child 1."                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set L_TcpFlag [expr $SYN]
UpdateTcpSendBuffer TCB -c $L_TcpFlag -w $L_WindowField -o Option_WS
SendTcpPacket TCB

#
# Call Tcp4.Accept() to accept a connetion.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context, &@R_Accept_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid   "BS.CreateEvent."              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Accept_ListenToken.CompletionToken @R_Accept_CompletionToken
SetVar R_Accept_ListenToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION

Tcp4->Accept {&@R_Accept_ListenToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Accept - Accept a connection."                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# OS get SYN & ACK segment
#
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_syn} != 1 && ${TCB.r_f_ack} != 1 } {
    set assert fail
    puts "EUT doesn't send out SYN & ACK segment correctly."
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out SYN & ACK segment correctly."
    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  }

  if { ${TCB.r_mss} <= 0 || ${TCB.r_mss} > 1460 } {
    set assert fail
    puts "EUT send out SYN segment with MSS wrongly."
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT send out SYN segment with MSS wrongly."
  } else {
    #
    # Get MSS from EUT
    #
    set EutMss ${TCB.r_mss}
  }
} else {
  set assert fail
  puts "EUT doesn't send out any segment."
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

#
# OS send ACK segment
#
UpdateTcpSendBuffer TCB -c $ACK -w $L_WindowField
SendTcpPacket TCB

#
# Get the NewChildHandle value.
#
GetVar R_Accept_ListenToken.NewChildHandle
SetVar R_Accept_NewChildHandle ${R_Accept_ListenToken.NewChildHandle}
SetVar [subst $ENTS_CUR_CHILD]  @R_Accept_NewChildHandle

#
# Call Tcp4.Transmit() to transmit a packet.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Transmit_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid      "BS.CreateEvent."           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_TxData.Push                      FALSE
SetVar R_TxData.Urgent                    FALSE
SetVar R_TxData.DataLength                $L_FragmentLength
SetVar R_TxData.FragmentCount             1

SetVar R_FragmentTable.FragmentLength     $L_FragmentLength
SetVar R_FragmentTable.FragmentBuffer     &@R_FragmentBuffer
SetVar R_TxData.FragmentTable(0)          @R_FragmentTable

SetVar R_Packet_Buffer.TxData  &@R_TxData

SetVar R_Transmit_IOToken.CompletionToken         @R_Transmit_CompletionToken
SetVar R_Transmit_IOToken.Packet_Buffer           @R_Packet_Buffer
SetVar R_Transmit_IOToken.CompletionToken.Status  $EFI_INCOMPATIBLE_VERSION

Tcp4->Transmit {&@R_Transmit_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Transmit - Transmit a packet."                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Do loop that [OS] need to capture the TCP Segment fragement.
#
set sum_fragment 0      ;# initial total received fragment size to zero.
set index        0      ;# initial fragment index to zero.
while { $sum_fragment < $L_FragmentLength } {
  incr index
  #
  # [OS] get the transmitted data segment.
  #
  ReceiveTcpPacket TCB 5

  if { ${TCB.received} == 1 } {
    if { ${TCB.r_f_ack} != 1 } {
      RecordAssertion fail $GenericAssertionGuid                               \
                           "EUT wrongly send out segment, fragment $index."

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
      GetAck
      BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
    } elseif { ${TCB.r_seq} != [ expr $sum_fragment + 1 ] } {    ;# check r_seq
        puts "{TCB.r_seq} = ${TCB.r_seq}"
        puts "Expected Sequence Number = [ expr $sum_fragment + 1 ]"
        RecordAssertion fail $GenericAssertionGuid                             \
                        "EUT send TCP data segment sequence unequal to OS expect."

        CleanUpEutEnvironmentBegin
        BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
        GetAck
        BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
        GetAck
        CleanUpEutEnvironmentEnd
        return
    } elseif { ${TCB.r_len} > $L_RCV_WND } {          ;# check r_len > RCV_WND?
        puts "{TCB.r_len} = ${TCB.r_len}"
        puts "Expected Segment Data Size should no more than $L_RCV_WND."
        RecordAssertion fail $GenericAssertionGuid                             \
                        "EUT send TCP Segment Data Size larger than OS receive window."

        CleanUpEutEnvironmentBegin
        BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
        GetAck
        BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
        GetAck
        CleanUpEutEnvironmentEnd
        return
    } elseif { ${TCB.r_len} > $RFC_TCP_DEF_MSS } {              ;# check r_len > MSS?
        puts "{TCB.r_len} = ${TCB.r_len}"
        puts "Expected Segment Data Size should no more than $RFC_TCP_DEF_MSS."
        RecordAssertion fail $GenericAssertionGuid                             \
                        "EUT send TCP Segment Data Size larger than OS MSS."

        CleanUpEutEnvironmentBegin
        BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
        GetAck
        BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
        GetAck
        CleanUpEutEnvironmentEnd
        return
    } else {
        # correct;
        RecordAssertion pass $GenericAssertionGuid                             \
                        "EUT correctly divide up TCP data segment to send. fragment $index."
        set sum_fragment [ expr $sum_fragment + ${TCB.r_len}]
    }
  } else {
      set assert fail
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "EUT doesn't send out TCP segment, fragment $index."

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
      GetAck
      BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
  }

  #
  # [OS] send ACK segment.
  #
  UpdateTcpSendBuffer TCB -c $ACK -w $L_WindowField
  SendTcpPacket TCB
}

#
# Check the Token.Status to verify the data has been transmitted successfully.
#
while {1 > 0} {
  Stall 1
  GetVar R_Transmit_IOToken.CompletionToken.Status

  if { ${R_Transmit_IOToken.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
    if { ${R_Transmit_IOToken.CompletionToken.Status} != $EFI_SUCCESS} {
      set assert fail
      puts "Data transmission failed."
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "Data transmission failed."                              \
      "ReturnStatus - ${R_Transmit_IOToken.CompletionToken.Status}, ExpectedStatus - $EFI_SUCCESS"

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
      GetAck
      BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
      GetAck
      CleanUpEutEnvironmentEnd
      return
    } else {
      break
    }
  }
}

#------------------------- [OS] sends data to [EUT] -------------------------#
#
# Create a data segment to be transmitted, with size larger than $RFC_TCP_DEF_MSS
#
CreatePayload PayloadData incr $EutMss 0x00

#
# OS sends DATA & ACK segment
#
set L_TcpFlag [expr $PSH | $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag -p PayloadData
SendTcpPacket TCB

EFI_TCP4_IO_TOKEN                R_Receive_IOToken
EFI_TCP4_COMPLETION_TOKEN        R_Receive_CompletionToken

EFI_TCP4_RECEIVE_DATA            R_RxData

#
# Call Tcp4.Receive to receive a packet.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Receive_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid   "BS.CreateEvent."              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_RxData.UrgentFlag                FALSE
SetVar R_RxData.DataLength                $L_FragmentLength
SetVar R_RxData.FragmentCount             1

SetVar R_FragmentTable.FragmentLength     $L_FragmentLength
SetVar R_FragmentTable.FragmentBuffer     &@R_FragmentBuffer
SetVar R_RxData.FragmentTable(0)          @R_FragmentTable

SetVar R_Packet_Buffer.RxData  &@R_RxData

SetVar R_Receive_IOToken.CompletionToken @R_Receive_CompletionToken
SetVar R_Receive_IOToken.Packet_Buffer   @R_Packet_Buffer
SetVar R_Receive_IOToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION

Tcp4->Receive {&@R_Receive_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Receive - Receive a packet."                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# OS get the ACK segment.
#
ReceiveTcpPacket TCB 5

#
# Check the Token.Status to verify the data has been transmitted successfully.
#
set timeout 60
set i       $timeout
while { 1 } {
  Stall 1
  incr  i  -1
  GetVar R_Receive_IOToken.CompletionToken.Status

  if { ${R_Receive_IOToken.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
    if { ${R_Receive_IOToken.CompletionToken.Status} == $EFI_SUCCESS} {
      RecordAssertion pass $Tcp4OptionsFunc4AssertionGuid004                   \
                      "EUT received data segment."                             \
      "ReturnStatus - ${R_Receive_IOToken.CompletionToken.Status}, ExpectedStatus - $EFI_SUCCESS"

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
      GetAck
      BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
      GetAck
#      BS->CloseEvent "@R_Receive_CompletionToken.Event, &@R_Status"
#      GetAck
      CleanUpEutEnvironmentEnd
      return
    } else {
      RecordAssertion pass $Tcp4OptionsFunc4AssertionGuid004                   \
                      "EUT discard data segment successfully."                 \
      "ReturnStatus - ${R_Receive_IOToken.CompletionToken.Status},             \
      ExpectedStatus - NOT $EFI_SUCCESS"
      break
    }
  } elseif { $i < 0 } {
    RecordAssertion pass $Tcp4OptionsFunc4AssertionGuid004                     \
                    "Discard data segment successfully. - Timeout, haven't receive data."\
    "ReturnStatus - ${R_Receive_IOToken.CompletionToken.Status},               \
    ExpectedStatus - NOT $EFI_SUCCESS"
    break
  }
}

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
GetAck
BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
GetAck
#BS->CloseEvent "@R_Receive_CompletionToken.Event, &@R_Status"
#GetAck
CleanUpEutEnvironmentEnd
