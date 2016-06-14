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
CaseGuid        9C868BD5-7E76-4818-B596-62284D603BF5
CaseName        InfoRequest.Conf7.Case1
CaseCategory    DHCP6
CaseDescription {Test the InfoRequest Conformance of DHCP6 - Invoke InfoRequest() \
                 when Dhcp6 server doesn't response. \
                 EFI_NO_RESPONSE should be returned.
                }
################################################################################

Include DHCP6/include/Dhcp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope  _DHCP6_INFOREQUEST_CONF7_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                                   R_Status
UINTN                                   R_Handle

#
# Create child.
#
Dhcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Dhcp6SB.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

BOOLEAN                                 R_SendClientId
SetVar R_SendClientId                   FALSE

#
# Build the Option Request Option
#
EFI_DHCP6_PACKET_OPTION                 R_OptionRequest
SetVar R_OptionRequest.OpCode           $Dhcp6OptRequestOption
SetVar R_OptionRequest.OpLen            4
UINT8                                   R_OptRequestData(4)
SetVar R_OptRequestData                 {0x00 0x17 0x00 0x18}
SetVar R_OptionRequest.Data             @R_OptRequestData

UINT32                                  R_OptionCount
SetVar R_OptionCount                    0

POINTER                                 R_OptionList
SetVar R_OptionList                     0

UINT32                                  R_Retransmission(4)
#
# Retransmission parameters
# Irt 1
# Mrc 2
# Mrt 3
# Mrd 2
#
SetVar R_Retransmission                 {1 2 3 2}

UINTN                                   R_ReplyCallback
UINTN                                   R_CallbackContext
#0: NULL 1: Abort 2: DoNothing
SetVar R_ReplyCallback                  2

#
# Check point: Call InfoRequest() when Dhcp6 server doesn't response.
#              EFI_NO_RESPONSE should be returned.
#
Dhcp6->InfoRequest "@R_SendClientId, &@R_OptionRequest, @R_OptionCount, @R_OptionList, \
                                                     &@R_Retransmission, 0, @R_ReplyCallback, &@R_CallbackContext, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NO_RESPONSE]
RecordAssertion $assert $Dhcp6InfoRequestConf7AssertionGuid001         \
                        "Dhcp6.InfoRequest - Dhcp6 server doesn't response" \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NO_RESPONSE"

#
# Destroy child.
#
Dhcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# EndScope
#
EndScope _DHCP6_INFOREQUEST_CONF7_
#
# End Log 
#
EndLog

