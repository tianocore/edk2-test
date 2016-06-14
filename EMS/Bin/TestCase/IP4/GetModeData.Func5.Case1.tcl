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
CaseGuid        40C62405-70A7-49ec-A20B-31A7B515E3D7
CaseName        GetModeData.Func5.Case1
CaseCategory    IP4
CaseDescription {Test the GetModeData Function of IP4 - Invoke GetModeData() to\
                 check the instance status when Configure() has been called    \
                 with the parameter Ip4ModeData being NULL.}
################################################################################

Include IP4/include/Ip4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# Begin scope
#
BeginScope _IP4_GETMODEDATA_FUNCTION5_CASE1_

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
EFI_IP4_MODE_DATA                R_Ip4ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE          R_SnpModeData

Ip4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SBP.GetModeData - Func - Create Child"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_IpConfigData.DefaultProtocol          0
SetVar R_IpConfigData.AcceptAnyProtocol        TRUE
SetVar R_IpConfigData.AcceptIcmpErrors         TRUE
SetVar R_IpConfigData.AcceptBroadcast          TRUE
SetVar R_IpConfigData.AcceptPromiscuous        TRUE
SetVar R_IpConfigData.UseDefaultAddress        FALSE
SetIpv4Address R_IpConfigData.StationAddress   "172.16.210.102"
SetIpv4Address R_IpConfigData.SubnetMask       "255.255.255.0"
SetVar R_IpConfigData.TypeOfService            0
SetVar R_IpConfigData.TimeToLive               16
SetVar R_IpConfigData.DoNotFragment            TRUE
SetVar R_IpConfigData.RawData                  FALSE
SetVar R_IpConfigData.ReceiveTimeout           0
SetVar R_IpConfigData.TransmitTimeout          0

#
# check point
#
Ip4->GetModeData {&@R_Ip4ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Func - Get Mode Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set assert pass
GetVar R_Ip4ModeData.IsStarted
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "false"] != 0} {
  set assert fail
}
GetVar R_Ip4ModeData.IsConfigured
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "false"] != 0} {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                        "Ip4.GetModeData - Func - check status"

Ip4->Configure {&@R_IpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Func - Config Child 1"                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# check point
#
Ip4->GetModeData {&@R_Ip4ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Func - Get Mode Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set assert pass
GetVar R_Ip4ModeData.IsStarted
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "true"] != 0} {
  set assert fail
}
GetVar R_Ip4ModeData.IsConfigured
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "true"] != 0} {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                        "Ip4.GetModeData - Func - check status"

Ip4->Configure {NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Func - Reset Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Ip4->GetModeData {&@R_Ip4ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4.GetModeData - Func - Get Mode Data"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set assert pass
GetVar R_Ip4ModeData.IsStarted
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "false"] != 0} {
  set assert fail
}
GetVar R_Ip4ModeData.IsConfigured
if {[string compare -nocase ${R_Ip4ModeData.IsStarted} "false"] != 0} {
  set assert fail
}
RecordAssertion $assert $Ip4GetModeDataFunc5AssertionGuid001                   \
                        "Ip4.GetModeData - Func - check status"

Ip4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Ip4SB.GetModeData - Func - Destroy Child"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

VifDown 0

#
# End scope
#
EndScope _IP4_GETMODEDATA_FUNCTION5_CASE1_

#
# End Log
#
EndLog
