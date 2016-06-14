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
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        D76E743A-BD6E-42a6-BB69-3CEB364F5384
CaseName        Transmit.Func1.Case1
CaseCategory    IP4
CaseDescription {Test the Transmit Function of IP4 - Invoke Transmit() to      \
                 transmit a unicast/multicast/broadcast packet}
################################################################################

Include IP4/include/Ip4.inc.tcl

proc CleanUpEutEnvironment {} {
  Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
  GetAck

  BS->CloseEvent "@R_Token.Event, &@R_Status"
  GetAck

  DestroyPacket
  EndCapture
  
  VifDown 0
  
  EndScope _IP4_TRANSMIT_FUNCTION1_CASE1_
  
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_TRANSMIT_FUNCTION1_CASE1_

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

VifUp 0 172.16.210.162 255.255.255.0

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_IP4_CONFIG_DATA              R_IpConfigData
UINTN                            R_Context
EFI_IP4_COMPLETION_TOKEN         R_Token
EFI_IP4_TRANSMIT_DATA            R_TxData
EFI_IP4_FRAGMENT_DATA            R_FragmentTable
CHAR8                            R_FragmentBuffer(1600)

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Transmit - Func - Create Child"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_IpConfigData.DefaultProtocol            0
SetVar R_IpConfigData.AcceptAnyProtocol          TRUE
SetVar R_IpConfigData.AcceptIcmpErrors           TRUE
SetVar R_IpConfigData.AcceptBroadcast            TRUE
SetVar R_IpConfigData.AcceptPromiscuous          TRUE
SetVar R_IpConfigData.UseDefaultAddress          FALSE
SetIpv4Address R_IpConfigData.StationAddress     "172.16.210.102"
SetIpv4Address R_IpConfigData.SubnetMask         "255.255.255.0"
SetVar R_IpConfigData.TypeOfService              0
SetVar R_IpConfigData.TimeToLive                 16
SetVar R_IpConfigData.DoNotFragment              TRUE
SetVar R_IpConfigData.RawData                    FALSE
SetVar R_IpConfigData.ReceiveTimeout             0
SetVar R_IpConfigData.TransmitTimeout            0

#
# check point
#
Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Func - Config Child"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

SetIpv4Address R_TxData.DestinationAddress "172.16.210.162"
SetVar R_TxData.TotalDataLength            40
SetVar R_TxData.FragmentCount              1

SetVar R_FragmentBuffer                    "IpConfigureTest"
SetVar R_FragmentTable.FragmentLength      40
SetVar R_FragmentTable.FragmentBuffer      &@R_FragmentBuffer
SetVar R_TxData.FragmentTable              @R_FragmentTable
SetVar R_Token.Packet                      &@R_TxData

#
# create an arp repquest packet to add an arp record in the EFI arp cache
#
CreatePacket arprepquest -t arp -arp_hrd 0x01 -arp_pro 0x0800 -arp_hln 6       \
	          -arp_pln 4 -arp_op 0x0001 -arp_sha $hostmac -arp_spa 172.16.210.162\
	           -arp_tha 0:0:0:0:0:0 -arp_tpa 172.16.210.102

SendPacket   arprepquest

set L_Filter "ip and src 172.16.210.102"
StartCapture CCB $L_Filter

Ip4->Transmit {&@R_Token, &@R_Status}

ReceiveCcbPacket CCB aaa 10
if { ${CCB.received} == 0} {
  GetAck
  GetVar R_Status
  GetVar R_Token.Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Ip4.Transmit - Func - Transmit a unicast packet"            \
                  "Packet not captured, R_Status - $R_Status, R_Token.Status - \
                  ${R_Token.Status}"
  
  CleanUpEutEnvironment
  
  return
}

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Func - Transmit a unicast packet"              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Token.Status
if {${R_Token.Status} == $EFI_SUCCESS} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Func - check R_Token"                          \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Context
if {$R_Context == 1} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Func - check Event"                            \
                "Return R_Context - $R_Context, Expected R_Context - 1"

DumpPacket    aaa
ParsePacket aaa -t eth -eth_src ETH_SRC
puts $ETH_SRC
ValidatePacket aaa -t ip "(ipv4_ver=4)AND(ipv4_ihl=5)AND(ipv4_tos=0)AND        \
                          (ipv4_frag=0x4000)AND(ipv4_ttl=16)AND(ipv4_prot=0)AND\
                          (ipv4_src=172.16.210.102)AND(ipv4_dst=172.16.210.162)"
if {[string compare -nocase $EMS_RESULT "TRUE"] == 0} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Ip4TransmitFunc1AssertionGuid001                      \
                        "Ip4.Transmit - Func - check packet field"

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

SetIpv4Address R_TxData.DestinationAddress "225.0.0.1"
SetVar R_TxData.TotalDataLength            40
SetVar R_TxData.FragmentCount              1

SetVar R_FragmentBuffer                    "IpConfigureTest"
SetVar R_FragmentTable.FragmentLength      40
SetVar R_FragmentTable.FragmentBuffer      &@R_FragmentBuffer
SetVar R_TxData.FragmentTable              @R_FragmentTable
SetVar R_Token.Packet                      &@R_TxData

#
# create an arp repquest packet to add an arp record in the EFI arp cache
#
CreatePacket arprepquest -t arp -arp_hrd 0x01 -arp_pro 0x0800 -arp_hln 6       \
	          -arp_pln 4 -arp_op 0x0001 -arp_sha $hostmac -arp_spa 172.16.210.162\
	           -arp_tha 0:0:0:0:0:0 -arp_tpa 172.16.210.102

SendPacket   arprepquest

Ip4->Transmit {&@R_Token, &@R_Status}

ReceiveCcbPacket CCB aaa 10
if { ${CCB.received} == 0} {
  GetAck
  GetVar R_Status
  GetVar R_Token.Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Ip4.Transmit - Func - Transmit a multicast packet"          \
                  "Packet not captured, R_Status - $R_Status, R_Token.Status - \
                  ${R_Token.Status}"

  CleanUpEutEnvironment

  return
}

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Func - Transmit a multicast packet"            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Token.Status
if {${R_Token.Status} == $EFI_SUCCESS} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Func - check R_Token"                          \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Context
if {$R_Context == 1} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Func - check Event"                            \
                "Return R_Context - $R_Context, Expected R_Context - 1"

DumpPacket  aaa
ParsePacket aaa -t eth -eth_src ETH_SRC
puts $ETH_SRC
ValidatePacket aaa -t ip "(ipv4_ver=4)AND(ipv4_ihl=5)AND(ipv4_tos=0)AND        \
                          (ipv4_frag=0x4000)AND(ipv4_ttl=16)AND(ipv4_prot=0)AND\
                          (ipv4_src=172.16.210.102)AND(ipv4_dst=225.0.0.1)"
if {[string compare -nocase $EMS_RESULT "TRUE"] == 0} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Ip4TransmitFunc1AssertionGuid002                      \
                        "Ip4.Transmit - Func - check packet field"

BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

SetIpv4Address R_TxData.DestinationAddress "172.16.210.255"
SetVar R_TxData.TotalDataLength            40
SetVar R_TxData.FragmentCount              1

SetVar R_FragmentBuffer                    "IpConfigureTest"
SetVar R_FragmentTable.FragmentLength      40
SetVar R_FragmentTable.FragmentBuffer      &@R_FragmentBuffer
SetVar R_TxData.FragmentTable              @R_FragmentTable
SetVar R_Token.Packet                      &@R_TxData

#
# create an arp repquest packet to add an arp record in the EFI arp cache
#
CreatePacket arprepquest -t arp -arp_hrd 0x01 -arp_pro 0x0800 -arp_hln 6       \
	          -arp_pln 4 -arp_op 0x0001 -arp_sha $hostmac -arp_spa 172.16.210.162\
	           -arp_tha 0:0:0:0:0:0 -arp_tpa 172.16.210.102

SendPacket   arprepquest

Ip4->Transmit {&@R_Token, &@R_Status}

ReceiveCcbPacket CCB aaa 10
if { ${CCB.received} == 0} {
  GetAck
  GetVar R_Status
  GetVar R_Token.Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Ip4.Transmit - Func - Transmit a broadcast packet"          \
                  "Packet not captured, R_Status - $R_Status, R_Token.Status - \
                  ${R_Token.Status}"

  CleanUpEutEnvironment

  return
}

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Func - Transmit a broadcast packet"            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Token.Status
if {${R_Token.Status} == $EFI_SUCCESS} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Func - check R_Token"                          \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Context
if {$R_Context == 1} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Func - check Event"                            \
                "Return R_Context - $R_Context, Expected R_Context - 1"

DumpPacket  aaa
ParsePacket aaa -t eth -eth_src ETH_SRC
puts $ETH_SRC
ValidatePacket aaa -t ip "(ipv4_ver=4)AND(ipv4_ihl=5)AND(ipv4_tos=0)AND        \
                         (ipv4_frag=0x4000)AND(ipv4_ttl=16)AND(ipv4_prot=0)AND \
                         (ipv4_src=172.16.210.102)AND(ipv4_dst=172.16.210.255)"
if {[string compare -nocase $EMS_RESULT "TRUE"] == 0} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Ip4TransmitFunc1AssertionGuid003                      \
                        "Ip4.Transmit - Func - check packet field"

CleanUpEutEnvironment
