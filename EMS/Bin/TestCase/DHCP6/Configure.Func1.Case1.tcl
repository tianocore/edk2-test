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
CaseGuid        CAD1B5E7-7DB8-41a2-9405-5D2F19DC5AA6
CaseName        Configure.Func1.Case1
CaseCategory    DHCP6

CaseDescription {Test the Configure Function of DHCP6 - Invoke Configure() \
                 to initialize or clean up the configuration data.
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
BeginScope  _DHCP6_CONFIGURE_FUNC1_

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
                "Dhcp6SB.CreateChild - Create Child "                       \
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
# o Dhcp6Callback              0          0:NULL 1:Abort 2:CallbackContext++
# o CallbackContext            0          
# o OptionCount                0        
# o OptionList                 0          
# o IaDescriptor               Type=Dhcp6IATypeNA IaId=1
# o IaInfoEvent                Not NULL          
# o ReconfigureAccept          FALSE
# o RapidCommit                FALSE
# o SolicitRetransmission      defined above
#

#
# Create Event for IaInfoEvent. When signaled, EventContext will be increased by 1.
#
UINTN                                          R_IaInfoEvent
UINTN                                          R_IaInfoEventContext
SetVar R_IaInfoEventContext                    0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_IaInfoEventContext,        \
                                     &@R_IaInfoEvent, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "BS.CreateEvent - Create event for IaInfoEvent."                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_ConfigData.Dhcp6Callback              0
SetVar R_ConfigData.CallbackContext            0
SetVar R_ConfigData.OptionCount                0
SetVar R_ConfigData.OptionList                 0
SetVar R_ConfigData.IaDescriptor.Type          $Dhcp6IATypeNA
SetVar R_ConfigData.IaDescriptor.IaId          1
SetVar R_ConfigData.IaInfoEvent                @R_IaInfoEvent
SetVar R_ConfigData.ReconfigureAccept          FALSE
SetVar R_ConfigData.RapidCommit                FALSE
SetVar R_ConfigData.SolicitRetransmission      &@R_SolicitRetransmission

#
# Configure this child
#
Dhcp6->Configure  "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp6ConfigureFunc1AssertionGuid001  \
                "Dhcp6.Configure - Configure Child 1"          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# First call Configure with Dhcp6ConfigData is NULL
#
Dhcp6->Configure  "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp6ConfigureFunc1AssertionGuid002  \
                "Dhcp6.Configure - Configure Child "          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
           
#
# Check point: Call GetModeData()
#
EFI_DHCP6_MODE_DATA      R_Dhcp6ModeData
Dhcp6->GetModeData "&@R_Dhcp6ModeData, NULL,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Dhcp6.GetModeData - Retrieve mode data and config data"  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

set assert  fail
GetVar      R_Dhcp6ModeData.ClientId
if { ${R_Dhcp6ModeData.ClientId} != 0} {
    set assert pass
}
RecordAssertion $assert   $Dhcp6ConfigureFunc1AssertionGuid003  \
                "Dhcp6.GetModeData - Func -Dhcp6ModeData.ClientId should not be NULL"

set assert  fail
GetVar      R_Dhcp6ModeData.Ia
if { ${R_Dhcp6ModeData.Ia}== 0} {
   set assert pass
}
RecordAssertion $assert  $Dhcp6ConfigureFunc1AssertionGuid004 \
                "Dhcp6.GetModeData -Func -Dhcp6ModeData.Ia should be NULL"

#
# Close Event
#
BS->CloseEvent    "@R_IaInfoEvent, &@R_Status"
GetAck

#
# DestroyChild.
#
Dhcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# End scope
#
EndScope _DHCP6_CONFIGURE_FUNC1_
#
# End Log
#
EndLog
