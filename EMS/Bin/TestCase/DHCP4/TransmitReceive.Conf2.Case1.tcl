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
CaseGuid        8ce002cf-24f5-4a0c-a984-2ee5711aab43
CaseName        TransmitReceive.Conf2.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_NOT_READY          \
                -- Previous call not end}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _DHCP4_TRANSMITRECEIVE_CONF2
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_TRANSMITRECEIVE_CONF2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                                 R_Status
UINTN                                 R_Handle
                                      
UINTN                                 R_Context
EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN      R_Token
EFI_DHCP4_LISTEN_POINT                R_ListenPoint
EFI_DHCP4_PACKET                      R_Packet
EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN      R_Token2

EFI_DHCP4_MODE_DATA              R_ModeData

EFI_DHCP4_CONFIG_DATA            R_ConfigData
UINT32                           R_Timeout(2)
                                      
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
                &@R_Token.CompletionEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid  "BS.CreateEvent."               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4]->Configure to initialize the child with the following parameters
# o	DiscoverRetryCount=2, DiscoverTimeout=5,10
# o	RequestRetryCount=2, RequestTimeout=1,2
# o	ClientAddress=192.168.2.4
# o	Dhcp4CallBack=NULL
# o	OptionCount=0, OptionList=NULL
#
SetVar  R_Timeout(0)                           5
SetVar  R_Timeout(1)                           10
SetVar  R_ConfigData.DiscoverTryCount          2
SetVar  R_ConfigData.DiscoverTimeout           &@R_Timeout
SetVar  R_ConfigData.RequestTryCount           2
SetVar  R_ConfigData.RequestTimeout            &@R_Timeout
SetVar  R_ConfigData.Dhcp4Callback             0
SetVar  R_ConfigData.CallbackContext           0
SetIpv4Address R_ConfigData.ClientAddress      "192.168.2.4"

Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Func - Configure Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> Start to start DHCP4 configuration process, 
# require Signal Event when the process complete.
#
set L_Filter "udp src port 68 and ether host $targetmac"
StartCapture CCB $L_Filter

#
# Check Point: Call Dhcp4->Start to validate the configure process.
# 1).Capture and validate DHCPREQUEST packet 
# 
Dhcp4->Start "0, &@R_Status"

ReceiveCcbPacket CCB  RequestPacket   15

set assert pass
if { ${CCB.received} == 0 } {
  set assert fail
  GetAck
	RecordAssertion $assert $Dhcp4StartFunc2AssertionGuid005                     \
                  "Dhcp4.Start - No RequestPacket packet Captured."
  
  CleanUpEutEnvironment
  return
} else {
  ParsePacket RequestPacket -t dhcp -dhcp_xid xid -dhcp_htype htype -dhcp_hlen\
              hlen -dhcp_chaddr chaddr -dhcp_options options
  ParsePacket RequestPacket -t eth -eth_src eth_src
  CreateDhcpOpt opt1 mesg_type 3;       #Message Type = DHCPREQUEST
  set result1 [DhcpOptOpt options opt1]
  if { $result1 != 0} {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPREQUEST Packets"

#
# 2). Send DHCPACK packet to DHCP client
#
LocalEther   0:3:5:6:6:7
RemoteEther  $eth_src
LocalIp      192.168.2.1

CreateDhcpOpt ack1_opt1 mesg_type  5;    #Message Type = DHCPACK
CreateDhcpOpt ack1_opt2 server_id  "192.168.2.1"
CreateDhcpOpt ack1_opt3 ip_lease_t 120
CreateDhcpOpt ack1_opt4 req_ip_addr "192.168.2.4"
ConcatPayload ack1_opt1 ack1_opt1 ack1_opt2 ack1_opt3 ack1_opt4
CreatePacket  ack -t dhcp -dhcp_xid $xid -dhcp_op 2 -dhcp_htype $htype         \
              -dhcp_hlen $hlen -dhcp_chaddr $chaddr -dhcp_yiaddr 192.168.2.4   \
              -dhcp_options ack1_opt1

SendPacket    ack
DestroyPacket

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4StartFunc2AssertionGuid005                       \
                "Dhcp4.Start - Check the config data effect."                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Mode Data After Start Exit
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar  R_ModeData.State
  set tempaddr [GetIpv4Address R_ModeData.ClientAddress]
  if { ${R_ModeData.State} != $Dhcp4Bound } {
    set assert fail
  } else {
    if { [string compare -nocase $tempaddr "192.168.2.4"] != 0 } {
      set assert fail
    }
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Func - Check the DHCP instance State"           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "CurState - ${R_ModeData.State}, ExpectState - $Dhcp4Bound     \
                CurClientAddress - $tempaddr, ExpectClientAddr - 192.168.2.4."
		
				
				
				
				
				
				
#
# Call [DHCP4] -> TransmitReceive with the following parameters
# o TimeoutValue: 		10 seconds
# o CompletionEvent:	A valid Event
#
SetIpv4Address  R_ListenPoint.ListenAddress   "192.168.2.21"
SetIpv4Address  R_ListenPoint.SubnetMask      "255.255.255.0"
SetVar          R_ListenPoint.ListenPort      68

SetVar  R_Packet.Size                     [Sizeof EFI_DHCP4_PACKET]
SetVar  R_Packet.Length                   [expr [Sizeof EFI_DHCP4_HEADER] + 5]
SetVar  R_Packet.Dhcp4.Magik              0x63538263
SetVar  R_Packet.Dhcp4.Header.OpCode      1
SetVar  R_Packet.Dhcp4.Header.HwType      1
SetVar  R_Packet.Dhcp4.Header.HwAddrLen   6
SetVar  R_Packet.Dhcp4.Header.Xid         0xe139e46c
SetIpv4Address  R_Packet.Dhcp4.Header.ClientAddr    "192.168.2.24"
SetVar  R_Packet.Dhcp4.Header.ClientHwAddr  { 0x00 0x0d 0x60 0x36 0x87 0x49}
SetVar  R_Packet.Dhcp4.Option               {0xff}

SetVar  R_Token.Status                    0
SetIpv4Address  R_Token.RemoteAddress     "192.168.2.2" 
SetVar  R_Token.RemotePort                67
SetVar  R_Token.ListenPointCount          1
SetVar  R_Token.ListenPoints              &@R_ListenPoint
SetVar  R_Token.TimeoutValue              10;       #TimeoutValue is 10s
SetVar  R_Token.Packet                    &@R_Packet

Dhcp4->TransmitReceive "&@R_Token, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.TransmitReceive - Previous Call Not End - 1nd Call"     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> TransmitReceive before TimeoutValue expires.
#
SetVar  R_Token2                          @R_Token
SetVar  R_Token2.CompletionEvent          0

#
# Check Point: Call Dhcp4.TransmitReceive while while the previous call to this 
#              function has not finished yet.
#
Dhcp4->TransmitReceive "&@R_Token2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_READY]
RecordAssertion $assert $Dhcp4TransmitReceiveConf2AssertionGuid001             \
                "Dhcp4.TransmitReceive - Previous Call Not End - 2nd Call"     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_READY"

Stall   10

#
# Close Event.
#
BS->CloseEvent "@R_Token.CompletionEvent, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CloseEvent."                                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Dhcp4->Stop "&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Stop - Stop"     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"				
				
				
#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment
