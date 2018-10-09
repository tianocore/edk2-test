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
CaseGuid        2A276A33-A2B1-4610-922E-3F50DB1C18F7
CaseName        Release.Func2.Case1
CaseCategory    DHCP6

CaseDescription {Test the Release Function of DHCP6 - Invoke Release() \
                 to release one or more Ipv6 addresses associated with \
                 the configured IA for current instance.             
                }
################################################################################

Include DHCP6/include/Dhcp6.inc.tcl

proc CleanUpEnvironment {} {
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
EndScope _DHCP6_RELEASE_FUNC2_
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
BeginScope  _DHCP6_RELEASE_FUNC2_

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
# Call Configure() to configure this child
# o Dhcp6Callback              2          0:NULL 1:Abort 2:CallbackContext++
# o CallbackContext            0          
# o OptionCount                0        
# o OptionList                 0          
# o IaDescriptor               Type=Dhcp6IATypeNA IaId=1
# o IaInfoEvent                NULL          
# o ReconfigureAccept          FALSE
# o RapidCommit                FALSE
# o SolicitRetransmission      defined above
#
UINTN  R_CallbackContext    
SetVar R_CallbackContext       0
SetVar R_ConfigData.Dhcp6Callback              2;    #0:NULL 1: Abort 2:CallbackContext++
SetVar R_ConfigData.CallbackContext            &@R_CallbackContext
SetVar R_ConfigData.OptionCount                0
SetVar R_ConfigData.OptionList                 0
SetVar R_ConfigData.IaDescriptor.Type          $Dhcp6IATypeNA
SetVar R_ConfigData.IaDescriptor.IaId          1
SetVar R_ConfigData.IaInfoEvent                0;    #synchronous call
SetVar R_ConfigData.ReconfigureAccept          FALSE
SetVar R_ConfigData.RapidCommit                FALSE
SetVar R_ConfigData.SolicitRetransmission      &@R_SolicitRetransmission

#
# Configure this child
#
Dhcp6->Configure  "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid         \
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
    RecordAssertion $assert $GenericAssertionGuid        \
                    "Dhcp6.Start - No Solicit Packet sent."

    CleanUpEnvironment
    return
}

ParsePacket SolicitPacket -t IPv6 -IPv6_src IPV6Src -IPv6_payload IPV6Payload
EndCapture
RemoteIPv6 $IPV6Src
#
# CreateDHCP6AdvertisePayloadData2 to assign two Ipv6 Addresses to IA.
#
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
set AdvertisePayloadData [CreateDHCP6AdvertisePayloadData2 $IPV6Src $LocalIP $TransId_and_ClientId]
if { $DuidType != "0x00 0x04" } {
    set PayloadDataLength    259
} else {  
    #
    # New DHCP6 DUID-UUID type
    #
    set PayloadDataLength    263
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
set ReplyPayloadData     [CreateDHCP6ReplyPayloadData2 $IPV6Src $LocalIP $TransId_and_ClientId]
if { $DuidType != "0x00 0x04" } {
    set PayloadDataLength 207
} else {
    #
    # New DHCP6 DUID-UUID type
    #
    set PayloadDataLength 211
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
#             called is SendSolict/RcvdAdvertise/SelectAdvertise/SendRequest/RcvdReply.\
#             when start returns,the state of IA should be DhcpBound.
#
GetVar R_CallbackContext
set assert pass
if { $R_CallbackContext != 5 } {
  set assert fail
  RecordAssertion  $assert   $GenericAssertionGuid \
                   "After the S.A.R.R process finished,the CallbackContext should be add 5"
  CleanUpEnvironment
    return
}

EFI_DHCP6_MODE_DATA             R_Dhcp6ModeData1
EFI_DHCP6_CONFIG_DATA           R_Dhcp6CfgData1
Dhcp6->GetModeData "&@R_Dhcp6ModeData1, &@R_Dhcp6CfgData1, &@R_Status"
GetAck

GetVar        R_Dhcp6ModeData1
EFI_DHCP6_IA  R_Ia1
UINTN         R_CopyLen1
SetVar  R_CopyLen1  [Sizeof R_Ia1]
BS->CopyMem  "&@R_Ia1, @R_Dhcp6ModeData1.Ia, @R_CopyLen1, &@R_Status"
GetAck

GetVar  R_Ia1.State
set assert fail
if { ${R_Ia1.State} == $Dhcp6Bound } {
  set assert pass
}
RecordAssertion $assert  $GenericAssertionGuid    \
                "When Start returns, the state of IA should be Dhcp6Bound"

UINT32                                    R_AddressCount
SetVar              R_AddressCount        2
EFI_IPv6_ADDRESS                          R_Address(2)
SetIpv6Address      R_Address(0)          "2000::14da:d837:147:527d"
SetIpv6Address      R_Address(1)          "2000::14da:d837:147:527c"
#
# Call Release to release all the Ipv6 addresses that have already assigned to the configured IA.
#
Dhcp6->Release "@R_AddressCount, &@R_Address, &@R_Status"

set count 0

while {${count} < 10} {

  ReceiveCcbPacket CCB ReleasePacket 5
  set assert pass
  if { ${CCB.received} == 0} {    
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid \
                    "Dhcp6.Release- No Release  Packet sent."

    CleanUpEnvironment
    return
  }

  ParsePacket ReleasePacket -t IPv6 -IPv6_src IPV6Src -IPv6_payload IPV6Payload
  set MessageType [lrange $IPV6Payload 8 8]

  if {${MessageType} == 8} {
    break
  }

  incr count  
}

if {${count} == 10} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid \
                  "Dhcp6.Release- No Release  Packet sent."

  CleanUpEnvironment
  return
}

ParsePacket ReleasePacket -t IPv6 -IPv6_src IPV6Src -IPv6_payload IPV6Payload
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
set ReplyPayloadData     [CreateDHCP6DeclineReplyPayloadData $IPV6Src $LocalIP $TransId_and_ClientId]

if { $DuidType != "0x00 0x04" } {
    set PayloadDataLength 151
} else {
    #
    # New DHCP6 DUID-UUID type
    #
    set PayloadDataLength 155
}

CreatePayload ReplyPayload List $PayloadDataLength $ReplyPayloadData

#
# Create RleaseReply packet
#
CreatePacket ReleaseReplyPacket -t IPv6 -IPv6_ver 0x06 -IPv6_tc 0x00 -IPv6_fl 0x00 \
                                -IPv6_pl $PayloadDataLength -IPv6_nh 0x11 -IPv6_hl 128 \
                                -IPv6_payload ReplyPayload

SendPacket ReleaseReplyPacket

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp6ReleaseFunc2AssertionGuid001 \
                "Dhcp6.Release-Release all the Ipv6 addresses that have already assigned to the configured IA" \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: After all the Ipv6 addresses are released,the state of IA should be Dhcp6Init.
#
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
RecordAssertion $assert  $Dhcp6ReleaseFunc2AssertionGuid002 \
                "When Release-Reply process finished, the state of IA should be Dhcp6Init"

CleanUpEnvironment
