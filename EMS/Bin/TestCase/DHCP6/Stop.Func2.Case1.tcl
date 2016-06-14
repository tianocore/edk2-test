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
CaseGuid        B5A4CA16-C0EE-45d6-8B01-466E68B4005A
CaseName        Stop.Func2.Case1
CaseCategory    DHCP6

CaseDescription {Test the Stop Function of DHCP6 - Invoke Stop() to stop the  \
                 Dhcpv6 S.A.R.R process,when the instance is in Dhcp6Init state.	             
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
BeginScope  _DHCP6_STOP_FUNC2_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

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

EFI_DHCP6_CONFIG_DATA                   R_ConfigData
#
# SolicitRetransmission parameters
# Irt 1
# Mrc 2
# Mrt 3
# Mrd 2
#
UINT32                                  R_SolicitRetransmission(4)
SetVar R_SolicitRetransmission          {1 2 3 2}
#
# Call Configure() to configure this child
# o Dhcp6Callback              2          0:NULL 1:Abort 2:CallbackContext++
# o CallbackContext            0          
# o OptionCount                0        
# o OptionList                 0          
# o IaDescriptor               Type=Dhcp6IATypeNA IaId=1
# o IaInfoEvent                Not NULL          
# o ReconfigureAccept          FALSE
# o RapidCommit                FALSE
# o SolicitRetransmission      defined above
#

UINTN                                          R_Dhcp6CallbackContext
SetVar R_Dhcp6CallbackContext                  0

SetVar R_ConfigData.Dhcp6Callback              2;     #0:NULL 1:Abort 2:CallbackContext++
SetVar R_ConfigData.CallbackContext            &@R_Dhcp6CallbackContext
SetVar R_ConfigData.OptionCount                0
SetVar R_ConfigData.OptionList                 0
SetVar R_ConfigData.IaDescriptor.Type          $Dhcp6IATypeNA
SetVar R_ConfigData.IaDescriptor.IaId          1
SetVar R_ConfigData.IaInfoEvent                0
SetVar R_ConfigData.ReconfigureAccept          FALSE
SetVar R_ConfigData.RapidCommit                FALSE
SetVar R_ConfigData.SolicitRetransmission      &@R_SolicitRetransmission

#
# Configure this child
#
Dhcp6->Configure  "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid  \
                "Dhcp6.Configure - Configure Child 1"          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: After call the Configure function the state of instance should be Dhcp6Init.
#
EFI_DHCP6_MODE_DATA             R_Dhcp6ModeData
EFI_DHCP6_CONFIG_DATA           R_Dhcp6CfgData
Dhcp6->GetModeData "&@R_Dhcp6ModeData, &@R_Dhcp6CfgData, &@R_Status"
GetAck

GetVar        R_Dhcp6ModeData
EFI_DHCP6_IA  R_Ia
UINTN         R_CopyLen
SetVar  R_CopyLen  [Sizeof R_Ia]
BS->CopyMem  "&@R_Ia, @R_Dhcp6ModeData.Ia, @R_CopyLen, &@R_Status"
GetAck

GetVar  R_Ia.State
set assert fail
if { ${R_Ia.State} == $Dhcp6Init } {
    set assert pass
}
RecordAssertion $assert  $GenericAssertionGuid   \
                "When Configure successfully returns, the state of IA should be Dhcp6Init"	

#
# Check point: Call Stop function when the instance is in Dhcp6Init state.It should return EFI_SUCCESS.
#
Dhcp6->Stop "&@R_Status"
GetAck
set assert  [VerifyReturnStatus  R_Status $EFI_SUCCESS]
RecordAssertion $assert   $Dhcp6StopFunc2AssertionGuid001   \
                "Dhcp6.Stop- Call Stop to stop the Dhcpv6 S.A.R.R process when the instance is in Dhcp6Init state"\
                "ReturnStatus-$R_Status, ExpectStatus- $EFI_SUCCESS"

#
# DestroyChild.
#
Dhcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# End scope
#
EndScope _DHCP6_STOP_FUNC2_
#
# End Log
#
EndLog
