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
CaseGuid          9B735919-A37E-4480-A49A-F0C7F47BBB9C
CaseName          Cancel.Conf1.Case1
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
  EndScope _HTTP_SPEC_CONFORMANCE_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _HTTP_SPEC_CONFORMANCE_

UINTN        R_Status
UINTN        R_Handle

EFI_HTTP_TOKEN        R_HTTP_Token

#
# Create Child.
#
HttpServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "HttpSBP.CreateChild - Create Child 1"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_HTTP_Token 0

Http->Cancel "&@R_HTTP_Token, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $HttpCancelConf1AssertionGuid001                     \
                "Http.Cancel - Call Cancel() without a configuration."     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

#
# Clean up the environment on EUT side.
#

CleanUpEutEnvironmentBegin

CleanUpEutEnvironmentEnd
