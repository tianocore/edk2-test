# 
#  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
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

#
# test case Name, category, description, GUID...
#
CaseGuid          BA421B49-FBAB-455d-98CD-45AC8DF36A43
CaseName          Request.Conf3.Case2
CaseCategory      HTTP
CaseDescription   {This case is to test the conformance - EFI_INVALID_PARAMETER.     \
                   -- Token->Message is NULL.}
################################################################################

Include HTTP/include/Http.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  HttpServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck
}

proc CleanUpEutEnvironmentEnd {} {
  EndScope _REQUEST_CONF3_CASE2_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _REQUEST_CONF3_CASE2_


UINTN        R_Status
UINTN        R_Handle
UINTN        R_Context

UINTN                 R_Request_Token_Status
EFI_HTTP_TOKEN        R_Request_Token


#
# Create Http Child.
#
HttpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "HttpSBP.CreateChild - Create Child 1"    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"



BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,    \
                 &@R_Request_Token.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "BS.CreateEvent."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Request_Token.Status               @R_Request_Token_Status
SetVar R_Request_Token.Message              0

#
# Check Point: Call Http.Request()
#              with NULL Token->Message.
#
Http->Request {&@R_Request_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $HttpRequestConf3AssertionGuid002    \
                "Http.Request - Call Request() with NULL Token->Message."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"


#
# Clean up the environment on EUT side.
#

CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Request_Token.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
