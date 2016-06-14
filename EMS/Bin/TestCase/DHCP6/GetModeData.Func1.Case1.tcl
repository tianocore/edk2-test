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
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        656A2D3C-A9F3-4cb6-93C2-455C063433AE
CaseName        GetModeData.Func1.Case1
CaseCategory    DHCP6

CaseDescription {Test the GetModeData Function of DHCP6 - Invoke GetModeData() \
                 to retrieve the current operating mode data and config data.
                }
################################################################################

Include DHCP6/include/Dhcp6.inc.tcl

proc CleanUpEnvironment {} {

    #
    # Close Event
    #
    BS->CloseEvent  "@R_IaInfoEvent, &@R_Status"
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
    EndScope _DHCP6_GETMODEDATA_FUNC1_
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
BeginScope  _DHCP6_GETMODEDATA_FUNC1_

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
# o IaInfoEvent                Not NULL          
# o ReconfigureAccept          FALSE
# o RapidCommit                FALSE
# o SolicitRetransmission      defined above
#

#
# Create Event for IaInfoEvent. When signaled, EventContext will be increased by 1.
#
UINTN                                          R_CallbackContext
SetVar R_CallbackContext                       0
UINTN                                          R_IaInfoEvent
UINTN                                          R_IaInfoEventContext
SetVar R_IaInfoEventContext                    0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_IaInfoEventContext,        \
                                            &@R_IaInfoEvent, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "BS.CreateEvent - Create event for IaInfoEvent."                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_ConfigData.Dhcp6Callback              2
SetVar R_ConfigData.CallbackContext            &@R_CallbackContext
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
RecordAssertion $assert $GenericAssertionGuid         \
                "Dhcp6.Configure - Configure Child 1"          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]
RemoteEther    $targetmac
LocalEther     $hostmac
set LocalIP    "fe80::203:47ff:fead:6a28"
LocalIPv6      $LocalIP

set  L_Filter  "src port 546"
StartCapture CCB $L_Filter

#
# Call Start()
#
Dhcp6->Start "&@R_Status"

ReceiveCcbPacket CCB SolicitPacket 5
set assert pass
if { ${CCB.received} == 0} {    
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                \
                    "Dhcp6.Start - No Solicit Packet sent."	

CleanUpEnvironment
return
}

ParsePacket SolicitPacket -t IPv6 -IPv6_src IPV6Src -IPv6_payload IPV6Payload
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
set AdvertisePayloadData [CreateDHCP6AdvertisePayloadData $IPV6Src $LocalIP $TransId_and_ClientId]

if { $DuidType != "0x00 0x04"} {
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

if { $DuidType != "0x00 0x04"} {
    set TransId_and_ClientId [lrange $IPV6Payload 9 29]
} else {
    #
    # New DHCP6 DUID-UUID type
    #
    set TransId_and_ClientId [lrange $IPV6Payload 9 33]
}
set ReplyPayloadData     [CreateDHCP6ReplyPayloadData $IPV6Src $LocalIP $TransId_and_ClientId]

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
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid \
                "Dhcp6.Start - Start Child "                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# Check point:When the S.A.R.R process finished,Callback() will be called 5 times and \
#             CallbackContext will add 5.And the five events which cause Callback() being\ 
#             called is SendSolict/RcvdAdvertise/SelectAdvertise/SendRequest/RcvdReply.
#
GetVar R_CallbackContext
set assert pass
if { $R_CallbackContext != 5 } {
    set assert fail
    RecordAssertion  $assert   $Dhcp6GetModeDataFunc1AssertionGuid001 \
                     "After the S.A.R.R process finished,the CallbackContext should be add 5"
CleanUpEnvironment
return
}
#
# Check point: when start returns the IaInfoEvent will be signaled
#
GetVar  R_IaInfoEventContext
set assert fail
if {$R_IaInfoEventContext != 0} {
    set assert pass
}
RecordAssertion $assert $Dhcp6GetModeDataFunc1AssertionGuid002 \
                "Dhcp6.GetModeData- When Ipv6 Address of IA changed,the IaInfoEvent will be signaled and IaInfoEventcontext add 1"
#
# Check point: Call GetModeData()
#
EFI_DHCP6_MODE_DATA             R_Dhcp6ModeData
EFI_DHCP6_CONFIG_DATA           R_Dhcp6CfgData
Dhcp6->GetModeData "&@R_Dhcp6ModeData, &@R_Dhcp6CfgData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp6GetModeDataFunc1AssertionGuid003      \
                "Dhcp6.GetModeData - GetModeData with both Dhcp6ConfigData and Dhcp6ModeData." \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

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
RecordAssertion $assert  $Dhcp6GetModeDataFunc1AssertionGuid004    \
                "When Start returns, the state of IA should be Dhcp6Bound"

set assert pass
GetVar     R_Dhcp6CfgData.OptionCount
if { ${R_Dhcp6CfgData.OptionCount}!= 0} {
     set assert fail
}
RecordAssertion $assert $Dhcp6GetModeDataFunc1AssertionGuid005 \
               "Dhcp6.GetModeData -Func- Dhcp6CfgData.OptionCount should be 0"

set assert pass
GetVar     R_Dhcp6CfgData.OptionList

if { ${R_Dhcp6CfgData.OptionList}!= 0} {
     set assert fail
}
RecordAssertion $assert $Dhcp6GetModeDataFunc1AssertionGuid006 \
               "Dhcp6.GetModeData -Func- Dhcp6CfgData.OptionList should be 0"

set assert pass
GetVar     R_Dhcp6CfgData.IaDescriptor.Type
GetVar     R_Dhcp6CfgData.IaDescriptor.IaId
set   type [expr ${R_Dhcp6CfgData.IaDescriptor.Type} != $Dhcp6IATypeNA]
set   IaId [expr ${R_Dhcp6CfgData.IaDescriptor.IaId} != 1]
if { [expr $type || $IaId]} {
     set assert fail
}
RecordAssertion $assert $Dhcp6GetModeDataFunc1AssertionGuid007 \
               "Dhcp6.GetModeData -Func-Check whether the parameter is the same as configured"

set assert pass
GetVar R_IaInfoEvent
GetVar R_Dhcp6CfgData.IaInfoEvent 
if {${R_Dhcp6CfgData.IaInfoEvent} != $R_IaInfoEvent} {
    set assert fail
}
RecordAssertion $assert $Dhcp6GetModeDataFunc1AssertionGuid008 \
                "Dhcp6.GetModeData -Func-IaInfoEvent should be the same as we configured before" 

set assert pass 
GetVar    R_Dhcp6CfgData.ReconfigureAccept;                    #0:FALSE 1:TRUE
if {${R_Dhcp6CfgData.ReconfigureAccept} != 0} {
     set asser fail 
}
RecordAssertion $assert $Dhcp6GetModeDataFunc1AssertionGuid009 \
                "Dhcp6.GetModeData -Func-ReconfigAccept should be FALSE"

set assert pass 
GetVar     R_Dhcp6CfgData.RapidCommit;                         #0:FALSE 1:TRUE
if {${R_Dhcp6CfgData.RapidCommit} != 0} {
     set asser fail 
}
RecordAssertion $assert $Dhcp6GetModeDataFunc1AssertionGuid010 \
                "Dhcp6.GetModeData -Func-RapidCommit should be FALSE"

set assert pass
GetVar R_ConfigData.SolicitRetransmission
UINT32                                  R_SolicitRetransmission1(4)

SetVar   R_CopyLen [Sizeof R_SolicitRetransmission1]
BS->CopyMem  "&@R_SolicitRetransmission1, @R_ConfigData.SolicitRetransmission, @R_CopyLen, &@R_Status"
GetAck
GetVar  R_SolicitRetransmission1
GetVar  R_SolicitRetransmission
set i 0
while {[expr $i < 4]!= 0} {
  if {$i == 0} {
    set temp1 $R_SolicitRetransmission1(0)
    set temp2 $R_SolicitRetransmission(0)
    if {$temp1 == $temp2} {
      set i [expr $i + 1]
    } else {
      break
    }
  }
  
  if {$i == 1} {
    set temp1 $R_SolicitRetransmission1(1)
    set temp2 $R_SolicitRetransmission(1)
    if {$temp1 == $temp2} {
      set i [expr $i + 1]
    } else {
      break
    }
  }

  if {$i == 2} {
    set temp1 $R_SolicitRetransmission1(2)
    set temp2 $R_SolicitRetransmission(2)
    if {$temp1 == $temp2} {
      set i [expr $i + 1]
    } else {
      break
    }
  }

  if {$i == 3} {
    set temp1 $R_SolicitRetransmission1(3)
    set temp2 $R_SolicitRetransmission(3)
    if {$temp1 == $temp2} {
      set i [expr $i + 1]
    } else {
      break
    }
  }

}
if {$i != 4} {
    set assert fail
}
RecordAssertion $assert $Dhcp6GetModeDataFunc1AssertionGuid011 \
                "Dhcp6.GetModeData -Func-SolicitRetransmission should be the same as we configured"

CleanUpEnvironment
