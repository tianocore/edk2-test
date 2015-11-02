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
# Copyright 2006 - 2013 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR> 
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
CaseGuid        30E5CCF2-2595-4a66-83D6-D58F9426636E
CaseName        Transmit.Conf1.Case3
CaseCategory    IP4
CaseDescription {Test the Transmit Conformance of IP4 - Invoke Transmit() when \
                the IP header in FragmentTable is not a well-formed header and \
                RawData is TRUE.The return status should be EFI_INVALID_PARAMETER.}
################################################################################

Include IP4/include/Ip4.inc.tcl

proc CleanUpEutEnvironment {} {
  Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
  GetAck

  BS->CloseEvent "@R_Token.Event, &@R_Status"
  GetAck

  EndCapture
  
  VifDown 0
  
  EndScope _IP4_TRANSMIT_CONFORMANCE1_CASE3_
  
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _IP4_TRANSMIT_CONFORMANCE1_CASE3_

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

VifUp 0 172.16.210.162 255.255.255.0

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_IP4_CONFIG_DATA              R_IpConfigData
UINTN                            R_Context
EFI_IP4_COMPLETION_TOKEN         R_Token
EFI_IP4_TRANSMIT_DATA            R_TxData
EFI_IP4_FRAGMENT_DATA            R_FragmentTable
CHAR8                            R_FragmentBuffer(1600)
EFI_IP4_OVERRIDE_DATA            R_OverrideData

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.Transmit - Conf - Create Child"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_IpConfigData.DefaultProtocol            0
SetVar R_IpConfigData.AcceptAnyProtocol          TRUE
SetVar R_IpConfigData.AcceptIcmpErrors           TRUE
SetVar R_IpConfigData.AcceptBroadcast            TRUE
SetVar R_IpConfigData.AcceptPromiscuous          TRUE
SetVar R_IpConfigData.UseDefaultAddress          FALSE
SetIpv4Address R_IpConfigData.StationAddress     "172.16.210.102"
SetIpv4Address R_IpConfigData.SubnetMask         "255.255.255.0"
SetVar R_IpConfigData.TypeOfService              0
SetVar R_IpConfigData.TimeToLive                 16
SetVar R_IpConfigData.DoNotFragment              TRUE
SetVar R_IpConfigData.RawData                    TRUE
SetVar R_IpConfigData.ReceiveTimeout             0
SetVar R_IpConfigData.TransmitTimeout            0

Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.Transmit - Conf - Config Child"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

if { $R_Status != $EFI_SUCCESS} {
  CleanUpEutEnvironment
  return
}

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Token.Event, &@R_Status"
GetAck

SetIpv4Address R_TxData.DestinationAddress "172.16.210.162"
SetVar R_TxData.TotalDataLength 38
SetVar R_TxData.FragmentCount 1

SetVar R_FragmentBuffer(0)  0x45
SetVar R_FragmentBuffer(1)  0x01
SetVar R_FragmentBuffer(2)  0x00
SetVar R_FragmentBuffer(3)  0x26
SetVar R_FragmentBuffer(8)  0x08
SetVar R_FragmentBuffer(9)  0xfc
SetVar R_FragmentBuffer(10) 0xb4
SetVar R_FragmentBuffer(11) 0xb2
SetVar R_FragmentBuffer(12) 0xac
SetVar R_FragmentBuffer(13) 0x10
SetVar R_FragmentBuffer(14) 0xd2
SetVar R_FragmentBuffer(15) 0x66
SetVar R_FragmentBuffer(16) 0xac
SetVar R_FragmentBuffer(17) 0x10
SetVar R_FragmentBuffer(18) 0xd2
SetVar R_FragmentBuffer(19) 0xa1

SetVar R_FragmentTable.FragmentLength 38
SetVar R_FragmentTable.FragmentBuffer &@R_FragmentBuffer
SetVar R_TxData.FragmentTable         @R_FragmentTable
SetVar R_Token.Packet                 &@R_TxData

#
# check sum invalid
#
SetVar R_FragmentBuffer(10) 0x5a
SetVar R_FragmentBuffer(11) 0x5a

#
# check point
#
Ip4->Transmit {&@R_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Ip4TransmitConf1AssertionGuid014                      \
                "Ip4.Transmit - Conf - With not well-formed header"            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

CleanUpEutEnvironment
