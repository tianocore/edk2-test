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
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        AB35E520-4928-438d-A51D-8F62AA7D69DF
CaseName        InfoRequest.Conf8.Case1
CaseCategory    DHCP6
CaseDescription {Test the InfoRequest Conformance of DHCP6 - Invoke InfoRequest() \
                 when the user returns error status from ReplyCallback function. \
                 EFI_ABORTED should be returned.
                }
################################################################################

Include DHCP6/include/Dhcp6.inc.tcl

proc CleanUpEutEnvironment {} {

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
EndScope _DHCP6_INFOREQUEST_CONF8_
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
BeginScope  _DHCP6_INFOREQUEST_CONF8_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                                   R_Status
UINTN                                   R_Handle

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

BOOLEAN                         R_SendClientId
SetVar R_SendClientId           TRUE

EFI_DHCP6_PACKET_OPTION         R_OptionRequest
#Dhcp6OptRequestOption
SetVar  R_OptionRequest.OpCode  0x0600
SetVar  R_OptionRequest.OpLen   0x0600
UINT8   R_OptRequestData(6)
SetVar  R_OptRequestData        {0x00 0x17 0x00 0x32 0x00 0x33}
SetVar  R_OptionRequest.Data    @R_OptRequestData

UINT32                          R_OptionCount
SetVar  R_OptionCount           0

UINT32                          R_Retransmission(4)
#
# Retransmission parameters
# Irt 1
# Mrc 2
# Mrt 3
# Mrd 2
#
SetVar R_Retransmission         {1 2 3 2}

UINTN                                   R_ReplyCallback
UINTN                                   R_CallbackContext
#0: NULL 1: Abort
SetVar R_ReplyCallback                  1

set  hostmac   [GetHostMac]
set  targetmac [GetTargetMac]
RemoteEther    $targetmac
LocalEther     $hostmac
set LocalIP    "fe80::2012:3fff:fe86:31da"
LocalIPv6      $LocalIP

set  L_Filter  "src port 546"
StartCapture CCB $L_Filter

#
# Check point:Call InfoRequest to obtain configuration information without any IA address
# Capture and Validate Dhcp6 InfoRequest packet.
#
Dhcp6->InfoRequest "@R_SendClientId, &@R_OptionRequest, @R_OptionCount, NULL,  \
                              &@R_Retransmission, 0, @R_ReplyCallback,  &@R_CallbackContext, &@R_Status"

ReceiveCcbPacket CCB InfoRequestPacket 15
set assert pass
if { ${CCB.received} == 0} {
    set assert fail
    RecordAssertion  $assert $Dhcp6InfoRequestFunc2AssertionGuid001 \
                 "Dhcp6.InfoRequest - No InfoRequest Packet sent."

CleanUpEutEnvironment
return
}

ParsePacket InfoRequestPacket -t IPv6 -IPv6_src IPV6Src -IPv6_payload IPV6Payload
EndCapture
RemoteIPv6 $IPV6Src

set DuidType [lrange $IPV6Payload 16 17] 
puts "DuidType : $DuidType\n"

if { $DuidType != "0x00 0x04"} {
    set TransId_and_ClientId [lrange $IPV6Payload 9 29]
} else {
    #
    # New DHCP6 DUID-UUID type
    #
    set TransId_and_ClientId [lrange $IPV6Payload 9 33]
}
set ReplyPayloadData [CreateDHCP6InfoReqReplyPayloadData $IPV6Src $LocalIP $TransId_and_ClientId]
if { $DuidType != "0x00 0x04"} {
    set PayloadDataLength    104
} else {
    set PayloadDataLength    108
}
CreatePayload ReplyPayload List $PayloadDataLength $ReplyPayloadData

#
#Create Reply packet for InfoRequest message
#
CreatePacket ReplyPacket -t IPv6 -IPv6_ver 0x06 -IPv6_tc 0x00 -IPv6_fl 0x00 \
                                     -IPv6_pl $PayloadDataLength -IPv6_nh 0x11 -IPv6_hl 64 \
                                     -IPv6_payload ReplyPayload

SendPacket ReplyPacket

#
# GetAck of InfoRequest
#
GetAck

set assert [VerifyReturnStatus R_Status $EFI_ABORTED]
RecordAssertion $assert $Dhcp6InfoRequestConf8AssertionGuid001   \
                        "Dhcp6.InfoRequest - ReplyCallback returns EFI_ABORTED" \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ABORTED"

CleanUpEutEnvironment

