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
CaseGuid        73F7ADF5-880D-4082-BD2A-517365FAB8CE
CaseName        Cancel.Conf2.Case1
CaseCategory    MNP
CaseDescription {Test the Cancel  Conformance of MNP - Aborts an asynchronous  \
	               transmit or receive request - Call MNP.Cancel() when Token is \
	               not NULL, but the asynchronous I/O request was not found in   \
	               transmit or receive queue.. The return status should be       \
	               EFI_NOT_FOUND.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
#Begin log ...
#
BeginLog
BeginScope _MNP_CANCEL_CONFORMANCE2_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS	Side Parameter"
#
UINTN                                 R_Status
UINTN                                 R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA       R_MnpConfData
EFI_MANAGED_NETWORK_TRANSMIT_DATA     R_TxData
EFI_MANAGED_NETWORK_FRAGMENT_DATA     R_FragData
EFI_MANAGED_NETWORK_COMPLETION_TOKEN  R_Token
RAW_ETH_PACKET_BODY                   R_Body

#
# Create Child
#
MnpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Cancel - Conf - Create Child"                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# configure this child
#
SetMnpConfigData R_MnpConfData 0 0 0 FALSE FALSE TRUE FALSE FALSE FALSE TRUE
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Cancel - Conf - Configure"                                \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Transmit 
# transmit 
#
#
# Send unicast packet
#
SetEtherTestPacket R_Body "1:1:1:1:1:1" "2:2:2:2:2:2"

SetVar R_TxData.HeaderLength          $ETH_HDR_LEN
SetVar R_TxData.DataLength            [expr [Sizeof R_Body]-$ETH_HDR_LEN]
SetVar R_TxData.FragmentCount         1
SetVar R_FragData.FragmentBuffer      &@R_Body
SetVar R_FragData.FragmentLength      [Sizeof R_Body]
SetVar R_TxData.FragmentTable         @R_FragData
SetVar R_Token.Packet.TxData          &@R_TxData


Mnp->Cancel "&@R_Token, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_FOUND]
RecordAssertion $assert $MnpCancelConf2AssertionGuid001                        \
                "Mnp.Cancel - Conf - Call Cancle when R_Token is not NULL,the    \
                asynchronous I/O request was not found in transmit or receive  \
                queue."                                                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_FOUND"

#
# Destroy Child
#
MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MnpSB.Cancel - Conf - Destroy Child1"                         \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"

EndScope  _MNP_CANCEL_CONFORMANCE2_CASE1_

#
# EndLog
#
EndLog
