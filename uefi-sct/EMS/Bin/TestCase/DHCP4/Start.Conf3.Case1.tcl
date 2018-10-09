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
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        5ca60ebc-e01d-4a5b-9fb6-90e261602632
CaseName        Start.Conf3.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the the Conformance - EFI_ABORTED        \
                -- the user aborted the DHCP process.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

	EndCapture
  EndScope _DHCP4_START_CONF3
  EndLog
}

#
# Begin log ...
#
BeginLog
BeginScope  _DHCP4_START_CONF3

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                                       R_Status
UINTN                                       R_Handle
EFI_DHCP4_CONFIG_DATA                       R_ConfigData
UINT32                                      R_Timeout(2)
UINTN                                       R_Context

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
# Call [DHCP4]->Configure to initialize the child with the following parameters
#   o	DiscoverRetryCount=2, DiscoverTimeout=10,20
#   o	RequestRetryCount=2, RequestTimeout=10,20
#   o	ClientAddress=192.168.1.1
#   o	Dhcp4CallBack=(Self-defined-callback: Abort when in DHCP4Seleting state)
#   o	OptionCount=1, OptionList=ClientIdentifier
#
                                            
SetVar  R_Timeout(0)                        10
SetVar  R_Timeout(1)                        20
SetVar  R_ConfigData.DiscoverTryCount       2
SetVar  R_ConfigData.DiscoverTimeout        &@R_Timeout
SetVar  R_ConfigData.RequestTryCount        2
SetVar  R_ConfigData.RequestTimeout         &@R_Timeout
SetIpv4Address  R_ConfigData.ClientAddress  "192.168.1.24"
SetVar  R_ConfigData.Dhcp4Callback          1; #Callback[list1]=Aborted 
SetVar  R_ConfigData.CallbackContext        &@R_Context

Dhcp4->Configure  "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Configure - Configure Child 1"                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Dhcp4.Start when the user aborted the DHCP process.
# o		CompletionEvnet = NULL
#
Dhcp4->Start "0, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ABORTED] 
RecordAssertion $assert $Dhcp4StartConf3AssertionGuid001                       \
                "Dhcp4.Start - User Abort the config process"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ABORTED"

#
# Call Dhcp4->Stop to stop the driver
#
Dhcp4->Stop "&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Stop DHCP Driver"                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment