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
CaseLevel          CONFORMANCE
CaseAttribute      AUTO
CaseVerboseLevel   DEFAULT
set reportfile     report.csv

#
# Test Case Name, Category, Description, GUID ...
#
CaseGuid           3D981267-364B-461b-8101-EA3817B6DA27
CaseName           Cancel.Conf3.Case1
CaseCategory       IP6
CaseDescription    { Test the Cancel Function of IP6 - invoke Cancel() when Token can \
                     not be found in receive queue after the packet has been received.\
                     EFI_NOT_FOUND should be returned.
                   }
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin  log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope     IP6_CANCEL_CONF3_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                       R_Status
UINTN                       R_Handle 

#
# Create a Child
#
Ip6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion  $assert $GenericAssertionGuid               \
                 "Ip6SB->CreateChild - Conf - Create Child "             \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"
SetVar  [subst $ENTS_CUR_CHILD]    @R_Handle

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

EFI_IP6_CONFIG_DATA                R_Ip6ConfigData
SetVar           R_Ip6ConfigData.DefaultProtocol    0x11;       #NextHeader: UDP
SetVar           R_Ip6ConfigData.AcceptAnyProtocol  FALSE
SetVar           R_Ip6ConfigData.AcceptIcmpErrors   TRUE
SetVar           R_Ip6ConfigData.AcceptPromiscuous  FALSE
SetIpv6Address   R_Ip6ConfigData.DestinationAddress "::"    
SetIpv6Address R_Ip6ConfigData.StationAddress         $DEF_EUT_IP_ADDR
SetVar           R_Ip6ConfigData.TrafficClass       0
SetVar           R_Ip6ConfigData.HopLimit           64
SetVar           R_Ip6ConfigData.FlowLabel          0
SetVar           R_Ip6ConfigData.ReceiveTimeout     50000
SetVar           R_Ip6ConfigData.TransmitTimeout    50000

#
# Configure this child with valid parameter.
#
Ip6->Configure   "&@R_Ip6ConfigData, &@R_Status"
GetAck
set assert       [VerifyReturnStatus  R_Status  $EFI_SUCCESS]
RecordAssertion  $assert     $GenericAssertionGuid            \
                 "Ip6->Configure -Conf- Configure the Child "              \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"
 
EFI_IP6_COMPLETION_TOKEN                            R_Token
UINTN            R_NotifyContext                     
SetVar           R_NotifyContext                    0

#
# Create an Event
#
BS->CreateEvent  "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_NotifyContext, &@R_Token.Event, &@R_Status"
GetAck
set assert       [VerifyReturnStatus  R_Status  $EFI_SUCCESS]
RecordAssertion  $assert      $GenericAssertionGuid            \
                 "BS->CreateEvent -Conf- Create an Event  "              \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"


EFI_IP6_RECEIVE_DATA                           R_RxData
SetVar R_Token.Packet                          &@R_RxData

#
# Create a IPv6 packet
#
set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]
RemoteEther    $targetmac
LocalEther     $hostmac
set LocalIP    "2002::2"
set RemoteIP   "2002::4321"
LocalIPv6      $LocalIP
RemoteIPv6     $RemoteIP
set PayloadDataLength 30
CreatePayload IPv6Payload String $PayloadDataLength "helloworld"
CreatePacket  Ipv6Packet -t udp -Udp_sp 1781 -Udp_dp 1780 -Udp_len $PayloadDataLength\
              -Udp_payload IPv6Payload -IP_ver 6

#
# Check point: Call Receive() to receive a packet
#
Ip6->Receive "&@R_Token, &@R_Status"
SendPacket Ipv6Packet
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Ip6.Receive - Func - Call Receive "                    \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Token->Event should be signaled
#
GetVar R_NotifyContext
set assert fail
if { ${R_NotifyContext} ==1} {
  set assert pass
}
RecordAssertion $assert $GenericAssertionGuid          \
                "Ip6.Receive -Func- Token->Event should be signaled"

Stall 5

#
# Check point: Call Cancel when Token has been signaled in Receive Queue.EFI_NOT_FOUND should be returned.             
#  
Ip6->Cancel      "&@R_Token, &@R_Status"
GetAck
set  assert      [VerifyReturnStatus R_Status  $EFI_NOT_FOUND]
RecordAssertion  $assert       $Ip6CancelConf3AssertionGuid001                 \
                 "Ip6->Cancel -Conf- Call Cancel Function with Token not found in  Receive Queue"  \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_NOT_FOUND"

#
# Destroy Child
#
Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert        [VerifyReturnStatus  R_Status $EFI_SUCCESS]
RecordAssertion   $assert  $GenericAssertionGuid                 \
                  "Ip6SB->DestroyChild - Conf - Destroy Child"              \
                  "RetrunStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                  
#
# Close an Event
#
BS->CloseEvent   "@R_Token.Event, &@R_Status"
GetAck
set assert      [VerifyReturnStatus  R_Status  $EFI_SUCCESS]
RecordAssertion  $assert       $GenericAssertionGuid         \
                 "BS->CloseEvent -Conf- Close the Event "              \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

#DestroyPacket
#EndCapture

#
# End scope
#
EndScope        IP6_CANCEL_CONF3_CASE1_
#
# End log
#
EndLog
