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
# Copyright 2006 - 2017 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR> 
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
CaseGuid        f7d1a72e-50aa-4623-a36c-886d084c6792
CaseName        Configure.Conf3.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_INVALID_PATAMETER  \
	              -- A). DiscoverTryCount > 0 and DiscoverTimeout is NULL.       \
                   B). RequestTryCount > 0 and RequestTimeout is NULL.         \
                   C). OptionCount >0 and OptionList is NULL.                  \
                   D). ClientAddress is not a valid unicast address.           \
                   - 255.255.255.255}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _DHCP4_CONFIGURE_CONF3
  EndLog
}

#
# Begin log ...
#
BeginLog
BeginScope  _DHCP4_CONFIGURE_CONF3

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

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

#
# Call [DHCP4] -> Configure with the following parameters
#   A). DiscoverTryCount > 0 and DiscoverTimeout is NULL.
#   B). RequestTryCount > 0 and RequestTimeout is NULL.
#   C). OptionCount >0 and OptionList is NULL.
#   D). ClientAddress is not a valid unicast address. - 192.168.1.255,234.0.0.1
#
SetVar    R_ConfigData.DiscoverTryCount   2
SetVar    R_ConfigData.DiscoverTimeout    0

#
# Check Point: Call Dhcp4.Configure for an DHCP instance,
#              with DiscoverTryCount > 0 and  DiscoverTimeout is NULL.
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4ConfigureConf3AssertionGuid001                   \
                "Dhcp4.Configure - DiscoverTryCount > 0 and                    \
                DiscoverTimeout is NULL"                                       \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"

SetVar    R_Timeout(0)                    2
SetVar    R_Timeout(1)                    5
SetVar    R_ConfigData.DiscoverTimeout    &@R_Timeout
SetVar    R_ConfigData.RequestTryCount    2
SetVar    R_ConfigData.RequestTimeout     0

#
# Check Point: Call Dhcp4.Configure for an DHCP instance,
#              with Dhcp4.Configure - RequestTryCount > 0 and 
#              RequestTimeout is NULL.
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4ConfigureConf3AssertionGuid002                   \
                "Dhcp4.Configure - RequestTryCount > 0 and                     \
                RequestTimeout is NULL"                                        \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"

SetVar    R_ConfigData.RequestTimeout     &@R_Timeout
SetVar    R_ConfigData.OptionCount        1
SetVar    R_ConfigData.OptionList         0

#
# Check Point: Call Dhcp4.Configure for an DHCP instance,
#              with Dhcp4.Configure - OptionCount > 0 and OptionList is NULL.
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4ConfigureConf3AssertionGuid003                   \
                "Dhcp4.Configure - OptionCount > 0 and                         \
                OptionList is NULL"                                            \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"
#
# Build an option of ClientIdentifier
#
UINT8          R_ClientIdOpt(9)
SetVar         R_ClientIdOpt(0)           61  ;#Code
SetVar         R_ClientIdOpt(1)           7   ;#Len
SetVar         R_ClientIdOpt(2)           1   ;#Hardware type & Hardware address
SetVar         R_ClientIdOpt(3)           00
SetVar         R_ClientIdOpt(4)           01
SetVar         R_ClientIdOpt(6)           03
SetVar         R_ClientIdOpt(5)           02
SetVar         R_ClientIdOpt(7)           04
SetVar         R_ClientIdOpt(8)           05

POINTER        R_OptionPtr
SetVar         R_OptionPtr                &@R_ClientIdOpt
SetVar         R_ConfigData.OptionList    &@R_OptionPtr
SetIpv4Address R_ConfigData.ClientAddress "255.255.255.255"

#
# Check Point: Call Dhcp4.Configure for an DHCP instance,
#              with a invalid unicast address.
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4ConfigureConf3AssertionGuid004                   \
                "Dhcp4.Configure - ClientAddress = 255.255.255.255"            \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"


#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment