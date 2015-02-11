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
CaseVerboseLevel  DEFAULT 
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        00CE5B70-2FC9-4e0b-8645-C4DFA6027A3A
CaseName        GetModeData.Func1.Case1
CaseCategory    Udp4
CaseDescription {Test the GetModeData Function of UDP4 - Invoke GetModeData() to\
                 get all-mode/Udp4/Ip4/Mnp/Snp data before/after configuration.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _UDP4_GETMODEDATA_FUNCTION1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_UDP4_CONFIG_DATA             R_Udp4ConfigData
EFI_IP4_MODE_DATA                R_Ip4ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE          R_SnpModeData

Udp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ud4SBP.GetModeData - Func - Create Child"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Udp4ConfigData.AcceptBroadcast             TRUE
SetVar R_Udp4ConfigData.AcceptPromiscuous           FALSE
SetVar R_Udp4ConfigData.AcceptAnyPort               FALSE
SetVar R_Udp4ConfigData.AllowDuplicatePort          FALSE
SetVar R_Udp4ConfigData.TypeOfService               0
SetVar R_Udp4ConfigData.TimeToLive                  8
SetVar R_Udp4ConfigData.DoNotFragment               TRUE
SetVar R_Udp4ConfigData.ReceiveTimeout              2
SetVar R_Udp4ConfigData.TransmitTimeout             2
SetVar R_Udp4ConfigData.UseDefaultAddress           FALSE
SetIpv4Address R_Udp4ConfigData.StationAddress      "192.168.88.1"
SetIpv4Address R_Udp4ConfigData.SubnetMask          "255.255.255.0"
SetVar R_Udp4ConfigData.StationPort                 999
SetIpv4Address R_Udp4ConfigData.RemoteAddress       "192.168.88.2"
SetVar R_Udp4ConfigData.RemotePort                  666


Udp4->GetModeData {&@R_Udp4ConfigData, &@R_Ip4ModeData, &@R_MnpConfigData,     \
                   &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Udp4GetModeDataFunc1AssertionGuid001                  \
                "Udp4.GetModeData - Func - Get all Mode Data"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

Udp4->GetModeData {&@R_Udp4ConfigData, NULL, NULL, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Udp4GetModeDataFunc1AssertionGuid002                  \
                "Udp4.GetModeData - Func - Get Udp4 Data"                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

Udp4->GetModeData {NULL, &@R_Ip4ModeData, NULL, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4GetModeDataFunc1AssertionGuid003                  \
                "Udp4.GetModeData - Func - Get Ip4 Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->GetModeData {NULL, NULL, &@R_MnpConfigData, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4GetModeDataFunc1AssertionGuid004                  \
                "Udp4.GetModeData - Func - Get Mnp Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->GetModeData {NULL, NULL, NULL, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4GetModeDataFunc1AssertionGuid005                  \
                "Udp4.GetModeData - Func - Get Snp Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4.Configure - Config Child 1"                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->GetModeData {&@R_Udp4ConfigData, &@R_Ip4ModeData, &@R_MnpConfigData,     \
                   &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4GetModeDataFunc1AssertionGuid006                  \
                "Udp4.GetModeData - Func - Get all Mode Data"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->GetModeData {&@R_Udp4ConfigData, NULL, NULL, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4GetModeDataFunc1AssertionGuid007                  \
                "Udp4.GetModeData - Func - Get Udp4 Data"                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->GetModeData {NULL, &@R_Ip4ModeData, NULL, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4GetModeDataFunc1AssertionGuid008                  \
                "Udp4.GetModeData - Func - Get Ip4 Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->GetModeData {NULL, NULL, &@R_MnpConfigData, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4GetModeDataFunc1AssertionGuid009                  \
                "Udp4.GetModeData - Func - Get Mnp Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->GetModeData {NULL, NULL, NULL, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4GetModeDataFunc1AssertionGuid010                  \
                "Udp4.GetModeData - Func - Get Snp Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SBP.DestroyChild - Func - Destroy Child"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# End scope
#
EndScope _UDP4_GETMODEDATA_FUNCTION1_CASE1_

#
# End Log
#
EndLog
