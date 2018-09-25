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
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        88A3F9AD-2300-42c9-B63D-D5F46846886C
CaseName        Cancel.Conf3.Case1
CaseCategory    UDP6
CaseDescription {Test the Cancel Conformance of UDP6 - Invoke Cancel() when \
                 Token can't be found in either transmit or receive queue. \
                 EFI_NOT_FOUND should be returned.}           
################################################################################

Include  UDP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope _UDP6_CANCEL_CONF3_CASE1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Create child.
#
Udp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                  \
                "Udp6SB.CreateChild - Create Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

# 
# Call Configure function with valid parameters.EFI_SUCCESS should be returned.
#
EFI_UDP6_CONFIG_DATA                            R_Udp6ConfigData
SetVar  R_Udp6ConfigData.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData.TrafficClass           0
SetVar  R_Udp6ConfigData.HopLimit               64
SetVar  R_Udp6ConfigData.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData.StationAddress $DEF_EUT_IP_ADDR
SetVar  R_Udp6ConfigData.StationPort            1780
SetIpv6Address  R_Udp6ConfigData.RemoteAddress  $DEF_ENTS_IP_ADDR
SetVar  R_Udp6ConfigData.RemotePort             1781
  
Udp6->Configure "&@R_Udp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid     \
                "Udp6.Configure - Configure Child with valid parameters"     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

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

SetVar                R_Token.Status                       "$EFI_SUCCESS"
EFI_UDP6_RECEIVE_DATA                                      R_RxData
SetVar                R_Token.Packet                       &@R_RxData

#
# Create a UdP6 packet
#
set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]
RemoteEther    $targetmac
LocalEther     $hostmac
set LocalIP    $DEF_ENTS_IP_ADDR
set RemoteIp   $DEF_EUT_IP_ADDR
LocalIPv6      $LocalIP
RemoteIPv6     $RemoteIp
set UdpPayloadlen  30
CreatePayload Udp6Payload String $UdpPayloadlen "Udp6ReceiveTest"
CreatePacket  Udp6Packet -t udp -Udp_sp 1781 -Udp_dp 1780 -Udp_len 30\
              -Udp_payload Udp6Payload -IP_ver 6

Udp6->Receive "&@R_Token, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid        \
                "Udp6.Receive - Func - Call Receive "                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SendPacket Udp6Packet 

set assert pass

set i 0
set L_TimeOut 10
while { 1 > 0 } {
  GetVar R_NotifyContext
  if { $R_NotifyContext == 1 } {
    puts "The time to trigger the Event is: $i"
    break
  } elseif { $i == $L_TimeOut } {
    set assert fail
    break
  }
  incr i
  Stall 1
}


GetVar R_NotifyContext 
if {$R_NotifyContext != 1} {
   set assert fail
}

RecordAssertion $assert $GenericAssertionGuid     \
                "When received data,the event will be signaled and the value of R_NotifyContext will increase."


GetVar R_Token.Status
if {${R_Token.Status} != $EFI_SUCCESS} {
   set assert fail
} else {
   set assert pass
}
RecordAssertion $assert $GenericAssertionGuid       \
                "When returned, the R_Token.Status should be EFI_SUCCESS"


# 
# Check point: Call Cancel function with Token not in either transmit or receive queue.\
#              EFI_NOT_FOUND should be returned.
#
Udp6->Cancel  "&@R_Token, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $Udp6CancelConf3AssertionGuid001             \
                "Udp6.Cancel -conf- Call Cancel with Token not in either transmit or receive queue."  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

#
# Check Point: Siganl RecycleSignal
#
if { [string compare -nocase $assert "pass"] == 0 } {
  Udp6->SignalRecycleEvent "&@R_Token, &@R_Status"
  GetAck
}


#
# Destroy child.
#
Udp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Udp6SB.DestroyChild - Destroy Child1"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Close Event
#
BS->CloseEvent    "@R_Token.Event, &@R_Status"
GetAck
set assert        [VerifyReturnStatus   R_Status   $EFI_SUCCESS]
RecordAssertion   $assert     $GenericAssertionGuid             \
                  "BS->CloseEvent -Conf- Close the Event we created before"  \
                  "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

EUTClose

#
# EndScope
#
EndScope    _UDP6_CANCEL_CONF3_CASE1_
#
# End Log 
#
EndLog
