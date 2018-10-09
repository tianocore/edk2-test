# 
#  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
# 
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
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
