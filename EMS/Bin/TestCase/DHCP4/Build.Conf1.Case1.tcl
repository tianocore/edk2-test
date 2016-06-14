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
CaseGuid        b86ce4c8-d4ba-454a-8395-844704ff5ec0
CaseName        Build.Conf1.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_INVALID_PARAMETER  \
	              -- SeedPacket is NULL}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _DHCP4_BUILD_CONF1
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_BUILD_CONF1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

POINTER                          R_NewPacket
UINT8                            R_Option1(10)
POINTER                          R_PtrOptList

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
# Call [DHCP4] -> Build with the invalid parameters
# o	SeedPacket is NULL
# o Option 60, Vendor Class Identifier = 'MSFT 5.0'
#
SetVar  R_Option1     { 0x3c 0x08 0x4d 0x53 0x46 0x54 0x20 0x35 0x2e 0x30}
SetVar  R_PtrOptList  &@R_Option1

#
# Check Point: Call DDhcp4->Build while SeedPacket is NULL.
#
Dhcp4->Build "NULL, 0, NULL, 1, &@R_PtrOptList, &@R_NewPacket, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4BuildConf1AssertionGuid001                       \
                "Dhcp4.Build - Call Build while SeedPacket is NULL"            \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment



