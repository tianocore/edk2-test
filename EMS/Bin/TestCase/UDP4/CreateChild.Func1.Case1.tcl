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
CaseGuid        1253C922-40DB-4bcd-9D81-19EC13DD2E4A
CaseName        CreateChild.Func1.Case1
CaseCategory    Udp4
CaseDescription {Test the CreateChild Function of UDP4 - Invoke CreateChild()\
                 to create three instances.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _UDP4_CREATECHILD_FUNCTION1_CASE1_


UINTN                            R_Status
UINTN                            R_Handle1
UINTN                            R_Handle2
UINTN                            R_Handle3
EFI_UDP4_CONFIG_DATA             R_Udp4ConfigData

SetVar R_Udp4ConfigData.AcceptBroadcast             TRUE
SetVar R_Udp4ConfigData.AcceptPromiscuous           TRUE
SetVar R_Udp4ConfigData.AcceptAnyPort               TRUE
SetVar R_Udp4ConfigData.AllowDuplicatePort          TRUE
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


Udp4ServiceBinding->CreateChild "&@R_Handle1, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.CreateChild - Func - Create Child 1"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.CreateChild - Func - Config Child 1"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4ServiceBinding->CreateChild "&@R_Handle2, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.CreateChild - Func - Create Child 2"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->Configure "&@R_Udp4ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.CreateChild - Func - Config Child 2"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4ServiceBinding->CreateChild "&@R_Handle3, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle3
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4CreateChildFunc1AssertionGuid001                  \
                "Udp4SB.CreateChild - Func - Create Child 3"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.CreateChild - Func - Config Child 3"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4ServiceBinding->DestroyChild {@R_Handle1, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.DestroyChild - Destroy Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"  

Udp4ServiceBinding->DestroyChild {@R_Handle2, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.DestroyChild - Destroy Child 2"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4ServiceBinding->DestroyChild {@R_Handle3, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.DestroyChild - Destroy Child 3"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - EFI_SUCCESS" 

#
# End scope
#
EndScope  _UDP4_CREATECHILD_FUNCTION1_CASE1_

#
# EndLog
#
EndLog
                                                                                                                                                                                                                                                             
