# 
#  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
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
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        4326C531-B440-43e7-A572-96984C890FF4
CaseName        Stop.Func3.Case1
CaseCategory    DHCP6

CaseDescription {Test the Stop Function of DHCP6 - Invoke Stop() to stop the  \
                 Dhcpv6 S.A.R.R process,when the instance isn't in Dhcp6Init state.	             
                }
################################################################################

Include DHCP6/include/Dhcp6.inc.tcl

proc CleanUpEnvironment {} {
#
# Close Event
#
BS->CloseEvent    "@R_IaInfoEvent, &@R_Status"
GetAck

#
# Destroy child.
#
Dhcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

DestroyPacket
EndCapture

#
# EndScope
#
EndScope _DHCP6_STOP_FUNC3_
#
# End Log 
#
EndLog
}
#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope  _DHCP6_STOP_FUNC3_

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
Dhcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Dhcp6SB.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

EFI_DHCP6_CONFIG_DATA                   R_ConfigData
#
# SolicitRetransmission parameters
# Irt 1
# Mrc 2
# Mrt 3
# Mrd 2
#
UINT32                                  R_SolicitRetransmission(4)
SetVar R_SolicitRetransmission          {1 2 3 2}

#
# Create Event for IaInfoEvent. When signaled, EventContext will be increased by 1.
#
UINTN                                   R_IaInfoEvent
UINTN                                   R_IaInfoEventContext
SetVar R_IaInfoEventContext             0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_IaInfoEventContext,        \
                                    &@R_IaInfoEvent, &@R_Status"

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "BS.CreateEvent - Create event for IaInfoEvent."                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Configure() to configure this child
# o Dhcp6Callback              2          0:NULL 1:Abort 2:CallbackContext++
# o CallbackContext            0          
# o OptionCount                0        
# o OptionList                 0          
# o IaDescriptor               Type=Dhcp6IATypeNA IaId=1
# o IaInfoEvent                Not NULL          
# o ReconfigureAccept          FALSE
# o RapidCommit                FALSE
# o SolicitRetransmission      defined above
#
UINTN                                          R_Dhcp6CallbackContext
SetVar R_Dhcp6CallbackContext                  0

SetVar R_ConfigData.Dhcp6Callback              2;     #0:NULL 1:Abort 2:CallbackContext++
SetVar R_ConfigData.CallbackContext            &@R_Dhcp6CallbackContext
SetVar R_ConfigData.OptionCount                0
SetVar R_ConfigData.OptionList                 0
SetVar R_ConfigData.IaDescriptor.Type          $Dhcp6IATypeNA
SetVar R_ConfigData.IaDescriptor.IaId          1
SetVar R_ConfigData.IaInfoEvent                @R_IaInfoEvent
SetVar R_ConfigData.ReconfigureAccept          FALSE
SetVar R_ConfigData.RapidCommit                FALSE
SetVar R_ConfigData.SolicitRetransmission      &@R_SolicitRetransmission

#
# Configure this child
#
Dhcp6->Configure  "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid  \
                "Dhcp6.Configure - Configure Child 1"          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set  hostmac   [GetHostMac]
set  targetmac [GetTargetMac]
RemoteEther    $targetmac
LocalEther     $hostmac
set LocalIP    "fe80::2012:3fff:fe86:31da"
LocalIPv6      $LocalIP

set  L_Filter  "src port 546"
StartCapture CCB $L_Filter

#
# Check point: Call Start() to validate the start process.
# Capture and validate DHCP6 Solicit packet. Get the remote IPv6 address
#
Dhcp6->Start    "&@R_Status"

ReceiveCcbPacket CCB SolicitPacket 5
set assert pass
if { ${CCB.received} == 0} {    
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid         \
                  "Dhcp6.Start - No Solicit Packet sent."
  CleanUpEnvironment
  return
}

ParsePacket SolicitPacket -t IPv6 -IPv6_src IPV6Src -IPv6_payload IPV6Payload
EndCapture
RemoteIPv6 $IPV6Src

set DuidType [lrange $IPV6Payload 16 17] 
puts "DuidType : $DuidType\n"

if { $DuidType != "0x00 0x04" } {
  set TransId_and_ClientId [lrange $IPV6Payload 9 29]
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set TransId_and_ClientId [lrange $IPV6Payload 9 33]
}

set AdvertisePayloadData [CreateDHCP6AdvertisePayloadData $IPV6Src $LocalIP $TransId_and_ClientId]

if { $DuidType != "0x00 0x04" } {
  set PayloadDataLength    231
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set PayloadDataLength    235
}
CreatePayload AdvertisePayload List $PayloadDataLength $AdvertisePayloadData

#
#Create Advertise packet
#
CreatePacket AdvertisePacket -t IPv6 -IPv6_ver 0x06 -IPv6_tc 0x00 -IPv6_fl 0x00 \
                             -IPv6_pl $PayloadDataLength -IPv6_nh 0x11 -IPv6_hl 128 \
                             -IPv6_payload AdvertisePayload

#
# Ready to capture the Request packet
#
StartCapture CCB $L_Filter
SendPacket AdvertisePacket
ReceiveCcbPacket CCB RequestPacket 10
if { ${CCB.received} == 0} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                \
                  "Dhcp6.Start - No Request Packet sent."

  CleanUpEnvironment
  return
}

#
# Build and send Reply packet
#
ParsePacket RequestPacket -t IPv6 -IPv6_src IPV6Src -IPv6_payload IPV6Payload
RemoteIPv6 $IPV6Src

set DuidType [lrange $IPV6Payload 16 17] 
puts "DuidType : $DuidType\n"

if { $DuidType != "0x00 0x04" } {
  set TransId_and_ClientId [lrange $IPV6Payload 9 29]
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set TransId_and_ClientId [lrange $IPV6Payload 9 33]
}

set ReplyPayloadData     [CreateDHCP6ReplyPayloadData $IPV6Src $LocalIP $TransId_and_ClientId]

if { $DuidType != "0x00 0x04" } {
  set PayloadDataLength 179
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set PayloadDataLength 183
}
CreatePayload ReplyPayload List $PayloadDataLength $ReplyPayloadData

#
# Create Reply packet
#
CreatePacket ReplyPacket -t IPv6 -IPv6_ver 0x06 -IPv6_tc 0x00 -IPv6_fl 0x00 \
                         -IPv6_pl $PayloadDataLength -IPv6_nh 0x11 -IPv6_hl 128 \
                         -IPv6_payload ReplyPayload

SendPacket ReplyPacket

#
# Get Ack of Start()
#
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid \
                "Dhcp6.Start - Start Child 1"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point:When the S.A.R.R process finished,Callback() will be called 5 times and \
#             CallbackContext will add 5.And the five events which cause Callback() being\ 
#             called is SendSolict/RcvdAdvertise/SelectAdvertise/SendRequest/RcvdReply.
#
GetVar R_Dhcp6CallbackContext
set assert pass
if { $R_Dhcp6CallbackContext != 5 } {
  set assert fail
  RecordAssertion  $assert   $GenericAssertionGuid \
                   "After the S.A.R.R process finished,the CallbackContext should be add 5"
  CleanUpEnvironment
  return
}
#
# Check point:Call GetModeData to get the state of IA,\
#             when Start returns it should be Dhcp6Bound.  
#
EFI_DHCP6_MODE_DATA             R_Dhcp6ModeData
EFI_DHCP6_CONFIG_DATA           R_Dhcp6CfgData
Dhcp6->GetModeData "&@R_Dhcp6ModeData, &@R_Dhcp6CfgData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion  $assert  $GenericAssertionGuid \
                 "Dhcp6.GetModeData -Func- Check the state of IA when Start returns"
GetVar        R_Dhcp6ModeData

EFI_DHCP6_IA  R_Ia
UINTN         R_CopyLen
SetVar  R_CopyLen  [Sizeof R_Ia]
BS->CopyMem  "&@R_Ia, @R_Dhcp6ModeData.Ia, @R_CopyLen, &@R_Status"
GetAck

GetVar  R_Ia.State
set assert fail
if { ${R_Ia.State} == $Dhcp6Bound } {
  set assert pass
}
RecordAssertion $assert  $GenericAssertionGuid \
                "When Start returns, the state of IA should be Dhcp6Bound"

GetVar    R_IaInfoEventContext
set assert fail
if { $R_IaInfoEventContext != 0 } {
  set assert pass
}
RecordAssertion $assert  $GenericAssertionGuid \
                "When the Event is signaled , the IaInfoEventContext should be increased 1"

#
# Check point: Call Stop function when the instance isn't in Dhcp6Init state, \
#              and it will include the RELEASE-REPLY process.
#
Dhcp6->Stop "&@R_Status"
ReceiveCcbPacket CCB ReleasePacket 10
set assert pass
if { ${CCB.received} == 0} {    
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid \
                  "Dhcp6.Release- No Release  Packet sent."
  CleanUpEnvironment
  return
}

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp6StopFunc3AssertionGuid001\
                "Dhcp6.Stop- Since it is a asynchronous call ,so after release packet sent out it finished "

#
# Check point:Since this is a asynchronous call,so after send release packet,the Dhcp6states  \   
# have been cleaned.No need to Get Ack of Stop.after the stop process finished,the IaInfoEvent \
# should be signaled and the state of IA should be Dhcp6Init.
#
GetVar  R_IaInfoEventContext
set assert fail
if {$R_IaInfoEventContext != 0} {
  set assert pass
}
RecordAssertion $assert $Dhcp6StopFunc3AssertionGuid002 \
                "Dhcp6.Release- Call Stop,When RELEASE-REPLY process finished,the IaInfoEvent will be signaled "

EFI_DHCP6_MODE_DATA             R_Dhcp6ModeData2
EFI_DHCP6_CONFIG_DATA           R_Dhcp6CfgData2
Dhcp6->GetModeData "&@R_Dhcp6ModeData2, &@R_Dhcp6CfgData2, &@R_Status"
GetAck

GetVar        R_Dhcp6ModeData2
EFI_DHCP6_IA  R_Ia2
UINTN         R_CopyLen2
SetVar  R_CopyLen2  [Sizeof R_Ia2]
BS->CopyMem  "&@R_Ia2, @R_Dhcp6ModeData2.Ia, @R_CopyLen2, &@R_Status"
GetAck

GetVar  R_Ia2.State
set assert fail
if { ${R_Ia2.State} == $Dhcp6Init } {
    set assert pass
}
RecordAssertion $assert  $Dhcp6StopFunc3AssertionGuid003 \
                "When Release-Reply process finished, the state of IA should be Dhcp6Init"
CleanUpEnvironment
