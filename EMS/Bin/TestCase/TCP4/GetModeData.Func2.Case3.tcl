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
CaseName          GetModeData.Func2.Case3
CaseCategory      TCP
CaseDescription   {This case is to test the functionality -- To correctly get  \
Tcp4ConfigData.AccessPoint.}
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

BeginLogPacket GetModeData.Func3.Case3 "host $DEF_EUT_IP_ADDR and host         \
                                             $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
set L_Flag_UseDefaultAddress     FALSE
set L_Flag_ActiveFlag            TRUE

UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Tcp4State
UINTN                            R_Context

EFI_TCP4_CONFIG_DATA             R_Tcp4ConfigData
EFI_IP4_MODE_DATA                R_Ip4ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE          R_SnpModeData

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData

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
# Configure TCP instance.
#
SetVar          R_Configure_AccessPoint.UseDefaultAddress  $L_Flag_UseDefaultAddress
SetIpv4Address  R_Configure_AccessPoint.StationAddress     $DEF_EUT_IP_ADDR
SetIpv4Address  R_Configure_AccessPoint.SubnetMask         $DEF_EUT_MASK
SetVar          R_Configure_AccessPoint.StationPort        $DEF_EUT_PRT
SetIpv4Address  R_Configure_AccessPoint.RemoteAddress      $DEF_ENTS_IP_ADDR
SetVar          R_Configure_AccessPoint.RemotePort         $DEF_ENTS_PRT
SetVar          R_Configure_AccessPoint.ActiveFlag         $L_Flag_ActiveFlag

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
#              to correctly get the Tcp4ConfigData.AccessPoint.
#
Tcp4->GetModeData {&@R_Tcp4State, &@R_Tcp4ConfigData, &@R_Ip4ModeData,         \
                   &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp4GetModeDataFunc2AssertionGuid003                  \
                "Tcp4.GetModeData - Call GetModeData() to correctly get the    \
                 Tcp4ConfigData.AccessPoint."                                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Tcp4ConfigData

#
# Check: Tcp4ConfigData.AccessPoint.UseDefaultAddress
#
set UseDefaultAddress  ${R_Tcp4ConfigData.AccessPoint.UseDefaultAddress}
if {[string compare -nocase $UseDefaultAddress $L_Flag_UseDefaultAddress] != 0} {
  puts "AccessPoint.UseDefaultAddress = ${R_Tcp4ConfigData.AccessPoint.UseDefaultAddress}\n"
  puts "L_Flag_UseDefaultAddress = $L_Flag_UseDefaultAddress\n"
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "AccessPoint.UseDefaultAddress was not the same that configured before."
}

#
# Check: Tcp4ConfigData.AccessPoint.StationAddress
#
set StationAddress [GetIpv4Address R_Tcp4ConfigData.AccessPoint.StationAddress]
if {[string compare -nocase $StationAddress $DEF_EUT_IP_ADDR] != 0} {
  puts "AccessPoint.StationAddress = $StationAddress\n"
  puts "DEF_EUT_IP_ADDR = $DEF_EUT_IP_ADDR\n"
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "AccessPoint.StationAddress was not the same that configured before."
}

#
# Check: Tcp4ConfigData.AccessPoint.SubnetMask
#
set SubnetMask [GetIpv4Address R_Tcp4ConfigData.AccessPoint.SubnetMask]
if {[string compare -nocase $SubnetMask $DEF_EUT_MASK] != 0} {
  puts "AccessPoint.SubnetMask = $SubnetMask\n"
  puts "DEF_EUT_MASK = $DEF_EUT_MASK\n"
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "AccessPoint.SubnetMask was not the same that configured before."
}

#
# Check: Tcp4ConfigData.AccessPoint.StationPort
#
if {${R_Tcp4ConfigData.AccessPoint.StationPort} != $DEF_EUT_PRT} {
  puts "AccessPoint.StationPort = ${R_Tcp4ConfigData.AccessPoint.StationPort}\n"
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "AccessPoint.StationPort was not the same that configured before."
}

#
# Check: Tcp4ConfigData.AccessPoint.RemoteAddress
#
set RemoteAddress [GetIpv4Address R_Tcp4ConfigData.AccessPoint.RemoteAddress]
if {[string compare -nocase $RemoteAddress $DEF_ENTS_IP_ADDR] != 0} {
  puts "AccessPoint.RemoteAddress = $RemoteAddress\n"
  puts "DEF_EUT_MASK = $DEF_EUT_MASK\n"
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "AccessPoint.RemoteAddress was not the same that configured before."
}

#
# Check: Tcp4ConfigData.AccessPoint.RemotePort
#
if {${R_Tcp4ConfigData.AccessPoint.RemotePort} != $DEF_ENTS_PRT} {
  puts "AccessPoint.RemotePort = ${R_Tcp4ConfigData.AccessPoint.RemotePort}\n"
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "AccessPoint.RemotePort was not the same that configured before."
}

#
# Check: Tcp4ConfigData.AccessPoint.ActiveFlag
#
set ActiveFlag  ${R_Tcp4ConfigData.AccessPoint.ActiveFlag}
if {[string compare -nocase $ActiveFlag $L_Flag_ActiveFlag] != 0} {
  puts "AccessPoint.ActiveFlag = ${R_Tcp4ConfigData.AccessPoint.ActiveFlag}\n"
  puts "L_Flag_ActiveFlag = $L_Flag_ActiveFlag\n"
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "AccessPoint.ActiveFlag was not the same that configured before."
}

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
