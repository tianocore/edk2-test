# 
#  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
#  Copyright (c) 2011, Intel Corporation. All rights reserved.<BR>
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
CaseGuid          03683075-D99D-45d2-8F4F-44221646F063
CaseName          Accept.Func2.Case1
CaseCategory      TCP
CaseDescription   {This case is to test the Functionality.   \
                  -- RST recevied in SYN-RECEIVED State      \
                  in passive mode connection.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  global RST
  UpdateTcpSendBuffer TCB -c $RST
  SendTcpPacket TCB

  DestroyTcb
  DelEntryInArpCache

  Tcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  Tcp4ServiceBinding->DestroyChild "@R_Accept_NewChildHandle, &@R_Status"
  GetAck

  BS->CloseEvent "@R_Accept_CompletionToken.Event, &@R_Status"
  GetAck

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

BeginLogPacket Accept.Func1.Case1 "host $DEF_EUT_IP_ADDR and host              \
                                             $DEF_ENTS_IP_ADDR"
#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Context
UINTN                            R_Accept_NewChildHandle

EFI_TCP4_CONFIG_DATA             R_Tcp4ConfigData
EFI_IP4_MODE_DATA                R_Ip4ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE          R_SnpModeData

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData

EFI_TCP4_LISTEN_TOKEN            R_Accept_ListenToken
EFI_TCP4_COMPLETION_TOKEN        R_Accept_CompletionToken

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

#
# Check Point: Call Tcp4.Accept() to Listen on the passive instance to accept
#              an incoming connection request.
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
RecordAssertion $assert $GenericAssertionGuid                       \
                "Tcp4.Accept - Accept a connection."                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

UpdateTcpSendBuffer TCB -c $SYN
SendTcpPacket TCB

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
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."
  CleanUpEutEnvironment
  return
}

UINTN    State
Tcp4->GetModeData "&@State, NULL, NULL, NULL, NULL, &@R_Status"
GetAck
GetVar    State
RecordMessage DEFAULT "Parent State: $State. Expect State: 0x01"

#
# send a RST, SYN-RCV is expect to go back to listen state
#
UpdateTcpSendBuffer TCB -c $RST
SendTcpPacket TCB

Tcp4->GetModeData "&@State, NULL, NULL, NULL, NULL, &@R_Status"
GetAck
GetVar State

GetVar R_Accept_ListenToken.CompletionToken.Status
if {${R_Accept_ListenToken.CompletionToken.Status} == $EFI_INCOMPATIBLE_VERSION} {
  if {$State == 0x01} {
    set assert pass
  } else {
    set assert fail
  }
} else {
  set assert fail
}

RecordAssertion $assert $Tcp4AcceptFunc2AssertionGuid001                            \
                      "Accept completion token status should beunchanged."        \
                      "Status - ${R_Accept_ListenToken.CompletionToken.Status},\
                       ExpectedStatus - $EFI_INCOMPATIBLE_VERSION. \
                       Parent TCB State: $State. Expect State: 0x01"   
                        
UpdateTcpSendBuffer TCB -c $SYN
SendTcpPacket TCB

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
  }
} else {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."
  CleanUpEutEnvironment
  return
}

Tcp4->GetModeData "&@State, NULL, NULL, NULL, NULL, &@R_Status"
GetAck
GetVar State
RecordMessage DEFAULT "State $State. Expect State: 0x01"

#
# OS send <ACK> segment
#
UpdateTcpSendBuffer TCB -c $ACK
SendTcpPacket TCB

#
# Check the Token.Status to verify the Tcp4->Accept() has completed.
#
while {1} {
  Stall 1
  GetVar R_Accept_ListenToken.CompletionToken.Status

  if { ${R_Accept_ListenToken.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} {
    if { ${R_Accept_ListenToken.CompletionToken.Status} != $EFI_SUCCESS} {
      set assert fail
      RecordAssertion $assert $Tcp4AcceptFunc1AssertionGuid003                            \
                      "passive mode connection creation failed."               \
                      "ReturnStatus - ${R_Accept_ListenToken.CompletionToken.Status},\
                       ExpectedStatus - $EFI_SUCCESS"
      CleanUpEutEnvironment
      return
    } else {
      set assert pass
      RecordAssertion $assert $Tcp4AcceptFunc2AssertionGuid002                           \
                      "passive mode connection creation success."                      \
                      "Status - ${R_Accept_ListenToken.CompletionToken.Status},\
                       ExpectedStatus - $EFI_SUCCESS"

      break
    }
  }
}


SetVar R_Accept_NewChildHandle 0

#
# Get the NewChildHandle value.
#
GetVar R_Accept_ListenToken.NewChildHandle
SetVar R_Accept_NewChildHandle ${R_Accept_ListenToken.NewChildHandle}

#
# Switch to new created TCP child handler
#
GetVar R_Accept_NewChildHandle
SetVar CurrentChild $R_Accept_NewChildHandle

Tcp4->GetModeData "&@State, NULL, NULL, NULL, NULL, &@R_Status"
GetAck
GetVar    State
if {$State == 0x04} {
  set assert pass
} else {
  set assert fail
} 
RecordAssertion $assert $Tcp4AcceptFunc2AssertionGuid003                            \
                "New created TCB is now connected."     \
                "GetModeData show TCB current Status - $State,\
                ExpectedStatus - 0x04"

#
# Restore to old TCP child handler
#
GetVar R_Handle
SetVar CurrentChild $R_Handle

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment


