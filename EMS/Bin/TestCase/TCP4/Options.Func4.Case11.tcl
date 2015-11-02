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
CaseGuid          84911E3C-692F-491d-A149-5A526B5388CF
CaseName          Options.Func4.Case11
CaseCategory      TCP
CaseDescription   {This case is to test the Functionality.                     \
                   -- This case is designed to test that when [EUT] received   \
                   <SYN> segment without MSS option, [EUT] could take [OS]'s   \
                    MSS as RFC default value 536.                              \
                   -- With unaligned window scale option.                      \
                   -- format 2:                                                \
                     0            7           15           23           31     \
                     +------------+------------+------------+------------+     \
                     |   No-Oper  |   No-Oper  |  00000011  |  00000011  |     \
                     +------------+------------+------------+------------+     \
                     +------------+------------+------------+------------+     \
                     |  shift.cnt |   No-Oper  |   No-Oper  |   No-Oper  |     \
                     +------------+------------+------------+------------+}
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

BeginLogPacket Options.Func6.Case11 "host $DEF_EUT_IP_ADDR and host            \
                                             $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
set    L_FragmentLength          14600   ;# data to transmit by [EUT]
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
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
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
      RecordAssertion $assert $Tcp4OptionsFunc4AssertionGuid011                \
                      "Data transmission failed."                              \
                      "ReturnStatus - ${R_Transmit_IOToken.CompletionToken.Status},\
                       ExpectedStatus - $EFI_SUCCESS"

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

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
GetAck
BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
