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
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        6f5cfbcd-d313-44ce-a8e7-14a5518ef61b
CaseName        TransmitReceive.Conf1.Case4
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_INVALID_PARAMETER  \
                -- transaction id in Packet is in use by another DHCP process.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4->Stop "&@R_Status"
  GetAck

  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  BS->CloseEvent	"@R_Event, &@R_Status"
  GetAck

  EndCapture
  EndScope _DHCP4_TRANSMITRECEIVE_CONF1
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_TRANSMITRECEIVE_CONF1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                               R_Status
UINTN                               R_Handle

UINTN                               R_Context
UINTN                               R_Event
EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN    R_Token
EFI_DHCP4_LISTEN_POINT              R_ListenPoint
EFI_DHCP4_PACKET                    R_Packet

EFI_DHCP4_CONFIG_DATA               R_ConfigData
UINT32                              R_Timeout(2)

#
# Call [DHCP4SBP] -> CreateChild to create child.
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                &@R_Event, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid  "BS.CreateEvent."               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> TransmitReceive with the invalid parameters
# o	The transaction id in Packet is in use by another DHCP process.
#
SetIpv4Address  R_ListenPoint.ListenAddress   "0.0.0.0"
SetIpv4Address  R_ListenPoint.SubnetMask      "255.255.255.255"
SetVar          R_ListenPoint.ListenPort      68

SetVar  R_Packet.Size                     [expr [Sizeof EFI_DHCP4_HEADER]]
SetVar  R_Packet.Length                   [expr [Sizeof EFI_DHCP4_HEADER] + 5]
SetVar  R_Packet.Dhcp4.Magik              0x63538263; #0x63825363
SetVar  R_Packet.Dhcp4.Header.OpCode      1
SetVar  R_Packet.Dhcp4.Header.HwType      1
SetVar  R_Packet.Dhcp4.Header.HwAddrLen   6
SetIpv4Address  R_Packet.Dhcp4.Header.ClientAddr    "192.168.11.21" 
SetVar  R_Packet.Dhcp4.Header.ClientHwAddr  { 0x00 0x0d 0x60 0x36 0x87 0x49}
SetVar  R_Packet.Dhcp4.Option               {0xff}

SetVar          R_Token.Status             0
SetVar          R_Token.CompletionEvent    0
SetIpv4Address  R_Token.RemoteAddress      "192.168.1.34" 
SetVar          R_Token.RemotePort         0
SetVar          R_Token.ListenPointCount   1
SetVar          R_Token.ListenPoints       &@R_ListenPoint
SetVar          R_Token.TimeoutValue       10;   #TimeoutValue is 10s

#
# a). Start DHCP Configuration process
# a1: Call [DHCP4] -> Configure to initialize the child with the following parameters
#   o   DiscoverRetryCount=2, DiscoverTimeout=10,20
#   o   RequestRetryCount=2, RequestTimeout=10,20
#   o   ClientAddress=0.0.0.0
#   o   Dhcp4CallBack=(Self-defined-callback: Abort when in DHCP4Seleting state)
#   o   OptionCount=1, OptionList=ClientIdentifier
#
SetVar  R_Timeout(0)                        10
SetVar  R_Timeout(1)                        20
SetVar  R_ConfigData.DiscoverTryCount       2
SetVar  R_ConfigData.DiscoverTimeout        &@R_Timeout
SetVar  R_ConfigData.RequestTryCount        2
SetVar  R_ConfigData.RequestTimeout         &@R_Timeout
SetIpv4Address  R_ConfigData.ClientAddress  "0.0.0.0"
SetVar  R_ConfigData.Dhcp4Callback          0

Dhcp4->Configure  "&@R_ConfigData, &@R_Status"
GetAck
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Create Child 1"                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


set L_Filter "udp src port 68"
StartCapture CCB $L_Filter

#
# a2:  Call [DHCP4] -> Start to start DHCP4 configuration process.
# o  CompletionEvnet = A valid Event
#
Dhcp4->Start "@R_Event, &@R_Status"
GetAck

#
# b). Capture packet and parse transition ID
#
ReceiveCcbPacket CCB discoverpacket 30
if { ${CCB.received} == 0} {
	set assert fail
	RecordAssertion $assert $GenericAssertionGuid                                \
                  "Dhcp4.Start - No DHCPDISCOVER packet Captured."
	
	CleanUpEutEnvironment 
  return
} else {
  set assert pass
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPDISCOVER Packets"

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - No Response with in the specified timeout value"\
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# c). Set Xid in packet to be the currently used Xid
#
ParsePacket discoverpacket -t dhcp -dhcp_xid xid
puts "Xid=$xid"
puts "test xid"
SetVar  R_Packet.Dhcp4.Header.Xid       [Htonl $xid]
SetVar  R_Token.Packet                  &@R_Packet

#
# Check Point: Call Dhcp4.TransmitReceive while XID already in use .
#
Dhcp4->TransmitReceive "&@R_Token, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4TransmitReceiveConf1AssertionGuid004             \
                "Dhcp4.TransmitReceive - Conf - (InvalidPara)XID in use."      \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment
