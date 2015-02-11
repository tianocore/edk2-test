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
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  default

#
# test case Name, category, description, GUID...
#
CaseGuid        67C85B8D-8F49-4c86-95C1-E3BFAE4EAE44
CaseName        ArpRfc.Func.Case1
CaseCategory    ARP
CaseDescription {This case is to test the RFC function of ARP.}
################################################################################

proc CleanUpEutEnvironment {} {
  Arp->Delete {TRUE, NULL, &@R_Status}
  GetAck

  Arp->Delete {FALSE, NULL, &@R_Status}
  GetAck
 
  ArpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
  GetAck
 
  EndCapture
  EndScope _ARP_FUNC_CONFORMANCE_
  VifDown 0
  EndLog
}

#
# Begin log ...
#
BeginLog

Include ARP/include/Arp.inc.tcl

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

VifUp 0 172.16.210.162 255.255.255.0
BeginScope _ARP_FUNC_CONFORMANCE_

UINTN                            R_Status
UINTN                            R_Handle
EFI_IP_ADDRESS                   R_StationAddress
EFI_ARP_CONFIG_DATA              R_ArpConfigData

ArpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "ArpSBP.CreateChild - Create Child 1"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetIpv4Address R_StationAddress.v4     "172.16.210.102"
SetVar R_ArpConfigData.SwAddressType   0x800
SetVar R_ArpConfigData.SwAddressLength 4
SetVar R_ArpConfigData.StationAddress  &@R_StationAddress
SetVar R_ArpConfigData.EntryTimeOut    0
SetVar R_ArpConfigData.RetryCount      30
SetVar R_ArpConfigData.RetryTimeOut    5000000

#
# Check point
#
Arp->Configure {&@R_ArpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Configure - Config Child 1"                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set L_Filter "ether proto \\arp and src host 172.16.210.102"
StartCapture CCB $L_Filter

#
# Send ARP request
#
LocalEther  00:02:03:04:05:07
RemoteEther ff:ff:ff:ff:ff:ff
LocalIp     172.16.210.161
RemoteIp    172.16.210.102

CreatePayload ReqPktPayload const 18 0x0
CreatePacket ArpReqPkt -t arp -arp_op 1 -arp_tha 00:00:00:00:00:00 -arp_payload\
              ReqPktPayload

SendPacket ArpReqPkt

ReceiveCcbPacket CCB ReqReplyPkt 10
if { ${CCB.received} == 0} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Arp.Reply - Send Reply"                                     \
                  "Packet not captured"
  
  CleanUpEutEnvironment
  return
}

set assert pass
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Arp.Reply - Send Reply"                                       \
                "Send Reply packet"

DumpPacket ReqReplyPkt
ValidatePacket ReqReplyPkt -t arp "(arp_hrd=1)AND(arp_pro=0x0800)AND(arp_hln=6)\
                          AND(arp_pln=4)AND(arp_op=2)AND(arp_sha=$targetmac)AND\
                          (arp_spa=172.16.210.102)AND(arp_tha=00:02:03:04:05:07)\
                           AND(arp_tpa=172.16.210.161)"
if {[string compare -nocase $EMS_RESULT "TRUE"] == 0} {
  set assert pass
} else {
  set assert fail
}
RecordAssertion $assert $ArpRfcFuncAssertionGuid001                            \
                 "Arp - check packet field"

CleanUpEutEnvironment