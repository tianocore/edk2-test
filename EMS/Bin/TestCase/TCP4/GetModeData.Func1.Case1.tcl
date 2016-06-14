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

#
# test case Name, category, description, GUID...
#
CaseGuid          200BBFC7-3E68-4a0c-AC1A-16A5859EA3C5
CaseName          GetModeData.Func1.Case1
CaseCategory      TCP
CaseDescription   {This case is to test the functionality -- with one OPTIONAL \
parameter is NULL.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Tcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _TCP4_SPEC_FUNCTIONALITY_
  EndLog
}

#
# Begin log ...
#
BeginLog


#
# BeginScope
#
BeginScope _TCP4_SPEC_FUNCTIONALITY_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Tcp4State
UINTN                            R_Context

EFI_TCP4_CONFIG_DATA             R_Tcp4ConfigData
EFI_IP4_MODE_DATA                R_Ip4ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA  R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE          R_SnpModeData

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData

#
# Initialization of TCB related on OS side.
#
LocalEther  $DEF_ENTS_MAC_ADDR
RemoteEther $DEF_EUT_MAC_ADDR
LocalIp     $DEF_ENTS_IP_ADDR
RemoteIp    $DEF_EUT_IP_ADDR

#
# Create Tcp4 Child.
#
Tcp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4SBP.CreateChild - Create Child 1"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure TCP instance.
#
SetVar          R_Configure_AccessPoint.UseDefaultAddress  FALSE
SetIpv4Address  R_Configure_AccessPoint.StationAddress     $DEF_EUT_IP_ADDR
SetIpv4Address  R_Configure_AccessPoint.SubnetMask         $DEF_EUT_MASK
SetVar          R_Configure_AccessPoint.StationPort        $DEF_EUT_PRT
SetIpv4Address  R_Configure_AccessPoint.RemoteAddress      $DEF_ENTS_IP_ADDR
SetVar          R_Configure_AccessPoint.RemotePort         $DEF_ENTS_PRT
SetVar          R_Configure_AccessPoint.ActiveFlag         TRUE

SetVar R_Configure_Tcp4ConfigData.TypeOfService       1
SetVar R_Configure_Tcp4ConfigData.TimeToLive          128
SetVar R_Configure_Tcp4ConfigData.AccessPoint         @R_Configure_AccessPoint
SetVar R_Configure_Tcp4ConfigData.ControlOption       0

Tcp4->Configure {&@R_Configure_Tcp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Configure - Configure Child 1."                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Calling Tcp4.GetModeData(),
#              with one optional parameter is NULL.
#
Tcp4->GetModeData {NULL, &@R_Tcp4ConfigData, &@R_Ip4ModeData,                  \
                   &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp4GetModeDataFunc1AssertionGuid001                  \
                "Tcp4.GetModeData - Call GetModeData() with parameter          \
                *Tcp4State is NULL."                                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Tcp4->GetModeData {&@R_Tcp4State, NULL, &@R_Ip4ModeData,                       \
                   &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp4GetModeDataFunc1AssertionGuid002                  \
                "Tcp4.GetModeData - Call GetModeData() with parameter          \
                *Tcp4ConfigData is NULL."                                      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Tcp4->GetModeData {&@R_Tcp4State, &@R_Tcp4ConfigData, NULL,                    \
                   &@R_MnpConfigData, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp4GetModeDataFunc1AssertionGuid003                  \
                "Tcp4.GetModeData - Call GetModeData() with parameter          \
                *Ip4ModeData is NULL."                                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Tcp4->GetModeData {&@R_Tcp4State, &@R_Tcp4ConfigData, &@R_Ip4ModeData,         \
                   NULL, &@R_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp4GetModeDataFunc1AssertionGuid004                  \
                "Tcp4.GetModeData - Call GetModeData() with parameter          \
                *MnpConfigData is NULL."                                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Tcp4->GetModeData {&@R_Tcp4State, &@R_Tcp4ConfigData, &@R_Ip4ModeData,         \
                   &@R_MnpConfigData, NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp4GetModeDataFunc1AssertionGuid005                  \
                "Tcp4.GetModeData - Call GetModeData() with parameter          \
                *SnpModeData is NULL."                                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment
