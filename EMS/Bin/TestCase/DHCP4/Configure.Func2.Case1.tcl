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
CaseGuid        4f94bd03-2f46-4c02-bf21-987b16eaa043
CaseName        Configure.Func2.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
                -- A) Access denied when another DHCP instance is already in a \
                valid state.                                                   \
                   B)if one instance wants to make it possible for another     \
                 instance, it must call Dhcp4->Configure with  DhcpCfgData     \
                 set to Null. }

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle1, &@R_Status"
  GetAck

  Dhcp4ServiceBinding->DestroyChild "@R_Handle2, &@R_Status"
  GetAck

  EndScope _DHCP4_CONFIGURE_FUNC2
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_CONFIGURE_FUNC2

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                                           R_Status
UINTN                                           R_Handle1
UINTN                                           R_Handle2
UINT32                                          R_Timeout(2)
EFI_DHCP4_CONFIG_DATA                           R_ConfigData
EFI_DHCP4_MODE_DATA                             R_ModeData

#
# Call [DHCP4SBP] -> CreateChild to create child 1.
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle1, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1

#
# Call [DHCP4] -> Configure () to initialize Child 1.
#
SetVar    R_Timeout(0)                          1
SetVar    R_Timeout(1)                          2
SetVar    R_ConfigData.DiscoverTryCount         2
SetVar    R_ConfigData.DiscoverTimeout          &@R_Timeout
SetVar    R_ConfigData.RequestTryCount          2
SetVar    R_ConfigData.RequestTimeout           &@R_Timeout
SetVar    R_ConfigData.OptionCount              0
SetVar    R_ConfigData.OptionList               0                   
SetIpv4Address  R_ConfigData.ClientAddress      "192.168.1.1"
SetVar    R_ConfigData.Dhcp4Callback            0;  # CallbackList[1] = Abort
SetVar    R_ConfigData.CallbackContext          0;

Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Initialize Child 1"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4SBP] -> CreateChild () to create DHCP Child2
#
Dhcp4ServiceBinding->CreateChild "&@R_Handle2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.CreateChild - Create Child 2"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2

#
# Check Point: Call [DHCP4] -> Configure () to initialize Child2
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ACCESS_DENIED]
RecordAssertion $assert $Dhcp4ConfigureFunc2AssertionGuid001                   \
                "Dhcp4.CreateChild - Initialzie Child 2"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ACCESS_DENIED"

#
# Check Point: Call [DHCP4] -> Configure () to reset Child1
#
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1
Dhcp4->Configure "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4ConfigureFunc2AssertionGuid001                   \
                "Dhcp4.CreateChild - Reset Child 1"                            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call [DHCP4] -> Configure () to initialize Child2
#
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4ConfigureFunc2AssertionGuid001                   \
                "Dhcp4.CreateChild - Initialize Child 2"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment