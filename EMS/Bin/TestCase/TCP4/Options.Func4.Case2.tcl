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
CaseGuid          3DFBEC24-1B8E-44de-A2AF-650826CB175C
CaseName          Options.Func4.Case2
CaseCategory      TCP
CaseDescription   {This case is to test the Functionality.                     \
                   -- This item is to test the [EUT] correctly receives MSS    \
                   option in <SYN> segment, and then replies to transmit MSS   \
                   option in <SYN, ACK> segment correctly.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironment {} {
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

  BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
  GetAck

  EndLogPacket
  EndScope _TCP4_SPEC_CONFORMANCE_
  EndLog
}

#
# Begin log ...
#
BeginLog


#
# BeginScope
#
BeginScope _TCP4_SPEC_CONFORMANCE_

BeginLogPacket Options.Func6.Case2 "host $DEF_EUT_IP_ADDR and host             \
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
EFI_IP4_MODE_DATA                R_Ip4ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE          R_SnpModeData

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData

EFI_TCP4_LISTEN_TOKEN            R_Accept_ListenToken
UINTN                            R_Accept_NewChildHandle
EFI_TCP4_COMPLETION_TOKEN        R_Accept_CompletionToken

#
# Build TCP Segment with MSS OPTION, here MSS = 256
#
CreatePayload OptionMSS Data 4 0x02 0x04 0x01 0x00

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
SetVar          R_Configure_AccessPoint.ActiveFlag         FALSE

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

set L_TcpFlag [expr $SYN]
UpdateTcpSendBuffer TCB -c $L_TcpFlag -o OptionMSS
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
# OS get <SYN, ACK> segment
#
ReceiveTcpPacket TCB 5

if { ${TCB.received} == 1 } {
  if { ${TCB.r_f_syn} != 1 && ${TCB.r_f_ack} != 1 } {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "EUT doesn't send out SYN & ACK segment correctly."
    CleanUpEutEnvironment
    return
  } else {
    if { ${TCB.r_mss} <= 0 || ${TCB.r_mss} >1460 } {
      puts "{TCB.r_mss} = ${TCB.r_mss}"
      RecordAssertion fail $GenericAssertionGuid                               \
                      "EUT send out MSS option in SYN & ACK segment wrongly."
    } else {
      # correct
      RecordAssertion pass $GenericAssertionGuid                               \
                      "EUT send out MSS option in SYN & ACK segment correctly."
    }
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."
  CleanUpEutEnvironment
  return
}

#
# OS send <ACK> segment
#
UpdateTcpSendBuffer TCB -c $ACK
SendTcpPacket TCB

#
# Get the NewChildHandle value.
#
GetVar R_Accept_ListenToken.NewChildHandle
SetVar R_Accept_NewChildHandle ${R_Accept_ListenToken.NewChildHandle}
SetVar [subst $ENTS_CUR_CHILD]  @R_Accept_NewChildHandle

#
# Check the Token.Status to verify the Accept connection has been completed.
#
while {1} {
  Stall 1
  GetVar R_Accept_ListenToken.CompletionToken.Status

  if { ${R_Accept_ListenToken.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
    if { ${R_Accept_ListenToken.CompletionToken.Status} != $EFI_SUCCESS} {
      set assert fail
      RecordAssertion $assert $Tcp4OptionsFunc4AssertionGuid002                \
                              "Transmission failed."                           \
                              "ReturnStatus - ${R_Accept_ListenToken.CompletionToken.Status},\
                               ExpectedStatus - $EFI_SUCCESS"
      CleanUpEutEnvironment
      return
    } else {
    	set assert pass
      RecordAssertion $assert $Tcp4OptionsFunc4AssertionGuid002                \
                              "Transmission successfully."                     \
                              "ReturnStatus - ${R_Accept_ListenToken.CompletionToken.Status},\
                               ExpectedStatus - $EFI_SUCCESS"
      CleanUpEutEnvironment
      return
    }
  }
}

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment
