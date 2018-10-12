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
CaseGuid          74E37C30-B50D-4fdf-9604-8E249687802D
CaseName          Request.Conf1.Case1
CaseCategory      HTTP
CaseDescription   {This case is to test the conformance - EFI_NOT_STARTED.    \
                   -- This EFI HTTP Protocol instance has not been configured.}
################################################################################

Include HTTP/include/Http.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  HttpServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck
}

proc CleanUpEutEnvironmentEnd {} {
  EndScope _REQUEST_CONF1_CASE1_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _REQUEST_CONF1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#

UINTN        R_Status
UINTN        R_Handle
UINTN        R_Context

CHAR16                       R_Request_Url(30)
EFI_HTTP_REQUEST_DATA        R_Request_Data
EFI_HTTP_MESSAGE_DATA        R_Request_Message_Data
UINTN                        R_Request_HeaderCount
EFI_HTTP_HEADER              R_Request_Headers
EFI_HTTP_MESSAGE             R_Request_Message
EFI_HTTP_TOKEN               R_Request_Token



#
# Create Child.
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

SetVar R_Request_Token.Status                 $EFI_SUCCESS

SetVar R_Request_Url                         "http://192.168.88.1:8888"
SetVar R_Request_Data.Url                    &@R_Request_Url
SetVar R_Request_Data.Method                 $HttpMethodGet
SetVar R_Request_Message_Data.Request        &@R_Request_Data
SetVar R_Request_Message.Data                @R_Request_Message_Data

SetVar R_Request_HeaderCount                 1
SetVar R_Request_Message.HeaderCount         @R_Request_HeaderCount

SetVar R_Request_Headers.FieldName           0
SetVar R_Request_Headers.FieldValue          0
SetVar R_Request_Message.Headers             &@R_Request_Headers

SetVar R_Request_Message.BodyLength          0
SetVar R_Request_Message.Body                0

SetVar R_Request_Token.Message               &@R_Request_Message


Http->Request {&@R_Request_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $HttpRequestConf1AssertionGuid001    \
                "Http.Request - Call Request() without a configuration."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Request_Token.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
