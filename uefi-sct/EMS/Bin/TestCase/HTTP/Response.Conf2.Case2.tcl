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
CaseGuid          AEA768FC-9585-4530-9A26-76F8310962F0
CaseName          Response.Conf2.Case2
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
  EndScope _RESPONSE_CONF2_CASE2_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _RESPONSE_CONF2_CASE2_



UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Context

EFI_HTTP_RESPONSE_DATA           R_Response_Data
EFI_HTTP_HEADER                  R_Response_Headers
EFI_HTTP_MESSAGE                 R_Response_Message
EFI_HTTP_TOKEN                   R_Response_Token
EFI_HTTP_MESSAGE_DATA            R_Response_Message_Data

UINTN                            R_Response_Token_Status

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
                 &@R_Response_Token.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "BS.CreateEvent."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Response_Token_Status         $EFI_SUCCESS
SetVar R_Response_Token.Status         @R_Response_Token_Status
SetVar R_Response_Token.Message        0

#
# Check Point: Call Http.Response()
#              with NULL Token->Message.
#
Http->Response {&@R_Response_Token, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $HttpResponseConf2AssertionGuid002    \
                "Http.Request - Call Request() with NULL Token->Message."    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Clean up the environment on EUT side.
#

CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Response_Token.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
