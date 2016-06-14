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
CaseGuid        5879D777-EE67-400b-9228-6ACD30BFBF83
CaseName        Transmit.Func1.Case1
CaseCategory    IP6
CaseDescription {Test the Transmit Function of IP6 - Invoke Transmit() \
                 to transmit data.}
################################################################################

Include IP6/include/Ip6.inc.tcl

proc CleanUpEutEnvironment {} {
  Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  BS->CloseEvent "@R_Token.Event, &@R_Status"
  GetAck

  DestroyPacket
  EndCapture
  
  EndScope _IP6_TRANSMIT_FUNCTION1_CASE1_
  
  EndLog
}

#
# Begin Log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope   _IP6_TRANSMIT_FUNCTION1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Create child.
#
Ip6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Ip6SB.CreateChild - Create Child 1"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar [subst $ENTS_CUR_CHILD]          @R_Handle

#
# Address Configuration
#
UINTN                                       R_Ip6ConfigDataSize
UINT32                                      R_Ip6ConfigDataType
UINT32                                      R_Ip6ConfigPolicy
EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS    R_Ip6ConfigDadTransmits
EFI_IP6_CONFIG_MANUAL_ADDRESS               R_Ip6ConfigManualAddress

SetVar R_Ip6ConfigDataType   2
SetVar R_Ip6ConfigDataSize   4
SetVar R_Ip6ConfigPolicy     $IP6CP(Manual)
  
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigPolicy,&@R_Status"
GetAck

SetVar R_Ip6ConfigDataType   3
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS]
SetVar R_Ip6ConfigDadTransmits.DupAddrDetectTransmits 0
  
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigDadTransmits,&@R_Status"
GetAck
  
SetVar R_Ip6ConfigDataType   4
SetVar R_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_MANUAL_ADDRESS]
SetVar R_Ip6ConfigManualAddress.IsAnycast    FALSE
SetVar R_Ip6ConfigManualAddress.PrefixLength 64
SetIpv6Address R_Ip6ConfigManualAddress.Address $DEF_EUT_IP_ADDR
puts $DEF_EUT_IP_ADDR
Ip6Config->SetData "@R_Ip6ConfigDataType,@R_Ip6ConfigDataSize,&@R_Ip6ConfigManualAddress,&@R_Status"
GetAck

EFI_IP6_CONFIG_DATA                           R_Ip6ConfigData
SetVar R_Ip6ConfigData.DefaultProtocol        0x11;        #Next Header: UDP
SetVar R_Ip6ConfigData.AcceptAnyProtocol      FALSE
SetVar R_Ip6ConfigData.AcceptIcmpErrors       TRUE
SetVar R_Ip6ConfigData.AcceptPromiscuous      FALSE
SetIpv6Address R_Ip6ConfigData.DestinationAddress     "::"
SetIpv6Address R_Ip6ConfigData.StationAddress         "2002::4321"
SetVar R_Ip6ConfigData.TrafficClass           0
SetVar R_Ip6ConfigData.HopLimit               64
SetVar R_Ip6ConfigData.FlowLabel              0
SetVar R_Ip6ConfigData.ReceiveTimeout         50000
SetVar R_Ip6ConfigData.TransmitTimeout        50000

#
# Configure this child with valid parameter.
#
Ip6->Configure "&@R_Ip6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Ip6.Configure - Func - Configure child with valid parameter"     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Add a Neighbor cache
# Call Neighbors with 
#                         DeleteFlag = FALSE
#                         TargetIp6Address = 
#                         TargetLinkAddress = 
#                         Timeout = 0
#                         Override = TRUE
#              EFI_SUCCESS should be returned.
#
EFI_IPv6_ADDRESS                              R_TargetIp6Address
SetIpv6Address R_TargetIp6Address             $DEF_ENTS_IP_ADDR
EFI_MAC_ADDRESS                               R_TargetLinkAddress             
SetEthMacAddress R_TargetLinkAddress          $DEF_ENTS_MAC_ADDR
UINT32                                        R_Timeout
SetVar R_Timeout                              0

Ip6->Neighbors "FALSE, &@R_TargetIp6Address, &@R_TargetLinkAddress, @R_Timeout, TRUE, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Ip6.Neighbors - Func - Add a neighbor entry"               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Add a route cache
# Call Routes with DeleteRoute = FALSE and *Destination = 2002::2
#              and PrefixLength = 16 and *GatewayAddress = 2002::1
#              EFI_SUCCESS should be returned.
#
EFI_IPv6_ADDRESS                              R_Destination
SetIpv6Address R_Destination                  "2002::2"
UINT8                                         R_PrefixLength
SetVar R_PrefixLength                         16
EFI_IPv6_ADDRESS                              R_GatewayAddress
SetIpv6Address R_GatewayAddress               "2002::1"
Ip6->Routes "FALSE, &@R_Destination, @R_PrefixLength, &@R_GatewayAddress, &@R_Status"
GetAck

puts .......................
puts $R_Status

#
# Check point
#
EFI_IP6_COMPLETION_TOKEN                       R_Token
UINTN                                          R_Context
SetVar R_Context                               0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck
#
# Check point: Call Transmit
#
EFI_IP6_TRANSMIT_DATA                          R_TxData
SetIpv6Address R_TxData.DestinationAddress     2002::2
SetVar R_TxData.OverrideData                   0
SetVar R_TxData.ExtHdrsLength                  0
SetVar R_TxData.ExtHdrs                        0
SetVar R_TxData.NextHeader                     0
SetVar R_TxData.DataLength                     30
SetVar R_TxData.FragmentCount                  1

EFI_IP6_FRAGMENT_DATA                          R_FragmentTable
set Ip6PayloadLength                           30
SetVar R_FragmentTable.FragmentLength          $Ip6PayloadLength
CHAR8                                          R_FragmentBuffer(1600)
SetVar R_FragmentBuffer                        "IP6TransmitFunc1Test."
SetVar R_FragmentTable.FragmentBuffer          &@R_FragmentBuffer
SetVar R_TxData.FragmentTable                  @R_FragmentTable

SetVar R_Token.Packet                          &@R_TxData

#
# Start capture
#
set L_Filter "ether proto 0x86dd"
StartCapture CCB $L_Filter

Ip6->Transmit "&@R_Token, &@R_Status"
ReceiveCcbPacket CCB Ip6Packet 15
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Ip6TransmitFunc1AssertionGuid001       \
                "Ip6.Transmit - Func - Call Transmit "                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Token->Event should be signaled
#
GetVar R_Context
set assert fail
if { ${R_Context} ==1} {
  set assert pass
}
RecordAssertion $assert $Ip6TransmitFunc1AssertionGuid002       \
                "Ip6.Transmit - Func - Verify Token->Event whether signaled"
#
# Check point: Token->Status should be EFI_SUCCESS
#
GetVar R_Token
set assert fail
if { ${R_Token.Status} == $EFI_SUCCESS} {
  set assert pass
}
RecordAssertion $assert $Ip6TransmitFunc1AssertionGuid003       \
                "Ip6.Transmit - Func - Verify R_Token.Status "              \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Verify the packet received
#
set assert pass
if { ${CCB.received} == 0} {    
  set assert fail
  RecordAssertion $assert $Ip6TransmitFunc1AssertionGuid004   \
                  "Ip6.Transmit - No Packet transmitted."
  CleanUpEutEnvironment
  return
}
# Dump the packet into the log file
DumpPacket Ip6Packet

ValidatePacket Ip6Packet -t ipv6 "(IPv6_ver=6)AND(IPv6_tc=0)AND(IPv6_fl=0)AND\
                          (IPv6_pl=$Ip6PayloadLength)AND(IPv6_nh=0x11)AND(IPv6_hl=64)\
                          (IPv6_dst=2002:0:0:0:0:0:0:2)AND(IPv6_src=2002:0:0:0:0:0:0:4321)"

if {[string compare -nocase $EMS_RESULT "TRUE"] == 0} {
  set assert pass
} else {
  set assert fail
}

RecordAssertion $assert $Ip6TransmitFunc1AssertionGuid005     \
                        "Ip6.Transmit - Func - check IPv6 packet"

#
# Clean: Delete the route cache and the neighbor cache
#
Ip6->Routes "TRUE, &@R_Destination, @R_PrefixLength, &@R_GatewayAddress, &@R_Status"
GetAck

Ip6->Neighbors "TRUE, &@R_TargetIp6Address, &@R_TargetLinkAddress, @R_Timeout, TRUE, &@R_Status"
GetAck

CleanUpEutEnvironment