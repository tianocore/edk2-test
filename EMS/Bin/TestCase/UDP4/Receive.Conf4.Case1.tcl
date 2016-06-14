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
CaseLevel         CONFORMANCE 
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT 
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        FFBA4112-D57A-485e-A8F9-78292A3CB9D5
CaseName        Receive.Conf4.Case1
CaseCategory    Udp4
CaseDescription {Test the Receive Conformance of UDP4 - EFI_NETWORK_UNREACHABLE\
	               EFI_HOST_UNREACHABLE/EFI_PROTOCOL_UNREACHABLE/EFI_PORT_UNREACHABLE\
	               EFI_ICMP_ERROR --- The receiving fails because an ICMP error\
	               packet is received.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _UDP4_RECEIVE_CONFORMANCE4_CASE1_

set hostmac       [GetHostMac]
set targetmac     [GetTargetMac]
set targetip      192.168.88.88
set hostip        192.168.88.1
set subnetmask    255.255.255.0
set targetport    4000
set hostport      4000

VifUp 0 $hostip
#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                             R_Status
UINTN                             R_PollStatus
UINTN                             R_Handle
EFI_UDP4_CONFIG_DATA              R_Udp4ConfigData
UINTN                             R_Context
EFI_UDP4_COMPLETION_TOKEN         R_Token

Udp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar   [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SBP.Receive - Conf - Create Child"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Udp4ConfigData.AcceptBroadcast             FALSE
SetVar R_Udp4ConfigData.AcceptPromiscuous           FALSE
SetVar R_Udp4ConfigData.AcceptAnyPort               FALSE
SetVar R_Udp4ConfigData.AllowDuplicatePort          FALSE
SetVar R_Udp4ConfigData.TypeOfService               0
SetVar R_Udp4ConfigData.TimeToLive                  1
SetVar R_Udp4ConfigData.DoNotFragment               TRUE
SetVar R_Udp4ConfigData.ReceiveTimeout              0
SetVar R_Udp4ConfigData.TransmitTimeout             0
SetVar R_Udp4ConfigData.UseDefaultAddress           FALSE
SetIpv4Address R_Udp4ConfigData.StationAddress      $targetip
SetIpv4Address R_Udp4ConfigData.SubnetMask          $subnetmask
SetVar R_Udp4ConfigData.StationPort                 $targetport
SetIpv4Address R_Udp4ConfigData.RemoteAddress       $hostip
SetVar R_Udp4ConfigData.RemotePort                  $hostport

CreatePayload icmppayload data 28 0x45 0x00 0x00 0x2e 0x00 0x00 0x00 0x00 0x10 \
                                  0x11 0x00 0x00 0xc0 0xa8 0x58 0x58 0xc0 0xa8 \
                                  0x58 0x01 0x0f 0xa0 0x0f 0xa0 0x00 0x00 0x00 \
                                  0x00
#
# check point
#
Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - Config Child"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# NETWORK UNREACHABLE
#                                 
LocalEther  $hostmac
RemoteEther $targetmac
LocalIp     $hostip
RemoteIp    $targetip                              
CreatePacket icmppacket1 -t icmp -icmp_type 3 -icmp_code 0 -icmp_orig_len 66    \
               -icmp_orig_tos 0 -icmp_orig_id 0x017b -icmp_orig_frag 0         \
               -icmp_orig_ttl 255 -icmp_orig_prot 0x11 -icmp_orig_check 0x8885 \
               -icmp_orig_src 192.168.88.88 -icmp_orig_dst 192.168.88.1        \
               -icmp_payload icmppayload    

# Send ICMP packet 
SendPacket icmppacket1
Stall      1

SetVar R_Context 0                
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

Udp4->Receive {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - Receive a packet"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                

GetVar R_Context
if {$R_Context == 1} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - Check Event"                             \
                "Return R_Context - $R_Context, Expected R_Context - 1"   
                       
GetVar R_Token.Status
if {${R_Token.Status} == $EFI_NETWORK_UNREACHABLE} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Udp4ReceiveConf4AssertionGuid001                      \
                "Udp4.Receive - Conf - Check R_Token"                           \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_NETWORK_UNREACHABLE"

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

#
# HOST UNREACHABLE
#
CreatePacket icmppacket2 -t icmp -icmp_type 3 -icmp_code 1 -icmp_orig_len 66    \
               -icmp_orig_tos 0 -icmp_orig_id 0x017b -icmp_orig_frag 0         \
               -icmp_orig_ttl 255 -icmp_orig_prot 0x11 -icmp_orig_check 0x8885 \
               -icmp_orig_src 192.168.88.88 -icmp_orig_dst 192.168.88.1        \
               -icmp_payload icmppayload  

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

Udp4->Receive {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - Receive a packet"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                
SendPacket icmppacket2
Stall      1
GetVar R_Context
if {$R_Context == 1} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - Check Event"                             \
                "Return R_Context - $R_Context, Expected R_Context - 1"   
                       
GetVar R_Token.Status
if {${R_Token.Status} == $EFI_HOST_UNREACHABLE} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Udp4ReceiveConf4AssertionGuid002                      \
                "Udp4.Receive - Conf - Check R_Token"                           \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_HOST_UNREACHABLE"

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck               

#
# PROTOCOL UNREACHABLE
#
CreatePacket icmppacket3 -t icmp -icmp_type 3 -icmp_code 2 -icmp_orig_len 66    \
               -icmp_orig_tos 0 -icmp_orig_id 0x017b -icmp_orig_frag 0         \
               -icmp_orig_ttl 255 -icmp_orig_prot 0x11 -icmp_orig_check 0x8885 \
               -icmp_orig_src 192.168.88.88 -icmp_orig_dst 192.168.88.1        \
               -icmp_payload icmppayload  

SendPacket icmppacket3

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

Udp4->Receive {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - Receive a packet"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                

GetVar R_Context
if {$R_Context == 1} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - Check Event"                             \
                "Return R_Context - $R_Context, Expected R_Context - 1"   
                       
GetVar R_Token.Status
if {${R_Token.Status} == $EFI_PROTOCOL_UNREACHABLE} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Udp4ReceiveConf4AssertionGuid003                      \
                "Udp4.Receive - Conf - Check R_Token"                           \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_PROTOCOL_UNREACHABLE"

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck  

#
# PORT UNREACHALE
#
CreatePacket icmppacket4 -t icmp -icmp_type 3 -icmp_code 3 -icmp_orig_len 66    \
               -icmp_orig_tos 0 -icmp_orig_id 0x017b -icmp_orig_frag 0         \
               -icmp_orig_ttl 255 -icmp_orig_prot 0x11 -icmp_orig_check 0x8885 \
               -icmp_orig_src 192.168.88.88 -icmp_orig_dst 192.168.88.1        \
               -icmp_payload icmppayload  

SendPacket icmppacket4

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

Udp4->Receive {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - Receive a packet"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                
GetVar R_Context
if {$R_Context == 1} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - Check Event"                             \
                "Return R_Context - $R_Context, Expected R_Context - 1"   
                       
GetVar R_Token.Status
if {${R_Token.Status} == $EFI_PORT_UNREACHABLE} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Udp4ReceiveConf4AssertionGuid004                      \
                "Udp4.Receive - Conf - Check R_Token"                           \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_PORT_UNREACHABLE"

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck  

#
# ICMP ERROR
#
CreatePacket icmppacket5 -t icmp -icmp_type 3 -icmp_code 4 -icmp_orig_len 66    \
               -icmp_orig_tos 0 -icmp_orig_id 0x017b -icmp_orig_frag 0         \
               -icmp_orig_ttl 255 -icmp_orig_prot 0x11 -icmp_orig_check 0x8885 \
               -icmp_orig_src 192.168.88.88 -icmp_orig_dst 192.168.88.1        \
               -icmp_payload icmppayload  

SendPacket icmppacket5

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

Udp4->Receive {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - Receive a packet"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                
GetVar R_Context
if {$R_Context == 1} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - Check Event"                             \
                "Return R_Context - $R_Context, Expected R_Context - 1"   
                       
GetVar R_Token.Status
if {${R_Token.Status} == $EFI_ICMP_ERROR} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Udp4ReceiveConf4AssertionGuid005                      \
                "Udp4.Receive - Conf - Check R_Token"                          \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_ICMP_ERROR"

#
# Call SignalRecycleEvent to recycle receive buffer
#
Udp4->SignalRecycleEvent {&@R_Token, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Receive - Conf - SignalRecycleEvent"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

VifDown 0
#
# EndScope
#
EndScope _UDP4_RECEIVE_CONFORMANCE4_CASE1_

#
#End Log
#
EndLog
