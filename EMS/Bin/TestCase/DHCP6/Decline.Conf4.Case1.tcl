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
# Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR> 
#
#
################################################################################
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        9FC28F67-5094-41cb-8B82-C3DBBD1BDCD3
CaseName        Decline.Conf4.Case1
CaseCategory    DHCP6
CaseDescription {Test the Decline Conformance of DHCP6 - Invoke Decline() \
                 with Address which is not correlated with the configured IA. \
                 EFI_NOT_FOUND should be returned.
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
    EndScope _DHCP6_DECLINE_CONF4_
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
BeginScope  _DHCP6_DECLINE_CONF4_

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
# o Dhcp6Callback              0          0:NULL 1:Abort 2:DoNothing
# o CallbackContext            0          
# o OptionCount                0        
# o OptionList                 0          
# o IaDescriptor               Type=Dhcp6IATypeNA IaId=1
# o IaInfoEvent                NULL          
# o ReconfigureAccept          FALSE
# o RapidCommit                FALSE
# o SolicitRetransmission      defined above
#

SetVar R_ConfigData.Dhcp6Callback              0
SetVar R_ConfigData.CallbackContext            0
SetVar R_ConfigData.OptionCount                0
SetVar R_ConfigData.OptionList                 0
SetVar R_ConfigData.IaDescriptor.Type          $Dhcp6IATypeNA
SetVar R_ConfigData.IaDescriptor.IaId          1
SetVar R_ConfigData.IaInfoEvent                0
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

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]
RemoteEther    $targetmac
LocalEther     $hostmac
set LocalIP    "fe80::203:47ff:fead:6a28"
LocalIPv6      $LocalIP

set L_Filter "src port 546"
StartCapture CCB $L_Filter

#
# Check point: Call Start() to validate the start process.
# 1). Capture and validate DHCP6 Solicit packet. Get the remote IPv6 address
#
Dhcp6->Start "&@R_Status"

ReceiveCcbPacket CCB SolicitPacket 5
set assert pass
if { ${CCB.received} == 0} {    
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                \
                    "Dhcp6.Start - No Solicit Packet sent."	

    CleanUpEutEnvironment
    return
}

ParsePacket SolicitPacket -t IPv6 -IPv6_src IPV6Src -IPv6_payload IPV6Payload
EndCapture
RemoteIPv6 $IPV6Src
#puts "Remote IP: $IPV6Src"

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


#puts "Transaction ID and Client Id: $TransId_and_ClientId"

set AdvertisePayloadData [CreateDHCP6AdvertisePayloadData $IPV6Src $LocalIP \
                         $TransId_and_ClientId]
if { $DuidType != "0x00 0x04" } {
    set PayloadDataLength 231
} else {
    #
    # New DHCP6 DUID-UUID type
    #
    set PayloadDataLength 235
}
CreatePayload AdvertisePayload List $PayloadDataLength $AdvertisePayloadData

#
# Create Advertise packet
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

    CleanUpEutEnvironment
    return
}

#
# Build and send Reply packet
#
ParsePacket RequestPacket -t IPv6 -IPv6_src IPV6Src -IPv6_payload IPV6Payload
RemoteIPv6 $IPV6Src
#puts "Remote IP: $IPV6Src"

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

#puts "Transaction ID and Client Id: $TransId_and_ClientId"

set ReplyPayloadData [CreateDHCP6ReplyPayloadData $IPV6Src $LocalIP \
                         $TransId_and_ClientId]

if { $DuidType != "0x00 0x04"} {
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
# Get ACK of Start()
#
GetAck

#
# Check point: Call Decline() when any specified address in Addresses 
#              is not correlated with the configured IA.
#              EFI_NOT_FOUND should be returned.
#
UINT32                                   R_AddressCount
EFI_IPv6_ADDRESS                         R_Addresses
SetVar R_AddressCount                    1
SetIpv6Address R_Addresses               "2001::1"

Dhcp6->Decline  "@R_AddressCount, &@R_Addresses, &@R_Status"
GetAck

set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $Dhcp6DeclineConf4AssertionGuid001           \
                "Dhcp6.Decline - AddressCount is zero."                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

CleanUpEutEnvironment
