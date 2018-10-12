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
CaseGuid          33E75173-1C47-4642-AFA0-2CC2FCCE3379
CaseName          Request.Conf2.Case1
CaseCategory      HTTP
CaseDescription   {This case is to test the conformance - EFI_TIMEOUT. \
                   Httpcreateconnection return EFI_TIMEOUT.}
################################################################################

Include HTTP/include/Http.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  HttpServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck
}

proc CleanUpEutEnvironmentEnd {} {
  EndScope _REQUEST_CONF2_CASE1_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _REQUEST_CONF2_CASE1_


UINTN        R_Status
UINTN        R_Handle
UINTN        R_Context

CHAR16                       R_Request_Url(30)
CHAR8                        R_Request_Headers_Name(10)
CHAR8                        R_Request_Headers_Value(30)
EFI_HTTP_REQUEST_DATA        R_Request_Data

EFI_HTTP_MESSAGE_DATA        R_Request_Message_Data
EFI_HTTP_HEADER              R_Request_Headers
UINTN                        R_Request_HeaderCount
EFI_HTTP_MESSAGE             R_Request_Message
EFI_HTTP_TOKEN               R_Request_Token

EFI_IPv4_ADDRESS                        R_Configure_LocalAddress
EFI_IPv4_ADDRESS                        R_Configure_SubnetMask
EFI_HTTPv4_ACCESS_POINT                 R_Configure_AccessPointv4
EFI_HTTP_CONFIG_DATA_ACCESSPOINT        R_Configure_AccessPoint
EFI_HTTP_CONFIG_DATA                    R_Configure_HttpConfigData



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


SetIpv4Address  R_Configure_LocalAddress                     "192.168.88.88"
SetIpv4Address  R_Configure_SubnetMask                       "255.255.255.0"
SetVar          R_Configure_AccessPointv4.UseDefaultAddress  FALSE
SetVar          R_Configure_AccessPointv4.LocalAddress       @R_Configure_LocalAddress
SetVar          R_Configure_AccessPointv4.LocalSubnet        @R_Configure_SubnetMask
SetVar          R_Configure_AccessPointv4.LocalPort          6666
SetVar          R_Configure_AccessPoint.IPv4Node             &@R_Configure_AccessPointv4


SetVar R_Configure_HttpConfigData.HttpVersion                $HttpVersion10
SetVar R_Configure_HttpConfigData.TimeOutMillisec            10
SetVar R_Configure_HttpConfigData.LocalAddressIsIPv6         FALSE
SetVar R_Configure_HttpConfigData.AccessPoint                @R_Configure_AccessPoint


Http->Configure {&@R_Configure_HttpConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "Http.Configure - Call Configure()"    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,    \
                 &@R_Request_Token.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "BS.CreateEvent."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


SetVar R_Request_Token.Status                $EFI_SUCCESS

SetVar R_Request_Url                         "http://192.168.88.1:8888"
SetVar R_Request_Data.Url                    &@R_Request_Url
SetVar R_Request_Data.Method                 $HttpMethodGet
SetVar R_Request_Message_Data.Request        &@R_Request_Data
SetVar R_Request_Message.Data                @R_Request_Message_Data

SetVar R_Request_HeaderCount                 1
SetVar R_Request_Message.HeaderCount         @R_Request_HeaderCount

SetVar R_Request_Headers.FieldName           &@R_Request_Headers_Name
SetVar R_Request_Headers.FieldValue          &@R_Request_Headers_Value
SetVar R_Request_Message.Headers             &@R_Request_Headers

SetVar R_Request_Message.BodyLength          0
SetVar R_Request_Message.Body                0

SetVar R_Request_Token.Message               &@R_Request_Message


#
# Check Point: Call Http.Request().
#
Http->Request {&@R_Request_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_TIMEOUT]
RecordAssertion $assert $HttpRequestConf2AssertionGuid001    \
                "Http.Request - Call Request()"    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_TIMEOUT"


#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Request_Token.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd










