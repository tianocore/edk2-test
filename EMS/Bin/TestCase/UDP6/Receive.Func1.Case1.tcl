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
CaseGuid        8DA07DF8-2EBB-4f36-8396-6592D23920E6
CaseName        Receive.Func1.Case1
CaseCategory    UDP6

CaseDescription {Test the Receive Function of UdP6 - Invoke Receive()     \
                 with valid parameters and EFI_SUCCESS should be returned.
                }
################################################################################

Include UdP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope  _UDP6_RECEIVE_FUNC1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Check point: Create child.
#
Udp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Udp6SB.CreateChild - Create Child "                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Check Point:Call Configure with valid parameters.EFI_SUCCESS should be returned.
#
EFI_UDP6_CONFIG_DATA                            R_Udp6ConfigData
SetVar  R_Udp6ConfigData.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData.TrafficClass           0
SetVar  R_Udp6ConfigData.HopLimit               64
SetVar  R_Udp6ConfigData.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData.StationAddress "::"
SetVar  R_Udp6ConfigData.StationPort            1780
SetIpv6Address  R_Udp6ConfigData.RemoteAddress  "2002::2"
SetVar  R_Udp6ConfigData.RemotePort             1781
  
Udp6->Configure "&@R_Udp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid  \
                "Udp6.Configure - Configure Child with valid parameters"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Receive with valid parameters.EFI_SUCCESS should be returned.   
#
EFI_UDP6_COMPLETION_TOKEN                    R_Token
UINTN                                        R_NotifyContext
SetVar               R_NotifyContext         0

#
# Create an Event
#
BS->CreateEvent      "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_NotifyContext, &@R_Token.Event, &@R_Status"
GetAck
set assert           [VerifyReturnStatus  R_Status  $EFI_SUCCESS]
RecordAssertion      $assert          $GenericAssertionGuid           \
                     "BS->CreateEvent -Conf- Create an Event "                  \
                     "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

SetVar                R_Token.Status                       "$EFI_INCOMPATIBLE_VERSION"
EFI_UDP6_RECEIVE_DATA                                      R_RxData
SetVar                R_Token.Packet                       &@R_RxData

#
# Create a UdP6 packet
#
set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]
RemoteEther    $targetmac
LocalEther     $hostmac
set LocalIP    "2002::2"
set RemoteIp   "2002::4321"
LocalIPv6      $LocalIP
RemoteIPv6     $RemoteIp
set UdpPayloadlen  30
CreatePayload Udp6Payload String $UdpPayloadlen "Udp6ReceiveTest"
CreatePacket  Udp6Packet -t udp -Udp_sp 1781 -Udp_dp 1780 -Udp_len 30\
              -Udp_payload Udp6Payload -IP_ver 6

Udp6->Receive "&@R_Token, &@R_Status"
GetAck
SendPacket Udp6Packet 

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6ReceiveFunc1AssertionGuid001        \
                "Udp6.Receive - Func - Call Receive "                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Token->Event should be signaled
#
set L_Timeout 10
set i 0
while {1} {
  GetVar R_NotifyContext
  if { ${R_NotifyContext} == 1 } {
    set assert pass
    break
  }
  incr i
  if { $i == $L_Timeout } {
    set assert fail
    break
  }
}
RecordAssertion $assert $Udp6ReceiveFunc1AssertionGuid002        \
                "Udp6.Receive - Func - Verify Token->Event whether signaled"


#
# Check point: Verify the packet received
#
if { [string compare -nocase $assert "pass"] == 0 } {
  UINTN  R_CopyLen
  SetVar R_CopyLen [Sizeof R_RxData]
  GetVar R_CopyLen
  BS->CopyMem "&@R_RxData, @R_Token.Packet, @R_CopyLen, &@R_Status"
  GetAck

  GetVar R_RxData
  puts "Data length: ${R_RxData.DataLength}"
  # Check point: Udp6 Datalength should be 30
  if {${R_RxData.DataLength}==30} {
    set assert pass
  } else {
    set assert fail
  }
  RecordAssertion $assert $Udp6ReceiveFunc1AssertionGuid003   \
                  "Udp6.Receive - Validate RxData: Datalength."

  # Check point: Check FragmentCount
  if {${R_RxData.FragmentCount}==1} {
    set assert pass
  } else {
    set assert fail
  }
  RecordAssertion $assert $Udp6ReceiveFunc1AssertionGuid003   \
                  "Udp6.Receive - Validate RxData: FragmentCount."
}


#
# Check point: Token->Status should be EFI_SUCCESS
#
GetVar R_Token
set assert fail
if { ${R_Token.Status} == $EFI_SUCCESS} {
  set assert pass
}
RecordAssertion $assert $Udp6ReceiveFunc1AssertionGuid004        \
                "Udp6.Receive - Func - Verify R_Token.Status "               \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_SUCCESS"


#
# Check Point: Siganl RecycleSignal
#
if { ${R_NotifyContext} ==1} {
  Udp6->SignalRecycleEvent "&@R_Token, &@R_Status"
  GetAck
}


#
# Check Point: Close the events we created before.
#
BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

#
# Check point: Destroy child.
#
Udp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                         \
                "Udp6SB.DestroyChild - Destroy Child."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EUTClose
				
#
# EndScope
#
EndScope    _UDP6_RECEIVE_FUNC1_
#
# End Log 
#
EndLog