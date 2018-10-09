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
############################################
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        80bcccbf-0f50-4e00-ab25-522603c57f6a
CaseName        Start.Conf4.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the the Conformance - EFI_ALREADY_STARTED\
                --start while another instance already started the DHCP process}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle1, &@R_Status"
  GetAck

  Dhcp4ServiceBinding->DestroyChild "@R_Handle2, &@R_Status"
  GetAck

  BS->CloseEvent "@R_Event, &@R_Status"
  GetAck
  
  EndScope _DHCP4_START_CONF4
  EndLog
}

#
# Begin log ...
#
BeginLog
BeginScope  _DHCP4_START_CONF4

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle1
UINTN                            R_Handle2
UINTN                            R_Event
UINTN                            R_Context

#
# Call [DHCP4SBP] -> CreateChild to create child1.
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle1, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# Call [DHCP4SBP] -> CreateChild to create child2
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle2, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 2"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                
#
# Call [DHCP4]->Configure to initialize the child1 with the following parameters
# o	DiscoverRetryCount=2, DiscoverTimeout=5,10
# o	RequestRetryCount=2, RequestTimeout=5,10
# o	ClientAddress=0.0.0.0
# o	Dhcp4CallBack=NULL
# o	OptionCount=1, OptionList=ClientIdentifier
#
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1

EFI_DHCP4_CONFIG_DATA           R_ConfigData
UINT32                          R_Timeout(2)

SetVar  R_Timeout(0)                        5
SetVar  R_Timeout(1)                        10
SetVar  R_ConfigData.DiscoverTryCount       2
SetVar  R_ConfigData.DiscoverTimeout        &@R_Timeout
SetVar  R_ConfigData.RequestTryCount        2
SetVar  R_ConfigData.RequestTimeout         &@R_Timeout
SetIpv4Address  R_ConfigData.ClientAddress  "0.0.0.0"
SetVar  R_ConfigData.Dhcp4Callback          0;  # CallbackList[0] = NULL
SetVar  R_ConfigData.CallbackContext        0

#
# Build an option of ClientIdentifier
#
UINT8     R_ClientIdOpt(9)
SetVar    R_ClientIdOpt   {61 7 1 0 1 2 3 4 5}
POINTER   R_OptionPtr
SetVar    R_OptionPtr                   &@R_ClientIdOpt
SetVar    R_ConfigData.OptionCount      1
SetVar    R_ConfigData.OptionList       &@R_OptionPtr
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Configure Child 1"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# Create Event
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                &@R_Event, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> Start to start DHCP4 configuration process on child1
# o	CompletionEvnet = NULL
#
Dhcp4->Start  "@R_Event, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Start DHCP4 config process on Child 1."         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Dhcp4.Start while another instance already started 
#              the DHCP process.
#
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2
Dhcp4->Start  "0, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_ALREADY_STARTED]
RecordAssertion $assert $Dhcp4StartConf4AssertionGuid001                       \
                "Dhcp4.Start - Start config process on Child2 while Child1     \
                already started."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_ALREADY_STARTED"

Dhcp4->Stop	"&@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Stop - Stop Driver on Child1"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1
Dhcp4->Stop	"&@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Stop - Stop Driver on Child2"                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment
