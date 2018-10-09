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
CaseGuid        F24699BF-41B2-478c-849F-E72E790F1E8D
CaseName        Transmit.Func1.Case1
CaseCategory    UDP6

CaseDescription {Test the Transmit Function of UdP6 - Invoke Transmit()     \
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
BeginScope  _UDP6_TRANSMIT_FUNC1_

EUTSetup

UINTN                            R_Status
UINTN                            R_Handle

#
# Check point: Create child.
#
Udp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Udp6SB.CreateChild - Create Child "                   \
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
SetIpv6Address  R_Udp6ConfigData.RemoteAddress  "::"
SetVar  R_Udp6ConfigData.RemotePort             0
  
Udp6->Configure "&@R_Udp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid  \
                "Udp6.Configure - Configure Child with valid parameters"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Transmit with valid parameter.EFI_SUCCESS should be returned.    \
#              Token.Event should be signaled and Token.Status should be EFI_SUCCESS\
#              validate the packet received.
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

SetVar                R_Token.Status                       "$EFI_SUCCESS"
EFI_UDP6_TRANSMIT_DATA                                     R_TxData
EFI_UDP6_SESSION_DATA                                      R_Udp6SessionData
SetIpv6Address        R_Udp6SessionData.SourceAddress      "::"
SetVar                R_Udp6SessionData.SourcePort         0
SetIpv6Address        R_Udp6SessionData.DestinationAddress "2002::2"
SetVar                R_Udp6SessionData.DestinationPort    1781
SetVar                R_TxData.UdpSessionData              &@R_Udp6SessionData
SetVar                R_TxData.DataLength                  30
SetVar                R_TxData.FragmentCount               1

EFI_UDP6_FRAGMENT_DATA                                     R_FragmentTable
SetVar                R_FragmentTable.FragmentLength       30
CHAR8                 R_FragmentBuffer(1600)
SetVar                R_FragmentBuffer                     "Udp6TestBuffer"
SetVar                R_FragmentTable.FragmentBuffer       &@R_FragmentBuffer 
SetVar                R_TxData.FragmentTable               @R_FragmentTable
SetVar                R_Token.Packet                       &@R_TxData

#
# Start capture
#
set L_Filter "ether proto 0x86dd"
StartCapture CCB $L_Filter
 
Udp6->Transmit  "&@R_Token, &@R_Status"
ReceiveCcbPacket CCB Udp6Packet 10
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6TransmitFunc1AssertionGuid001        \
                "Udp6.Transmit -func- Call Transmit with valid paramters "        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Token->Event should be signaled
#
GetVar R_NotifyContext
set assert fail
if { ${R_NotifyContext} ==1} {
  set assert pass
}
RecordAssertion $assert $Udp6TransmitFunc1AssertionGuid002       \
                "Udp6.Transmit - Func - Verify Token->Event whether signaled"
#
# Check point: Token->Status should be EFI_SUCCESS
#
GetVar R_Token
set assert fail
if { ${R_Token.Status} == $EFI_SUCCESS} {
  set assert pass
}
RecordAssertion $assert $Udp6TransmitFunc1AssertionGuid003       \
                "Udp6.Transmit - Func - Verify R_Token.Status "              \
                "ReturnStatus - ${R_Token.Status}, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Verify the packet received
#
set assert fail
if { ${CCB.received} == 1} {
    set assert pass
    RecordAssertion $assert $Udp6TransmitFunc1AssertionGuid004   \
                    "Udp6.Transmit - Packet transmitted."
   }
# Dump the packet into the log file
DumpPacket Udp6Packet
set Ip6PayloadLength 38
ValidatePacket Udp6Packet -t ipv6 "(IPv6_ver=6)AND(IPv6_tc=0)AND(IPv6_fl=0)AND    \
                                               (IPv6_pl=$Ip6PayloadLength)AND(IPv6_nh=0x11)AND(IPv6_hl=64)AND\
                                                (IPv6_dst=2002:0:0:0:0:0:0:2)AND(IPv6_src=2002:0:0:0:0:0:0:4321)"
if {[string compare -nocase $EMS_RESULT "TRUE"] == 0} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Udp6TransmitFunc1AssertionGuid004   \
                        "Udp6.Transmit - Func - check Ip6 header"

ValidatePacket Udp6Packet -t udp "(udp_sp=1780)AND(udp_dp=1781)"
if {[string compare -nocase $EMS_RESULT "TRUE"] == 0} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $Udp6TransmitFunc1AssertionGuid004  \
                        "Udp6.Transmit - Func - check Udp6 header"


#
# Check Point: Close the event
#
BS->CloseEvent "@R_Token.Event, &@R_Status"
GetAck

DestroyPacket
EndCapture

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
EndScope    _UDP6_TRANSMIT_FUNC1_
#
# End Log 
#
EndLog