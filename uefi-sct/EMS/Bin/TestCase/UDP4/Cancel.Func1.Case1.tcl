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
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT 
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        8DC54638-4BE0-41a0-9249-9F9A7203188C
CaseName        Cancel.Func1.Case1
CaseCategory    Udp4
CaseDescription {Test the Cancel Function of UDP4 - Invoke Cancel() to cancel a\
                 receive request.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _UDP4_CANCEL_FUNCTION1_CASE1_

set hostmac          [GetHostMac]
set targetmac        [GetTargetMac]
set targetip         192.168.88.1
set hostip           192.168.88.2
set subnetmask       255.255.255.0
set targetport       4000
set hostport         4000

VifUp 0 $hostip

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_PollStatus
EFI_UDP4_CONFIG_DATA             R_Udp4ConfigData
UINTN                            R_Context
EFI_UDP4_COMPLETION_TOKEN        R_Token

Udp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar   [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SBP.Cancel - Func - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Udp4ConfigData.AcceptBroadcast             FALSE
SetVar R_Udp4ConfigData.AcceptPromiscuous           FALSE
SetVar R_Udp4ConfigData.AcceptAnyPort               FALSE
SetVar R_Udp4ConfigData.AllowDuplicatePort          TRUE
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

#check point
Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Cancel - Func - Config Child"                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

SetVar R_Token.Packet 0    ;#NULL
SetVar R_Token.Status 0x01 ;#Make sure it will be modified.

#
# Build a UDP packet
#
LocalEther  $hostmac
RemoteEther $targetmac
LocalIp     $hostip
RemoteIp    $targetip

CreatePayload aaa const 18 0x0
CreatePacket udp_packet -t udp -udp_dp $targetport -udp_sp $hostport           \
                        -udp_payload aaa

#
# EFI begins to receive 
#
Udp4->Receive {&@R_Token, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Cancel - Func - Receive a packet"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


#
# Call Cancel, it should return EFI_SUCCESS
#
Udp4->Cancel {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4CancelFunc1AssertionGuid001                       \
                "Udp4.Cancel - Func - Call Cancel, it should return EFI_SUCCESS"\
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# The event should have been signaled, so R_Context should be 1 now.
#
GetVar R_Context
if {$R_Context == 0} {
  set assert fail
} else {
  set assert pass
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Cancel - Func - check Event"                             \
                "Return R_Context - $R_Context, Expected R_Context - 1"

#
# Sends the Packet. Because the token has been canceled, it will not be 
# captured by EFI.
#
SendPacket udp_packet

for {set i 0} { $i < 10} {incr i} {
  Udp4->Poll {&@R_PollStatus}
  GetAck

  GetVar R_Context
  if {$R_Context == 2} {
    set assert fail
    break
  } else {
    set assert pass
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Cancel - Func - check Event"                             \
                "Return R_Context - $R_Context, Expected R_Context - 1"

GetVar R_Token.Status
if {${R_Token.Status} == $EFI_ABORTED} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Cancel - Func - Check R_Token"                            \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_ABORTED"


#
# Call SignalRecycleEvent to recycle receive buffer
#
Udp4->SignalRecycleEvent {&@R_Token, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Cancel - Conf - SignalRecycleEvent"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Destroy the child handle
#
Udp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SBP.Cancel - Func - Destroy Child "                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# Close the EVENT.
#
BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

VifDown 0

#
# BeginScope
#
EndScope _UDP4_CANCEL_FUNCTION1_CASE1_

#
# End Log
#
EndLog
