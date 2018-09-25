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
CaseGuid          72969021-DDB2-4a7c-95CC-3234C59BE2A8
CaseName          CnntClosing.Func1.Case8
CaseCategory      TCP
CaseDescription   {This item is to test the [EUT] correctly support partner's  \
                   half-close.}
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

BeginLogPacket CnntClosing.Func1.Case4 "host $DEF_EUT_IP_ADDR and host         \
                                             $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
set    L_FragmentLength          536

UINTN                            R_Status
UINTN                            R_Tcp4Handle
UINTN                            R_Context

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData

EFI_TCP4_COMPLETION_TOKEN        R_Connect_CompletionToken
EFI_TCP4_CONNECTION_TOKEN        R_Connect_ConnectionToken

EFI_TCP4_IO_TOKEN                R_Transmit_IOToken
EFI_TCP4_COMPLETION_TOKEN        R_Transmit_CompletionToken

Packet                           R_Packet_Buffer
EFI_TCP4_TRANSMIT_DATA           R_TxData
EFI_TCP4_FRAGMENT_DATA           R_FragmentTable
CHAR8                            R_FragmentBuffer($L_FragmentLength)

EFI_TCP4_COMPLETION_TOKEN        R_Close_CompletionToken
EFI_TCP4_CLOSE_TOKEN             R_Close_CloseToken

#
# Initialization of TCB related on OS side.
#
CreateTcb TCB $DEF_ENTS_IP_ADDR $DEF_ENTS_PRT $DEF_EUT_IP_ADDR $DEF_EUT_PRT
CreatePayload HelloWorld STRING 11 HelloWorld

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
# Configure the [OS] to initiate the connection closing.
#
set L_TcpFlag [expr $FIN | $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag
SendTcpPacket TCB
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_ack} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out ACK segment to respond FIN segment correctly."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  } else {
      if { ${TCB.r_ack} != 2} {
        set assert fail
        RecordAssertion $assert $GenericAssertionGuid                          \
                        "The acknowledge number of ACK segment is not correct."

        CleanUpEutEnvironmentBegin
        BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
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
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

#
# Configure the [EUT] to send data segments to the [OS].
#

#
# Call Tcp4.Transmit to transmit a packet.
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

SetVar R_Transmit_IOToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION
SetVar R_Transmit_IOToken.CompletionToken @R_Transmit_CompletionToken
SetVar R_Transmit_IOToken.Packet_Buffer   @R_Packet_Buffer

Tcp4->Transmit {&@R_Transmit_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Transmit - Transmit a packet."                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# OS get the transmitted data packet.
#
ReceiveTcpPacket TCB 5
if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_ack} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out the first data segment correctly."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
    GetAck
    BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  } else {
      if { ${TCB.r_seq} != 1 || ${TCB.r_ack} != 2} {
        set assert fail
        RecordAssertion $assert $GenericAssertionGuid                          \
                        "The sequence number or acknowledge number of the first\
                         data segment is not correct."

        CleanUpEutEnvironmentBegin
        BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
        GetAck
        BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
        GetAck
        CleanUpEutEnvironmentEnd
        return
      }
      if { ${TCB.r_len} != 536 } {
       	set assert fail
        RecordAssertion $assert $GenericAssertionGuid                          \
                        "The data length of the first data segment is not correct"

        CleanUpEutEnvironmentBegin
        BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
        GetAck
        BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
        GetAck
        CleanUpEutEnvironmentEnd
        return
      }
    }
  set assert pass
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "The EUT send out the first data segment correctly."
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."

  CleanUpEutEnvironmentBegin
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}
UpdateTcpSendBuffer TCB -c $ACK
SendTcpPacket TCB

#
# Check the Token.Status to verify the data has been sent out.
#
while {1 > 0} {
  Stall 1
  GetVar R_Transmit_IOToken.CompletionToken.Status
 
  if { ${R_Transmit_IOToken.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
    if { ${R_Transmit_IOToken.CompletionToken.Status} != $EFI_SUCCESS} {
      set assert fail
      puts "Transmit data segments failed."
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "Graceful connection closing failed."                    \
                      "ReturnStatus - ${R_Transmit_IOToken.CompletionToken.Status},\
                       ExpectedStatus - $EFI_SUCCESS"

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
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
# Call Close interface to do close the connection.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Close_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Close_CloseToken.CompletionToken        @R_Close_CompletionToken
SetVar R_Close_CloseToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION
SetVar R_Close_CloseToken.AbortOnClose           FALSE

Tcp4->Close {&@R_Close_CloseToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp4CnntClosingFunc1AssertionGuid008                  \
                "Tcp4.Close - Close a connection."                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Hanlde the graceful close.
#
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_fin} != 1 || ${TCB.r_f_ack} != 1} {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out FIN segment correctly."

    CleanUpEutEnvironmentBegin
    BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
    GetAck
    CleanUpEutEnvironmentEnd
    return
  } else {
      if { ${TCB.r_seq} != 537 || ${TCB.r_ack} != 2} {
        set assert fail
        RecordAssertion $assert $GenericAssertionGuid                          \
                        "The sequence number or acknowledge number of ACK segment\
                         is not correct."

        CleanUpEutEnvironmentBegin
        BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
        GetAck
        BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
        GetAck
        BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
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
  BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
  GetAck
  BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
  GetAck
  CleanUpEutEnvironmentEnd
  return
}

UpdateTcpSendBuffer TCB -c $ACK
SendTcpPacket TCB

#
# Check the Token.Status to verify the connection has been closed.
#
while {1 > 0} {
  Stall 1
  GetVar R_Close_CloseToken.CompletionToken.Status
 
  if { ${R_Close_CloseToken.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
    if { ${R_Close_CloseToken.CompletionToken.Status} != $EFI_SUCCESS} {
      set assert fail
      puts "Graceful connection closing failed."
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "Graceful connection closing failed."                    \
                      "ReturnStatus - ${R_Close_CloseToken.CompletionToken.Status},\
                       ExpectedStatus - $EFI_SUCCESS"

      CleanUpEutEnvironmentBegin
      BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
      GetAck
      BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
      GetAck
      BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
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
BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
BS->CloseEvent "@R_Transmit_CompletionToken.Event, &@R_Status"
GetAck
BS->CloseEvent "@R_Close_CompletionToken.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
