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
CaseGuid        350BFB10-0D56-4f39-82BA-BC91D79BE0CA
CaseName        CreateDestroyChild.Func1.Case1
CaseCategory    TCP6
CaseDescription {Test the Function of CreateDestroyChild of TCP6 - CreateDestroyChild\
                 must succeed with valid parameters.}
################################################################################

Include TCP6/include/Tcp6.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _TCP6SB_CREATEDESTROYCHILD_FUNC1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Handle1
UINTN                            R_Handle2
UINTN                            R_Status1
UINTN                            R_Status2

#
#Check Point: Create Child with valid parameters
#
Tcp6ServiceBinding->CreateChild "&@R_Handle1, &@R_Status1"
GetAck
set assert [VerifyReturnStatus R_Status1 $EFI_SUCCESS]
RecordAssertion $assert $Tcp6CreateDestroyChildFunc1AssertionGuid001                  \
                "Tcp6SBP.CreateChild - Create ChildHandle, returns EFI_SUCCESS."                   \
                "ReturnStatus - $R_Status1, ExpectedStatus - $EFI_SUCCESS"

Tcp6ServiceBinding->CreateChild "&@R_Handle2, &@R_Status2"
GetAck
set assert [VerifyReturnStatus R_Status2 $EFI_SUCCESS]
RecordAssertion $assert $Tcp6CreateDestroyChildFunc1AssertionGuid002                  \
                "Tcp6SBP.CreateChild - Create ChildHandle, returns EFI_SUCCESS."                   \
                "ReturnStatus - $R_Status2, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Destroy Child with valid parameters
#
Tcp6ServiceBinding->DestroyChild "@R_Handle1, &@R_Status1"
GetAck
set assert [VerifyReturnStatus R_Status1 $EFI_SUCCESS]
RecordAssertion $assert $Tcp6CreateDestroyChildFunc1AssertionGuid003                  \
                "Tcp6SBP.DestroyChild - Destroy ChildHandle, returns EFI_SUCCESS."                   \
                "ReturnStatus - $R_Status1, ExpectedStatus - $EFI_SUCCESS"

Tcp6ServiceBinding->DestroyChild "@R_Handle2, &@R_Status2"
GetAck
set assert [VerifyReturnStatus R_Status2 $EFI_SUCCESS]
RecordAssertion $assert $Tcp6CreateDestroyChildFunc1AssertionGuid004                  \
                "Tcp6SBP.DestroyChild - Destroy ChildHandle, returns EFI_SUCCESS."                   \
                "ReturnStatus - $R_Status2, ExpectedStatus - $EFI_SUCCESS"
 
#
# EndScope
#
EndScope   _TCP6SB_CREATEDESTROYCHILD_FUNC1_CASE1_

#
# End log
#
EndLog
