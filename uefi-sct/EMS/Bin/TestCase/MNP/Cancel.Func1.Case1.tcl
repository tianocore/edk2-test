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
CaseGuid        F5768212-B2BF-4110-9030-2B2EAA60B06E
CaseName        Cancel.Func1.Case1
CaseCategory    MNP
CaseDescription {Test the Cancel function of MNP - Call MNP.Cancel() when      \
	               Token is NULL. }
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope  _MNP_CANCEL_FUNCTION1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS	Side Parameter"
#
UINTN                                 R_Status
UINTN                                 R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA       R_MnpConfData
EFI_MANAGED_NETWORK_COMPLETION_TOKEN  R_Token(10)
UINTN                                 R_Context
#
# Create Child
#
MnpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Cancel - Func - Create Child"                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure Child
#
SetMnpConfigData R_MnpConfData 0 0 0 FALSE FALSE FALSE FALSE FALSE FALSE TRUE
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Cancel - Func - Start Child"                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Receive with Token
#
#
# Empty Receive Queue
#
SetVar  R_Context   1
GetVar  R_Context
while { $R_Context == 1 } {
  SetVar          R_Context 0
  BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,      \
                  &@R_Token(0).Event, &@R_Status"
  GetAck
  Mnp->Receive    "&@R_Token(0), &@R_Status"
  GetAck
  set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
  if { [string compare -nocase $assert "fail" ] == 0} {
    EndScope  _MNP_CANCEL_FUNCTION1_CASE1_
    EndLog
    exit
  }
  GetVar          R_Context
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Cancel - Func - Chk Ret Code"                             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Cancel with Token1
#
Mnp->Cancel "&@R_Token(0), &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $MnpCancleFunc1AssertionGuid001                        \
                "Mnp.Cancel - Func - Call Cancel() to aborts an                \
                asynchronous transmit or receive request."                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check R_Context
#
GetVar  R_Context
set assert pass
if {1 != $R_Context} {
  set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Cancel - Func - Check R_Context"                            \
                "Return R_Context - $R_Context, Expected R_Context - 1"

#
# Check R_Token.Status
#
GetVar  R_Token(0)
set assert fail
if { ${R_Token(0).Status} == $EFI_ABORTED } {
  set assert pass
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mnp.Cancel - Func - Chk Ret Code"                             \
                "ReturnStatus - ${R_Token(0).Status}, ExpectedStatus - $EFI_ABORTED" 

#
# Destroy Child
#
MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MnpSB.Cancel - Func - Destroy Child1"                         \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_SUCCESS"

EndScope    _MNP_CANCEL_FUNCTION1_CASE1_

#
# EndLog
#
EndLog
