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
CaseGuid          200BBFC7-3E68-4a0c-AC1A-16A5859EA3C5
CaseName          GetModeData.Func2.Case4
CaseCategory      TCP
CaseDescription   {This case is to test the functionality -- To correctly get  \
Tcp4ConfigData.ControlOption.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  global RST
  UpdateTcpSendBuffer TCB -c $RST
  SendTcpPacket TCB

  DestroyTcb
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

BeginLogPacket GetModeData.Func3.Case4 "host $DEF_EUT_IP_ADDR and host         \
                                             $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
set L_ControlOption_ReceiveBufferSize       102400
set L_ControlOption_SendBufferSize          102400
set L_ControlOption_MaxSynBackLog           8
set L_ControlOption_ConnectionTimeout       75
set L_ControlOption_DataRetries             10
set L_ControlOption_FinTimeout              2
set L_ControlOption_KeepAliveProbes         4
set L_ControlOption_KeepAliveTime           10800
set L_ControlOption_KeepAliveInterval       60
set L_ControlOption_EnableNagle             TRUE
set L_ControlOption_EnableTimeStamp         TRUE
set L_ControlOption_EnableWindowScaling     TRUE

UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Tcp4State
UINTN                            R_Context

EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData
EFI_IP4_MODE_DATA                R_Ip4ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE          R_SnpModeData

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_OPTION                  R_Configure_ControlOption
EFI_TCP4_OPTION                  R_TCP4_Option
UINTN                            R_SIZE_TCP4_OPTION

EFI_TCP4_COMPLETION_TOKEN        R_Connect_CompletionToken
EFI_TCP4_CONNECTION_TOKEN        R_Connect_ConnectionToken

#
# Initialization of TCB related on ENTS side.
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
#
# Call Tcp.Configrue() with TCP Option,
# SACK & MTU is not supported in EFI TCP at present(2005-5-8).
#
SetVar R_Configure_ControlOption.ReceiveBufferSize    $L_ControlOption_ReceiveBufferSize
SetVar R_Configure_ControlOption.SendBufferSize       $L_ControlOption_SendBufferSize
SetVar R_Configure_ControlOption.MaxSynBackLog        $L_ControlOption_MaxSynBackLog
SetVar R_Configure_ControlOption.ConnectionTimeout    $L_ControlOption_ConnectionTimeout
SetVar R_Configure_ControlOption.DataRetries          $L_ControlOption_DataRetries
SetVar R_Configure_ControlOption.FinTimeout           $L_ControlOption_FinTimeout
SetVar R_Configure_ControlOption.KeepAliveProbes      $L_ControlOption_KeepAliveProbes
SetVar R_Configure_ControlOption.KeepAliveTime        $L_ControlOption_KeepAliveTime
SetVar R_Configure_ControlOption.KeepAliveInterval    $L_ControlOption_KeepAliveInterval
SetVar R_Configure_ControlOption.EnableNagle          $L_ControlOption_EnableNagle
SetVar R_Configure_ControlOption.EnableTimeStamp      $L_ControlOption_EnableTimeStamp
SetVar R_Configure_ControlOption.EnableWindowScaling  $L_ControlOption_EnableWindowScaling

SetVar R_Configure_Tcp4ConfigData.ControlOption       &@R_Configure_ControlOption

Tcp4->Configure {&@R_Configure_Tcp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Configure - Configure Child 1."                  \
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

set L_TcpFlag [expr $SYN | $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag
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

#
# Check Point: Calling Tcp4.GetModeData(),
#              to correctly get the Tcp4ConfigData.ControlOption.
#
Tcp4->GetModeData {&@R_Tcp4State, &@R_Configure_Tcp4ConfigData, &@R_Ip4ModeData,
                   &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp4GetModeDataFunc2AssertionGuid004                  \
                "Tcp4.GetModeData - Call GetModeData() to correctly get the    \
                 Tcp4ConfigData.ControlOption."                                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Get Rivl Variable, a POINT: R_Configure_Tcp4ConfigData.ControlOption
#
GetVar R_Configure_Tcp4ConfigData.ControlOption

#
# Copy *@R_Configure_Tcp4ConfigData.ControlOption to @R_TCP4_Option
#
SetVar  R_SIZE_TCP4_OPTION          [Sizeof EFI_TCP4_OPTION]

BS->CopyMem {&@R_TCP4_Option, @R_Configure_Tcp4ConfigData.ControlOption,       \
             @R_SIZE_TCP4_OPTION, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CopyMem - Copy Memory."                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# Get Rivl Variable R_TCP4_Option
#
GetVar R_TCP4_Option
#
# Check options one by one
#
if {${R_TCP4_Option.ReceiveBufferSize} != $L_ControlOption_ReceiveBufferSize} {
    puts "Tcp4ConfigData.ControlOption.ReceiveBufferSize = ${R_TCP4_Option.ReceiveBufferSize}\n"
    puts "L_ControlOption_ReceiveBufferSize = $L_ControlOption_ReceiveBufferSize\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.ReceiveBufferSize was not the same that configured before."
}
if {${R_TCP4_Option.SendBufferSize} != $L_ControlOption_SendBufferSize} {
    puts "Tcp4ConfigData.ControlOption.SendBufferSize = ${R_TCP4_Option.SendBufferSize}\n"
    puts "L_ControlOption_SendBufferSize = $L_ControlOption_SendBufferSize\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.SendBufferSize was not the same that configured before."
}
if {${R_TCP4_Option.MaxSynBackLog} != $L_ControlOption_MaxSynBackLog} {
    puts "Tcp4ConfigData.ControlOption.MaxSynBackLog = ${R_TCP4_Option.MaxSynBackLog}\n"
    puts "L_ControlOption_MaxSynBackLog = $L_ControlOption_MaxSynBackLog\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.MaxSynBackLog was not the same that configured before."
}
if {${R_TCP4_Option.ConnectionTimeout} != $L_ControlOption_ConnectionTimeout} {
    puts "Tcp4ConfigData.ControlOption.ConnectionTimeout = ${R_TCP4_Option.ConnectionTimeout}\n"
    puts "L_ControlOption_ConnectionTimeout = $L_ControlOption_ConnectionTimeout\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.ConnectionTimeout was not the same that configured before."
}
if {${R_TCP4_Option.DataRetries} != $L_ControlOption_DataRetries} {
    puts "Tcp4ConfigData.ControlOption.DataRetries = ${R_TCP4_Option.DataRetries}\n"
    puts "L_ControlOption_DataRetries = $L_ControlOption_DataRetries\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.DataRetries was not the same that configured before."
}
if {${R_TCP4_Option.FinTimeout} != $L_ControlOption_FinTimeout} {
    puts "Tcp4ConfigData.ControlOption.FinTimeout = ${R_TCP4_Option.FinTimeout}\n"
    puts "L_ControlOption_FinTimeout = $L_ControlOption_FinTimeout\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.FinTimeout was not the same that configured before."
}
if {${R_TCP4_Option.KeepAliveProbes}!= $L_ControlOption_KeepAliveProbes} {
    puts "Tcp4ConfigData.ControlOption.KeepAliveProbes = ${R_TCP4_Option.KeepAliveProbes}\n"
    puts "L_ControlOption_KeepAliveProbes = $L_ControlOption_KeepAliveProbes\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.KeepAliveProbes was not the same that configured before."
}
if {${R_TCP4_Option.KeepAliveTime} != $L_ControlOption_KeepAliveTime} {
    puts "Tcp4ConfigData.ControlOption.KeepAliveTime = ${R_TCP4_Option.KeepAliveTime}\n"
    puts "L_ControlOption_KeepAliveTime = $L_ControlOption_KeepAliveTime\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.KeepAliveTime was not the same that configured before."
}
if {${R_TCP4_Option.KeepAliveInterval}!= $L_ControlOption_KeepAliveInterval} {
    puts "Tcp4ConfigData.ControlOption.KeepAliveInterval = ${R_TCP4_Option.KeepAliveInterval}\n"
    puts "L_ControlOption_KeepAliveInterval = $L_ControlOption_KeepAliveInterval\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.KeepAliveInterval was not the same that configured before."
}
set EnableNagle ${R_TCP4_Option.EnableNagle}
if {[string compare -nocase $EnableNagle $L_ControlOption_EnableNagle] != 0} {
    puts "Tcp4ConfigData.ControlOption.EnableNagle = ${R_TCP4_Option.EnableNagle}\n"
    puts "L_ControlOption_EnableNagle = $L_ControlOption_EnableNagle\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.EnableNagle was not the same that configured before."
}
set EnableTimeStamp ${R_TCP4_Option.EnableTimeStamp}
if {[string compare -nocase $EnableTimeStamp $L_ControlOption_EnableTimeStamp] != 0} {
    puts "Tcp4ConfigData.ControlOption.EnableTimeStamp = ${R_TCP4_Option.EnableTimeStamp}\n"
    puts "L_ControlOption_EnableTimeStamp = $L_ControlOption_EnableTimeStamp\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.EnableTimeStamp was not the same that configured before."
}
set EnableWindowScaling ${R_TCP4_Option.EnableWindowScaling}
if {[string compare -nocase $EnableWindowScaling $L_ControlOption_EnableTimeStamp] != 0} {
    puts "Tcp4ConfigData.ControlOption.EnableWindowScaling = ${R_TCP4_Option.EnableWindowScaling}\n"
    puts "L_ControlOption_EnableWindowScaling = $L_ControlOption_EnableWindowScaling\n"
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "ControlOption.EnableWindowScaling was not the same that configured before."
}

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
