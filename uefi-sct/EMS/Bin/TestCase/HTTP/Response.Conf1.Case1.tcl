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
CaseGuid          06946A35-FF0A-4dd7-A1D6-36B9851AC79B
CaseName          Response.Conf1.Case1
CaseCategory      HTTP
CaseDescription   {This case is to test the conformance - EFI_NOT_STARTED.     \
                   -- This EFI HTTP Protocol instance has not been configured.}
################################################################################

Include HTTP/include/Http.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  HttpServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

}

proc CleanUpEutEnvironmentEnd {} {
  EndScope _RESPONSE_CONF1_CASE1_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _RESPONSE_CONF1_CASE1_


#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#

UINTN        R_Status
UINTN        R_Handle
UINTN        R_Context

EFI_HTTP_RESPONSE_DATA        R_Response_Data
EFI_HTTP_MESSAGE_DATA         R_Response_Message_Data;

EFI_HTTP_MESSAGE              R_Response_Message
EFI_HTTP_TOKEN                R_Response_Token


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
                 &@R_Response_Token.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "BS.CreateEvent."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"



SetVar R_Response_Data.StatusCode             $EFI_SUCCESS
SetVar R_Response_Message_Data.Response       &@R_Response_Data

SetVar R_Response_Message.Data                @R_Response_Message_Data
SetVar R_Response_Message.HeaderCount         0
SetVar R_Response_Message.Headers             0

SetVar R_Response_Message.BodyLength          0
SetVar R_Response_Message.Body                0

SetVar R_Response_Token.Status                $EFI_SUCCESS
SetVar R_Response_Token.Message               &@R_Response_Message



Http->Response {&@R_Response_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $HttpResponseConf1AssertionGuid001    \
                "Http.Response - Call Response() without a configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

#
# Clean up the environment on EUT side.
#

CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Response_Token.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
